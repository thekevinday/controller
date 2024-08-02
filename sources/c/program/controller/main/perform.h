/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides perform functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_perform_h
#define _controller_main_perform_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform all activities requiring the state to be "ready".
 *
 * This prints messages on errors.
 *
 * This does not do any locking or unlocking for the setting data, and so be sure to lock appropriately before and after calling this.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 * @param is_entry
 *   If TRUE, then this operates as an Entry.
 *   If FALSE, then this operates as an Exit.
 *
 * @return
 *   F_okay on success.
 *
 *   Errors from controller_file_pid_create() are not returned, unless it is a memory error.
 *
 * @see controller_file_pid_create()
 */
#ifndef _di_controller_perform_ready_
  extern f_status_t controller_perform_ready(controller_t * const main, const uint8_t is_entry);
#endif // _di_controller_perform_ready_

/**
 * Perform the socket loading when "ready".
 *
 * This prints messages on errors.
 *
 * This does not do any locking or unlocking for the setting data, and so be sure to lock appropriately before and after calling this.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *   F_data_not on success but socket file not created.
 *
 *   Errors (with error bit) from: f_file_mode_set().
 *   Errors (with error bit) from: f_file_remove().
 *   Errors (with error bit) from: f_file_role_change().
 *   Errors (with error bit) from: f_socket_bind_local().
 *   Errors (with error bit) from: f_socket_create().
 *   Errors (with error bit) from: f_thread_create().
 *
 * @see f_file_mode_set()
 * @see f_file_remove()
 * @see f_file_role_change()
 * @see f_socket_bind_local()
 * @see f_socket_create()
 * @see f_thread_create()
 */
#ifndef _di_controller_perform_ready_socket_
  extern f_status_t controller_perform_ready_socket(controller_t * const main);
#endif // _di_controller_perform_ready_socket_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_perform_h
