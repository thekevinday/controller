/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common thread defines.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_common_define_thread_h
#define _controller_main_common_define_thread_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Thread related defines.
 *
 * controller_thread_cleanup_interval_*_d:
 *   - long:  How many seconds to wait for clean up for long waits.
 *   - short: How many seconds to wait for clean up for short waits.
 *
 * controller_thread_exit_*_d:
 *   - disable_force_times:  The number of times to retry apply lock aon exit before forcibly setting state to disabled on exit.
 *   - process_cancel_total: The number of nanoseconds to wait when cancelling a process.
 *   - process_cancel_wait:  The total number of times to wait when cancelling a process (multiply this by wait time to get total nanoseconds).
 */
#ifndef _di_controller_thread_d_
  #define controller_thread_cleanup_interval_long_d  3600 // 1 hour in seconds.
  #define controller_thread_cleanup_interval_short_d 180  // 3 minutes in seconds.

  #define controller_thread_exit_disable_force_times    12
  #define controller_thread_exit_process_cancel_wait_d  600000000 // 0.6 seconds in nanoseconds.
  #define controller_thread_exit_process_cancel_total_d 150       // 90 seconds in multiples of wait.
#endif // _di_controller_thread_d_

/**
 * Thread related timeout defines.
 *
 * controller_thread_timeout_*_d:
 *   - exit:                           The number of milliseconds to wait before exit times out (before a terminate/kill signal is sent).
 *   - exit_disable_force_nanoseconds: The nanoseconds to wait between each attempt to lock and set disable state.
 *   - exit_disable_force_seconds:     The seconds to wait between each attempt to lock and set disable state.
 *   - exit_helper_nanoseconds:        The nanoseconds to wait before the exit helper times out.
 *   - exit_helper_seconds:            The seconds to wait before the exit helper times out.
 *   - exit_ready_nanoseconds:         The nanoseconds to wait before the exit ready times out.
 *   - exit_ready_seconds:             The seconds to wait before the exit ready times out.
 *   - lock_read_nanoseconds:          The nanoseconds to wait before the read lock times out.
 *   - lock_read_seconds:              The seconds to wait before the read lock times out.
 *   - lock_write_nanoseconds:         The nanoseconds to wait before the write lock times out.
 *   - lock_write_seconds:             The seconds to wait before the write lock times out.
 *   - simulation:                     The number of milliseconds to wait to simulate a pause due to a process execution.
 *   - wait_signal_nanoseconds:        The nanoseconds to wait before waiting for the signal times out.
 *   - wait_signal_seconds:            The seconds to wait before waiting for the signal times out.
 *   - wait_1_before:                  The max number of retries to perform set 1 wait timeouts.
 *   - wait_1_nanoseconds:             The nanoseconds to wait in set 1 timeouts while waiting for an Instance.
 *   - wait_1_seconds:                 The seconds to wait in set 1 timeouts while waiting for an Instance.
 *   - wait_2_before:                  The max number of retries to perform set 2 wait timeouts (after set 1 wait before is exceeded).
 *   - wait_2_nanoseconds:             The nanoseconds to wait in set 2 timeouts while waiting for an Instance.
 *   - wait_2_seconds:                 The seconds to wait in set 2 timeouts while waiting for an Instance.
 *   - wait_3_before:                  The max number of retries to perform set 3 wait timeouts (after set 2 wait before is exceeded).
 *   - wait_3_nanoseconds:             The nanoseconds to wait in set 3 timeouts while waiting for an Instance.
 *   - wait_3_seconds:                 The seconds to wait in set 3 timeouts while waiting for an Instance.
 *   - wait_4_nanoseconds:             The nanoseconds to wait in set 4 timeouts while waiting for an Instance.
 *   - wait_4_seconds:                 The seconds to wait in set 4 timeouts while waiting for an Instance.
 */
#ifndef _di_controller_thread_timeout_d_
  #define controller_thread_timeout_exit_d                           500 // 0.5 seconds in milliseconds.
  #define controller_thread_timeout_exit_disable_force_nanoseconds_d 10000000  // 0.01 seconds in nanoseconds.
  #define controller_thread_timeout_exit_disable_force_seconds_d     0
  #define controller_thread_timeout_exit_helper_nanoseconds_d        100000000 // 0.1 seconds in nanoseconds.
  #define controller_thread_timeout_exit_helper_seconds_d            0
  #define controller_thread_timeout_exit_ready_nanoseconds_d         500000000 // 0.5 seconds in nanoseconds.
  #define controller_thread_timeout_exit_ready_seconds_d             0

  #define controller_thread_timeout_lock_read_nanoseconds_d  0
  #define controller_thread_timeout_lock_read_seconds_d      3
  #define controller_thread_timeout_lock_write_nanoseconds_d 0
  #define controller_thread_timeout_lock_write_seconds_d     3

  #define controller_thread_timeout_simulation_d 200 // 0.2 seconds in milliseconds.

  #define controller_thread_timeout_wait_1_before_d           4
  #define controller_thread_timeout_wait_1_nanoseconds_d      20000000  // 0.02 seconds in nanoseconds.
  #define controller_thread_timeout_wait_1_seconds_d          0
  #define controller_thread_timeout_wait_2_before_d           12
  #define controller_thread_timeout_wait_2_nanoseconds_d      200000000 // 0.2 seconds in nanoseconds.
  #define controller_thread_timeout_wait_2_seconds_d          0
  #define controller_thread_timeout_wait_3_before_d           28
  #define controller_thread_timeout_wait_3_nanoseconds_d      0
  #define controller_thread_timeout_wait_3_seconds_d          2
  #define controller_thread_timeout_wait_4_nanoseconds_d      0
  #define controller_thread_timeout_wait_4_seconds_d          20
  #define controller_thread_timeout_wait_signal_nanoseconds_d 0
  #define controller_thread_timeout_wait_signal_seconds_d     70
#endif // _di_controller_thread_timeout_d_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_define_thread_h
