/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print rule item functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_rule_item_h
#define _controller_main_print_rule_item_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print rule debug message about the rule item action being empty.
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
 * @see controller_print_rule_error_cache()
 * @see controller_unlock_print_flush()
 */
#ifndef _di_controller_print_rule_item_debug_action_empty_
  extern f_status_t controller_print_rule_item_debug_action_empty(fl_print_t * const print, controller_cache_t * const cache);
#endif // _di_controller_print_rule_item_debug_action_empty_

/**
 * Print additional error/warning information in addition to existing error.
 *
 * This is explicitly intended to be used in addition to the error message.
 *
 * @param print
 *   The error or warning print structure.
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param item
 *   If TRUE, then this error is associated with an item.
 *   If FALSE, then this error is associated with a rule setting.
 * @param status
 *   The status code representing the failure (without the error bit set).
 *
 * @see controller_print_rule_error_cache()
 */
#ifndef _di_controller_print_rule_item_error_
  extern void controller_print_rule_item_error(fl_print_t * const print, const controller_cache_action_t cache, const bool item, const f_status_t status);
#endif // _di_controller_print_rule_item_error_

/**
 * Print rule error message about the first rule item action parameter being invalid.
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
 * @see controller_print_rule_error_cache()
 * @see controller_unlock_print_flush()
 */
#ifndef _di_controller_print_rule_item_error_action_first_
  extern f_status_t controller_print_rule_item_error_action_first(fl_print_t * const print, controller_cache_t * const cache);
#endif // _di_controller_print_rule_item_error_action_first_

/**
 * Print rule error message about the second rule item action parameter being invalid.
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
 * @see controller_print_rule_error_cache()
 * @see controller_unlock_print_flush()
 */
#ifndef _di_controller_print_rule_item_error_action_second_
  extern f_status_t controller_print_rule_item_error_action_second(fl_print_t * const print, controller_cache_t * const cache);
#endif // _di_controller_print_rule_item_error_action_second_

/**
 * Print rule error message about the rule item action being unknown.
 *
 * @param print
 *   The output structure to print to.
 *
 *   Must not be NULL.
 * @param cache
 *   A structure for containing and caching relevant data.
 *
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
 * @see controller_print_rule_error_cache()
 * @see controller_unlock_print_flush()
 */
#ifndef _di_controller_print_rule_item_error_action_unknown_
  extern f_status_t controller_print_rule_item_error_action_unknown(fl_print_t * const print, controller_cache_t * const cache, const f_string_static_t name, const f_number_unsigned_t index);
#endif // _di_controller_print_rule_item_error_action_unknown_

/**
 * Print an error or warning message related to the failed execution of some program or script.
 *
 * @param print
 *   The output structure to print to.
 *
 *   Must not be NULL.
 * @param instance
 *   The process instance.
 *
 *   Must not be NULL.
 * @param script_is
 *   If TRUE, then this represents a script.
 *   If FALSE, then this represents a program.
 * @param name
 *   The name of the program or script.
 * @param code
 *   The code returned by the executed program or script.
 * @param status
 *   The status code representing the failure (without the error bit set).
 */
#ifndef _di_controller_print_rule_item_error_execute_
  extern void controller_print_rule_item_error_execute(fl_print_t * const print, controller_instance_t * const instance, const bool script_is, const f_string_static_t name, const f_status_t status);
#endif // _di_controller_print_rule_item_error_execute_

/**
 * Print an error or warning message related to need/want/wish settings of some rule.
 *
 * @param print
 *   The error or warning output structure.
 * @param need_want_wish
 *   The appropriate string, such as "needs", "wants", or "wishes for" to output when describing this error/warning.
 *   This string is expected to already be "safe" (no control characters, etc..).
 * @param value
 *   The value that is the error or warning.
 * @param why
 *   A short explanation on why this is an error or warning.
 */
#ifndef _di_controller_print_rule_item_error_need_want_wish_
  extern void controller_print_rule_item_error_need_want_wish(fl_print_t * const print, const f_string_static_t need_want_wish, const f_string_static_t value, const f_string_t why);
#endif // _di_controller_print_rule_item_error_need_want_wish_

/**
 * Print an error or warning message about some rule not being loaded.
 *
 * @param print
 *   The error or warning output structure.
 * @param alias
 *   The rule alias of the rule that is not loaded.
 */
#ifndef _di_controller_print_rule_item_error_rule_not_loaded_
  extern void controller_print_rule_item_error_rule_not_loaded(fl_print_t * const print, const f_string_static_t alias);
#endif // _di_controller_print_rule_item_error_rule_not_loaded_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_rule_item_h
