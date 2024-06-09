/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print debug entry action functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_debug_entry_action_h
#define _controller_main_print_debug_entry_action_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print debug message about the rule item action being empty.
 *
 * @param print
 *   The output structure to print to.
 *
 *   Must not be NULL.
 * @param cache
 *   A structure for containing and caching relevant data.
 *
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fl_print_format()
 * @see fll_error_print()
 *
 * @see controller_lock_print()
 * @see controller_print_error_rule_cache()
 * @see controller_unlock_print_flush()
 */
#ifndef _di_controller_print_debug_rule_action_empty_
  extern f_status_t controller_print_debug_rule_action_empty(fl_print_t * const print, controller_cache_t * const cache);
#endif // _di_controller_print_debug_rule_action_empty_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_debug_entry_action_h
