#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_entry_action_read_
  f_status_t controller_entry_action_read(controller_t * const main, const uint8_t is_entry, f_range_t range, controller_entry_actions_t * const actions) {

    if (!main || !actions) return F_status_set_error(F_parameter);

    f_status_t status = F_okay;
    f_status_t status_action = F_okay;

    actions->used = 0;

    main->thread.cache.object_actions.used = main->thread.cache.object_actions.size;
    main->thread.cache.content_actions.used = main->thread.cache.content_actions.size;

    while (main->thread.cache.object_actions.used) {

      main->thread.cache.object_actions.array[--main->thread.cache.object_actions.used].start = 1;
      main->thread.cache.object_actions.array[main->thread.cache.object_actions.used].stop = 0;
    } // while

    while (main->thread.cache.content_actions.used) {
      main->thread.cache.content_actions.array[--main->thread.cache.content_actions.used].used = 0;
    } // while

    {
      controller_state_interrupt_t custom = macro_controller_state_interrupt_t_initialize_1(is_entry, global.thread);
      f_state_t state = macro_f_state_t_initialize_1(controller_common_allocation_large_d, controller_common_allocation_small_d, F_okay, 0, 0, 0, &controller_thread_signal_state_fss, 0, (void *) &custom, 0);
      f_range_t content_range = range;

      fll_fss_extended_read(main->thread.cache.buffer_file, &content_range, &main->thread.cache.object_actions, &main->thread.cache.content_actions, 0, 0, &main->thread.cache.delimits, 0, &state);
    }

    if (F_status_is_error(status)) {
      controller_print_error_entry(&main->program.error, is_entry, F_status_set_fine(status), macro_controller_f(fll_fss_extended_read), F_true);

      return status;
    }

    f_state_t state = f_state_t_initialize;

    f_fss_apply_delimit(main->thread.cache.delimits, &main->thread.cache.buffer_file, &state);

    if (F_status_is_error(status)) {
      controller_print_error_entry(&main->program.error, is_entry, F_status_set_fine(status), macro_controller_f(f_fss_apply_delimit), F_true);

      return status;
    }

    main->thread.cache.delimits.used = 0;

    status  f_memory_array_increase_by(main->thread.cache.object_actions.used, sizeof(controller_entry_action_t), (void **) &actions->array, &actions->used, &actions->size);

    if (F_status_is_error(status)) {
      controller_print_error_entry(&main->program.error, is_entry, F_status_set_fine(status), macro_controller_f(f_memory_array_increase_by), F_true);

      return status;
    }

    controller_entry_action_t *action = 0;

    f_number_unsigned_t allocate = 0;
    f_number_unsigned_t at_least = 0;
    f_number_unsigned_t at_most = 0;

    f_number_unsigned_t i = 0;
    f_number_unsigned_t j = 0;

    for (; i < main->thread.cache.object_actions.used; ++i) {

      main->thread.cache.action.line_action = 0;
      main->thread.cache.action.name_action.used = 0;

      action = &actions->array[actions->used];
      action->type = 0;
      action->code = 0;
      action->line = 0;
      action->number = 0;
      action->status = F_known_not;
      action->parameters.used = 0;

      f_fss_count_lines(main->thread.cache.buffer_file, main->thread.cache.object_actions.array[i].start, &main->thread.cache.action.line_action, &global.main->setting.state);

      if (F_status_is_error(status)) {
        controller_print_error_entry(&main->program.error, is_entry, F_status_set_fine(status), macro_controller_f(f_fss_count_lines), F_true);

        break;
      }

      action->line = ++main->thread.cache.action.line_action;

      status = f_rip_dynamic_partial_nulless(main->thread.cache.buffer_file, main->thread.cache.object_actions.array[i], &main->thread.cache.action.name_action);

      if (F_status_is_error(status)) {
        controller_print_error_entry(&main->program.error, is_entry, F_status_set_fine(status), macro_controller_f(f_rip_dynamic_partial_nulless), F_true);

        break;
      }

      if (f_compare_dynamic(controller_consider_s, main->thread.cache.action.name_action) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_consider_e;
      }
      else if (f_compare_dynamic(controller_execute_s, main->thread.cache.action.name_action) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_execute_e;
      }
      else if (f_compare_dynamic(controller_failsafe_s, main->thread.cache.action.name_action) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_failsafe_e;
      }
      else if (f_compare_dynamic(controller_freeze_s, main->thread.cache.action.name_action) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_freeze_e;
      }
      else if (f_compare_dynamic(controller_item_s, main->thread.cache.action.name_action) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_item_e;
      }
      else if (f_compare_dynamic(controller_kill_s, main->thread.cache.action.name_action) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_kill_e;
      }
      else if (f_compare_dynamic(controller_pause_s, main->thread.cache.action.name_action) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_pause_e;
      }
      else if (f_compare_dynamic(controller_ready_s, main->thread.cache.action.name_action) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_ready_e;
      }
      else if (f_compare_dynamic(controller_reload_s, main->thread.cache.action.name_action) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_reload_e;
      }
      else if (f_compare_dynamic(controller_restart_s, main->thread.cache.action.name_action) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_restart_e;
      }
      else if (f_compare_dynamic(controller_resume_s, main->thread.cache.action.name_action) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_resume_e;
      }
      else if (f_compare_dynamic(controller_start_s, main->thread.cache.action.name_action) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_start_e;
      }
      else if (f_compare_dynamic(controller_stop_s, main->thread.cache.action.name_action) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_stop_e;
      }
      else if (f_compare_dynamic(controller_thaw_s, main->thread.cache.action.name_action) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_thaw_e;
      }
      else if (f_compare_dynamic(controller_timeout_s, main->thread.cache.action.name_action) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_timeout_e;
      }
      else {
        if (global.main->program.warning.verbosity == f_console_verbosity_debug_e) {
          controller_lock_print(global.main->program.warning.to, global.thread);

          fl_print_format("%r%[%QUnknown %r item action '%]", global.main->program.warning.to, f_string_eol_s, global.main->program.warning.context, global.main->program.warning.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->program.warning.context);
          fl_print_format(f_string_format_Q_single_s.string, global.main->program.warning.to, global.main->program.warning.notable, main->thread.cache.action.name_action, global.main->program.warning.notable);
          fl_print_format(f_string_format_sentence_end_quote_s.string, global.main->program.warning.to, global.main->program.warning.context, global.main->program.warning.context, f_string_eol_s);

          controller_entry_print_error_cache(is_entry, &global.main->program.warning, main->thread.cache.action);

          controller_unlock_print_flush(global.main->program.warning.to, global.thread);
        }

        continue;
      }

      if (action->type == controller_entry_action_type_consider_e || controller_entry_action_type_is_rule(action->type)) {
        allocate = main->thread.cache.content_actions.array[i].used;
        at_least = 2;
        at_most = allocate;
      }
      else if (action->type == controller_entry_action_type_execute_e) {
        allocate = main->thread.cache.content_actions.array[i].used;
        at_least = 1;
        at_most = allocate;
      }
      else if (action->type == controller_entry_action_type_failsafe_e || action->type == controller_entry_action_type_item_e) {
        allocate = 1;
        at_least = 1;
        at_most = 1;
      }
      else if (action->type == controller_entry_action_type_timeout_e) {
        allocate = 2;
        at_least = 1;
        at_most = 2;
      }
      else if (action->type == controller_entry_action_type_ready_e) {
        allocate = 1;
        at_least = 0;
        at_most = 1;
      }

      if (main->thread.cache.content_actions.array[i].used < at_least || main->thread.cache.content_actions.array[i].used > at_most) {
        action->status = F_status_set_error(F_parameter);

        if (global.main->program.error.verbosity > f_console_verbosity_quiet_e) {
          f_thread_mutex_lock(&global.thread->lock.print);

          f_file_stream_lock(global.main->program.error.to);

          fl_print_format("%r%[%QThe %r item action '%]", global.main->program.error.to, f_string_eol_s, global.main->program.error.context, global.main->program.error.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->program.error.context);
          fl_print_format(f_string_format_Q_single_s.string, global.main->program.error.to, global.main->program.error.notable, main->thread.cache.action.name_action, global.main->program.error.notable);
          fl_print_format("%[' requires ", global.main->program.error.to, global.main->program.error.context);

          if (at_least == at_most) {
            f_print_terminated("exactly ", global.main->program.error.to);
          }

          fl_print_format("%]%[%un%]", global.main->program.error.to, global.main->program.error.context, global.main->program.error.notable, at_least, global.main->program.error.notable);

          if (action->type == controller_entry_action_type_consider_e || controller_entry_action_type_is_rule(action->type)) {
            fl_print_format("%[ or more parameters.%]%r", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context, f_string_eol_s);
          }
          else {
            if (at_least == at_most) {
              fl_print_format("%[ parameters.%]%r", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context, f_string_eol_s);
            }
            else {
              fl_print_format("%[ to %]", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context);
              fl_print_format("%[%un%]", global.main->program.error.to, global.main->program.error.notable, at_most, global.main->program.error.notable);
              fl_print_format("%[ parameters.%]%r", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context, f_string_eol_s);
            }
          }

          f_file_stream_unlock(global.main->program.error.to);

          f_thread_mutex_unlock(&global.thread->lock.print);
        }
      }
      else {
        action->status = F_okay;
      }

      if (F_status_is_error(action->status)) {
        if (F_status_is_error_not(status_action)) {
          status_action = action->status;
        }

        continue;
      }

      if (allocate) {
        status = f_memory_array_increase_by(allocate, sizeof(f_string_dynamic_t), (void **) &action->parameters.array, &action->parameters.used, &action->parameters.size);

        if (F_status_is_error(status)) {
          controller_print_error_entry(&main->program.error, is_entry, F_status_set_fine(status), macro_controller_f(f_memory_array_increase_by), F_true);

          action->status = status;

          if (F_status_is_error_not(status_action)) {
            status_action = status;
          }

          break;
        }

        for (j = 0; j < allocate && j < main->thread.cache.content_actions.array[i].used; ++j) {

          action->parameters.array[j].used = 0;

          if (main->thread.cache.content_actions.array[i].array[j].start > main->thread.cache.content_actions.array[i].array[j].stop) continue;

          status = f_memory_array_increase_by((main->thread.cache.content_actions.array[i].array[j].stop - main->thread.cache.content_actions.array[i].array[j].start) + 1, sizeof(f_char_t), (void **) &action->parameters.array[j].string, &action->parameters.array[j].used, &action->parameters.array[j].size);

          if (F_status_is_error(status)) {
            controller_print_error_entry(&main->program.error, is_entry, F_status_set_fine(status), macro_controller_f(f_memory_array_increase_by), F_true);

            break;
          }

          status = f_string_dynamic_partial_append_nulless(main->thread.cache.buffer_file, main->thread.cache.content_actions.array[i].array[j], &action->parameters.array[j]);

          if (F_status_is_error(status)) {
            controller_print_error_entry(&main->program.error, is_entry, F_status_set_fine(status), macro_controller_f(f_string_dynamic_partial_append_nulless), F_true);

            break;
          }

          ++action->parameters.used;
        } // for

        if (F_status_is_error_not(action->status)) {
          if (action->type == controller_entry_action_type_consider_e || controller_entry_action_type_is_rule(action->type)) {
            if (action->parameters.array[0].used) {

              // Force the path to be canonical (removing all '../' parts).
              status = controller_path_canonical_relative(global.setting, action->parameters.array[0], &main->thread.cache.buffer_path);

              if (F_status_is_error(status)) {
                controller_entry_print_error_file(is_entry, &global.main->program.error, main->thread.cache.action, F_status_set_fine(status), "controller_path_canonical_relative", F_true, main->thread.cache.action.generic, f_file_operation_analyze_s, fll_error_file_type_path_e, global.thread);

                action->status = status;

                if (F_status_set_fine(status) == F_memory_not) {
                  status_action = status;

                  break;
                }

                if (F_status_is_error_not(status_action)) {
                  status_action = status;
                }
              }
            }
            else {
              action->status = F_status_set_error(F_parameter);

              if (F_status_is_error_not(status_action)) {
                status_action = action->status;
              }

              if (global.main->program.error.verbosity > f_console_verbosity_quiet_e) {
                fll_print_format("%r%[%QThe %r item action must not have an empty string for a path (the first parameter).%]%r", global.main->program.error.to, f_string_eol_s, global.main->program.error.context, global.main->program.error.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->program.error.context, f_string_eol_s);
              }
            }

            if (action->parameters.array[1].used) {
              main->thread.cache.buffer_path.used = 0;

              status = f_file_name_base(action->parameters.array[1], &main->thread.cache.buffer_path);

              if (F_status_is_error(status)) {
                controller_print_error_entry(&main->program.error, is_entry, F_status_set_fine(status), macro_controller_f(f_file_name_base), F_true);

                if (F_status_set_fine(status) == F_memory_not) {
                  status_action = status;

                  break;
                }

                action->status = status;

                if (F_status_is_error_not(status_action)) {
                  status_action = status;
                }
              }
              else {
                if (f_compare_dynamic(action->parameters.array[1], main->thread.cache.buffer_path) == F_equal_to_not) {
                  if (global.main->program.error.verbosity > f_console_verbosity_quiet_e) {
                    f_file_stream_lock(global.main->program.error.to);

                    fl_print_format("%r%[%QThe %r item action second parameter '%]", global.main->program.error.to, f_string_eol_s, global.main->program.error.context, global.main->program.error.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->program.error.context);
                    fl_print_format(f_string_format_Q_single_s.string, global.main->program.error.to, global.main->program.error.notable, action->parameters.array[1], global.main->program.error.notable);
                    fl_print_format("%[' must be a base path name, such as '%]", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context);
                    fl_print_format(f_string_format_Q_single_s.string, global.main->program.error.to, global.main->program.error.notable, main->thread.cache.buffer_path, global.main->program.error.notable);
                    fl_print_format("%['.%]", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context, f_string_eol_s);

                    f_file_stream_unlock(global.main->program.error.to);
                  }

                  action->status = F_status_set_error(F_parameter);

                  if (F_status_is_error_not(status_action)) {
                    status_action = action->status;
                  }
                }
              }
            }
            else {
              action->status = F_status_set_error(F_parameter);

              if (F_status_is_error_not(status_action)) {
                status_action = action->status;
              }

              if (global.main->program.error.verbosity > f_console_verbosity_quiet_e) {
                fll_print_format("%r%[%QThe %r item action must not have an empty string for a rule name (the second parameter).%]", global.main->program.error.to, f_string_eol_s, global.main->program.error.context, global.main->program.error.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->program.error.context, f_string_eol_s);
              }
            }

            for (j = 2; j < action->parameters.used; ++j) {

              if (f_compare_dynamic(controller_asynchronous_s, action->parameters.array[j]) == F_equal_to) {
                action->code |= controller_entry_rule_code_asynchronous_d;
              }
              else if (f_compare_dynamic(controller_require_s, action->parameters.array[j]) == F_equal_to) {
                action->code |= controller_entry_rule_code_require_d;
              }
              else if (f_compare_dynamic(controller_wait_s, action->parameters.array[j]) == F_equal_to) {
                action->code |= controller_entry_rule_code_wait_d;
              }
              else {
                if (action->status == F_okay) {
                  action->status = F_status_set_error(F_support_not);

                  if (F_status_is_error_not(status_action)) {
                    status_action = action->status;
                  }
                }

                if (global.main->program.error.verbosity > f_console_verbosity_quiet_e) {
                  f_file_stream_lock(global.main->program.error.to);

                  fl_print_format("%r%[%QThe %r item action third parameter (and beyond) must be one of '%]", global.main->program.error.to, f_string_eol_s, global.main->program.error.context, global.main->program.error.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->program.error.context);
                  fl_print_format(f_string_format_r_single_s.string, global.main->program.error.to, global.main->program.error.notable, controller_asynchronous_s, global.main->program.error.notable);
                  fl_print_format("%[', '%]", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context);
                  fl_print_format(f_string_format_r_single_s.string, global.main->program.error.to, global.main->program.error.notable, controller_require_s, global.main->program.error.notable);
                  fl_print_format("%[', or '%]", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context);
                  fl_print_format(f_string_format_r_single_s.string, global.main->program.error.to, global.main->program.error.notable, controller_wait_s, global.main->program.error.notable);
                  fl_print_format("%[' but instead has '%]", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context);
                  fl_print_format(f_string_format_Q_single_s.string, global.main->program.error.to, global.main->program.error.notable, action->parameters.array[j], global.main->program.error.notable);
                  fl_print_format("%['.%]", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context, f_string_eol_s);

                  f_file_stream_unlock(global.main->program.error.to);
                }
              }
            } // for
          }
          else if (action->type == controller_entry_action_type_failsafe_e || action->type == controller_entry_action_type_item_e) {
            if (f_compare_dynamic(controller_main_s, action->parameters.array[0]) == F_equal_to) {
              action->status = F_status_set_error(F_support_not);

              if (F_status_is_error_not(status_action)) {
                status_action = action->status;
              }

              if (global.main->program.error.verbosity > f_console_verbosity_quiet_e) {
                f_file_stream_lock(global.main->program.error.to);

                fl_print_format("%r%[%QThe %r item action may not specify the reserved item '%]", global.main->program.error.to, f_string_eol_s, global.main->program.error.context, global.main->program.error.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->program.error.context);
                fl_print_format(f_string_format_r_single_s.string, global.main->program.error.to, global.main->program.error.notable, controller_main_s, global.main->program.error.notable);
                fl_print_format("%['.%]", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context, f_string_eol_s);

                f_file_stream_unlock(global.main->program.error.to);
              }
            }
          }
          else if (action->type == controller_entry_action_type_timeout_e) {

            if (f_compare_dynamic(controller_kill_s, action->parameters.array[0]) == F_equal_to) {
              action->code = controller_entry_timeout_code_kill_d;
            }
            else if (f_compare_dynamic(controller_start_s, action->parameters.array[0]) == F_equal_to) {
              action->code = controller_entry_timeout_code_start_d;
            }
            else if (f_compare_dynamic(controller_stop_s, action->parameters.array[0]) == F_equal_to) {
              action->code = controller_entry_timeout_code_stop_d;
            }
            else {
              action->status = F_status_set_error(F_support_not);

              if (F_status_is_error_not(status_action)) {
                status_action = action->status;
              }

              if (global.main->program.error.verbosity > f_console_verbosity_quiet_e) {
                f_file_stream_lock(global.main->program.error.to);

                fl_print_format("%r%[%QThe %r item action must have one of '%]", global.main->program.error.to, f_string_eol_s, global.main->program.error.context, global.main->program.error.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->program.error.context);
                fl_print_format(f_string_format_r_single_s.string, global.main->program.error.to, global.main->program.error.notable, controller_kill_s, global.main->program.error.notable);
                fl_print_format("%[', '%]", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context);
                fl_print_format(f_string_format_r_single_s.string, global.main->program.error.to, global.main->program.error.notable, controller_start_s, global.main->program.error.notable);
                fl_print_format("%[', or '%]", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context);
                fl_print_format(f_string_format_r_single_s.string, global.main->program.error.to, global.main->program.error.notable, controller_stop_s, global.main->program.error.notable);
                fl_print_format("%[' but instead has '%]", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context);
                fl_print_format(f_string_format_Q_single_s.string, global.main->program.error.to, global.main->program.error.notable, action->parameters.array[0], global.main->program.error.notable);
                fl_print_format("%['.%]", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context, f_string_eol_s);

                f_file_stream_unlock(global.main->program.error.to);
              }
            }

            if (action->status == F_okay) {
              if (action->parameters.used == 2) {
                action->flag &= ~controller_entry_action_flag_undefined_e;

                status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, action->parameters.array[1], &action->number);

                if (F_status_is_error(status) || status == F_data_not) {
                  action->number = 0;

                  if (status == F_data_not) {
                    action->status = F_status_set_error(F_number);
                  }
                  else {
                    action->status = controller_status_simplify_error(F_status_set_fine(status));
                  }

                  if (F_status_set_fine(status) == F_memory_not) {
                    controller_print_error_entry(&main->program.error, is_entry, F_status_set_fine(status), macro_controller_f(fl_conversion_dynamic_to_unsigned_detect), F_true);

                    status_action = status;

                    break;
                  }

                  if (global.main->program.error.verbosity > f_console_verbosity_quiet_e) {
                    f_file_stream_lock(global.main->program.error.to);

                    fl_print_format("%r%[%QThe %r item action parameter '%]", global.main->program.error.to, f_string_eol_s, global.main->program.error.context, global.main->program.error.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->program.error.context);
                    fl_print_format(f_string_format_Q_single_s.string, global.main->program.error.to, global.main->program.error.notable, action->parameters.array[1], global.main->program.error.notable);
                    fl_print_format("%[' is not a valid supported number.%]", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context, f_string_eol_s);

                    f_file_stream_unlock(global.main->program.error.to);
                  }
                }
              }
              else {
                action->flag |= controller_entry_action_flag_undefined_e;
              }
            }
          }
          else if (action->type == controller_entry_action_type_ready_e) {
            if (action->parameters.used) {
              if (f_compare_dynamic(controller_wait_s, action->parameters.array[0]) == F_equal_to) {
                action->code |= controller_entry_rule_code_wait_d;
              }
              else {
                action->status = F_status_set_error(F_support_not);

                if (global.main->program.error.verbosity > f_console_verbosity_quiet_e) {
                  f_file_stream_lock(global.main->program.error.to);

                  fl_print_format("%r%[%QThe %r item action may only have '%]", global.main->program.error.to, f_string_eol_s, global.main->program.error.context, global.main->program.error.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->program.error.context);
                  fl_print_format(f_string_format_r_single_s.string, global.main->program.error.to, global.main->program.error.notable, controller_wait_s, global.main->program.error.notable);
                  fl_print_format("%[' but instead has '%]", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context);
                  fl_print_format(f_string_format_Q_single_s.string, global.main->program.error.to, global.main->program.error.notable, action->parameters.array[0], global.main->program.error.notable);
                  fl_print_format("%['.%]", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context, f_string_eol_s);

                  f_file_stream_unlock(global.main->program.error.to);
                }
              }
            }
          }
        }
      }

      ++actions->used;
    } // for

    if (F_status_is_error(status_action)) {
      return status_action;
    }

    return status;
  }
#endif // _di_controller_entry_action_read_

#ifdef __cplusplus
} // extern "C"
#endif
