/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common process type structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_common_type_process_h
#define _controller_main_common_type_process_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Controller program process data.
 *
 * The typedef for this is located in the defs.h header.
 *
 * Properties:
 *   - flag:  Flags from controller_process_flag_*_e.
 *   - ready: State representing if the settings are all loaded and is ready to run program operations.
 *   - mode:  Controller setting mode based on the setting mode enumerator.
 *
 *   - failsafe_item_id: The Entry Item ID to execute when failsafe execution is enabled.
 *
 *   - name_entry:   The name of the Entry file.
 *   - path_cgroup:  Directory path to the cgroup directory.
 *   - path_control: File path to the control socket (used for printing the path).
 *   - path_current: The current path.
 *   - path_pid:     File path to the PID file.
 *   - path_setting: File path to the setting directory.
 *
 *   - control: The control socket data.
 *   - entry:   The Entry settings.
 *   - exit:    The Exit settings.
 *   - rules:   All rules and their respective settings.
 */
#ifndef _di_controller_process_t
  struct controller_process_t_ {
    uint8_t flag;
    uint8_t ready;
    uint8_t mode;

    f_number_unsigned_t failsafe_item_id;

    f_string_dynamic_t name_entry;
    f_string_dynamic_t path_cgroup;
    f_string_dynamic_t path_control;
    f_string_dynamic_t path_current;
    f_string_dynamic_t path_pid;
    f_string_dynamic_t path_setting;

    controller_control_t control;
    controller_entry_t entry;
    controller_entry_t exit;
    controller_rules_t rules;
  };

  #define controller_process_t_initialize { \
    0, \
    0, \
    0, \
    0, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    controller_control_t_initialize, \
    macro_controller_entry_t_initialize_1(controller_entry_flag_is_e), \
    controller_entry_t_initialize, \
    controller_rules_t_initialize, \
  }
#endif // _di_controller_process_t

/**
 * Delete the Controller process data.
 *
 * @param process
 *   A pointer to the current process data.
 *
 *   Must not be NULL.
 */
#ifndef _di_controller_process_delete_
  extern void controller_process_delete(controller_process_t * const process);
#endif // _di_controller_process_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_type_process_h
