/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_common_h
#define _controller_main_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Given a wide range of status codes (that are errors), simplify them down to a small subset.
 *
 * @param status
 *   The status code (without the error bit set) to simplify.
 *
 * @return
 *   A subset of status codes (with error bit set).
 */
#ifndef _di_controller_error_simplify_
  extern f_status_t controller_error_simplify(const f_status_t status);
#endif // _di_controller_error_simplify_

/**
 * Given a string whose range represents a number, seek past the first positive or negative sign.
 *
 * This will stop at the first non-NULL, non-'+' and non-'-' characters.
 *
 * Only the first '+' or '-' are processed.
 *
 * @param buffer
 *   The string referenced by the range.
 * @param range
 *   The range within the buffer to process.
 *
 * @return
 *   The string range.
 *   The start range will be past the stop range on overflow or on any failure.
 */
#ifndef _di_controller_range_after_number_sign_
  extern f_range_t controller_range_after_number_sign(const f_string_static_t buffer, const f_range_t range);
#endif // _di_controller_range_after_number_sign_

/**
 * Perform the standard program setting load settings.
 *
 * This prints error messages as appropriate.
 *
 * If either main or setting is NULL, then this immediately returns without doing anything.
 *
 * @param arguments
 *   The parameters passed to the program (often referred to as command line arguments).
 * @param main
 *   The program and settings data.
 *
 *   Must not be NULL.
 *
 *   This alters setting.state.status:
 *     F_okay on success.
 *
 *     Errors (with error bit) from: f_console_parameter_process().
 *     Errors (with error bit) from: fll_program_parameter_process_context().
 *
 * @see f_console_parameter_process()
 * @see fll_program_parameter_process_context()
 */
#ifndef _di_controller_setting_load_
  extern void controller_setting_load(const f_console_arguments_t arguments, controller_t * const main);
#endif // _di_controller_setting_load_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_h
