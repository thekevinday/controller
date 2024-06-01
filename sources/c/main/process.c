#include "controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_main_process_
  void controller_main_process(controller_main_t * const main, controller_program_t * const program) {

    if (!main || !program || F_status_is_error(main->setting.state.status)) return;

    main->setting.state.status = F_okay;

    if (main->setting.flag & controller_main_flag_version_copyright_help_e) {
      if (main->setting.flag & controller_main_flag_help_e) {
        controller_main_print_message_help(&main->program.message, F_false);
      }
      else if (main->setting.flag & controller_main_flag_version_e) {
        fll_program_print_version(&main->program.message, controller_program_version_s);
      }
      else if (main->setting.flag & controller_main_flag_copyright_e) {
        fll_program_print_copyright(&main->program.message, fll_program_copyright_year_author_s);
      }

      return;
    }

    fl_print_t message = main->program.message;
    fl_print_t output = main->program.output;
    fl_print_t error = main->program.error;
    fl_print_t warning = main->program.warning;
    fl_print_t debug = main->program.debug;

    controller_thread_t thread = controller_thread_t_initialize;
    controller_global_t global = macro_controller_global_t_initialize_1(main, program, &thread, &message, &output, &error, &warning, &debug);

    message.custom = output.custom = error.custom = warning.custom = debug.custom = (void *) &global;

    // The global locks must be initialized, but only once, so initialize immediately upon allocation.
    f_status_t status = controller_main_lock_create(&thread.lock);

    if (F_status_is_error(status)) {
      controller_main_print_error_status(&main->program.error, macro_controller_f(controller_main_lock_create), status);
    } else {
      status = f_memory_array_increase(controller_allocation_small_d, sizeof(controller_instance_t), (void **) &thread.instances.array, &thread.instances.used, &thread.instances.size);

      if (F_status_is_error(status)) {
        controller_main_print_error_status(&main->program.error, macro_controller_f(f_memory_array_increase), status);
      }
    }

    if (F_status_is_error_not(status)) {
      status = f_thread_create(0, &thread.id_signal, &controller_main_thread_signal_normal, (void *) &global);
    }

    if (F_status_is_error(status)) {
      thread.id_signal = 0;

      controller_main_print_error_status(&main->program.error, macro_controller_f(f_thread_create), status);
    }
    else {
      if (main->setting.flag & controller_main_flag_daemon_e) {
        program->ready = controller_program_ready_done_e;

        if (f_file_exists(program->path_pid, F_true) == F_true) {
          status = F_status_set_error(F_available_not);
          program->ready = controller_program_ready_abort_e;

          controller_main_print_error_file_pid_exists(&main->program.error, &thread, program->path_pid);
        }
      }
      else if (program->name_entry.used) {
        status = f_thread_create(0, &thread.id_entry, &controller_main_thread_entry, (void *) &global);

        if (F_status_is_error(status)) {
          controller_main_print_error_status(&main->program.error, macro_controller_f(f_thread_create), status);
        }
        else {
          controller_main_thread_join(&thread.id_entry);

          status = thread.status;
          thread.id_entry = 0;
        }
      }
    }

    // Only make the rule and control threads available once any/all pre-processing are complete.
    if (F_status_is_error_not(status) && status != F_failure && status != F_child && thread.enabled == controller_thread_enabled_e) {
      if (!(main->setting.flag & controller_main_flag_validate_e)) {

        // Wait for the entry thread to complete before starting the rule thread.
        controller_main_thread_join(&thread.id_rule);

        if (thread.enabled && program->mode == controller_program_mode_service_e) {
          status = f_thread_create(0, &thread.id_rule, &controller_main_thread_rule, (void *) &global);

          if (F_status_is_error(status)) {
            thread.id_rule = 0;
          }
          else {
            status = f_thread_create(0, &thread.id_cleanup, &controller_main_thread_cleanup, (void *) &global);
          }

          if (F_status_is_error(status)) {
            thread.id_cleanup = 0;

            controller_main_print_error_status(&main->program.error, macro_controller_f(f_thread_create), status);
          }
        }
      }
    }

    if (status == F_child) {
      main->setting.state.status = F_child;

      controller_thread_delete(&thread);

      return;
    }

    if (F_status_is_error_not(status) && status != F_failure && !(main->setting.flag & controller_main_flag_validate_e) && controller_main_thread_is_enabled(F_true, &thread)) {
      if (program->mode == controller_program_mode_service_e) {
        controller_main_thread_join(&thread.id_signal);
      }
      else if (program->mode == controller_program_mode_helper_e || program->mode == controller_program_mode_program_e) {
        status = controller_main_rule_wait_all(global, F_true, F_false);
      }
    }

    controller_main_thread_instance_cancel(global, F_true, controller_thread_cancel_call_e);

    controller_main_thread_instance_exit(&global);

    if (thread.id_signal) f_thread_join(thread.id_signal, 0);
    if (thread.id_cleanup) f_thread_join(thread.id_cleanup, 0);
    if (thread.id_control) f_thread_join(thread.id_control, 0);
    if (thread.id_entry) f_thread_join(thread.id_entry, 0);
    if (thread.id_rule) f_thread_join(thread.id_rule, 0);

    thread.id_cleanup = 0;
    thread.id_control = 0;
    thread.id_entry = 0;
    thread.id_rule = 0;
    thread.id_signal = 0;

    controller_thread_delete(&thread);

    if (F_status_set_fine(status) == F_interrupt) {
      fll_program_print_signal_received(&main->program.warning, thread.signal);

      if (main->program.output.verbosity > f_console_verbosity_quiet_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.output.to);
      }

      fll_program_print_signal_received(&main->program.warning, main->program.signal_received);

      return F_status_set_error(F_interrupt);
    }

    return F_status_is_error(status) ? F_status_set_error(F_failure) : F_okay;
  }
#endif // _di_controller_main_process_

#ifdef __cplusplus
} // extern "C"
#endif
