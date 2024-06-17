/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides entry functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_entry_h
#define _controller_entry_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Read the entry, extracting all lists.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 * @param entry
 *   The entry data.
 *
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *   F_file_found_not on file not found for a an exit file (is_entry is FALSE).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: controller_entry_actions_read().
 *   Errors (with error bit) from: controller_entry_items_increase_by().
 *   Errors (with error bit) from: controller_file_load().
 *   Errors (with error bit) from: controller_status_simplify_error().
 *
 *   Errors (with error bit) from: f_fss_count_lines().
 *   Errors (with error bit) from: f_string_dynamic_append().
 *   Errors (with error bit) from: f_string_dynamic_append_nulless().
 *   Errors (with error bit) from: f_string_dynamic_partial_append().
 *   Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *   Errors (with error bit) from: f_string_dynamic_terminate().
 *   Errors (with error bit) from: f_fss_apply_delimit().
 *   Errors (with error bit) from: fll_fss_basic_list_read().
 *
 * @see controller_entry_actions_read()
 * @see controller_entry_items_increase_by()
 * @see controller_file_load()
 * @see controller_status_simplify_error()
 *
 * @see f_fss_count_lines()
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_append_nulless()
 * @see f_string_dynamic_partial_append()
 * @see f_string_dynamic_partial_append_nulless()
 * @see f_string_dynamic_terminate()
 * @see f_fss_apply_delimit()
 * @see fll_fss_basic_list_read()
 */
#ifndef _di_controller_entry_read_
  extern f_status_t controller_entry_read(controller_t * const main, controller_entry_t * const entry);
#endif // _di_controller_entry_read_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_entry_h
