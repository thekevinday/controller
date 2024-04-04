/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print message functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_message_h
#define _controller_main_print_message_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print help.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be controller_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param uninterrupt
 *   Set to F_true to print that the default behavior is uninterruptible.
 *   Otherwise, print that the default behavior is interruptible.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_flush()
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see f_print_dynamic_raw()
 * @see fll_program_print_help_header()
 * @see fll_program_print_help_option()
 * @see fll_program_print_help_usage()
 */
#ifndef _di_controller_main_print_message_help_
  extern f_status_t controller_main_print_message_help(fl_print_t * const print, const uint8_t uninterrupt);
#endif // _di_controller_main_print_message_help_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_message_h
