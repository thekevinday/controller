/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the Rule "setting" functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_rule_setting_h
#define _controller_main_rule_setting_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Identify the Rule Item code the given name represents.
 *
 * @param item
 *   The string representing an Rule Action.
 *
 * @return
 *   The Rule Item type code on success.
 *   0 if name is unknown.
 */
#ifndef _di_controller_rule_setting_limit_type_identify_
  extern uint8_t controller_rule_setting_limit_type_identify(const f_string_static_t item);
#endif // _di_controller_rule_setting_limit_type_identify_

/**
 * Get a string representing the Rule setting limit type.
 *
 * @param type
 *   The Rule setting limit type code.
 *
 * @return
 *   The string with used > 0 on success.
 *   The string with used == 0 if no match was found.
 */
#ifndef _di_controller_rule_setting_limit_type_name_
  extern f_string_static_t controller_rule_setting_limit_type_name(const uint8_t type);
#endif // di_controller_rule_setting_limit_type_name_

/**
 * Get the current line number relative to the start position within the buffer.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 * @param action
 *   The Action cache.
 *
 *   This alters the action.line_item to perform the calculation.
 *   This alters the action.line_action to save the line number.
 *   Both action.line_item and action.line_action should be the same after this function succeeds.
 *
 *   Must not be NULL.
 * @param buffer
 *   The string containing the lines to count.
 * @param start
 *   The start position in the buffer where counting begins.
 * @param line
 *   The current line number to start counting from.
 * @param state
 *   The state data.
 *
 *   The state.status is modified.
 *
 *   Must not be NULL.
 *
 * @see f_fss_count_lines()
 */
#ifndef _di_controller_rule_setting_line_action_
  extern f_status_t controller_rule_setting_line_action(controller_t * const main, controller_cache_action_t * const action, const f_string_static_t buffer, const f_number_unsigned_t start, const f_number_unsigned_t line, f_state_t * const state);
#endif // _di_controller_rule_setting_line_action_

/**
 * Read the content within the buffer, extracting all valid settings.
 *
 * This will perform additional FSS read functions as appropriate.
 *
 * Errors from this are not considered fatal, but the first error code encountered is returned.
 * Memory failure errors are always immediately returned.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 *
 *   This does not alter main.setting.state.status.
 * @param is_normal
 *   If TRUE, then process as if this operates during a normal operation (Entry and Control).
 *   If FALSE, then process as if this operates during a an Exit operation.
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param rule
 *   The processed Rule.
 *
 * @return
 *    F_okay on success.
 *
 *    F_valid_not (with error bit) on success but there were one or more invalid settings encountered.
 *
 *   Errors (with error bit) from: f_memory_array_increase().
 *   Errors (with error bit) from: f_rip_dynamic_partial_nulless().
 *   Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *   Errors (with error bit) from: fll_fss_extended_read().
 *
 *   Errors (with error bit) from: controller_path_canonical_relative().
 *
 * @see f_memory_array_increase()
 * @see f_rip_dynamic_partial_nulless()
 * @see f_string_dynamic_partial_append_nulless()
 * @see fll_fss_extended_read()
 *
 * @see controller_path_canonical_relative()
 */
#ifndef _di_controller_rule_setting_read_
  extern f_status_t controller_rule_setting_read(controller_t * const main, controller_cache_t * const cache, const uint8_t is_normal, controller_rule_t * const rule);
#endif // _di_controller_rule_setting_read_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_rule_setting_h
