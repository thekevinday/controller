#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_thread_signal_
  void controller_thread_signal(controller_t * const main, const uint8_t is_normal) {

    if (!main) return;
    if (!controller_thread_is_enabled(&main->thread, is_normal)) return;
    if (!(main->setting.flag & controller_main_flag_interruptible_d)) return;

    siginfo_t information;
    f_time_spec_t time = f_time_spec_t_initialize;

    while (controller_thread_is_enabled(&main->thread, is_normal)) {

      memset((void *) &information, 0, sizeof(siginfo_t));

      controller_time_now(controller_thread_timeout_exit_ready_seconds_d, controller_thread_timeout_exit_ready_nanoseconds_d, &time);

      if (f_signal_wait_until(&main->program.signal.set, &time, &information) == F_time_out) continue;

      if (information.si_signo == F_signal_interrupt || information.si_signo == F_signal_abort || information.si_signo == F_signal_quit || information.si_signo == F_signal_termination) {
        main->thread.signal = information.si_signo;

        controller_thread_instance_cancel(main, is_normal, controller_thread_cancel_signal_e);

        break;
      }
    } // while
  }
#endif // _di_controller_thread_signal_

#ifndef _di_controller_thread_signal_state_fss_
  void controller_thread_signal_state_fss(f_state_t * const state, void * const internal) {

    if (!state || !state->custom) return;

    controller_interrupt_t * const interrupt = (controller_interrupt_t *) state->custom;

    if (!interrupt->main) return;

    if (!controller_thread_is_enabled(&interrupt->main->thread, interrupt->is_normal)) {
      interrupt->main->program.signal_received = F_signal_abort;
      interrupt->main->setting.state.status = F_status_set_error(F_interrupt);
    }
    else if (interrupt->main->thread.signal == F_signal_interrupt || interrupt->main->thread.signal == F_signal_abort || interrupt->main->thread.signal == F_signal_quit || interrupt->main->thread.signal == F_signal_termination) {
      interrupt->main->program.signal_received = F_signal_abort;
      interrupt->main->setting.state.status = F_status_set_error(F_interrupt);
    }
  }
#endif // _di_controller_thread_signal_state_fss_

#ifndef _di_controller_thread_signal_state_iki_
  void controller_thread_signal_state_iki(f_state_t * const state, void * const internal) {

    if (!state || !state->custom) return;

    controller_interrupt_t * const interrupt = (controller_interrupt_t *) state->custom;

    if (!interrupt->main) return;

    if (!controller_thread_is_enabled(&interrupt->main->thread, interrupt->is_normal)) {
      interrupt->main->program.signal_received = F_signal_abort;
      interrupt->main->setting.state.status = F_status_set_error(F_interrupt);
    }
    else if (interrupt->main->thread.signal == F_signal_interrupt || interrupt->main->thread.signal == F_signal_abort || interrupt->main->thread.signal == F_signal_quit || interrupt->main->thread.signal == F_signal_termination) {
      interrupt->main->program.signal_received = F_signal_abort;
      interrupt->main->setting.state.status = F_status_set_error(F_interrupt);
    }
  }
#endif // _di_controller_thread_signal_state_iki_

#ifndef _di_controller_thread_signal_normal_
  void * controller_thread_signal_normal(void * const argument) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_thread_signal((controller_t *) argument, F_true);

    return 0;
  }
#endif // _di_controller_thread_signal_normal_

#ifndef _di_controller_thread_signal_other_
  void * controller_thread_signal_other(void * const argument) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_thread_signal((controller_t *) argument, F_false);

    return 0;
  }
#endif // _di_controller_thread_signal_other_

#ifdef __cplusplus
} // extern "C"
#endif
