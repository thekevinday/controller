/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print Entry setting warning functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_entry_warning_setting_h
#define _controller_main_print_entry_warning_setting_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print a message for when an Entry Setting Action is unknown.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be controller_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 *   Must not be NULL.
 * @param cache
 *   The cache.
 *
 *   Must not be NULL.
 * @param is_entry
 *   If TRUE, then this loads as an Entry.
 *   If FALSE, then this loads as an Exit.
 * @param name
 *   The parameter name whose value is unknown.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_warning_entry_setting_unknown_action_
  extern f_status_t controller_print_warning_entry_setting_unknown_action(fl_print_t * const print, controller_cache_t * const cache, const uint8_t is_entry, const f_string_static_t name);
#endif // _di_controller_print_warning_entry_setting_unknown_action_

/**
 * Print a message for when an Entry Setting Action value is unknown.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be controller_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 *   Must not be NULL.
 * @param cache
 *   The cache.
 *
 *   Must not be NULL.
 * @param is_entry
 *   If TRUE, then this loads as an Entry.
 *   If FALSE, then this loads as an Exit.
 * @param name
 *   The parameter name whose value is unknown.
 * @param buffer
 *   The buffer containing the unknown value.
 * @param range
 *   The range within the buffer representing the unknown value.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_warning_entry_setting_unknown_action_value_
  extern f_status_t controller_print_warning_entry_setting_unknown_action_value(fl_print_t * const print, controller_cache_t * const cache, const uint8_t is_entry, const f_string_static_t name, const f_string_static_t buffer, const f_range_t range);
#endif // _di_controller_print_warning_entry_setting_unknown_action_value_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_entry_warning_setting_h
