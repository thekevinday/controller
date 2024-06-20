/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print error lock functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_error_lock_h
#define _controller_main_print_error_lock_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print a r/w lock related error message, locking the print mutex during the print.
 *
 * This will ignore F_interrupt and not print any messages, if passed.
 *
 * @param print
 *   The output structure to print to.
 *
 *   Must not be NULL.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param status
 *   The status code to process.
 *   Make sure this has F_status_set_fine() called if the status code has any error or warning bits.
 * @param is_read
 *   If TRUE, then this is for a read lock.
 *   If FALSE, then this is for a write lock.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_controller_print_error_lock_critical_
  extern f_status_t controller_print_error_lock_critical(fl_print_t * const print, const f_status_t status, const uint8_t is_read);
#endif // _di_controller_print_error_lock_critical_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_error_lock_h
