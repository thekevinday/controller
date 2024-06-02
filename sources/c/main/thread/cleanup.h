/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the thread "cleanup" functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_thread_cleanup_h
#define _controller_main_thread_cleanup_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Thread for periodically cleaning up data when not busy.
 *
 * @param arguments
 *   The thread arguments.
 *   Must be of type controller_global_t.
 *
 *   Must not be NULL.
 *
 * @return
 *   0, always.
 */
#ifndef _di_controller_thread_cleanup_
  extern void * controller_thread_cleanup(void * const arguments);
#endif // _di_controller_thread_cleanup_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_thread_cleanup_h
