/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common thread enumerations.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_common_enumeration_thread_h
#define _controller_main_common_enumeration_thread_h

#ifdef __cplusplus
extern "C" {
#endif

  /**
   * States for the thread, designating how to stop the process.
   *
   * controller_thread_*_e:
   *   - enabled_not:          The controller is no longer enabled, shut down and abort all work.
   *   - enabled:              The controller is operating normally.
   *   - enabled_execute:      The controller is executing another process, all running operations must terminate.
   *   - enabled_exit:         The controller is shutting down, only process Exit rules.
   *   - enabled_exit_execute: The controller is executing another process while in failsafe mode, all running operations must terminate.
   *   - enabled_exit_ready:   The controller is shutting down, only process Exit rules, and now ready to send termination signals.
   */
  enum {
    controller_thread_enabled_not_e = 0,
    controller_thread_enabled_e,
    controller_thread_enabled_execute_e,
    controller_thread_enabled_exit_e,
    controller_thread_enabled_exit_execute_e,
    controller_thread_enabled_exit_ready_e,
  }; // enum

  /**
   * States for the thread, designating how the process is cancelled.
   *
   * controller_thread_cancel_*_e:
   *   - signal:       Cancellation is triggered by a signal.
   *   - call:         Cancellation is explicitly called.
   *   - execute:      Cancellation is explicitly called due to an "execute" Item Action, when not during Exit.
   *   - exit:         Cancellation is explicitly called during Exit.
   *   - exit_execute: Cancellation is explicitly called due to an "execute" Item Action during Exit.
   */
  enum {
    controller_thread_cancel_signal_e = 0,
    controller_thread_cancel_call_e,
    controller_thread_cancel_execute_e,
    controller_thread_cancel_exit_e,
    controller_thread_cancel_exit_execute_e,
  }; // enum

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_enumeration_thread_h
