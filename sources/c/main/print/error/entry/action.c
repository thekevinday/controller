#include "../../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_error_entry_action_execution_failure_
  f_status_t controller_print_error_entry_action_execution_failure(fl_print_t * const print, controller_cache_action_t * const action, const uint8_t is_entry, const int code) {

    if (!print || !print->custom || !action) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QExecution failed with return value of '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_i_single_s.string, print->to, print->notable, code, print->notable);
    fl_print_format(f_string_format_sentence_end_quote_s.string, print->to, print->context, print->context, f_string_eol_s);

    controller_print_error_entry_cache(print, action, is_entry);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_entry_action_execution_failure_

#ifndef _di_controller_print_error_entry_action_execution_missing_
  f_status_t controller_print_error_entry_action_execution_missing(fl_print_t * const print, controller_cache_action_t * const action, const uint8_t is_entry, const f_string_static_t name) {

    if (!print || !print->custom || !action) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QExecution failed, unable to find program or script '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, name, print->notable);
    fl_print_format(f_string_format_sentence_end_quote_s.string, print->to, print->context, print->context, f_string_eol_s);

    controller_print_error_entry_cache(print, action, is_entry);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_entry_action_execution_missing_

#ifndef _di_controller_print_error_entry_action_invalid_allow_1_
  f_status_t controller_print_error_entry_action_invalid_allow_1(fl_print_t * const print, controller_cache_action_t * const action, const uint8_t is_entry, const f_string_static_t has, const f_string_static_t allow) {

    if (!print || !print->custom || !action) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QThe %r Item Action may only have '%]", print->to, f_string_eol_s, print->context, print->prefix, is_entry ? controller_entry_s : controller_exit_s, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, allow, print->notable);
    fl_print_format("%[' but instead has '%]", print->to, print->context, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, has, print->notable);
    fl_print_format(f_string_format_sentence_end_quote_s.string, print->to, print->context, print->context, f_string_eol_s);

    controller_print_error_entry_cache(print, action, is_entry);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_entry_action_invalid_allow_1_

#ifndef _di_controller_print_error_entry_action_invalid_allow_3_
  f_status_t controller_print_error_entry_action_invalid_allow_3(fl_print_t * const print, controller_cache_action_t * const action, const uint8_t is_entry, const f_string_static_t has, const f_string_static_t allow_1, const f_string_static_t allow_2, const f_string_static_t allow_3) {

    if (!print || !print->custom || !action) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QThe %r Item Action must have one of '%]", print->to, f_string_eol_s, print->context, print->prefix, is_entry ? controller_entry_s : controller_exit_s, print->context);
    fl_print_format(f_string_format_r_single_s.string, print->to, print->notable, allow_1, print->notable);
    fl_print_format("%[', '%]", print->to, print->context, print->context);
    fl_print_format(f_string_format_r_single_s.string, print->to, print->notable, allow_2, print->notable);
    fl_print_format("%[', or '%]", print->to, print->context, print->context);
    fl_print_format(f_string_format_r_single_s.string, print->to, print->notable, allow_3, print->notable);
    fl_print_format("%[' but instead has '%]", print->to, print->context, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, has, print->notable);
    fl_print_format(f_string_format_sentence_end_quote_s.string, print->to, print->context, print->context, f_string_eol_s);

    controller_print_error_entry_cache(print, action, is_entry);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_entry_action_invalid_allow_3_

#ifndef _di_controller_print_error_entry_action_unsupported_number_
  f_status_t controller_print_error_entry_action_unsupported_number(fl_print_t * const print, controller_cache_action_t * const action, const uint8_t is_entry, const f_string_static_t has) {

    if (!print || !print->custom || !action) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QThe %r Item Action parameter '%]", print->to, f_string_eol_s, print->context, print->prefix, is_entry ? controller_entry_s : controller_exit_s, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, has, print->notable);
    fl_print_format("%[' is not a valid supported number.%]%r", print->to, print->context, print->context, f_string_eol_s);

    controller_print_error_entry_cache(print, action, is_entry);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_entry_action_unsupported_number_

#ifdef __cplusplus
} // extern "C"
#endif
