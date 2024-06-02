#include "controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_lock_create_
  f_status_t controller_lock_create(controller_lock_t * const lock) {

    if (!lock) return F_status_set_error(F_parameter);

    f_status_t status = f_thread_mutex_create(0, &lock->alert);

    if (F_status_is_error_not(status)) {
      status = f_thread_mutex_create(0, &lock->cancel);
    }

    if (F_status_is_error_not(status)) {
      status = f_thread_mutex_create(0, &lock->print);
    }

    if (F_status_is_error_not(status)) {
      status = f_thread_lock_create(0, &lock->instance);
    }

    if (F_status_is_error_not(status)) {
      status = f_thread_lock_create(0, &lock->rule);
    }

    if (F_status_is_error_not(status)) {
      status = f_thread_mutex_create(0, &lock->alert);
    }

    if (F_status_is_error_not(status)) {
      status = f_thread_condition_create(0, &lock->alert_condition);
    }

    return F_status_is_error(status) ? status : F_okay;
  }
#endif // _di_controller_lock_create_

#ifndef _di_controller_lock_read_
  f_status_t controller_lock_read(const bool is_normal, controller_thread_t * const thread, f_thread_lock_t * const lock) {

    if (!thread || !lock) return F_status_set_error(F_parameter);

    f_status_t status = F_okay;

    for (f_time_spec_t time; ; ) {

      controller_time_now(controller_thread_lock_read_timeout_seconds_d, controller_thread_lock_read_timeout_nanoseconds_d, &time);

      status = f_thread_lock_read_timed(&time, lock);

      if (status == F_time) {
        if (!controller_thread_is_enabled(is_normal, thread)) return F_status_set_error(F_interrupt);
      }
      else {
        break;
      }
    } // for

    return status;
  }
#endif // _di_controller_lock_read_

#ifndef _di_controller_lock_read_instance_
  f_status_t controller_lock_read_instance(controller_instance_t * const instance, f_thread_lock_t * const lock) {

    if (!instance || !lock) return F_status_set_error(F_parameter);

    return controller_lock_read_instance_type(instance->type, instance->global->thread, lock);
  }
#endif // _di_controller_lock_read_instance_

#ifndef _di_controller_lock_read_instance_type_
  f_status_t controller_lock_read_instance_type(const uint8_t type, controller_thread_t * const thread, f_thread_lock_t * const lock) {

    if (!thread || !lock) return F_status_set_error(F_parameter);

    return controller_lock_read(type != controller_instance_type_exit_e, thread, lock);
  }
#endif // _di_controller_lock_read_instance_type_

#ifndef _di_controller_lock_write_
  f_status_t controller_lock_write(const bool is_normal, controller_thread_t * const thread, f_thread_lock_t * const lock) {

    if (!thread || !lock) return F_status_set_error(F_parameter);

    f_status_t status = F_okay;

    for (f_time_spec_t time; ; ) {

      controller_time_now(controller_thread_lock_write_timeout_seconds_d, controller_thread_lock_write_timeout_nanoseconds_d, &time);

      status = f_thread_lock_write_timed(&time, lock);

      if (status == F_time) {
        if (!controller_thread_is_enabled(is_normal, thread)) return F_status_set_error(F_interrupt);
      }
      else {
        break;
      }
    } // for

    return status;
  }
#endif // _di_controller_lock_write_

#ifndef _di_controller_lock_write_instance_
  f_status_t controller_lock_write_instance(controller_instance_t * const instance, f_thread_lock_t * const lock) {

    if (!instance || !lock) return F_status_set_error(F_parameter);

    return controller_lock_write_instance_type(instance->type, instance->global->thread, lock);
  }
#endif // _di_controller_lock_write_instance_

#ifndef _di_controller_lock_write_instance_type_
  f_status_t controller_lock_write_instance_type(const uint8_t type, controller_thread_t * const thread, f_thread_lock_t * const lock) {

    if (!thread || !lock) return F_status_set_error(F_parameter);

    return controller_lock_write(type != controller_instance_type_exit_e, thread, lock);
  }
#endif // _di_controller_lock_write_instance_type_

#ifdef __cplusplus
} // extern "C"
#endif
