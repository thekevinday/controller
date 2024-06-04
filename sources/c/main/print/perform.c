#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_perform_debug_control_socket_failure_
  f_status_t controller_print_perform_debug_control_socket_failure(fl_print_t * const print, const f_status_t status, const f_string_t message) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_debug_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QControl socket '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, main->setting.path_control, print->notable);
    fl_print_format("%[' %S, code %]", print->to, print->context, message, print->context);
    fl_print_format(f_string_format_ui_single_s.string, print->to, print->notable, status, print->notable);
    fl_print_format(f_string_format_sentence_end_s.string, print->to, print->context, print->context, f_string_eol_s);

    controller_unlock_print_flush(print->to, &main->thread);
  }
#endif // _di_controller_print_perform_debug_control_socket_failure_

#ifndef _di_controller_print_perform_debug_control_socket_success_
  f_status_t controller_print_perform_debug_control_socket_success(fl_print_t * const print, const f_status_t status, const f_string_t message) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_debug_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%rControl socket '", print->to, f_string_eol_s);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, main->setting.path_control, print->notable);
    fl_print_format("' created.%r", print->to, f_string_eol_s);

    controller_unlock_print_flush(print->to, &main->thread);
  }
#endif // _di_controller_print_perform_debug_control_socket_success_

#ifndef _di_controller_print_perform_debug_control_socket_missing_read_only_
  f_status_t controller_print_perform_debug_control_socket_missing_read_only(fl_print_t * const print) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_debug_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QControl socket '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, main->setting.path_control, print->notable);
    fl_print_format("' .%r", print->to, f_string_eol_s);
    fl_print_format("%[' cannot be found while read only mode is enabled and so the Control socket is unavailable.%]%r", print->to, print->context, print->context, f_string_eol_s);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_perform_debug_control_socket_missing_read_only_

#ifndef _di_controller_print_perform_debug_pid_file_control_socket_
  f_status_t controller_print_perform_debug_pid_file_control_socket(fl_print_t * const print) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_debug_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%rPID file '", print->to, f_string_eol_s);
    fl_print_format("%[%Q%]'.%r", print->to, print->notable, main->setting.path_pid, print->notable, f_string_eol_s);

    if (main->setting.path_control.used) {
      fl_print_format("%rControl socket '", print->to, f_string_eol_s);
      fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, main->setting.path_control, print->notable);
      fl_print_format("'.%r", print->to, f_string_eol_s);
    }

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_perform_debug_pid_file_control_socket_

#ifndef _di_controller_print_perform_debug_pid_file_create_problem_
  f_status_t controller_print_perform_debug_pid_file_create_problem(fl_print_t * const print, const f_string_t function, const f_status_t status, const uint8_t is_entry) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_debug_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    if (F_status_set_fine(status) == F_read_only) {
      fl_print_format("%r%[%QThe pid file '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
      fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, main->setting.path_pid, print->notable);
      fl_print_format("%[' could not be written because the destination is read only.%]%r", print->to, print->context, print->context, f_string_eol_s);
    }
    else {
      controller_print_error_file_status(print, function, F_true, main->setting.path_pid, f_file_operation_create_s, fll_error_file_type_file_e, status);
    }

    f_file_stream_lock(print->to);

    controller_entry_print_error_cache(print->to, main->thread.cache.action, is_entry);

    controller_unlock_print_flush(print->to, &main->thread);
  }
#endif // _di_controller_print_perform_debug_pid_file_create_problem_

#ifndef _di_controller_print_perform_debug_pid_file_create_success_
  f_status_t controller_print_perform_debug_pid_file_create_success(fl_print_t * const print, const uint8_t is_entry) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_debug_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%rPID file '", print->to, f_string_eol_s);
    fl_print_format("%[%Q%]' created.%r", print->to, print->notable, main->setting.path_pid, print->notable, f_string_eol_s);

    controller_unlock_print_flush(print->to, &main->thread);
  }
#endif // _di_controller_print_perform_debug_pid_file_create_success_

#ifndef _di_controller_print_perform_error_pid_file_create_
  f_status_t controller_print_perform_error_pid_file_create(fl_print_t * const print, const f_string_t function, const f_status_t status, const uint8_t is_entry) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    controller_print_error_file_status(print, function, F_true, main->setting.path_pid, f_file_operation_create_s, fll_error_file_type_file_e, status);

    f_file_stream_lock(print->to);

    controller_entry_print_error_cache(print->to, main->thread.cache.action, is_entry);

    controller_unlock_print_flush(print->to, &main->thread);
  }
#endif // _di_controller_print_perform_error_pid_file_create_

#ifdef __cplusplus
} // extern "C"
#endif
