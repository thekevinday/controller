#include "../../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_debug_perform_control_socket_failure_
  f_status_t controller_print_debug_perform_control_socket_failure(fl_print_t * const print, const f_status_t status, const f_string_t message) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_debug_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QControl socket '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, main->process.path_control, print->notable);
    fl_print_format("%[' %S, code %]", print->to, print->context, message, print->context);
    fl_print_format(f_string_format_ui_single_s.string, print->to, print->notable, status, print->notable);
    fl_print_format(f_string_format_sentence_end_s.string, print->to, print->context, print->context, f_string_eol_s);

    controller_unlock_print_flush(print->to, &main->thread);
  }
#endif // _di_controller_print_debug_perform_control_socket_failure_

#ifndef _di_controller_print_debug_perform_control_socket_success_
  f_status_t controller_print_debug_perform_control_socket_success(fl_print_t * const print) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_debug_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%rControl socket '", print->to, f_string_eol_s);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, main->process.path_control, print->notable);
    fl_print_format("' created.%r", print->to, f_string_eol_s);

    controller_unlock_print_flush(print->to, &main->thread);
  }
#endif // _di_controller_print_debug_perform_control_socket_success_

#ifndef _di_controller_print_debug_perform_control_socket_missing_read_only_
  f_status_t controller_print_debug_perform_control_socket_missing_read_only(fl_print_t * const print) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_debug_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QControl socket '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, main->process.path_control, print->notable);
    fl_print_format("' .%r", print->to, f_string_eol_s);
    fl_print_format("%[' cannot be found while read only mode is enabled and so the Control socket is unavailable.%]%r", print->to, print->context, print->context, f_string_eol_s);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_debug_perform_control_socket_missing_read_only_

#ifdef __cplusplus
} // extern "C"
#endif
