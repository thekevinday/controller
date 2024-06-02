/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print rule action functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_rule_action_h
#define _controller_main_print_rule_action_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print an error or warning message about some rule not having the pid file information.
 *
 * @param print
 *   The error or warning output structure.
 * @param alias
 *   The rule alias of the rule that is missing the pid file designation.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_rule_action_error_missing_pid_
  extern f_status_t controller_print_rule_action_error_missing_pid(fl_print_t * const print, const f_string_static_t alias);
#endif // _di_controller_print_rule_action_error_missing_pid_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_rule_action_h
