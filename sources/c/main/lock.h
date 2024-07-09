/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides lock functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_lock_h
#define _controller_lock_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform the initial, required, allocation for the lock.
 *
 * @param lock
 *   The lock to allocate.
 *
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_thread_lock_delete().
 *   Errors (with error bit) from: f_thread_mutex_delete().
 *
 * @see f_thread_lock_delete()
 * @see f_thread_mutex_delete()
 */
#ifndef _di_controller_lock_create_
  extern f_status_t controller_lock_create(controller_lock_t * const lock);
#endif // _di_controller_lock_create_

/**
 * Wait to get a read lock.
 *
 * Given a r/w lock, periodically check to see if main thread is disabled while waiting.
 *
 * @param is_normal
 *   If TRUE, then perform as if this operates during a normal operation (Entry and Control).
 *   If FALSE, then perform as if this operates during a an Exit operation.
 * @param thread
 *   The thread data used to determine if the main thread is disabled or not.
 *
 *   Must not be NULL.
 * @param lock
 *   The r/w lock to obtain a read lock on.
 *
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *
 *   F_interrupt (with error bit set) on (exit) signal received, lock will not be set when this is returned.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Status from: f_thread_lock_read_timed().
 *
 *   Errors (with error bit) from: f_thread_lock_read_timed().
 *
 * @see f_thread_lock_read_timed()
 */
#ifndef _di_controller_lock_read_
  extern f_status_t controller_lock_read(const uint8_t is_normal, controller_thread_t * const thread, f_thread_lock_t * const lock);
#endif // _di_controller_lock_read_

/**
 * Wait to get a read lock for some instance.
 *
 * Given a r/w lock, periodically check to see if main thread is disabled while waiting.
 *
 * @param instance
 *   The instance to use when checking if thread is enabled.
 *
 *   Must not be NULL.
 * @param lock
 *   The r/w lock to obtain a read lock on.
 *
 *   Must not be NULL.
 *
 * @return
 *   Status from: controller_lock_read().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: controller_lock_read().
 *
 * @see controller_lock_read()
 */
#ifndef _di_controller_lock_read_instance_
  extern f_status_t controller_lock_read_instance(controller_instance_t * const instance, f_thread_lock_t * const lock);
#endif // _di_controller_lock_read_instance_

/**
 * Wait to get a read lock for some instance type.
 *
 * Given a r/w lock, periodically check to see if main thread is disabled while waiting.
 *
 * @param type
 *   The instance type to use when checking if thread is enabled.
 * @param thread
 *   The thread data used to determine if the main thread is disabled or not.
 *
 *   Must not be NULL.
 * @param lock
 *   The r/w lock to obtain a read lock on.
 *
 *   Must not be NULL.
 *
 * @return
 *   Status from: controller_lock_read().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: controller_lock_read().
 *
 * @see controller_lock_read()
 */
#ifndef _di_controller_lock_read_instance_type_
  extern f_status_t controller_lock_read_instance_type(const uint8_t type, controller_thread_t * const thread, f_thread_lock_t * const lock);
#endif // _di_controller_lock_read_instance_type_

/**
 * Wait to get a write lock.
 *
 * Given a r/w lock, periodically check to see if main thread is disabled while waiting.
 *
 * @param is_normal
 *   If TRUE, then perform as if this operates during a normal operation (Entry and Control).
 *   If FALSE, then perform as if this operates during a an Exit operation.
 * @param thread
 *   The thread data used to determine if the main thread is disabled or not.
 *
 *   Must not be NULL.
 * @param lock
 *   The r/w lock to obtain a write lock on.
 *
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *
 *   F_interrupt (with error bit set) on (exit) signal received, lock will not be set when this is returned.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Status from: f_thread_lock_write_timed().
 *
 *   Errors (with error bit) from: f_thread_lock_write_timed().
 *
 * @see f_thread_lock_write_timed()
 */
#ifndef _di_controller_lock_write_
  extern f_status_t controller_lock_write(const uint8_t is_normal, controller_thread_t * const thread, f_thread_lock_t * const lock);
#endif // _di_controller_lock_write_

/**
 * Wait to get a write lock for some instance.
 *
 * Given a r/w lock, periodically check to see if main thread is disabled while waiting.
 *
 * @param instance
 *   The instance to use when checking if thread is enabled.
 *
 *   Must not be NULL.
 * @param lock
 *   The r/w lock to obtain a write lock on.
 *
 *   Must not be NULL.
 *
 * @return
 *   Status from: controller_lock_write_instance_type().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: controller_lock_write_instance_type().
 *
 * @see controller_lock_write_instance_type()
 */
#ifndef _di_controller_lock_write_instance_
  extern f_status_t controller_lock_write_instance(controller_instance_t * const instance, f_thread_lock_t * const lock);
#endif // _di_controller_lock_write_instance_

/**
 * Wait to get a write lock for some instance type.
 *
 * Given a r/w lock, periodically check to see if main thread is disabled while waiting.
 *
 * @param type
 *   The instance type to use when checking if thread is enabled.
 * @param thread
 *   The thread data used to determine if the main thread is disabled or not.
 *
 *   Must not be NULL.
 * @param lock
 *   The r/w lock to obtain a write lock on.
 *
 *   Must not be NULL.
 *
 * @return
 *   Status from: controller_lock_write().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: controller_lock_write().
 *
 * @see controller_lock_write()
 */
#ifndef _di_controller_lock_write_instance_type_
  extern f_status_t controller_lock_write_instance_type(const uint8_t type, controller_thread_t * const thread, f_thread_lock_t * const lock);
#endif // _di_controller_lock_write_instance_type_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_lock_h
