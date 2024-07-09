/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common instance enumerations.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_common_enumeration_instance_h
#define _controller_main_common_enumeration_instance_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Instance options.
 *
 * controller_instance_option_*_e:
 *   - asynchronous:      The Instance runs asynchronously.
 *   - require:           The Instance is required.
 *   - simulate:          The Instance is being simulated.
 *   - validate:          The Instance is being validated.
 *   - wait:              The Instance is blocking (waiting) for all asynchronous Instances before it to complete before running.
 *   - simulate_validate: A helper flag representing simulate and validate flag bits being set.
 */
#ifndef _di_controller_instance_option_e_
  enum {
    controller_instance_option_asynchronous_e      = 0x1,
    controller_instance_option_require_e           = 0x2,
    controller_instance_option_simulate_e          = 0x4,
    controller_instance_option_validate_e          = 0x8,
    controller_instance_option_wait_e              = 0x10,
    controller_instance_option_simulate_validate_e = 0xc,
  }; // enum
#endif // _di_controller_instance_option_e_

/**
 * Instance states.
 *
 * controller_instance_state_*_e:
 *   - idle:   No instance is running for this Rule.
 *   - busy:   A instance is actively using this, and is running synchronously.
 *   - active: A instance is actively using this, and is running asynchronously.
 *   - done:   A instance has finished running on this and there is a thread that needs to be cleaned up.
 */
#ifndef _di_controller_instance_state_e_
  enum {
    controller_instance_state_idle_e = 1,
    controller_instance_state_busy_e,
    controller_instance_state_active_e,
    controller_instance_state_done_e,
  }; // enum
#endif // _di_controller_instance_state_e_

/**
 * Instance types.
 *
 * controller_instance_type_*_e:
 *   - entry:   The instance is started from an Entry.
 *   - exit:    The instance is started from an Exit.
 *   - control: The instance is started from a control operation.
 */
#ifndef _di_controller_instance_type_e_
  enum {
    controller_instance_type_entry_e = 1,
    controller_instance_type_exit_e,
    controller_instance_type_control_e,
  }; // enum
#endif // _di_controller_instance_type_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_enumeration_instance_h
