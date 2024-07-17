/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common string structures for the init program.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_init_string_h
#define _controller_init_string_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program name.
 */
#ifndef _di_controller_program_name_s_
  #define CONTROLLER_program_name_s      "init"
  #define CONTROLLER_program_name_long_s "Init"

  #define CONTROLLER_program_name_s_length      4
  #define CONTROLLER_program_name_long_s_length 4
#endif // _di_controller_program_name_s_

/**
 * The program defaults.
 */
#ifndef _di_controller_default_s_

  // The init pid path is a system-specific path and needs to be more easily controlled at compile time.
  #if defined(_override_controller_path_pid_) && defined(_override_controller_path_pid_length_)
    #define CONTROLLER_default_path_pid_s        _override_controller_path_pid_
    #define CONTROLLER_default_path_pid_s_length _override_controller_path_pid_length_
  #else
    #define CONTROLLER_init_default_path_pid_s        "/run/init"
    #define CONTROLLER_init_default_path_pid_s_length 9
  #endif // defined(_override_controller_path_pid_) && defined(_override_controller_path_pid_length_)

  // The pid prefix is a system-specific path part and needs to be more easily controlled at compile time.
  #if defined(_override_controller_path_pid_prefix_) && defined(_override_controller_path_pid_prefix_length_)
    #define CONTROLLER_default_path_pid_prefix_s _override_controller_path_pid_prefix_

    #define CONTROLLER_default_path_pid_prefix_s_length _override_controller_path_pid_prefix_length_
  #else
    #define CONTROLLER_init_default_path_pid_prefix_s        "init-"
    #define CONTROLLER_init_default_path_pid_prefix_s_length 5
  #endif // defined(_override_controller_name_pid_prefix_) && defined(_override_controller_name_pid_prefix_length_)

  // The init settings path is a system-specific path part and needs to be more easily controlled at compile time.
  #if defined(_override_controller_path_settings_) && defined(_override_controller_path_settings_length_)
    #define CONTROLLER_default_path_settings_s        _override_controller_path_settings_
    #define CONTROLLER_default_path_settings_s_length _override_controller_path_settings_length_
  #else
    #define CONTROLLER_init_default_path_settings_s        "/etc/init"
    #define CONTROLLER_init_default_path_settings_s_length 9
  #endif // defined(_override_controller_path_settings_) && defined(_override_controller_path_settings_length_)

  // The socket path is a system-specific path and needs to be more easily controlled at compile time.
  #if defined(_override_controller_path_socket_) && defined(_override_controller_path_socket_length_)
    #define CONTROLLER_default_path_socket_s        _override_controller_path_socket_
    #define CONTROLLER_default_path_socket_s_length _override_controller_path_socket_length_
  #else
    #define CONTROLLER_init_default_path_socket_s        "/run/init"
    #define CONTROLLER_init_default_path_socket_s_length 9
  #endif // defined(_override_controller_path_socket_) && defined(_override_controller_path_socket_length_)

  // The socket prefix path is a system-specific path part and needs to be more easily controlled at compile time.
  #if defined(_override_controller_path_socket_prefix_) && defined(_override_controller_path_socket_prefix_length_)
    #define CONTROLLER_default_path_socket_prefix_s        _override_controller_path_socket_prefix_
    #define CONTROLLER_default_path_socket_prefix_s_length _override_controller_path_socket_prefix_length_
  #else
    #define CONTROLLER_init_default_path_socket_prefix_s        "init-"
    #define CONTROLLER_init_default_path_socket_prefix_s_length 5
  #endif // defined(_override_controller_path_socket_prefix_) && defined(_override_controller_path_socket_prefix_length_)
#endif // _di_controller_default_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_init_string_h
