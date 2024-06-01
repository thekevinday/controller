#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_main_thread_entry_
  void * controller_main_thread_entry(void * const arguments) {

    if (!arguments) return 0;

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_global_t * const global = (controller_global_t * const) arguments;

    if (!controller_main_thread_is_enabled(F_true, global->thread)) return 0;

    f_status_t * const status = &global->thread->status;

    *status = controller_main_entry_read(global, F_true);

    if (F_status_set_fine(*status) == F_interrupt) {
      global->program->ready = controller_setting_ready_abort_e;
    }
    else if (F_status_is_error(*status)) {
      global->program->ready = controller_setting_ready_fail_e;
    }
    else if (*status != F_child) {
      *status = controller_main_entry_preprocess(global, F_true);

      if ((global->main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e) && (global->main->program.parameters.array[controller_parameter_validate_e].result & f_console_result_found_e)) {
        controller_main_entry_setting_validate(global, F_true);
      }
    }

    if (F_status_is_error_not(*status) && *status != F_child) {
      if (!(global->main->program.parameters.array[controller_parameter_validate_e].result & f_console_result_found_e) || (global->main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e)) {

        if (global->program->entry.pid == controller_entry_pid_require_e && f_file_exists(global->program->path_pid, F_true) == F_true) {
          *status = F_status_set_error(F_available_not);
          global->program->ready = controller_setting_ready_fail_e;

          controller_main_print_error_file_pid_exists(&global->main->program.error, global->thread, global->program->path_pid);
        }
        else {
          *status = controller_main_entry_process(global, F_false, F_true);

          if (F_status_is_error(*status)) {
            global->program->ready = controller_setting_ready_fail_e;

            if ((F_status_set_fine(*status) == F_execute || F_status_set_fine(*status) == F_require) && (program->flag & controller_setting_flag_failsafe_e)) {
              const uint8_t original_enabled = global->thread->enabled;

              // Restore operating mode so that the failsafe can execute.
              *status = f_thread_mutex_lock(&global->thread->lock.alert);

              if (F_status_is_error_not(*status)) {
                global->thread->enabled = controller_thread_enabled_e;

                f_thread_mutex_unlock(&global->thread->lock.alert);
              }

              // Restart the signal global->thread to allow for signals while operating the failsafe Items.
              if (!global->thread->id_signal) {
                f_thread_create(0, &global->thread->id_signal, &controller_main_thread_signal_normal, (void *) global);
              }

              const f_status_t status_failsafe = controller_main_entry_process(global, F_true, F_true);

              if (F_status_is_error(status_failsafe)) {
                *status = F_status_set_error(F_failure);

                controller_main_print_error_failsafe_item(&global->main->program.error, global->thread, global->program->entry.items.array[program->failsafe_item_id].name);
              }
              else {

                // Restore operating mode to value prior to failsafe mode.
                *status = f_thread_mutex_lock(&global->thread->lock.alert);

                if (F_status_is_error_not(*status)) {
                  global->thread->enabled = original_enabled;

                  f_thread_mutex_unlock(&global->thread->lock.alert);
                }

                *status = F_failure;
              }
            }
          }
          else if (F_status_set_fine(*status) == F_interrupt) {
            global->program->ready = controller_setting_ready_abort_e;
          }
          else if (*status != F_child) {
            global->program->ready = controller_setting_ready_done_e;
          }
        }

        if (F_status_is_error_not(*status) && *status != F_child && global->main->program.parameters.array[controller_parameter_validate_e].result == f_console_result_none_e && global->program->mode == controller_setting_mode_helper_e) {
          f_time_spec_t time;
          time.tv_sec = controller_main_thread_exit_helper_timeout_seconds_d;
          time.tv_nsec = controller_main_thread_exit_helper_timeout_nanoseconds_d;

          nanosleep(&time, 0);

          controller_main_thread_process_cancel(global, F_true, controller_thread_cancel_exit_e);
        }
      }
    }

    if (*status == F_child) {

      // A forked child process should deallocate memory on exit.
      // It seems that this function doesn't return to the calling thread for a forked child process, even with the "return 0;" below.
      controller_main_thread_delete(global->thread);
      controller_main_program_delete(global->program);
      controller_main_delete(global->main);

      // According to the manpages, pthread_exit() calls exit(0), which the value of global->main->program.child should be returned instead.
      if (global->main->program.child) exit(global->main->program.child);

      return 0;
    }

    f_thread_condition_signal_all(&global->thread->lock.alert_condition);

    return 0;
  }
