/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print entry error functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_entry_error_h
#define _controller_main_print_entry_error_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print the entry related error.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be controller_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 *   Must not be NULL.
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param status
 *   The status code to process.
 *   Make sure this has F_status_set_fine() called if the status code has any error or warning bits.
 * @param function
 *   (optional) The name of the function where the error happened.
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
 */
#ifndef _di_controller_print_error_entry_
  extern f_status_t controller_print_error_entry(fl_print_t * const print, const uint8_t is_entry, const f_status_t status, const char * const function, const bool fallback);
#endif // _di_controller_print_error_entry_

/**
 * Print additional error/warning information in addition to existing error that is found within the given action cache.
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
 *   The action cache.
 *
 *   Must not be NULL.
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_entry_cache_
  extern f_status_t controller_print_error_entry_cache(fl_print_t * const print, controller_cache_action_t * const cache, const uint8_t is_entry);
#endif // _di_controller_print_error_entry_cache_

/**
 * Print the entry related file error.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be controller_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 *   Must not be NULL.
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param status
 *   The status code to process.
 *   Make sure this has F_status_set_fine() called if the status code has any error or warning bits.
 * @param function
 *   (optional) The name of the function where the error happened.
 *   Set to 0 to disable.
 * @param fallback
 *   If TRUE, then print the fallback error message for unknown errors.
 *   If FALSE, then do not print the fallback error message.
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
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_entry_file_
  extern f_status_t controller_print_error_entry_file(fl_print_t * const print, const uint8_t is_entry, const f_status_t status, const char * const function, const uint8_t fallback, const f_string_static_t name, const f_string_static_t operation, const uint8_t type);
#endif // _di_controller_print_error_entry_file_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_entry_error_h
