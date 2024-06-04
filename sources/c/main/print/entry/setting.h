/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print entry setting functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_entry_setting_h
#define _controller_main_print_entry_setting_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print a message about an entry setting problem, with additional messages about the value.
 *
 * This is intended to be explicitly called by controller_entry_settings_read().
 * This is intended only to be used for simple messages.
 *
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param print
 *   The error or warning output structure.
 * @param before
 *   The string to add to the message being printed (before the value).
 * @param range
 *   The range within the cache item buffer representing the value.
 * @param after
 *   The string to add to the message being printed (after the value).
 * @param thread
 *   The thread data.
 * @param cache
 *   A structure for containing and caching relevant data.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see controller_entry_settings_read()
 */
#ifndef _di_controller_entry_setting_read_print_error_with_range_
  extern f_status_t controller_entry_setting_read_print_error_with_range(fl_print_t * const print, const uint8_t is_entry, const fl_print_t print, const f_string_t before, const f_string_range_t range, const f_string_t after);
#endif // _di_controller_entry_setting_read_print_error_with_range_

/**
 * Print a message for when an entry setting is being ignored.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param total
 *   The expected number of arguments.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_entry_setting_read_ignored_
  extern f_status_t controller_print_entry_setting_read_ignored(fl_print_t * const print, const uint8_t is_entry, const f_array_length_t index);
#endif // _di_controller_print_entry_setting_read_ignored_

/**
 * Print a message for when an entry setting action has the incorrect number of parameters when the required amount is between a range.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param cache
 *   A structure for containing and caching relevant data.
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
#ifndef _di_controller_print_entry_setting_read_requires_between_
  extern f_status_t controller_print_entry_setting_read_requires_between(fl_print_t * const print, const uint8_t is_entry, const f_number_unsigned_t minimum, const f_number_unsigned_t maximum);
#endif // _di_controller_print_entry_setting_read_requires_between_

/**
 * Print a message for when an entry setting action has the incorrect number of parameters when the required amount is fixed.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param total
 *   The expected number of arguments.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_entry_setting_read_requires_exactly_
  extern f_status_t controller_print_entry_setting_read_requires_exactly(fl_print_t * const print, const uint8_t is_entry, const f_number_unsigned_t total);
#endif // _di_controller_print_entry_setting_read_requires_exactly_

/**
 * Print a message for when an entry setting action is unknown.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param cache
 *   A structure for containing and caching relevant data.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_entry_setting_read_unknown_action_
  extern f_status_t controller_print_entry_setting_read_unknown_action(fl_print_t * const print, const uint8_t is_entry);
#endif // _di_controller_print_entry_setting_read_unknown_action_

/**
 * Print a message for when an entry setting action has an unknown value.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param total
 *   The expected number of arguments.
 * @param index
 *   The location in the content actions array representing the action value.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_entry_setting_read_unknown_action_value_
  extern f_status_t controller_print_entry_setting_read_unknown_action_value(fl_print_t * const print, const uint8_t is_entry, const f_array_length_t index);
#endif // _di_controller_print_entry_setting_read_unknown_action_value_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_entry_setting_h
