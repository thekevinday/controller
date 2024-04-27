#include "../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_instance_delete_
  void controller_instance_delete(controller_instance_t * const instance) {

    if (!instance) return;

    controller_cache_delete(&instance->cache);
  }
#endif // _di_controller_instance_delete_

#ifndef _di_f_instances_delete_callback_
  f_status_t f_instances_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      controller_instance_t * const instances = (controller_instance_t *) void_array;

      for (f_number_unsigned_t i = start; i < stop; ++i) {
        controller_instance_delete(&instances[i]);
      } // for
    }

    return F_okay;
  }
#endif // _di_f_instances_delete_callback_

#ifdef __cplusplus
} // extern "C"
#endif
