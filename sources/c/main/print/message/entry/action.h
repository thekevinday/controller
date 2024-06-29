/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print entry action message functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_entry_message_action_h
#define _controller_main_print_entry_message_action_h

#ifdef __cplusplus
extern "C" {
#endif

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
 *   The entry action.
 *
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_message_entry_action_parameters_
  extern f_status_t controller_print_message_entry_action_parameters(fl_print_t * const print, controller_entry_action_t * const action);
#endif // _di_controller_print_message_entry_action_parameters_

/**
 * Print message about the specified Entry Item Action being in the ready state.
 *
 * This generally only applies to the "ready" Entry Item Action.
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
 */
#ifndef _di_controller_print_message_entry_action_ready_
  extern f_status_t controller_print_message_entry_action_ready(fl_print_t * const print, const uint8_t is_entry, const f_string_static_t name);
#endif // _di_controller_print_message_entry_action_ready_

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
 * @param cache
 *   The cache.
 *
 *   Must not be NULL.
 * @param action
 *   The entry action.
 *
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_message_entry_action_state_
  extern f_status_t controller_print_message_entry_action_state(fl_print_t * const print, controller_cache_t * const cache, controller_entry_action_t * const action, const uint8_t is_entry);
#endif // _di_controller_print_message_entry_action_state_

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
 * @param cache
 *   The cache.
 *
 *   Must not be NULL.
 * @param action
 *   The entry action.
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
#ifndef _di_controller_print_message_entry_action_state_failed_
  extern f_status_t controller_print_message_entry_action_state_failed(fl_print_t * const print, controller_cache_t * const cache, controller_entry_action_t * const action, const uint8_t is_entry);
#endif // _di_controller_print_message_entry_action_state_failed_

/**
 * Print message about waiting for the specified Entry Item Action.
 *
 * This generally only applies to the "ready" Entry Item Action.
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
 */
#ifndef _di_controller_print_message_entry_action_wait_
  extern f_status_t controller_print_message_entry_action_wait(fl_print_t * const print, const uint8_t is_entry, const f_string_static_t name);
#endif // _di_controller_print_message_entry_action_wait_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_entry_message_action_h
