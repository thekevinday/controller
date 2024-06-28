#include "../../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_error_rule_action_missing_pid_
  f_status_t controller_print_error_rule_action_missing_pid(fl_print_t * const print, const f_string_static_t alias) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QThe rule '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, alias, print->notable);
    fl_print_format("%[' is not designating a pid file.%]%r", print->to, print->context, print->context, f_string_eol_s);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_rule_action_missing_pid_

#ifndef _di_controller_print_error_rule_action_type_supported_not_
  f_status_t controller_print_error_rule_action_type_supported_not(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t type) {

    if (!print || !print->custom || !action) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QUnsupported action type '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, type, print->notable);
    fl_print_format("%[' while attempting to execute rule.%]%r", print->to, print->context, print->context, f_string_eol_s);

    controller_print_error_rule_cache(print, action, F_true);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_rule_action_type_supported_not_

#ifndef _di_controller_print_error_rule_action_unknown_execute_
  f_status_t controller_print_error_rule_action_unknown_execute(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t name, const f_string_static_t type, const f_number_unsigned_t total) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    if (total) {
      fl_print_format("%r%[%QThe rule '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
      fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, name, print->notable);
      fl_print_format("%[' has no '%]", print->to, print->context, print->context);
      fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, type, print->notable);
      fl_print_format("%[' action to execute.%]%r", print->to, print->context, print->context, f_string_eol_s);
    }
    else {
      fl_print_format("%r%[%QThe rule '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
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
