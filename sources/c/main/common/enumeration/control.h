/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common control enumerations.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_common_enumeration_control_h
#define _controller_main_common_enumeration_control_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Controller Control flags.
 *
 * controller_control_flag_*_e:
 *   - none:      Nothing set.
 *   - readonly:  Control is set to read-only mode.
 *   - has_user:  A user is manually specified.
 *   - has_group: A group is manually specified.
 *   - has_mode:  A file mode is manually specified.
 */
#ifndef _di_controller_control_e_
  enum {
    controller_control_flag_none_e      = 0x0,
    controller_control_flag_readonly_e  = 0x1,
    controller_control_flag_has_user_e  = 0x2,
    controller_control_flag_has_group_e = 0x4,
    controller_control_flag_has_mode_e  = 0x8,
  }; // enum
#endif // _di_controller_control_e_

/**
 * Controller Control payload type enumeration.
 *
 * controller_control_payload_type_*_e:
 *   - none:       Nothing set.
 *   - controller: The item type represents a command operation.
 *   - error:      The item type represents a script operation.
 *   - init:       The item type represents an init operation (Only fo init mode).
 */
#ifndef _di_controller_control_payload_type_e_
  enum {
    controller_control_payload_type_none_e = 0,
    controller_control_payload_type_controller_e,
    controller_control_payload_type_error_e,
    controller_control_payload_type_init_e,
  }; // enum
#endif // _di_controller_control_payload_type_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_enumeration_control_h
