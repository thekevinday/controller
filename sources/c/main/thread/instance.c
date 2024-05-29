#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_main_thread_instance_
  void controller_main_thread_instance(const uint8_t is_normal, controller_instance_t * const instance) {

    if (!instance) return;
    if (!controller_main_thread_is_enabled(is_normal, (controller_thread_t * const) instance->thread)) return;

    const f_status_t status = controller_rule_process_do(controller_process_option_asynchronous_d, instance);

    // A forked child instance should deallocate memory on exit.
    // It seems that this function doesn't return to the calling thread for a forked child instance, even with the "return 0;" below.
    if (status == F_child) {
      controller_thread_delete_simple(instance->main_thread);
      controller_process_delete(instance->program);
      controller_main_delete(instance->main_data);

      // According to some man pages, pthread_exit() calls exit(0), so expliticly exit to ensure a non-zero code is returned when needed.
      if (instance->main_data->program.child) exit(instance->main_data->program.child);
    }
  }
#endif // _di_controller_main_thread_instance_

#ifndef _di_controller_main_thread_instance_cancel_
  void controller_main_thread_instance_cancel(controller_instance_t * const global, const uint8_t is_normal, const uint8_t by) {

    if (!global) return;

    f_thread_mutex_lock(&global->thread->lock.cancel);

    // Only cancel when enabled.
    if (!controller_main_thread_is_enabled(is_normal, global->thread)) {
      f_thread_mutex_unlock(&global->thread->lock.cancel);

      return;
    }

    controller_entry_t * const entry = is_normal ? &global->setting->entry : &global->setting->exit;
    controller_instance_t *instance = 0;

    f_time_spec_t time = f_time_spec_t_initialize;
    f_status_t status = F_okay;
    f_number_unsigned_t i = 0;
    f_number_unsigned_t j = 0;
    pid_t pid = 0;

    // A simple but inaccurate interval counter (expect this to be replaced in the future).
    const f_number_unsigned_t interval_nanoseconds = entry->timeout_exit < 1000 ? (entry->timeout_exit < 100 ? 5000000 : 100000000) : 500000000;
    const f_number_unsigned_t interval_milliseconds = entry->timeout_exit < 1000 ? (entry->timeout_exit < 100 ? 5 : 100) : 500;

    time.tv_sec = 0;
    time.tv_nsec = interval_nanoseconds;

    if (global->setting->mode == controller_setting_mode_helper_e && global->main->program.parameters.array[controller_parameter_validate_e].result == f_console_result_none_e) {
      int value = 0;
      f_number_unsigned_t lapsed = 0;

      for (i = 0; i < global->thread->instances.used; ++i) {

        if (!global->thread->instances.array[i]) continue;

        instance = global->thread->instances.array[i];

        if (!instance->id_thread) continue;

        controller_thread_detach(&instance->id_thread);

        instance->id_thread = 0;
      } // for
    }

    // Use the alert lock to toggle enabled (using it as if it is a write like and a signal lock).
    status = f_thread_mutex_lock(&global->thread->lock.alert);

    if (F_status_is_error(status)) {
      global->thread->enabled = controller_thread_enabled_not_e;
    }
    else {
      if (by == controller_thread_cancel_execute_e) {
        global->thread->enabled = controller_thread_enabled_execute_e;
      }
      else if (by == controller_thread_cancel_exit_e) {
        global->thread->enabled = controller_thread_enabled_not_e;
      }
      else if (by == controller_thread_cancel_exit_execute_e) {
        global->thread->enabled = controller_thread_enabled_exit_execute_e;
      }
      else {
        global->thread->enabled = controller_thread_enabled_exit_e;
      }

      f_thread_mutex_unlock(&global->thread->lock.alert);
    }

    if (global->thread->id_cleanup) {
      f_thread_cancel(global->thread->id_cleanup);
      f_thread_join(global->thread->id_cleanup, 0);

      global->thread->id_cleanup = 0;
    }

    if (global->thread->id_control) {
      f_thread_cancel(global->thread->id_control);
      f_thread_join(global->thread->id_control, 0);

      global->thread->id_control = 0;
    }

    // The sigtimedwait() function that is run inside of signal must be interrupted via the f_thread_cancel().
    if (by != controller_thread_cancel_signal_e && global->thread->id_signal) {
      f_thread_cancel(global->thread->id_signal);
      f_thread_join(global->thread->id_signal, 0);

      global->thread->id_signal = 0;
    }

    if (global->setting->mode == controller_setting_mode_helper_e && global->main->program.parameters.array[controller_parameter_validate_e].result == f_console_result_none_e) {
      f_thread_mutex_unlock(&global->thread->lock.cancel);

      return;
    }

    for (; i < global->thread->instances.used; ++i) {

      if (!global->thread->instances.array[i]) continue;

      instance = global->thread->instances.array[i];

      // Do not cancel exit instances, when not performing "execute" during exit.
      if (instance->type == controller_data_type_exit_e && global->thread->enabled != controller_thread_enabled_exit_execute_e) {
        continue;
      }

      for (j = 0; j < instance->childs.used; ++j) {

        if (instance->childs.array[j] > 0) {
          f_signal_send(global->thread->signal ? global->thread->signal : F_signal_termination, instance->childs.array[j]);
        }
      } // for

      for (j = 0; j < instance->path_pids.used; ++j) {

        if (instance->path_pids.array[j].used && f_file_exists(instance->path_pids.array[j], F_true) == F_true) {
          status = controller_file_pid_read(instance->path_pids.array[j], &pid);

          if (pid) {
            f_signal_send(global->thread->signal ? global->thread->signal : F_signal_termination, pid);
          }
        }
      } // for
    } // for

    if (entry->timeout_exit && !(entry->flag & controller_entry_flag_timeout_exit_no_e)) {
      f_number_unsigned_t lapsed = 0;

      for (i = 0; i < global->thread->instances.used && lapsed < entry->timeout_exit; ++i) {

        if (!global->thread->instances.array[i]) continue;

        instance = global->thread->instances.array[i];

        // Do not wait for instances, when not performing "execute" during exit.
        if (instance->type == controller_data_type_exit_e && global->thread->enabled != controller_thread_enabled_exit_execute_e) {
          continue;
        }

        for (j = 0; j < instance->childs.used && lapsed < entry->timeout_exit; ++j) {

          while (instance->childs.array[j] > 0 && lapsed < entry->timeout_exit) {

            // A hackish way to determine if the child instance exists while waiting.
            if (getpgid(instance->childs.array[j]) >= 0) {
              time.tv_sec = 0;
              time.tv_nsec = interval_nanoseconds;

              f_time_sleep_spec(&time, 0);

              lapsed += interval_milliseconds;
            }
            else {
              instance->childs.array[j] = 0;

              break;
            }
          } // while
        } // for

        for (j = 0; j < instance->path_pids.used && lapsed < entry->timeout_exit; ++j) {

          if (instance->path_pids.array[j].used && f_file_exists(instance->path_pids.array[j], F_true) == F_true) {
            status = controller_file_pid_read(instance->path_pids.array[j], &pid);

            if (pid) {
              while (lapsed < entry->timeout_exit) {

                // A hackish way to determine if the instance exists while waiting.
                if (getpgid(pid) >= 0) {
                  time.tv_sec = 0;
                  time.tv_nsec = interval_nanoseconds;

                  f_time_sleep_spec(&time, 0);

                  lapsed += interval_milliseconds;
                }
                else {
                  instance->path_pids.array[j].used = 0;

                  break;
                }
              } // while
            }
          }
        } // for
      } // for
    }

    for (i = 0; i < global->thread->instances.size; ++i) {

      if (!global->thread->instances.array[i]) continue;

      instance = global->thread->instances.array[i];

      // Do not kill exit instances, when not performing "execute" during exit.
      if (instance->type == controller_data_type_exit_e && global->thread->enabled != controller_thread_enabled_exit_execute_e) continue;

      if (instance->id_thread) {
        if (instance->childs.used) {
          for (j = 0; j < instance->childs.used; ++j) {

            if (instance->childs.array[j] > 0) {
              f_signal_send(F_signal_kill, instance->childs.array[j]);

              time.tv_sec = 0;
              time.tv_nsec = controller_main_thread_exit_process_cancel_wait_d;

              instance->childs.array[j] = 0;
            }
          } // for

          f_time_sleep_spec(&time, 0);
        }

        f_thread_join(instance->id_thread, 0);

        instance->id_thread = 0;
      }

      if (!(entry->flag & controller_entry_flag_timeout_exit_no_e)) {
        for (j = 0; j < instance->childs.size; ++j) {

          // Do not kill exit processes, when not performing "execute" during exit.
          if (instance->type == controller_data_type_exit_e && global->thread->enabled != controller_thread_enabled_exit_execute_e) continue;

          if (instance->childs.array[j]) {

            // A hackish way to determine if the child instance exists, and if it does then forcibly terminate it.
            if (getpgid(instance->childs.array[j]) >= 0) {
              f_signal_send(F_signal_kill, instance->childs.array[j]);
            }

            instance->childs.array[j] = 0;
          }
        } // for
      }

      if (!(entry->flag & controller_entry_flag_timeout_exit_no_e)) {
        for (j = 0; j < instance->path_pids.used; ++j) {

          // Do not kill exit processes, when not performing "execute" during exit.
          if (instance->type == controller_data_type_exit_e && global->thread->enabled != controller_thread_enabled_exit_execute_e) continue;

          if (f_file_exists(instance->path_pids.array[j], F_true) == F_true) {
            status = controller_file_pid_read(instance->path_pids.array[j], &pid);

            if (pid) {
              f_signal_send(F_signal_kill, pid);
            }

            f_file_remove(instance->path_pids.array[j]);
            instance->path_pids.array[j].used = 0;
          }
        } // for
      }

      // Shrink the child pids as much as possible.
      while (instance->childs.used) {

        // Do not shrink below an exit instances, when not performing "execute" during exit.
        if (instance->type == controller_data_type_exit_e && global->thread->enabled != controller_thread_enabled_exit_execute_e) break;
        if (instance->childs.array[j] > 0) break;

        --instance->childs.used;
      } // while

      // Shrink the path pids as much as possible.
      while (instance->path_pids.used) {

        // Do not shrink below an exit instances, when not performing "execute" during exit.
        if (instance->type == controller_data_type_exit_e && global->thread->enabled != controller_thread_enabled_exit_execute_e) break;
        if (instance->path_pids.array[j].used) break;

        --instance->path_pids.used;
      } // while
    } // for

    f_thread_mutex_unlock(&global->thread->lock.cancel);
  }
