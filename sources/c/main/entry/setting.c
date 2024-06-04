#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_entry_setting_read_
  f_status_t controller_entry_setting_read(controller_t * const main, controller_cache_t * const cache, const uint8_t is_entry, const f_range_t content_range) {

    f_status_t status = F_okay;

    {
      controller_interrupt_t custom = macro_controller_interrupt_t_initialize_1(is_entry, main);
      f_state_t state = macro_f_state_t_initialize_1(controller_common_allocation_large_d, controller_common_allocation_small_d, F_okay, 0, 0, 0, &controller_thread_signal_state_fss, 0, (void *) &custom, 0);
      f_range_t range = content_range;

      fll_fss_extended_read(cache->buffer_file, &range, &cache->object_actions, &cache->content_actions, 0, 0, &cache->delimits, 0, &state);
    }

    if (F_status_is_error(status)) {
      controller_entry_print_error(&main->program.error, cache->action, is_entry, F_status_set_fine(status), macro_controller_f(fll_fss_extended_read), F_true);

      return status;
    }

    {
      f_state_t state = f_state_t_initialize;

      f_fss_apply_delimit(cache->delimits, &cache->buffer_file, &state);
    }

    if (F_status_is_error(status)) {
      controller_entry_print_error(&main->program.error, cache->action, is_entry, F_status_set_fine(status), macro_controller_f(f_fss_apply_delimit), F_true);

      return status;
    }

    cache->delimits.used = 0;

    f_number_unsigned_t i = 0;

    controller_entry_t *entry = is_entry ? &main->setting.entry : &main->setting.exit;
    f_state_t state = f_state_t_initialize;

    for (; i < cache->object_actions.used; ++i) {

      cache->action.line_action = 0;

      f_fss_count_lines(cache->buffer_file, cache->object_actions.array[i].start, &cache->action.line_action, &main->setting.state);

      if (F_status_is_error(status)) {
        controller_entry_print_error(&main->program.error, cache->action, is_entry, F_status_set_fine(status), macro_controller_f(f_fss_count_lines), F_true);

        break;
      }

      ++cache->action.line_action;
      cache->action.name_action.used = 0;

      status = f_rip_dynamic_partial_nulless(cache->buffer_file, cache->object_actions.array[i], &cache->action.name_action);

      if (F_status_is_error(status)) {
        controller_entry_print_error(&main->program.error, cache->action, is_entry, F_status_set_fine(status), macro_controller_f(f_rip_dynamic_partial_nulless), F_true);

        break;
      }

      if (is_entry && f_compare_dynamic(controller_control_s, cache->action.name_action) == F_equal_to) {
        if (cache->content_actions.array[i].used < 1 || cache->content_actions.array[i].used > 2) {
          controller_entry_setting_read_print_setting_requires_between(main, is_entry, *cache, 1, 2);

          continue;
        }

        if (cache->content_actions.array[i].used == 2) {
          if (f_compare_dynamic_partial_string(controller_readonly_s.string, cache->buffer_file, controller_readonly_s.used, cache->content_actions.array[i].array[1]) == F_equal_to) {
            main->setting.control.flag |= controller_control_flag_readonly_e;
          }
          else {
            if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
              controller_lock_print(main->program.error.to, &main->thread);

              fl_print_format("%r%[%QThe %r item setting '%]", main->program.error.to, f_string_eol_s, main->program.error.context, main->program.error.prefix, is_entry ? controller_entry_s : controller_exit_s, main->program.error.context);
              fl_print_format(f_string_format_Q_single_s.string, main->program.error.to, main->program.error.notable, controller_control_s, main->program.error.notable);
              fl_print_format("%[' does not support the option '%]", main->program.error.to, main->program.error.context, main->program.error.context, f_string_eol_s);

              fl_print_format(f_string_format_Q_range_single_s.string, main->program.error.to, main->program.error.notable, cache->buffer_file, cache->content_actions.array[i].array[1], main->program.error.notable);

              fl_print_format(f_string_format_sentence_end_quote_s.string, main->program.error.to, main->program.error.context, main->program.error.context, f_string_eol_s);

              controller_entry_print_error_cache(is_entry, &main->program.error, cache->action);

              controller_unlock_print_flush(main->program.error.to, &main->thread);

              continue;
            }
          }
        }
        else {
          main->setting.control.flag &= ~controller_control_flag_readonly_e;
        }

        cache->action.generic.used = 0;
        main->setting.path_control.used = 0;

        status = f_rip_dynamic_partial_nulless(cache->buffer_file, cache->content_actions.array[i].array[0], &cache->action.generic);

        if (F_status_is_error(status)) {
          controller_entry_print_error(&main->program.error, cache->action, is_entry, F_status_set_fine(status), macro_controller_f(f_rip_dynamic_partial_nulless), F_true);

          break;
        }

        main->setting.path_control.used = 0;

        status = controller_path_canonical_relative(main->setting, cache->action.generic, &main->setting.path_control);

        if (F_status_is_error(status)) {
          controller_entry_print_error_file(&main->program.error, cache->action, is_entry, F_status_set_fine(status), macro_controller_f(controller_path_canonical_relative), F_true, cache->action.generic, f_file_operation_analyze_s, fll_error_file_type_path_e);

          continue;
        }
      }
      else if (is_entry && f_compare_dynamic(controller_control_group_s, cache->action.name_action) == F_equal_to) {
        gid_t number = 0;

        status = controller_convert_group_id(cache->buffer_file, cache->content_actions.array[i].array[0], cache, &number);

        if (F_status_is_error(status)) {
          status = F_status_set_fine(status);

          if (status == F_exist_not) {
            controller_entry_setting_read_print_error_with_range(&main->program.error, cache, is_entry, " has an invalid group", cache->content_actions.array[i].array[0], ", because no group was found by that name");
          }
          else if (status == F_number_too_large) {
            controller_entry_setting_read_print_error_with_range(&main->program.error, cache, is_entry, " has an invalid group", cache->content_actions.array[i].array[0], ", because the given ID is too large");
          }
          else if (status == F_number) {
            controller_entry_setting_read_print_error_with_range(&main->program.error, cache, is_entry, " has an invalid group", cache->content_actions.array[i].array[0], ", because the given ID is not a valid supported number");
          }
          else {
            controller_entry_print_error(&main->program.error, cache->action, is_entry, F_status_set_fine(status), macro_controller_f(controller_convert_group_id), F_true);
          }

          continue;
        }

        main->setting.control.group = number;
        main->setting.control.flag |= controller_control_flag_has_group_e;
      }
      else if (is_entry && f_compare_dynamic(controller_control_mode_s, cache->action.name_action) == F_equal_to) {
        mode_t mode = 0;
        uint8_t replace = 0;
        f_file_mode_t mode_file = f_file_mode_t_initialize;

        cache->action.generic.used = 0;

        status = f_rip_dynamic_partial_nulless(cache->buffer_file, cache->content_actions.array[i].array[0], &cache->action.generic);

        if (F_status_is_error(status)) {
          controller_entry_print_error(&main->program.error, cache->action, is_entry, F_status_set_fine(status), macro_controller_f(f_rip_dynamic_partial_nulless), F_true);

          break;
        }

        status = f_file_mode_from_string(cache->action.generic, main->program.umask, &mode_file, &replace);

        if (F_status_is_error(status)) {
          controller_entry_setting_read_print_error_with_range(&main->program.error, cache, is_entry, " has an unsupported mode", cache->content_actions.array[i].array[0], ", because the format is unknown or contains invalid data");

          continue;
        }

        status = f_file_mode_to_mode(mode_file, &mode);

        if (F_status_is_error(status)) {
          controller_entry_print_error(&main->program.error, cache->action, is_entry, F_status_set_fine(status), macro_controller_f(f_file_mode_to_mode), F_true);

          continue;
        }

        main->setting.control.mode = mode;
        main->setting.control.flag |= controller_control_flag_has_mode_e;
      }
      else if (is_entry && f_compare_dynamic(controller_control_user_s, cache->action.name_action) == F_equal_to) {
        uid_t number = 0;

        status = controller_convert_user_id(cache->buffer_file, cache->content_actions.array[i].array[0], cache, &number);

        if (F_status_is_error(status)) {
          status = F_status_set_fine(status);

          if (status == F_exist_not) {
            controller_entry_setting_read_print_error_with_range(&main->program.error, cache, is_entry, " has an invalid user", cache->content_actions.array[i].array[0], ", because no user was found by that name");
          }
          else if (status == F_number_too_large) {
            controller_entry_setting_read_print_error_with_range(&main->program.error, cache, is_entry, " has an invalid user", cache->content_actions.array[i].array[0], ", because the given ID is too large");
          }
          else if (status == F_number) {
            controller_entry_setting_read_print_error_with_range(&main->program.error, cache, is_entry, " has an invalid user", cache->content_actions.array[i].array[0], ", because the given ID is not a valid supported number");
          }
          else {
            controller_entry_print_error(&main->program.error, cache->action, is_entry, F_status_set_fine(status), macro_controller_f(controller_convert_user_id), F_true);
          }

          continue;
        }

        main->setting.control.user = number;
        main->setting.control.flag |= controller_control_flag_has_user_e;
      }
      else if (f_compare_dynamic(controller_define_s, cache->action.name_action) == F_equal_to) {
        if (cache->content_actions.array[i].used != 2) {
          controller_entry_setting_read_print_setting_requires_exactly(main, is_entry, *cache, 2);

          continue;
        }

        status = controller_entry_setting_read_map(cache->buffer_file, cache->content_actions.array[i], &entry->define);

        if (F_status_is_error(status)) {
          controller_entry_print_error(&main->program.error, cache->action, is_entry, F_status_set_fine(status), macro_controller_f(controller_entry_setting_read_map), F_true);

          continue;
        }
      }
      else if (is_entry && f_compare_dynamic(controller_mode_s, cache->action.name_action) == F_equal_to) {
        if (cache->content_actions.array[i].used != 1) {
          controller_entry_setting_read_print_setting_requires_exactly(main, is_entry, *cache, 1);

          continue;
        }

        if (f_compare_dynamic_partial_string(controller_service_s.string, cache->buffer_file, controller_service_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          main->setting.mode = controller_setting_mode_service_e;
        }
        else if (f_compare_dynamic_partial_string(controller_helper_s.string, cache->buffer_file, controller_helper_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          main->setting.mode = controller_setting_mode_helper_e;
        }
        else if (f_compare_dynamic_partial_string(controller_program_s.string, cache->buffer_file, controller_program_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          main->setting.mode = controller_setting_mode_program_e;
        }
        else {
          controller_entry_setting_read_print_setting_unknown_action_value(main, is_entry, *cache, i);

          continue;
        }
      }
      else if (f_compare_dynamic(controller_parameter_s, cache->action.name_action) == F_equal_to) {
        if (cache->content_actions.array[i].used != 2) {
          controller_entry_setting_read_print_setting_requires_exactly(main, is_entry, *cache, 2);

          continue;
        }

        status = controller_entry_setting_read_map(cache->buffer_file, cache->content_actions.array[i], &entry->parameter);

        if (F_status_is_error(status)) {
          controller_entry_print_error(&main->program.error, cache->action, is_entry, F_status_set_fine(status), macro_controller_f(controller_entry_setting_read_map), F_true);

          continue;
        }
      }
      else if (f_compare_dynamic(controller_pid_s, cache->action.name_action) == F_equal_to) {
        if (cache->content_actions.array[i].used != 1) {
          controller_entry_setting_read_print_setting_requires_exactly(main, is_entry, *cache, 1);

          continue;
        }

        if (f_compare_dynamic_partial_string(controller_disable_s.string, cache->buffer_file, controller_disable_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          entry->pid = controller_entry_pid_disable_e;
        }
        else if (f_compare_dynamic_partial_string(controller_ready_s.string, cache->buffer_file, controller_ready_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          entry->pid = controller_entry_pid_ready_e;
        }
        else if (f_compare_dynamic_partial_string(controller_require_s.string, cache->buffer_file, controller_require_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          entry->pid = controller_entry_pid_require_e;
        }
        else {
          controller_entry_setting_read_print_setting_unknown_action_value(main, is_entry, *cache, i);

          continue;
        }
      }
      else if (is_entry && f_compare_dynamic(controller_pid_file_s, cache->action.name_action) == F_equal_to) {
        if (cache->content_actions.array[i].used != 1) {
          controller_entry_setting_read_print_setting_requires_exactly(main, is_entry, *cache, 1);

          continue;
        }

        if (main->program.parameters.array[controller_parameter_pid_e].result & f_console_result_value_e) {
          controller_entry_setting_read_print_setting_ignored(main, is_entry, *cache, i);
        }
        else {
          cache->action.generic.used = 0;

          status = f_rip_dynamic_partial_nulless(cache->buffer_file, cache->content_actions.array[i].array[0], &cache->action.generic);

          if (F_status_is_error(status)) {
            controller_entry_print_error(&main->program.error, cache->action, is_entry, F_status_set_fine(status), macro_controller_f(f_rip_dynamic_partial_nulless), F_true);

            continue;
          }

          main->setting.path_pid.used = 0;

          status = controller_path_canonical_relative(main->setting, cache->action.generic, &main->setting.path_pid);

          if (F_status_is_error(status)) {
            controller_entry_print_error(&main->program.error, cache->action, is_entry, F_status_set_fine(status), macro_controller_f(controller_path_canonical_relative), F_true);

            continue;
          }
        }
      }
      else if (f_compare_dynamic(controller_session_s, cache->action.name_action) == F_equal_to) {
        if (cache->content_actions.array[i].used != 1) {
          controller_entry_setting_read_print_setting_requires_exactly(main, is_entry, *cache, 1);

          continue;
        }

        if (f_compare_dynamic_partial_string(controller_new_s.string, cache->buffer_file, controller_new_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          entry->session = controller_entry_session_new_e;
        }
        else if (f_compare_dynamic_partial_string(controller_same_s.string, cache->buffer_file, controller_same_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          entry->session = controller_entry_session_same_e;
        }
        else {
          controller_entry_setting_read_print_setting_unknown_action_value(main, is_entry, *cache, i);

          continue;
        }
      }
      else if (f_compare_dynamic(controller_show_s, cache->action.name_action) == F_equal_to) {
        if (cache->content_actions.array[i].used != 1) {
          controller_entry_setting_read_print_setting_requires_exactly(main, is_entry, *cache, 1);

          continue;
        }

        if (f_compare_dynamic_partial_string(controller_normal_s.string, cache->buffer_file, controller_normal_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          entry->show = controller_entry_show_normal_e;
        }
        else if (f_compare_dynamic_partial_string(controller_init_s.string, cache->buffer_file, controller_init_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          entry->show = controller_entry_show_init_e;
        }
        else {
          controller_entry_setting_read_print_setting_unknown_action_value(main, is_entry, *cache, i);

          continue;
        }
      }
      else if (f_compare_dynamic(controller_timeout_s, cache->action.name_action) == F_equal_to) {
        if (cache->content_actions.array[i].used < 1 || cache->content_actions.array[i].used > 2) {
          controller_entry_setting_read_print_setting_requires_between(main, is_entry, *cache, 1, 2);

          continue;
        }

        f_number_unsigned_t *time = 0;

        if (f_compare_dynamic_partial_string(controller_exit_s.string, cache->buffer_file, controller_exit_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          if (cache->content_actions.array[i].used == 1) {
            entry->flag |= controller_entry_flag_timeout_exit_no_e;

            continue;
          }

          entry->flag &= ~controller_entry_flag_timeout_exit_no_e;
          time = &entry->timeout_exit;
        }
        else if (f_compare_dynamic_partial_string(controller_kill_s.string, cache->buffer_file, controller_kill_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          if (cache->content_actions.array[i].used == 1) {
            entry->flag |= controller_entry_flag_timeout_kill_no_e;

            continue;
          }

          entry->flag &= ~controller_entry_flag_timeout_kill_no_e;
          time = &entry->timeout_kill;
        }
        else if (f_compare_dynamic_partial_string(controller_start_s.string, cache->buffer_file, controller_start_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          if (cache->content_actions.array[i].used == 1) {
            entry->flag |= controller_entry_flag_timeout_start_no_e;

            continue;
          }

          entry->flag &= ~controller_entry_flag_timeout_start_no_e;
          time = &entry->timeout_start;
        }
        else if (f_compare_dynamic_partial_string(controller_stop_s.string, cache->buffer_file, controller_stop_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          if (cache->content_actions.array[i].used == 1) {
            entry->flag |= controller_entry_flag_timeout_stop_no_e;

            continue;
          }

          entry->flag &= ~controller_entry_flag_timeout_stop_no_e;
          time = &entry->timeout_stop;
        }
        else {
          controller_entry_setting_read_print_setting_unknown_action_value(main, is_entry, *cache, i);

          continue;
        }

        const f_number_unsigned_t time_previous = *time;

        status = fl_conversion_dynamic_partial_to_unsigned_detect(fl_conversion_data_base_10_c, cache->buffer_file, cache->content_actions.array[i].array[1], time);

        if (F_status_is_error(status) || status == F_data_not) {
          *time = time_previous;

          if (F_status_set_fine(status) == F_memory_not) {
            controller_entry_print_error(&main->program.error, cache->action, is_entry, F_status_set_fine(status), macro_controller_f(fl_conversion_dynamic_partial_to_unsigned_detect), F_true);

            continue;
          }

          if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
            f_file_stream_lock(main->program.error.to);

            fl_print_format("%r%[%QThe %r setting '%]", main->program.error.to, f_string_eol_s, main->program.error.context, main->program.error.prefix, is_entry ? controller_entry_s : controller_exit_s, main->program.error.context);
            fl_print_format(f_string_format_Q_range_single_s.string, main->program.error.to, main->program.error.notable, cache->buffer_file, cache->content_actions.array[i].array[1], main->program.error.notable);
            fl_print_format("%[' is not a valid supported number.%]", main->program.error.to, main->program.error.context, main->program.error.context, f_string_eol_s);

            f_file_stream_unlock(main->program.error.to);
          }
        }
      }
      else {
        if (main->program.warning.verbosity == f_console_verbosity_debug_e) {
          controller_entry_setting_read_print_setting_unknown_action(main, is_entry, *cache);
        }

        continue;
      }
    } // for

    return f_status_is_error(status) ? status : F_okay;
  }
#endif // _di_controller_entry_setting_read_

#ifndef _di_controller_entry_setting_read_map_
  f_status_t controller_entry_setting_read_map(const f_string_static_t buffer, const f_ranges_t ranges, f_string_maps_t * const setting_maps) {

    {
      f_status_t status = f_memory_array_increase(controller_common_allocation_small_d, sizeof(f_string_map_t), (void **) &setting_maps->array, &setting_maps->used, &setting_maps->size);
      if (F_status_is_error(status)) return status;

      setting_maps->array[setting_maps->used].key.used = 0;
      setting_maps->array[setting_maps->used].value.used = 0;

      status = f_string_dynamic_partial_append_nulless(buffer, ranges.array[0], &setting_maps->array[setting_maps->used].key);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamic_partial_append_nulless(buffer, ranges.array[1], &setting_maps->array[setting_maps->used].value);
      if (F_status_is_error(status)) return status;
    }

    ++setting_maps->used;

    return F_okay;
  }
#endif // _di_controller_entry_setting_read_map_

#ifdef __cplusplus
} // extern "C"
#endif
