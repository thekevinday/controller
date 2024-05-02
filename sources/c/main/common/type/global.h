/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common global type structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_common_type_global_h
#define _controller_main_common_type_global_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A wrapper used for passing a common set of all data, particularly for sharing between threads.
 *
 * main:    The main program data.
 * program: The program data.
 * thread:  The thread data for a specific thread.
 */
#ifndef _di_controller_global_t_
  typedef struct {
    controller_main_t *main;
    controller_program_t *program;
    controller_thread_t *thread;
  } controller_global_t;

  #define controller_global_t_initialize { 0, 0, 0 }

  #define macro_controller_global_t_initialize(main, program, thread) { \
    main, \
    program, \
    thread, \
  }
#endif // _di_controller_global_t_

/**
 * A structure for passing data to the interrupt state function.
 *
 * is_normal: Boolean designating if this is operating in a normal state.
 * thread:    The thread data.
 */
#ifndef _di_controller_interrupt_t_
  typedef struct {
    bool is_normal;

    controller_thread_t *thread;
  } controller_interrupt_t;

  #define controller_interrupt_t_initialize { \
    F_true, \
    0, \
  }

  #define macro_controller_interrupt_t_initialize_1(is_normal, thread) { \
    is_normal, \
    thread, \
  }
#endif // _di_controller_interrupt_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_type_global_h
