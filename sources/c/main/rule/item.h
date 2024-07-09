/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the Rule "item" functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_rule_item_h
#define _controller_main_rule_item_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Read the content within the buffer, extracting all valid items after determining their type for some Rule file.
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
 *   If TRUE, then process as if this operates during a normal operation (Entry and Control).
 *   If FALSE, then process as if this operates during a an Exit operation.
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param item
 *   The processed item.
 * @param state
 *   The state information.
 *
 *   This alters state.status:
 *     F_okay on success.
 *     F_valid_not (with error bit) on invalid data.
 *
 *     Errors (with error bit) from: f_fss_count_lines().
 *     Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *
 *   Must not be NULL.
 *
 * @see controller_rule_action_read()
 * @see f_fss_count_lines()
 * @see f_string_dynamic_partial_append_nulless()
 */
#ifndef _di_controller_rule_item_read_
  extern void controller_rule_item_read(controller_t * const main, controller_cache_t * const cache, const uint8_t is_normal, controller_rule_item_t * const item, f_state_t * const state);
#endif // _di_controller_rule_item_read_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_rule_item_h
