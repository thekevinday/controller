/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the thread "instance" functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_thread_instance_h
#define _controller_main_thread_instance_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Asynchronously execute a Rule process.
 *
 * @param is_normal
 *   If F_true, then process as if this operates during a normal operation (Entry and Control).
 *   If F_false, then process as if this operates during an Exit operation.
 * @param instance
 *   The instance data.
 *
 *   Must not be NULL.
 *
 * @see controller_rule_instance_perform()
 */
#ifndef _di_controller_thread_instance_
  extern void controller_thread_instance(const uint8_t is_normal, controller_instance_t * const instance);
#endif // _di_controller_thread_instance_

/**
 * Cancel all process threads.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 *
 *   This does not alter main.setting.state.status.
 * @param is_normal
 *   If F_true, then process as if this operates during a normal operation (Entry and Control).
 *   If F_false, then process as if this operates during an Exit operation.
 * @param by
 *   Designate the way in which the cancellation should operate.
 *
 *   If controller_thread_cancel_signal_e, then this was called from within the signal handling thread, so do not cancel the signal thread.
 *   If controller_thread_cancel_call_e, then this was not called from within the signal handling thread, so cancel the signal thread.
 *   If controller_thread_cancel_execute_e, then this was called from within the Entry/Exit for executing a process, so cancel the signal thread but not the Entry thread.
 */
#ifndef _di_controller_thread_instance_cancel_
  extern void controller_thread_instance_cancel(controller_t * const main, const uint8_t is_normal, const uint8_t by);
#endif // _di_controller_thread_instance_cancel_

/**
 * Process the Exit file, if applicable.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 *
 *   This does not alter main.setting.state.status.
 */
#ifndef _di_controller_thread_instance_exit_
  extern void controller_thread_instance_exit(controller_t * const main);
#endif // _di_controller_thread_instance_exit_

/**
 * Asynchronously execute a Rule process during normal operations.
 *
 * @param argument
 *   The instance data.
 *
 *   Must be of type controller_instance_t.
 *   Must not be NULL.
 *
 * @return
 *   0, always.
 *
 * @see controller_thread_instance()
 */
#ifndef _di_controller_thread_instance_normal_
  extern void * controller_thread_instance_normal(void * const argument);
#endif // _di_controller_thread_instance_normal_

/**
 * Asynchronously execute a Rule process during other operations.
 *
 * @param argument
 *   The instance data.
 *
 *   Must be of type controller_instance_t.
 *   Must not be NULL.
 *
 * @return
 *   0, always.
 *
 * @see controller_thread_instance()
 */
#ifndef _di_controller_thread_instance_other_
  extern void * controller_thread_instance_other(void * const argument);
#endif // _di_controller_thread_instance_other_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_thread_instance_h
