/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the entry setting functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_entry_setting_h
#define _controller_main_entry_setting_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Read the entry settings, loading all settings.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 * @param cache
 *   A structure for containing and caching relevant data.
 *
 *   Must not be NULL.
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param content_range
 *   The range in the list buffer representing the content.
 *
 * @return
 *   F_okay on success.
 *
 *   Errors (with error bit) from: controller_print_entry_error_file().
 *
 * @see controller_print_entry_error_file()
 */
#ifndef _di_controller_entry_setting_read_
  extern f_status_t controller_entry_setting_read(controller_t * const main, controller_cache_t * const cache, const uint8_t is_entry, const f_range_t content_range);
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
