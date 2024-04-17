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
 *
 * The implementation for this is defined within the individual programs.
 */
#ifndef _di_controller_program_name_s_
  extern const f_string_static_t controller_program_name_s;
  extern const f_string_static_t controller_program_name_long_s;
#endif // _di_controller_program_name_s_

/**
 * The main program parameters.
 */
#ifndef _di_controller_parameter_s_
  #define CONTROLLER_short_cgroup_s          "c"
  #define CONTROLLER_short_daemon_s          "d"
  #define CONTROLLER_short_interruptible_s   "I"
  #define CONTROLLER_short_pid_s             "p"
  #define CONTROLLER_short_settings_s        "s"
  #define CONTROLLER_short_simulate_s        "S"
  #define CONTROLLER_short_socket_s          "k"
  #define CONTROLLER_short_uninterruptible_s "U"
  #define CONTROLLER_short_validate_s        "v"

  #define CONTROLLER_long_cgroup_s          "cgroup"
  #define CONTROLLER_long_daemon_s          "daemon"
  #define CONTROLLER_long_interruptible_s   "interruptible"
  #define CONTROLLER_long_pid_s             "pid"
  #define CONTROLLER_long_settings_s        "settings"
  #define CONTROLLER_long_simulate_s        "simulate"
  #define CONTROLLER_long_socket_s          "socket"
  #define CONTROLLER_long_uninterruptible_s "uninterruptible"
  #define CONTROLLER_long_validate_s        "validate"

  #define CONTROLLER_short_cgroup_s_length          1
  #define CONTROLLER_short_daemon_s_length          1
  #define CONTROLLER_short_interruptible_s_length   1
  #define CONTROLLER_short_pid_s_length             1
  #define CONTROLLER_short_settings_s_length        1
  #define CONTROLLER_short_simulate_s_length        1
  #define CONTROLLER_short_socket_s_length          1
  #define CONTROLLER_short_uninterruptible_s_length 1
  #define CONTROLLER_short_validate_s_length        1

  #define CONTROLLER_long_cgroup_s_length          6
  #define CONTROLLER_long_daemon_s_length          6
  #define CONTROLLER_long_interruptible_s_length   13
  #define CONTROLLER_long_pid_s_length             3
  #define CONTROLLER_long_settings_s_length        8
  #define CONTROLLER_long_simulate_s_length        8
  #define CONTROLLER_long_socket_s_length          6
  #define CONTROLLER_long_uninterruptible_s_length 15
  #define CONTROLLER_long_validate_s_length        8

  extern const f_string_static_t controller_short_cgroup_s;
  extern const f_string_static_t controller_short_daemon_s;
  extern const f_string_static_t controller_short_interruptible_s;
  extern const f_string_static_t controller_short_pid_s;
  extern const f_string_static_t controller_short_settings_s;
  extern const f_string_static_t controller_short_simulate_s;
  extern const f_string_static_t controller_short_socket_s;
  extern const f_string_static_t controller_short_uninterruptible_s;
  extern const f_string_static_t controller_short_validate_s;

  extern const f_string_static_t controller_long_cgroup_s;
  extern const f_string_static_t controller_long_daemon_s;
  extern const f_string_static_t controller_long_init_s;
  extern const f_string_static_t controller_long_interruptible_s;
  extern const f_string_static_t controller_long_pid_s;
  extern const f_string_static_t controller_long_settings_s;
  extern const f_string_static_t controller_long_simulate_s;
  extern const f_string_static_t controller_long_socket_s;
  extern const f_string_static_t controller_long_uninterruptible_s;
  extern const f_string_static_t controller_long_validate_s;
#endif // _di_controller_parameter_s_

/**
 * The program defaults.
 *
 * These are defines inside the programs utilizing this rather than in the library itself.
 */
