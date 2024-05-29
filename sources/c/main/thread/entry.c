#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_main_thread_entry_
  void * controller_main_thread_entry(void * const arguments) {

    if (!arguments) return 0;

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_instance_t * const instance = (controller_instance_t * const ) arguments;

    if (!controller_main_thread_is_enabled(F_true, instance->thread)) return 0;

    controller_main_t * const main = instance->main;
    controller_cache_t * const cache = &instance->thread->cache;
    f_status_t * const status = &instance->thread->status;

    *status = controller_entry_read(*instance->global, F_true, cache);

    if (F_status_set_fine(*status) == F_interrupt) {
      instance->setting->ready = controller_setting_ready_abort_e;
    }
    else if (F_status_is_error(*status)) {
      instance->setting->ready = controller_setting_ready_fail_e;
    }
    else if (*status != F_child) {
      *status = controller_entry_preprocess(*instance->global, F_true, cache);

      if ((main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e) && (main->program.parameters.array[controller_parameter_validate_e].result & f_console_result_found_e)) {
        controller_entry_setting_validate(*instance->global, F_true, cache);
      }
    }

    if (F_status_is_error_not(*status) && *status != F_child) {
      if (!(main->program.parameters.array[controller_parameter_validate_e].result & f_console_result_found_e) || (main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e)) {

        if (instance->setting->instance.pid == controller_entry_pid_require_e && f_file_exists(instance->setting->path_pid, F_true) == F_true) {
          if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
            controller_lock_print(main->program.error.to, instance->thread);

            fl_print_format("%r%[%QThe pid file '%]", main->program.error.to, f_string_eol_s, main->program.error.context, main->program.error.prefix, main->program.error.context);
            fl_print_format(f_string_format_Q_single_s.string, main->program.error.to, main->program.error.notable, instance->setting->path_pid, main->program.error.notable);
            fl_print_format("%[' must not already exist.%]%r", main->program.error.to, main->program.error.context, main->program.error.context, f_string_eol_s);

            controller_unlock_print_flush(main->program.error.to, instance->thread);
          }

          instance->setting->ready = controller_setting_ready_fail_e;
          *status = F_status_set_error(F_available_not);
        }
        else {
          *status = controller_entry_process(instance->global, cache, F_false, F_true);

          if (F_status_is_error(*status)) {
            instance->setting->ready = controller_setting_ready_fail_e;

            if ((F_status_set_fine(*status) == F_execute || F_status_set_fine(*status) == F_require) && (instance->setting->flag & controller_setting_flag_failsafe_e)) {
              const uint8_t original_enabled = instance->thread->enabled;

              // Restore operating mode so that the failsafe can execute.
              *status = f_thread_mutex_lock(&instance->thread->lock.alert);

              if (F_status_is_error_not(*status)) {
                instance->thread->enabled = controller_thread_enabled_e;

                f_thread_mutex_unlock(&instance->thread->lock.alert);
              }

              // Restart the signal thread to allow for signals while operating the failsafe Items.
              if (!instance->thread->id_signal) {
                f_thread_create(0, &instance->thread->id_signal, &controller_main_thread_signal_normal, (void *) instance->global);
              }

              const f_status_t status_failsafe = controller_entry_process(instance->global, cache, F_true, F_true);

              if (F_status_is_error(status_failsafe)) {
                if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
                  controller_lock_print(main->program.error.to, instance->thread);

                  fl_print_format("%r%[%QFailed while processing requested failsafe item '%]", main->program.error.to, f_string_eol_s, main->program.error.context, main->program.error.prefix, main->program.error.context);
                  fl_print_format(f_string_format_Q_single_s.string, main->program.error.to, main->program.error.notable, instance->setting->instance.items.array[instance->setting->failsafe_item_id].name, main->program.error.notable);
                  fl_print_format(f_string_format_sentence_end_quote_s.string, main->program.error.to, main->program.error.context, main->program.error.context, f_string_eol_s);

                  controller_unlock_print_flush(main->program.error.to, instance->thread);
                }

                *status = F_status_set_error(F_failure);
              }
              else {

                // Restore operating mode to value prior to failsafe mode.
                *status = f_thread_mutex_lock(&instance->thread->lock.alert);

                if (F_status_is_error_not(*status)) {
                  instance->thread->enabled = original_enabled;

                  f_thread_mutex_unlock(&instance->thread->lock.alert);
                }

                *status = F_failure;
              }
            }
          }
          else if (F_status_set_fine(*status) == F_interrupt) {
            instance->setting->ready = controller_setting_ready_abort_e;
          }
          else if (*status != F_child) {
            instance->setting->ready = controller_setting_ready_done_e;
          }
        }

        if (F_status_is_error_not(*status) && *status != F_child && main->program.parameters.array[controller_parameter_validate_e].result == f_console_result_none_e && instance->setting->mode == controller_setting_mode_helper_e) {
          f_time_spec_t time;
          time.tv_sec = controller_main_thread_exit_helper_timeout_seconds_d;
          time.tv_nsec = controller_main_thread_exit_helper_timeout_nanoseconds_d;

          nanosleep(&time, 0);

          controller_main_thread_process_cancel(*(instance->global), F_true, controller_thread_cancel_exit_e);
        }
      }
    }

    if (*status == F_child) {

      // A forked child process should deallocate memory on exit.
      // It seems that this function doesn't return to the calling thread for a forked child process, even with the "return 0;" below.
      controller_thread_delete_simple(instance->thread);
      controller_process_delete(instance->setting);
      controller_main_delete(main);

      // According to the manpages, pthread_exit() calls exit(0), which the value of main->program.child should be returned instead.
      if (main->program.child) exit(main->program.child);

      return 0;
    }

    f_thread_condition_signal_all(&instance->thread->lock.alert_condition);

    return 0;
  }
