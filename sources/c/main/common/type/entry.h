/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common entry type structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_common_type_entry_h
#define _controller_main_common_type_entry_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Controller Entry Item Action.
 *
 * type:       The type of Action.
 * code:       A single code or sub-type associated with the Action.
 * flag:       A set of flags to describe special behavior for the given type and code (flags may be different per type and code).
 * line:       The line number where the Entry Item begins.
 * number:     The unsigned number that some types use instead of the "parameters".
 * status:     The overall status.
 * parameters: The values associated with the Action.
 */
#ifndef _di_controller_entry_action_t_
  typedef struct {
    uint8_t type;
    uint8_t code;
    uint8_t flag;

    f_number_unsigned_t line;
    f_number_unsigned_t number;

    f_status_t status;

    f_string_dynamics_t parameters;
  } controller_entry_action_t;

  #define controller_entry_action_t_initialize { \
    0, \
    0, \
    0, \
    controller_entry_action_flag_none_e, \
    0, \
    F_known_not, \
    f_string_dynamics_t_initialize, \
  }
#endif // _di_controller_entry_action_t_

/**
 * Controller Entry Item Actions.
 *
 * array: An array of Entry Item Actions.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_controller_entry_actions_t_
  typedef struct {
    controller_entry_action_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } controller_entry_actions_t;

  #define controller_entry_actions_t_initialize { \
    0, \
    0, \
    0, \
  }
#endif // _di_controller_entry_actions_t_

/**
 * Controller Entry Item.
 *
 * line:    The line number where the Entry Item begins.
 * name:    The name of the Entry Item.
 * actions: The Actions associated with the Entry Item.
 */
#ifndef _di_controller_entry_item_t_
  typedef struct {
    f_number_unsigned_t line;
    f_string_dynamic_t name;

    controller_entry_actions_t actions;
  } controller_entry_item_t;

  #define controller_entry_item_t_initialize \
    { \
      0, \
      f_string_dynamic_t_initialize, \
      controller_entry_actions_t_initialize, \
    }
#endif // _di_controller_entry_item_t_

/**
 * Controller Entry Items.
 *
 * array: An array of Entry Items.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_controller_entry_items_t_
  typedef struct {
    controller_entry_item_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } controller_entry_items_t;

  #define controller_entry_items_t_initialize { \
    0, \
    0, \
    0, \
  }

  #define macro_controller_entry_items_t_clear(items) \
    items.array = 0; \
    items.size = 0; \
    items.used = 0;
#endif // _di_controller_entry_items_t_

/**
 * Controller Entry (or Exit).
 *
 * Entry and Exit files are essentially the same structure with minor differences in settings and behavior.
 * The structure is identical and due to lacking any particularly good name to represent both "entry" or "exit", the name "entry" is being used for both.
 *
 * define:        Any defines (environment variables) made available to all Rules in this entry for IKI substitution or just as environment variables.
 * flag:          A set of flags, primarily used to designate that timeouts are disabled.
 * items:         The array of entry items.
 * parameter:     Any parameters made available to all Rules in this entry for IKI substitution.
 * pid:           The PID file generation setting.
 * session:       The default session settings (when NULL, no default is specified).
 * show:          The show setting for controlling what to show when executing entry items and rules.
 * status:        The overall status.
 * timeout_exit:  The timeout to wait when exiting the Controller program after sending the terminate signal to send the kill signal.
 * timeout_kill:  The timeout to wait relating to using a kill signal.
 * timeout_start: The timeout to wait relating to starting a process.
 * timeout_stop:  The timeout to wait relating to stopping a process.
 */
#ifndef _di_controller_entry_t_
  typedef struct {
    f_status_t status;

    uint8_t pid;
    uint8_t session;
    uint8_t show;
    uint8_t flag;

    f_number_unsigned_t timeout_exit;
    f_number_unsigned_t timeout_kill;
    f_number_unsigned_t timeout_start;
    f_number_unsigned_t timeout_stop;

    f_string_maps_t define;
    f_string_maps_t parameter;

    controller_entry_items_t items;
  } controller_entry_t;

  #define controller_entry_t_initialize { \
    F_known_not, \
    controller_entry_pid_require_e, \
    0, \
    0, \
    0, \
    controller_main_thread_exit_timeout_d, \
    0, \
    0, \
    0, \
    f_string_maps_t_initialize, \
    f_string_maps_t_initialize, \
    controller_entry_items_t_initialize, \
  }
#endif // _di_controller_entry_t_

/**
 * Delete the Controller Entry Action data.
 *
 * @param actions
 *   The Controller Entry Action.
 *
 * @see f_memory_arrays_resize()
 */
#ifndef _di_controller_entry_action_delete_
  extern void controller_entry_action_delete(controller_entry_action_t * const action);
#endif // _di_controller_entry_action_delete_

/**
 * Delete the Controller Entry Actions data.
 *
 * @param actions
 *   The Controller Entry Actions.
 *
 * @see controller_entry_action_delete()
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_controller_entry_actions_delete_
  extern void controller_entry_actions_delete(controller_entry_actions_t * const actions);
#endif // _di_controller_entry_actions_delete_

/**
 * Delete the Controller Entry Item data.
 *
 * @param item
 *   The Controller Entry Item.
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_controller_entry_item_delete_
  extern void controller_entry_item_delete(controller_entry_item_t * const item);
#endif // _di_controller_entry_item_delete_

/**
 * Delete the Controller Entry Items data.
 *
 * @param items
 *   The Controller Entry Items.
 *
 * @see controller_entry_item_delete()
 * @see f_memory_delete()
 */
#ifndef _di_controller_entry_items_delete_
  extern void controller_entry_items_delete(controller_entry_items_t * const items);
#endif // _di_controller_entry_items_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_type_entry_h
