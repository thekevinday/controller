/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common program enumerations.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_common_enumeration_program_h
#define _controller_main_common_enumeration_program_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Controller program flags.
 *
 * controller_setting_flag_*_e:
 *   - interruptible: When specified, program responds to interrupt signals, otherwise block/ignore interrupt signals.
 *   - pid_created:   When specified, the program responds to interrupt signals, otherwise block/ignore interrupt signals.
 *   - failsafe:      When specified, failsafe mode is enabled, otherwise failsafe mode is disabled.
 */
#ifndef _di_controller_program_flag_e_
  enum {
    controller_program_flag_interruptible_e = 0x1,
    controller_program_flag_pid_created_e   = 0x2,
    controller_program_flag_failsafe_e      = 0x4,
  }; // enum
#endif // _di_controller_program_flag_e_

/**
 * Controller program mode enumeration.
 *
 * controller_setting_mode_*:
 *   - helper:  Run as a helper, exiting when finished prrocess entry (and any respective exit).
 *   - program: Run as a program, exiting when finished prrocess entry (and any respective exit).
 *   - service: Run as a service, listening for requests after processing entry.
 */
#ifndef _di_controller_program_mode_e_
  enum {
    controller_program_mode_service_e = 0,
    controller_program_mode_helper_e,
    controller_program_mode_program_e,
  }; // enum
#endif // _di_controller_program_mode_e_

/**
 * Controller Process ready enumeration.
 *
 * controller_program_ready_*_e:
 *   - no:    Entry/Exit is not ready.
 *   - wait:  Entry/Exit has "ready" somewhere in the file but is not yet ready.
 *   - yes:   Entry/Exit is now ready (Entry/Exit is still being processed).
 *   - done:  Entry/Exit is ready and processing is complete.
 *   - fail:  Entry/Exit processing failed.
 *   - abort: Abort received before finished processing Entry/Exit.
 */
#ifndef _di_controller_program_ready_e_
  enum {
    controller_program_ready_no_e = 0,
    controller_program_ready_wait_e,
    controller_program_ready_yes_e,
    controller_program_ready_done_e,
    controller_program_ready_fail_e,
    controller_program_ready_abort_e,
  }; // enum
#endif // _di_controller_program_ready_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_enumeration_program_h
