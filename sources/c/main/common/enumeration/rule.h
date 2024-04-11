/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common rule enumerations.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_common_enumeration_rule_h
#define _controller_main_common_enumeration_rule_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Controller Rule Action execute type enumeration index.
 *
 * Execute type starts at 0 because it is intended to be used as an index within a static array.
 *
 * controller_rule_action_execute_type_*_e:
 *   - freeze:   The Freeze execution instructions.
 *   - kill:     The Kill execution instructions.
 *   - pause:    The Pause execution instructions.
 *   - reload:   The Reload execution instructions.
 *   - restart:  The Restart execution instructions.
 *   - resume:   The Resume execution instructions.
 *   - start:    The Start execution instructions.
 *   - stop:     The Stop execution instructions.
 *   - thaw:     The Thaw execution instructions.
 */
#ifndef _di_controller_rule_action_execute_type_e_
  enum {
    controller_rule_action_execute_type_freeze_e = 0,
    controller_rule_action_execute_type_kill_e,
    controller_rule_action_execute_type_pause_e,
    controller_rule_action_execute_type_reload_e,
    controller_rule_action_execute_type_restart_e,
    controller_rule_action_execute_type_resume_e,
    controller_rule_action_execute_type_start_e,
    controller_rule_action_execute_type_stop_e,
    controller_rule_action_execute_type_thaw_e,

    // Designate the largest value in the enum, the '__' is intentional.
    controller_rule_action_execute_type__enum_size_e,
  }; // enum
#endif // _di_controller_rule_action_execute_type_e_

/**
 * Controller Rule Action method enumeration.
 *
 * controller_rule_action_method_*_e:
 *   - none:          Nothing set.
 *   - extended:      Designate that this Action is represented using FSS Extended.
 *   - extended_list: Designate that this Action is represented using FSS Extended List.
 */
#ifndef _di_controller_rule_action_method_e_
  enum {
    controller_rule_action_method_none_e = 0,
    controller_rule_action_method_extended_e,
    controller_rule_action_method_extended_list_e,
  }; // enum
#endif // _di_controller_rule_action_method_e_

/**
 * Controller Rule Action type enumeration.
 *
 * controller_rule_action_type_*_e:
 *   - none:     Nothing set.
 *   - freeze:   The Freeze execution instructions.
 *   - group:    The Group setting.
 *   - kill:     The Kill execution instructions.
 *   - pause:    The Pause execution instructions.
 *   - pid_file: The PID file setting.
 *   - rerun:    The Re-run execution after success or failure.
 *   - reload:   The Reload execution instructions.
 *   - restart:  The Restart execution instructions.
 *   - resume:   The Resume execution instructions.
 *   - start:    The Start execution instructions.
 *   - stop:     The Stop execution instructions.
 *   - thaw:     The Thaw execution instructions.
 *   - user:     The User setting.
 *   - with:     The With flags.
 */
#ifndef _di_controller_rule_action_type_e_
  enum {
    controller_rule_action_type_none_e = 0,
    controller_rule_action_type_freeze_e,
    controller_rule_action_type_group_e,
    controller_rule_action_type_kill_e,
    controller_rule_action_type_pause_e,
    controller_rule_action_type_pid_file_e,
    controller_rule_action_type_reload_e,
    controller_rule_action_type_rerun_e,
    controller_rule_action_type_restart_e,
    controller_rule_action_type_resume_e,
    controller_rule_action_type_start_e,
    controller_rule_action_type_stop_e,
    controller_rule_action_type_thaw_e,
    controller_rule_action_type_user_e,
    controller_rule_action_type_with_e,

    // Designate the largest value in the enum, the '__' is intentional.
    controller_rule_action_type__enum_size_e,
  }; // enum
#endif // _di_controller_rule_action_type_e_

/**
 * Controller Rule Item type enumeration.
 *
 * controller_rule_item_type_*_e:
 *   - none:     Nothing set.
 *   - command:  The item type represents a command operation.
 *   - script:   The item type represents a script operation.
 *   - service:  The item type represents a service operation.
 *   - settings: The item type represents a setting operation.
 *   - utility:  The item type represents a utility operation.
 */
#ifndef _di_controller_rule_item_type_e_
  enum {
    controller_rule_item_type_none_e = 0,
    controller_rule_item_type_command_e,
    controller_rule_item_type_script_e,
    controller_rule_item_type_service_e,
    controller_rule_item_type_settings_e,
    controller_rule_item_type_utility_e,
  }; // enum
#endif // _di_controller_rule_item_type_e_

/**
 * Contoller Rule setting type enumeration.
 *
 * controller_rule_setting_type_*_e:
 *   - none:             Nothing set.
 *   - affinity:         Setting type representing a affinity.
 *   - capability:       Setting type representing a capability.
 *   - cgroup:           Setting type representing a control group.
 *   - define:           Setting type representing a define.
 *   - engine:           Setting type representing a engine.
 *   - engine_arguments: Setting type representing a engine.
 *   - environment:      Setting type representing a environment.
 *   - group:            Setting type representing a group.
 *   - limit:            Setting type representing a limit.
 *   - name:             Setting type representing a name.
 *   - nice:             Setting type representing a nice.
 *   - on:               Setting type representing a on.
 *   - parameter:        Setting type representing a parameter.
 *   - path:             Setting type representing a path.
 *   - scheduler:        Setting type representing a scheduler.
 *   - user:             Setting type representing a user.
 */
#ifndef _di_controller_rule_setting_type_e_
  enum {
    controller_rule_setting_type_none_e = 0,
    controller_rule_setting_type_affinity_e,
    controller_rule_setting_type_capability_e,
    controller_rule_setting_type_cgroup_e,
    controller_rule_setting_type_define_e,
    controller_rule_setting_type_engine_e,
    controller_rule_setting_type_environment_e,
    controller_rule_setting_type_group_e,
    controller_rule_setting_type_limit_e,
    controller_rule_setting_type_name_e,
    controller_rule_setting_type_nice_e,
    controller_rule_setting_type_on_e,
    controller_rule_setting_type_parameter_e,
    controller_rule_setting_type_path_e,
    controller_rule_setting_type_scheduler_e,
    controller_rule_setting_type_timeout_e,
    controller_rule_setting_type_user_e,
  }; // enum
#endif // _di_controller_rule_setting_type_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_enumeration_rule_h