#endif // _di_controller_main_thread_instance_cancel_

#ifndef _di_controller_main_thread_instance_exit_
  void controller_main_thread_instance_exit(controller_global_t * const global) {

    if (!global) return;

    if (global->thread->enabled != controller_thread_enabled_exit_e) return;

    if (global->setting->ready == controller_setting_ready_done_e) {

      // The exit processing runs using the entry thread.
      if (global->thread->id_entry) {
        f_thread_cancel(global->thread->id_entry);
        f_thread_join(global->thread->id_entry, 0);

        global->thread->id_entry = 0;
      }

      // Restart the signal thread to allow for signals while operating the Exit.
      if (!global->thread->id_signal) {
        f_thread_create(0, &global->thread->id_signal, &controller_main_thread_signal_other, (void *) global);
      }

      const controller_main_entry_t entry = macro_controller_main_entry_t_initialize_1(global, global->setting);

      f_status_t status = f_thread_create(0, &global->thread->id_entry, &controller_main_thread_exit, (void *) &entry);

      if (F_status_is_error(status)) {
        if (global->main->program.error.verbosity > f_console_verbosity_quiet_e) {
          controller_main_print_error_status(&global->main->program.error, macro_controller_f(f_thread_create), F_status_set_fine(status));
        }

        if (F_status_is_error_not(f_thread_mutex_lock(&global->thread->lock.alert))) {
          global->thread->enabled = controller_thread_enabled_not_e;

          f_thread_mutex_unlock(&global->thread->lock.alert);
        }
        else {
          global->thread->enabled = controller_thread_enabled_not_e;
        }
      }
      else {
        f_time_spec_t time = f_time_spec_t_initialize;

        do {
          status = f_thread_mutex_lock(&global->thread->lock.alert);

          if (F_status_is_error(status)) {
            global->thread->enabled = controller_thread_enabled_not_e;

            break;
          }

          controller_time(controller_main_thread_exit_ready_timeout_seconds_d, controller_main_thread_exit_ready_timeout_nanoseconds_d, &time);

          status = f_thread_condition_wait_timed(&time, &global->thread->lock.alert_condition, &global->thread->lock.alert);

          f_thread_mutex_unlock(&global->thread->lock.alert);

        } while (F_status_is_error_not(status) && global->thread->enabled == controller_thread_enabled_exit_e);

        if (F_status_is_error(status)) {
          if (F_status_is_error_not(f_thread_mutex_lock(&global->thread->lock.alert))) {
            global->thread->enabled = controller_thread_enabled_not_e;

            f_thread_mutex_unlock(&global->thread->lock.alert);
          }
          else {
            global->thread->enabled = controller_thread_enabled_not_e;
          }
        }
      }

      // The sigtimedwait() function that is run inside of signal must be interrupted via the f_thread_cancel().
      if (global->thread->id_signal) {
        f_thread_cancel(global->thread->id_signal);
        f_thread_join(global->thread->id_signal, 0);

        global->thread->id_signal = 0;
      }

      controller_main_thread_instance_cancel(*global, F_false, controller_thread_cancel_exit_e);
    }
    else {
      if (F_status_is_error_not(f_thread_mutex_lock(&global->thread->lock.alert))) {
        global->thread->enabled = controller_thread_enabled_not_e;

        f_thread_mutex_unlock(&global->thread->lock.alert);
      }
      else {
        global->thread->enabled = controller_thread_enabled_not_e;
      }
    }
  }
#endif // _di_controller_main_thread_instance_exit_

#ifndef _di_controller_main_thread_instance_normal_
  void * controller_main_thread_instance_normal(void * const arguments) {

    if (!arguments) return 0;

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_main_thread_instance(F_true, (controller_instance_t * const) arguments);

    return 0;
  }
#endif // _di_controller_main_thread_instance_normal_

#ifndef _di_controller_main_thread_instance_other_
  void * controller_main_thread_instance_other(void * const arguments) {

    if (!arguments) return 0;

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_main_thread_instance(F_false, (controller_instance_t * const) arguments);

    return 0;
  }
#endif // _di_controller_main_thread_instance_other_

#ifdef __cplusplus
} // extern "C"
#endif
