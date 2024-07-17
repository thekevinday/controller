/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print Entry Item error functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_error_entry_item_h
#define _controller_main_print_error_entry_item_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print additional error/warning information in addition to existing error.
 *
 * This is explicitly intended to be used in addition to the error message.
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
 * @param item
 *   If TRUE, then this error is associated with an item.
 *   If FALSE, then this error is associated with a Rule setting.
 * @param status
 *   The status code representing the failure (without the error bit set).
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_rule_item_
  extern f_status_t controller_print_error_rule_item(fl_print_t * const print, controller_cache_action_t * const action, const uint8_t item, const f_status_t status);
#endif // _di_controller_print_error_rule_item_

/**
 * Print an error or warning message related to the failed execution of some program or script.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be controller_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 *   Must not be NULL.
 * @param script_is
 *   If TRUE, then this represents a script.
 *   If FALSE, then this represents a program.
 * @param name
 *   The name of the program or script.
 * @param code
 *   The code returned by the executed program or script.
 * @param status
 *   The status code representing the failure (without the error bit set).
 * @param result
 *   The status code result.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_rule_item_execute_
  extern f_status_t controller_print_error_rule_item_execute(fl_print_t * const print, const uint8_t script_is, const f_string_static_t name, const f_status_t status, const int result);
#endif // _di_controller_print_error_rule_item_execute_

/**
 * Print an error about a Rule have no Items to execute.
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
 *   The Rule alias of the Rule that has no Items.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_rule_item_execute_none_
  extern f_status_t controller_print_error_rule_item_execute_none(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t alias);
#endif // _di_controller_print_error_rule_item_execute_none_

/**
 * Print an error or warning message related to need/want/wish settings of some Rule.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be controller_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 *   Must not be NULL.
 * @param need_want_wish
 *   The appropriate string, such as "needs", "wants", or "wishes for" to output when describing this error/warning.
 *   This string is expected to already be "safe" (no control characters, etc..).
 * @param value
 *   The value that is the error or warning.
 * @param why
 *   A short explanation on why this is an error or warning.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_rule_item_need_want_wish_
  extern f_status_t controller_print_error_rule_item_need_want_wish(fl_print_t * const print, const f_string_static_t need_want_wish, const f_string_static_t value, const f_string_t why);
#endif // _di_controller_print_error_rule_item_need_want_wish_

/**
 * Print an error or warning message about some Rule not being loaded.
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
 *   The Rule alias of the Rule that is not loaded.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_rule_item_rule_not_loaded_
  extern f_status_t controller_print_error_rule_item_rule_not_loaded(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t alias);
#endif // _di_controller_print_error_rule_item_rule_not_loaded_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_error_entry_item_h
