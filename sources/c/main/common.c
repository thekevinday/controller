#include "controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_main_setting_load_
  void controller_main_setting_load(const f_console_arguments_t arguments, controller_main_t * const main, controller_process_t * const process) {

    if (!main || !process) return;

    main->setting.state.step_small = controller_allocation_console_d;

    f_console_parameter_process(arguments, &main->program.parameters, &main->setting.state, 0);

    main->setting.state.step_small = controller_allocation_small_d;

    if (main->program.parameters.array[f_console_standard_parameter_line_first_no_e].result & f_console_result_found_e) {
      main->setting.flag &= ~controller_main_flag_print_first_e;
    }
    else {
      main->setting.flag |= controller_main_flag_print_first_e;
    }

    if (main->program.parameters.array[f_console_standard_parameter_line_last_no_e].result & f_console_result_found_e) {
      main->setting.flag &= ~controller_main_flag_print_last_e;
    }
    else {
      main->setting.flag |= controller_main_flag_print_last_e;
    }

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & controller_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      controller_main_print_error(&main->program.error, macro_controller_f(f_console_parameter_process));

      return;
    }

    main->setting.state.status = fll_program_parameter_process_context_standard(F_true, &main->program);

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & controller_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      controller_main_print_error(&main->program.error, macro_controller_f(fll_program_parameter_process_context_standard));

      return;
    }

    main->setting.state.status = fll_program_parameter_process_verbosity_standard(F_true, &main->program);

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & controller_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

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

    process->control.server.domain = f_socket_protocol_family_local_e;
    process->control.server.type = f_socket_type_stream_e;
    process->control.server.form = f_socket_address_form_local_e;

    memset(&process->control.server.address, 0, sizeof(f_socket_address_t));

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

          if ((main->setting.flag & controller_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          fll_program_print_error_parameter_missing_value(&main->program.error, f_console_symbol_long_normal_s, strings[index]);

          return;
        }
      } // for
    }

    // The first remaining argument represents the entry name.
    main->setting.state.status = f_string_dynamic_append(main->program.parameters.remaining.used ? args[main->program.parameters.remaining.array[0]] : controller_default_s, &process->name_entry);

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & controller_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      controller_main_print_error(&main->program.error, macro_controller_f(fll_program_parameter_process_verbosity_standard));

      return;
    }

    main->setting.state.status = f_path_current(F_false, &process->path_current);

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & controller_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      controller_main_print_error(&main->program.error, macro_controller_f(f_path_current));

      return;
    }

    process->path_setting.used = 0;

    if (main->program.parameters.array[controller_parameter_settings_e].locations.used) {
      index = main->program.parameters.array[controller_parameter_settings_e].values.array[main->program.parameters.array[controller_parameter_settings_e].values.used - 1];

      controller_path_canonical_relative(main, process->path_current, args[index], &process->path_setting);
    }
    else {
      main->setting.state.status = f_string_dynamic_append(controller_default_path_settings_s, &process->path_setting);
    }

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & controller_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      if (main->program.parameters.array[controller_parameter_settings_e].locations.used) {
        controller_main_print_error_file(&main->program.error, macro_controller_f(controller_path_canonical_relative), args[index], f_file_operation_verify_s, fll_error_file_type_path_e);
      }
      else {
        controller_main_print_error(&main->program.error, macro_controller_f(f_string_dynamic_append));
      }

      return;
    }

    if (!process->path_pid.used && !main->program.parameters.array[controller_parameter_pid_e].locations.used) {
      main->setting.state.status = f_string_dynamic_append(controller_default_path_pid_s, &process->path_pid);

      if (F_status_is_error_not(main->setting.state.status)) {
        main->setting.state.status = f_string_dynamic_append(f_path_separator_s, &process->path_pid);
      }

      if (F_status_is_error_not(main->setting.state.status)) {
        main->setting.state.status = f_string_dynamic_append(controller_default_path_pid_prefix_s, &process->path_pid);
      }

      if (F_status_is_error_not(main->setting.state.status)) {
        main->setting.state.status = f_string_dynamic_append(process->name_entry, &process->path_pid);
      }

      if (F_status_is_error_not(main->setting.state.status)) {
        main->setting.state.status = f_string_dynamic_append(controller_default_path_pid_suffix_s, &process->path_pid);
      }

      if (F_status_is_error(main->setting.state.status)) {
        if ((main->setting.flag & controller_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        controller_main_print_error(&main->program.error, macro_controller_f(f_string_dynamic_append));

        return;
      }
    }

    if (main->program.parameters.array[controller_parameter_cgroup_e].locations.used) {
      index = main->program.parameters.array[controller_parameter_cgroup_e].values.array[main->program.parameters.array[controller_parameter_cgroup_e].values.used - 1];

      if (args[index].used) {
        controller_path_canonical_relative(main, process->path_current, args[index], &process->path_cgroup);

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & controller_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          controller_main_print_error_file(&main->program.error, macro_controller_f(controller_path_canonical_relative), args[index], f_file_operation_verify_s, fll_error_file_type_path_e);

          return;
        }

        main->setting.state.status = f_string_append_assure(F_path_separator_s, 1, &process->path_cgroup);

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & controller_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          controller_main_print_error(&main->program.error, macro_controller_f(f_string_append_assure));

          return;
        }
      }
      else {
        controller_main_print_debug_directory_path_empty(&main->program.warning, f_console_symbol_long_normal_s, controller_long_cgroup_s);
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
  }
#endif // _di_controller_main_setting_load_

#ifdef __cplusplus
} // extern "C"
#endif
