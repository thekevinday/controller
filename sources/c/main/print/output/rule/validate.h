/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print output rule "validate" functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_output_rule_validate_h
#define _controller_main_print_output_rule_validate_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform a simulated execution of the given rule.
 *
 * This simply prints information about the rule.
 *
 * This automatically sets the rule's status to F_complete.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be controller_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 *   Must not be NULL.
 * @param cache
 *   The cache.
 *
 *   Must not be NULL.
 * @param rule
 *   The rule to process.
 *
 *   Must not be NULL.
 * @param action
 *   The action to perform based on the action type codes.
 * @param options
 *   A number using bits to represent specific boolean options.
 *   If no bits set, then operate normally in a synchronous manner.
 *   If bit controller_instance_option_simulate_e, then the rule execution is in simulation mode (printing a message that the rule would be executed but does not execute the rule).
 *   If bit controller_instance_option_asynchronous_e, then run asynchronously.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_output_rule_validate_
  extern f_status_t controller_output_rule_validate(fl_print_t * const print, controller_cache_t * const cache, controller_rule_t * const rule, const uint8_t action, const uint8_t options);
#endif // _di_controller_output_rule_validate_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_output_rule_validate_h
