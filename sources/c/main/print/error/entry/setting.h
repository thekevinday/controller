/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print entry error setting functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_entry_error_setting_h
#define _controller_main_print_entry_error_setting_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print a message about an entry setting problem, with additional messages about the value.
 *
 * This is intended to be explicitly called by controller_entry_settings_read().
 * This is intended only to be used for simple messages.
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
 * @param before
 *   The string to add to the message being printed (before the value).
 * @param range
 *   The range within the cache item buffer representing the value.
 * @param after
 *   The string to add to the message being printed (after the value).
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see controller_entry_settings_read()
 */
#ifndef _di_controller_print_error_entry_setting_with_range_
  extern f_status_t controller_print_error_entry_setting_with_range(fl_print_t * const print, controller_cache_t * const cache, const uint8_t is_entry, const f_string_t before, const f_range_t range, const f_string_t after);
#endif // _di_controller_print_error_entry_setting_with_range_

/**
 * Print a message for when an entry setting is being ignored.
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
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_entry_setting_ignored_
  extern f_status_t controller_print_error_entry_setting_ignored(fl_print_t * const print, controller_cache_t * const cache, const uint8_t is_entry);
#endif // _di_controller_print_error_entry_setting_ignored_

/**
 * Print a message for when an entry setting action has the incorrect number of parameters when the required amount is between a range.
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
 * @param minimum
 *   The expected minimum number of arguments.
 * @param maximum
 *   The expected maximum number of arguments.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_entry_setting_requires_between_
  extern f_status_t controller_print_error_entry_setting_requires_between(fl_print_t * const print, controller_cache_t * const cache, const uint8_t is_entry, const f_number_unsigned_t minimum, const f_number_unsigned_t maximum);
#endif // _di_controller_print_error_entry_setting_requires_between_

/**
 * Print a message for when an entry setting action has the incorrect number of parameters when the required amount is fixed.
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
 * @param total
 *   The expected number of arguments.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_entry_setting_requires_exactly_
  extern f_status_t controller_print_error_entry_setting_requires_exactly(fl_print_t * const print, controller_cache_t * const cache, const uint8_t is_entry, const f_number_unsigned_t total);
#endif // _di_controller_print_error_entry_setting_requires_exactly_

/**
 * Print an error message about an entry setting value not being a supported number.
 *
 * This utilizes the buffer and range because the number is not supported and therefore the string cannot be converted to a number.
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
 * @param buffer
 *   The buffer containing the settings.
 * @param range
 *   The range within the buffer representing the unsupported number.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_file_print()
 * @see controller_print_error_entry_cache()
 */
#ifndef _di_controller_print_error_entry_setting_support_not_number_
  extern f_status_t controller_print_error_entry_setting_support_not_number(fl_print_t * const print, const uint8_t is_entry, const f_string_static_t buffer, const f_range_t range);
#endif // _di_controller_print_error_entry_setting_support_not_number_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_entry_error_setting_h
