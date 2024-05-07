/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides rule functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_rule_h
#define _controller_main_rule_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Copy a rule, allocating new space as necessary.
 *
 * This does not do any locking or unlocking for the rule data, be sure to lock appropriately before and after calling this.
 *
 * @param source
 *   The source rule to copy from.
 * @param destination
 *   The destination rule to copy to.
 *
 * @return
 *   F_okay on success.
 *
 *   Errors (with error bit) from: f_capability_copy().
 *   Errors (with error bit) from: f_control_group_copy().
 *   Errors (with error bit) from: f_iki_datas_append_all().
 *   Errors (with error bit) from: f_int32s_append_all().
 *   Errors (with error bit) from: f_limit_sets_copy().
 *   Errors (with error bit) from: f_string_dynamic_append().
 *   Errors (with error bit) from: f_string_dynamics_append_all().
 *   Errors (with error bit) from: f_string_maps_append_all().
 *
 *  @see f_capability_copy()
 *  @see f_control_group_copy()
 *  @see f_iki_datas_append_all()
 *  @see f_int32s_append_all()
 *  @see f_limit_sets_append()
 *  @see f_string_dynamic_append()
 *  @see f_string_dynamics_append_all()
 *  @see f_string_maps_append_all()
 */
#ifndef _di_controller_rule_copy_
  extern f_status_t controller_rule_copy(const controller_rule_t source, controller_rule_t *destination);
#endif // _di_controller_rule_copy_

/**
 * Find the location of the Rule by the Rule alias.
 *
 * @param alias
 *   The Rule alias to find.
 * @param rules
 *   The rules to search through.
 * @param at
 *   The index the rule was found at.
 *   (optional) Set to NULL to disable.
 *
 * @return
 *   F_okay on success, but the id.used is 0.
 *   F_true on success and rule was found, index is updated.
 *   F_false on success and rule was not found.
 */
#ifndef _di_controller_rule_find_
  extern f_status_t controller_rule_find(const f_string_static_t alias, const controller_rules_t rules, f_number_unsigned_t *at);
#endif // _di_controller_rule_find_

/**
 * Construct an id from two distinct strings found within a single given source.
 *
 * @param global
 *   The global data.
 * @param source
 *   The source string that both the directory and basename are copied from.
 * @param directory
 *   A range within the source representing the directory part of a rule id.
 * @param basename
 *   A range within the source representing the basename part of a rule id.
 * @param alias
 *   The constructed alias.
 *
 * @return
 *   F_okay on success.
 *
 *   Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *
 * @see f_string_append()
 * @see f_string_dynamic_partial_append_nulless()
 */
#ifndef _di_controller_rule_id_construct_
  extern f_status_t controller_rule_id_construct(controller_global_t * const global, const f_string_static_t source, const f_range_t directory, const f_range_t basename, f_string_dynamic_t * const alias);
#endif // _di_controller_rule_id_construct_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_rule_h
