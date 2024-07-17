/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print Entry message functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_entry_message_h
#define _controller_main_print_entry_message_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print message about the specified Entry being in the given state.
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
 *   If TRUE, then this loads as an Entry.
 *   If FALSE, then this loads as an Exit.
 * @param name
 *   The name of the state.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_message_entry_state_
  extern f_status_t controller_print_message_entry_state(fl_print_t * const print, const uint8_t is_entry, const f_string_static_t name);
#endif // _di_controller_print_message_entry_state_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_entry_message_h
