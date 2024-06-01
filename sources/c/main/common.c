#include "controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_main_error_simplify_
  f_status_t controller_main_error_simplify(const f_status_t status) {

    if (status == F_memory_not) {
      return F_status_set_error(F_memory);
    }

    if (status == F_file_open_max || status == F_space_not || status == F_busy) {
      return F_status_set_error(F_resource);
    }

    if (status == F_access_denied || status == F_filesystem_quota_block || status == F_prohibited || status == F_input_output) {
      return F_status_set_error(F_access);
    }

    if (status == F_complete_not_utf || status == F_complete_not_utf_block || status == F_complete_not_utf_eof || status == F_complete_not_utf_eol || status == F_complete_not_utf_eos || status == F_complete_not_utf_stop) {
      return F_status_set_error(F_encoding);
    }

    if (status == F_number || status == F_number_negative || status == F_number_positive || status == F_number_overflow) {
      return F_status_set_error(F_number);
    }

    if (status == F_parameter || status == F_found_not || status == F_interrupt || status == F_support_not || status == F_critical) {
      return F_status_set_error(status);
    }

    if (status == F_valid_not) {
      return F_status_set_error(F_valid_not);
    }

    return F_status_set_error(F_failure);
  }
#endif // _di_controller_main_error_simplify_

#ifndef _di_controller_main_range_after_number_sign_
  f_range_t controller_main_range_after_number_sign(const f_string_static_t buffer, const f_range_t range) {

    f_range_t result = range;

    for (; result.start <= result.stop; ++result.start) {

      if (!buffer.string[result.start]) continue;

      if (buffer.string[result.start] == f_string_ascii_minus_s.string[0] || buffer.string[result.start] == f_string_ascii_plus_s.string[0]) {
        ++result.start;
      }

      break;
    } // for

    return result;
  }
#endif // _di_controller_main_range_after_number_sign_

