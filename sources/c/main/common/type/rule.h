/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common rules type structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_common_type_rule_h
#define _controller_main_common_type_rule_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The Rule "rerun" item for controlling re-execution.
 *
 * Properties:
 *   - count: A count of the number of executions.
 *   - delay: The time to wait before attempting to re-run.
 *   - max:   The maximum number of times to re-run (with 0 representing re-run infinitely) for executions.
 */
#ifndef _di_controller_rule_rerun_item_t_
  typedef struct {
    uint8_t reset;

    f_number_unsigned_t count;
    f_number_unsigned_t delay;
    f_number_unsigned_t max;
  } controller_rule_rerun_item_t;

  #define controller_rule_rerun_item_initialize { \
    F_false, \
    0, \
    5000, \
    0, \

  #define macro_controller_rule_rerun_item_initialize(item) { \
    item.reset = F_false; \
    item.count = 0; \
    item.delay = 5000; \
    item.max = 0; \
  }
#endif // _di_controller_rule_rerun_item_t_

/**
 * The Rule "rerun" values for controlling re-execution.
 *
 * Properties:
 *   - is:            A bitwise set of options to designate whether rerun is enabled or not and other options.
 *   - count_failure: A count of the number of failed executions.
 *   - count_success: A count of the number of successful executions.
 *   - delay_failure: The time to wait before attempting to "rerun" for failed executions.
 *   - delay_success: The time to wait before attempting to "rerun" for successful executions.
 *   - max_failure:   The maximum number of times to "rerun" (with 0 representing "rerun" infinitely) for failed executions.
 *   - max_success:   The maximum number of times to "rerun" (with 0 representing "rerun" infinitely) for successful executions.
 */
#ifndef _di_controller_rule_rerun_t_
  typedef struct {
    uint8_t is;

    controller_rule_rerun_item_t failure;
    controller_rule_rerun_item_t success;
  } controller_rule_rerun_t;

  #define controller_rule_rerun_initialize { \
    0, \
    controller_rule_rerun_item_initialize, \
    controller_rule_rerun_item_initialize, \
  }
#endif // _di_controller_rule_rerun_t_

/**
 * Controller Rule Action.
 *
 * Properties:
 *   - type:       The Rule Action type.
 *   - line:       The line number where the Rule Action begins.
 *   - status:     The last execution status of the Rule Action.
 *   - parameters: All parameters associated with the Rule Action.
 */
#ifndef _di_controller_rule_action_t_
  typedef struct {
    uint8_t type;
    f_number_unsigned_t line;
    f_status_t status;

    f_string_dynamics_t parameters;
    f_iki_datas_t ikis;
  } controller_rule_action_t;

  #define controller_rule_action_t_initialize { \
    0, \
    0, \
    F_known_not, \
    f_string_dynamics_t_initialize, \
    f_iki_datas_t_initialize, \
  }
#endif // _di_controller_rule_action_t_

/**
 * Controller Rule Actions.
 *
 * Properties:
 *   - array: An array of Rule Actions.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_controller_rule_actions_t_
  typedef struct {
    controller_rule_action_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } controller_rule_actions_t;

  #define controller_rule_actions_t_initialize { \
    0, \
    0, \
    0, \
  }
#endif // _di_controller_rule_actions_t_

/**
 * Controller Rule Item.
 *
 * Properties:
 *   - type:    The type of the Rule Item.
 *   - with:    A bitwise number representing execute "with" options.
 *   - line:    The line number where the Rule Item begins.
 *   - reruns:  An array designating rerun settings for each execution type available.
 *   - actions: The actions associated with the Rule Item.
 */
#ifndef _di_controller_rule_item_t_
  typedef struct {
    uint8_t type;
    uint8_t with;
    f_number_unsigned_t line;

    f_string_dynamic_t pid_file;
    controller_rule_rerun_t reruns[controller_rule_action_execute_type__enum_size_e];
    controller_rule_actions_t actions;
  } controller_rule_item_t;

  #define controller_rule_item_t_initialize \
    { \
      0, \
      0, \
      0, \
      f_string_dynamic_t_initialize, \
      { \
        controller_rule_rerun_t_initialize, \
        controller_rule_rerun_t_initialize, \
        controller_rule_rerun_t_initialize, \
        controller_rule_rerun_t_initialize, \
        controller_rule_rerun_t_initialize, \
        controller_rule_rerun_t_initialize, \
        controller_rule_rerun_t_initialize, \
        controller_rule_rerun_t_initialize, \
        controller_rule_rerun_t_initialize, \
      }, \
      controller_rule_actions_t_initialize, \
    }
