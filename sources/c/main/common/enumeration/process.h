/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common process enumerations.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_common_enumeration_process_h
#define _controller_main_common_enumeration_process_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Controller process flags.
 *
 * controller_process_flag_*_e:
 *   - interruptible: When specified, process responds to interrupt signals, otherwise block/ignore interrupt signals.
 *   - pid_created:   When specified, the process responds to interrupt signals, otherwise block/ignore interrupt signals.
 *   - failsafe:      When specified, failsafe mode is enabled, otherwise failsafe mode is disabled.
 */
#ifndef _di_controller_process_flag_e_
  enum {
    controller_process_flag_interruptible_e = 0x1,
    controller_process_flag_pid_created_e   = 0x2,
    controller_process_flag_failsafe_e      = 0x4,
  }; // enum
#endif // _di_controller_process_flag_e_

/**
 * Controller process mode enumeration.
 *
 * controller_process_mode_*:
 *   - helper:  Run as a helper, exiting when finished prrocess entry (and any respective exit).
 *   - program: Run as a program, exiting when finished prrocess entry (and any respective exit).
 *   - service: Run as a service, listening for requests after processing entry.
 */
#ifndef _di_controller_process_mode_e_
  enum {
    controller_process_mode_service_e = 0,
    controller_process_mode_helper_e,
    controller_process_mode_program_e,
  }; // enum
#endif // _di_controller_process_mode_e_

/**
 * Controller process ready enumeration.
 *
 * controller_process_ready_*_e:
 *   - no:    Entry/Exit is not ready.
 *   - wait:  Entry/Exit has "ready" somewhere in the file but is not yet ready.
 *   - yes:   Entry/Exit is now ready (Entry/Exit is still being processed).
 *   - done:  Entry/Exit is ready and processing is complete.
 *   - fail:  Entry/Exit processing failed.
 *   - abort: Abort received before finished processing Entry/Exit.
 */
#ifndef _di_controller_process_ready_e_
  enum {
    controller_process_ready_no_e = 0,
    controller_process_ready_wait_e,
    controller_process_ready_yes_e,
    controller_process_ready_done_e,
    controller_process_ready_fail_e,
    controller_process_ready_abort_e,
  }; // enum
#endif // _di_controller_process_ready_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_enumeration_process_h
