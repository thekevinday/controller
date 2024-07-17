#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_thread_control_
  void * controller_thread_control(void * const argument) {

    if (!argument) return 0;

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_t * const main = (controller_t *) argument;

    if (main->thread.enabled != controller_thread_enabled_e) return 0;

    f_status_t status = F_okay;

    // A forked child process should de-allocate memory on exit.
    // It seems that this function doesn't return to the calling thread for a forked child process, even with the "return 0;" below.
    if (status == F_child) {
      controller_delete(main);
    }

    return 0;
  }
#endif // _di_controller_thread_control_

#ifdef __cplusplus
} // extern "C"
#endif
