/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common string structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_common_string_h
#define _controller_main_common_string_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program version.
 */
#ifndef _di_controller_program_version_s_
  #define CONTROLLER_program_version_major_s F_string_ascii_0_s
  #define CONTROLLER_program_version_minor_s F_string_ascii_7_s
  #define CONTROLLER_program_version_micro_s F_string_ascii_0_s

  #define CONTROLLER_program_version_major_s_length F_string_ascii_0_s_length
  #define CONTROLLER_program_version_minor_s_length F_string_ascii_7_s_length
  #define CONTROLLER_program_version_micro_s_length F_string_ascii_0_s_length

  #if !(defined(CONTROLLER_program_version_nano_prefix_s) && defined(CONTROLLER_program_version_nano_prefix_s_length))
    #define CONTROLLER_program_version_nano_prefix_s
    #define CONTROLLER_program_version_nano_prefix_s_length 0
  #endif // !(defined(CONTROLLER_program_version_nano_prefix_s) && defined(CONTROLLER_program_version_nano_prefix_s_length))

  #if !(defined(CONTROLLER_program_version_nano_s) && defined(CONTROLLER_program_version_nano_s_length))
    #define CONTROLLER_program_version_nano_s
    #define CONTROLLER_program_version_nano_s_length 0
  #endif // !(defined(CONTROLLER_program_version_nano_s) && defined(CONTROLLER_program_version_nano_s_length))

  #define CONTROLLER_program_version_s CONTROLLER_program_version_major_s F_string_ascii_period_s CONTROLLER_program_version_minor_s F_string_ascii_period_s CONTROLLER_program_version_micro_s CONTROLLER_program_version_nano_prefix_s CONTROLLER_program_version_nano_s

  #define CONTROLLER_program_version_s_length CONTROLLER_program_version_major_s_length + F_string_ascii_period_s_length + CONTROLLER_program_version_minor_s_length + F_string_ascii_period_s_length + CONTROLLER_program_version_micro_s_length + CONTROLLER_program_version_nano_prefix_s_length + CONTROLLER_program_version_nano_s_length

  extern const f_string_static_t controller_program_version_s;
#endif // _di_controller_program_version_s_

/**
 * The program name.
 */
#ifndef _di_controller_program_name_s_
  #define CONTROLLER_program_name_s      "controller"
  #define CONTROLLER_program_name_long_s "Controller"

  #define CONTROLLER_program_name_s_length      10
  #define CONTROLLER_program_name_long_s_length 10

  extern const f_string_static_t controller_program_name_s;
  extern const f_string_static_t controller_program_name_long_s;
#endif // _di_controller_program_name_s_

/**
 * The main program parameters.
 */
#ifndef _di_controller_parameter_s_
  #define CONTROLLER_short_controller_s "e"

  #define CONTROLLER_long_controller_s "controller"

  #define CONTROLLER_short_controller_s_length 1

  #define CONTROLLER_long_controller_s_length 7

  extern const f_string_static_t controller_short_controller_s;

  extern const f_string_static_t controller_long_controller_s;
#endif // _di_controller_parameter_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_string_h
