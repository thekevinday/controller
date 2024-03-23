#include "controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_main_setting_load_
  void controller_main_setting_load(const f_console_arguments_t arguments, controller_main_t * const main) {

    if (!main) return;

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
  }
#endif // _di_controller_main_setting_load_

#ifdef __cplusplus
} // extern "C"
#endif
