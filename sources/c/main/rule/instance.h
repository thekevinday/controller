/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the rule "instance" functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_rule_instance_h
#define _controller_main_rule_instance_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Process and execute the given rule.
 *
 * Any dependent rules are processed and executed as per "need", "want", and "wish" rule settings.
 * All dependent rules must be already loaded, this function will not load any rules.
 *
 * This requires that a read lock be set on instance->lock before being called.
 *
 * This function is recursively called for each "need", "want", and "wish", and has a max recursion length of the max size of the f_number_unsigneds_t array.
 *
 * The rule status will be updated by this function.
 *
 * @param instance
 *   The instance data for processing this rule.
 *
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *   F_child on child instance exiting.
 *   F_failure on execution failure.
 *
 *   F_interrupt (with error bit) on receiving a instance signal, such as an interrupt signal.
 *   F_lock (with error bit) if failed to re-establish read lock on instance->lock while returning.
 *
 *   Errors (with error bit) from: controller_lock_read().
 *   Errors (with error bit) from: controller_lock_write().
 */
#ifndef _di_controller_rule_instance_
  extern f_status_t controller_rule_instance(controller_instance_t * const instance);
#endif // _di_controller_rule_instance_

/**
 * Synchronously or asynchronously begin processing some rule.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 *
 *   This does not alter main.setting.state.status.
 * @param options_force
 *   Force the given instance options, only supporting a subset of instance options.
 *
 *   If controller_instance_option_asynchronous_e, then asynchronously execute.
 *   If not controller_instance_option_asynchronous_e, then synchronously execute.
 * @param alias_rule
 *   The alias of the rule, such as "boot/init".
 * @param action
 *   The action to perform based on the action type codes.
 * @param options
 *   The instance options to pass to the instance.
 * @param type
 *   The instance type, such as controller_instance_type_entry_e.
 * @param stack
 *   A stack representing the instances already running in this rule instance dependency tree.
 *   This is used to prevent circular dependencies.
 * @param cache
 *   A structure for containing and caching relevant data.
 *
 * @return
 *   F_okay on success.
 *   F_busy on success and the instance is found to already be running (nothing to do).
 *
 *   F_found_not (with error bit) if unable to for a instance for the given rule id.
 *   F_interrupt (with error bit) on receiving a process signal, such as an interrupt signal.
 *   F_recurse (with error bit) on recursion error (the instance is already on the instance stack).
 *
 *   Status from: controller_rule_instance().
 *
 *   Errors (with error bit) from: controller_rule_instance().
 *   Errors (with error bit) from: f_string_dynamic_append().
 *   Errors (with error bit) from: f_thread_create().
 *
 * @see controller_rule_instance()
 * @see f_string_dynamic_append()
 * @see f_thread_create()
 */
#ifndef _di_controller_rule_instance_begin_
  extern f_status_t controller_rule_instance_begin(controller_t * const main, const uint8_t options_force, const f_string_static_t alias_rule, const uint8_t action, const uint8_t options, const uint8_t type, const f_number_unsigneds_t stack, const controller_cache_t cache);
#endif // _di_controller_rule_instance_begin_

/**
 * Helper for calling controller_rule_instance().
 *
 * This does all the preparation work that needs to be synchronously performed within the same thread.
 * This will copy the rule by the alias to the instance structure.
 *
 * @param options_force
 *   Force the given instance options, only supporting a subset of instance options.
 *
 *   If controller_instance_option_asynchronous_e, then asynchronously execute.
 *   If not controller_instance_option_asynchronous_e, then synchronously execute.
 * @param instance
 *   The instance data.
 *
 * @return
 *   F_okay on success.
 *   F_found on the instance was found to already be running (nothing to do).
 *   F_process_not if the instance was not executed because it is a "consider" Action.
 *
 *   F_found_not (with error bit) if unable to for a instance for the given rule id.
 *   F_interrupt (with error bit) on receiving a process signal, such as an interrupt signal.
 *
 *   Status from: controller_rule_instance().
 *
 *   Errors (with error bit) from: controller_rule_copy().
 *   Errors (with error bit) from: controller_rule_instance().
 *
 * @see controller_rule_copy()
 * @see controller_rule_instance()
 * @see controller_rule_instance_begin()
 */
#ifndef _di_controller_rule_instance_do_
  extern f_status_t controller_rule_instance_do(const uint8_t options_force, controller_instance_t * const instance);
#endif // _di_controller_rule_instance_do_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_rule_instance_h
