#include "../../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_output_entry_setting_simulate_value_
  f_status_t controller_print_output_entry_setting_simulate_value(fl_print_t * const print, const uint8_t is_entry, const f_string_static_t name, const f_string_static_t name_sub, const f_string_static_t value, const f_string_static_t suffix) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);

    controller_t * const main = (controller_t *) print->custom;

    if (print->verbosity < f_console_verbosity_debug_e && !((main->setting.flag & controller_main_flag_simulate_e) && print->verbosity > f_console_verbosity_normal_e)) {
      return F_output_not;
    }

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%rProcessing %r item action '", print->to, f_string_eol_s, is_entry ? controller_entry_s : controller_exit_s);

    fl_print_format("%[%Q%]' setting ", print->to, print->set->title, name, print->set->title);

    if (name_sub.used) {
      fl_print_format("'%[%Q%]'", print->to, print->set->notable, name_sub, print->set->notable);
    }
    else {
      fl_print_format("value", print->to);
    }

    fl_print_format(" to '%[%Q%]", print->to, print->set->important, value, print->set->important);

    fl_print_format("'%Q.%r", print->to, suffix, f_string_eol_s);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_output_entry_setting_simulate_value_

#ifndef _di_controller_print_output_entry_setting_validate_
  f_status_t controller_print_output_entry_setting_validate(fl_print_t * const print, const uint8_t is_entry) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_entry_t * const entry = is_entry ? &main->process.entry : &main->process.exit;

    controller_lock_print(print->to, &main->thread);

    const f_string_static_t *string = 0;

    f_status_t status = F_okay;
    f_number_unsigned_t i = 0;
    f_number_unsigned_t j = 0;

    fl_print_format("%r%Q %[%Q%] {%r", print->to, f_string_eol_s, is_entry ? controller_Entry_s : controller_Exit_s, print->set->title, controller_settings_s, print->set->title, f_string_eol_s);


    // Mode.
    if (main->process.mode == controller_process_mode_service_e) {
      string = &controller_mode_s;
    }
    else if (main->process.mode == controller_process_mode_helper_e) {
      string = &controller_helper_s;
    }
    else if (main->process.mode == controller_process_mode_program_e) {
      string = &controller_program_s;
    }
    else {
      string = &f_string_empty_s;
    }

    fl_print_format("  %[%r%]", print->to, print->set->important, controller_mode_s, print->set->important, f_string_eol_s);

    if (string->used) {
      fl_print_format(" %r", print->to, *string);
    }

    fl_print_format("%r", print->to, f_string_eol_s);


    // Session.
    if (entry->pid == controller_entry_session_new_e) {
      string = &controller_new_s;
    }
    else if (entry->pid == controller_entry_session_same_e) {
      string = &controller_same_s;
    }
    else {
      string = &f_string_empty_s;
    }

    fl_print_format("  %[%r%]", print->to, print->set->important, controller_session_s, print->set->important, f_string_eol_s);

    if (string->used) {
      fl_print_format(" %r", print->to, *string, f_string_eol_s);
    }

    fl_print_format("%r", print->to, f_string_eol_s);


    // Show.
    if (entry->pid == controller_entry_show_normal_e) {
      string = &controller_normal_s;
    }
    else if (entry->pid == controller_entry_show_init_e) {
      string = &controller_init_s;
    }
    else {
      string = &f_string_empty_s;
    }

    fl_print_format("  %[%r%]", print->to, print->set->important, controller_show_s, print->set->important, f_string_eol_s);

    if (string->used) {
      fl_print_format(" %r", print->to, *string, f_string_eol_s);
    }

    fl_print_format("%r", print->to, f_string_eol_s);


    // Pid.
    if (entry->pid == controller_entry_pid_disable_e) {
      string = &controller_disable_s;
    }
    else if (entry->pid == controller_entry_pid_require_e) {
      string = &controller_require_s;
    }
    else if (entry->pid == controller_entry_pid_ready_e) {
      string = &controller_ready_s;
    }
    else {
      string = &f_string_empty_s;
    }

    fl_print_format("  %[%r%]", print->to, print->set->important, controller_pid_s, print->set->important);

    if (string->used) {
      fl_print_format(" %r", print->to, *string);
    }

    fl_print_format("%r", print->to, f_string_eol_s);


    // Pid File.
    fl_print_format("  %[%r%]", print->to, print->set->important, controller_pid_file_s, print->set->important);

    if (main->process.path_pid.used) {
      fl_print_format(" %r", print->to, main->process.path_pid);
    }

    fl_print_format("%r", print->to, f_string_eol_s);


    // Control.
    fl_print_format("  %[%r%]", print->to, print->set->important, controller_control_s, print->set->important);

    if (main->process.path_control.used) {
      fl_print_format(" %Q", print->to, main->process.path_control);
    }

    fl_print_format("%r", print->to, f_string_eol_s);


    // Control Has.
    fl_print_format("  %[%r%]", print->to, print->set->important, controller_control_has_s, print->set->important);

    if (main->process.control.flag & controller_control_flag_readonly_e) {
      fl_print_format(" %r", print->to, controller_readonly_s);
    }

    fl_print_format("%r", print->to, f_string_eol_s);


    // Control User.
    fl_print_format("  %[%r%]", print->to, print->set->important, controller_control_user_s, print->set->important);

    if (main->process.control.flag & controller_control_flag_has_user_e) {
      fl_print_format(" %u", print->to, (unsigned int) main->process.control.user);
    }

    fl_print_format("%r", print->to, f_string_eol_s);


    // Control Group.
    fl_print_format("  %[%r%]", print->to, print->set->important, controller_control_group_s, print->set->important);

    if (main->process.control.flag & controller_control_flag_has_group_e) {
      fl_print_format(" %u", print->to, (unsigned int) main->process.control.group);
    }

    fl_print_format("%r", print->to, f_string_eol_s);


    // Control Mode.
    fl_print_format("  %[%r%]", print->to, print->set->important, controller_control_mode_s, print->set->important);

    if (F_status_is_error_not(status)) {
      if (main->process.control.flag & controller_control_flag_has_group_e) {
        fl_print_format(" %@05u", print->to, (unsigned int) main->process.control.mode);
      }
    }

    fl_print_format("%r", print->to, f_string_eol_s);


    // Timeout: Exit.
    fl_print_format("  %[%r%] %r", print->to, print->set->important, controller_timeout_s, print->set->important, controller_exit_s);

    if (!(entry->flag & controller_entry_flag_timeout_exit_no_e)) {
      fl_print_format(" %ul", print->to, entry->timeout_exit, f_string_eol_s);
    }

    fl_print_format("%r", print->to, f_string_eol_s);


    // Timeout: Kill.
    fl_print_format("  %[%r%] %r", print->to, print->set->important, controller_timeout_s, print->set->important, controller_kill_s);

    if (!(entry->flag & controller_entry_flag_timeout_kill_no_e)) {
      fl_print_format(" %ul", print->to, entry->timeout_kill, f_string_eol_s);
    }

    fl_print_format("%r", print->to, f_string_eol_s);


    // Timeout: Start.
    fl_print_format("  %[%r%] %r", print->to, print->set->important, controller_timeout_s, print->set->important, controller_start_s);

    if (!(entry->flag & controller_entry_flag_timeout_start_no_e)) {
      fl_print_format(" %ul", print->to, entry->timeout_start, f_string_eol_s);
    }

    fl_print_format("%r", print->to, f_string_eol_s);


    // Timeout: Stop.
    fl_print_format("  %[%r%] %r", print->to, print->set->important, controller_timeout_s, print->set->important, controller_stop_s);

    if (!(entry->flag & controller_entry_flag_timeout_stop_no_e)) {
      fl_print_format(" %ul", print->to, entry->timeout_stop, f_string_eol_s);
    }

    fl_print_format("%r", print->to, f_string_eol_s);


    // Define.
    fl_print_format("  %[%r%] {%r", print->to, print->set->important, controller_define_s, print->set->important, f_string_eol_s);

    for (i = 0; i < entry->define.used; ++i) {
      fl_print_format("    %Q %Q%r", print->to, entry->define.array[i].key, entry->define.array[i].value, f_string_eol_s);
    } // for

    fl_print_format("  }%r", print->to, f_string_eol_s, f_string_eol_s);


    // Parameter.
    fl_print_format("  %[%r%] {%r", print->to, print->set->important, controller_parameter_s, print->set->important, f_string_eol_s);

    for (i = 0; i < entry->parameter.used; ++i) {
      fl_print_format("    %Q %Q%r", print->to, entry->parameter.array[i].key, entry->parameter.array[i].value, f_string_eol_s);
    } // for

    fl_print_format("  }%r", print->to, f_string_eol_s);

    fl_print_format("}%r", print->to, f_string_eol_s);


    // Entry Items.
    if (entry->items.used) {
      controller_entry_action_t *action = 0;
      bool raw = F_false;
      f_number_unsigned_t k = 0;

      for (i = 0; i < entry->items.used; ++i) {

        fl_print_format("%r%Q %Q %[%Q%] {%r", print->to, f_string_eol_s, is_entry ? controller_Entry_s : controller_Exit_s, controller_Item_s, print->set->title, entry->items.array[i].name, print->set->title, f_string_eol_s);

        for (j = 0; j < entry->items.array[i].actions.used; ++j) {

          action = &entry->items.array[i].actions.array[j];

          fl_print_format("  %[%r%] {%r", print->to, print->set->important, controller_action_s, print->set->important, f_string_eol_s);


          // Item Type.
          if (action->type == controller_entry_action_type_consider_e) {
            string = &controller_consider_s;
            raw = F_false;
          }
          else if (action->type == controller_entry_action_type_execute_e) {
            string = &controller_execute_s;
            raw = F_true;
          }
          else if (action->type == controller_entry_action_type_failsafe_e) {
            string = &controller_failsafe_s;
            raw = F_true;
          }
          else if (action->type == controller_entry_action_type_freeze_e) {
            string = &controller_freeze_s;
            raw = F_false;
          }
          else if (action->type == controller_entry_action_type_item_e) {
            string = &controller_item_s;
            raw = F_true;
          }
          else if (action->type == controller_entry_action_type_kexec_e) {
            string = &controller_kexec_s;
            raw = F_false;
          }
          else if (action->type == controller_entry_action_type_kill_e) {
            string = &controller_kill_s;
            raw = F_false;
          }
          else if (action->type == controller_entry_action_type_pause_e) {
            string = &controller_pause_s;
            raw = F_false;
          }
          else if (action->type == controller_entry_action_type_ready_e) {
            string = &controller_ready_s;
            raw = F_true;
          }
          else if (action->type == controller_entry_action_type_reboot_e) {
            string = &controller_reboot_s;
            raw = F_false;
          }
          else if (action->type == controller_entry_action_type_reload_e) {
            string = &controller_reload_s;
            raw = F_false;
          }
          else if (action->type == controller_entry_action_type_restart_e) {
            string = &controller_restart_s;
            raw = F_false;
          }
          else if (action->type == controller_entry_action_type_resume_e) {
            string = &controller_resume_s;
            raw = F_false;
          }
          else if (action->type == controller_entry_action_type_shutdown_e) {
            string = &controller_shutdown_s;
            raw = F_false;
          }
          else if (action->type == controller_entry_action_type_start_e) {
            string = &controller_start_s;
            raw = F_false;
          }
          else if (action->type == controller_entry_action_type_stop_e) {
            string = &controller_stop_s;
            raw = F_false;
          }
          else if (action->type == controller_entry_action_type_timeout_e) {
            string = &controller_timeout_s;
            raw = F_true;
          }
          else if (action->type == controller_entry_action_type_thaw_e) {
            string = &controller_thaw_s;
            raw = F_false;
          }
          else {
            string = &f_string_empty_s;
          }

          fl_print_format("    %[%r%] %r%r", print->to, print->set->important, controller_type_s, print->set->important, *string, f_string_eol_s);


          // Item Code (How).
          fl_print_format("    %[%r%]", print->to, print->set->important, controller_how_s, print->set->important);

          if (action->code) {
            if (action->code == controller_entry_rule_code_asynchronous_d) {
              fl_print_format(" %r", print->to, controller_asynchronous_s);
            }

            if (action->type == controller_entry_rule_code_require_d) {
              fl_print_format(" %r", print->to, controller_require_s);
            }

            if (action->type == controller_entry_rule_code_wait_d) {
              fl_print_format(" %r", print->to, controller_wait_s);
            }
          }

          fl_print_format("%r", print->to, f_string_eol_s);


          // Parameters.
          if (action->type == controller_entry_action_type_item_e) {
            fl_print_format("    %[%r%]", print->to, print->set->important, controller_item_s, print->set->important);

            if (action->parameters.used && action->parameters.array[0].used) {
              fl_print_format(" %Q", print->to, action->parameters.array[0], f_string_eol_s);
            }

            fl_print_format("%r", print->to, f_string_eol_s);
          }
          else if (raw) {
            for (k = 0; k < action->parameters.used; ++k) {
              fl_print_format("    %[%r%] %Q%r", print->to, print->set->important, controller_parameter_s, print->set->important, action->parameters.array[k], f_string_eol_s);
            } // for
          }
          else {

            // Parameter, Directory.
            fl_print_format("    %[%r%]", print->to, print->set->important, controller_directory_s, print->set->important);

            if (action->parameters.used && action->parameters.array[0].used) {
              fl_print_format(" %Q", print->to, action->parameters.array[0], f_string_eol_s);
            }

            fl_print_format("%r", print->to, f_string_eol_s);


            // Parameter, File.
            fl_print_format("    %[%r%]", print->to, print->set->important, controller_file_s, print->set->important);

            if (action->parameters.used && action->parameters.array[0].used > 1) {
              fl_print_format(" %Q", print->to, action->parameters.array[1], f_string_eol_s);
            }

            fl_print_format("%r", print->to, f_string_eol_s);
          }

          fl_print_format("  }%r", print->to, f_string_eol_s);
        } // for

        fl_print_format("}%r", print->to, f_string_eol_s);
      } // for
    }

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_output_entry_setting_validate_

#ifdef __cplusplus
} // extern "C"
#endif
