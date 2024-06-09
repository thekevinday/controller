#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_thread_cleanup_
  void * controller_thread_cleanup(void * const argument) {

    if (!argument) return 0;

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_t * const main = (controller_t *) argument;

    if (main->thread.enabled != controller_thread_enabled_e) return 0;

    const f_time_spec_t delay = {
      .tv_sec = (main->setting.flag & controller_main_flag_simulate_e)
        ? controller_thread_cleanup_interval_short_d
        : controller_thread_cleanup_interval_long_d,
      .tv_nsec = 0,
    };

    f_status_t status = F_okay;

    while (main->thread.enabled == controller_thread_enabled_e) {

      f_time_sleep_spec(delay, 0);

      if (main->thread.enabled != controller_thread_enabled_e) break;

      if (f_thread_lock_write_try(&main->thread.lock.instance) == F_okay) {
        controller_instance_t *instance = 0;

        f_number_unsigned_t i = 0;

        for (; i < main->thread.instances.size && main->thread.enabled == controller_thread_enabled_e; ++i) {

          if (!main->thread.instances.array[i]) continue;

          instance = main->thread.instances.array[i];

          // If "active" has a read lock, then do not attempt to clean it.
          if (f_thread_lock_write_try(&instance->active) != F_okay) continue;

          // If "lock" has a read or write lock, then do not attempt to clean it.
          if (f_thread_lock_write_try(&instance->lock) != F_okay) {
            f_thread_unlock(&instance->active);

            continue;
          }

          // If instance is active or busy, then do not attempt to clean it.
          if (instance->state == controller_instance_state_active_e || instance->state == controller_instance_state_busy_e) {
            f_thread_unlock(&instance->active);
            f_thread_unlock(&instance->lock);

            continue;
          }

          // If instance has a PID file, then it is running in the background, only cleanup if the PID file no longer exists.
          if (instance->path_pids.used) {
            f_number_unsigned_t j = 0;

            for (; j < instance->path_pids.used; ++j) {

              if (instance->path_pids.array[j].used && f_file_exists(instance->path_pids.array[j], F_true) == F_true) {
                break;
              }
            } // for

            if (j < instance->path_pids.used) {
              f_thread_unlock(&instance->active);
              f_thread_unlock(&instance->lock);

              continue;
            }
          }

          f_thread_unlock(&instance->lock);

          // Close any still open thread.
          if (instance->id_thread) {
            status = f_thread_join(instance->id_thread, 0);

            if (F_status_is_error_not(status) || F_status_set_fine(status) == F_found_not) {
              status = f_thread_lock_write(&instance->lock);

              if (F_status_is_error(status)) {
                controller_print_error_lock_critical(&main->program.error, F_status_set_fine(status), F_false);

                f_thread_unlock(&instance->active);

                continue;
              }

              instance->state = controller_instance_state_idle_e;
              instance->id_thread = 0;

              f_thread_mutex_lock(&instance->wait_lock);
              f_thread_condition_signal_all(&instance->wait);
              f_thread_mutex_unlock(&instance->wait_lock);

              f_thread_unlock(&instance->lock);
            }
            else {
              f_thread_unlock(&instance->active);

              continue;
            }
          }

          // De-allocate dynamic portions of the structure that are only ever needed while the instance is running.
          controller_cache_delete(&instance->cache);
          f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &instance->stack.array, &instance->stack.used, &instance->stack.size);

          // Shrink the childs array.
          if (instance->childs.used) {
            for (; instance->childs.used; --instance->childs.used) {
              if (instance->childs.array[instance->childs.used]) break;
            } // for

            if (instance->childs.used < instance->childs.size) {
              f_memory_array_resize(instance->childs.used, sizeof(pid_t), (void **) &instance->childs.array, &instance->childs.used, &instance->childs.size);
            }
          }

          // De-allocate the PID files.
          if (instance->path_pids.used) {
            instance->path_pids.used = 0;

            f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &instance->path_pids.array, &instance->path_pids.used, &instance->path_pids.size, &f_string_dynamics_delete_callback);
          }

          // De-allocate any rules in the space that is declared to be unused.
          if (i >= main->thread.instances.used) {
            controller_rule_delete(&instance->rule);
          }

          f_thread_unlock(&instance->active);
        } // for

        f_thread_unlock(&main->thread.lock.instance);
      }
    } // while

    return 0;
  }
#endif // _di_controller_thread_cleanup_

#ifdef __cplusplus
} // extern "C"
#endif
