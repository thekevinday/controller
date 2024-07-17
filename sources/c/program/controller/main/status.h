/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides status functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_status_h
#define _controller_status_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Given a wide range of status codes (that are errors), simplify them down to a smaller subset.
 *
 * @param status
 *   The status code (without the error bit set) to simplify.
 *
 * @return
 *   The status code (with error bit set) mapped to a status code from a subset of status codes.
 */
#ifndef _di_controller_status_simplify_error_
  extern f_status_t controller_status_simplify_error(const f_status_t status);
#endif // _di_controller_status_simplify_error_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_status_h
