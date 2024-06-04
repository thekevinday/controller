/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print entry functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_entry_h
#define _controller_main_print_entry_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print all parameters for some action, separated by a space.
 *
 * @param stream
 *   The file stream to print to.
 * @param action
 *   The entry action whose parameters will be printed.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_entry_action_parameters_print_
  extern f_status_t controller_entry_action_parameters_print(fl_print_t * const print, controller_entry_action_t * const action);
#endif // _di_controller_entry_action_parameters_print_

/**
 * Print the entry related error, locking the print mutex during the print.
 *
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
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
 * @param thread
 *   The thread data.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_print()
 * @see controller_entry_print_error_cache()
 */
#ifndef _di_controller_entry_print_error_
  extern f_status_t controller_entry_print_error(fl_print_t * const print, controller_cache_action_t * const cache, const uint8_t is_entry, const f_status_t status, const char *function, const bool fallback);
#endif // _di_controller_entry_print_error_

/**
 * Print additional error/warning information in addition to existing error that is found within the cache.
 *
 * This is explicitly intended to be used in addition to the error message.
 *
 * This neither locks the thread nor does it check to see if output is enabled or disabled.
 *
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param output
 *   Designates how printing is to be performed.
 * @param cache
 *   The action cache.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see controller_entry_actions_read()
 * @see controller_entry_read()
 */
#ifndef _di_controller_entry_print_error_cache_
  extern f_status_t controller_entry_print_error_cache(fl_print_t * const print, controller_cache_action_t * const cache, const uint8_t is_entry);
#endif // _di_controller_entry_print_error_cache_

/**
 * Print the entry related file error, locking the print mutex during the print.
 *
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
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
 * @param name
 *   The name of the file or directory.
 * @param operation
 *   The operation that fails, such as 'create' or 'access'.
 * @param type
 *   A valid file type code from the fll_error_file_type enum.
 * @param thread
 *   The thread data.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_file_print()
 * @see controller_entry_print_error_cache()
 */
#ifndef _di_controller_entry_print_error_file_
  extern f_status_t controller_entry_print_error_file(fl_print_t * const print, controller_cache_action_t * const cache, const uint8_t is_entry, const f_status_t status, const char *function, const bool fallback, const f_string_static_t name, const f_string_static_t operation, const uint8_t type);
#endif // _di_controller_entry_print_error_file_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_entry_h
