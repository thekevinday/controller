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
 * The typedef for this is located in the defs.h header.
 *
 * Properties:
 *   - main:    The main program data.
 *   - program: The program data.
 *   - thread:  The thread data for a specific thread.
 *
 *   - message: The output file for normal output messages (often stdout), but with custom set to (controller_global_t *).
 *   - output:  The output file for normal/non-message output, aka data output (often stdout or a file), but with custom set to (controller_global_t *).
 *   - error:   The output file for error output messages, but with custom set to (controller_global_t *).
 *   - warning: The output file for warning output messages, but with custom set to (controller_global_t *).
 *   - debug:   The output file for debug output messages, but with custom set to (controller_global_t *).
 */
#ifndef _di_controller_global_t_
  struct controller_global_t_ {
    controller_t *main;
    controller_program_t *program;
    controller_thread_t *thread;

    fl_print_t *message;
    fl_print_t *output;
    fl_print_t *error;
    fl_print_t *warning;
    fl_print_t *debug;
  };

  #define controller_global_t_initialize { 0, 0, 0, 0, 0, 0, 0, 0 }

  #define macro_controller_global_t_initialize_1(main, program, thread, message, output, error, warning, debug) { \
    main, \
    program, \
    thread, \
    message, \
    output, \
    error, \
    warning, \
    debug, \
  }
#endif // _di_controller_global_t_

/**
 * A structure for passing data to the interrupt state function.
 *
 * Properties:
 *   - is_normal: Boolean designating if this is operating in a normal state.
 *   - global:    The global data.
 */
#ifndef _di_controller_interrupt_t_
  typedef struct {
    bool is_normal;

    controller_global_t *global;
  } controller_interrupt_t;

  #define controller_interrupt_t_initialize { \
    F_true, \
    0, \
  }

  #define macro_controller_interrupt_t_initialize_1(is_normal, global) { \
    is_normal, \
    global, \
  }
#endif // _di_controller_interrupt_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_type_global_h
