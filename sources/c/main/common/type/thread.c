#include "../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_thread_delete_
  void controller_thread_delete(controller_thread_t * const thread) {

    if (!thread) return;

    controller_lock_delete(&thread->lock);
    controller_cache_delete(&thread->cache);

    f_memory_arrays_resize(0, sizeof(controller_instance_t), (void **) &thread->instances.array, &thread->instances.used, &thread->instances.size, &f_instances_delete_callback);
  }
#endif // _di_controller_thread_delete_

#ifdef __cplusplus
} // extern "C"
#endif