#endif // _di_controller_main_thread_entry_

#ifndef _di_controller_main_thread_exit_
  void * controller_main_thread_exit(void * const arguments) {

    if (!arguments) return 0;

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_main_entry_t *instance = (controller_main_entry_t *) arguments;

    controller_main_t * const main = instance->main;
    controller_cache_t * const cache = &instance->thread->cache;
    f_status_t * const status = &instance->thread->status;

    *status = controller_entry_read(*instance->global, F_false, cache);

    if (F_status_set_fine(*status) == F_interrupt) {
      instance->setting->ready = controller_setting_ready_abort_e;
    }
    else if (F_status_is_error(*status)) {
      instance->setting->ready = controller_setting_ready_fail_e;
    }
    else if (*status == F_file_found_not) {
      instance->setting->ready = controller_setting_ready_done_e;
    }
    else if (*status != F_child) {
      *status = controller_entry_preprocess(*instance->global, F_false, cache);

      if ((main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e) && (main->program.parameters.array[controller_parameter_validate_e].result & f_console_result_found_e)) {
        controller_entry_setting_validate(*instance->global, F_false, cache);
      }
    }

    if (F_status_is_error_not(*status) && *status != F_child && *status != F_file_found_not) {
      if (!(main->program.parameters.array[controller_parameter_validate_e].result & f_console_result_found_e) || (main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e)) {

        *status = controller_entry_process(instance->global, cache, F_false, F_false);

        if (F_status_is_error(*status)) {
          instance->setting->ready = controller_setting_ready_fail_e;

          if ((F_status_set_fine(*status) == F_execute || F_status_set_fine(*status) == F_require) && (instance->setting->flag & controller_setting_flag_failsafe_e)) {

            const uint8_t original_enabled = instance->thread->enabled;

            // Restore operating mode so that the failsafe can execute.
            if (F_status_set_fine(*status) == F_execute) {
              *status = f_thread_mutex_lock(&instance->thread->lock.alert);

              if (F_status_is_error_not(*status)) {
                instance->thread->enabled = controller_thread_enabled_exit_e;

                f_thread_mutex_unlock(&instance->thread->lock.alert);
              }

              // Restart the signal thread to allow for signals while operating the failsafe Items.
              if (!instance->thread->id_signal) {
                f_thread_create(0, &instance->thread->id_signal, &controller_main_thread_signal_other, (void *) instance->global);
              }
            }

            const f_status_t status_failsafe = controller_entry_process(instance->global, cache, F_true, F_false);

            if (F_status_is_error(status_failsafe)) {
              if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
                controller_lock_print(main->program.error.to, instance->thread);

                fl_print_format("%r%[%QFailed while processing requested failsafe item '%]", main->program.error.to, f_string_eol_s, main->program.error.context, main->program.error.prefix, main->program.error.context);
                fl_print_format(f_string_format_Q_single_s.string, main->program.error.to, main->program.error.notable, instance->setting->instance.items.array[instance->setting->failsafe_item_id].name, main->program.error.notable);
                fl_print_format(f_string_format_sentence_end_quote_s.string, main->program.error.to, main->program.error.context, main->program.error.context, f_string_eol_s);

                controller_unlock_print_flush(main->program.error.to, instance->thread);
              }

              *status = F_status_set_error(F_failure);
            }
            else {

              // Restore operating mode to value prior to failsafe mode.
              *status = f_thread_mutex_lock(&instance->thread->lock.alert);

              if (F_status_is_error_not(*status)) {
                instance->thread->enabled = original_enabled;

                f_thread_mutex_unlock(&instance->thread->lock.alert);
              }

              *status = F_failure;
            }
          }
        }
        else if (F_status_set_fine(*status) == F_interrupt) {
          instance->setting->ready = controller_setting_ready_abort_e;
        }
        else if (*status != F_child) {
          instance->setting->ready = controller_setting_ready_done_e;
        }
      }
    }

    if (*status == F_child) {

      // A forked child process should deallocate memory on exit.
      // It seems that this function doesn't return to the calling thread for a forked child process, even with the "return 0;" below.
      controller_thread_delete_simple(instance->thread);
      controller_process_delete(instance->setting);
      controller_main_delete(main);

      return 0;
    }

    if (F_status_is_error_not(f_thread_mutex_lock(&instance->thread->lock.alert))) {
      instance->thread->enabled = controller_thread_enabled_not_e;

      f_thread_mutex_unlock(&instance->thread->lock.alert);
    }

    f_thread_condition_signal_all(&instance->thread->lock.alert_condition);

    return 0;
  }
#endif // _di_controller_main_thread_exit_

#ifdef __cplusplus
} // extern "C"
#endif
