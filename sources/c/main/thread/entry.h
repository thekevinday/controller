/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the thread "entry" functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_thread_entry_h
#define _controller_main_thread_entry_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Thread for handling Entry processing.
 *
 * This acts as the main Rule thread during Entry processing.
 * This runs all synchronous Rules or spawns asynchronous rules.
 *
 * @param arguments
 *   The main program data.
 *
 *   Must be of type controller_t.
 *   Must not be NULL.
 *
 * @return
 *   0, always.
 */
#ifndef _di_controller_thread_entry_
  extern void * controller_thread_entry(void * const arguments);
#endif // _di_controller_thread_entry_

/**
 * Thread for handling Exit file processing.
 *
 * This acts as the main Rule thread during Exit processing.
 * This runs all synchronous Rules or spawns asynchronous rules.
 *
 * Do not confuse this with exiting a thread, this is the what process the Exit files (similar to that of an Entry file).
 * Exit files process the "stop" action, whereas the Entry files process the "start" Action
 *
 * @param argument
 *   The main program data.
 *
 *   Must be of type controller_t.
 *   Must not be NULL.
 *
 * @return
 *   0, always.
 */
#ifndef _di_controller_thread_exit_
  extern void * controller_thread_exit(void * const argument);
#endif // _di_controller_thread_exit_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_thread_entry_h
