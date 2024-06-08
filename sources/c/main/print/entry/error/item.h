/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print entry error item functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_entry_error_item_h
#define _controller_main_print_entry_error_item_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print an error about a entry item action program or script execution failure.
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
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param code
 *   The return code.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_file_print()
 * @see controller_print_entry_error_cache()
 */
#ifndef _di_controller_print_entry_error_item_action_execution_failure_
  extern f_status_t controller_print_entry_error_item_action_execution_failure(fl_print_t * const print, controller_cache_t * const cache, const uint8_t is_entry, const int code);
#endif // _di_controller_print_entry_error_item_action_execution_failure_

/**
 * Print an error about a entry item action program or script not being found.
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
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param name
 *   The program or script name.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_file_print()
 * @see controller_print_entry_error_cache()
 */
#ifndef _di_controller_print_entry_error_item_action_execution_missing_
  extern f_status_t controller_print_entry_error_item_action_execution_missing(fl_print_t * const print, controller_cache_t * const cache, const uint8_t is_entry, const f_string_static_t name);
#endif // _di_controller_print_entry_error_item_action_execution_missing_

/**
 * Print the entry item related error.
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
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param name
 *   The item name.
 * @param message
 *   A short message describing the reason for the failure.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_file_print()
 * @see controller_print_entry_error_cache()
 */
#ifndef _di_controller_print_entry_error_item_failure_
  extern f_status_t controller_print_entry_error_item_failure(fl_print_t * const print, controller_cache_t * const cache, const uint8_t is_entry, const f_string_static_t name, const f_string_static_t message);
#endif // _di_controller_print_entry_error_item_failure_

/**
 * Print an error message for an invalid entry item.
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
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param number
 *   The index position of the invalid item.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_file_print()
 * @see controller_print_entry_error_cache()
 */
#ifndef _di_controller_print_entry_error_item_invalid_
  extern f_status_t controller_print_entry_error_item_invalid(fl_print_t * const print, controller_cache_t * const cache, const uint8_t is_entry, const f_number_unsigned_t number);
#endif // _di_controller_print_entry_error_item_invalid_

/**
 * Print an error message about an entry it setting option not being supported.
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
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param setting
 *   The setting name.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_file_print()
 * @see controller_print_entry_error_cache()
 */
#ifndef _di_controller_print_entry_error_item_setting_support_not_option_
  extern f_status_t controller_print_entry_error_item_setting_support_not_option(fl_print_t * const print, controller_cache_t * const cache, const uint8_t is_entry, const f_string_static_t setting);
#endif // _di_controller_print_entry_error_item_setting_support_not_option_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_entry_error_item_h
