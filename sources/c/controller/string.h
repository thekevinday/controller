/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common string structures for the controller program.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_controller_string_h
#define _controller_controller_string_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program name.
 */
#ifndef _di_controller_controller_program_name_s_
  #define CONTROLLER_controller_program_name_s      "controller"
  #define CONTROLLER_controller_program_name_long_s "Controller"

  #define CONTROLLER_controller_program_name_s_length      10
  #define CONTROLLER_controller_program_name_long_s_length 10

  extern const f_string_static_t controller_controller_program_name_s;
  extern const f_string_static_t controller_controller_program_name_long_s;
#endif // _di_controller_controller_program_name_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_controller_string_h
