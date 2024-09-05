#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_rule_action_method_name_
  f_string_static_t controller_rule_action_method_name(const uint8_t type) {

    switch (type) {
      case controller_rule_action_method_extended_e:
        return controller_rule_action_method_extended_s;

      case controller_rule_action_method_extended_list_e:
        return controller_rule_action_method_extended_list_s;
    }

    return f_string_empty_s;
  }
#endif // _di_controller_rule_action_method_name_

#ifndef _di_controller_rule_action_type_to_action_execute_type_
  uint8_t controller_rule_action_type_to_action_execute_type(const uint8_t type) {

    switch (type) {
      case controller_rule_action_type_freeze_e:
        return controller_rule_action_execute_type_freeze_e;

      case controller_rule_action_type_kill_e:
        return controller_rule_action_execute_type_kill_e;

      case controller_rule_action_type_pause_e:
        return controller_rule_action_execute_type_pause_e;

      case controller_rule_action_type_reload_e:
        return controller_rule_action_execute_type_reload_e;

      case controller_rule_action_type_restart_e:
        return controller_rule_action_execute_type_restart_e;

      case controller_rule_action_type_resume_e:
        return controller_rule_action_execute_type_resume_e;

      case controller_rule_action_type_start_e:
        return controller_rule_action_execute_type_start_e;

      case controller_rule_action_type_stop_e:
        return controller_rule_action_execute_type_stop_e;

      case controller_rule_action_type_thaw_e:
        return controller_rule_action_execute_type_thaw_e;
    }

    return controller_rule_action_execute_type__enum_size_e;
  }
#endif // _di_controller_rule_action_type_to_action_execute_type_

