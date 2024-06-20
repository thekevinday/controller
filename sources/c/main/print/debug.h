/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print debug functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_debug_h
#define _controller_main_print_debug_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print a debug message about the directory path string being empty.
 *
 * @param print
 *   The output structure to print to.
 *
 *   Must not be NULL.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param symbol
 *   The symbol string prepended to the parameter.
 *   This locks, uses, and unlocks the file stream.
 *   This is usually f_console_symbol_long_normal_s.
 * @param name
 *   The parameter name.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_debug_directory_path_empty_
  extern f_status_t controller_print_debug_directory_path_empty(fl_print_t * const print, const f_string_static_t symbol, const f_string_static_t name);
#endif // _di_controller_print_debug_directory_path_empty_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_debug_h
