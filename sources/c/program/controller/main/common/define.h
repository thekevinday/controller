/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common define types.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_common_define_h
#define _controller_main_common_define_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program allocation defines.
 *
 * controller_allocation_*_d:
 *   - console:   An allocation step used for small buffers specifically for console parameter.
 *   - iki_large: An allocation step used for IKI buffers that are anticipated to have large buffers.
 *   - iki_small: An allocation step used for IKI buffers that are anticipated to have small buffers.
 *   - large:     An allocation step used for buffers that are anticipated to have large buffers.
 *   - pipe:      A buffer size used for processing piped data.
 *   - small:     An allocation step used for buffers that are anticipated to have small buffers.
 */
#ifndef _di_controller_allocation_d_
  #define controller_allocation_console_d   4
  #define controller_allocation_iki_large_d 128
  #define controller_allocation_iki_small_d 8
  #define controller_allocation_large_d     256
  #define controller_allocation_pipe_d      16384
  #define controller_allocation_small_d     4
#endif // _di_controller_allocation_d_

/**
 * Controller lock defines.
 *
 * controller_lock_*_d:
 *   - mutex_max_retry: The maximum amount of times to retry the mutex lock before giving up.
 */
#ifndef _di_controller_lock_d_
  #define controller_lock_mutex_max_retry_d 1000000
#endif // _di_controller_lock_d_

/**
 * Flags associated with Controller locks.
 *
 * controller_lock_flag_*_d:
 *   - setup_not: No locks are initialized, so do not attempt to deallocate them.
 */
#ifndef _di_controller_lock_flag_d_
  #define controller_lock_flag_setup_not_d 0x1
#endif // _di_controller_lock_flag_d_

/**
 * Flags passed to the main function or program.
 *
 * When number mode is not specified, then mode is "string" mode (there is no flag for "string" mode).
 *
 * controller_main_flag_*_d:
 *   - none:                   No flags set.
 *   - copyright:              Print copyright.
 *   - daemon:                 Run the process in the background and create a PID file.
 *   - error:                  Check if status is "error".
 *   - fine:                   Check if status is "fine".
 *   - help:                   Print help.
 *   - interruptible:          The process is interruptible.
 *   - pid:                    Designate that a custom PID is specified.
 *   - pipe:                   Use the input pipe.
 *   - simulate:               Perform simulation of rules rather than execution.
 *   - validate:               Perform validation of rules rather than execution.
 *   - version:                Print version.
 *   - version_copyright_help: A helper flag representing version, copyright, and help flag bits being set.
 */
#ifndef _di_controller_main_flag_d_
  #define controller_main_flag_none_d                   0x0
  #define controller_main_flag_copyright_d              0x1
  #define controller_main_flag_daemon_d                 0x2
  #define controller_main_flag_error_d                  0x4
  #define controller_main_flag_fine_d                   0x8
  #define controller_main_flag_help_d                   0x10
  #define controller_main_flag_interruptible_d          0x20
  #define controller_main_flag_pid_d                    0x40
  #define controller_main_flag_pipe_d                   0x80
  #define controller_main_flag_simulate_d               0x100
  #define controller_main_flag_validate_d               0x200
  #define controller_main_flag_version_d                0x400
  #define controller_main_flag_version_copyright_help_d 0x411
#endif // _di_controller_main_flag_d_

/**
 * The program signal defines.
 *
 * controller_signal_*_d:
 *   - check:          Number of iterations before performing signal check in non-threaded signal handling.
 *   - check_failsafe: When using threads, how many consecutive failures to check signal before aborting (as a recursion failsafe).
 *   - check_tiny:     The tiny check.
 *   - check_short:    The short signal check.
 */
#ifndef _di_controller_signal_d_
  #define controller_signal_check_d          500000
  #define controller_signal_check_failsafe_d 20000
  #define controller_signal_check_tiny_d     4
  #define controller_signal_check_short_d    16
#endif // _di_controller_signal_d_

/**
 * Controller "with" codes.
 *
 * controller_with_*_d:
 *   - full_path:    Using "with" full path.
 *   - session_new:  Using "with" new session.
 *   - session_same: Using "with" same session.
 */
#ifndef _di_controller_with_d_
  #define controller_with_full_path_d    0x1
  #define controller_with_session_new_d  0x2
  #define controller_with_session_same_d 0x4
#endif // _di_controller_with_d_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_define_h
