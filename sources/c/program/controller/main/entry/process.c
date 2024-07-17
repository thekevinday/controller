#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_entry_process_
  f_status_t controller_entry_process(controller_t * const main, const uint8_t is_entry, const uint8_t failsafe) {

    f_status_t status = F_okay;
    f_status_t status_lock = F_okay;

    f_number_unsigned_t at_i = 0;
    f_number_unsigned_t at_j = 1;

    uint8_t options_force = 0;
    uint8_t options_instance = 0;

    controller_entry_t * const entry = is_entry ? &main->process.entry : &main->process.exit;
    controller_cache_t * const cache = &main->thread.cache;
    controller_entry_action_t *entry_action = 0;
    controller_entry_actions_t *entry_actions = 0;

    // An empty stack is used here because each Rule here is the first Rule run in the Rule's scope.
    const f_number_unsigneds_t stack = f_number_unsigneds_t_initialize;

    cache->ats.used = 0;
    cache->stack.used = 0;

    cache->action.line_action = 0;
    cache->action.line_item = 0;
    cache->action.name_action.used = 0;
    cache->action.name_item.used = 0;

    status = f_memory_array_increase(controller_allocation_small_d, sizeof(f_number_unsigned_t), (void **) &cache->ats.array, &cache->ats.used, &cache->ats.size);

    if (F_status_is_error(status)) {
      controller_print_error_entry(&main->program.error, is_entry, F_status_set_fine(status), macro_controller_f(f_memory_array_increase), F_true);

      return status;
    }

    // Utilize the "ats" cache as an item execution stack (at_i is for item index, and at_j (at_i + 1) is for Action index).
    cache->ats.array[0] = failsafe ? main->process.failsafe_item_id : 0;
    cache->ats.array[1] = 0;
    cache->ats.used = 2;

    cache->action.line_item = entry->items.array[cache->ats.array[0]].line;
    cache->action.name_item.used = 0;

    status = f_string_dynamic_append_nulless(entry->items.array[cache->ats.array[0]].name, &cache->action.name_item);

    if (F_status_is_error(status)) {
      controller_print_error_entry(&main->program.error, is_entry, F_status_set_fine(status), macro_controller_f(f_string_dynamic_append_nulless), F_true);

      return status;
    }

    if ((main->setting.flag & controller_main_flag_simulate_e) || main->program.message.verbosity > f_console_verbosity_normal_e) {
      controller_print_message_entry_item_process(&main->program.message, is_entry, failsafe ? controller_failsafe_s : f_string_empty_s, cache->action.name_item);
    }

    // The pre-process determines if ready is explicitly specified within the Entry file and if it is not start as ready.
    if (main->process.ready == controller_process_ready_yes_e) {
      status = controller_perform_ready(main, is_entry);
      if (F_status_is_error(status)) return status;
    }

    while (controller_thread_is_enabled(&main->thread, is_entry)) {

      entry_actions = &entry->items.array[cache->ats.array[at_i]].actions;

      for (; cache->ats.array[at_j] < entry_actions->used && controller_thread_is_enabled(&main->thread, is_entry); ++cache->ats.array[at_j]) {

        entry_action = &entry_actions->array[cache->ats.array[at_j]];

        cache->action.line_action = entry_action->line;
        cache->action.name_action.used = 0;

        status = f_string_dynamic_append_nulless(controller_entry_action_type_name(entry_action->type), &cache->action.name_action);

        if (F_status_is_error(status)) {
          controller_print_error_entry(&main->program.error, is_entry, F_status_set_fine(status), macro_controller_f(f_string_dynamic_append_nulless), F_true);

          return status;
        }

        if (F_status_is_error(entry_action->status)) {
          if (main->setting.flag & controller_main_flag_simulate_e) {
            controller_print_message_entry_action_state_failed(&main->program.message, cache, entry_action, is_entry);
          }
          else {
            if ((entry_action->code & controller_entry_rule_code_require_d) && main->program.error.verbosity > f_console_verbosity_quiet_e || !(entry_action->code & controller_entry_rule_code_require_d) && (main->program.warning.verbosity == f_console_verbosity_verbose_e || main->program.warning.verbosity == f_console_verbosity_debug_e)) {
              fl_print_t * const print = (entry_action->code & controller_entry_rule_code_require_d)
                ? &main->program.error
                : (main->program.error.verbosity != f_console_verbosity_error_e)
                  ? &main->program.warning
                  : 0;

              if (print) {
                controller_print_message_entry_action_state(print, cache, entry_action, is_entry);
              }
            }

            if (controller_entry_action_type_is_rule(entry_action->type) && entry_action->code & controller_entry_rule_code_require_d) {
              return F_status_is_error(F_require);
            }
          }

          continue;
        }

        if (entry_action->type == controller_entry_action_type_ready_e) {
          if ((entry_action->code & controller_entry_rule_code_wait_d) || main->process.ready == controller_process_ready_wait_e) {
            if ((main->setting.flag & controller_main_flag_simulate_e) || main->program.error.verbosity == f_console_verbosity_verbose_e || main->program.error.verbosity == f_console_verbosity_debug_e || entry->show == controller_entry_show_init_e) {
              controller_print_message_entry_action_wait(&main->program.message, is_entry, controller_ready_s);
            }

            if (!(main->setting.flag & controller_main_flag_validate_e)) {
              status = controller_rule_wait_all(main, is_entry, F_false);
              if (F_status_is_error(status)) return status;
            }
          }

          if (main->process.ready == controller_process_ready_yes_e) {
            if ((main->setting.flag & controller_main_flag_simulate_e) || main->program.error.verbosity == f_console_verbosity_verbose_e || main->program.error.verbosity == f_console_verbosity_debug_e) {
              controller_print_message_entry_action_ready(&main->program.message, is_entry, controller_ready_s);
            }
          }
          else {
            if (!failsafe && (main->program.error.verbosity == f_console_verbosity_verbose_e || entry->show == controller_entry_show_init_e) && !(main->setting.flag & controller_main_flag_simulate_e)) {
              controller_print_message_entry_state(&main->program.message, is_entry, controller_ready_s);
            }

            status = controller_perform_ready(main, is_entry);
            if (F_status_is_error(status)) return status;
          }
        }
        else if (entry_action->type == controller_entry_action_type_item_e) {
          if (entry_action->number == 0 || entry_action->number >= entry->items.used || failsafe && entry_action->number == main->process.failsafe_item_id) {

            // This should not happen if the pre-process is working as intended, but in case it doesn't, return a critical error to prevent infinite recursion and similar errors.
            controller_print_error_entry_item_invalid(&main->program.error, cache, is_entry, entry_action->number);

            return F_status_is_error(F_critical);
          }

          status = f_memory_array_increase(controller_allocation_small_d, sizeof(f_number_unsigned_t), (void **) &cache->ats.array, &cache->ats.used, &cache->ats.size);

          if (F_status_is_error(status)) {
            controller_print_error_entry(&main->program.error, is_entry, F_status_set_fine(status), macro_controller_f(f_memory_array_increase), F_true);

            return status;
          }

          // Continue into the requested item.
          cache->ats.array[cache->ats.used] = entry_action->number;
          cache->ats.array[cache->ats.used + 1] = 0;

          at_i = cache->ats.used;
          at_j = cache->ats.used + 1;

          cache->ats.used += 2;

          cache->action.name_action.used = 0;
          cache->action.line_action = 0;

          cache->action.name_item.used = 0;
          cache->action.line_item = entry->items.array[cache->ats.array[at_i]].line;

          status = f_string_dynamic_append_nulless(entry->items.array[cache->ats.array[at_i]].name, &cache->action.name_item);

          if (F_status_is_error(status)) {
            controller_print_error_entry(&main->program.error, is_entry, F_status_set_fine(status), macro_controller_f(f_string_dynamic_append_nulless), F_true);

            return status;
          }

          if ((main->setting.flag & controller_main_flag_simulate_e) || main->program.message.verbosity > f_console_verbosity_normal_e) {
            controller_print_message_entry_item_process(&main->program.message, is_entry, f_string_empty_s, cache->action.name_item);
          }

          // Exit inner loop to force restarting and start processing the requested item.
          break;
        }
        else if (entry_action->type == controller_entry_action_type_consider_e || controller_entry_action_type_is_rule(entry_action->type)) {
          status_lock = controller_lock_write(is_entry, F_true, &main->thread, &main->thread.lock.rule);

          if (F_status_is_error(status_lock)) {
            controller_print_error_lock_critical(&main->program.error, F_status_set_fine(status_lock), F_false);

            break;
          }

          status = f_memory_array_increase(controller_allocation_small_d, sizeof(controller_rule_t), (void **) &main->process.rules.array, &main->process.rules.used, &main->process.rules.size);

          f_thread_unlock(&main->thread.lock.rule);

          if (F_status_is_error(status)) {
            controller_print_error_entry(&main->program.error, is_entry, F_status_set_fine(status), macro_controller_f(f_memory_array_increase), F_true);

            return status;
          }

          const f_number_unsigned_t id_rule_length = entry_action->parameters.array[0].used + entry_action->parameters.array[1].used + 1;
          f_char_t id_rule_name[id_rule_length + 1];
          const f_string_static_t alias_rule = macro_f_string_static_t_initialize_1(id_rule_name, 0, id_rule_length);

          memcpy(id_rule_name, entry_action->parameters.array[0].string, sizeof(f_char_t) * entry_action->parameters.array[0].used);
          memcpy(id_rule_name + entry_action->parameters.array[0].used + 1, entry_action->parameters.array[1].string, sizeof(f_char_t) * entry_action->parameters.array[1].used);

          id_rule_name[entry_action->parameters.array[0].used] = f_path_separator_s.string[0];
          id_rule_name[id_rule_length] = 0;

          status_lock = controller_lock_read(is_entry, F_true, &main->thread, &main->thread.lock.rule);

          if (F_status_is_error(status_lock)) {
            controller_print_error_lock_critical(&main->program.error, F_status_set_fine(status_lock), F_true);

            break;
          }

          status = controller_rule_find(alias_rule, main->process.rules, 0);

          f_thread_unlock(&main->thread.lock.rule);

          if ((main->setting.flag & controller_main_flag_simulate_e) || main->program.error.verbosity == f_console_verbosity_verbose_e || main->program.error.verbosity == f_console_verbosity_debug_e || (entry->show == controller_entry_show_init_e && entry_action->type != controller_entry_action_type_consider_e)) {
            controller_print_message_entry_item_rule(&main->program.message, entry, entry_action, is_entry, alias_rule);
          }

          if (!controller_thread_is_enabled(&main->thread, is_entry)) break;

          // The Rule is not yet loaded, ensure that it is loaded.
          if (status != F_true) {

            // Rule execution will re-use the existing cache, so save the current cache.
            const f_number_unsigned_t cache_line_action = cache->action.line_action;
            const f_number_unsigned_t cache_line_item = cache->action.line_item;

            const f_number_unsigned_t cache_name_action_used = cache->action.name_action.used;
            const f_number_unsigned_t cache_name_item_used = cache->action.name_item.used;
            const f_number_unsigned_t cache_name_file_used = cache->action.name_file.used;

            f_char_t cache_name_action[cache_name_action_used];
            f_char_t cache_name_item[cache_name_item_used];
            f_char_t cache_name_file[cache_name_file_used];

            memcpy(cache_name_action, cache->action.name_action.string, sizeof(f_char_t) * cache->action.name_action.used);
            memcpy(cache_name_item, cache->action.name_item.string, sizeof(f_char_t) * cache->action.name_item.used);
            memcpy(cache_name_file, cache->action.name_file.string, sizeof(f_char_t) * cache->action.name_file.used);

            status_lock = controller_lock_write(is_entry, F_true, &main->thread, &main->thread.lock.rule);

            if (F_status_is_fine(status_lock)) {
              status = controller_rule_read(main, cache, is_entry, alias_rule, entry, &main->process.rules.array[main->process.rules.used]);
            }

            // Restore cache.
            memcpy(cache->action.name_action.string, cache_name_action, sizeof(f_char_t) * cache_name_action_used);
            memcpy(cache->action.name_item.string, cache_name_item, sizeof(f_char_t) * cache_name_item_used);
            memcpy(cache->action.name_file.string, cache_name_file, sizeof(f_char_t) * cache_name_file_used);

            cache->action.name_action.string[cache_name_action_used] = 0;
            cache->action.name_item.string[cache_name_item_used] = 0;
            cache->action.name_file.string[cache_name_file_used] = 0;

            cache->action.name_action.used = cache_name_action_used;
            cache->action.name_item.used = cache_name_item_used;
            cache->action.name_file.used = cache_name_file_used;

            cache->action.line_action = cache_line_action;
            cache->action.line_item = cache_line_item;

            if (F_status_is_error(status_lock)) {
              controller_print_error_lock_critical(&main->program.error, F_status_set_fine(status_lock), F_false);

              break;
            }

            if (F_status_set_fine(status) == F_interrupt || !controller_thread_is_enabled(&main->thread, is_entry)) {
              f_thread_unlock(&main->thread.lock.rule);

              break;
            }

            if (F_status_is_error(status)) {
              if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
                controller_lock_print(main->program.error.to, &main->thread);

                controller_print_error_entry_cache(&main->program.error, &cache->action, is_entry);

                controller_unlock_print_flush(main->program.error.to, &main->thread);
              }

              // Designate the Action as failed.
              entry_action->status = controller_status_simplify_error(F_failure);

              if (!(main->setting.flag & controller_main_flag_simulate_e)) {
                f_thread_unlock(&main->thread.lock.rule);

                if (entry_action->code & controller_entry_rule_code_require_d) return F_status_set_error(F_require);

                ++cache->ats.array[at_j];

                break;
              }
            }
            else {
              ++main->process.rules.used;
            }

            f_thread_unlock(&main->thread.lock.rule);
          }

          if (F_status_is_error_not(status)) {
            options_force = 0;
            options_instance = 0;

            if (main->setting.flag & controller_main_flag_simulate_e) {
              options_instance |= controller_instance_option_simulate_e;
            }

            if (entry_action->code & controller_entry_rule_code_require_d) {
              options_instance |= controller_instance_option_require_e;
            }

            if (entry_action->code & controller_entry_rule_code_wait_d) {
              options_instance |= controller_instance_option_wait_e;
            }

            if (main->setting.flag & controller_main_flag_validate_e) {
              options_instance |= controller_instance_option_validate_e;
            }

            if (entry_action->code & controller_entry_rule_code_asynchronous_d) {
              if (!(main->setting.flag & controller_main_flag_validate_e)) {
                options_force |= controller_instance_option_asynchronous_e;
              }

              options_instance |= controller_instance_option_asynchronous_e;
            }

            status = controller_rule_instance_begin(main, cache, options_force, alias_rule, controller_entry_action_type_to_rule_action_type(entry_action->type), options_instance, is_entry ? controller_instance_type_entry_e : controller_instance_type_exit_e, stack);
            if (F_status_set_fine(status) == F_memory_not || status == F_child || F_status_set_fine(status) == F_interrupt) break;

            if (F_status_is_error(status) && !(main->setting.flag & controller_main_flag_simulate_e) && (entry_action->code & controller_entry_rule_code_require_d)) {
              return F_status_set_error(F_require);
            }
          }
        }
        else if (entry_action->type == controller_entry_action_type_execute_e) {
          if ((main->setting.flag & controller_main_flag_simulate_e) || main->program.message.verbosity > f_console_verbosity_normal_e || entry->show == controller_entry_show_init_e) {
            controller_print_message_entry_item_executing(&main->program.message, is_entry, &entry_action->parameters);
          }

          if (main->setting.flag & controller_main_flag_simulate_e) return F_execute;

          controller_thread_instance_cancel(main, is_entry, is_entry ? controller_thread_cancel_execute_e : controller_thread_cancel_exit_execute_e);

          int result = 0;
          int option = FL_execute_parameter_option_path_d;

          if (entry->session == controller_entry_session_new_e) {
            option |= FL_execute_parameter_option_session_d;
          }

          status = fll_execute_into(f_string_empty_s, entry_action->parameters, option, 0, (void *) &result);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_file_found_not) {
              controller_print_error_entry_action_execution_missing(&main->program.error, &cache->action, is_entry, entry_action->parameters.array[0]);
            }
            else {
              controller_print_error_entry(&main->program.error, is_entry, F_status_set_fine(status), macro_controller_f(fll_execute_into), F_true);
            }

            return F_status_set_error(F_execute);
          }
          else if (result != 0) {
            controller_print_error_entry_action_execution_failure(&main->program.error, &cache->action, is_entry, result);

            return F_status_set_error(F_execute);
          }

          return F_execute;
        }
        else if (entry_action->type == controller_entry_action_type_timeout_e) {
          if (entry_action->code == controller_entry_timeout_code_exit_d) {
            entry->timeout_exit = entry_action->number;

            controller_print_output_entry_setting_simulate_value(&main->program.output, is_entry, controller_timeout_s, controller_exit_s, entry->items.array[main->process.failsafe_item_id].name, controller_print_entry_suffix_megatime_s);
          }
          else if (entry_action->code == controller_entry_timeout_code_kill_d) {
            entry->timeout_kill = entry_action->number;

            controller_print_output_entry_setting_simulate_value(&main->program.output, is_entry, controller_timeout_s, controller_kill_s, entry->items.array[main->process.failsafe_item_id].name, controller_print_entry_suffix_megatime_s);
          }
          else if (entry_action->code == controller_entry_timeout_code_start_d) {
            entry->timeout_start = entry_action->number;

            controller_print_output_entry_setting_simulate_value(&main->program.output, is_entry, controller_timeout_s, controller_start_s, entry->items.array[main->process.failsafe_item_id].name, controller_print_entry_suffix_megatime_s);
          }
          else if (entry_action->code == controller_entry_timeout_code_stop_d) {
            entry->timeout_stop = entry_action->number;

            controller_print_output_entry_setting_simulate_value(&main->program.output, is_entry, controller_timeout_s, controller_stop_s, entry->items.array[main->process.failsafe_item_id].name, controller_print_entry_suffix_megatime_s);
          }
        }
        else if (entry_action->type == controller_entry_action_type_failsafe_e) {
          if (failsafe) {
            controller_print_warning_entry_action_failsafe_twice(&main->program.warning, cache, is_entry);
          }
          else {
            if (entry_action->number == 0 || entry_action->number >= entry->items.used) {

              // This should not happen if the pre-process is working as designed, but in case it doesn't, return a critical error to prevent infinite recursion and similar errors.
              controller_print_error_entry_item_invalid(&main->program.error, cache, is_entry, entry_action->number);

              return F_status_is_error(F_critical);
            }
            else {
              main->process.flag |= controller_process_flag_failsafe_e;
              main->process.failsafe_item_id = entry_action->number;

              controller_print_output_entry_setting_simulate_value(&main->program.output, is_entry, controller_failsafe_s, f_string_empty_s, entry->items.array[main->process.failsafe_item_id].name, f_string_empty_s);
            }
          }
        }
      } // for

      if (status == F_child || F_status_set_fine(status) == F_interrupt) break;

      cache->action.line_action = 0;
      cache->action.name_action.used = 0;

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_memory_not || F_status_set_fine(status) == F_require) break;
      }

      // End of actions found, so drop to previous loop in stack.
      if (cache->ats.array[at_j] == entry_actions->used) {

        // All actions for "main" are processed so there is nothing left to do.
        if (at_i == 0) break;

        at_i -= 2;
        at_j -= 2;

        cache->ats.used -= 2;
        ++cache->ats.array[at_j];

        cache->action.line_item = entry->items.array[cache->ats.array[at_i]].line;
        cache->action.name_item.used = 0;

        status = f_string_dynamic_append_nulless(entry->items.array[cache->ats.array[at_i]].name, &cache->action.name_item);

        if (F_status_is_error(status)) {
          controller_print_error_entry(&main->program.error, is_entry, F_status_set_fine(status), macro_controller_f(f_string_dynamic_append_nulless), F_true);

          break;
        }
      }
    } // while

    if (!controller_thread_is_enabled(&main->thread, is_entry)) return F_status_set_error(F_interrupt);
    if (status == F_child) return status;
    if (F_status_is_error(status_lock)) return status_lock;

    // Check to see if any required processes failed, but do not do this if already operating in failsafe.
    if (F_status_is_error_not(status) && !failsafe && !(main->setting.flag & controller_main_flag_validate_e) && main->process.mode != controller_process_mode_helper_e) {
      const f_status_t status_wait = controller_rule_wait_all(main, is_entry, F_true);
      if (F_status_is_error(status_wait)) return status_wait;
      if (status_wait == F_require) return F_status_set_error(F_require);
    }

    if (((main->setting.flag & controller_main_flag_simulate_e) && main->program.error.verbosity > f_console_verbosity_error_e) || main->program.error.verbosity > f_console_verbosity_normal_e) {
      controller_print_message_entry_item_done(&main->program.message, is_entry, failsafe, controller_main_s);
    }

    return status;
  }
#endif // _di_controller_entry_process_

#ifdef __cplusplus
} // extern "C"
#endif
