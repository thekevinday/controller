/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the Rule "action" functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_rule_action_h
#define _controller_main_rule_action_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Get a string representing the Rule Action method.
 *
 * @param type
 *   The Rule Action type code.
 *
 * @return
 *   The string with used > 0 on success.
 *   The string with used == 0 if no match was found.
 */
#ifndef _di_controller_rule_action_method_name_
  extern f_string_static_t controller_rule_action_method_name(const uint8_t type);
#endif // _di_controller_rule_action_method_name_

/**
 * Convert the Action type to an Action execute type.
 *
 * @param type
 *   The Action type to convert from.
 *
 * @return
 *   The converted Action type, converted into an Action execute type.
 *
 *   The code controller_rule_action_execute_type__enum_size_e is returned for unknown types.
 */
#ifndef _di_controller_rule_action_type_to_action_execute_type_
  extern uint8_t controller_rule_action_type_to_action_execute_type(const uint8_t type);
#endif // _di_controller_rule_action_type_to_action_execute_type_

/**
 * Read the content within the buffer, processing the Action (or a set of within a list) for the given item.
 *
 * This will automatically increase the size of the actions array as needed.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 *
 *   This does not alter main.setting.state.status.
 * @param cache
 *   A structure for containing and caching relevant data.
 *
 *   Must not be NULL.
 * @param is_normal
 *   If TRUE, then process as if this operates during a normal operation (Entry and Control).
 *   If FALSE, then process as if this operates during a an Exit operation.
 * @param type
 *   The Action type for this Action or set of actions.
 * @param method
 *   The Action method for this Action or set of actions.
 * @param item
 *   The processed item.
 *
 *   Must not be NULL.
 * @param actions
 *   The processed actions.
 *
 *   Must not be NULL.
 * @param range
 *   The current positions within the buffer being operated on.
 *   This is expected to be set to a position immediately after a valid object read.
 *
 *   Must not be NULL.
 * @param state
 *   The state information.
 *
 *   This alters state.status:
 *     F_okay on success.
 *
 *     Errors (with error bit) from: controller_rule_parameters_read().
 *     Errors (with error bit) from: f_fss_count_lines().
 *     Errors (with error bit) from: f_memory_array_increase_by().
 *
 *   Must not be NULL.
 *
 * @see controller_rule_parameters_read()
 * @see f_fss_count_lines()
 * @see f_memory_array_increase_by()
 */
#ifndef _di_controller_rule_action_read_
  extern void controller_rule_action_read(controller_t * const main, controller_cache_t * const cache, const uint8_t is_normal, const uint8_t type, const uint8_t method, controller_rule_item_t * const item, controller_rule_actions_t * const actions, f_range_t * const range, f_state_t * const state);
#endif // _di_controller_rule_action_read_

/**
 * Process a number from a Rule file, incrementing index as necessary.
 *
 * This prints error messages as necessary.
 *
 * This is intended to be called by controller_rule_action_read().
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 *
 *   This does not alter main.setting.state.status.
 * @param cache
 *   A structure for containing and caching relevant data.
 *
 *   Must not be NULL.
 * @param name
 *   The name representing the value whose number is being processed.
 * @param index
 *   The position within the content Action array for some Rule to process.
 * @param number
 *   The processed number will be saved here.
 *
 * @return
 *   F_okay on success.
 *
 *   F_valid_not (with error bit) on failure due to invalid value.
 *
 *   Errors (with error bit) from: fl_conversion_dynamic_partial_to_signed_detect().
 *
 * @see controller_rule_action_read()
 * @see fl_conversion_dynamic_partial_to_signed_detect()
 */
#ifndef _di_controller_rule_action_read_rerun_number_
  extern f_status_t controller_rule_action_read_rerun_number(controller_t * const main, controller_cache_t * const cache, const f_string_static_t name, f_number_unsigned_t * const index, f_number_unsigned_t * const number);
#endif // _di_controller_rule_action_read_rerun_number_


#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_rule_action_h
