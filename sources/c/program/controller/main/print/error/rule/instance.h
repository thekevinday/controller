/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print Entry Rule Instance error functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_error_rule_instance_h
#define _controller_main_print_error_rule_instance_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print a error message related to need/want/wish settings of some Rule for some Instance.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be controller_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 *   Must not be NULL.
 * @param instance
 *   The Controller Instance.
 *
 *   Must not be NULL.
 * @param need_want_wish
 *   The appropriate string, such as "needs", "wants", or "wishes for" to output when describing this error/warning.
 *   This string is expected to already be "safe" (no control characters, etc..).
 * @param value
 *   The value that is the error or warning.
 * @param why
 *   A short explanation on why this is an error or warning.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_rule_instance_need_want_wish_
  extern f_status_t controller_print_error_rule_instance_need_want_wish(fl_print_t * const print, controller_instance_t * const instance, const f_string_static_t need_want_wish, const f_string_static_t value, const f_string_t why);
#endif // _di_controller_print_error_rule_instance_need_want_wish_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_error_rule_instance_h
