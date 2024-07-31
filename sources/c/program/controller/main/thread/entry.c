#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_thread_entry_
  void * controller_thread_entry(void * const argument) {

    if (!argument) return 0;

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_t * const main = (controller_t *) argument;

    if (!controller_thread_is_enabled(&main->thread, F_true)) return 0;

    f_status_t * const status = &main->thread.status;

    *status = controller_entry_read(main, F_true);

    if (F_status_set_fine(*status) == F_interrupt) {
      main->process.ready = controller_process_ready_abort_e;
    }
    else if (F_status_is_error(*status)) {
      main->process.ready = controller_process_ready_fail_e;
    }
    else if (*status != F_child) {
      *status = controller_entry_preprocess(main, F_true);

      if ((main->setting.flag & controller_main_flag_simulate_d) && (main->setting.flag & controller_main_flag_validate_d)) {
        controller_print_output_entry_setting_validate(&main->program.output, F_true);
      }
    }

    if (F_status_is_error_not(*status) && *status != F_child) {
      if (!(main->setting.flag & controller_main_flag_validate_d) || (main->setting.flag & controller_main_flag_simulate_d)) {
        if (main->process.entry.pid == controller_entry_pid_require_e && f_file_exists(main->process.path_pid, F_true) == F_true) {
          *status = F_status_set_error(F_available_not);
          main->process.ready = controller_process_ready_fail_e;

          controller_print_error_file_pid_exists(&main->program.error, &main->thread, main->process.path_pid);
        }
        else {
          *status = controller_entry_process(main, F_true, F_false);

          if (F_status_is_error(*status)) {
            main->process.ready = controller_process_ready_fail_e;

            if ((F_status_set_fine(*status) == F_execute || F_status_set_fine(*status) == F_require) && (main->process.flag & controller_process_flag_failsafe_e)) {
              const uint8_t original_enabled = main->thread.enabled;

              // Restore operating mode so that the failsafe can execute.
              *status = f_thread_mutex_lock(&main->thread.lock.alert);

              if (F_status_is_error_not(*status)) {
                main->thread.enabled = controller_thread_enabled_e;

                f_thread_mutex_unlock(&main->thread.lock.alert);
              }

              // Restart the signal main->thread to allow for signals while operating the failsafe Items.
              if (!main->thread.id_signal) {
                f_thread_create(0, &main->thread.id_signal, &controller_thread_signal_normal, (void *) main);
              }

              const f_status_t status_failsafe = controller_entry_process(main, F_true, F_true);

              if (F_status_is_error(status_failsafe)) {
                *status = F_status_set_error(F_failure);

                controller_print_error_failsafe_item(&main->program.error, &main->thread, main->process.entry.items.array[main->process.failsafe_item_id].name);
              }
              else {

                // Restore operating mode to value prior to failsafe mode.
                *status = f_thread_mutex_lock(&main->thread.lock.alert);

                if (F_status_is_error_not(*status)) {
                  main->thread.enabled = original_enabled;

                  f_thread_mutex_unlock(&main->thread.lock.alert);
                }

                *status = F_failure;
              }
            }
          }
          else if (F_status_set_fine(*status) == F_interrupt) {
            main->process.ready = controller_process_ready_abort_e;
          }
          else if (*status != F_child) {
            main->process.ready = controller_process_ready_done_e;
          }
        }

        if (F_status_is_error_not(*status) && *status != F_child && !(main->setting.flag & controller_main_flag_validate_d) && main->process.mode == controller_process_mode_helper_e) {
          const f_time_spec_t time = macro_f_time_spec_t_initialize_1(controller_thread_timeout_exit_helper_seconds_d, controller_thread_timeout_exit_helper_nanoseconds_d);

          f_time_sleep_spec(time, 0);

          controller_thread_instance_cancel(main, F_true, controller_thread_cancel_exit_e);
        }
      }
    }

    // A forked child process should de-allocate memory on exit.
    // It seems that this function doesn't return to the calling thread for a forked child process, even with the "return 0;" below.
    if (*status == F_child) {
      controller_delete(main);

      // According to the manpages, pthread_exit() calls exit(0), which the value of main->program.child should be returned instead.
      if (main->program.child) exit(main->program.child);
    } else {
      f_thread_condition_signal_all(&main->thread.lock.alert_condition);
    }

    return 0;
  }
