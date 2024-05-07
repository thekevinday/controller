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
 * Print rule debug message about the rule item action being empty.
 *
 * @param print
 *   The output structure to print to.
 *   Must not be NULL.
 * @param cache
 *   A structure for containing and caching relevant data.
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
 * @see controller_rule_print_rule_message_cache()
 * @see controller_unlock_print_flush()
 */
#ifndef _di_controller_main_print_rule_debug_item_action_empty_
  extern f_status_t controller_main_print_rule_debug_item_action_empty(fl_print_t * const print, controller_cache_t * const cache);
#endif // _di_controller_main_print_rule_debug_item_action_empty_

/**
 * Print rule error message about the first rule item action parameter being invalid.
 *
 * @param print
 *   The output structure to print to.
 *   Must not be NULL.
 * @param cache
 *   A structure for containing and caching relevant data.
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
 * @see controller_rule_print_rule_message_cache()
 * @see controller_unlock_print_flush()
 */
#ifndef _di_controller_main_print_rule_error_item_action_first_
  extern f_status_t controller_main_print_rule_error_item_action_first(fl_print_t * const print, controller_cache_t * const cache);
#endif // _di_controller_main_print_rule_error_item_action_first_

/**
 * Print rule error message about the second rule item action parameter being invalid.
 *
 * @param print
 *   The output structure to print to.
 *   Must not be NULL.
 * @param cache
 *   A structure for containing and caching relevant data.
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
 * @see controller_rule_print_rule_message_cache()
 * @see controller_unlock_print_flush()
 */
#ifndef _di_controller_main_print_rule_error_item_action_second_
  extern f_status_t controller_main_print_rule_error_item_action_second(fl_print_t * const print, controller_cache_t * const cache);
#endif // _di_controller_main_print_rule_error_item_action_second_

/**
 * Print rule error message about the rule item action being unknown.
 *
 * @param print
 *   The output structure to print to.
 *   Must not be NULL.
 * @param cache
 *   A structure for containing and caching relevant data.
 *   Must not be NULL.
 * @param name
 *   The parameter name whose value is unknown.
 * @param index
 *   The index in the content action cache representing the unknown value.
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
 * @see controller_rule_print_rule_message_cache()
 * @see controller_unlock_print_flush()
 */
#ifndef _di_controller_main_print_rule_error_item_action_unknown_
  extern f_status_t controller_main_print_rule_error_item_action_unknown(fl_print_t * const print, controller_cache_t * const cache, const f_string_static_t name, const f_number_unsigned_t index);
#endif // _di_controller_main_print_rule_error_item_action_unknown_

/**
 * Print rule error message about the rule item action being unknown.
 *
 * @param print
 *   The output structure to print to.
 *   Must not be NULL.
 *
 *   This does not lock the stream.
 * @param cache
 *   A structure for containing and caching relevant data.
 *   Must not be NULL.
 * @param name
 *   The parameter name related to the message.
 * @param index
 *   The index in the content action cache representing the parameter value related to the message.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fl_print_format()
 */
#ifndef _di_controller_rule_print_rule_message_cache_
  extern f_status_t controller_rule_print_rule_message_cache(fl_print_t * const print, controller_cache_action_t * const cache, const bool item);
#endif // _di_controller_rule_print_rule_message_cache_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_rule_h
