#include "../../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_error_rule_item_
  f_status_t controller_print_error_rule_item(fl_print_t * const print, controller_cache_action_t * const action, const uint8_t item, const f_status_t status) {

    if (!print || !print->custom || !action || status == F_interrupt) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    // fll_error_print() automatically locks, so manually handle only the mutex locking and flushing rather than calling controller_lock_print().
    f_thread_mutex_lock(&main->thread.lock.print);

    controller_print_error_rule_cache(print, action, item);

    f_file_stream_lock(print->to);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_rule_item_

#ifndef _di_controller_print_error_rule_item_execute_
  f_status_t controller_print_error_rule_item_execute(fl_print_t * const print, controller_instance_t * const instance, const uint8_t script_is, const f_string_static_t name, const f_status_t status) {

    if (!print || !instance || !instance->main) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_lock_print(print->to, &instance->main->thread);

    fl_print_format("%r%[%QThe %r '%]", print->to, f_string_eol_s, print->context, print->prefix, script_is ? controller_engine_s : controller_program_s, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, name, print->notable);

    if (status == F_control_group || status == F_limit || status == F_processor || status == F_schedule) {
      fl_print_format("%[' failed to setup the '%]%[", print->to, print->context, print->context, print->notable);

      if (status == F_control_group) {
        f_print_dynamic_raw(controller_cgroup_s, print->to);
      }
      else if (status == F_limit) {
        f_print_dynamic_raw(controller_limit_s, print->to);
      }
      else if (status == F_processor) {
        f_print_dynamic_raw(controller_processor_s, print->to);
      }
      else if (status == F_schedule) {
        f_print_dynamic_raw(controller_scheduler_s, print->to);
      }

      fl_print_format("%]%['.%]%r", print->to, print->notable, print->context, print->context, f_string_eol_s);
    }
    else if (WIFEXITED(instance->result) ? WEXITSTATUS(instance->result) : 0) {
      const uint8_t code = WIFEXITED(instance->result) ? WEXITSTATUS(instance->result) : 0;

      if (code == F_execute_access) {
        fl_print_format("%[' failed, access is denied.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_bad) {
        fl_print_format("%[' failed, unsupported format.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_buffer) {
        fl_print_format("%[' invalid memory access in arguments buffer.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_busy) {
        fl_print_format("%[' required resources are unavailable, too busy.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_capability) {
        fl_print_format("%[' failed to setup capabilities.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_control_group) {
        fl_print_format("%[' failed to setup control group.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_child) {
        fl_print_format("%[' failed to setup child process.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_directory_not) {
        fl_print_format("%[' invalid path, part of the path is not a valid directory.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_failure) {
        fl_print_format("%[' failed during execution.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_file_found_not) {
        fl_print_format("%[' failed, unable to find file.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_file_type_directory) {
        fl_print_format("%[' ELF interpreter is a directory.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_fork_not) {
        fl_print_format("%[' fork failure.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_format_not) {
        fl_print_format("%[' could not be executed because the program has an invalid ELF header.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_group) {
        fl_print_format("%[' failed to setup group.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_input_output) {
        fl_print_format("%[' I/O failure.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_limit) {
        fl_print_format("%[' failed to setup resource limits.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_loop) {
        fl_print_format("%[' max recursion reached.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_memory_not) {
        fl_print_format("%[' is out of memory.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_name_not) {
        fl_print_format("%[' file name or path is too long.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_nice) {
        fl_print_format("%[' failed to setup niceness.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_parameter) {
        fl_print_format("%[' failed due to an invalid parameter.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_pipe) {
        fl_print_format("%[' pipe failed.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_processor) {
        fl_print_format("%[' failed to setup processor affinity.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_prohibited) {
        fl_print_format("%[' access prohibited.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_resource_not) {
        fl_print_format("%[' resource limit reached.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_schedule) {
        fl_print_format("%[' failed to setup scheduler.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_terminal) {
        fl_print_format("%[' failed while processing the terminal.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_terminal_known_not) {
        fl_print_format("%[' cannot process terminal, unknown terminal control command.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_terminal_not) {
        fl_print_format("%[' cannot process terminal, not a known terminal.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_terminal_prohibited) {
        fl_print_format("%[' insufficient permissions to process the terminal.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_terminal_valid_not) {
        fl_print_format("%[' invalid parameter while processing the terminal.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_too_large) {
        fl_print_format("%[' too many arguments or arguments are too large.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_user) {
        fl_print_format("%[' failed to setup user.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_valid_not) {
        fl_print_format("%[' unknown ELF interpreter format.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_invoke_not) {
        fl_print_format("%[' cannot execute command.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_found_not) {
        fl_print_format("%[' command not found.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_found_not) {
        fl_print_format("%[' invalid argument to exit().%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_signal_hangup) {
        fl_print_format("%[' hang up signal received.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_signal_interrupt) {
        fl_print_format("%[' interrupt signal received.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_signal_quit) {
        fl_print_format("%[' quit signal received.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_signal_illegal) {
        fl_print_format("%[' illegal signal received.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_signal_trap) {
        fl_print_format("%[' trap signal received.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_signal_abort) {
        fl_print_format("%[' abort signal received.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_signal_bus_error) {
        fl_print_format("%[' bus error signal received.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_signal_floating_point_error) {
        fl_print_format("%[' floating point error signal received.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_signal_kill) {
        fl_print_format("%[' kill signal received.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_signal_user_1) {
        fl_print_format("%[' user 1 signal received.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_signal_segmentation_fault) {
        fl_print_format("%[' segmentation fault signal received.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_signal_user_2) {
        fl_print_format("%[' user 2 signal received.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_signal_broken_pipe) {
        fl_print_format("%[' broken pipe signal received.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_signal_alarm_clock) {
        fl_print_format("%[' alarm clock signal received.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_signal_termination) {
        fl_print_format("%[' terminate signal received.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_signal_stack_fault) {
        fl_print_format("%[' stack fault signal received.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_signal_child) {
        fl_print_format("%[' child signal received.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_signal_continue) {
        fl_print_format("%[' continue signal received.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_signal_stop) {
        fl_print_format("%[' stop signal received.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_signal_keyboard_stop) {
        fl_print_format("%[' keyboard stop signal received.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_signal_tty_in) {
        fl_print_format("%[' TTY in signal received.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_signal_tty_out) {
        fl_print_format("%[' TTY out signal received.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_signal_urgent) {
        fl_print_format("%[' urgent signal received.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_signal_cpu_limit) {
        fl_print_format("%[' CPU limit signal received.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_signal_file_size_limit) {
        fl_print_format("%[' file size signal received.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_signal_virtual_alarm_clock) {
        fl_print_format("%[' virtual alarm clock signal received.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_signal_profile_alarm_clock) {
        fl_print_format("%[' profile alarm clock signal received.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_signal_window_size_change) {
        fl_print_format("%[' window size change signal received.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_signal_pollable_event) {
        fl_print_format("%[' pollable signal received.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_signal_power_failure) {
        fl_print_format("%[' power failure signal received.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else if (code == F_execute_signal_bad_system_call) {
        fl_print_format("%[' bad system call signal received.%]%r", print->to, print->context, print->context, f_string_eol_s);
      }
      else {
        fl_print_format("%[' failed with the execute error code %]", print->to, print->context, print->context);
        fl_print_format("%[%i%]", print->to, print->notable, code, print->notable);
        fl_print_format(f_string_format_sentence_end_s.string, print->to, print->context, print->context, f_string_eol_s);
      }
    }
    else {
      fl_print_format("%[' failed.%]%r", print->to, print->context, print->context, f_string_eol_s);
    }

    controller_unlock_print_flush(print->to, &instance->main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_rule_item_execute_

#ifndef _di_controller_print_error_rule_item_need_want_wish_
  f_status_t controller_print_error_rule_item_need_want_wish(fl_print_t * const print, const f_string_static_t need_want_wish, const f_string_static_t value, const f_string_t why) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    if (print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

    fl_print_format("%r%[%QThe %r rule '%]", print->to, f_string_eol_s, print->context, print->prefix, need_want_wish, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, value, print->notable);
    fl_print_format("%[' %S.%]%r", print->to, print->context, why, print->context, f_string_eol_s);

    return F_okay;
  }
#endif // _di_controller_print_error_rule_item_need_want_wish_

#ifndef _di_controller_print_error_rule_item_rule_not_loaded_
  f_status_t controller_print_error_rule_item_rule_not_loaded(fl_print_t * const print, const f_string_static_t alias) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    if (print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

    fl_print_format("%r%[%QThe rule '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, alias, print->notable);
    fl_print_format("%[' is no longer loaded.%]%r", print->to, print->context, print->context, f_string_eol_s);

    return F_okay;
  }
#endif // _di_controller_print_error_rule_item_rule_not_loaded_

#ifdef __cplusplus
} // extern "C"
#endif
