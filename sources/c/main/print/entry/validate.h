/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print entry validate functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_entry_validate_h
#define _controller_main_print_entry_validate_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print a simulated execution of the given entry.
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
 *   If TRUE, then this is an entry.
 *   If FALSE, then this is an exit.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_entry_validate_setting_
  extern f_status_t controller_print_entry_validate_setting(fl_print_t * const print, const uint8_t is_entry);
#endif // _di_controller_print_entry_validate_setting_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_entry_validate_h
