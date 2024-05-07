#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_rule_wait_all_
  f_status_t controller_rule_wait_all(controller_global_t * const global, const bool is_normal, const bool required) {

    if (!global) return F_status_set_error(F_parameter);

    f_status_t status_lock = controller_lock_read(is_normal, global->thread, &global->thread->lock.instance);

    if (F_status_is_error(status_lock)) {
      controller_lock_print_error_critical(&global->main->program.error, F_status_set_fine(status_lock), F_true, global->thread);

      return status_lock;
    }

    if (!global->thread->instances.used) {
      f_thread_unlock(&global->thread->lock.instance);

      return F_data_not;
    }

    f_status_t status = F_okay;

    bool required_not_run = F_false;
    bool skip = F_false;

    f_number_unsigned_t i = 0;
    f_number_unsigned_t j = 0;

    // Vuild a list of what to wait for so that anything new after this point will not be waited for.
    const f_number_unsigned_t instance_total = global->thread->instances.used;
    controller_data_t *instance_list[instance_total];

    for (; i < instance_total; ++i) {
      instance_list[i] = global->thread->instances.array[i];
    } // for

    f_thread_unlock(&global->thread->lock.instance);

    for (i = 0; i < instance_total; ++i) {

      if (!controller_thread_is_enabled(is_normal, global->thread)) break;

      // Re-establish global instance read lock to wait for or protect from the cleanup thread while checking the read instance.
      status_lock = controller_lock_read(is_normal, global->thread, &global->thread->lock.instance);
      if (F_status_is_error(status_lock)) break;

      if (!instance_list[i]) {
        f_thread_unlock(&global->thread->lock.instance);

        continue;
      }

      status_lock = controller_lock_read(is_normal, global->thread, &instance_list[i]->active);

      if (F_status_is_error(status_lock)) {
        f_thread_unlock(&global->thread->lock.instance);

        break;
      }

      // Once the active lock is obtained, then the main instance read lock can be safely released.
      f_thread_unlock(&global->thread->lock.instance);

      status_lock = controller_lock_read(is_normal, global->thread, &instance_list[i]->lock);

      if (F_status_is_error(status_lock)) {
        f_thread_unlock(&instance_list[i]->active);

        break;
      }

      if (required) {
        if (!(instance_list[i]->options & controller_instance_option_require_d)) {
          f_thread_unlock(&instance_list[i]->lock);
          f_thread_unlock(&instance_list[i]->active);

          continue;
        }
      }

      if (!instance_list[i]->state || instance_list[i]->state == controller_instance_state_idle_e || instance_list[i]->state == controller_instance_state_done_e) {

        if (instance_list[i]->state == controller_instance_state_done_e) {
          f_thread_unlock(&instance_list[i]->lock);

          status_lock = controller_lock_write(is_normal, global->thread, &instance_list[i]->lock);

          if (F_status_is_error(status_lock)) {
            controller_lock_print_error_critical(&global->main->program.error, F_status_set_fine(status_lock), F_false, global->thread);

            f_thread_unlock(&instance_list[i]->active);

            return status_lock;
          }

          if (instance_list[i]->state == controller_instance_state_done_e) {
            f_thread_unlock(&instance_list[i]->active);

            if (f_thread_lock_write_try(&instance_list[i]->active) == F_okay) {
              controller_thread_join(&instance_list[i]->id_thread);

              instance_list[i]->state = controller_instance_state_idle_e;

              f_thread_unlock(&instance_list[i]->active);

              f_thread_mutex_lock(&instance_list[i]->wait_lock);
              f_thread_condition_signal_all(&instance_list[i]->wait);
              f_thread_mutex_unlock(&instance_list[i]->wait_lock);
            }

            status_lock = controller_lock_read(is_normal, global->thread, &instance_list[i]->active);

            if (F_status_is_error(status_lock)) {
              f_thread_unlock(&instance_list[i]->lock);

              break;
            }
          }

          f_thread_unlock(&instance_list[i]->lock);

          status_lock = controller_lock_read(is_normal, global->thread, &instance_list[i]->lock);
          if (F_status_is_error(status_lock)) break;
        }

        if (instance_list[i]->options & controller_instance_option_require_d) {
          if (controller_rule_status_is_error(instance_list[i]->action, instance_list[i]->rule)) {
            status = F_status_set_error(F_require);

            f_thread_unlock(&instance_list[i]->lock);
            f_thread_unlock(&instance_list[i]->active);

            break;
          }
          else if (controller_rule_status_is_available(instance_list[i]->action, instance_list[i]->rule)) {
            required_not_run = F_true;
          }
        }

        f_thread_unlock(&instance_list[i]->lock);
        f_thread_unlock(&instance_list[i]->active);

        if (F_status_set_fine(status) == F_require) break;

        continue;
      }

      if (!controller_rule_status_is_error(instance_list[i]->action, instance_list[i]->rule) && (instance_list[i]->state == controller_instance_state_active_e || instance_list[i]->state == controller_instance_state_busy_e)) {
        f_thread_unlock(&instance_list[i]->lock);

        status = controller_instance_wait(global, instance_list[i]);

        if (F_status_set_fine(status) == F_interrupt) {
          f_thread_unlock(&instance_list[i]->active);

          break;
        }

        status_lock = controller_lock_read(is_normal, global->thread, &instance_list[i]->lock);

        if (F_status_is_error(status_lock)) {
          f_thread_unlock(&instance_list[i]->active);

          break;
        }

        if ((instance_list[i]->options & controller_instance_option_require_d)) {
          f_thread_unlock(&instance_list[i]->lock);

          if (controller_rule_status_is_error(instance_list[i]->action, instance_list[i]->rule)) {
            status = F_status_set_error(F_require);

            f_thread_unlock(&instance_list[i]->active);

            break;
          }
        }
        else {
          f_thread_unlock(&instance_list[i]->lock);
        }
      }
      else {
        f_thread_unlock(&instance_list[i]->lock);
      }

      f_thread_unlock(&instance_list[i]->active);

      if (F_status_set_fine(status) == F_interrupt || F_status_set_fine(status) == F_require) break;
    } // for

    if (F_status_is_error(status_lock)) {
      controller_lock_print_error_critical(&global->main->program.error, F_status_set_fine(status_lock), F_true, global->thread);

      return status_lock;
    }

    if (!controller_thread_is_enabled(is_normal, global->thread)) return F_status_set_error(F_interrupt);
    if (F_status_set_fine(status) == F_require) return status;
    if (required_not_run) return F_require;

    return F_okay;
  }
#endif // _di_controller_rule_wait_all_

#ifndef _di_controller_rule_wait_all_instance_type_
  f_status_t controller_rule_wait_all_instance_type(controller_global_t * const global, const uint8_t type, const bool required) {

    if (!global) return F_status_set_error(F_parameter);

    return controller_rule_wait_all(global, type != controller_data_type_exit_e, required);
  }
#endif // _di_controller_rule_wait_all_instance_type_

#ifdef __cplusplus
} // extern "C"
#endif
