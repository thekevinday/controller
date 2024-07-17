#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_message_help_
  f_status_t controller_print_message_help(fl_print_t * const print, const uint8_t uninterrupt) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);

    controller_t * const main = (controller_t *) print->custom;

    f_file_stream_lock(print->to);

    fll_program_print_help_header(print, controller_program_name_long_s, controller_program_version_s);

    fll_program_print_help_option_standard(print);

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fll_program_print_help_option(print, controller_short_cgroup_s, controller_long_cgroup_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "         Specify a custom control group file path, such as '" F_control_group_path_system_prefix_s F_control_group_path_system_default_s "'.");
    fll_program_print_help_option(print, controller_short_daemon_s, controller_long_daemon_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "         Run in daemon only mode (do not process the entry).");
    fll_program_print_help_option(print, controller_short_interruptible_s, controller_long_interruptible_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "  Designate that this program can be interrupted by a signal.");
    fll_program_print_help_option(print, controller_short_pid_s, controller_long_pid_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "            Specify a custom pid file path, such as 'controller/run/default.pid'.");
    fll_program_print_help_option(print, controller_short_settings_s, controller_long_settings_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "       Specify a custom settings path, such as 'controller/'.");
    fll_program_print_help_option(print, controller_short_simulate_s, controller_long_simulate_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "       Run as a simulation.");
    fll_program_print_help_option(print, controller_short_socket_s, controller_long_socket_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "         Specify a custom socket file path, such as 'controller/run/default.socket'.");
    fll_program_print_help_option(print, controller_short_uninterruptible_s, controller_long_uninterruptible_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "Designate that this program cannot be interrupted by a signal.");
    fll_program_print_help_option(print, controller_short_validate_s, controller_long_validate_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "       Validate the settings (entry and rules) without running (does not simulate).");

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fll_program_print_help_usage(print, controller_program_name_s, f_string_empty_s);

    fl_print_format("%r  When both the %[%r%r%] parameter and the", print->to, f_string_eol_s, print->set->notable, f_console_symbol_long_normal_s, controller_long_simulate_s, print->set->notable);
    fl_print_format(" %[%r%r%] parameter are specified, then additional information on each would be executed Rule is printed but no simulation is performed.%r%r", print->to, print->set->notable, f_console_symbol_long_normal_s, controller_long_validate_s, print->set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The default interrupt behavior is to operate as if the %[%r%r%] parameter is passed.%r%r", print->to, print->set->notable, f_console_symbol_long_normal_s, uninterrupt ? controller_long_uninterruptible_s : controller_long_interruptible_s, print->set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  Specify an empty string for the %[%r%r%] parameter to disable pid file creation for this program.%r", print->to, print->set->notable, f_console_symbol_long_normal_s, controller_long_pid_s, print->set->notable, f_string_eol_s);

    f_file_stream_flush(print->to);
    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_controller_print_message_help_

#ifdef __cplusplus
} // extern "C"
#endif
