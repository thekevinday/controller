/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print entry action error functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_entry_error_action_h
#define _controller_main_print_entry_error_action_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print an error about a Entry Item Action program or script execution failure.
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
 *   The Action cache.
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
 */
#ifndef _di_controller_print_error_entry_action_execution_failure_
  extern f_status_t controller_print_error_entry_action_execution_failure(fl_print_t * const print, controller_cache_action_t * const action, const uint8_t is_entry, const int code);
#endif // _di_controller_print_error_entry_action_execution_failure_

/**
 * Print an error about a Entry Item Action program or script not being found.
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
 *   The Action cache.
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
 */
#ifndef _di_controller_print_error_entry_action_execution_missing_
  extern f_status_t controller_print_error_entry_action_execution_missing(fl_print_t * const print, controller_cache_action_t * const action, const uint8_t is_entry, const f_string_static_t name);
#endif // _di_controller_print_error_entry_action_execution_missing_

/**
 * Print an error when an Item Action only supports a single value and the wrong value is given.
 *
 * The one in the function name represents that this only accepts a single value.
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
 *   The Action cache.
 *
 *   Must not be NULL.
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param has
 *   The invalid value that is not supported.
 * @param allow
 *   The allowed value that is supported.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_entry_action_invalid_allow_1_
  extern f_status_t controller_print_error_entry_action_invalid_allow_1(fl_print_t * const print, controller_cache_action_t * const action, const uint8_t is_entry, const f_string_static_t has, const f_string_static_t allow);
#endif // _di_controller_print_error_entry_action_invalid_allow_1_

/**
 * Print an error when an Item Action only supports specific values and the wrong value is given.
 *
 * The three in the function name represents that this only accepts one of three named values.
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
 *   The Action cache.
 *
 *   Must not be NULL.
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param has
 *   The invalid value that is not supported.
 * @param allow_1
 *   The first allowed value that is supported.
 * @param allow_2
 *   The second allowed value that is supported.
 * @param allow_3
 *   The third allowed value that is supported.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_entry_action_invalid_allow_3_
  extern f_status_t controller_print_error_entry_action_invalid_allow_3(fl_print_t * const print, controller_cache_action_t * const action, const uint8_t is_entry, const f_string_static_t has, const f_string_static_t allow_1, const f_string_static_t allow_2, const f_string_static_t allow_3);
#endif // _di_controller_print_error_entry_action_invalid_allow_3_

/**
 * Print an error when an Item Action is not a valid number.
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
 *   The Action cache.
 *
 *   Must not be NULL.
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param has
 *   The invalid value that is not supported.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_entry_action_unsupported_number_
  extern f_status_t controller_print_error_entry_action_unsupported_number(fl_print_t * const print, controller_cache_action_t * const action, const uint8_t is_entry, const f_string_static_t has);
#endif // _di_controller_print_error_entry_action_unsupported_number_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_entry_error_action_h
