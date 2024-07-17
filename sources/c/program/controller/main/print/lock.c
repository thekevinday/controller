#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_lock_print_
  void controller_lock_print(const f_file_t to, controller_thread_t * const thread) {

    if (thread) {
      f_thread_mutex_lock(&thread->lock.print);
    }

    f_file_stream_lock(to);
  }
#endif // _di_controller_lock_print_

#ifndef _di_controller_unlock_print_flush_
  void controller_unlock_print_flush(const f_file_t to, controller_thread_t * const thread) {

    f_file_stream_flush(to);
    f_file_stream_unlock(to);

    if (thread) {
      f_thread_mutex_unlock(&thread->lock.print);
    }
  }
#endif // _di_controller_unlock_print_flush_

#ifdef __cplusplus
} // extern "C"
#endif