#endif // _di_controller_thread_entry_

#ifndef _di_controller_thread_exit_
  void * controller_thread_exit(void * const argument) {

    if (!argument) return 0;

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_t * const main = (controller_t *) argument;
    f_status_t * const status = &main->thread.status;

    *status = controller_entry_read(main, F_false);

    if (F_status_set_fine(*status) == F_interrupt) {
      main->process.ready = controller_process_ready_abort_e;
    }
    else if (F_status_is_error(*status)) {
      main->process.ready = controller_process_ready_fail_e;
    }
    else if (*status == F_file_found_not) {
      main->process.ready = controller_process_ready_done_e;
    }
    else if (*status != F_child) {
      *status = controller_entry_preprocess(main, F_false);

      if ((main->setting.flag & controller_main_flag_simulate_d) && (main->setting.flag & controller_main_flag_validate_d)) {
        controller_print_output_entry_setting_validate(&main->program.output, F_false);
      }
    }

    if (F_status_is_error_not(*status) && *status != F_child && *status != F_file_found_not) {
      if (!(main->setting.flag & controller_main_flag_validate_d) || (main->setting.flag & controller_main_flag_simulate_d)) {

        *status = controller_entry_process(main, F_false, F_false);

        if (F_status_is_error(*status)) {
          main->process.ready = controller_process_ready_fail_e;

          if ((F_status_set_fine(*status) == F_execute || F_status_set_fine(*status) == F_require) && (main->process.flag & controller_process_flag_failsafe_e)) {

            const uint8_t original_enabled = main->thread.enabled;

            // Restore operating mode so that the failsafe can execute.
            if (F_status_set_fine(*status) == F_execute) {
              *status = f_thread_mutex_lock(&main->thread.lock.alert);

              if (F_status_is_error_not(*status)) {
                main->thread.enabled = controller_thread_enabled_exit_e;

                f_thread_mutex_unlock(&main->thread.lock.alert);
              }

              // Restart the signal thread to allow for signals while operating the failsafe Items.
              if (!main->thread.id_signal) {
                f_thread_create(0, &main->thread.id_signal, &controller_thread_signal_other, (void *) main);
              }
            }

            const f_status_t status_failsafe = controller_entry_process(main, F_false, F_true);

            if (F_status_is_error(status_failsafe)) {
              *status = F_status_set_error(F_failure);

              controller_print_error_failsafe_item(&main->program.error, &main->thread, main->process.entry.items.array[main->process.failsafe_item_id].name);
            }
            else {

              // Restore operating mode to value prior to failsafe mode.
              *status = f_thread_mutex_lock(&main->thread.lock.alert);

              if (F_status_is_error_not(*status)) {
                main->thread.enabled = original_enabled;

                f_thread_mutex_unlock(&main->thread.lock.alert);
              }

              *status = F_failure;
            }
          }
        }
        else if (F_status_set_fine(*status) == F_interrupt) {
          main->process.ready = controller_process_ready_abort_e;
        }
        else if (*status != F_child) {
          main->process.ready = controller_process_ready_done_e;
        }
      }
    }

    // A forked child process should de-allocate memory on exit.
    // It seems that this function doesn't return to the calling thread for a forked child process, even with the "return 0;" below.
    if (*status == F_child) {
      controller_delete(main);
    }
    else {
      controller_thread_instance_force_set_disable(main);

      f_thread_condition_signal_all(&main->thread.lock.alert_condition);
    }

    return 0;
  }
#endif // _di_controller_thread_exit_

#ifdef __cplusplus
} // extern "C"
#endif
