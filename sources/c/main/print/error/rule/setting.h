/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print Entry setting error functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_error_entry_setting_h
#define _controller_main_print_error_entry_setting_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print a message about a Rule setting problem.
 *
 * This is intended to be explicitly called by controller_rule_setting_read().
 * This is intended only to be used for simple messages.
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
 *   This alters action.line_item to get the current line.
 *
 *   Must not be NULL.
 * @param message
 *   The string to append to the message being printed.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_rule_setting_
  extern f_status_t controller_print_error_rule_setting(fl_print_t * const print, controller_cache_action_t * const action, const f_string_t message);
#endif // _di_controller_print_error_rule_setting_

/**
 * Print a message about a Rule setting problem given a specified reason and providing the setting name or value.
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
 * @param reason
 *   The reason for the error.
 * @param name
 *   The name or value of the setting associated with the error.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_rule_setting_reason_name_
  extern f_status_t controller_print_error_rule_setting_reason_name(fl_print_t * const print, controller_cache_action_t * const action, const f_string_t reason, const f_string_static_t name);
#endif // _di_controller_print_error_rule_setting_reason_name_

/**
 * Print a message about a Rule setting problem, with additional messages about the value.
 *
 * This is intended to be explicitly called by controller_rule_setting_read().
 * This is intended only to be used for simple messages.
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
 *   This alters action.line_item to get the current line.
 *
 *   Must not be NULL.
 * @param before
 *   The string to add to the message being printed (before the value).
 * @param buffer
 *   The buffer representing the Rule settings.
 * @param range_content
 *   The range within the buffer representing the setting Content.
 * @param after
 *   The string to add to the message being printed (after the value).
 * @param start
 *   The position where to start counting lines.
 * @param line
 *   The current line number.
 * @param state
 *   The state information
 *
 *   The state.status is modified.
 *
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_rule_setting_with_range_
  extern f_status_t controller_print_error_rule_setting_with_range(fl_print_t * const print, controller_cache_action_t * const action, const f_string_t before, const f_string_static_t buffer, const f_range_t range_content, const f_string_t after, const f_number_unsigned_t start, const f_number_unsigned_t line, f_state_t * const state);
#endif // _di_controller_print_error_rule_setting_with_range_

/**
 * Print message regarding the mapping of a setting when in simulation or verbose mode.
 *
 * @param print
 *   The error or warning output structure.
 *
 *   Must not be NULL.
 * @param name
 *   The Object name of the setting being populated.
 * @param map
 *   The map being applied.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_rule_setting_mapping_
  extern f_status_t controller_print_error_rule_setting_mapping(fl_print_t * const print, const f_string_static_t name, const f_string_map_t map);
#endif // _di_controller_print_error_rule_setting_mapping_

/**
 * Print message regarding the setting being invalid.
 *
 * @param print
 *   The error or warning output structure.
 *
 *   Must not be NULL.
 * @param action
 *   The Action cache.
 *
 *   Must not be NULL.
 * @param name
 *   The name of the setting that is invalid.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_rule_setting_name_invalid_
  extern f_status_t controller_print_error_rule_setting_name_invalid(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t name);
#endif // _di_controller_print_error_rule_setting_name_invalid_

/**
 * Print message regarding the "nice" setting value being an invalid number.
 *
 * @param print
 *   The error or warning output structure.
 *
 *   Must not be NULL.
 * @param action
 *   The Action cache.
 *
 *   Must not be NULL.
 * @param buffer
 *   The buffer containing the invalid number.
 * @param range
 *   The ranger within the buffer representing the invalid number.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_rule_setting_number_invalid_nice_
  extern f_status_t controller_print_error_rule_setting_number_invalid_nice(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t buffer, const f_range_t range);
#endif // _di_controller_print_error_rule_setting_number_invalid_nice_

/**
 * Print message regarding the first value for the "on" setting being invalid.
 *
 * @param print
 *   The error or warning output structure.
 *
 *   Must not be NULL.
 * @param action
 *   The Action cache.
 *
 *   Must not be NULL.
 * @param buffer
 *   The buffer containing the invalid value.
 * @param range
 *   The ranger within the buffer representing the invalid value.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_rule_setting_number_invalid_on_first_
  extern f_status_t controller_print_error_rule_setting_number_invalid_on_first(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t buffer, const f_range_t range);
#endif // _di_controller_print_error_rule_setting_number_invalid_on_first_

/**
 * Print message regarding the second value for the "on" setting being invalid.
 *
 * @param print
 *   The error or warning output structure.
 *
 *   Must not be NULL.
 * @param action
 *   The Action cache.
 *
 *   Must not be NULL.
 * @param buffer
 *   The buffer containing the invalid value.
 * @param range
 *   The ranger within the buffer representing the invalid value.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_rule_setting_number_invalid_on_second_
  extern f_status_t controller_print_error_rule_setting_number_invalid_on_second(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t buffer, const f_range_t range);
#endif // _di_controller_print_error_rule_setting_number_invalid_on_second_

/**
 * Print message regarding the "scheduler" setting value being an invalid number.
 *
 * @param print
 *   The error or warning output structure.
 *
 *   Must not be NULL.
 * @param action
 *   The Action cache.
 *
 *   Must not be NULL.
 * @param buffer
 *   The buffer containing the invalid number.
 * @param range
 *   The ranger within the buffer representing the invalid number.
 * @param zero_only
 *   If TRUE, then only 0 is supported.
 *   If FALSE, then only the range 1 through 99 is supported.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_rule_setting_number_invalid_scheduler_
  extern f_status_t controller_print_error_rule_setting_number_invalid_scheduler(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t buffer, const f_range_t range, const uint8_t zero_only);
#endif // _di_controller_print_error_rule_setting_number_invalid_scheduler_

/**
 * Print message regarding the "timeout" setting value being invalid.
 *
 * @param print
 *   The error or warning output structure.
 *
 *   Must not be NULL.
 * @param action
 *   The Action cache.
 *
 *   Must not be NULL.
 * @param buffer
 *   The buffer containing the invalid value.
 * @param range
 *   The ranger within the buffer representing the invalid value.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_rule_setting_number_invalid_timeout_
  extern f_status_t controller_print_error_rule_setting_number_invalid_timeout(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t buffer, const f_range_t range);
#endif // _di_controller_print_error_rule_setting_number_invalid_timeout_

/**
 * Print message regarding the population of a setting when in simulation or verbose mode.
 *
 * @param print
 *   The error or warning output structure.
 *
 *   Must not be NULL.
 * @param name
 *   The Object name of the setting being populated.
 * @param name_sub
 *   A sub-name associated with the setting being populated.
 *   Set to a string with used set to 0 to not use.
 * @param value
 *   The value being set.
 * @param suffix
 *   An additional message to append at the end (before the final period).
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_rule_setting_value_
  extern f_status_t controller_print_error_rule_setting_value(fl_print_t * const print, const f_string_static_t name, const f_string_static_t name_sub, const f_string_static_t value, const f_string_t suffix);
#endif // _di_controller_print_error_rule_setting_value_

/**
 * Print message regarding the population of a setting when in simulation or verbose mode.
 *
 * This handles the case where there are multiple values stored in the buffer_item at a given content_actions position.
 *
 * @param print
 *   The error or warning output structure.
 *
 *   Must not be NULL.
 * @param cache
 *   A structure for containing and caching relevant data.
 *
 *   Must not be NULL.
 * @param name
 *   The Object name of the setting being populated.
 * @param index
 *   Position within the content_actions range cache array.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_rule_setting_values_
  extern f_status_t controller_print_error_rule_setting_values(fl_print_t * const print, controller_cache_t * const cache, const f_string_static_t name, const f_number_unsigned_t index);
#endif // _di_controller_print_error_rule_setting_values_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_error_entry_setting_h
