/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print entry message functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_entry_message_h
#define _controller_main_print_entry_message_h

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_entry_message_h
