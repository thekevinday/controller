#include "controller.h"

int main(const int argc, const f_string_t *argv, const f_string_t *envp) {

  controller_main_t data = controller_main_t_initialize;

  data.program.debug.flag |= controller_print_flag_debug_e | controller_print_flag_out_e;
  data.program.error.flag |= controller_print_flag_error_e | controller_print_flag_out_e;
  data.program.output.flag |= controller_print_flag_out_e;
  data.program.message.flag |= controller_print_flag_message_e | controller_print_flag_out_e;
  data.program.warning.flag |= controller_print_flag_warning_e | controller_print_flag_out_e;
  data.program.error.custom = (void *) &data;
  data.program.debug.custom = (void *) &data;
  data.program.message.custom = (void *) &data;
  data.program.output.custom = (void *) &data;
  data.program.warning.custom = (void *) &data;

  data.setting.program_name = &controller_controller_program_name_s;
  data.setting.program_name_long = &controller_controller_program_name_long_s;

  f_console_parameter_t parameters[] = controller_console_parameter_t_initialize;

  data.program.parameters.array = parameters;
  data.program.parameters.used = controller_parameter_total_d;
  data.program.environment = envp;

  if (f_pipe_input_exists()) {
    data.program.pipe = fll_program_data_pipe_input_e;
  }

  fll_program_standard_set_up(&data.program);

  f_file_umask_get(&data.program.umask);

  #ifdef _di_thread_support_
    {
      const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize_1(argc, argv, envp);

      controller_main_setting_load(arguments, &data);
    }

    controller_controller_main(&data);
  #else
    {
      f_thread_id_t id_signal;

      memset(&id_signal, 0, sizeof(f_thread_id_t));

      data.setting.state.status = f_thread_create(0, &id_signal, &controller_main_thread_signal, (void *) &data);

      if (F_status_is_error(data.setting.state.status)) {
        controller_main_print_error(&data.program.error, macro_controller_f(f_thread_create));
      }
      else {
        {
          const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize_1(argc, argv, envp);

          controller_main_setting_load(arguments, &data);
        }

        if (!controller_main_signal_check(&data)) {
          controller_controller_main(&data);
        }

        f_thread_cancel(id_signal);
        f_thread_join(id_signal, 0);
      }
    }
  #endif // _di_thread_support_

  controller_main_delete(&data);

  fll_program_standard_set_down(&data.program);

  if (data.setting.state.status == F_child) {
    exit(data.program.child);
  }

  return (F_status_is_error(data.setting.state.status) || data.setting.state.status == F_false) ? 1 : 0;
}
