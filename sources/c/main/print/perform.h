/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print perform functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_perform_h
#define _controller_main_print_perform_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print debug message about control socket failing for the reason specified.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be controller_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param status
 *   The status code relating to the failure.
 * @param message
 *   A short message describing the reason for the failure.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_perform_debug_control_socket_failure_
  extern f_status_t controller_print_perform_debug_control_socket_failure(fl_print_t * const print, const f_status_t status, const f_string_t message);
#endif // _di_controller_print_perform_debug_control_socket_failure_

/**
 * Print debug message about control socket being created.
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
#ifndef _di_controller_print_perform_debug_control_socket_success_
  extern f_status_t controller_print_perform_debug_control_socket_success(fl_print_t * const print);
#endif // _di_controller_print_perform_debug_control_socket_success_

/**
 * Print debug message about control socket missing in read only mode.
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
#ifndef _di_controller_print_perform_debug_control_socket_missing_read_only_
  extern f_status_t controller_print_perform_debug_control_socket_missing_read_only(fl_print_t * const print);
#endif // _di_controller_print_perform_debug_pid_file_control_socket_

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
#ifndef _di_controller_print_perform_debug_pid_file_control_socket_
  extern f_status_t controller_print_perform_debug_pid_file_control_socket(fl_print_t * const print);
#endif // _di_controller_print_perform_debug_pid_file_control_socket_

/**
 * Print debug message on problems when creating PID file.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be controller_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param function
 *   The name of the function associated with the error.
 * @param status
 *   The status code to process.
 *   Make sure this has F_status_set_fine() called if the status code has any error or warning bits.
 * @param is_entry
 *   If TRUE, then this operates as an entry.
 *   If FALSE, then this operates as an exit.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_perform_debug_pid_file_create_problem_
  extern f_status_t controller_print_perform_debug_pid_file_create_problem(fl_print_t * const print, const f_string_t function, const f_status_t status, const uint8_t is_entry);
#endif // _di_controller_print_perform_debug_pid_file_create_problem_

/**
 * Print debug message on success when creating PID file.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be controller_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param is_entry
 *   If TRUE, then this operates as an entry.
 *   If FALSE, then this operates as an exit.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_perform_debug_pid_file_create_success_
  extern f_status_t controller_print_perform_debug_pid_file_create_success(fl_print_t * const print, const uint8_t is_entry);
#endif // _di_controller_print_perform_debug_pid_file_create_success_

/**
 * Print error message on problems when creating PID file.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be controller_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param function
 *   The name of the function associated with the error.
 * @param status
 *   The status code to process.
 *   Make sure this has F_status_set_fine() called if the status code has any error or warning bits.
 * @param is_entry
 *   If TRUE, then this operates as an entry.
 *   If FALSE, then this operates as an exit.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_perform_error_pid_file_create_
  extern f_status_t controller_print_perform_error_pid_file_create(fl_print_t * const print, const f_string_t function, const f_status_t status, const uint8_t is_entry);
#endif // _di_controller_print_perform_error_pid_file_create_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_perform_h
