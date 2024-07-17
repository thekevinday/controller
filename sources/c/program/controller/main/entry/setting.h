/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the Entry setting functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_entry_setting_h
#define _controller_main_entry_setting_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Read the Entry settings, loading all settings.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 * @param is_entry
 *   If TRUE, then this loads as an Entry.
 *   If FALSE, then this loads as an Exit.
 * @param content_range
 *   The range in the list buffer representing the content.
 *
 * @return
 *   F_okay on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_file_mode_from_string().
 *   Errors (with error bit) from: f_file_mode_to_mode().
 *   Errors (with error bit) from: f_fss_apply_delimit().
 *   Errors (with error bit) from: f_fss_count_lines().
 *   Errors (with error bit) from: f_rip_dynamic_partial_nulless().
 *   Errors (with error bit) from: fl_conversion_dynamic_partial_to_unsigned_detect().
 *   Errors (with error bit) from: fll_fss_extended_read().
 *
 *   Errors (with error bit) from: controller_convert_group_id().
 *   Errors (with error bit) from: controller_convert_user_id().
 *   Errors (with error bit) from: controller_entry_setting_read_map().
 *   Errors (with error bit) from: controller_path_canonical_relative().
 *
 * @see f_file_mode_from_string()
 * @see f_fss_apply_delimit()
 * @see f_fss_count_lines()
 * @see f_rip_dynamic_partial_nulless()
 * @see fl_conversion_dynamic_partial_to_unsigned_detect()
 * @see fll_fss_extended_read()
 *
 * @see controller_convert_group_id()
 * @see controller_convert_user_id()
 * @see controller_entry_setting_read_map()
 * @see controller_path_canonical_relative()
 */
#ifndef _di_controller_entry_setting_read_
  extern f_status_t controller_entry_setting_read(controller_t * const main, const uint8_t is_entry, const f_range_t content_range);
#endif // _di_controller_entry_setting_read_

/**
 * Load the given ranges within the buffer into the provided map.
 *
 * @param buffer
 *   The buffer the ranges are associated with.
 * @param ranges
 *   The ranges to load from the buffer.
 *   This expects the caller to already ensure the ranges.used = 2.
 * @param setting_maps
 *   The map to load the settings into.
 *
 * @return
 *   F_okay on success.
 *
 *   Errors (with error bit) from: f_memory_aray_increase().
 *   Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *
 * @see f_memory_aray_increase()
 * @see f_string_dynamic_partial_append_nulless()
 */
#ifndef _di_controller_entry_setting_read_map_
  extern f_status_t controller_entry_setting_read_map(const f_string_static_t buffer, const f_ranges_t ranges, f_string_maps_t * const setting_maps);
#endif // _di_controller_entry_setting_read_map_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_entry_setting_h
