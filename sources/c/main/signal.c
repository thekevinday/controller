#include "controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_controller_main_signal_check_) && defined(_di_thread_support_)
  f_status_t controller_main_signal_check(controller_main_t * const main) {

    if (!main || main->program.signal.id == -1) return F_false;

    if (!((++main->program.signal_check) % controller_main_signal_check_d)) {
      if (fll_program_standard_signal_received(&main->program)) {
        fll_program_print_signal_received(&main->program.warning, main->program.signal_received);

        main->setting.state.status = F_status_set_error(F_interrupt);

        return F_true;
      }

      main->program.signal_check = 0;
    }

    return F_false;
  }
#endif // !defined(_di_controller_main_signal_check_) && defined(_di_thread_support_)

#if !defined(_di_controller_main_signal_check_) && !defined(_di_thread_support_)
  f_status_t controller_main_signal_check(controller_main_t * const main) {

    if (!main || main->program.signal.id == -1) return F_false;

    if (main->program.signal_received) {
      fll_program_print_signal_received(&main->program.warning, main->program.signal_received);

      main->setting.state.status = F_status_set_error(F_interrupt);

      return F_true;
    }

    return F_false;
  }
#endif // !defined(_di_controller_main_signal_check_) && !defined(_di_thread_support_)

#if !defined(_di_controller_main_signal_handler_) && !defined(_di_thread_support_)
  void controller_main_signal_handler(controller_main_t * const main) {

    if (!main) return;

    siginfo_t information;
    f_number_unsigned_t failsafe = 0;

    memset(&information, 0, sizeof(siginfo_t));

    main->program.signal_received = 0;

    f_signal_set_empty(&main->program.signal.set);
    f_signal_set_add(F_signal_abort, &main->program.signal.set);
    f_signal_set_add(F_signal_broken_pipe, &main->program.signal.set);
    f_signal_set_add(F_signal_hangup, &main->program.signal.set);
    f_signal_set_add(F_signal_interrupt, &main->program.signal.set);
    f_signal_set_add(F_signal_quit, &main->program.signal.set);
    f_signal_set_add(F_signal_termination, &main->program.signal.set);

    if (main->program.signal.id == -1) {
      main->setting.status_signal = f_signal_open(&main->program.signal);

      if (F_status_is_error(main->setting.status_signal)) {
        main->program.signal_received = F_signal_abort;

        return;
      }
    }

    do {
      memset(&information, 0, sizeof(siginfo_t));

      main->setting.status_signal = f_signal_wait(&main->program.signal.set, &information);

      if (F_status_is_error(main->setting.status_signal) && F_status_set_fine(main->setting.status_signal) != F_interrupt) {
        if (++failsafe >= controller_signal_check_failsafe_d) break;
      }

      switch (information.si_signo) {
        case F_signal_abort:
        case F_signal_broken_pipe:
        case F_signal_hangup:
        case F_signal_interrupt:
        case F_signal_quit:
        case F_signal_termination:
          main->program.signal_received = information.si_signo;

          break;
      }

      failsafe = 0;
      main->setting.status_signal = F_okay;

    } while (!main->program.signal_received);

    f_signal_close(&main->program.signal);

    if (F_status_is_error(main->setting.status_signal)) {
      main->program.signal_received = F_signal_abort;
    }
  }
#endif // !defined(_di_controller_main_signal_handler_) && !defined(_di_thread_support_)

#ifdef __cplusplus
} // extern "C"
#endif
