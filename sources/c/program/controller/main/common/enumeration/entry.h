/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common Entry enumerations.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_common_enumeration_entry_h
#define _controller_main_common_enumeration_entry_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Controller Entry Action flags.
 *
 * controller_entry_action_flag_*_e:
 *   - undefined: The given type and code are designated as undefined.
 */
#ifndef _di_controller_entry_action_e_
  enum {
    controller_entry_action_flag_none_e      = 0x0,
    controller_entry_action_flag_undefined_e = 0x1,
  }; // enum
#endif // _di_controller_entry_action_e_

/**
 * Controller Entry Action type enumeration.
 *
 * controller_entry_action_type_*_e:
 *   - none:     Nothing set.
 *   - consider: Perform the consider controller operation.
 *   - execute:  Perform the execute controller operation.
 *   - freeze:   Perform the freeze controller operation..
 *   - item:     Perform the item controller operation.
 *   - kexec:    Perform the kexec controller operation (only for init mode).
 *   - kill:     Perform the kill controller operation.
 *   - pause:    Perform the pause controller operation.
 *   - ready:    Perform the ready controller operation.
 *   - reboot:   Perform the reboot controller operation (only for init mode).
 *   - reload:   Perform the reload controller operation.
 *   - restart:  Perform the restart controller operation.
 *   - resume:   Perform the resume controller operation.
 *   - shutdown: Perform the shutdown controller operation (only for init mode).
 *   - start:    Perform the start controller operation.
 *   - stop:     Perform the stop controller operation.
 *   - timeout:  Perform the timeout controller operation.
 *   - thaw:     Perform the thaw controller operation.
 */
#ifndef _di_controller_entry_action_type_e_
  enum {
    controller_entry_action_type_none_e = 0,
    controller_entry_action_type_consider_e,
    controller_entry_action_type_execute_e,
    controller_entry_action_type_failsafe_e,
    controller_entry_action_type_freeze_e,
    controller_entry_action_type_item_e,
    controller_entry_action_type_kexec_e,
    controller_entry_action_type_kill_e,
    controller_entry_action_type_pause_e,
    controller_entry_action_type_ready_e,
    controller_entry_action_type_reboot_e,
    controller_entry_action_type_reload_e,
    controller_entry_action_type_restart_e,
    controller_entry_action_type_resume_e,
    controller_entry_action_type_shutdown_e,
    controller_entry_action_type_start_e,
    controller_entry_action_type_stop_e,
    controller_entry_action_type_timeout_e,
    controller_entry_action_type_thaw_e,
  }; // enum
#endif // _di_controller_entry_action_type_e_

/**
 * Controller Entry flags.
 *
 * controller_entry_flag_*_e:
 *   - none:             No flags are set.
 *   - is:               Designate that this is an Entry rather than an Exit.
 *   - timeout_exit_no:  The exit timeout is disabled.
 *   - timeout_kill_no:  The kill timeout is disabled for Rules by default.
 *   - timeout_start_no: The start timeout is disabled for Rules by default.
 *   - timeout_stop_no:  The stop timeout is disabled for Rules by default.
 */
#ifndef _di_controller_entry_flag_e_
  enum {
    controller_entry_flag_none_e             = 0x0,
    controller_entry_flag_is_e               = 0x1,
    controller_entry_flag_timeout_exit_no_e  = 0x2,
    controller_entry_flag_timeout_kill_no_e  = 0x4,
    controller_entry_flag_timeout_start_no_e = 0x8,
    controller_entry_flag_timeout_stop_no_e  = 0x10,
  }; // enum
#endif // _di_controller_entry_flag_e_

/**
 * Controller Entry PID enumeration.
 *
 * controller_entry_pid_*_e:
 *   - disable: Do not check for or create a PID file to represent the Entry execution.
 *   - require: Check to see if the PID file exists for an Entry at startup and then when "ready" create a pid file, display error on pid file already exists or on failure and then fail.
 *   - ready:   When "ready" create a pid file, display error on failure and then fail (does not check if PID file exists).
 */
#ifndef _di_controller_entry_pid_e_
  enum {
    controller_entry_pid_disable_e = 0,
    controller_entry_pid_require_e,
    controller_entry_pid_ready_e,
  }; // enum
#endif // _di_controller_entry_pid_e_

/**
 * Controller Entry session enumeration.
 *
 * controller_entry_session_*_e:
 *   - none: No special session configuration specified, use built in defaults.
 *   - new:  Designate the default to use a new session, ignoring built in defaults (passing FL_execute_parameter_option_session_d to the execute functions).
 *   - same: Designate the default to use a same session, ignoring built in defaults.
 */
#ifndef _di_controller_entry_session_e_
  enum {
    controller_entry_session_none_e = 0,
    controller_entry_session_new_e,
    controller_entry_session_same_e,
  }; // enum
#endif // _di_controller_entry_session_e_

/**
 * Controller Entry show enumeration.
 *
 * controller_entry_show_*_e:
 *   - normal: Do not print anything other than warnings and errors, but allow executed programs and scripts to output however they like.
 *   - init:   Print like an init program, printing status of Entry and Rules as they are being started, stopped, etc...
 */
#ifndef _di_controller_entry_show_e_
  enum {
    controller_entry_show_normal_e = 0,
    controller_entry_show_init_e,
  }; // enum
#endif // _di_controller_entry_show_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_enumeration_entry_h
