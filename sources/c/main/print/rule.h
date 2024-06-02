/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print rule functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_rule_h
#define _controller_main_print_rule_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print generic error/warning information.
 *
 * This is essentially a wrapper to fll_error_print() that includes locking.
 *
 * @param print
 *   Designates how printing is to be performed.
 * @param cache
 *   The action cache.
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
 * @see fll_error_print()
 * @see controller_print_rule_error_cache()
 */
#ifndef _di_controller_print_rule_error_
  extern f_status_t controller_print_rule_error(fl_print_t * const print, const controller_cache_action_t cache, const f_status_t status, const f_string_t function, const bool fallback, const bool item);
#endif // _di_controller_print_rule_error_

/**
 * Print additional error/warning information in addition to existing error.
 *
 * This is explicitly intended to be used in addition to the error message.
 *
 * This neither locks the thread nor does it check to see if output is enabled or disabled.
 *
 * @param print
 *   The error or warning output structure.
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param item
 *   If TRUE, then this error is associated with an item.
 *   If FALSE, then this error is associated with a rule setting.
 *
 * @see controller_rule_action_read()
 * @see controller_rule_item_read()
 * @see controller_rule_items_read()
 * @see controller_rule_read()
 * @see controller_rule_setting_read()
 */
#ifndef _di_controller_print_rule_error_cache_
  extern f_status_t controller_print_rule_error_cache(fl_print_t * const print, const controller_cache_action_t cache, const bool item);
#endif // _di_controller_print_rule_error_cache_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_rule_h
