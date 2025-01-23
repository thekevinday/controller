#include "controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_controller_signal_check_) && defined(_di_thread_support_)
  f_status_t controller_signal_check(controller_t * const main) {

    if (!main) return F_false;
    if (main->program.signal_received) return F_true;

    if (!((++main->program.signal_check) % controller_signal_check_d)) {
      if (F_status_set_fine(fll_program_standard_signal_received(&main->program)) == F_interupt) {
        fll_program_print_signal_received(&main->program.warning, main->program.signal_received);

        main->setting.state.status = F_status_set_error(F_interrupt);

        return F_true;
      }

      main->program.signal_check = 0;
    }

    return F_false;
  }
#endif // !defined(_di_controller_signal_check_) && defined(_di_thread_support_)

#if !defined(_di_controller_signal_check_) && !defined(_di_thread_support_)
  f_status_t controller_signal_check(controller_t * const main) {

    if (!main || main->program.signal.id == -1) return F_false;

    if (main->program.signal_received) {
      fll_program_print_signal_received(&main->program.warning, main->program.signal_received);

      main->setting.state.status = F_status_set_error(F_interrupt);

      return F_true;
    }

    return F_false;
  }
#endif // !defined(_di_controller_signal_check_) && !defined(_di_thread_support_)

#if !defined(_di_controller_signal_handler_) && !defined(_di_thread_support_)
  void controller_signal_handler(controller_t * const main) {

    if (!main) return;

    f_signal_set_empty(&main->program.signal.set);
    f_signal_set_add(F_signal_abort, &main->program.signal.set);
    f_signal_set_add(F_signal_broken_pipe, &main->program.signal.set);
    f_signal_set_add(F_signal_hangup, &main->program.signal.set);
    f_signal_set_add(F_signal_interrupt, &main->program.signal.set);
    f_signal_set_add(F_signal_quit, &main->program.signal.set);
    f_signal_set_add(F_signal_termination, &main->program.signal.set);

    fll_program_standard_signal_received_wait(&main->program, controller_signal_check_failsafe_d);

    if (F_status_is_error(main->program.signal_status) && F_status_set_fine(main->program.signal_status) != F_interrupt) {
      main->program.signal_received = F_signal_abort;
    }
  }
#endif // !defined(_di_controller_signal_handler_) && !defined(_di_thread_support_)

#ifdef __cplusplus
} // extern "C"
#endif
