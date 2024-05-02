#include "controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_main_thread_signal_
  void controller_main_thread_signal(controller_global_t * const global, const bool is_normal) {

    if (!global || !global->main || !global->thread) return;
    if (!controller_main_thread_is_enabled(is_normal, global->thread)) return;
    if (!(global->main->setting.flag & controller_main_flag_interruptible_e)) return;

    f_status_t status = F_okay;
    siginfo_t information;
    f_time_spec_t time = f_time_spec_t_initialize;

    while (controller_main_thread_is_enabled(is_normal, global->thread)) {

      controller_time_now(controller_thread_exit_ready_timeout_seconds_d, controller_thread_exit_ready_timeout_nanoseconds_d, &time);

      memset((void *) &information, 0, sizeof(siginfo_t));

      status = f_signal_wait_until(&global->main->program.signal.set, &time, &information);
      if (status == F_time_out) continue;

      if (information.si_signo == F_signal_interrupt || information.si_signo == F_signal_abort || information.si_signo == F_signal_quit || information.si_signo == F_signal_termination) {
        global->thread->signal = information.si_signo;

        controller_thread_instance_cancel(global, is_normal, controller_thread_cancel_signal_e);

        break;
      }
    } // while
  }
#endif // _di_controller_main_thread_signal_

#ifndef _di_controller_main_thread_signal_state_fss_
  f_status_t controller_main_thread_signal_state_fss(f_state_t * const state, void * const internal) {

    if (!state || !state->custom || !internal) return F_interrupt_not;

    controller_interrupt_t * const custom = (controller_interrupt_t *) state->custom;
    controller_thread_t * const thread = custom->thread;

    if (!controller_main_thread_is_enabled(custom->is_normal, thread)) {
      return F_status_set_error(F_interrupt);
    }

    if (thread->signal == F_signal_interrupt || thread->signal == F_signal_abort || thread->signal == F_signal_quit || thread->signal == F_signal_termination) {
      return F_status_set_error(F_interrupt);
    }

    return F_interrupt_not;
  }
#endif // _di_controller_main_thread_signal_state_fss_

#ifndef _di_controller_main_thread_signal_state_iki_
  f_status_t controller_main_thread_signal_state_iki(f_state_t * const state, void * const internal) {

    if (!state || !state->custom || !internal) return F_interrupt_not;

    controller_interrupt_t * const custom = (controller_interrupt_t *) state->custom;
    controller_thread_t * const thread = custom->thread;

    if (!controller_main_thread_is_enabled(custom->is_normal, thread)) {
      return F_status_set_error(F_interrupt);
    }

    if (thread->signal == F_signal_interrupt || thread->signal == F_signal_abort || thread->signal == F_signal_quit || thread->signal == F_signal_termination) {
      return F_status_set_error(F_interrupt);
    }

    return F_interrupt_not;
  }
#endif // _di_controller_main_thread_signal_state_iki_

#ifndef _di_controller_main_thread_signal_normal_
  void * controller_main_thread_signal_normal(void * const global) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_main_thread_signal((controller_global_t *) global, F_true);

    return 0;
  }
#endif // _di_controller_main_thread_signal_normal_

#ifndef _di_controller_main_thread_signal_other_
  void * controller_main_thread_signal_other(void * const global) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_main_thread_signal((controller_global_t *) global, F_false);

    return 0;
  }
#endif // _di_controller_main_thread_signal_other_

#ifdef __cplusplus
} // extern "C"
#endif
