/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print output Rule execute functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_output_rule_execute_h
#define _controller_main_print_output_rule_execute_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print the execute simulation.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be controller_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 *   Must not be NULL.
 * @param instance
 *   The instance performing the simulation.
 *
 *   Must not be NULL.
 * @param program
 *   (optional) The name of the program whose execution is being simulated.
 *   When disabled, arguments.array[0] will be used as the program.
 *
 *   Set program.used to 0 to disable.
 * @param arguments
 *   The array of arguments passed to the simulated program.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_entry_output_execute_simulate_
  extern f_status_t controller_print_entry_output_execute_simulate(fl_print_t * const print, controller_instance_t * const instance, const f_string_static_t program, const f_string_statics_t arguments);
#endif // _di_controller_print_entry_output_execute_simulate_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_output_rule_execute_h
