/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the entry action functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_entry_action_h
#define _controller_main_entry_action_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Read the entry list, loading all items and values.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 * @param is_entry
 *   If TRUE, then this operates as an entry.
 *   If FALSE, then this operates as an exit.
 * @param range
 *   The range in the list buffer representing the content.
 * @param actions
 *   The processed actions.
 *
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *
 *   Errors (with error bit) from: controller_entry_actions_increase_by().
 *   Errors (with error bit) from: f_fss_apply_delimit().
 *   Errors (with error bit) from: f_fss_count_lines().
 *   Errors (with error bit) from: f_memory_array_increase_by().
 *   Errors (with error bit) from: f_rip_dynamic_partial_nulless().
 *   Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *   Errors (with error bit) from: fll_fss_extended_read().
 *
 * @see controller_entry_actions_increase_by()
 * @see f_fss_apply_delimit()
 * @see f_fss_count_lines()
 * @see f_memory_array_increase_by()
 * @see f_rip_dynamic_partial_nulless()
 * @see f_string_dynamic_partial_append_nulless()
 * @see fll_fss_extended_read()
 */
#ifndef _di_controller_entry_action_read_
  extern f_status_t controller_entry_action_read(controller_t * const main, const uint8_t is_entry, const f_range_t range, controller_entry_actions_t * const actions);
#endif // _di_controller_entry_action_read_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_entry_action_h
