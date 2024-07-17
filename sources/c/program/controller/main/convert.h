/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides convert functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_convert_h
#define _controller_convert_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Convert the string from a string representation of an ID or a user name into the numeric representation of that ID or user name.
 *
 * @param cache
 *   The cache.
 *
 *   Must not be NULL.
 * @param buffer
 *   A string containing group name or ID.
 * @param range
 *   The range within the buffer specifically containing the name or ID.
 * @param id
 *   The determined user ID.
 *
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *
 *   F_exist_not (with error bit) if failed to match the name to an ID.
 *   F_number_too_large (with error bit) if the given ID is too large.
 *
 *   Errors (with error bit) from: f_account_id_by_name().
 *   Errors (with error bit) from: fl_conversion_dynamic_partial_to_unsigned_detect().
 *   Errors (with error bit) from: f_rip_dynamic_partial_nulless().
 *
 * @see f_account_id_by_name()
 * @see fl_conversion_dynamic_partial_to_unsigned_detect()
 * @see f_rip_dynamic_partial_nulless()
 */
#ifndef _di_controller_convert_user_id_
  f_status_t controller_convert_user_id(controller_cache_t * const cache, const f_string_static_t buffer, const f_range_t range, uid_t * const id);
#endif // _di_controller_convert_user_id_

/**
 * Convert the string from a string representation of an ID or a group name into the numeric representation of that ID or group name.
 *
 * @param cache
 *   The cache.
 *
 *   Must not be NULL.
 * @param buffer
 *   A string containing group name or ID.
 * @param range
 *   The range within the buffer specifically containing the name or ID.
 * @param id
 *   The determined user ID.
 *
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *
 *   F_exist_not (with error bit) if failed to match the name to an ID.
 *   F_number_too_large (with error bit) if the given ID is too large.
 *
 *   Errors (with error bit) from: f_account_group_id_by_name().
 *   Errors (with error bit) from: fl_conversion_dynamic_partial_to_unsigned_detect().
 *   Errors (with error bit) from: f_rip_dynamic_partial_nulless().
 *
 * @see f_account_group_id_by_name()
 * @see fl_conversion_dynamic_partial_to_unsigned_detect()
 * @see f_rip_dynamic_partial_nulless()
 */
#ifndef _di_controller_convert_group_id_
  f_status_t controller_convert_group_id(controller_cache_t * const cache, const f_string_static_t buffer, const f_range_t range, gid_t * const id);
#endif // _di_controller_convert_group_id_

/**
 * Convert the Rule Action execute type code to the string representation.
 *
 * @param type
 *   The Rule Action execute type code.
 *
 * @return
 *   The string with used > 0 on success.
 *   The string with used == 0 if no match was found.
 */
#ifndef _di_controller_convert_rule_action_execute_type_string_
  extern f_string_static_t controller_convert_rule_action_execute_type_string(const uint8_t type);
#endif // _di_controller_convert_rule_action_execute_type_string_

/**
 * Convert the Rule Action type code to the string representation.
 *
 * @param type
 *   The Rule Action type code.
 *
 * @return
 *   The string with used > 0 on success.
 *   The string with used == 0 if no match was found.
 */
#ifndef _di_controller_convert_rule_action_type_string_
  extern f_string_static_t controller_convert_rule_action_type_string(const uint8_t type);
#endif // _di_controller_convert_rule_action_type_string_

/**
 * Convert the Rule Item type code to the string representation.
 *
 * @param type
 *   The Rule Item type code.
 *
 * @return
 *   The string with used > 0 on success.
 *   The string with used == 0 if no match was found.
 */
#ifndef _di_controller_convert_rule_item_type_string_
  extern f_string_static_t controller_convert_rule_item_type_string(const uint8_t type);
#endif // _di_controller_convert_rule_item_type_string_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_convert_h
