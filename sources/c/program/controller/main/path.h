/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides path functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_path_h
#define _controller_main_path_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Determine a canonical path and then, if it is relative to the current working directory, make it a relative path.
 *
 * For example, given the paths "../hello/world/" and "../controller/files/" with a current working directory of "/tmp/controller", then a canonical path for these might look like:
 * - "/tmp/hello/world/"
 * - "/tmp/controller/files/"
 *
 * This function would instead result in the following:
 * - "/tmp/hello/world/"
 * - "files/"
 * @param main
 *   The program and settings data.
 *
 *   Must not be NULL.
 *
 *   This alters setting.state.status:
 *     F_okay on success.
 *
 *     Errors (with error bit) from: fl_path_canonical().
 * @param current
 *   The current path, such as process.path_current.
 * @param source
 *   The source path to determine the relative canonical from.
 * @param destination
 *   The resulting relative canonical path.
 *   The destination will be completely replaced on success.
 *
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fl_path_canonical()
 *
 * @see memmove()
 */
#ifndef _di_controller_path_canonical_relative_
  extern f_status_t controller_path_canonical_relative(controller_t * const main, const f_string_static_t current, const f_string_static_t source, f_string_dynamic_t * const destination);
#endif // _di_controller_path_canonical_relative_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_path_h
