#include "../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_thread_delete_simple_
  void controller_thread_delete_simple(controller_thread_t * const thread) {

    controller_lock_delete(&thread->lock);
    controller_process_delete(&thread->process);
    controller_cache_delete(&thread->cache);
  }
#endif // _di_controller_thread_delete_simple_

#ifdef __cplusplus
} // extern "C"
#endif
