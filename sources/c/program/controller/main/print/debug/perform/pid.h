/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print perform pid debug functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_debug_perform_pid_h
#define _controller_main_print_debug_perform_pid_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print debug message about PID file and control socket.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be controller_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_debug_perform_pid_file_control_socket_
  extern f_status_t controller_print_debug_perform_pid_file_control_socket(fl_print_t * const print);
#endif // _di_controller_print_debug_perform_pid_file_control_socket_

/**
 * Print debug message on problems when creating PID file.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be controller_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param status
 *   The status code to process.
 *   Make sure this has F_status_set_fine() called if the status code has any error or warning bits.
 * @param function
 *   The name of the function associated with the error.
 * @param is_entry
 *   If TRUE, then this operates as an Entry.
 *   If FALSE, then this operates as an Exit.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_debug_perform_pid_file_create_problem_
  extern f_status_t controller_print_debug_perform_pid_file_create_problem(fl_print_t * const print, const f_status_t status, const f_string_t function, const uint8_t is_entry);
#endif // _di_controller_print_debug_perform_pid_file_create_problem_

/**
 * Print debug message on success when creating PID file.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be controller_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_debug_perform_pid_file_create_success_
  extern f_status_t controller_print_debug_perform_pid_file_create_success(fl_print_t * const print);
#endif // _di_controller_print_debug_perform_pid_file_create_success_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_debug_perform_pid_h
