/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the rule "read" functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_rule_read_h
#define _controller_main_rule_read_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Read the parameters for some rule action.
 *
 * The object and content ranges are merged together (in that order) as the action parameters.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 *
 *   This does not alter main.setting.state.status.
 * @param buffer
 *   The buffer containing the content.
 * @param object
 *   (optional) The range representing where the object is found within the buffer.
 *   Set pointer address to 0 to disable.
 * @param content
 *   (optional) The ranges representing where the content is found within the buffer.
 *   Set pointer address to 0 to disable.
 * @param action
 *   The rule action.
 * @param state
 *   The state data for passing to fl_iki_read().
 *
 * @return
 *   F_okay on success.
 *
 *   Errors (with error bit) from: f_fss_count_lines().
 *   Errors (with error bit) from: f_memory_array_increase().
 *   Errors (with error bit) from: f_memory_array_increase_by().
 *   Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *   Errors (with error bit) from: f_memory_array_increase().
 *   Errors (with error bit) from: fl_iki_read().
 *
 * @see f_fss_count_lines()
 * @see f_memory_array_increase()
 * @see f_memory_array_increase_by()
 * @see f_string_dynamic_partial_append_nulless()
 * @see f_memory_array_increase()
 * @see f_memory_array_increase_by()
 * @see fl_iki_read()
 */
#ifndef _di_controller_rule_parameters_read_
  extern f_status_t controller_rule_parameters_read(controller_t * const main, const f_string_static_t buffer, f_range_t * const object, f_ranges_t * const content, controller_rule_action_t * const action, f_state_t * const state);
#endif // _di_controller_rule_parameters_read_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_rule_read_h
