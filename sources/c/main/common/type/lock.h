/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common lock type structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_common_type_lock_h
#define _controller_main_common_type_lock_h

#ifdef __cplusplus
extern "C" {
#endif
/**
 * A structure for sharing mutexes globally between different threads.
 *
 * The alert lock is intended for a generic waiting on alerts operations.
 * The cancel lock is intended for preventing double cancellation calls (which can happen due to interrupts).
 * The print lock is intended to lock any activity printing to stdout/stderr.
 * The process lock is intended to lock any activity on the process structure.
 * The rule lock is intended to lock any activity on the rules structure.
 *
 * alert:           The alert mutex lock for waking up on alerts.
 * cancel:          The cancel mutex lock for locking the cancel operation.
 * print:           The print mutex lock.
 * process:         The process r/w lock.
 * rule:            The rule r/w lock.
 * alert_condition: The condition used to trigger alerts.
 */
#ifndef _di_controller_lock_t_
  typedef struct {
    f_thread_mutex_t alert;
    f_thread_mutex_t cancel;
    f_thread_mutex_t print;

    f_thread_lock_t process;
    f_thread_lock_t rule;

    f_thread_condition_t alert_condition;
  } controller_lock_t;

  #define controller_lock_t_initialize { \
    f_thread_mutex_t_initialize, \
    f_thread_mutex_t_initialize, \
    f_thread_mutex_t_initialize, \
    f_thread_lock_t_initialize, \
    f_thread_lock_t_initialize, \
    f_thread_condition_t_initialize, \
  }
#endif // _di_controller_lock_t_

/**
 * Fully deallocate all memory for the given lock without caring about return status.
 *
 * @param lock
 *   The lock to deallocate.
 *
 * @see f_thread_lock_delete()
 * @see f_thread_mutex_delete()
 */
#ifndef _di_controller_lock_delete_
  extern void controller_lock_delete(controller_lock_t * const lock);
#endif // _di_controller_lock_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_type_lock_h