#ifndef _di_controller_rule_action_read_
  void controller_rule_action_read(controller_t * const main, controller_cache_t * const cache, const uint8_t is_normal, const uint8_t type, const uint8_t method, controller_rule_item_t * const item, controller_rule_actions_t * const actions, f_range_t * const range, f_state_t * const state) {

    if (!state) return;

    if (!main || !cache || !item || !actions || !range) {
      state->status = F_status_set_error(F_parameter);

      return;
    }

    f_number_unsigned_t i = 0;

    for (; i < cache->comments.size; ++i) {

      cache->comments.array[i].start = 1;
      cache->comments.array[i].stop = 0;
    } // for

    for (i = 0; i < cache->delimits.size; ++i) {
      cache->delimits.array[i] = 0;
    } // for

    for (i = 0; i < cache->content_action.size; ++i) {

      cache->content_action.array[i].start = 1;
      cache->content_action.array[i].stop = 0;
    } // for

    cache->close.start = 1;
    cache->close.stop = 0;

    cache->comments.used = 0;
    cache->delimits.used = 0;
    cache->content_action.used = 0;

    if (method == controller_rule_action_method_extended_list_e) {
      fl_fss_extended_list_content_read(cache->buffer_item, range, &cache->content_action, &cache->close, &cache->delimits, &cache->comments, state);

      if (F_status_is_error(state->status)) {
        controller_print_error(&main->program.error, macro_controller_f(fl_fss_extended_list_content_read));

        return;
      }

      if (state->status == F_fss_found_content) {
        f_fss_apply_delimit(cache->delimits, &cache->buffer_item, state);

        if (F_status_is_error(state->status)) {
          controller_print_error(&main->program.error, macro_controller_f(f_fss_apply_delimit));

          return;
        }

        // The "script" and "utility" types use the entire content and can be directly passed through at index 0.
        if (item->type == controller_rule_item_type_script_e || item->type == controller_rule_item_type_utility_e) {
          actions->array[actions->used].parameters.used = 0;

          state->status = f_memory_array_increase(controller_allocation_small_d, sizeof(f_string_dynamic_t), (void **) &actions->array[actions->used].parameters.array, &actions->array[actions->used].parameters.used, &actions->array[actions->used].parameters.size);

          if (F_status_is_error(state->status)) {
            controller_print_error(&main->program.error, macro_controller_f(f_memory_array_increase));

            return;
          }

          state->status = f_memory_array_increase(controller_allocation_small_d, sizeof(f_iki_data_t), (void **) &actions->array[actions->used].ikis.array, &actions->array[actions->used].ikis.used, &actions->array[actions->used].ikis.size);

          if (F_status_is_error(state->status)) {
            controller_print_error(&main->program.error, macro_controller_f(f_memory_array_increase));

            return;
          }

          actions->array[actions->used].type = type;
          actions->array[actions->used].line = cache->action.line_action;
          actions->array[actions->used].status = F_known_not;

          state->status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_action.array[0], &actions->array[actions->used].parameters.array[0]);

          if (F_status_is_error(state->status)) {
            controller_print_error(&main->program.error, macro_controller_f(f_string_dynamic_append_nulless));

            actions->array[actions->used++].status = controller_error_simplify(F_status_set_fine(state->status));

            return;
          }

          if (actions->array[actions->used].parameters.array[0].used) {
            const uint16_t old_step_large = state->step_large;
            const uint16_t old_step_small = state->step_small;
            void * const old_interrupt = state->interrupt;

            state->step_large = controller_allocation_iki_large_d;
            state->step_small = controller_allocation_iki_small_d;
            state->interrupt = &controller_thread_signal_state_iki;

            f_range_t range_iki = macro_f_range_t_initialize_2(actions->array[actions->used].parameters.array[0].used);

            fl_iki_read(&actions->array[actions->used].parameters.array[0], &range_iki, &actions->array[actions->used].ikis.array[0], state);

            state->step_large = old_step_large;
            state->step_small = old_step_small;
            state->interrupt = old_interrupt;

            if (F_status_is_error(state->status)) {
              controller_print_error(&main->program.error, macro_controller_f(fl_iki_read));

              actions->array[actions->used++].status = controller_error_simplify(F_status_set_fine(state->status));

              return;
            }
          }

          actions->array[actions->used].ikis.used = 1;
          actions->array[actions->used++].parameters.used = 1;

          return;
        }

        cache->delimits.used = 0;

        // The object_actions and content_actions caches are being used for the purposes of getting the parameters a given the Action.
        fll_fss_extended_read(cache->buffer_item, &cache->content_action.array[0], &cache->object_actions, &cache->content_actions, 0, 0, &cache->delimits, 0, state);

        if (F_status_is_error(state->status)) {
          controller_print_error(&main->program.error, macro_controller_f(fll_fss_extended_read));

          return;
        }

        f_fss_apply_delimit(cache->delimits, &cache->buffer_item, state);

        if (F_status_is_error(state->status)) {
          controller_print_error(&main->program.error, macro_controller_f(f_fss_apply_delimit));

          return;
        }

        for (i = 0; i < cache->object_actions.used; ++i) {

          state->status = f_memory_array_increase(controller_allocation_small_d, sizeof(controller_rule_action_t), (void **) &actions->array, &actions->used, &actions->size);

          if (F_status_is_error(state->status)) {
            controller_print_error(&main->program.error, macro_controller_f(f_memory_array_increase));

            return;
          }

          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &actions->array[actions->used].line, state);

          if (F_status_is_error(state->status)) {
            controller_print_error(&main->program.error, macro_controller_f(f_fss_count_lines));

            return;
          }

          actions->array[actions->used].type = type;
          actions->array[actions->used].line += ++item->line;
          actions->array[actions->used].status = F_known_not;

          controller_rule_parameters_read(main, cache->buffer_item, &cache->object_actions.array[i], &cache->content_actions.array[i], &actions->array[actions->used], state);

          if (F_status_is_error(state->status)) {
            actions->array[actions->used++].status = controller_error_simplify(F_status_set_fine(state->status));

            return;
          }

          actions->array[actions->used++].status = state->status;
        } // for

        range->start = cache->content_action.array[0].start;
      }
      else {
        state->status = F_data_not;
      }
    }
    else {
      fl_fss_extended_content_read(cache->buffer_item, range, &cache->content_action, 0, &cache->delimits, state);

      if (F_status_is_error(state->status)) {
        controller_print_error(&main->program.error, macro_controller_f(fll_fss_extended_content_read));
      }
      else if (state->status == F_fss_found_content) {
        f_fss_apply_delimit(cache->delimits, &cache->buffer_item, state);

        if (F_status_is_error(state->status)) {
          controller_print_error(&main->program.error, macro_controller_f(f_fss_apply_delimit));
        }
        else if (type == controller_rule_action_type_pid_file_e) {
          item->pid_file.used = 0;

          state->status = f_rip_dynamic_partial(cache->buffer_item, cache->content_action.array[0], &item->pid_file);

          if (F_status_is_error(state->status)) {
            controller_print_error(&main->program.error, macro_controller_f(f_rip_dynamic_partial));
          }
        }
        else if (type == controller_rule_action_type_rerun_e) {
          uint8_t type_rerun = 0;

          if (cache->content_action.used) {
            if (f_compare_dynamic_partial_string(controller_freeze_s.string, cache->buffer_item, controller_freeze_s.used, cache->content_action.array[0]) == F_equal_to) {
              type_rerun = controller_rule_action_execute_type_freeze_e;
            }
            if (f_compare_dynamic_partial_string(controller_kill_s.string, cache->buffer_item, controller_kill_s.used, cache->content_action.array[0]) == F_equal_to) {
              type_rerun = controller_rule_action_execute_type_kill_e;
            }
            else if (f_compare_dynamic_partial_string(controller_pause_s.string, cache->buffer_item, controller_pause_s.used, cache->content_action.array[0]) == F_equal_to) {
              type_rerun = controller_rule_action_execute_type_pause_e;
            }
            else if (f_compare_dynamic_partial_string(controller_reload_s.string, cache->buffer_item, controller_reload_s.used, cache->content_action.array[0]) == F_equal_to) {
              type_rerun = controller_rule_action_execute_type_reload_e;
            }
            else if (f_compare_dynamic_partial_string(controller_restart_s.string, cache->buffer_item, controller_restart_s.used, cache->content_action.array[0]) == F_equal_to) {
              type_rerun = controller_rule_action_execute_type_restart_e;
            }
            else if (f_compare_dynamic_partial_string(controller_resume_s.string, cache->buffer_item, controller_resume_s.used, cache->content_action.array[0]) == F_equal_to) {
              type_rerun = controller_rule_action_execute_type_resume_e;
            }
            else if (f_compare_dynamic_partial_string(controller_start_s.string, cache->buffer_item, controller_start_s.used, cache->content_action.array[0]) == F_equal_to) {
              type_rerun = controller_rule_action_execute_type_start_e;
            }
            else if (f_compare_dynamic_partial_string(controller_stop_s.string, cache->buffer_item, controller_stop_s.used, cache->content_action.array[0]) == F_equal_to) {
              type_rerun = controller_rule_action_execute_type_stop_e;
            }
            else if (f_compare_dynamic_partial_string(controller_thaw_s.string, cache->buffer_item, controller_thaw_s.used, cache->content_action.array[0]) == F_equal_to) {
              type_rerun = controller_rule_action_execute_type_thaw_e;
            }
          }

          if (!type_rerun) {
            state->status = F_status_set_error(F_valid_not);

            controller_print_error_rule_action_first(&main->program.error, &cache->action, cache->buffer_item, cache->content_action.array[0]);

            return;
          }

          controller_rule_rerun_item_t *rerun_item = 0;

          if (cache->content_action.used > 1) {
            if (f_compare_dynamic_partial_string(controller_failure_s.string, cache->buffer_item, controller_failure_s.used, cache->content_action.array[1]) == F_equal_to) {
              rerun_item = &item->reruns[type_rerun].failure;
              item->reruns[type_rerun].is |= controller_rule_rerun_is_failure_d;
            }
            else if (f_compare_dynamic_partial_string(controller_success_s.string, cache->buffer_item, controller_success_s.used, cache->content_action.array[1]) == F_equal_to) {
              rerun_item = &item->reruns[type_rerun].success;
              item->reruns[type_rerun].is |= controller_rule_rerun_is_success_d;
            }
          }
          else {
            state->status = F_status_set_error(F_valid_not);

            controller_print_error_rule_action_second(&main->program.error, &cache->action, cache->buffer_item, cache->content_action.array[1]);

            return;
          }

          for (i = 2; i < cache->content_action.used; ++i) {

            if (f_compare_dynamic_partial_string(controller_delay_s.string, cache->buffer_item, controller_delay_s.used, cache->content_action.array[i]) == F_equal_to) {
              state->status = controller_rule_action_read_rerun_number(main, cache, controller_delay_s, &i, &rerun_item->delay);
            }
            else if (f_compare_dynamic_partial_string(controller_max_s.string, cache->buffer_item, controller_max_s.used, cache->content_action.array[i]) == F_equal_to) {
              state->status = controller_rule_action_read_rerun_number(main, cache, controller_max_s, &i, &rerun_item->max);
            }
            else if (f_compare_dynamic_partial_string(controller_reset_s.string, cache->buffer_item, controller_reset_s.used, cache->content_action.array[i]) == F_equal_to) {
              item->reruns[type_rerun].is |= rerun_item == &item->reruns[type_rerun].failure ? controller_rule_rerun_is_failure_reset_d : controller_rule_rerun_is_success_reset_d;
            }
            else {
              state->status = F_status_set_error(F_valid_not);

              controller_print_error_rule_action_unknown(&main->program.error, &cache->action, controller_rerun_s, cache->buffer_item, cache->content_action.array[i]);

              return;
            }
          } // for
        }
        else if (type == controller_rule_action_type_with_e) {
          for (i = 0; i < cache->content_action.used; ++i) {

            if (f_compare_dynamic_partial_string(controller_full_path_s.string, cache->buffer_item, controller_full_path_s.used, cache->content_action.array[i]) == F_equal_to) {
              item->with |= controller_with_full_path_d;
            }
            else if (f_compare_dynamic_partial_string(controller_session_new_s.string, cache->buffer_item, controller_session_new_s.used, cache->content_action.array[i]) == F_equal_to) {
              item->with |= controller_with_session_new_d;

              // The "session_new" and "session_same" are mutually exclusive.
              item->with &= ~controller_with_session_same_d;
            }
            else if (f_compare_dynamic_partial_string(controller_session_same_s.string, cache->buffer_item, controller_session_same_s.used, cache->content_action.array[i]) == F_equal_to) {
              item->with |= controller_with_session_same_d;

              // The "session_new" and "session_same" are mutually exclusive.
              item->with &= ~controller_with_session_new_d;
            }
            else {
              controller_print_error_rule_action_unknown(&main->program.error, &cache->action, controller_with_s, cache->buffer_item, cache->content_action.array[i]);

              state->status = F_status_set_error(F_valid_not);

              break;
            }
          } // for
        }
        else if (item->type == controller_rule_item_type_script_e || item->type == controller_rule_item_type_utility_e) {
          state->status = f_memory_array_increase(controller_allocation_small_d, sizeof(f_string_dynamic_t), (void **) &actions->array[actions->used].parameters.array, &actions->array[actions->used].parameters.used, &actions->array[actions->used].parameters.size);

          if (F_status_is_error(state->status)) {
            controller_print_error(&main->program.error, macro_controller_f(f_memory_array_increase));

            return;
          }

          state->status = f_memory_array_increase(controller_allocation_small_d, sizeof(f_iki_data_t), (void **) &actions->array[actions->used].ikis.array, &actions->array[actions->used].ikis.used, &actions->array[actions->used].ikis.size);

          if (F_status_is_error(state->status)) {
            controller_print_error(&main->program.error, macro_controller_f(f_memory_array_increase));

            return;
          }

          // The "script" types use the entire content as a single string piped to the script, so merge all arguments together.
          actions->array[actions->used].type = type;
          actions->array[actions->used].line = cache->action.line_action;
          actions->array[actions->used].status = F_known_not;

          for (i = 0; i < cache->content_action.used; ++i) {

            state->status = f_string_dynamic_partial_mash_nulless(f_string_space_s, cache->buffer_item, cache->content_action.array[i], &actions->array[actions->used].parameters.array[0]);
            if (F_status_is_error(state->status)) break;
          } // for

          if (F_status_is_error(state->status)) {
            controller_print_error(&main->program.error, macro_controller_f(f_string_dynamic_partial_mash_nulless));

            actions->array[actions->used++].status = controller_error_simplify(F_status_set_fine(state->status));

            return;
          }

          if (actions->array[actions->used].parameters.array[0].used) {
            const uint16_t old_step_large = state->step_large;
            const uint16_t old_step_small = state->step_small;
            void * const old_interrupt = state->interrupt;

            state->step_large = controller_allocation_iki_large_d;
            state->step_small = controller_allocation_iki_small_d;
            state->interrupt = &controller_thread_signal_state_iki;

            f_range_t range_iki = macro_f_range_t_initialize_2(actions->array[actions->used].parameters.array[0].used);

            fl_iki_read(&actions->array[actions->used].parameters.array[0], &range_iki, &actions->array[actions->used].ikis.array[0], state);

            state->step_large = old_step_large;
            state->step_small = old_step_small;
            state->interrupt = old_interrupt;

            if (F_status_is_error(state->status)) {
              controller_print_error(&main->program.error, macro_controller_f(fl_iki_read));

              actions->array[actions->used++].status = controller_error_simplify(F_status_set_fine(state->status));

              return;
            }
          }

          actions->array[actions->used].ikis.used = 1;
          actions->array[actions->used++].parameters.used = 1;
        }
        else {
          f_fss_count_lines(cache->buffer_item, range->start, &actions->array[actions->used].line, state);

          if (F_status_is_error(state->status)) {
            controller_print_error(&main->program.error, macro_controller_f(f_fss_count_lines));

            return;
          }

          actions->array[actions->used].type = type;
          actions->array[actions->used].line += ++item->line;
          actions->array[actions->used].status = F_known_not;

          controller_rule_parameters_read(main, cache->buffer_item, 0, &cache->content_action, &actions->array[actions->used], state);

          if (F_status_is_error(state->status)) {
            actions->array[actions->used++].status = controller_error_simplify(F_status_set_fine(state->status));

            return;
          }

          actions->array[actions->used++].status = state->status;
        }
      }
      else {
        state->status = F_data_not;
      }
    }

    if (F_status_is_error_not(state->status) && state->status == F_data_not) {
      controller_print_debug_rule_action_empty(&main->program.debug, cache);
    }
  }
