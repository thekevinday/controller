#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_entry_action_read_
  f_status_t controller_entry_action_read(controller_t * const main, controller_entry_t * const entry, const f_range_t range, controller_entry_actions_t * const actions) {

    if (!main || !entry || !actions) return F_status_set_error(F_parameter);

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

    controller_interrupt_t custom = macro_controller_interrupt_t_initialize_1(entry->flag & controller_entry_flag_is_e, main);
    f_state_t state = macro_f_state_t_initialize_1(controller_allocation_large_d, controller_allocation_small_d, F_okay, 0, 0, 0, &controller_thread_signal_state_fss, 0, (void *) &custom, 0);

    {
      f_range_t content_range = range;

      fll_fss_extended_read(main->thread.cache.buffer_file, &content_range, &main->thread.cache.object_actions, &main->thread.cache.content_actions, 0, 0, &main->thread.cache.delimits, 0, &state);
    }

    if (F_status_is_error(state.status)) {
      controller_print_error_entry(&main->program.error, entry->flag & controller_entry_flag_is_e, F_status_set_fine(state.status), macro_controller_f(fll_fss_extended_read), F_true);

      return state.status;
    }

    f_fss_apply_delimit(main->thread.cache.delimits, &main->thread.cache.buffer_file, &state);

    if (F_status_is_error(state.status)) {
      controller_print_error_entry(&main->program.error, entry->flag & controller_entry_flag_is_e, F_status_set_fine(state.status), macro_controller_f(f_fss_apply_delimit), F_true);

      return state.status;
    }

    main->thread.cache.delimits.used = 0;

    state.status = f_memory_array_increase_by(main->thread.cache.object_actions.used, sizeof(controller_entry_action_t), (void **) &actions->array, &actions->used, &actions->size);

    if (F_status_is_error(state.status)) {
      controller_print_error_entry(&main->program.error, entry->flag & controller_entry_flag_is_e, F_status_set_fine(state.status), macro_controller_f(f_memory_array_increase_by), F_true);

      return state.status;
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

      f_fss_count_lines(main->thread.cache.buffer_file, main->thread.cache.object_actions.array[i].start, &main->thread.cache.action.line_action, &state);

      if (F_status_is_error(state.status)) {
        controller_print_error_entry(&main->program.error, entry->flag & controller_entry_flag_is_e, F_status_set_fine(state.status), macro_controller_f(f_fss_count_lines), F_true);

        break;
      }

      action->line = ++main->thread.cache.action.line_action;

      state.status = f_rip_dynamic_partial_nulless(main->thread.cache.buffer_file, main->thread.cache.object_actions.array[i], &main->thread.cache.action.name_action);

      if (F_status_is_error(state.status)) {
        controller_print_error_entry(&main->program.error, entry->flag & controller_entry_flag_is_e, F_status_set_fine(state.status), macro_controller_f(f_rip_dynamic_partial_nulless), F_true);

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
        controller_print_warning_entry_action_unknown(&main->program.warning, &main->thread.cache.action, entry->flag & controller_entry_flag_is_e, main->thread.cache.action.name_action);

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
        action->status = controller_status_simplify_error(F_parameter);

        controller_print_error_entry_action_requires_range(&main->program.error, &main->thread.cache.action, entry->flag & controller_entry_flag_is_e, main->thread.cache.action.name_action, at_least, at_most, action->type);
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
        state.status = f_memory_array_increase_by(allocate, sizeof(f_string_dynamic_t), (void **) &action->parameters.array, &action->parameters.used, &action->parameters.size);

        if (F_status_is_error(state.status)) {
          controller_print_error_entry(&main->program.error, entry->flag & controller_entry_flag_is_e, F_status_set_fine(state.status), macro_controller_f(f_memory_array_increase_by), F_true);

          action->status = state.status;

          if (F_status_is_error_not(status_action)) {
            status_action = state.status;
          }

          break;
        }

        for (j = 0; j < allocate && j < main->thread.cache.content_actions.array[i].used; ++j) {

          action->parameters.array[j].used = 0;

          if (main->thread.cache.content_actions.array[i].array[j].start > main->thread.cache.content_actions.array[i].array[j].stop) continue;

          state.status = f_memory_array_increase_by((main->thread.cache.content_actions.array[i].array[j].stop - main->thread.cache.content_actions.array[i].array[j].start) + 1, sizeof(f_char_t), (void **) &action->parameters.array[j].string, &action->parameters.array[j].used, &action->parameters.array[j].size);

          if (F_status_is_error(state.status)) {
            controller_print_error_entry(&main->program.error, entry->flag & controller_entry_flag_is_e, F_status_set_fine(state.status), macro_controller_f(f_memory_array_increase_by), F_true);

            break;
          }

          state.status = f_string_dynamic_partial_append_nulless(main->thread.cache.buffer_file, main->thread.cache.content_actions.array[i].array[j], &action->parameters.array[j]);

          if (F_status_is_error(state.status)) {
            controller_print_error_entry(&main->program.error, entry->flag & controller_entry_flag_is_e, F_status_set_fine(state.status), macro_controller_f(f_string_dynamic_partial_append_nulless), F_true);

            break;
          }

          ++action->parameters.used;
        } // for

        if (F_status_is_error_not(action->status)) {
          if (action->type == controller_entry_action_type_consider_e || controller_entry_action_type_is_rule(action->type)) {
            if (action->parameters.array[0].used) {

              // Force the path to be canonical (removing all '../' parts).
              state.status = controller_path_canonical_relative(main, main->process.path_current, action->parameters.array[0], &main->thread.cache.buffer_path);

              if (F_status_is_error(state.status)) {
                controller_print_error_entry_file(&main->program.error, entry->flag & controller_entry_flag_is_e, F_status_set_fine(state.status), macro_controller_f(controller_path_canonical_relative), F_true, main->thread.cache.action.generic, f_file_operation_analyze_s, fll_error_file_type_path_e);

                action->status = state.status;

                if (F_status_set_fine(state.status) == F_memory_not) {
                  status_action = state.status;

                  break;
                }

                if (F_status_is_error_not(status_action)) {
                  status_action = state.status;
                }
              }
            }
            else {
              action->status = controller_status_simplify_error(F_parameter);

              if (F_status_is_error_not(status_action)) {
                status_action = action->status;
              }

              controller_print_error_entry_action_parameter_empty(&main->program.error, &main->thread.cache.action, entry->flag & controller_entry_flag_is_e, "first parameter");
            }

            if (action->parameters.array[1].used) {
              main->thread.cache.buffer_path.used = 0;

              state.status = f_file_name_base(action->parameters.array[1], &main->thread.cache.buffer_path);

              if (F_status_is_error(state.status)) {
                controller_print_error_entry(&main->program.error, entry->flag & controller_entry_flag_is_e, F_status_set_fine(state.status), macro_controller_f(f_file_name_base), F_true);

                if (F_status_set_fine(state.status) == F_memory_not) {
                  status_action = controller_status_simplify_error(state.status);

                  break;
                }

                action->status = controller_status_simplify_error(state.status);

                if (F_status_is_error_not(status_action)) {
                  status_action = state.status;
                }
              }
              else {
                if (f_compare_dynamic(action->parameters.array[1], main->thread.cache.buffer_path) == F_equal_to_not) {
                  controller_print_error_entry_action_parameter_second_base(&main->program.error, &main->thread.cache.action, entry->flag & controller_entry_flag_is_e, action->parameters.array[1], main->thread.cache.buffer_path);

                  action->status = controller_status_simplify_error(F_parameter);

                  if (F_status_is_error_not(status_action)) {
                    status_action = action->status;
                  }
                }
              }
            }
            else {
              action->status = controller_status_simplify_error(F_parameter);

              if (F_status_is_error_not(status_action)) {
                status_action = action->status;
              }

              controller_print_error_entry_action_parameter_empty(&main->program.error, &main->thread.cache.action, entry->flag & controller_entry_flag_is_e, "second parameter");
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
                  action->status = controller_status_simplify_error(F_support_not);

                  if (F_status_is_error_not(status_action)) {
                    status_action = action->status;
                  }
                }

                controller_print_error_entry_action_invalid_allow_3(&main->program.error, &main->thread.cache.action, entry->flag & controller_entry_flag_is_e, "third parameter (and beyond)", action->parameters.array[j], controller_asynchronous_s, controller_require_s, controller_wait_s);
              }
            } // for
          }
          else if (action->type == controller_entry_action_type_failsafe_e || action->type == controller_entry_action_type_item_e) {
            if (f_compare_dynamic(controller_main_s, action->parameters.array[0]) == F_equal_to) {
              action->status = controller_status_simplify_error(F_support_not);

              if (F_status_is_error_not(status_action)) {
                status_action = action->status;
              }

              controller_print_error_entry_action_unsupported_reserve(&main->program.error, &main->thread.cache.action, entry->flag & controller_entry_flag_is_e, controller_main_s);
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
              action->status = controller_status_simplify_error(F_support_not);

              if (F_status_is_error_not(status_action)) {
                status_action = action->status;
              }

              controller_print_error_entry_action_invalid_allow_3(&main->program.error, &main->thread.cache.action, entry->flag & controller_entry_flag_is_e, 0, action->parameters.array[0], controller_kill_s, controller_start_s, controller_stop_s);
            }

            if (action->status == F_okay) {
              if (action->parameters.used == 2) {
                action->flag &= ~controller_entry_action_flag_undefined_e;

                state.status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, action->parameters.array[1], &action->number);

                if (F_status_is_error(state.status) || state.status == F_data_not) {
                  action->number = 0;

                  if (state.status == F_data_not) {
                    action->status = controller_status_simplify_error(F_number);
                  }
                  else {
                    action->status = controller_status_simplify_error(F_status_set_fine(state.status));
                  }

                  if (F_status_set_fine(state.status) == F_memory_not) {
                    controller_print_error_entry(&main->program.error, entry->flag & controller_entry_flag_is_e, F_status_set_fine(state.status), macro_controller_f(fl_conversion_dynamic_to_unsigned_detect), F_true);

                    status_action = state.status;

                    break;
                  }

                  controller_print_error_entry_action_unsupported_number(&main->program.error, &main->thread.cache.action, entry->flag & controller_entry_flag_is_e, action->parameters.array[1]);
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
                action->status = controller_status_simplify_error(F_support_not);

                controller_print_error_entry_action_invalid_allow_1(&main->program.error, &main->thread.cache.action, entry->flag & controller_entry_flag_is_e, 0, action->parameters.array[0], controller_wait_s);
              }
            }
          }
        }
      }

      ++actions->used;
    } // for

    return F_status_is_error(status_action) ? status_action : state.status;
  }
