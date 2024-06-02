/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides thread functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_thread_h
#define _controller_main_thread_h

/***
 * Detach a thread, assigning id to NULL on success.
 *
 * If the ID is not found, then it is also set to NULL.
 *
 * This should be called for asynchronous processes.
 *
 * @param id
 *   The thread ID.
 *
 * @return
 *   F_okay on success.
 *   F_data_not if id is NULL or the value of id is 0.
 *
 *   Success from: f_thread_detach().
 *
 *   Errors (with error bit) from: f_thread_detach().
 *
 * @see f_thread_detach()
 */
#ifndef _di_controller_thread_detach_
  extern f_status_t controller_thread_detach(f_thread_id_t * const id);
#endif // _di_controller_thread_detach_

/***
 * Join a thread, assigning id to NULL on success.
 *
 * If the ID is not found, then it is also set to NULL.
 *
 * @param id
 *   The thread ID.
 *
 * @return
 *   F_okay on success.
 *   F_data_not if id is NULL or the value of id is 0.
 *
 *   Success from: f_thread_join().
 *
 *   Errors (with error bit) from: f_thread_join().
 *
 * @see f_thread_join()
 */
#ifndef _di_controller_thread_join_
  extern f_status_t controller_thread_join(f_thread_id_t * const id);
#endif // _di_controller_thread_join_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_thread_h
