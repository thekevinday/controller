/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the thread "is" functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_thread_is_h
#define _controller_main_thread_is_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Check to see if thread is enabled for the normal operations like entry and control or for exit operations.
 *
 * @param is_normal
 *   If TRUE, then instance as if this operates during a normal operation (entry and control).
 *   If FALSE, then instance as if this operates during a an exit operation.
 * @param thread
 *   The thread data.
 *
 * @return
 *   F_true when enabled.
 *   F_false when disabled.
 */
#ifndef _di_controller_main_thread_is_enabled_
  extern f_status_t controller_main_thread_is_enabled(const uint8_t is_normal, controller_thread_t * const thread);
#endif // _di_controller_main_thread_is_enabled_

/**
 * Check to see if thread is enabled for the normal operations like entry and control or for exit operations for some instance.
 *
 * @param instance
 *   The instance to use when checking if thread is enabled.
 * @param thread
 *   The thread data.
 *
 * @return
 *   F_true when enabled.
 *   F_false when disabled or when parameter is invalid..
 *
 * @see controller_main_thread_is_enabled_instance_type()
 */
#ifndef _di_controller_main_thread_is_enabled_instance_
  extern f_status_t controller_main_thread_is_enabled_instance(controller_instance_t * const instance, controller_thread_t * const thread);
#endif // _di_controller_main_thread_is_enabled_instance_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_thread_is_h