#endif // _di_controller_entry_action_read_

#ifndef _di_controller_entry_action_type_name_
  f_string_static_t controller_entry_action_type_name(const uint8_t type) {

    switch (type) {
      case controller_entry_action_type_consider_e:
        return controller_consider_s;

      case controller_entry_action_type_execute_e:
        return controller_execute_s;

      case controller_entry_action_type_failsafe_e:
        return controller_failsafe_s;

      case controller_entry_action_type_freeze_e:
        return controller_freeze_s;

      case controller_entry_action_type_item_e:
        return controller_item_s;

      case controller_entry_action_type_kexec_e:
        return controller_kexec_s;

      case controller_entry_action_type_kill_e:
        return controller_kill_s;

      case controller_entry_action_type_pause_e:
        return controller_pause_s;

      case controller_entry_action_type_ready_e:
        return controller_ready_s;

      case controller_entry_action_type_reboot_e:
        return controller_reboot_s;

      case controller_entry_action_type_reload_e:
        return controller_reload_s;

      case controller_entry_action_type_restart_e:
        return controller_restart_s;

      case controller_entry_action_type_resume_e:
        return controller_resume_s;

      case controller_entry_action_type_shutdown_e:
        return controller_shutdown_s;

      case controller_entry_action_type_start_e:
        return controller_start_s;

      case controller_entry_action_type_stop_e:
        return controller_stop_s;

      case controller_entry_action_type_thaw_e:
        return controller_thaw_s;

      case controller_entry_action_type_timeout_e:
        return controller_timeout_s;
    }

    return f_string_empty_s;
  }
