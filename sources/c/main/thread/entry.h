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
 * Thread for handling entry processing.
 *
 * This acts as the main rule thread during entry processing.
 * This runs all synchronous rules or spawns asynchronous rules.
 *
 * @param arguments
 *   The global data.
 *   Must be of type controller_instance_t.
 *
 *   Must not be NULL.
 *
 * @return
 *   0, always.
 */
#ifndef _di_controller_main_thread_entry_
  extern void * controller_main_thread_entry(void * const arguments);
#endif // _di_controller_main_thread_entry_

/**
 * Thread for handling exit file processing.
 *
 * This acts as the main rule thread during exit processing.
 * This runs all synchronous rules or spawns asynchronous rules.
 *
 * Do not confuse this with exiting a thread, this is the what process the exit files (similar to that of an entry file).
 * Exit files process the "stop" action, whereas the Entry files process the "start" Action
 *
 * @param arguments
 *   The global data.
 *   Must be of type controller_instance_t.
 *
 *   Must not be NULL.
 *
 * @return
 *   0, always.
 */
#ifndef _di_controller_main_thread_exit_
  extern void * controller_main_thread_exit(void * const arguments);
#endif // _di_controller_main_thread_exit_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_thread_entry_h
