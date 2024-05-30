/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print error functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_error_h
#define _controller_main_print_error_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print generic error message regarding a function failing in some way.
 *
 * @param print
 *   The output structure to print to.
 *   Must not be NULL.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param function
 *   The name of the function associated with the error.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_print()
 */
#ifndef _di_controller_main_print_error_
  extern f_status_t controller_main_print_error(fl_print_t * const print, const f_string_t function);
#endif // _di_controller_main_print_error_

/**
 * Print file related error or warning messages.
 *
 * @param print
 *   The output structure to print to.
 *   Must not be NULL.
 *
 *   The print.custom is expected to be of type fss_read_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param function
 *   The name of the function where the error happened.
 *   Set to 0 to disable.
 * @param name
 *   The name of the file or directory.
 * @param operation
 *   The operation that fails, such as 'create' or 'access'.
 * @param type
 *   A valid file type code from the fll_error_file_type enum.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if a parameter is NULL.
 *
 * @see fll_error_file_print()
 */
#ifndef _di_controller_main_print_error_file_
  extern f_status_t controller_main_print_error_file(fl_print_t * const print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type);
#endif // _di_controller_main_print_error_file_

/**
 * Print file related error or warning messages.
 *
 * @param print
 *   The output structure to print to.
 *   Must not be NULL.
 *
 *   The print.custom is expected to be of type fss_read_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param function
 *   The name of the function where the error happened.
 *   Set to 0 to disable.
 * @param name
 *   The name of the file or directory.
 * @param operation
 *   The operation that fails, such as 'create' or 'access'.
 * @param type
 *   A valid file type code from the fll_error_file_type enum.
 * @param status
 *   The status code to print an error message about.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if a parameter is NULL.
 *
 * @see fll_error_file_print()
 */
#ifndef _di_controller_main_print_error_file_status_
  extern f_status_t controller_main_print_error_file_status(fl_print_t * const print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type, const f_status_t status);
#endif // _di_controller_main_print_error_file_status_

/**
 * Print generic error message regarding a function failing in some way.
 *
 * @param print
 *   The output structure to print to.
 *   Must not be NULL.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param function
 *   The name of the function associated with the error.
 * @param status
 *   The status code to print an error message about.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_print()
 */
#ifndef _di_controller_main_print_error_status_
  extern f_status_t controller_main_print_error_status(fl_print_t * const print, const f_string_t function, const f_status_t status);
#endif // _di_controller_main_print_error_status_

/**
 * Print generic error/warning information.
 *
 * This is essentially a wrapper to fll_error_print() that includes locking.
 *
 * @param thread
 *   The thread data.
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
 * @see controller_rule_print_error_cache()
 */
#ifndef _di_controller_rule_print_error_
  extern void controller_rule_print_error(controller_thread_t * const thread, fl_print_t * const print, const controller_cache_action_t cache, const f_status_t status, const f_string_t function, const bool fallback, const bool item) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_print_error_

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
#ifndef _di_controller_rule_print_error_cache_
  extern void controller_rule_print_error_cache(fl_print_t * const print, const controller_cache_action_t cache, const bool item) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_print_error_cache_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_error_h
