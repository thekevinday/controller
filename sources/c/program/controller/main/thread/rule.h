/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the thread "rule" functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_thread_rule_h
#define _controller_main_thread_rule_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Thread for handling Rule processing.
 *
 * This acts as the main Rule thread after Entry processing.
 * This runs all synchronous Rules or spawns asynchronous rules.
 *
 * @todo the control thread should send commands to this thread, somehow.
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
#ifndef _di_controller_thread_rule_
  extern void * controller_thread_rule(void * const argument);
#endif // _di_controller_thread_rule_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_thread_rule_h
