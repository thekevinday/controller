/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the rule "validate" functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_rule_validate_h
#define _controller_main_rule_validate_h

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
 * @param global
 *   The global data.
 *   Must not be NULL.
 *
 *   This does not alter global.main.setting.state.status.
 * @param rule
 *   The rule to process.
 * @param action
 *   The action to perform based on the action type codes.
 * @param options
 *   A number using bits to represent specific boolean options.
 *   If no bits set, then operate normally in a synchronous manner.
 *   If bit controller_process_option_simulate_d, then the rule execution is in simulation mode (printing a message that the rule would be executed but does not execute the rule).
 *   If bit controller_process_option_asynchronous_d, then run asynchronously.
 * @param cache
 *   A structure for containing and caching relevant data.
 */
#ifndef _di_controller_rule_validate_
  extern void controller_rule_validate(controller_global_t * const global, const controller_rule_t rule, const uint8_t action, const uint8_t options, controller_cache_t * const cache);
#endif // _di_controller_rule_validate_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_rule_validate_h
