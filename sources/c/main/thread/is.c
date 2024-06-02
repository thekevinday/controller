#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_thread_is_enabled_
  f_status_t controller_thread_is_enabled(const uint8_t is_normal, controller_thread_t * const thread) {

    if (!thread) return F_false;

    return is_normal ? thread->enabled == controller_thread_enabled_e : thread->enabled;
  }
#endif // _di_controller_thread_is_enabled_

#ifndef _di_controller_thread_is_enabled_instance_
  f_status_t controller_thread_is_enabled_instance(controller_instance_t * const instance) {

    if (!instance) return F_false;

    return controller_thread_is_enabled_instance_type(instance->type, instance->global->thread);
  }
#endif // _di_controller_thread_is_enabled_instance_

#ifndef _di_controller_thread_is_enabled_instance_type_
  f_status_t controller_thread_is_enabled_instance_type(const uint8_t type, controller_thread_t * const thread) {

    return controller_thread_is_enabled(type != controller_instance_type_exit_e, thread);
  }
#endif // _di_controller_thread_is_enabled_instance_type_

#ifdef __cplusplus
} // extern "C"
#endif
