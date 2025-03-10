/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides thread "signal" functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_thread_signal_h
#define _controller_main_thread_signal_h

/**
 * Thread for handling signals/interrupts.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 * @param is_normal
 *   If TRUE, then process as if this operates during a normal operation (Entry and Control).
 *   If FALSE, then process as if this operates during an Exit operation.
 */
#ifndef _di_controller_thread_signal_
  extern void controller_thread_signal(controller_t * const main, const uint8_t is_normal);
#endif // _di_controller_thread_signal_

/**
 * Callback passed to FSS functions for checking for interrupts.
 *
 * @param state
 *   The state data.
 *
 *   Must not be NULL.
 * @param internal
 *   Not used.
 */
#ifndef _di_controller_thread_signal_state_fss_
  extern void controller_thread_signal_state_fss(f_state_t * const state, void * const internal);
#endif // _di_controller_thread_signal_state_fss_

/**
 * Callback passed to IKI functions for checking for interrupts.
 *
 * @param state
 *   The state data.
 *
 *   Must not be NULL.
 * @param internal
 *   Not used.
 */
#ifndef _di_controller_thread_signal_state_iki_
  extern void controller_thread_signal_state_iki(f_state_t * const state, void * const internal);
#endif // _di_controller_thread_signal_state_iki_

/**
 * Thread for handling signals/interrupts during normal operations.
 *
 * @param argument
 *   The main program data.
 *
 *   Must be of type controller_t.
 *   Must not be NULL.
 *
 * @return
 *   0, always.
 *
 * @see controller_thread_signal()
 */
#ifndef _di_controller_thread_signal_normal_
  extern void * controller_thread_signal_normal(void * const argument);
#endif // _di_controller_thread_signal_normal_

/**
 * Thread for handling signals/interrupts during other operations.
 *
 * @param argument
 *   The main program data.
 *
 *   Must be of type controller_t.
 *   Must not be NULL.
 *
 * @return
 *   0, always.
 *
 * @see controller_thread_signal()
 */
#ifndef _di_controller_thread_signal_other_
  extern void * controller_thread_signal_other(void * const argument);
#endif // _di_controller_thread_signal_other_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_thread_signal_h