#endif // _di_controller_rule_action_read_

#ifndef _di_controller_rule_action_read_rerun_number_
  f_status_t controller_rule_action_read_rerun_number(controller_t * const main, controller_cache_t * const cache, const f_string_static_t name, f_number_unsigned_t * const index, f_number_unsigned_t * const number) {

    f_status_t status = F_okay;
    f_number_signed_t parsed = 0;

    if (*index + 1 == cache->content_action.used) {
      status = F_status_set_error(F_valid_not);
    }
    else {
      status = fl_conversion_dynamic_partial_to_signed_detect(fl_conversion_data_base_10_c, cache->buffer_item, cache->content_action.array[++(*index)], &parsed);

      if (F_status_set_fine(status) == F_number_positive) {
        status = fl_conversion_dynamic_partial_to_signed_detect(fl_conversion_data_base_10_c, cache->buffer_item, controller_range_after_number_sign(cache->buffer_item, cache->content_action.array[*index]), &parsed);
      }

      if (status == F_data_not) {
        status = F_status_set_error(F_valid_not);
      }
    }

    if (F_status_is_error(status)) {
      if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
        status = F_status_set_fine(status);

        if (status != F_valid_not && status != F_number && status != F_number_decimal && status != F_number_overflow && status != F_number_underflow && status != F_number_negative) {
          controller_print_error(&main->program.error, macro_controller_f(fl_conversion_dynamic_partial_to_signed_detect));
        }
        else {
          controller_print_error_rule_action_positive_number_not(&main->program.error, &cache->action, name, cache->buffer_item, cache->content_action, *index, status);
        }
      }
    }
    else {
      *number = (f_number_unsigned_t) parsed;
      status = F_okay;
    }

    return status;
  }
#endif // _di_controller_rule_action_read_rerun_number_

#ifdef __cplusplus
} // extern "C"
#endif