#endif // _di_controller_rule_item_t_

/**
 * Controller Rule Items.
 *
 * Properties:
 *   - array: An array of Rule Items.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_controller_rule_items_t_
  typedef struct {
    controller_rule_item_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } controller_rule_items_t;

  #define controller_rule_items_initialize { \
    0, \
    0, \
    0, \
  }
#endif // _di_controller_rule_items_t_

/**
 * The Rule "on" values for designating dependencies.
 *
 * Properties:
 *   - action: The Rule Action type this "on" dependencies are associated with.
 *   - need:   The Rule Alias for a required Rule.
 *   - want:   The Rule Alias for an optional Rule that is required to succeed if found.
 *   - wish:   The Rule Alias for an optional Rule that is not required.
 */
#ifndef _di_controller_rule_on_t_
  typedef struct {
    uint8_t action;

    f_string_dynamics_t need;
    f_string_dynamics_t want;
    f_string_dynamics_t wish;
  } controller_rule_on_t;

  #define controller_rule_on_initialize { \
    0, \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
  }
#endif // _di_controller_rule_on_t_

/**
 * The Rule "on" array.
 *
 * Properties:
 *   - array: An array of Rule "on" values.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_controller_rule_ons_t_
  typedef struct {
    controller_rule_on_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } controller_rule_ons_t;

  #define controller_rule_ons_t_initialize { \
    0, \
    0, \
    0, \
  }
#endif // _di_controller_rule_ons_t_

/**
 * Controller Rule.
 *
 * Properties:
 *   - affinity:         The cpu affinity to be used when executing the Rule.
 *   - alias:            The distinct ID (machine name) of the Rule, such as "service/ssh".
 *   - capability:       The capability setting if the Rule "has" a capability.
 *   - cgroup:           The control group setting if the Rule "has" a control group.
 *   - define:           Any defines (environment variables) made available to the Rule for IKI substitution or just as environment variables.
 *   - engine:           The program or path to the program of the scripting engine to use when processing scripts in this Rule.
 *   - engine_arguments: Any arguments to pass to the engine program.
 *   - environment:      All environment variables allowed to be exposed to the Rule when processing.
 *   - group:            The group ID if the Rule "has" a group.
 *   - groups:           A set of group IDs to run the process with (first specified group is the primary group).
 *   - has:              Bitwise set of "has" codes representing what the Rule has.
 *   - items:            All items associated with the Rule.
 *   - limits:           The cpu/resource limits to use when executing the Rule.
 *   - name:             A human name for the Rule (does not have to be distinct), such as "Bash Script".
 *   - nice:             The niceness value if the Rule "has" nice.
 *   - on:               A set of parameters for defining dependencies and how they are needed, wanted, or wished for.
 *   - parameter:        Any parameters made available to the Rule for IKI substitution.
 *   - path:             The path to the Rule file.
 *   - scheduler:        The scheduler setting if the Rule "has" a scheduler.
 *   - status:           A set of action-specific success/failure status of the Rule. Each index represents a controller_rule_action_type_* enum value. Index 0 represents a global status.
 *   - timeout_exit:     The timeout to wait when exiting the Controller program after sending the terminate signal to send the kill signal.
 *   - timeout_kill:     The timeout to wait relating to using a kill signal.
 *   - timeout_start:    The timeout to wait relating to starting a process.
 *   - timeout_stop:     The timeout to wait relating to stopping a process.
 *   - timestamp:        The timestamp when the Rule was loaded.
 *   - user:             The User ID if the Rule "has" a user.
 */
#ifndef _di_controller_rule_t_
  typedef struct {
    f_status_t status[controller_rule_action_type__enum_size_e];

    f_number_unsigned_t timeout_kill;
    f_number_unsigned_t timeout_start;
    f_number_unsigned_t timeout_stop;

    uint8_t has;
    int nice;
    uid_t user;
    gid_t group;

    f_time_simple_t timestamp;

    f_string_dynamic_t alias;
    f_string_dynamic_t engine;
    f_string_dynamic_t name;
    f_string_dynamic_t path;

    f_string_maps_t define;
    f_string_maps_t parameter;

    f_string_dynamics_t engine_arguments;
    f_string_dynamics_t environment;

    f_int32s_t affinity;
    f_capability_t capability;
    f_control_group_t cgroup;
    f_int32s_t groups;
    f_limit_sets_t limits;
    f_execute_scheduler_t scheduler;

    controller_rule_ons_t ons;
    controller_rule_items_t items;
  } controller_rule_t;

  #define controller_rule_t_initialize { \
      { \
        F_known_not, \
        F_known_not, \
        F_known_not, \
        F_known_not, \
        F_known_not, \
        F_known_not, \
        F_known_not, \
        F_known_not, \
        F_known_not, \
        F_known_not, \
        F_known_not, \
        F_known_not, \
        F_known_not, \
        F_known_not, \
        F_known_not, \
      }, \
    0, \
    0, \
    0, \
    0, \
    0, \
    0, \
    0, \
    f_time_simple_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_maps_t_initialize, \
    f_string_maps_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_int32s_t_initialize, \
    f_capability_t_initialize, \
    f_control_group_t_initialize, \
    f_int32s_t_initialize, \
    f_limit_sets_t_initialize, \
    f_execute_scheduler_t_initialize, \
    controller_rule_ons_initialize, \
    controller_rule_items_initialize, \
  }
