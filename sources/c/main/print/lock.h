/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print lock functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_print_lock_h
#define _controller_main_print_lock_h

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
 */
#ifndef _di_controller_lock_print_error_critical_
  extern void controller_lock_print_error_critical(fl_print_t * const print, const f_status_t status, const uint8_t is_read);
#endif // _di_controller_lock_print_error_critical_

/**
 * Lock the mutex and the stream.
 *
 * This is implemented as a compliment to controller_unlock_print_flush() for consistency reasons.
 *
 * @param to
 *   The file stream to lock.
 * @param thread
 *   (optonal) The thread containing the print mutex to lock.
 *
 *   Set to NULL to not use.
 *
 * @see f_file_stream_lock()
 * @see f_thread_mutex_unlock()
 */
#ifndef _di_controller_lock_print_
  extern void controller_lock_print(const f_file_t to, controller_thread_t * const thread);
#endif // _di_controller_lock_print_

/**
 * Flush the stream buffer and then unlock the mutex.
 *
 * This unlocks both the stream and the mutex locks.
 *
 * Weird behavior was observed when piping data from this program.
 * The behavior appears related to how this handles locks in addition to the file streams own locking mechanisms.
 *
 * As a work-around, this performs a flush immediately before unlocking the print mutex.
 *
 * @param to
 *   The file stream to unlock and flush.
 * @param thread
 *   (optonal) The thread containing the print mutex to unlock.
 *
 *   Set to NULL to not use.
 *
 * @see f_file_stream_unlock()
 *
 * @see f_thread_mutex_unlock()
 */
#ifndef _di_controller_unlock_print_flush_
  void controller_unlock_print_flush(const f_file_t to, controller_thread_t * const thread);
#endif // _di_controller_unlock_print_flush_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_lock_h
