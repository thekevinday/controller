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
 */
#ifndef _di_controller_unlock_print_flush_
  extern void controller_unlock_print_flush(const f_file_t to, controller_thread_t * const thread);
#endif // _di_controller_unlock_print_flush_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_print_lock_h
