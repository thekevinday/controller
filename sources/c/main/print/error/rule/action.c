#include "../../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_error_rule_action_first_
  f_status_t controller_print_error_rule_action_first(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t buffer, const f_range_t range) {

    if (!print || !print->custom || !action) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QRule Item Action '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_r_single_s.string, print->to, print->notable, controller_rerun_s, print->notable);
    fl_print_format("%[' has '%]", print->to, print->context, print->context);
    fl_print_format(f_string_format_Q_range_single_s.string, print->to, print->notable, buffer, range, print->notable);
    fl_print_format("%[' as the first value, only the following are allowed: '%]", print->to, print->context, print->context);
    fl_print_format("%[%r%]%[', '%]", print->to, print->notable, controller_freeze_s, print->notable, print->context, print->context);
    fl_print_format("%[%r%]%[', '%]", print->to, print->notable, controller_kill_s, print->notable, print->context, print->context);
    fl_print_format("%[%r%]%[', '%]", print->to, print->notable, controller_pause_s, print->notable, print->context, print->context);
    fl_print_format("%[%r%]%[', '%]", print->to, print->notable, controller_reload_s, print->notable, print->context, print->context);
    fl_print_format("%[%r%]%[', '%]", print->to, print->notable, controller_restart_s, print->notable, print->context, print->context);
    fl_print_format("%[%r%]%[', '%]", print->to, print->notable, controller_resume_s, print->notable, print->context, print->context);
    fl_print_format("%[%r%]%[', '%]", print->to, print->notable, controller_start_s, print->notable, print->context, print->context);
    fl_print_format("%[%r%]%[', or '%]", print->to, print->notable, controller_stop_s, print->notable, print->context, print->context);
    fl_print_format(f_string_format_r_single_s.string, print->to, print->notable, controller_thaw_s, print->notable, print->context);
    fl_print_format(f_string_format_sentence_end_quote_s.string, print->to, print->context, print->context, f_string_eol_s);

    controller_print_error_rule_cache(print, action, F_true);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_rule_action_first_

#ifndef _di_controller_print_error_rule_action_fss_0003_unsupported_
  f_status_t controller_print_error_rule_action_fss_0003_unsupported(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t name) {

    if (!print || !print->custom || !action) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QFSS Extended List (FSS-0003) is not allowed for the Rule Item Action '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, name, print->notable);
    fl_print_format(f_string_format_sentence_end_quote_s.string, print->to, print->context, print->context, f_string_eol_s);

    controller_print_error_rule_cache(print, action, F_true);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_rule_action_fss_0003_unsupported_

#ifndef _di_controller_print_error_rule_action_missing_pid_
  f_status_t controller_print_error_rule_action_missing_pid(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t alias) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QThe Rule '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, alias, print->notable);
    fl_print_format("%[' is not designating a PID file.%]%r", print->to, print->context, print->context, f_string_eol_s);

    controller_print_error_rule_cache(print, action, F_true);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_rule_action_missing_pid_

#ifndef _di_controller_print_error_rule_action_positive_number_not_
  f_status_t controller_print_error_rule_action_positive_number_not(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t name, const f_string_static_t buffer, const f_ranges_t contents, const f_number_unsigned_t index, const f_status_t status) {

    if (!print || !print->custom || !action) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QRule Item Action '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_r_single_s.string, print->to, print->notable, controller_rerun_s, print->notable);
    fl_print_format("%[' requires a positive whole number or 0 for the '%]", print->to, print->context, print->context);
    fl_print_format(f_string_format_S_single_s.string, print->to, print->notable, name, print->notable);
    fl_print_format("%[' value", print->to, print->context, print->context);

    if (index + 1 == contents.used) {
      fl_print_format(", but none were given.%]%r", print->to, print->context, f_string_eol_s);
    }
    else {
      fl_print_format(", but '%]%[%/Q%]", print->to, print->context, print->notable, buffer, contents.array[index], print->notable);

      if (status == F_number || status == F_number_decimal) {
        fl_print_format("%[' was given.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (status == F_number_overflow) {
        fl_print_format("%[' is too large.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else {
        fl_print_format("%[' is negative.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
    }

    controller_print_error_rule_cache(print, action, F_true);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_rule_action_positive_number_not_

#ifndef _di_controller_print_error_rule_action_second_
  f_status_t controller_print_error_rule_action_second(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t buffer, const f_range_t range) {

    if (!print || !print->custom || !action) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QRule Item Action '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_r_single_s.string, print->to, print->notable, controller_rerun_s, print->notable);
    fl_print_format("%[' has '%]", print->to, print->context, print->context);
    fl_print_format(f_string_format_Q_range_single_s.string, print->to, print->notable, buffer, range, print->notable);
    fl_print_format("%[' as the second value, only the following are allowed: '%]", print->to, print->context, print->context);
    fl_print_format("%[%r%]%[' or '%]", print->to, print->notable, controller_stop_s, print->notable, print->context, print->context);
    fl_print_format(f_string_format_r_single_s.string, print->to, print->notable, controller_thaw_s, print->notable, print->context);
    fl_print_format(f_string_format_sentence_end_quote_s.string, print->to, print->context, print->context, f_string_eol_s);

    controller_print_error_rule_cache(print, action, F_true);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_rule_action_second_

#ifndef _di_controller_print_error_rule_action_type_unsupported_
  f_status_t controller_print_error_rule_action_type_unsupported(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t type, const f_string_t message) {

    if (!print || !print->custom || !action) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QUnsupported Action type '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, type, print->notable);
    fl_print_format("%[' while attempting to %S.%]%r", print->to, print->context, message, print->context, f_string_eol_s);

    controller_print_error_rule_cache(print, action, F_true);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_rule_action_type_unsupported_

#ifndef _di_controller_print_error_rule_action_unknown_
  f_status_t controller_print_error_rule_action_unknown(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t name, const f_string_static_t buffer, const f_range_t range) {

    if (!print || !print->custom || !action) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QRule Item Action '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, name, print->notable);
    fl_print_format("%[' has an unknown value '%]", print->to, print->context, print->context);
    fl_print_format(f_string_format_Q_range_single_s.string, print->to, print->notable, buffer, range, print->notable);
    fl_print_format(f_string_format_sentence_end_quote_s.string, print->to, print->context, print->context, f_string_eol_s);

    controller_print_error_rule_cache(print, action, F_true);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_rule_action_unknown_

#ifndef _di_controller_print_error_rule_action_unknown_execute_
  f_status_t controller_print_error_rule_action_unknown_execute(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t name, const f_string_static_t type, const f_number_unsigned_t total) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    if (total) {
      fl_print_format("%r%[%QThe Rule '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
      fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, name, print->notable);
      fl_print_format("%[' has no '%]", print->to, print->context, print->context);
      fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, type, print->notable);
      fl_print_format("%[' Action to execute.%]%r", print->to, print->context, print->context, f_string_eol_s);
    }
    else {
      fl_print_format("%r%[%QThe Rule '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
      fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, name, print->notable);
      fl_print_format("%[ has no known '%]", print->to, print->context, print->context);
      fl_print_format("%[%r %r%]", print->to, print->notable, controller_rule_s, controller_type_s, print->notable);
      fl_print_format("%[' (such as '%]", print->to, print->context, print->context);
      fl_print_format(f_string_format_r_single_s.string, print->to, print->notable, controller_command_s, print->notable);
      fl_print_format("%[', '%]", print->to, print->context, print->context);
      fl_print_format(f_string_format_r_single_s.string, print->to, print->notable, controller_service_s, print->notable);
      fl_print_format("%[', '%]", print->to, print->context, print->context);
      fl_print_format(f_string_format_r_single_s.string, print->to, print->notable, controller_script_s, print->notable);
      fl_print_format("%[', or '%]", print->to, print->context, print->context);
      fl_print_format(f_string_format_r_single_s.string, print->to, print->notable, controller_utility_s, print->notable);
      fl_print_format("%[') to execute.%]%r", print->to, print->context, print->context, f_string_eol_s);
    }

    controller_print_error_rule_cache(print, action, F_true);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_rule_action_unknown_execute_

#ifdef __cplusplus
} // extern "C"
#endif
