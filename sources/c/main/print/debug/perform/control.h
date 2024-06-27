/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print debug perform control functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_debug_perform_control_h
#define _controller_main_print_debug_perform_control_h

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
 *
 *   Must not be NULL.
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
#ifndef _di_controller_print_debug_perform_control_socket_failure_
  extern f_status_t controller_print_debug_perform_control_socket_failure(fl_print_t * const print, const f_status_t status, const f_string_t message);
#endif // _di_controller_print_debug_perform_control_socket_failure_

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
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_debug_perform_control_socket_success_
  extern f_status_t controller_print_debug_perform_control_socket_success(fl_print_t * const print);
#endif // _di_controller_print_debug_perform_control_socket_success_

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
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_debug_perform_control_socket_missing_read_only_
  extern f_status_t controller_print_debug_perform_control_socket_missing_read_only(fl_print_t * const print);
#endif // _di_controller_print_debug_perform_pid_file_control_socket_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_debug_perform_control_h
