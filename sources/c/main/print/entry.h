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
 * @param cache
 *   The action cache.
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
 *
 * @see fll_error_print()
 * @see controller_print_entry_error_cache()
 */
#ifndef _di_controller_print_entry_error_
  extern f_status_t controller_print_entry_error(fl_print_t * const print, controller_cache_action_t * const cache, const uint8_t is_entry, const f_status_t status, const char * const function, const bool fallback);
#endif // _di_controller_print_entry_error_

/**
 * Print additional error/warning information in addition to existing error that is found within the cache.
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
 *
 * @see controller_entry_actions_read()
 * @see controller_entry_read()
 */
#ifndef _di_controller_print_entry_error_cache_
  extern f_status_t controller_print_entry_error_cache(fl_print_t * const print, controller_cache_action_t * const cache, const uint8_t is_entry);
#endif // _di_controller_print_entry_error_cache_

/**
 * Print the entry related file error.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be controller_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param cache
 *   The action cache.
 * @param status
 *   The status code to process.
 *   Make sure this has F_status_set_fine() called if the status code has any error or warning bits.
 * @param function
 *   (optional) The name of the function where the error happened.
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
 * @see controller_print_entry_error_cache()
 */
#ifndef _di_controller_print_entry_error_file_
  extern f_status_t controller_print_entry_error_file(fl_print_t * const print, controller_cache_action_t * const cache, const uint8_t is_entry, const f_status_t status, const char * const function, const bool fallback, const f_string_static_t name, const f_string_static_t operation, const uint8_t type);
#endif // _di_controller_print_entry_error_file_

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
 *   The action cache.
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
  extern f_status_t controller_print_entry_error_item_action_execution_failure(fl_print_t * const print, controller_cache_action_t * const cache, const uint8_t is_entry, const int code);
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
 *   The action cache.
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
  extern f_status_t controller_print_entry_error_item_action_execution_missing(fl_print_t * const print, controller_cache_action_t * const cache, const uint8_t is_entry, const f_string_static_t name);
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
 *   The action cache.
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
  extern f_status_t controller_print_entry_error_item_failure(fl_print_t * const print, controller_cache_action_t * const cache, const uint8_t is_entry, const f_string_static_t name, const f_string_static_t message);
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
 *   The action cache.
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
  extern f_status_t controller_print_entry_error_item_invalid(fl_print_t * const print, controller_cache_action_t * const cache, const uint8_t is_entry, const f_number_unsigned_t number);
#endif // _di_controller_print_entry_error_item_invalid_

/**
 * Print all parameters for some action, separated by a space.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be controller_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 *   Must not be NULL.
 * @param action
 *   The entry action whose parameters will be printed.
 *
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_entry_message_action_parameters_
  extern f_status_t controller_print_entry_message_action_parameters(fl_print_t * const print, controller_entry_action_t * const action);
#endif // _di_controller_print_entry_message_action_parameters_

/**
 * Print message about entry action state.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be controller_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 *   Must not be NULL.
 * @param action
 *   The entry action whose parameters will be printed.
 *
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_entry_message_action_state_
  extern f_status_t controller_print_entry_message_action_state(fl_print_t * const print, controller_entry_action_t * const action, const uint8_t is_entry, const f_string_static_t name);
#endif // _di_controller_print_entry_message_action_state_

/**
 * Print message about entry action state having failed.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be controller_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 *   Must not be NULL.
 * @param action
 *   The entry action whose parameters will be printed.
 *
 *   Must not be NULL.
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param name
 *   The item name.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_entry_message_action_state_failed_
  extern f_status_t controller_print_entry_message_action_state_failed(fl_print_t * const print, controller_entry_action_t * const action, const uint8_t is_entry, const f_string_static_t name) {
#ifndef _di_controller_print_entry_message_action_state_failed_

/**
 * Print message about the specified entry item action being in the ready state.
 *
 * This generally only applies to the "ready" entry item action.
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
 * @param name
 *   The item name.
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
#ifndef _di_controller_print_entry_message_item_action_ready_
  extern f_status_t controller_print_entry_message_item_action_ready(fl_print_t * const print, const uint8_t is_entry, const f_string_static_t name);
#endif // _di_controller_print_entry_message_item_action_ready_

/**
 * Print message about waiting for the specified entry item action.
 *
 * This generally only applies to the "ready" entry item action.
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
 * @param name
 *   The item name.
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
#ifndef _di_controller_print_entry_message_item_action_wait_
  extern f_status_t controller_print_entry_message_item_action_wait(fl_print_t * const print, const uint8_t is_entry, const f_string_static_t name);
#endif // _di_controller_print_entry_message_item_action_wait_

/**
 * Print message about the entry item executing.
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
 * @param parameters
 *   The array of parameters.
 *
 *   Must not be NULL.
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
#ifndef _di_controller_print_entry_message_item_executing_
  extern f_status_t controller_print_entry_message_item_executing(fl_print_t * const print, const uint8_t is_entry, f_string_dynamics_t * const parameters);
#endif // _di_controller_print_entry_message_item_executing_

/**
 * Print message about processing an item.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be controller_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param cache
 *   The action cache.
 *
 *   Must not be NULL.
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param prepend
 *   A string to prepend before entry string in the message.
 *   When prepend.used is not 0, then a space is also printed between entry string and the prepend string.
 *   Set prepend.used to 0 to disable.
 * @param name
 *   The item name.
 *   This name is printed after the "item" and after any optonal append string.
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
#ifndef _di_controller_print_entry_message_item_process_
  extern f_status_t controller_print_entry_message_item_process(fl_print_t * const print, const uint8_t is_entry, const f_string_static_t prepend, const f_string_static_t name);
#endif // _di_controller_print_entry_message_item_process_

/**
 * Print warning message about multiple actions for a specified item.
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
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param name
 *   The item name.
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
#ifndef _di_controller_print_entry_message_item_rule_
  extern f_status_t controller_print_entry_message_item_rule(fl_print_t * const print, const uint8_t is_entry, const f_string_static_t name);
#endif // _di_controller_print_entry_message_item_rule_

/**
 * Print warning the "failsafe" entry item action being specified while already in failsafe mode.
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
 *
 * @see fll_error_file_print()
 * @see controller_print_entry_error_cache()
 */
#ifndef _di_controller_print_entry_warning_item_action_failsafe_twice_
  extern f_status_t controller_print_entry_warning_item_action_failsafe_twice(fl_print_t * const print, controller_cache_action_t * const cache, const uint8_t is_entry);
#endif // _di_controller_print_entry_warning_item_action_failsafe_twice_

/**
 * Print message about the specified entry being in the given state.
 *
 * This generally only applies to the "ready" entry item action.
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
 * @param name
 *   The name of the state.
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
#ifndef _di_controller_print_entry_message_state_
  extern f_status_t controller_print_entry_message_state(fl_print_t * const print, const uint8_t is_entry, const f_string_static_t name);
#endif // _di_controller_print_entry_message_state_

/**
 * Print warning message about multiple actions for a specified item.
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
 * @param name
 *   The item name.
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
#ifndef _di_controller_print_entry_warning_item_action_multiple_
  extern f_status_t controller_print_entry_warning_item_action_multiple(fl_print_t * const print, controller_cache_action_t * const cache, const uint8_t is_entry, const f_string_static_t name);
#endif // _di_controller_print_entry_warning_item_action_multiple_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_entry_h
