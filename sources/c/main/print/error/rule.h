/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print rule error functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_rule_error_h
#define _controller_main_print_rule_error_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print generic error/warning information.
 *
 * This is essentially a wrapper to fll_error_print() that includes locking.
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
 * @param status
 *   The status code to process.
 *   Make sure this has F_status_set_fine() called if the status code has any error or warning bits.
 * @param function
 *   The name of the function where the error happened.
 *   Set to 0 to disable.
 * @param fallback
 *   Set to F_true to print the fallback error message for unknown errors.
 * @param item
 *   If TRUE, then this error is associated with an item.
 *   If FALSE, then this error is associated with a rule setting.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_print()
 * @see controller_print_error_rule_cache()
 */
#ifndef _di_controller_print_error_rule_
  extern f_status_t controller_print_error_rule(fl_print_t * const print, controller_cache_action_t * const cache, const f_status_t status, const f_string_t function, const uint8_t fallback, const uint8_t item);
#endif // _di_controller_print_error_rule_

/**
 * Print additional error/warning information in addition to existing error.
 *
 * This is explicitly intended to be used in addition to the error message.
 *
 * This neither locks the thread nor does it check to see if output is enabled or disabled.
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
 * @param item
 *   If TRUE, then this error is associated with an item.
 *   If FALSE, then this error is associated with a rule setting.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_print()
 * @see controller_print_error_entry_cache()
 */
#ifndef _di_controller_print_error_rule_cache_
  extern f_status_t controller_print_error_rule_cache(fl_print_t * const print, controller_cache_action_t * const cache, const uint8_t item);
#endif // _di_controller_print_error_rule_cache_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_rule_error_h
