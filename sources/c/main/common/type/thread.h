/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common thread type structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_common_type_thread_h
#define _controller_main_common_type_thread_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A structure for managing threads.
 *
 * This is essentially data shared globally between threads, about threads.
 *
 * The "enabled" and "signal" utilize the lock: lock.process.
 *
 * enabled: TRUE when threads are active, FALSE when inactive and the program is essentially shutting down, no new threads should be started when FALSE.
 * signal:  The code of any signal received.
 * status:  A status used by the main entry/rule processing thread for synchronous operations.
 *
 * id_cleanup: The thread ID representing the Cleanup Process.
 * id_control: The thread ID representing the Control Process.
 * id_entry:   The thread ID representing the Entry or Exit Process.
 * id_rule:    The thread ID representing the Rule Process.
 * id_signal:  The thread ID representing the Signal Process.
 *
 * lock:    A r/w lock for operating on this structure.
 * process: All Rule Process thread data.
 * cache:   A cache used by the main entry/rule processing thread for synchronous operations.
 */
#ifndef _di_controller_thread_t_
  typedef struct {
    uint8_t enabled;
    int signal;
    f_status_t status;

    f_thread_id_t id_cleanup;
    f_thread_id_t id_control;
    f_thread_id_t id_entry;
    f_thread_id_t id_rule;
    f_thread_id_t id_signal;

    controller_lock_t lock;
    controller_process_t process;
    controller_cache_t cache;
  } controller_thread_t;

  #define controller_thread_t_initialize { \
    controller_thread_enabled_e, \
    0, \
    F_none, \
    f_thread_id_t_initialize, \
    f_thread_id_t_initialize, \
    f_thread_id_t_initialize, \
    f_thread_id_t_initialize, \
    f_thread_id_t_initialize, \
    controller_lock_t_initialize, \
    controller_processs_t_initialize, \
    controller_cache_t_initialize, \
  }
#endif // _di_controller_thread_t_

/**
 * Fully deallocate all memory for the given setting without caring about return status.
 *
 * @param thread
 *   The thread to deallocate.
 *
 *   Must not be NULL.
 *
 * @see controller_asynchronouss_resize()
 *
 * @see f_thread_mutex_unlock()
 */
#ifndef _di_controller_thread_delete_
  extern void controller_thread_delete(controller_thread_t * const thread);
#endif // _di_controller_thread_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_type_thread_h
