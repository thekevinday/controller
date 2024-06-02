#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_thread_signal_
  void controller_thread_signal(controller_global_t * const global, const bool is_normal) {

    if (!global || !global->main || !global->thread) return;
    if (!controller_thread_is_enabled(is_normal, global->thread)) return;
    if (!(global->main->setting.flag & controller_main_flag_interruptible_e)) return;

    f_status_t status = F_okay;
    siginfo_t information;
    f_time_spec_t time = f_time_spec_t_initialize;

    while (controller_thread_is_enabled(is_normal, global->thread)) {

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
#endif // _di_controller_thread_signal_

#ifndef _di_controller_thread_signal_state_fss_
  void controller_thread_signal_state_fss(f_state_t * const state, void * const internal) {

    if (!state || !state->custom) return;

    controller_interrupt_t * const interrupt = (controller_interrupt_t *) state->custom;

    if (!interrupt->global || !interrupt->global->main || !interrupt->global->thread) return;

    if (!controller_thread_is_enabled(interrupt->is_normal, interrupt->global->thread)) {
      interrupt->global->main->program.signal_received = F_signal_abort;
      interrupt->global->main->setting.state.status = F_status_set_error(F_interrupt);
    }
    else if (interrupt->global->thread->signal == F_signal_interrupt || interrupt->global->thread->signal == F_signal_abort || interrupt->global->thread->signal == F_signal_quit || interrupt->global->thread->signal == F_signal_termination) {
      interrupt->global->main->program.signal_received = F_signal_abort;
      interrupt->global->main->setting.state.status = F_status_set_error(F_interrupt);
    }
  }
#endif // _di_controller_thread_signal_state_fss_

#ifndef _di_controller_thread_signal_state_iki_
  void controller_thread_signal_state_iki(f_state_t * const state, void * const internal) {

    if (!state || !state->custom) return;

    controller_interrupt_t * const interrupt = (controller_interrupt_t *) state->custom;

    if (!interrupt->global || !interrupt->global->main || !interrupt->global->thread) return;

    if (!controller_thread_is_enabled(interrupt->is_normal, interrupt->global->thread)) {
      interrupt->global->main->program.signal_received = F_signal_abort;
      interrupt->global->main->setting.state.status = F_status_set_error(F_interrupt);
    }
    else if (interrupt->global->thread->signal == F_signal_interrupt || interrupt->global->thread->signal == F_signal_abort || interrupt->global->thread->signal == F_signal_quit || interrupt->global->thread->signal == F_signal_termination) {
      interrupt->global->main->program.signal_received = F_signal_abort;
      interrupt->global->main->setting.state.status = F_status_set_error(F_interrupt);
    }
  }
#endif // _di_controller_thread_signal_state_iki_

#ifndef _di_controller_thread_signal_normal_
  void * controller_thread_signal_normal(void * const global) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_thread_signal((controller_global_t * const) global, F_true);

    return 0;
  }
#endif // _di_controller_thread_signal_normal_

#ifndef _di_controller_thread_signal_other_
  void * controller_thread_signal_other(void * const global) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_thread_signal((controller_global_t * const) global, F_false);

    return 0;
  }
#endif // _di_controller_thread_signal_other_

#ifdef __cplusplus
} // extern "C"
#endif
