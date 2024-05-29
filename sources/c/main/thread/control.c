#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_main_thread_control_
  void * controller_main_thread_control(void * const arguments) {

    if (!arguments) return 0;

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_global_t * const global = (controller_global_t * const) arguments;

    if (global->thread->enabled != controller_thread_enabled_e) return 0;

    f_status_t status = F_okay;

    if (status == F_child) {

      // A forked child process should de-allocate memory on exit.
      // It seems that this function doesn't return to the calling thread for a forked child process, even with the "return 0;" below.
      controller_thread_delete_simple(global->thread);
      controller_process_delete(global->setting);
      controller_main_delete(global->main);
    }

    return 0;
  }
#endif // _di_controller_main_thread_control_

#ifdef __cplusplus
} // extern "C"
#endif