#endif // _di_controller_rule_t_

/**
 * Controller Rules.
 *
 * Properties:
 *   - array: An array of Rules.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_controller_rules_t_
  typedef struct {
    controller_rule_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } controller_rules_t;

  #define controller_rules_t_initialize { \
    0, \
    0, \
    0, \
  }
#endif // _di_controller_rules_t_

/**
 * Fully de-allocate all memory for the given Rule without caring about return status.
 *
 * @param rule
 *   The rule to de-allocate.
 *
 * @see f_capability_delete()
 * @see f_memory_array_resize()
 * @see f_memory_arrays_resize()
 */
#ifndef _di_controller_rule_delete_
  extern void controller_rule_delete(controller_rule_t * const rule);
#endif // _di_controller_rule_delete_

/**
 * Delete the Controller Rule Action data.
 *
 * @param action
 *   The Rule Action data.
 *
 * @see f_memory_array_resize()
 * @see f_memory_arrays_resize()
 */
#ifndef _di_controller_rule_action_delete_
  extern void controller_rule_action_delete(controller_rule_action_t * const action);
#endif // _di_controller_rule_action_delete_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an controller_rule_actions_t structure.
 *
 * This is only called when shrinking the array and generally should perform de-allocations.
 *
 * This does not do parameter checking.
 *
 * @param start
 *   The inclusive start position in the array to start deleting.
 * @param stop
 *   The exclusive stop position in the array to stop deleting.
 * @param array
 *   The array structure to delete all values of.
 *
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see controller_rule_action_delete()
 */
#ifndef _di_controller_rule_actions_delete_callback_
  extern f_status_t controller_rule_actions_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_controller_rule_actions_delete_callback_

/**
 * Delete the Controller Rule Item data.
 *
 * @param item
 *   The Rule Item data.
 *
 * @see controller_rule_actions_delete()
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_controller_rule_item_delete_
  extern void controller_rule_item_delete(controller_rule_item_t * const item);
#endif // _di_controller_rule_item_delete_
/**
 * A callback intended to be passed to f_memory_arrays_resize() for an controller_rule_items_t structure.
 *
 * This is only called when shrinking the array and generally should perform de-allocations.
 *
 * This does not do parameter checking.
 *
 * @param start
 *   The inclusive start position in the array to start deleting.
 * @param stop
 *   The exclusive stop position in the array to stop deleting.
 * @param array
 *   The array structure to delete all values of.
 *
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see controller_rule_item_delete()
 */
#ifndef _di_controller_rule_items_delete_callback_
  extern f_status_t controller_rule_items_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_controller_rule_items_delete_callback_

/**
 * Delete the Controller Rule "on" data.
 *
 * @param on
 *   The Rule "on" data.
 *
 * @see f_memory_arrays_resize()
 */
#ifndef _di_controller_rule_on_delete_
  extern void controller_rule_on_delete(controller_rule_on_t * const on);
#endif // _di_controller_rule_on_delete_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an controller_rule_ons_t structure.
 *
 * This is only called when shrinking the array and generally should perform de-allocations.
 *
 * This does not do parameter checking.
 *
 * @param start
 *   The inclusive start position in the array to start deleting.
 * @param stop
 *   The exclusive stop position in the array to stop deleting.
 * @param array
 *   The array structure to delete all values of.
 *
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see controller_rule_on_delete()
 */
#ifndef _di_controller_rule_ons_delete_callback_
  extern f_status_t controller_rule_ons_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_controller_rule_ons_delete_callback_

/**
 * Delete the Controller Rules data.
 *
 * @param rules
 *   The Controller Rules data.
 *
 * @see controller_rules_resize()
 */
#ifndef _di_controller_rules_delete_
  extern void controller_rules_delete(controller_rules_t * const rules);
#endif // _di_controller_rules_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_type_rule_h
