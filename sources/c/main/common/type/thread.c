#include "../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_thread_delete_
  void controller_thread_delete(controller_thread_t * const thread) {

    if (!thread) return;

    controller_lock_delete(&thread->lock);
    controller_process_delete(&thread->process);
    controller_cache_delete(&thread->cache);
  }
#endif // _di_controller_thread_delete_

#ifdef __cplusplus
} // extern "C"
#endif