#ifndef _di_controller_default_s_

  // The pid path is a system-specific path and needs to be more easily controlled at compile time.
  #if defined(_override_controller_path_pid_) && defined(_override_controller_path_pid_length_)
    #define CONTROLLER_default_path_pid_s        _override_controller_path_pid_
    #define CONTROLLER_default_path_pid_s_length _override_controller_path_pid_length_
  #else
    #define CONTROLLER_default_path_pid_s        "./run"
    #define CONTROLLER_default_path_pid_s_length 5
  #endif // defined(_override_controller_path_pid_) && defined(_override_controller_path_pid_length_)

  // The pid prefix is a system-specific path part and needs to be more easily controlled at compile time.
  #if defined(_override_controller_path_pid_prefix_) && defined(_override_controller_path_pid_prefix_length_)
    #define CONTROLLER_default_path_pid_prefix_s _override_controller_path_pid_prefix_

    #define CONTROLLER_default_path_pid_prefix_s_length _override_controller_path_pid_prefix_length_
  #else
    #define CONTROLLER_default_path_pid_prefix_s        ""
    #define CONTROLLER_default_path_pid_prefix_s_length 0
  #endif // defined(_override_controller_name_pid_prefix_) && defined(_override_controller_name_pid_prefix_length_)

  // The socket suffix path is a system-specific path part and needs to be more easily controlled at compile time.
  #if defined(_override_controller_path_pid_suffix_) && defined(_override_controller_path_pid_suffix_length_)
    #define CONTROLLER_default_path_pid_suffix_s        _override_controller_path_pid_suffix_
    #define CONTROLLER_default_path_pid_suffix_s_length _override_controller_path_pid_suffix_length_
  #else
    #define CONTROLLER_default_path_pid_suffix_s        ".pid"
    #define CONTROLLER_default_path_pid_suffix_s_length 4
  #endif // defined(_override_controller_name_pid_suffix_) && defined(_override_controller_name_pid_suffix_length_)

  // The settings path is a system-specific path part and needs to be more easily controlled at compile time.
  #if defined(_override_controller_path_settings_) && defined(_override_controller_path_settings_length_)
    #define CONTROLLER_default_path_settings_s        _override_controller_path_settings_
    #define CONTROLLER_default_path_settings_s_length _override_controller_path_settings_length_
  #else
    #define CONTROLLER_default_path_settings_s        "./"
    #define CONTROLLER_default_path_settings_s_length 2
  #endif // defined(_override_controller_path_settings_) && defined(_override_controller_path_settings_length_)

  // The socket path is a system-specific path and needs to be more easily controlled at compile time.
  #if defined(_override_controller_path_socket_) && defined(_override_controller_path_socket_length_)
    #define CONTROLLER_default_path_socket_s        _override_controller_path_socket_
    #define CONTROLLER_default_path_socket_s_length _override_controller_path_socket_length_
  #else
    #define CONTROLLER_default_path_socket_s        "./run"
    #define CONTROLLER_default_path_socket_s_length 5
  #endif // defined(_override_controller_path_socket_) && defined(_override_controller_path_socket_length_)

  // The socket prefix path is a system-specific path part and needs to be more easily controlled at compile time.
  #if defined(_override_controller_path_socket_prefix_) && defined(_override_controller_path_socket_prefix_length_)
    #define CONTROLLER_default_path_socket_prefix_s        _override_controller_path_socket_prefix_
    #define CONTROLLER_default_path_socket_prefix_s_length _override_controller_path_socket_prefix_length_
  #else
    #define CONTROLLER_default_path_socket_prefix_s        ""
    #define CONTROLLER_default_path_socket_prefix_s_length 0
  #endif // defined(_override_controller_path_socket_prefix_) && defined(_override_controller_path_socket_prefix_length_)

  // The socket suffix path is a system-specific path part and needs to be more easily controlled at compile time.
  #if defined(_override_controller_path_socket_suffix_) && defined(_override_controller_path_socket_suffix_length_)
    #define CONTROLLER_default_path_socket_suffix_s        _override_controller_path_socket_suffix_
    #define CONTROLLER_default_path_socket_suffix_s_length _override_controller_path_socket_suffix_length_
  #else
    #define CONTROLLER_default_path_socket_suffix_s        ".socket"
    #define CONTROLLER_default_path_socket_suffix_s_length 7
  #endif // defined(_override_controller_path_socket_suffix_) && defined(_override_controller_path_socket_suffix_length_)

  #if defined(_override_controller_default_program_script_) && defined(_override_controller_default_program_script_length_)
    #define CONTROLLER_default_engine_s        _override_controller_default_engine_
    #define CONTROLLER_default_engine_s_length _override_controller_default_engine_length_
  #else
    #define CONTROLLER_default_engine_s        "bash"
    #define CONTROLLER_default_engine_s_length 4
  #endif // defined(_override_controller_default_program_script_) && defined(_override_controller_default_program_script_length_)

  extern const f_string_static_t controller_default_engine_s;
  extern const f_string_static_t controller_default_path_pid_s;
  extern const f_string_static_t controller_default_path_pid_prefix_s;
  extern const f_string_static_t controller_default_path_pid_suffix_s;
  extern const f_string_static_t controller_default_path_settings_s;
  extern const f_string_static_t controller_default_path_socket_s;
  extern const f_string_static_t controller_default_path_socket_prefix_s;
  extern const f_string_static_t controller_default_path_socket_suffix_s;
#endif // _di_controller_default_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_string_h
