#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_thread_instance_
  void controller_thread_instance(controller_instance_t * const instance, const uint8_t is_normal) {

    if (!instance || !instance->main) return;
    if (!controller_thread_is_enabled(&instance->main->thread, is_normal)) return;

    const f_status_t status = controller_rule_instance_perform(instance, controller_instance_option_asynchronous_e);

    // A forked child Instance should de-allocate memory on exit.
    // It seems that this function doesn't return to the calling thread for a forked child Instance, even with the "return 0;" below.
    if (status == F_child) {
      controller_delete(instance->main);

      // According to some man pages, pthread_exit() calls exit(0), so expliticly exit to ensure a non-zero code is returned when needed.
      if (instance->main->program.child) exit(instance->main->program.child);
    }
  }
#endif // _di_controller_thread_instance_

#ifndef _di_controller_thread_instance_cancel_
  void controller_thread_instance_cancel(controller_t * const main, const uint8_t is_normal, const uint8_t by) {

    if (!main) return;

    f_thread_mutex_lock(&main->thread.lock.cancel);

    // Only cancel when enabled.
    if (!controller_thread_is_enabled(&main->thread, is_normal)) {
      f_thread_mutex_unlock(&main->thread.lock.cancel);

      return;
    }

    controller_entry_t * const entry = is_normal ? &main->process.entry : &main->process.exit;
    controller_instance_t *instance = 0;

    f_time_spec_t time = f_time_spec_t_initialize;
    f_number_unsigned_t i = 0;
    f_number_unsigned_t j = 0;
    pid_t pid = 0;

    // A simple but inaccurate interval counter.
    const f_number_unsigned_t interval_nanoseconds = entry->timeout_exit < 1000 ? (entry->timeout_exit < 100 ? 5000000 : 100000000) : 500000000;
    const f_number_unsigned_t interval_milliseconds = entry->timeout_exit < 1000 ? (entry->timeout_exit < 100 ? 5 : 100) : 500;

    time.tv_sec = 0;
    time.tv_nsec = interval_nanoseconds;

    if (main->process.mode == controller_process_mode_helper_e && !(main->setting.flag & controller_main_flag_validate_d)) {
      for (i = 0; i < main->thread.instances.used; ++i) {

        if (!main->thread.instances.array[i]) continue;

        instance = main->thread.instances.array[i];

        if (!instance->id_thread) continue;

        controller_thread_detach(&instance->id_thread);

        instance->id_thread = 0;
      } // for
    }

    f_status_t status = F_okay;

    for (f_number_unsigned_t i = 0; i < controller_lock_mutex_max_retry_d; ++i) {

      status = f_thread_mutex_lock(&main->thread.lock.alert);

      if (F_status_is_error_not(status) || F_status_set_fine(status) == F_parameter || F_status_set_fine(status) == F_deadlock) break;
    } // for

    if (F_status_is_error_not(status) && F_status_set_fine(status) != F_parameter && F_status_set_fine(status) != F_deadlock) {
      if (by == controller_thread_cancel_execute_e) {
        main->thread.enabled = controller_thread_enabled_execute_e;
      }
      else if (by == controller_thread_cancel_exit_e) {
        main->thread.enabled = controller_thread_enabled_not_e;
      }
      else if (by == controller_thread_cancel_exit_execute_e) {
        main->thread.enabled = controller_thread_enabled_exit_execute_e;
      }
      else {
        main->thread.enabled = controller_thread_enabled_exit_e;
      }

      f_thread_mutex_unlock(&main->thread.lock.alert);
    }

    if (main->thread.id_cleanup) {
      f_thread_cancel(main->thread.id_cleanup);
      f_thread_join(main->thread.id_cleanup, 0);

      main->thread.id_cleanup = 0;
    }

    if (main->thread.id_control) {
      f_thread_cancel(main->thread.id_control);
      f_thread_join(main->thread.id_control, 0);

      main->thread.id_control = 0;
    }

    // The sigtimedwait() function that is run inside of signal must be interrupted via the f_thread_cancel().
    if (by != controller_thread_cancel_signal_e && main->thread.id_signal) {
      f_thread_cancel(main->thread.id_signal);
      f_thread_join(main->thread.id_signal, 0);

      main->thread.id_signal = 0;
    }

    if (main->process.mode == controller_process_mode_helper_e && !(main->setting.flag & controller_main_flag_validate_d)) {
      f_thread_mutex_unlock(&main->thread.lock.cancel);

      return;
    }

    for (; i < main->thread.instances.used; ++i) {

      if (!main->thread.instances.array[i]) continue;

      instance = main->thread.instances.array[i];

      // Do not cancel Exit Instances, when not performing "execute" during exit.
      if (instance->type == controller_instance_type_exit_e && main->thread.enabled != controller_thread_enabled_exit_execute_e) {
        continue;
      }

      for (j = 0; j < instance->childs.used; ++j) {

        if (instance->childs.array[j] > 0) {
          f_signal_send(main->thread.signal ? main->thread.signal : F_signal_termination, instance->childs.array[j]);
        }
      } // for

      for (j = 0; j < instance->path_pids.used; ++j) {

        if (instance->path_pids.array[j].used && f_file_exists(instance->path_pids.array[j], F_true) == F_true) {
          status = controller_file_pid_read(instance->path_pids.array[j], &pid);

          if (pid) {
            f_signal_send(main->thread.signal ? main->thread.signal : F_signal_termination, pid);
          }
        }
      } // for
    } // for

    if (entry->timeout_exit && !(entry->flag & controller_entry_flag_timeout_exit_no_e)) {
      f_number_unsigned_t lapsed = 0;

      for (i = 0; i < main->thread.instances.used && lapsed < entry->timeout_exit; ++i) {

        if (!main->thread.instances.array[i]) continue;

        instance = main->thread.instances.array[i];

        // Do not wait for Instances, when not performing "execute" during exit.
        if (instance->type == controller_instance_type_exit_e && main->thread.enabled != controller_thread_enabled_exit_execute_e) {
          continue;
        }

        for (j = 0; j < instance->childs.used && lapsed < entry->timeout_exit; ++j) {

          while (instance->childs.array[j] > 0 && lapsed < entry->timeout_exit) {

            // A hackish way to determine if the child Instance exists while waiting (@todo look into pidfd() and epoll_wait()).
            if (getpgid(instance->childs.array[j]) >= 0) {
              time.tv_sec = 0;
              time.tv_nsec = interval_nanoseconds;

              f_time_sleep_spec(time, 0);

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

                // A hackish way to determine if the Instance exists while waiting (@todo look into pidfd() and epoll_wait()).
                if (getpgid(pid) >= 0) {
                  time.tv_sec = 0;
                  time.tv_nsec = interval_nanoseconds;

                  f_time_sleep_spec(time, 0);

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

    for (i = 0; i < main->thread.instances.size; ++i) {

      if (!main->thread.instances.array[i]) continue;

      instance = main->thread.instances.array[i];

      // Do not kill Exit Instances, when not performing "execute" during exit.
      if (instance->type == controller_instance_type_exit_e && main->thread.enabled != controller_thread_enabled_exit_execute_e) continue;

      if (instance->id_thread) {
        if (instance->childs.used) {
          for (j = 0; j < instance->childs.used; ++j) {

            if (instance->childs.array[j] > 0) {
              f_signal_send(F_signal_kill, instance->childs.array[j]);

              time.tv_sec = 0;
              time.tv_nsec = controller_thread_exit_process_cancel_wait_d;

              instance->childs.array[j] = 0;
            }
          } // for

          f_time_sleep_spec(time, 0);
        }

        f_thread_join(instance->id_thread, 0);

        instance->id_thread = 0;
      }

      if (!(entry->flag & controller_entry_flag_timeout_exit_no_e)) {
        for (j = 0; j < instance->childs.size; ++j) {

          // Do not kill Exit processes, when not performing "execute" during exit.
          if (instance->type == controller_instance_type_exit_e && main->thread.enabled != controller_thread_enabled_exit_execute_e) continue;

          if (instance->childs.array[j]) {

            // A hackish way to determine if the child instance exists, and if it does then forcibly terminate it (@todo look into pidfd() and epoll_wait()).
            if (getpgid(instance->childs.array[j]) >= 0) {
              f_signal_send(F_signal_kill, instance->childs.array[j]);
            }

            instance->childs.array[j] = 0;
          }
        } // for
      }

      if (!(entry->flag & controller_entry_flag_timeout_exit_no_e)) {
        for (j = 0; j < instance->path_pids.used; ++j) {

          // Do not kill Exit processes, when not performing "execute" during exit.
          if (instance->type == controller_instance_type_exit_e && main->thread.enabled != controller_thread_enabled_exit_execute_e) continue;

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

        // Do not shrink below an Exit Instances, when not performing "execute" during exit.
        if (instance->type == controller_instance_type_exit_e && main->thread.enabled != controller_thread_enabled_exit_execute_e) break;
        if (instance->childs.array[j] > 0) break;

        --instance->childs.used;
      } // while

      // Shrink the path pids as much as possible.
      while (instance->path_pids.used) {

        // Do not shrink below an Exit Instances, when not performing "execute" during exit.
        if (instance->type == controller_instance_type_exit_e && main->thread.enabled != controller_thread_enabled_exit_execute_e) break;
        if (instance->path_pids.array[j].used) break;

        --instance->path_pids.used;
      } // while
    } // for

    f_thread_mutex_unlock(&main->thread.lock.cancel);
  }
#endif // _di_controller_thread_instance_cancel_

#ifndef _di_controller_thread_instance_exit_
  void controller_thread_instance_exit(controller_t * const main) {

    if (!main || main->thread.enabled != controller_thread_enabled_exit_e) return;

    if (main->process.ready == controller_process_ready_done_e) {

      // The Exit processing runs using the Entry thread.
      if (main->thread.id_entry) {
        f_thread_cancel(main->thread.id_entry);
        f_thread_join(main->thread.id_entry, 0);

        main->thread.id_entry = 0;
      }

      // Restart the signal thread to allow for signals while operating the Exit.
      if (!main->thread.id_signal) {
        f_thread_create(0, &main->thread.id_signal, &controller_thread_signal_other, (void *) main);
      }

      f_status_t status = f_thread_create(0, &main->thread.id_entry, &controller_thread_exit, (void *) main);

      if (F_status_is_error(status)) {
        if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
          controller_print_error_status(&main->program.error, macro_controller_f(f_thread_create), F_status_set_fine(status));
        }

        controller_thread_instance_force_set_disable(main);
      }
      else {
        f_time_spec_t time = f_time_spec_t_initialize;

        do {
          status = f_thread_mutex_lock(&main->thread.lock.alert);
          if (F_status_is_error(status)) break;

          controller_time_now(controller_thread_timeout_exit_ready_seconds_d, controller_thread_timeout_exit_ready_nanoseconds_d, &time);

          status = f_thread_condition_wait_timed(&time, &main->thread.lock.alert_condition, &main->thread.lock.alert);

          f_thread_mutex_unlock(&main->thread.lock.alert);

        } while (F_status_is_error_not(status) && main->thread.enabled == controller_thread_enabled_exit_e);

        if (F_status_is_error(status)) controller_thread_instance_force_set_disable(main);
      }

      // The sigtimedwait() function that is run inside of signal must be interrupted via the f_thread_cancel().
      if (main->thread.id_signal) {
        f_thread_cancel(main->thread.id_signal);
        f_thread_join(main->thread.id_signal, 0);

        main->thread.id_signal = 0;
      }

      controller_thread_instance_cancel(main, F_false, controller_thread_cancel_exit_e);
    }
    else {
      controller_thread_instance_force_set_disable(main);
    }
  }
#endif // _di_controller_thread_instance_exit_

#ifndef _di_controller_thread_instance_force_set_disable_
  void controller_thread_instance_force_set_disable(controller_t * const main) {

    if (!main) return;

    if (F_status_is_error_not(f_thread_mutex_lock(&main->thread.lock.alert))) {
      main->thread.enabled = controller_thread_enabled_not_e;

      f_thread_mutex_unlock(&main->thread.lock.alert);

      return;
    }

    f_time_spec_t time;

    for (uint8_t i = 0; i < controller_thread_exit_disable_force_times; ++i) {

      memset((void *) &time, 0, sizeof(struct timespec));

      controller_time_now(controller_thread_timeout_exit_disable_force_seconds_d, controller_thread_timeout_exit_disable_force_nanoseconds_d, &time);

      if (F_status_is_error_not(f_thread_mutex_lock_timed(&time, &main->thread.lock.alert))) {
        main->thread.enabled = controller_thread_enabled_not_e;

        f_thread_mutex_unlock(&main->thread.lock.alert);

        return;
      }
    } // for

    // Forcibly set disable regardless of the risk.
    main->thread.enabled = controller_thread_enabled_not_e;
  }
#endif // _di_controller_thread_instance_force_set_disable_

#ifndef _di_controller_thread_instance_normal_
  void * controller_thread_instance_normal(void * const argument) {

    if (!argument) return 0;

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_thread_instance((controller_instance_t * const) argument, F_true);

    return 0;
  }
#endif // _di_controller_thread_instance_normal_

#ifndef _di_controller_thread_instance_other_
  void * controller_thread_instance_other(void * const argument) {

    if (!argument) return 0;

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_thread_instance((controller_instance_t * const) argument, F_false);

    return 0;
  }
#endif // _di_controller_thread_instance_other_

#ifdef __cplusplus
} // extern "C"
#endif
