#include "../../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_debug_perform_pid_file_control_socket_
  f_status_t controller_print_debug_perform_pid_file_control_socket(fl_print_t * const print) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_debug_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%rPID file '", print->to, f_string_eol_s);
    fl_print_format("%[%Q%]'.%r", print->to, print->notable, main->process.path_pid, print->notable, f_string_eol_s);

    if (main->process.path_control.used) {
      fl_print_format("%rControl socket '", print->to, f_string_eol_s);
      fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, main->process.path_control, print->notable);
      fl_print_format(f_string_format_sentence_end_quote_s.string, print->to, f_string_eol_s);
    }

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_debug_perform_pid_file_control_socket_

#ifndef _di_controller_print_debug_perform_pid_file_create_problem_
  f_status_t controller_print_debug_perform_pid_file_create_problem(fl_print_t * const print, const f_status_t status, const f_string_t function, const uint8_t is_entry) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_debug_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    if (F_status_set_fine(status) == F_read_only) {
      fl_print_format("%r%[%QThe pid file '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
      fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, main->process.path_pid, print->notable);
      fl_print_format("%[' could not be written because the destination is read only.%]%r", print->to, print->context, print->context, f_string_eol_s);
    }
    else {
      controller_print_error_file_status(print, function, main->process.path_pid, f_file_operation_create_s, fll_error_file_type_file_e, status);
    }

    f_file_stream_lock(print->to);

    controller_print_error_entry_cache(print, &main->thread.cache.action, is_entry);

    controller_unlock_print_flush(print->to, &main->thread);
  }
#endif // _di_controller_print_debug_perform_pid_file_create_problem_

#ifndef _di_controller_print_debug_perform_pid_file_create_success_
  f_status_t controller_print_debug_perform_pid_file_create_success(fl_print_t * const print) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_debug_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%rPID file '", print->to, f_string_eol_s);
    fl_print_format("%[%Q%]' created.%r", print->to, print->notable, main->process.path_pid, print->notable, f_string_eol_s);

    controller_unlock_print_flush(print->to, &main->thread);
  }
#endif // _di_controller_print_debug_perform_pid_file_create_success_

#ifdef __cplusplus
} // extern "C"
#endif
