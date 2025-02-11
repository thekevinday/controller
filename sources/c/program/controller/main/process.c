#include "controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_process_
  void controller_process(controller_t * const main) {

    if (!main || F_status_is_error(main->setting.state.status)) return;

    main->setting.state.status = F_okay;

    if (main->setting.flag & controller_main_flag_version_copyright_help_d) {
      if (main->setting.flag & controller_main_flag_help_d) {
        controller_print_message_help(&main->program.message, F_false);
      }
      else if (main->setting.flag & controller_main_flag_version_d) {
        fll_program_print_version(&main->program.message, controller_program_version_s);
      }
      else if (main->setting.flag & controller_main_flag_copyright_d) {
        fll_program_print_copyright(&main->program.message, fll_program_copyright_year_author_s);
      }

      if (main->program.signal_received) {
        fll_program_print_signal_received(&main->program.warning, main->program.signal_received);
      }

      return;
    }

    f_signal_set_fill(&main->program.signal.set);

    f_status_t status = f_thread_signal_mask(SIG_BLOCK, &main->program.signal.set, 0);

    if (F_status_is_error_not(status)) {
      status = f_signal_open(&main->program.signal);
    }

    // If there is an error opening a signal descriptor, then do not handle signals.
    if (F_status_is_error(status)) {
      f_thread_signal_mask(SIG_UNBLOCK, &main->program.signal.set, 0);
      f_signal_close(&main->program.signal);
    }

    // The locks must be initialized, but only once, so initialize immediately upon allocation.
    status = controller_lock_create(&main->thread.lock);

    if (F_status_is_error(status)) {
      controller_print_error_status(&main->program.error, macro_controller_f(controller_lock_create), status);
    }
    else {
      status = f_thread_create(0, &main->thread.id_signal, &controller_thread_signal_normal, (void *) main);

      if (F_status_is_error(status)) {
        main->thread.id_signal = 0;

        controller_print_error_status(&main->program.error, macro_controller_f(f_thread_create), status);
      }
      else {
        if (main->setting.flag & controller_main_flag_daemon_d) {
          main->process.ready = controller_process_ready_done_e;

          if (f_file_exists(main->process.path_pid, F_true) == F_true) {
            status = F_status_set_error(F_available_not);
            main->process.ready = controller_process_ready_abort_e;

            controller_print_error_file_pid_exists(&main->program.error, &main->thread, main->process.path_pid);
          }
        }
        else if (main->process.name_entry.used) {
          status = f_thread_create(0, &main->thread.id_entry, &controller_thread_entry, (void *) main);

          if (F_status_is_error(status)) {
            controller_print_error_status(&main->program.error, macro_controller_f(f_thread_create), status);
          }
          else {
            controller_thread_join(&main->thread.id_entry);

            status = main->thread.status;
            main->thread.id_entry = 0;
          }
        }
      }
    }

    // Only make the Rule and control threads available once any/all pre-processing is complete.
    if (F_status_is_error_not(status) && status != F_failure && status != F_child && main->thread.enabled == controller_thread_enabled_e) {
      if (!(main->setting.flag & controller_main_flag_validate_d)) {

        // Wait for the Entry thread to complete before starting the Rule thread.
        controller_thread_join(&main->thread.id_rule);

        if (main->thread.enabled && main->process.mode == controller_process_mode_service_e) {
          status = f_thread_create(0, &main->thread.id_rule, &controller_thread_rule, (void *) main);

          if (F_status_is_error(status)) {
            main->thread.id_rule = 0;
          }
          else {
            status = f_thread_create(0, &main->thread.id_cleanup, &controller_thread_cleanup, (void *) main);
          }

          if (F_status_is_error(status)) {
            main->thread.id_cleanup = 0;

            controller_print_error_status(&main->program.error, macro_controller_f(f_thread_create), status);
          }
        }
      }
    }

    if (status == F_child) {
      main->setting.state.status = F_child;

      controller_thread_delete(&main->thread);

      return;
    }

    if (F_status_is_error_not(status) && status != F_failure && !(main->setting.flag & controller_main_flag_validate_d) && controller_thread_is_enabled(&main->thread, F_true)) {
      if (main->process.mode == controller_process_mode_service_e) {
        controller_thread_join(&main->thread.id_signal);
      }
      else if (main->process.mode == controller_process_mode_helper_e || main->process.mode == controller_process_mode_program_e) {
        status = controller_rule_wait_all(main, F_true, F_false);
      }
    }

    controller_thread_instance_cancel(main, F_true, controller_thread_cancel_call_e);

    controller_thread_instance_exit(main);

    if (main->thread.id_signal) f_thread_join(main->thread.id_signal, 0);
    if (main->thread.id_cleanup) f_thread_join(main->thread.id_cleanup, 0);
    if (main->thread.id_control) f_thread_join(main->thread.id_control, 0);
    if (main->thread.id_entry) f_thread_join(main->thread.id_entry, 0);
    if (main->thread.id_rule) f_thread_join(main->thread.id_rule, 0);

    main->thread.id_cleanup = 0;
    main->thread.id_control = 0;
    main->thread.id_entry = 0;
    main->thread.id_rule = 0;
    main->thread.id_signal = 0;

    if (F_status_set_fine(status) == F_interrupt) {
      main->setting.state.status = F_status_set_error(F_interrupt);

      if (main->thread.signal) {
        main->program.signal_received = main->thread.signal;
      }
    }
    else {
      main->setting.state.status = F_status_is_error(status) ? F_status_set_error(F_failure) : F_okay;
    }

    if (main->program.signal_received) {
      fll_program_print_signal_received(&main->program.warning, main->program.signal_received);
    }
  }
#endif // _di_controller_process_

#ifdef __cplusplus
} // extern "C"
#endif
