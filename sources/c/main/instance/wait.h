/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the instance wait functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_instance_wait_h
#define _controller_main_instance_wait_h

#ifdef __cplusplus
extern "C" {
#endif

/***
 * Safely wait for a instance, periodically checking to see if instance completed or check if exiting.
 *
 * @param instance
 *   The instance to wait on.
 *
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *
 *   F_interrupt (with error bit) on receiving a instance signal, such as an interrupt signal.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Success from: f_thread_condition_wait_timed().
 *
 *   Errors (with error bit) from: f_thread_condition_wait_timed().
 *
 * @see f_thread_condition_wait_timed()
 */
#ifndef _di_controller_instance_wait_
  extern f_status_t controller_instance_wait(controller_instance_t * const instance);
#endif // _di_controller_instance_wait_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_instance_wait_h
