#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_error_
  f_status_t controller_print_error(fl_print_t * const print, const f_string_t function) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    fll_error_print(print, F_status_set_fine(main->setting.state.status), function, fll_error_file_flag_fallback_e);

    return F_okay;
  }
#endif // _di_controller_print_error_

#ifndef _di_controller_print_error_failsafe_item_
  f_status_t controller_print_error_failsafe_item(fl_print_t * const print, controller_thread_t * const thread, const f_string_dynamic_t name) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_lock_print(print->to, thread);

    fl_print_format("%r%[%QFailed while processing requested failsafe item '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->set->notable, name, print->set->notable);
    fl_print_format(f_string_format_sentence_end_quote_s.string, print->to, print->context, print->context, f_string_eol_s);

    controller_unlock_print_flush(print->to, thread);

    return F_okay;
  }
#endif // _di_controller_print_error_failsafe_item_

#ifndef _di_controller_print_error_file_
  f_status_t controller_print_error_file(fl_print_t * const print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    fll_error_file_print(print, F_status_set_fine(main->setting.state.status), function, fll_error_file_flag_fallback_e, name, operation, type);

    return F_okay;
  }
#endif // _di_controller_print_error_file_

#ifndef _di_controller_print_error_file_status_
  f_status_t controller_print_error_file_status(fl_print_t * const print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type, const f_status_t status) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

    fll_error_file_print(print, status, function, fll_error_file_flag_fallback_e, name, operation, type);

    return F_okay;
  }
#endif // _di_controller_print_error_file_status_

#ifndef _di_controller_print_error_file_pid_exists_
  f_status_t controller_print_error_file_pid_exists(fl_print_t * const print, controller_thread_t * const thread, const f_string_dynamic_t path) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_lock_print(print->to, 0);

    fl_print_format("%r%[%QThe pid file '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->set->notable, path, print->set->notable);
    fl_print_format("%[' must not already exist.%]%r", print->to, print->context, print->context, f_string_eol_s);

    controller_unlock_print_flush(print->to, 0);

    return F_okay;
  }
#endif // _di_controller_print_error_file_pid_exists_

#ifndef _di_controller_print_error_status_
  f_status_t controller_print_error_status(fl_print_t * const print, const f_string_t function, const f_status_t status) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_error_print(print, status, function, fll_error_file_flag_fallback_e);

    return F_okay;
  }
#endif // _di_controller_print_error_status_

#ifdef __cplusplus
} // extern "C"
#endif
