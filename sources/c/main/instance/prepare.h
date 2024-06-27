/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the instance prepare functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_instance_prepare_h
#define _controller_main_instance_prepare_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Prepare the instance.
 *
 * The instance is initialized with the instance id, the rule alias, and the rule action type.
 * These are the necessary parts for uniquely identifying the instance.
 *
 * If a instance by the given Rule alias and Rule Action already exists, then nothing is done.
 *
 * This requires that a main.thread.lock.instance lock be set on instance.lock before being called.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 * @param is_normal
 *   If TRUE, then instance as if this operates during a normal operation (entry and control).
 *   If FALSE, then instance as if this operates during a an exit operation.
 * @param action
 *   The Rule Action to use.
 * @param alias
 *   The Rule alias to use.
 * @param id
 *   (optional) The instance ID when found or created.
 *
 *   Set to NULL to not use.
 *
 * @return
 *   F_okay on success.
 *   F_found on success, but nothing was done because an existing instance was found.
 *
 *   F_lock (with error bit) if failed to re-establish read lock on main.thread.lock.instance while returning.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamic_append().
 *
 *   Errors (with error bit) from: controller_lock_read().
 *   Errors (with error bit) from: controller_lock_write().
 *
 * @see f_string_dynamic_append()
 * @see controller_lock_read()
 * @see controller_lock_write()
 */
#ifndef _di_controller_instance_prepare_
  extern f_status_t controller_instance_prepare(controller_t * const main, const uint8_t is_normal, const uint8_t action, const f_string_static_t alias, f_number_unsigned_t *id);
#endif // _di_controller_instance_prepare_

/**
 * Prepare the instance for some instance type.
 *
 * The instance is initialized with the instance id, the rule alias, and the rule action type.
 * These are the necessary parts for uniquely identifying the instance.
 *
 * If a instance by the given Rule alias and Rule Action already exists, then nothing is done.
 *
 * This requires that a main.thread.lock.instance lock be set on instance->lock before being called.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 * @param type
 *   The instance type to use when checking if thread is enabled.
 * @param action
 *   The Rule Action to use.
 * @param alias
 *   The Rule alias to use.
 * @param id
 *   (optional) The instance ID when found or created.
 *
 *   Set to NULL to not use.
 *
 * @return
 *   Success from: controller_instance_prepare()
 *
 *   Errors (with error bit) from: controller_instance_prepare().
 *
 * @see controller_instance_prepare()
 */
#ifndef _di_controller_instance_prepare_instance_type_
  extern f_status_t controller_instance_prepare_instance_type(controller_t * const main, const uint8_t type, const uint8_t action, const f_string_static_t alias, f_number_unsigned_t *id);
#endif // _di_controller_instance_prepare_instance_type_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_instance_prepare_h
