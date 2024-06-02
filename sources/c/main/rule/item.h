/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the rule "item" functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_rule_item_h
#define _controller_main_rule_item_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Read the content within the buffer, extracting all valid items after determining their type for some rule file.
 *
 * This will perform additional FSS read functions as appropriate.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 *
 *   This does not alter main.setting.state.status.
 * @param is_normal
 *   If TRUE, then process as if this operates during a normal operation (entry and control).
 *   If FALSE, then process as if this operates during a an exit operation.
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param item
 *   The processed item.
 *
 * @return
 *   F_okay on success.
 *   F_valid_not (with error bit) on invalid data.
 *
 *   Errors (with error bit) from: f_fss_count_lines().
 *   Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *
 * @see controller_rule_action_read()
 * @see f_fss_count_lines()
 * @see f_string_dynamic_partial_append_nulless()
 */
#ifndef _di_controller_rule_item_read_
  extern f_status_t controller_rule_item_read(controller_t * const main, const bool is_normal, controller_cache_t * const cache, controller_rule_item_t * const item);
#endif // _di_controller_rule_item_read_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_rule_item_h
