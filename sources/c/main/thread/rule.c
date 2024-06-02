#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_thread_rule_
  void * controller_thread_rule(void * const argument) {

    if (!argument) return 0;

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_t * const main = (controller_t *) argument;

    if (!controller_thread_is_enabled(F_true, &main->thread)) return 0;

    return 0;
  }
#endif // _di_controller_thread_rule_

#ifdef __cplusplus
} // extern "C"
#endif
