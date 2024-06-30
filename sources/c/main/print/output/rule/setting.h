/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print rule setting output functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_output_rule_setting_h
#define _controller_main_print_output_rule_setting_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print message about processing a Rule Item Action adding with the three Content ranges in the buffer.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be controller_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 *   Must not be NULL.
 * @param name
 *   The Rule Item Action name.
 * @param buffer
 *   A bufer containing the values.
 * @param range_1
 *   A range within the buffer representing value one.
 * @param range_2
 *   A range within the buffer representing value two.
 * @param range_3
 *   A range within the buffer representing value three.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_output_rule_execute_setting_simulate_adding_range_3_
  extern f_status_t controller_print_output_rule_execute_setting_simulate_adding_range_3(fl_print_t * const print, const f_string_static_t name, const f_string_static_t buffer, const f_range_t range_1, const f_range_t range_2, const f_range_t range_3);
#endif // _di_controller_print_output_rule_execute_setting_simulate_adding_range_3_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_output_rule_setting_h