#endif // _di_controller_main_thread_entry_

#ifndef _di_controller_main_thread_exit_
  void * controller_main_thread_exit(void * const arguments) {

    if (!arguments) return 0;

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_global_t * const global = (controller_global_t * const) arguments;

    controller_main_t * const main = global->main;
    controller_cache_t * const cache = &global->thread->cache;
    f_status_t * const status = &global->thread->status;

    *status = controller_entry_read(global, F_false);

    if (F_status_set_fine(*status) == F_interrupt) {
      global->program->ready = controller_setting_ready_abort_e;
    }
    else if (F_status_is_error(*status)) {
      global->program->ready = controller_setting_ready_fail_e;
    }
    else if (*status == F_file_found_not) {
      global->program->ready = controller_setting_ready_done_e;
    }
    else if (*status != F_child) {
      *status = controller_entry_preprocess(global, F_false, cache);

      if ((main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e) && (main->program.parameters.array[controller_parameter_validate_e].result & f_console_result_found_e)) {
        controller_entry_setting_validate(global, F_false, cache);
      }
    }

    if (F_status_is_error_not(*status) && *status != F_child && *status != F_file_found_not) {
      if (!(main->program.parameters.array[controller_parameter_validate_e].result & f_console_result_found_e) || (main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e)) {

        *status = controller_entry_process(global, F_false, F_false);

        if (F_status_is_error(*status)) {
          global->program->ready = controller_setting_ready_fail_e;

          if ((F_status_set_fine(*status) == F_execute || F_status_set_fine(*status) == F_require) && (global->program->flag & controller_setting_flag_failsafe_e)) {

            const uint8_t original_enabled = global->thread->enabled;

            // Restore operating mode so that the failsafe can execute.
            if (F_status_set_fine(*status) == F_execute) {
              *status = f_thread_mutex_lock(&global->thread->lock.alert);

              if (F_status_is_error_not(*status)) {
                global->thread->enabled = controller_thread_enabled_exit_e;

                f_thread_mutex_unlock(&global->thread->lock.alert);
              }

              // Restart the signal thread to allow for signals while operating the failsafe Items.
              if (!global->thread->id_signal) {
                f_thread_create(0, &global->thread->id_signal, &controller_main_thread_signal_other, (void *) global);
              }
            }

            const f_status_t status_failsafe = controller_entry_process(global, F_true, F_false);

            if (F_status_is_error(status_failsafe)) {
              *status = F_status_set_error(F_failure);

              controller_main_print_error_failsafe_item(&global->main->program.error, global->thread, global->program->entry.items.array[program->failsafe_item_id].name);
            }
            else {

              // Restore operating mode to value prior to failsafe mode.
              *status = f_thread_mutex_lock(&global->thread->lock.alert);

              if (F_status_is_error_not(*status)) {
                global->thread->enabled = original_enabled;

                f_thread_mutex_unlock(&global->thread->lock.alert);
              }

              *status = F_failure;
            }
          }
        }
        else if (F_status_set_fine(*status) == F_interrupt) {
          global->program->ready = controller_setting_ready_abort_e;
        }
        else if (*status != F_child) {
          global->program->ready = controller_setting_ready_done_e;
        }
      }
    }

    if (*status == F_child) {

      // A forked child process should deallocate memory on exit.
      // It seems that this function doesn't return to the calling thread for a forked child process, even with the "return 0;" below.
      controller_thread_delete_simple(global->thread);
      controller_process_delete(global->program);
      controller_main_delete(main);

      return 0;
    }

    if (F_status_is_error_not(f_thread_mutex_lock(&global->thread->lock.alert))) {
      global->thread->enabled = controller_thread_enabled_not_e;

      f_thread_mutex_unlock(&global->thread->lock.alert);
    }

    f_thread_condition_signal_all(&global->thread->lock.alert_condition);

    return 0;
  }
#endif // _di_controller_main_thread_exit_

#ifdef __cplusplus
} // extern "C"
#endif
