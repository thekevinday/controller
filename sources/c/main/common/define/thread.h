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
 */
#ifndef _di_controller_thread_d_
  #define controller_thread_cleanup_interval_long_d     3600      // 1 hour in seconds.
  #define controller_thread_cleanup_interval_short_d    180       // 3 minutes in seconds.
  #define controller_thread_exit_timeout_d              500       // 0.5 seconds in milliseconds.
  #define controller_thread_exit_process_cancel_wait_d  600000000 // 0.6 seconds in nanoseconds.
  #define controller_thread_exit_process_cancel_total_d 150       // 90 seconds in multiples of wait.
  #define controller_thread_simulation_timeout_d        200       // 0.2 seconds in milliseconds.

  #define controller_thread_signal_wait_timeout_seconds_d     70
  #define controller_thread_signal_wait_timeout_nanoseconds_d 0

  #define controller_thread_lock_read_timeout_seconds_d      3
  #define controller_thread_lock_read_timeout_nanoseconds_d  0
  #define controller_thread_lock_write_timeout_seconds_d     3
  #define controller_thread_lock_write_timeout_nanoseconds_d 0

  #define controller_thread_wait_timeout_1_before_d 4
  #define controller_thread_wait_timeout_2_before_d 12
  #define controller_thread_wait_timeout_3_before_d 28

  #define controller_thread_wait_timeout_1_seconds_d     0
  #define controller_thread_wait_timeout_1_nanoseconds_d 20000000  // 0.02 seconds in nanoseconds.
  #define controller_thread_wait_timeout_2_seconds_d     0
  #define controller_thread_wait_timeout_2_nanoseconds_d 200000000 // 0.2 seconds in nanoseconds.
  #define controller_thread_wait_timeout_3_seconds_d     2
  #define controller_thread_wait_timeout_3_nanoseconds_d 0
  #define controller_thread_wait_timeout_4_seconds_d     20
  #define controller_thread_wait_timeout_4_nanoseconds_d 0

  #define controller_thread_exit_helper_timeout_seconds_d     0
  #define controller_thread_exit_helper_timeout_nanoseconds_d 100000000 // 0.1 seconds in nanoseconds.

  #define controller_thread_exit_ready_timeout_seconds_d     0
  #define controller_thread_exit_ready_timeout_nanoseconds_d 500000000 // 0.5 seconds in nanoseconds.
#endif // _di_controller_thread_d_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_define_thread_h
