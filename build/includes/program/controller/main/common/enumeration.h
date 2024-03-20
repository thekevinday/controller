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
 * Flags passed to the main function or program.
 *
 * When number mode is not specified, then mode is "string" mode (there is no flag for "string" mode).
 *
 * controller_main_flag_*_e:
 *   - none:                   No flags set.
 *   - copyright:              Print copyright.
 *   - error:                  Check if status is "error".
 *   - fine:                   Check if status is "fine".
 *   - help:                   Print help.
 *   - pipe:                   Use the input pipe.
 *   - print_first:            When set, print new line to message output on program begin after loading settings.
 *   - print_last:             When set, print new line to message output on program end.
 *   - version:                Print version.
 *   - version_copyright_help: A helper flag representing version, copyright, and help flag bits being set.
 *   - warning:                Check if status is "warning".
 */
#ifndef _di_controller_main_flag_e_
  enum {
    controller_main_flag_none_e                   = 0x0,
    controller_main_flag_copyright_e              = 0x1,
    controller_main_flag_error_e                  = 0x2,
    controller_main_flag_fine_e                   = 0x4,
    controller_main_flag_help_e                   = 0x8,
    controller_main_flag_pipe_e                   = 0x10,
    controller_main_flag_print_first_e            = 0x20,
    controller_main_flag_print_last_e             = 0x40,
    controller_main_flag_version_e                = 0x80,
    controller_main_flag_version_copyright_help_e = 0x89,
    controller_main_flag_warning_e                = 0x100,
  }; // enum
#endif // _di_controller_main_flag_e_

/**
 * The main program parameters.
 */
#ifndef _di_controller_parameter_e_
  enum {
    controller_parameter_controller_e = f_console_standard_parameter_last_e,
  }; // enum

  #define controller_console_parameter_t_initialize \
    { \
      macro_fll_program_console_parameter_standard_initialize, \
      \
      macro_f_console_parameter_t_initialize_3(controller_short_controller_s, controller_long_controller_s, 0, f_console_flag_normal_e), \
    }

  #define controller_parameter_total_d (f_console_parameter_state_type_total_d + 1)
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

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_enumeration_h
