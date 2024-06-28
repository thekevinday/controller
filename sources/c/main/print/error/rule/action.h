/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print error entry action functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_error_entry_action_h
#define _controller_main_print_error_entry_action_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print an error or warning message about some rule not having the pid file information.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be controller_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 *   Must not be NULL.
 * @param alias
 *   The rule alias of the rule that is missing the pid file designation.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_rule_action_missing_pid_
  extern f_status_t controller_print_error_rule_action_missing_pid(fl_print_t * const print, const f_string_static_t alias);
#endif // _di_controller_print_error_rule_action_missing_pid_

/**
 * Print an error about Rule Action type not being supported.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be controller_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 *   Must not be NULL.
 * @param action
 *   The action cache.
 *
 *   Must not be NULL.
 * @param type
 *   The Action type name.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_rule_action_type_supported_not_
  extern f_status_t controller_print_error_rule_action_type_supported_not(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t type);
#endif // _di_controller_print_error_rule_action_type_supported_not_

/**
 * Print an error about Rule Action type not being supported.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be controller_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 *   Must not be NULL.
 * @param action
 *   The action cache.
 *
 *   Must not be NULL.
 * @param name
 *   The Rule name.
 * @param type
 *   The Action type name.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_rule_action_unknown_execute_
  extern f_status_t controller_print_error_rule_action_unknown_execute(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t name, const f_string_static_t type, const f_number_unsigned_t total);
#endif // _di_controller_print_error_rule_action_unknown_execute_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_error_entry_action_h
