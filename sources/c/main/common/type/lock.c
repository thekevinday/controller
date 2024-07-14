#include "../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_lock_delete_
  void controller_lock_delete(controller_lock_t * const lock) {

    if (!lock || (lock->flag & controller_lock_flag_setup_not_d)) return;

    f_thread_mutex_delete(&lock->alert);
    f_thread_mutex_delete(&lock->cancel);
    f_thread_mutex_delete(&lock->print);

    f_thread_lock_delete(&lock->instance);
    f_thread_lock_delete(&lock->rule);

    f_thread_condition_delete(&lock->alert_condition);

    lock->flag |= controller_lock_flag_setup_not_d;
  }
#endif // _di_controller_lock_delete_

#ifdef __cplusplus
} // extern "C"
#endif
