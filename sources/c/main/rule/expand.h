/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the rule "expand" functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_rule_expand_h
#define _controller_main_rule_expand_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Expand a single IKI variable into the buffer.
 *
 * @param global
 *   The global data.
 *
 *   Must not be NULL.
 *
 *   This does not alter global.main.setting.state.status.
 * @param action
 *   The rule action data.
 * @param process
 *   The process information.
 *
 * @return
 *   F_okay on success.
 *
 *   Errors (with error bit) from: controller_main_rule_expand_iki().
 *
 *   @see controller_main_rule_expand_iki()
 */
#ifndef _di_controller_main_rule_expand_
  extern f_status_t controller_main_rule_expand(controller_global_t * const global, const controller_main_rule_action_t action, controller_instance_t * const instance);
#endif // _di_controller_main_rule_expand_

/**
 * Expand a single IKI variable into the buffer.
 *
 * @param process
 *   The process information.
 * @param source
 *   The source buffer holding the string referenced by the IKI data.
 * @param vocabulary
 *   The range representing the IKI variable vocabulary.
 * @param content
 *   The range representing the IKI variable content.
 * @param destination
 *   The buffer to expand into.
 *
 * @return
 *   F_okay on success.
 *
 *   Errors (with error bit) from: f_environment_get().
 *   Errors (with error bit) from: f_string_dynamic_append().
 *
 *   @see f_environment_get()
 *   @see f_string_dynamic_append()
 */
#ifndef _di_controller_main_rule_expand_iki_
  extern f_status_t controller_main_rule_expand_iki(controller_instance_t * const instance, const f_string_static_t source, const f_range_t vocabulary, const f_range_t content, f_string_dynamic_t * const destination);
#endif // _di_controller_main_rule_expand_iki_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_rule_expand_h