#endif // _di_controller_entry_action_type_name_

#ifndef _di_controller_entry_action_type_is_rule_
  f_status_t controller_entry_action_type_is_rule(uint8_t type) {

    switch (type) {
      case controller_entry_action_type_freeze_e:
      case controller_entry_action_type_kill_e:
      case controller_entry_action_type_pause_e:
      case controller_entry_action_type_reload_e:
      case controller_entry_action_type_restart_e:
      case controller_entry_action_type_resume_e:
      case controller_entry_action_type_start_e:
      case controller_entry_action_type_stop_e:
      case controller_entry_action_type_thaw_e:
        return F_true;
    }

    return F_false;
  }
#endif // _di_controller_entry_action_type_is_rule_

#ifndef _di_controller_entry_action_type_to_rule_action_type_
  uint8_t controller_entry_action_type_to_rule_action_type(uint8_t type) {

    switch (type) {
      case controller_entry_action_type_freeze_e:
        return controller_rule_action_type_freeze_e;

      case controller_entry_action_type_kill_e:
        return controller_rule_action_type_kill_e;

      case controller_entry_action_type_pause_e:
        return controller_rule_action_type_pause_e;

      case controller_entry_action_type_reload_e:
        return controller_rule_action_type_reload_e;

      case controller_entry_action_type_restart_e:
        return controller_rule_action_type_restart_e;

      case controller_entry_action_type_resume_e:
        return controller_rule_action_type_resume_e;

      case controller_entry_action_type_start_e:
        return controller_rule_action_type_start_e;

      case controller_entry_action_type_stop_e:
        return controller_rule_action_type_stop_e;

      case controller_entry_action_type_thaw_e:
        return controller_rule_action_type_thaw_e;
    }

    return 0;
  }
#endif // _di_controller_entry_action_type_to_rule_action_type_

#ifdef __cplusplus
} // extern "C"
#endif
