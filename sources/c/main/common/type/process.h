/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common type process structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_common_type_process_h
#define _controller_main_common_type_process_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Controller process data.
 *
 * ready:            State representing if the settings are all loaded and is ready to run program operations.
 * mode:             Controller setting mode based on the setting mode enumerator.
 * control:          The control socket data.
 * failsafe_item_id: The Entry Item ID to execute when failsafe execution is enabled.
 * path_cgroup:      Directory path to the cgroup directory.
 * path_control:     File path to the control socket (used for printing the path).
 * path_pid:         File path to the PID file.
 * path_setting:     File path to the setting directory.
 * entry:            The Entry settings.
 * rules:            All rules and their respective settings.
 */
#ifndef _di_controller_process_t_
  typedef struct {
    uint8_t ready;
    uint8_t mode;

    f_number_unsigned_t failsafe_item_id;

    controller_control_t control;

    f_string_dynamic_t path_cgroup;
    f_string_dynamic_t path_control;
    f_string_dynamic_t path_current;
    f_string_dynamic_t path_pid;
    f_string_dynamic_t path_setting;

    f_string_dynamic_t name_entry;

    controller_entry_t entry;
    controller_entry_t exit;
    controller_rules_t rules;
  } controller_process_t;

  #define controller_process_t_initialize { \
    0, \
    0, \
    0, \
    0, \
    controller_control_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    controller_entry_t_initialize, \
    controller_entry_t_initialize, \
    controller_rules_t_initialize, \
  }
#endif // _di_controller_process_t_

/**
 * Delete the Controller process data.
 *
 * @param process
 *   The controller process data.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_controller_process_delete_
  extern f_status_t controller_process_delete(controller_process_t * const process);
#endif // _di_controller_process_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_type_process_h
