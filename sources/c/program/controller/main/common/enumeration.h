/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common enumeration types.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_common_enumeration_h
#define _controller_main_common_enumeration_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The main program parameters.
 */
#ifndef _di_controller_parameter_e_
  enum {
    controller_parameter_cgroup_e = f_console_standard_parameter_last_e,
    controller_parameter_daemon_e,
    controller_parameter_interruptible_e,
    controller_parameter_pid_e,
    controller_parameter_settings_e,
    controller_parameter_simulate_e,
    controller_parameter_socket_e,
    controller_parameter_uninterruptible_e,
    controller_parameter_validate_e,
  }; // enum

  #define controller_console_parameter_t_initialize \
    { \
      macro_fll_program_console_parameter_standard_initialize, \
      \
      macro_f_console_parameter_t_initialize_3(controller_short_cgroup_s,          controller_long_cgroup_s,          1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(controller_short_daemon_s,          controller_long_daemon_s,          0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(controller_short_interruptible_s,   controller_long_interruptible_s,   0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(controller_short_pid_s,             controller_long_pid_s,             1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(controller_short_settings_s,        controller_long_settings_s,        1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(controller_short_simulate_s,        controller_long_simulate_s,        0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(controller_short_socket_s,          controller_long_socket_s,          1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(controller_short_uninterruptible_s, controller_long_uninterruptible_s, 0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(controller_short_validate_s,        controller_long_validate_s,        0, f_console_flag_normal_e), \
    }

  #define controller_parameter_total_d (f_console_parameter_state_type_total_d + 9)
#endif // _di_controller_parameter_e_

/**
 * Flags for fine-tuned print control.
 *
 * controller_print_flag_*_e:
 *   - none:    No flags set.
 *   - debug:   Stream is for debug printing.
 *   - error:   Stream is for error printing.
 *   - in:      Stream is a source file.
 *   - message: Stream is for message printing.
 *   - out:     Stream is a destination file.
 *   - warning: Stream is for warning printing.
 */
#ifndef _di_controller_print_flag_e_
  enum {
    controller_print_flag_none_e    = 0x0,
    controller_print_flag_debug_e   = 0x1,
    controller_print_flag_error_e   = 0x2,
    controller_print_flag_file_e    = 0x4,
    controller_print_flag_in_e      = 0x8,
    controller_print_flag_out_e     = 0x10,
    controller_print_flag_message_e = 0x20,
    controller_print_flag_warning_e = 0x40,
  }; // enum
#endif // _di_controller_print_flag_e_

/**
 * A set of codes for resource limitations.
 *
 * This essentally converts the POSIX standard names into a more verbose format.
 */
#ifndef _di_controller_resource_limit_type_e_
  enum {
    controller_resource_limit_type_as_e = RLIMIT_AS,
    controller_resource_limit_type_core_e = RLIMIT_CORE,
    controller_resource_limit_type_cpu_e = RLIMIT_CPU,
    controller_resource_limit_type_data_e = RLIMIT_DATA,
    controller_resource_limit_type_fsize_e = RLIMIT_FSIZE,
    controller_resource_limit_type_locks_e = RLIMIT_LOCKS,
    controller_resource_limit_type_memlock_e = RLIMIT_MEMLOCK,
    controller_resource_limit_type_msgqueue_e = RLIMIT_MSGQUEUE,
    controller_resource_limit_type_nice_e = RLIMIT_NICE,
    controller_resource_limit_type_nofile_e = RLIMIT_NOFILE,
    controller_resource_limit_type_nproc_e = RLIMIT_NPROC,
    controller_resource_limit_type_rss_e = RLIMIT_RSS,
    controller_resource_limit_type_rtprio_e = RLIMIT_RTPRIO,
    controller_resource_limit_type_rttime_e = RLIMIT_RTTIME,
    controller_resource_limit_type_sigpending_e = RLIMIT_SIGPENDING,
    controller_resource_limit_type_stack_e = RLIMIT_STACK,
  }; // enum
#endif // _di_controller_resource_limit_type_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_enumeration_h
