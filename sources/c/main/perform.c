#include "controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_perform_ready_
  f_status_t controller_perform_ready(controller_t * const main, const uint8_t is_entry) {

    if (!main) return F_status_set_error(F_parameter);
    if (!is_entry) return F_okay;

    if (main->setting.flag & controller_main_flag_validate_e) {
      if ((main->setting.flag & controller_main_flag_simulate_e)) {
        controller_print_debug_perform_pid_file_control_socket(&main->program.debug);
      }

      return F_okay;
    }

    f_status_t status = F_okay;

    if (main->setting.entry.pid != controller_entry_pid_disable_e && !main->setting.path_pid.used) {
      status = controller_file_pid_create(main->program.pid, main->setting.path_pid);

      // Report pid file error but because this could be an "init" program, consider the pid file as optional and continue on.
      if (F_status_is_error(status)) {

        // Always return immediately on memory errors.
        if (F_status_set_fine(status) == F_memory_not) {
          controller_print_error_perform_pid_file_create(&main->program.error, macro_controller_f(controller_file_pid_create), is_entry);

          return status;
        }

        controller_print_debug_perform_pid_file_create_problem(&main->program.debug, macro_controller_f(controller_file_pid_create), is_entry);

        status = F_okay;
      }
      else {
        main->setting.flag |= controller_setting_flag_pid_created_e;

        controller_print_debug_perform_pid_file_create_success(&main->program.debug, is_entry);
      }
    }

    // Disabled, all parts are not yet implemented.
    /*if (main->setting.path_control.used) {
      status = controller_perform_ready_socket(main, is_entry);

      // Do not fail on non-memory errors related to creating the control socket.
      if (F_status_is_error(status) && F_status_set_fine(status) != F_memory) {
        status = F_okay;
      }
    }*/

    return status;
  }
#endif // _di_controller_perform_ready_

#ifndef _di_controller_perform_ready_socket_
  f_status_t controller_perform_ready_socket(controller_t * const main, const uint8_t is_entry) {

    f_status_t status = F_okay;

    if (main->process.control.flag & controller_control_flag_readonly_e) {
      if (f_file_exists(main->setting.path_control, F_true) != F_true) {
        controller_print_debug_perform_control_socket_missing_read_only(&main->program.debug);

        return F_data_not;
      }
    }

    status = f_socket_create(&main->process.control.server);

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_memory_not) {
        controller_print_error_status(&main->program.error, macro_controller_f(f_socket_create), F_status_set_fine(status));
      }
      else {
        // @todo make all message strings passed to controller_print_debug_perform_control_socket_failure() into global static strings and update the function accordingly.
        controller_print_debug_perform_control_socket_failure(&main->program.debug, F_status_set_fine(status), "could not be created");
      }

      return status;
    }

    if (!(main->process.control.flag & controller_control_flag_readonly_e)) {
      status = f_file_remove(main->setting.path_control);

      if (F_status_set_fine(status) == F_memory_not) {
        controller_print_error(global->thread, &main->program.error, F_status_set_fine(status), macro_controller_f(f_file_remove), F_true);

        return status;
      }
    }

    main->process.control.server.name = main->setting.path_control;

    status = f_socket_bind(&main->process.control.server);

    if (F_status_is_error(status)) {
      f_socket_disconnect(&main->process.control.server, f_socket_close_fast_e);

      if (!(main->process.control.flag & controller_control_flag_readonly_e)) {
        f_file_remove(main->setting.path_control);
      }

      if (F_status_set_fine(status) == F_memory_not) {
        controller_print_error(global->thread, &main->program.error, F_status_set_fine(status), macro_controller_f(f_socket_bind), F_true);
      }
      else {
        controller_print_debug_perform_control_socket_failure(&main->program.debug, F_status_set_fine(status), "could not be bound");
      }

      return status;
    }

    if (main->process.control.flag & (controller_control_flag_has_user_e | controller_control_flag_has_group_e)) {
      status = f_file_role_change(main->setting.path_control, main->process.control.user, main->process.control.group, F_true);

      if (F_status_is_error(status)) {
        f_socket_disconnect(&main->process.control.server, f_socket_close_fast_e);

        if (!(main->process.control.flag & controller_control_flag_readonly_e)) {
          f_file_remove(main->setting.path_control);
        }

        if (F_status_set_fine(status) == F_memory_not) {
          controller_print_error(global->thread, &main->program.error, F_status_set_fine(status), macro_controller_f(f_file_role_change), F_true);
        }
        else {
          controller_print_debug_perform_control_socket_failure(&main->program.debug, F_status_set_fine(status), "failed to set file roles");
        }

        return status;
      }
    }

    if (main->process.control.flag & controller_control_flag_has_mode_e) {
      status = f_file_mode_set(main->setting.path_control, main->process.control.mode);

      if (F_status_is_error(status)) {
        f_socket_disconnect(&main->process.control.server, f_socket_close_fast_e);

        if (!(main->process.control.flag & controller_control_flag_readonly_e)) {
          f_file_remove(main->setting.path_control);
        }

        if (F_status_set_fine(status) == F_memory_not) {
          controller_print_error(global->thread, &main->program.error, F_status_set_fine(status), macro_controller_f(f_file_role_change), F_true);
        }
        else {
          controller_print_debug_perform_control_socket_failure(&main->program.debug, F_status_set_fine(status), "failed to set file mode");
        }

        return status;
      }
    }

    controller_print_perform_debug_control_socket_success(&main->program.debug);

    // Disabled, not yet implemented.
    //status = f_thread_create(0, &global->thread->id_control, &controller_thread_control, (void *) global);

    if (status == F_child) return status;

    if (F_status_is_error(status)) {
      f_socket_disconnect(&main->process.control.server, f_socket_close_fast_e);

      if (!(main->process.control.flag & controller_control_flag_readonly_e)) {
        f_file_remove(main->setting.path_control);
      }

      if (global->thread->id_control) {
        f_thread_cancel(global->thread->id_control);
        f_thread_join(global->thread->id_control, 0);

        global->thread->id_control = 0;
      }

      controller_print_error_status(&main->program.error, macro_controller_f(f_thread_create), F_status_set_fine(status));
    }

    return F_okay;
  }
#endif // _di_controller_perform_ready_socket_

#ifdef __cplusplus
} // extern "C"
#endif
