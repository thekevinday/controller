#include "../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_lock_delete_
  void controller_lock_delete(controller_lock_t * const lock) {

    f_thread_mutex_delete(&lock->alert);
    f_thread_mutex_delete(&lock->cancel);
    f_thread_mutex_delete(&lock->print);

    f_thread_lock_delete(&lock->process);
    f_thread_lock_delete(&lock->rule);

    f_thread_condition_delete(&lock->alert_condition);

    memset(&lock->alert, 0, sizeof(f_thread_mutex_t));
    memset(&lock->cancel, 0, sizeof(f_thread_mutex_t));
    memset(&lock->print, 0, sizeof(f_thread_mutex_t));

    memset(&lock->process, 0, sizeof(f_thread_lock_t));
    memset(&lock->rule, 0, sizeof(f_thread_lock_t));

    memset(&lock->alert_condition, 0, sizeof(f_thread_condition_t));
  }
#endif // _di_controller_lock_delete_

#ifdef __cplusplus
} // extern "C"
#endif
