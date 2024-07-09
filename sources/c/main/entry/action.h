/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the Entry Action functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_entry_action_h
#define _controller_main_entry_action_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Read the Entry list, loading all Items and values.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 * @param entry
 *   The Entry.
 *
 *   Must not be NULL.
 * @param range
 *   The range in the list buffer representing the content.
 * @param actions
 *   The processed actions.
 *
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: controller_entry_actions_increase_by().
 *   Errors (with error bit) from: f_fss_apply_delimit().
 *   Errors (with error bit) from: f_fss_count_lines().
 *   Errors (with error bit) from: f_memory_array_increase_by().
 *   Errors (with error bit) from: f_rip_dynamic_partial_nulless().
 *   Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *   Errors (with error bit) from: fll_fss_extended_read().
 *
 * @see controller_entry_actions_increase_by()
 * @see f_fss_apply_delimit()
 * @see f_fss_count_lines()
 * @see f_memory_array_increase_by()
 * @see f_rip_dynamic_partial_nulless()
 * @see f_string_dynamic_partial_append_nulless()
 * @see fll_fss_extended_read()
 */
#ifndef _di_controller_entry_action_read_
  extern f_status_t controller_entry_action_read(controller_t * const main, controller_entry_t * const entry, const f_range_t range, controller_entry_actions_t * const actions);
#endif // _di_controller_entry_action_read_

/**
 * Determine if the Entry Action type code represents a Rule type.
 *
 * @param type
 *   The type code to compare against.
 *
 * @return
 *    TRUE if Rule type.
 *    FALSE otherwise.
 */
#ifndef _di_controller_entry_action_type_is_rule_
  extern f_status_t controller_entry_action_type_is_rule(uint8_t type);
#endif // _di_controller_entry_action_type_is_rule_

/**
 * Get a string representing the Entry Action type.
 *
 * @param type
 *   The Entry Action type code.
 *
 * @return
 *   The string with used > 0 on success.
 *   The string with used == 0 if no match was found.
 */
#ifndef _di_controller_entry_action_type_name_
  extern f_string_static_t controller_entry_action_type_name(const uint8_t type);
#endif // _di_controller_entry_action_type_name_

/**
 * Convert the Entry Action type to Rule Action type.
 *
 * @param type
 *   The Entry Action type.
 *
 * @return
 *    TRUE if Rule type.
 *    FALSE otherwise.
 */
#ifndef _di_controller_entry_action_type_to_rule_action_type_
  extern uint8_t controller_entry_action_type_to_rule_action_type(uint8_t type);
#endif // _di_controller_entry_action_type_to_rule_action_type_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_entry_action_h
