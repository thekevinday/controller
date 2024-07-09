/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print Rule Item warning functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_warning_rule_item_h
#define _controller_main_print_warning_rule_item_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print warning message about the Rule Item being unknown.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be controller_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 *   Must not be NULL.
 * @param action
 *   The Action cache.
 *
 *   Must not be NULL.
 * @param name
 *   The Item name that is unknown.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_warning_rule_item_unknown_
  extern f_status_t controller_print_warning_rule_item_unknown(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t name);
#endif // _di_controller_print_warning_rule_item_unknown_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_warning_rule_item_h
