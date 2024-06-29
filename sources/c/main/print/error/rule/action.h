/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print entry action error functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_error_entry_action_h
#define _controller_main_print_error_entry_action_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print Rule error message about the first Rule Item Action parameter being invalid.
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
 *   The Action cache.
 *
 *   Must not be NULL.
 * @param action
 *   The Action cache.
 *
 *   Must not be NULL.
 * @param buffer
 *   The buffer containing the setting name.
 * @param range
 *   The range within the buffer representing the unknown action name.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_rule_action_first_
  extern f_status_t controller_print_error_rule_action_first(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t buffer, const f_range_t range);
#endif // _di_controller_print_error_rule_action_first_

/**
 * Print an error message about the FSS-0003 standard not being supported for a particular Rule Action.
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
 *   The Action cache.
 *
 *   Must not be NULL.
 * @param alias
 *   The Rule alias of the Rule that is missing the pid file designation.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_rule_action_fss_0003_unsupported_
  extern f_status_t controller_print_error_rule_action_fss_0003_unsupported(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t name);
#endif // _di_controller_print_error_rule_action_fss_0003_unsupported_

/**
 * Print an error or warning message about some rule not having the PID file information.
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
 *   The Rule alias of the Rule that is missing the pid file designation.
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
 * Print Rule error message about the Item value not being a positive whole number.
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
 *   The Action cache.
 *
 *   Must not be NULL.
 * @param name
 *   The Object name.
 * @param buffer
 *   The buffer containing the number.
 * @param contents
 *   The array of ranges representing the Content.
 * @param index
 *   The index position in content representing the Content range for the buffer.
 * @param status
 *   The status code of the error.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_rule_action_positive_number_not_
  extern f_status_t controller_print_error_rule_action_positive_number_not(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t name, const f_string_static_t buffer, const f_ranges_t contents, const f_number_unsigned_t index, const f_status_t status);
#endif // _di_controller_print_error_rule_action_positive_number_not_

/**
 * Print Rule error message about the second Rule Item Action parameter being invalid.
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
 *   The Action cache.
 *
 *   Must not be NULL.
 * @param buffer
 *   The buffer containing the second Action.
 * @param range
 *   The range within the buffer representing the second Action.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_rule_action_second_
  extern f_status_t controller_print_error_rule_action_second(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t buffer, const f_range_t range);
#endif // _di_controller_print_error_rule_action_second_

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
#ifndef _di_controller_print_error_rule_action_type_unsupported_
  extern f_status_t controller_print_error_rule_action_type_unsupported(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t type);
#endif // _di_controller_print_error_rule_action_type_unsupported_

/**
 * Print Rule error message about the Rule Item Action being unknown.
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
 *   The Action cache.
 *
 *   Must not be NULL.
 * @param name
 *   The parameter name whose value is unknown.
 * @param buffer
 *   The buffer containing the setting name.
 * @param range
 *   The range within the buffer representing the unknown action name.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_rule_action_unknown_
  extern f_status_t controller_print_error_rule_action_unknown(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t name, const f_string_static_t buffer, const f_range_t range);
#endif // _di_controller_print_error_rule_action_unknown_

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
