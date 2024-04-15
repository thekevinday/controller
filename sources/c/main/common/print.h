/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common print functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_common_print_h
#define _controller_main_common_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A special array of strings intended for representing funciton names.
 *
 * These are primarily used for printing errors with the function names.
 *
 * The macro macro_controller_f() is used to reference the array index by the enum name.
 *
 * macro_controller_f():
 *   - name: The name of the function.
 */
#ifndef _di_controller_f_a_
  extern const f_string_t controller_f_a[];

  #define macro_controller_f(name) controller_f_a[controller_f_##name##_e]
#endif // _di_controller_f_a_

/**
 * An enum representing specific indexes within the above array.
 *
 * This is a convenience enum used to make code slightly more readable.
 */
#ifndef _di_controller_f_e_
  enum {
    controller_f_f_console_parameter_process_e,
    controller_f_f_path_current_e,
    controller_f_f_string_dynamic_append_e,
    controller_f_f_thread_create_e,
    controller_f_fll_program_parameter_process_context_standard_e,
    controller_f_fll_program_parameter_process_verbosity_standard_e,
  }; // enum
#endif // _di_controller_f_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_print_h
