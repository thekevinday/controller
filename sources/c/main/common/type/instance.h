/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common instance type structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_common_type_instance_h
#define _controller_main_common_type_instance_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Controller Instance.
 *
 * A Controller Instance represents the processing of a single Rule for some given Rule ID.
 *
 * The "cache" should only be used by the function processing/executing the process and as such should not require a write lock normally needed for thread-safety.
 * There must only be a single thread running any given Instance at a time, guaranteeing that the cache does not need read/write locks.
 *
 * id:        The ID of this process relative to the processes array.
 * id_thread: The thread ID, a valid ID when state is "active", and an invalid ID when the state is "busy".
 *
 * action:  The action being performed.
 * options: Configuration options for this thread.
 * state:   The state of the process.
 * type:    The currently active process type (from the controller_instance_type_*_e).
 * result:  The last return code from an execution of a process.
 *
 * active:    A read/write lock representing that something is currently using this (read locks = in use, write lock = begin deleting).
 * lock:      A read/write lock on the structure.
 * wait:      A thread condition to tell a process waiting process that the rule has is done being processed.
 * wait_lock: A mutex lock for working with "wait".
 *
 * child:     The process id of a child process, if one is running (when forking to execute a child process).
 * path_pids: An array of paths representing PID files.
 * stack:     A stack used to represent dependencies as Rule ID's to avoid circular Rule dependencies (If Rule A waits on Rule B, then Rule B must not wait on Rule A).
 *
 * rule:  A copy of the rule actively being executed.
 * cache: The cache used by this Instance.
 *
 * main:    The associated main program data (of type controller_main_t).
 * program: The associated program data.
 * thread:  The associated thread data (of type f_thread_t).
 */
#ifndef _di_controller_instance_t_
  typedef struct {
    f_number_unsigned_t id;
    f_thread_id_t id_thread;

    uint8_t action;
    uint8_t options;
    uint8_t state;
    uint8_t type;
    int result;

    f_thread_lock_t active;
    f_thread_lock_t lock;
    f_thread_condition_t wait;
    f_thread_mutex_t wait_lock;

    f_pids_t childs;
    f_string_dynamics_t path_pids;
    f_number_unsigneds_t stack;

    controller_rule_t rule;
    controller_cache_t cache;

    void *main;
    controller_program_t *program;
    void *thread;
  } controller_instance_t;

  #define controller_instance_t_initialize { \
    0, \
    f_thread_id_t_initialize, \
    0, \
    0, \
    0, \
    0, \
    0, \
    f_thread_lock_t_initialize, \
    f_thread_lock_t_initialize, \
    f_thread_condition_t_initialize, \
    f_thread_mutex_t_initialize, \
    f_pids_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_number_unsigneds_t_initialize, \
    controller_rule_t_initialize, \
    controller_cache_t_initialize, \
    0, \
    0, \
    0, \
  }
#endif // _di_controller_instance_t_

/**
 * An array of Controller Instances.
 *
 * This has a circular dependency with controller_thread_t.
 *
 * array: An array of Instances.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_controller_instances_t_
  typedef struct {
    controller_instance_t **array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } controller_instances_t;

  #define controller_instances_t_initialize { \
    0, \
    0, \
    0, \
  }
#endif // _di_controller_instances_t_

/**
 * Delete the Controller Instance.
 *
 * @param instance
 *   The Controller Instance.
 *
 *   Must not be NULL.
 *
 * @see controller_cache_delete()
 */
#ifndef _di_controller_instance_delete_
  extern void controller_instance_delete(controller_instance_t * const instance);
#endif // _di_controller_instance_delete_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_instances_t structure.
 *
 * This is only called when shrinking the array and generally should perform de-allocations.
 *
 * This does not do parameter checking.
 *
 * @param start
 *   The inclusive start position in the array to start deleting.
 * @param stop
 *   The exclusive stop position in the array to stop deleting.
 * @param array
 *   The array structure to delete all values of.
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see controller_instance_delete()
 */
#ifndef _di_f_instances_delete_callback_
  extern f_status_t f_instances_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_instances_delete_callback_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_type_process_h
