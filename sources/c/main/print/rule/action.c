#include "../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_rule_action_error_missing_pid_
  void controller_print_rule_action_error_missing_pid(fl_print_t * const print, const f_string_static_t alias) {

    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fl_print_format("%r%[%QThe rule '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, alias, print->notable);
    fl_print_format("%[' is not designating a pid file.%]%r", print->to, print->context, print->context, f_string_eol_s);
  }
#endif // _di_controller_print_rule_action_error_missing_pid_

#ifdef __cplusplus
} // extern "C"
#endif
