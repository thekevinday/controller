#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_main_thread_rule_
  void * controller_main_thread_rule(void * const arguments) {

    if (!arguments) return 0;

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_global_t * const global = (controller_global_t * const) arguments;

    if (!controller_main_thread_is_enabled(F_true, global->thread)) return 0;

    return 0;
  }
#endif // _di_controller_main_thread_rule_

#ifdef __cplusplus
} // extern "C"
#endif
