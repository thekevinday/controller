/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the Rule "is" functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_rule_is_h
#define _controller_main_rule_is_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Check to see if the given Rule has status F_known_not for the given Rule Action.
 *
 * The Rule status is checked for error and any errors on the Rule status will result in F_false.
 *
 * @param action
 *   The Rule Action type.
 * @param rule
 *   The Rule.
 *
 * @return
 *   F_true on available (status is F_known_not).
 *   F_false on unavailable.
 */
#ifndef _di_controller_rule_status_is_available_
  extern f_status_t controller_rule_status_is_available(const uint8_t action, const controller_rule_t rule);
#endif // _di_controller_rule_status_is_available_

/**
 * Check to see if the given Rule has status is designated as an error for the given Rule Action.
 *
 * The Rule status is checked for error and any errors on the Rule status will result in F_true.
 *
 * @param action
 *   The Rule Action type.
 * @param rule
 *   The Rule.
 *
 * @return
 *   F_true if status represents an error.
 *   F_false if status does not represent an error.
 */
#ifndef _di_controller_rule_status_is_error_
  extern f_status_t controller_rule_status_is_error(const uint8_t action, const controller_rule_t rule);
#endif // _di_controller_rule_status_is_error_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_rule_is_h
