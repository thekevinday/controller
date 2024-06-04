/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print entry simulate functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_entry_simulate_h
#define _controller_main_print_entry_simulate_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print message regarding the population of a setting when in simulation or verbose mode.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 * @param is_entry
 *   If TRUE, then this operate as an entry.
 *   If FALSE, then this operate as an exit.
 * @param name
 *   The Object name of the setting being populated.
 * @param name_sub
 *   A sub-name associated with the setting being populated.
 *   Set to a string with used set to 0 to not use.
 * @param value
 *   The value being set.
 * @param suffix
 *   An additional message to append at the end (before the final period).
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_entry_preprocess_print_simulate_setting_value_
  extern f_status_t controller_entry_preprocess_print_simulate_setting_value(controller_t * const main, const uint8_t is_entry, const f_string_static_t name, const f_string_static_t name_sub, const f_string_static_t value, const f_string_static_t suffix);
#endif // _di_controller_entry_preprocess_print_simulate_setting_value_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_entry_simulate_h
