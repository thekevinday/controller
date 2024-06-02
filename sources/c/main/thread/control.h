/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the thread "control" functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_thread_control_h
#define _controller_main_thread_control_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Thread for handling control requests and responses.
 *
 * @param arguments
 *   The global data.
 *   Must be of type controller_global_t.
 *
 *   Must not be NULL.
 *
 * @return
 *   0, always.
 */
#ifndef _di_controller_thread_control_
  extern void * controller_thread_control(void * const arguments);
#endif // _di_controller_thread_control_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_thread_control_h
