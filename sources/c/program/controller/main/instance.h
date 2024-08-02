/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides instance functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_instance_h
#define _controller_main_instance_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Find an existing instance, for the given Rule Action.
 *
 * This does not do any locking or unlocking for the instances data, be sure to lock appropriately before and after calling this.
 *
 * @param action
 *   The Rule Action to find.
 * @param alias
 *   The Rule alias to find.
 * @param instances
 *   The array of instancees to.
 * @param at
 *   (optional) The location within instances the id was found.
 *
 *   Set to NULL to disable.
 *
 * @return
 *   F_okay if not given a valid id to search.
 *   F_false if there is no instance found.
 *   F_true if there is a instance found (address is stored in "at").
 */
#ifndef _di_controller_instance_find_
  f_status_t controller_instance_find(const f_number_unsigned_t action, const f_string_static_t alias, const controller_instances_t instances, f_number_unsigned_t * const at);
#endif // _di_controller_instance_find_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_instance_h
