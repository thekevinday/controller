/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the rule "read" functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_rule_read_h
#define _controller_main_rule_read_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Read the rule file, extracting all valid items.
 *
 * @param global
 *   The global data.
 *   Must not be NULL.
 *
 *   This does not alter global.main.setting.state.status.
 * @param is_normal
 *   If TRUE, then process as if this operates during a normal operation (entry and control).
 *   If FALSE, then process as if this operates during a an exit operation.
 * @param alias
 *   The string identifying the rule.
 *   This is constructed from the path parts to the file without the file extension and without the settings directory prefix.
 *   "/etc/controller/rules/example/my.rule" would have a rule id of "example/my".
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param entry
 *   The entry containing the rule being read.
 * @param rule
 *   The processed rule.
 *   The rule status will be updated by this function.
 *
 * @return
 *   F_okay on success.
 *
 *   Simplified status (with error bit) from controller_status_simplify_error() on failure.
 *
 * @see controller_rule_items_increase_by().
 * @see controller_rule_item_read().
 * @see f_fss_count_lines().
 * @see f_fss_apply_delimit().
 * @see f_string_dynamic_partial_append().
 * @see f_string_dynamic_partial_append_nulless().
 * @see fll_fss_basic_list_read().
 */
#ifndef _di_controller_rule_read_
  extern f_status_t controller_rule_read(controller_global_t * const global, const bool is_normal, const f_string_static_t alias, controller_cache_t * const cache, controller_entry_t * const entry, controller_rule_t * const rule);
#endif // _di_controller_rule_read_

/**
 * Process a number from a rule file, incrementing index as necessary.
 *
 * This prints error messages as necessary.
 *
 * This is intended to be called by controller_rule_action_read().
 *
 * @param global
 *   The global data.
 *   Must not be NULL.
 *
 *   This does not alter global.main.setting.state.status.
 * @param name
 *   The name representing the value whose number is being processed.
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param index
 *   The position within the content action array for some rule to process.
 * @param number
 *   The processed number will be saved here.
 *
 * @return
 *   F_okay on success.
 *
 *   F_valid_not (with error bit) on failure due to invalid value.
 *
 *   Errors (with error bit) from: fl_conversion_dynamic_partial_to_signed_detect().
 *
 * @see controller_rule_action_read()
 * @see fl_conversion_dynamic_partial_to_signed_detect()
 */
#ifndef _di_controller_rule_action_read_rerun_number_
  extern f_status_t controller_rule_action_read_rerun_number(controller_global_t * const global, const f_string_t name, controller_cache_t * const cache, f_number_unsigned_t * const index, f_number_unsigned_t * const number);
#endif // _di_controller_rule_action_read_rerun_number_


#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_rule_read_h
