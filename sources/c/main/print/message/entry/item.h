/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print entry message item functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_entry_message_item_h
#define _controller_main_print_entry_message_item_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print message about processing an item.
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
 * @param failsafe
 *   If TRUE, then running in failsafe.
 *   If FALSE, then running normally.
 * @param name
 *   The item name.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_message_entry_item_done_
  extern f_status_t controller_print_message_entry_item_done(fl_print_t * const print, const uint8_t is_entry, const uint8_t failsafe, const f_string_static_t name);
#endif // _di_controller_print_message_entry_item_done_

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
 */
#ifndef _di_controller_print_message_entry_item_executing_
  extern f_status_t controller_print_message_entry_item_executing(fl_print_t * const print, const uint8_t is_entry, f_string_dynamics_t * const parameters);
#endif // _di_controller_print_message_entry_item_executing_

/**
 * Print message about processing an item.
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
 */
#ifndef _di_controller_print_message_entry_item_process_
  extern f_status_t controller_print_message_entry_item_process(fl_print_t * const print, const uint8_t is_entry, const f_string_static_t prepend, const f_string_static_t name);
#endif // _di_controller_print_message_entry_item_process_

/**
 * Print message about a problem with an entry item.
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
 * @param name
 *   The item name.
 * @param reason
 *   The reason regarding the problem with the required entry item.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_message_entry_item_required_
  extern f_status_t controller_print_message_entry_item_required(fl_print_t * const print, const uint8_t is_entry, const f_string_static_t name, const f_string_t reason);
#endif // _di_controller_print_message_entry_item_required_

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
 * @param entry
 *   The entry.
 *
 *   Must not be NULL.
 * @param action
 *   The entry action.
 *
 *   Must not be NULL.
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param alias_rule
 *   The rule alias name.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_message_entry_item_rule_
  extern f_status_t controller_print_message_entry_item_rule(fl_print_t * const print, controller_entry_t * const entry, controller_entry_action_t * const action, const uint8_t is_entry, const f_string_static_t alias_rule);
#endif // _di_controller_print_message_entry_item_rule_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_entry_message_item_h
