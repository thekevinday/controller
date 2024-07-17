/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the Rule "execute" functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_rule_execute_h
#define _controller_main_rule_execute_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform an execution of the given Rule.
 *
 * This requires that a read lock be set on instance->lock before being called.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 *
 *   This does not alter main.setting.state.status.
 * @param instance
 *   The instance data.
 *
 *   Must not be NULL.
 * @param action
 *   The Action to perform based on the Action type codes.
 *
 *   Only subset of the Action type codes are supported:
 *   - controller_rule_action_type_kill_e
 *   - controller_rule_action_type_pause_e
 *   - controller_rule_action_type_reload_e
 *   - controller_rule_action_type_restart_e
 *   - controller_rule_action_type_resume_e
 *   - controller_rule_action_type_start_e
 *   - controller_rule_action_type_stop_e
 * @param options
 *   Process options to consider when executing.
 *   If bit controller_instance_option_simulate_e, then the Rule execution is in simulation mode (printing a message that the Rule would be executed but does not execute the rule).
 *
 * @return
 *   F_okay on success.
 *   F_child on child process exiting.
 *   F_ignore if the Rule is unknown and nothing can be done.
 *
 *   F_failure (with error bit) if failed to execute.
 *   F_interrupt (with error bit) on receiving a process signal, such as an interrupt signal.
 *   F_lock (with error bit) if failed to establish a lock, and the instance->lock read lock is already restored.
 *   F_lock_read (with error bit) if failed to re-establish read lock on instance->lock while returning.
 *
 *   On success and the Rule is run synchronously, then the individual status for the Rule is set to F_complete.
 *   On success and the Rule is run asynchronously, then the individual status for the Rule is set to F_busy.
 *   On failure, the individual status for the Rule is set to an appropriate error status.
 */
#ifndef _di_controller_rule_execute_
  extern f_status_t controller_rule_execute(controller_t * const main, controller_instance_t * const instance, const uint8_t action, const uint8_t options);
#endif // _di_controller_rule_execute_

/**
 * Perform an execution of the given Rule in the foreground.
 *
 * This requires that a read lock be set on instance->lock before being called.
 *
 * @param instance
 *   The instance data.
 *
 *   Must not be NULL.
 * @param type
 *   The item type code.
 * @param program
 *   The program to use (such as "bash").
 * @param arguments
 *   The arguments to pass to the program.
 * @param options
 *   Process options to consider when executing.
 *   If bit controller_instance_option_simulate_e, then the Rule execution is in simulation mode (printing a message that the Rule would be executed but does not execute the rule).
 * @param execute_set
 *   The execute parameter and as settings.
 *
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *   F_child on child process exiting.
 *
 *   F_interrupt (with error bit) on receiving a process signal, such as an interrupt signal.
 *   F_lock (with error bit) if failed to establish a lock, and the instance->lock read lock is already restored.
 *   F_lock_read (with error bit) if failed to re-establish read lock on instance->lock while returning.
 *
 *   Errors (with error bit) from: fll_execute_program().
 *
 * @see fll_execute_program()
 */
#ifndef _di_controller_rule_execute_foreground_
  extern f_status_t controller_rule_execute_foreground(controller_instance_t * const instance, const uint8_t type, const f_string_static_t program, const f_string_statics_t arguments, const uint8_t options, controller_execute_set_t * const execute_set);
#endif // _di_controller_rule_execute_foreground_

/**
 * Find the next available child slot and return a pointer to that location.
 *
 * @param instance
 *   The instance data.
 *
 *   instance.childs.used is incremented on success if the last available position is at the "used" position in the array.
 *
 *   Must not be NULL.
 *
 * @return
 *   A pointer the next avialable child pid_t slot in the instance.
 *
 *   NULL on error.
 */
#ifndef _di_controller_rule_execute_next_child_
  extern pid_t * controller_rule_execute_next_child(controller_instance_t * const instance);
#endif // _di_controller_rule_execute_next_child_

/**
 * Find the next available PID path slot and return a pointer to that location.
 *
 * @param instance
 *   The instance data.
 *
 *   instance.path_pids.used is incremented on success if the last available position is at the "used" position in the array.
 *
 *   Must not be NULL.
 *
 * @return
 *   A pointer the next avialable PID path f_string_dynamic_t slot in the instance.
 *
 *   NULL on error.
 */
#ifndef _di_controller_rule_execute_next_pid_path_
  extern f_string_dynamic_t * controller_rule_execute_next_pid_path(controller_instance_t * const instance);
#endif // _di_controller_rule_execute_next_pid_path_

/**
 * Perform an execution of the given Rule in the foreground or background and creating a PID file.
 *
 * This requires that a read lock be set on instance->lock before being called.
 *
 * When this is synchronous, this will wait for the PID file to be generated before continuing.
 * When this is asynchronous, this will continue on adding the Rule id and Action to the asynchronous list.
 *
 * @param instance
 *   The instance data.
 *
 *   Must not be NULL.
 * @param pid_file
 *   The path to the PID file.
 * @param type
 *   The item type code.
 * @param program
 *   The program to use (such as "bash").
 * @param arguments
 *   The arguments to pass to the program.
 * @param options
 *   Process options to consider when executing.
 *   If bit controller_instance_option_simulate_e, then the Rule execution is in simulation mode (printing a message that the Rule would be executed but does not execute the rule).
 * @param with
 *   The "with" option flags.
 * @param execute_set
 *   The execute parameter and as settings.
 *
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *   F_child on child process exiting.
 *
 *   F_file_found (with error bit) if the PID file already exists.
 *   F_interrupt (with error bit) on receiving a process signal, such as an interrupt signal.
 *   F_lock (with error bit) if failed to establish a lock, and the instance->lock read lock is already restored.
 *   F_lock_read (with error bit) if failed to re-establish read lock on instance->lock while returning.
 *
 *   Errors (with error bit) from: fll_execute_program().
 *
 * @see fll_execute_program()
 */
#ifndef _di_controller_rule_execute_pid_with_
  extern f_status_t controller_rule_execute_pid_with(controller_instance_t * const instance, const f_string_dynamic_t pid_file, const uint8_t type, const f_string_static_t program, const f_string_statics_t arguments, const uint8_t options, const uint8_t with, controller_execute_set_t * const execute_set);
#endif // _di_controller_rule_execute_pid_with_

/**
 * Determine whether or not an execute Rule should be re-run, applying a delay as requested.
 *
 * @param instance
 *   The instance data for processing this Rule.
 *
 *   Must not be NULL.
 * @param item
 *   The Rule Item being executed.
 *
 *   Must not be NULL.
 * @param action
 *   The Action type.
 *
 * @return
 *   A positive number to designate re-run.
 *   0 to designate do not re-run.
 *   -1 to designate an error from nanosleep(), with errno set to values like:
 *     - EFAULT: Designates that there was a problem copying information from user space.
 *     - EINTR:  Consider this having returned F_interrupt.
 *     - EINVAL: Consider this having returned F_status_set_error(F_parameter);
 *   -2 to designate exit due to signal/disabled thread.
 */
#ifndef _di_controller_rule_execute_rerun_
  extern int8_t controller_rule_execute_rerun(controller_instance_t * const instance, controller_rule_item_t * const item, const uint8_t action);
#endif // _di_controller_rule_execute_rerun_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_rule_execute_h
