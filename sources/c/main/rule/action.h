/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the rule "action" functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_rule_action_h
#define _controller_main_rule_action_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Get a string representing the rule action method.
 *
 * @param type
 *   The rule action type code.
 *
 * @return
 *   The string with used > 0 on success.
 *   The string with used == 0 if no match was found.
 */
#ifndef _di_controller_main_rule_action_method_name_
  extern f_string_static_t controller_main_rule_action_method_name(const uint8_t type);
#endif // _di_controller_main_rule_action_method_name_

/**
 * Convert the action type to an action execute type.
 *
 * @param type
 *   The action type to convert from.
 *
 * @return
 *   The converted action type, converted into an action execute type.
 *
 *   The code controller_main_rule_action_execute_type__enum_size_e is returned for unknown types.
 */
#ifndef _di_controller_main_rule_action_type_to_action_execute_type_
  extern uint8_t controller_main_rule_action_type_to_action_execute_type(const uint8_t type);
#endif // _di_controller_main_rule_action_type_to_action_execute_type_

/**
 * Read the content within the buffer, processing the action (or a set of within a list) for the given item.
 *
 * This will automatically increase the size of the actions array as needed.
 *
 * @param global
 *   The global data.
 *
 *   Must not be NULL.
 *
 *   This does not alter global.main.setting.state.status.
 * @param is_normal
 *   If TRUE, then process as if this operates during a normal operation (entry and control).
 *   If FALSE, then process as if this operates during a an exit operation.
 * @param type
 *   The action type for this action or set of actions.
 * @param method
 *   The action method for this action or set of actions.
 * @param cache
 *   A structure for containing and caching relevant data.
 *
 *   Must not be NULL.
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
 *
 * @return
 *   F_okay on success.
 *
 *   Errors (with error bit) from: controller_main_rule_parameters_read().
 *   Errors (with error bit) from: f_fss_count_lines().
 *   Errors (with error bit) from: f_memory_array_increase_by().
 *
 * @see controller_main_rule_parameters_read()
 * @see f_fss_count_lines()
 * @see f_memory_array_increase_by()
 */
#ifndef _di_controller_main_rule_action_read_
  extern f_status_t controller_main_rule_action_read(controller_global_t * const global, const bool is_normal, const uint8_t type, const uint8_t method, controller_cache_t * const cache, controller_rule_item_t * const item, controller_main_rule_actions_t * const actions, f_range_t * const range);
#endif // _di_controller_main_rule_action_read_

/**
 * Process a number from a rule file, incrementing index as necessary.
 *
 * This prints error messages as necessary.
 *
 * This is intended to be called by controller_main_rule_action_read().
 *
 * @param global
 *   The global data.
 *
 *   Must not be NULL.
 *
 *   This does not alter global.main.setting.state.status.
 * @param name
 *   The name representing the value whose number is being processed.
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param index
 *   The position within the content action array for some rule to process.
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
 * @see controller_main_rule_action_read()
 * @see fl_conversion_dynamic_partial_to_signed_detect()
 */
#ifndef _di_controller_main_rule_action_read_rerun_number_
  extern f_status_t controller_main_rule_action_read_rerun_number(controller_global_t * const global, const f_string_t name, controller_cache_t * const cache, f_number_unsigned_t * const index, f_number_unsigned_t * const number);
#endif // _di_controller_main_rule_action_read_rerun_number_


#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_rule_action_h