#ifndef _di_controller_main_setting_load_
  void controller_main_setting_load(const f_console_arguments_t arguments, controller_main_t * const main, controller_program_t * const program) {

    if (!main || !program) return;

    main->setting.state.step_small = controller_allocation_console_d;

    f_console_parameter_process(arguments, &main->program.parameters, &main->setting.state, 0);

    main->setting.state.step_small = controller_allocation_small_d;

    if (F_status_is_error(main->setting.state.status)) {
      controller_main_print_error(&main->program.error, macro_controller_f(f_console_parameter_process));

      return;
    }

    main->setting.state.status = fll_program_parameter_process_context_standard(F_true, &main->program);

    if (F_status_is_error(main->setting.state.status)) {
      controller_main_print_error(&main->program.error, macro_controller_f(fll_program_parameter_process_context_standard));

      return;
    }

    main->setting.state.status = fll_program_parameter_process_verbosity_standard(F_true, &main->program);

    if (F_status_is_error(main->setting.state.status)) {
      controller_main_print_error(&main->program.error, macro_controller_f(fll_program_parameter_process_verbosity_standard));

      return;
    }

    if (main->program.parameters.array[f_console_standard_parameter_help_e].result & f_console_result_found_e) {
      main->setting.flag |= controller_main_flag_help_e;

      return;
    }

    if (main->program.parameters.array[f_console_standard_parameter_version_e].result & f_console_result_found_e) {
      main->setting.flag |= controller_main_flag_version_e;

      return;
    }

    if (main->program.parameters.array[f_console_standard_parameter_copyright_e].result & f_console_result_found_e) {
      main->setting.flag |= controller_main_flag_copyright_e;

      return;
    }

    if (main->program.pipe & fll_program_data_pipe_input_e) {
      main->setting.flag |= controller_main_flag_pipe_e;
    }
    else {
      main->setting.flag &= ~controller_main_flag_pipe_e;
    }

    f_string_static_t * const args = main->program.parameters.arguments.array;
    f_number_unsigned_t index = 0;

    program->control.server.domain = f_socket_protocol_family_local_e;
    program->control.server.type = f_socket_type_stream_e;
    program->control.server.form = f_socket_address_form_local_e;

    memset(&program->control.server.address, 0, sizeof(f_socket_address_t));

    {
      const uint8_t codes[] = {
        controller_parameter_cgroup_e,
        controller_parameter_daemon_e,
        controller_parameter_pid_e,
        controller_parameter_settings_e,
      };

      const f_string_static_t strings[] = {
        controller_long_cgroup_s,
        controller_long_daemon_s,
        controller_long_pid_s,
        controller_long_settings_s,
      };

      for (index = 0; index < 4; ++index) {

        if (main->program.parameters.array[controller_parameter_settings_e].result & codes[index]) {
          main->setting.state.status = F_status_set_error(F_parameter);

          fll_program_print_error_parameter_missing_value(&main->program.error, f_console_symbol_long_normal_s, strings[index]);

          return;
        }
      } // for
    }

    // The first remaining argument represents the entry name.
    main->setting.state.status = f_string_dynamic_append(main->program.parameters.remaining.used ? args[main->program.parameters.remaining.array[0]] : controller_default_s, &program->name_entry);

    if (F_status_is_error(main->setting.state.status)) {
      controller_main_print_error(&main->program.error, macro_controller_f(fll_program_parameter_process_verbosity_standard));

      return;
    }

    main->setting.state.status = f_path_current(F_false, &program->path_current);

    if (F_status_is_error(main->setting.state.status)) {
      controller_main_print_error(&main->program.error, macro_controller_f(f_path_current));

      return;
    }

    program->path_setting.used = 0;

    if (main->program.parameters.array[controller_parameter_settings_e].locations.used) {
      index = main->program.parameters.array[controller_parameter_settings_e].values.array[main->program.parameters.array[controller_parameter_settings_e].values.used - 1];

      controller_path_canonical_relative(main, program->path_current, args[index], &program->path_setting);

      if (F_status_is_error(main->setting.state.status)) {
        controller_main_print_error_file(&main->program.error, macro_controller_f(controller_path_canonical_relative), args[index], f_file_operation_verify_s, fll_error_file_type_path_e);

        return;
      }
    }
    else {
      main->setting.state.status = f_string_dynamic_append(controller_default_path_settings_s, &program->path_setting);

      if (F_status_is_error(main->setting.state.status)) {
        controller_main_print_error(&main->program.error, macro_controller_f(f_string_dynamic_append));

        return;
      }
    }

    if (!program->path_pid.used && !main->program.parameters.array[controller_parameter_pid_e].locations.used) {
      main->setting.state.status = f_string_dynamic_append(controller_default_path_pid_s, &program->path_pid);

      if (F_status_is_error_not(main->setting.state.status)) {
        main->setting.state.status = f_string_dynamic_append(f_path_separator_s, &program->path_pid);
      }

      if (F_status_is_error_not(main->setting.state.status)) {
        main->setting.state.status = f_string_dynamic_append(controller_default_path_pid_prefix_s, &program->path_pid);
      }

      if (F_status_is_error_not(main->setting.state.status)) {
        main->setting.state.status = f_string_dynamic_append(program->name_entry, &program->path_pid);
      }

      if (F_status_is_error_not(main->setting.state.status)) {
        main->setting.state.status = f_string_dynamic_append(controller_default_path_pid_suffix_s, &program->path_pid);
      }

      if (F_status_is_error(main->setting.state.status)) {
        controller_main_print_error(&main->program.error, macro_controller_f(f_string_dynamic_append));

        return;
      }
    }

    if (main->program.parameters.array[controller_parameter_cgroup_e].locations.used) {
      index = main->program.parameters.array[controller_parameter_cgroup_e].values.array[main->program.parameters.array[controller_parameter_cgroup_e].values.used - 1];

      if (args[index].used) {
        controller_path_canonical_relative(main, program->path_current, args[index], &program->path_cgroup);

        if (F_status_is_error(main->setting.state.status)) {
          controller_main_print_error_file(&main->program.error, macro_controller_f(controller_path_canonical_relative), args[index], f_file_operation_verify_s, fll_error_file_type_path_e);

          return;
        }

        main->setting.state.status = f_string_append_assure(F_path_separator_s, 1, &program->path_cgroup);

        if (F_status_is_error(main->setting.state.status)) {
          controller_main_print_error(&main->program.error, macro_controller_f(f_string_append_assure));

          return;
        }
      }
      else {
        controller_main_print_debug_directory_path_empty(&main->program.warning, f_console_symbol_long_normal_s, controller_long_cgroup_s);
      }
    }
    else {
      main->setting.state.status = f_string_dynamic_append_nulless(f_control_group_path_system_prefix_s, &program->path_cgroup);

      if (F_status_is_error_not(main->setting.state.status)) {
        main->setting.state.status = f_string_dynamic_append_nulless(f_control_group_path_system_default_s, &program->path_cgroup);
      }

      if (F_status_is_error(main->setting.state.status)) {
        controller_main_print_error(&main->program.error, macro_controller_f(f_string_dynamic_append_nulless));

        return;
      }

      main->setting.state.status = f_string_dynamic_append_assure(f_path_separator_s, &program->path_cgroup);

      if (F_status_is_error(main->setting.state.status)) {
        controller_main_print_error(&main->program.error, macro_controller_f(f_string_dynamic_append_assure));

        return;
      }
    }

    if (main->program.parameters.array[controller_parameter_interruptible_e].result & f_console_result_found_e) {
      if (main->program.parameters.array[controller_parameter_uninterruptible_e].result & f_console_result_found_e) {
        if (main->program.parameters.array[controller_parameter_interruptible_e].location < main->program.parameters.array[controller_parameter_uninterruptible_e].location) {
          main->setting.flag &= ~controller_main_flag_interruptible_e;
        }
        else {
          main->setting.flag |= controller_main_flag_interruptible_e;
        }
      }
      else {
        main->setting.flag |= controller_main_flag_interruptible_e;
      }
    }
    else if (main->program.parameters.array[controller_parameter_uninterruptible_e].result & f_console_result_found_e) {
      main->setting.flag &= ~controller_main_flag_interruptible_e;
    }

    if (main->program.parameters.array[f_console_standard_parameter_daemon_e].result & f_console_result_found_e) {
      main->setting.flag |= controller_main_flag_daemon_e;
    }

    if (main->program.parameters.array[controller_parameter_validate_e].result & f_console_result_found_e) {
      main->setting.flag |= controller_main_flag_validate_e;
    }
  }
#endif // _di_controller_main_setting_load_

#ifdef __cplusplus
} // extern "C"
#endif
