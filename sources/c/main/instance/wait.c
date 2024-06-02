#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_instance_wait_
  f_status_t controller_instance_wait(controller_instance_t * const instance) {

    if (!instance || !instance->global || !instance->global->main || !instance->global->thread) return F_status_set_error(F_parameter);
    if (!controller_thread_is_enabled_instance(instance)) return F_status_set_error(F_interrupt);

    f_time_spec_t time;

    f_status_t status = F_okay;
    f_status_t status_lock = F_okay;

    uint8_t count = 0;

    do {
      f_thread_mutex_lock(&instance->wait_lock);

      if (count < controller_thread_wait_timeout_1_before_d) {
        controller_time_now(controller_thread_wait_timeout_1_seconds_d, controller_thread_wait_timeout_1_nanoseconds_d, &time);
      }
      else if (count < controller_thread_wait_timeout_2_before_d) {
        controller_time_now(controller_thread_wait_timeout_2_seconds_d, controller_thread_wait_timeout_2_nanoseconds_d, &time);
      }
      else if (count < controller_thread_wait_timeout_3_before_d) {
        controller_time_now(controller_thread_wait_timeout_3_seconds_d, controller_thread_wait_timeout_3_nanoseconds_d, &time);
      }
      else {
        controller_time_now(controller_thread_wait_timeout_4_seconds_d, controller_thread_wait_timeout_4_nanoseconds_d, &time);
      }

      status = f_thread_condition_wait_timed(&time, &instance->wait, &instance->wait_lock);

      f_thread_mutex_unlock(&instance->wait_lock);

      if (!controller_thread_is_enabled_instance(instance)) return F_status_set_error(F_interrupt);
      if (F_status_is_error(status)) break;

      status_lock = controller_lock_read_instance(instance, &instance->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(&instance->global->main->program.error, F_status_set_fine(status_lock), F_true, instance->global->thread);

        break;
      }

      if (!controller_rule_status_is_available(instance->action, instance->rule) && !(instance->state == controller_instance_state_active_e || instance->state == controller_instance_state_busy_e)) {
        f_thread_unlock(&instance->lock);

        return F_okay;
      }

      if (status != F_time) {

        // move up the wait timer after a trigger was received.
        if (count < controller_thread_wait_timeout_2_before_d) {
          count = 0;
        }
        else if (count < controller_thread_wait_timeout_3_before_d) {
          count = controller_thread_wait_timeout_1_before_d;
        }
        else {
          count = controller_thread_wait_timeout_2_before_d;
        }
      }

      f_thread_unlock(&instance->lock);

      if (count < controller_thread_wait_timeout_3_before_d) {
        ++count;
      }

    } while (status == F_time && controller_thread_is_enabled_instance(instance));

    return status;
  }
#endif // _di_controller_instance_wait_

#ifdef __cplusplus
} // extern "C"
#endif
