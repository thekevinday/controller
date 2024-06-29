/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the rule "setting" functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_rule_setting_h
#define _controller_main_rule_setting_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Identify the Rule Item code the given name represents.
 *
 * @param item
 *   The string representing an rule action.
 *
 * @return
 *   The Rule Item type code on success.
 *   0 if name is unknown.
 */
#ifndef _di_controller_rule_setting_limit_type_identify_
  extern uint8_t controller_rule_setting_limit_type_identify(const f_string_static_t item);
#endif // _di_controller_rule_setting_limit_type_identify_

/**
 * Get a string representing the rule setting limit type.
 *
 * @param type
 *   The rule setting limit type code.
 *
 * @return
 *   The string with used > 0 on success.
 *   The string with used == 0 if no match was found.
 */
#ifndef _di_controller_rule_setting_limit_type_name_
  extern f_string_static_t controller_rule_setting_limit_type_name(const uint8_t type);
#endif // di_controller_rule_setting_limit_type_name_

/**
 * Read the content within the buffer, extracting all valid settings.
 *
 * This will perform additional FSS read functions as appropriate.
 *
 * Errors from this are not considered fatal, but the first error code encountered is returned.
 * Memory failure errors are always immediately returned.
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
 * @param rule
 *   The processed rule.
 *
 * @return
 *    F_okay on success.
 *
 *    F_valid_not (with error bit) on success but there were one or more invalid settings encountered.
 *
 *   Errors (with error bit) from: f_memory_array_increase().
 *   Errors (with error bit) from: f_rip_dynamic_partial_nulless().
 *   Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *   Errors (with error bit) from: fll_fss_extended_read().
 *
 *   Errors (with error bit) from: controller_path_canonical_relative().
 *
 * @see f_memory_array_increase()
 * @see f_rip_dynamic_partial_nulless()
 * @see f_string_dynamic_partial_append_nulless()
 * @see fll_fss_extended_read()
 *
 * @see controller_path_canonical_relative()
 */
#ifndef _di_controller_rule_setting_read_
  extern f_status_t controller_rule_setting_read(controller_t * const main, controller_cache_t * const cache, const uint8_t is_normal, controller_rule_t * const rule);
#endif // _di_controller_rule_setting_read_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_rule_setting_h
