#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_thread_is_enabled_
  f_status_t controller_thread_is_enabled(controller_thread_t * const thread, const uint8_t is_normal) {

    if (!thread) return F_false;

    const uint8_t enabled = thread->enabled;

    return is_normal ? enabled == controller_thread_enabled_e : enabled;
  }
#endif // _di_controller_thread_is_enabled_

#ifndef _di_controller_thread_is_enabled_instance_
  f_status_t controller_thread_is_enabled_instance(controller_instance_t * const instance) {

    if (!instance) return F_false;

    return controller_thread_is_enabled_instance_type(&instance->main->thread, instance->type);
  }
#endif // _di_controller_thread_is_enabled_instance_

#ifndef _di_controller_thread_is_enabled_instance_type_
  f_status_t controller_thread_is_enabled_instance_type(controller_thread_t * const thread, const uint8_t type) {

    return controller_thread_is_enabled(thread, type != controller_instance_type_exit_e);
  }
#endif // _di_controller_thread_is_enabled_instance_type_

#ifdef __cplusplus
} // extern "C"
#endif
