/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print rule setting functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_rule_setting_h
#define _controller_main_print_rule_setting_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print a message about a rule setting problem.
 *
 * This is intended to be explicitly called by controller_rule_setting_read().
 * This is intended only to be used for simple messages.
 *
 * @param print
 *   The error or warning output structure.
 * @param message
 *   The string to append to the message being printed.
 * @param index
 *   The position in the object actions cache representing the object.
 * @param line_item
 *   The current line number.
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
 * @see controller_rule_setting_read()
 */
#ifndef _di_controller_print_rule_setting_read_error_
  extern f_status_t controller_print_rule_setting_read_error(fl_print_t * const print, controller_thread_t * const thread, controller_cache_t * const cache, const f_string_t message, const f_number_unsigned_t index, const f_number_unsigned_t line_item);
#endif // _di_controller_print_rule_setting_read_error_

/**
 * Print a message about a rule setting problem, with additional messages about the value.
 *
 * This is intended to be explicitly called by controller_rule_setting_read().
 * This is intended only to be used for simple messages.
 *
 * @param print
 *   The error or warning output structure.
 * @param before
 *   The string to add to the message being printed (before the value).
 * @param range
 *   The range within the cache item buffer representing the value.
 * @param after
 *   The string to add to the message being printed (after the value).
 * @param index
 *   The position in the object actions cache representing the object.
 * @param line_item
 *   The current line number.
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
 * @see controller_rule_setting_read()
 */
#ifndef _di_controller_print_rule_setting_read_error_with_range_
  extern f_status_t controller_print_rule_setting_read_error_with_range(fl_print_t * const print, controller_thread_t * const thread, controller_cache_t * const cache, const f_string_t before, const f_range_t range, const f_string_t after, const f_number_unsigned_t index, const f_number_unsigned_t line_item);
#endif // _di_controller_print_rule_setting_read_error_with_range_

/**
 * Print message regarding the mapping of a setting when in simulation or verbose mode.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 * @param name
 *   The Object name of the setting being populated.
 * @param map
 *   The map being applied.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_rule_setting_read_mapping_
  extern f_status_t controller_print_rule_setting_read_mapping(controller_t * const main, const f_string_static_t name, const f_string_map_t map);
#endif // _di_controller_print_rule_setting_read_mapping_

/**
 * Print message regarding the population of a setting when in simulation or verbose mode.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 * @param name
 *   The Object name of the setting being populated.
 * @param name_sub
 *   A sub-name associated with the setting being populated.
 *   Set to a string with used set to 0 to not use.
 * @param value
 *   The value being set.
 * @param suffix
 *   An additional message to append at the end (before the final period).
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_rule_setting_read_value_
  extern f_status_t controller_print_rule_setting_read_value(controller_t * const main, const f_string_static_t name, const f_string_static_t name_sub, const f_string_static_t value, const f_string_t suffix);
#endif // _di_controller_print_rule_setting_read_value_

/**
 * Print message regarding the population of a setting when in simulation or verbose mode.
 *
 * This handles the case where there are multiple values stored in the buffer_item at a given content_actions position.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 * @param name
 *   The Object name of the setting being populated.
 * @param index
 *   Position within the content_actions range cache array.
 * @param cache
 *   A structure for containing and caching relevant data.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_rule_setting_read_values_
  extern f_status_t controller_print_rule_setting_read_values(controller_t * const main, controller_cache_t * const cache, const f_string_static_t name, const f_number_unsigned_t index);
#endif // _di_controller_print_rule_setting_read_values_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_rule_setting_h
