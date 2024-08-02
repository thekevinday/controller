/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides time functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_time_h
#define _controller_main_time_h

/**
 * Get the current time, plus the given offset.
 *
 * @param seconds
 *   The seconds to add to current time.
 * @param nanoseconds
 *   The nanoseconds to add to current time.
 * @param time
 *   The resulting current time.
 *
 * @see f_time_of_day_get()
 */
#ifndef _di_controller_time_now_
  extern void controller_time_now(const time_t seconds, const long nanoseconds, f_time_spec_t * const time);
#endif // _di_controller_time_now_

/**
 * Sleep for the given time.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 *
 *   This does not alter main.setting.state.status.
 * @param time
 *   The time in nanoseconds to wait.
 *
 * @return
 *   Success from: f_signal_wait_until().
 *   Success from: f_time_of_day_get().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_signal_wait_until().
 *   Errors (with error bit) from: f_time_of_day_get().
 *
 * @see f_time_of_day_get()
 */
#ifndef _di_controller_time_sleep_nanoseconds_
  extern f_status_t controller_time_sleep_nanoseconds(controller_t * const main, const f_time_spec_t time);
#endif // _di_controller_time_sleep_nanoseconds_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_time_h
