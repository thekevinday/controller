#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_entry_process_
  f_status_t controller_entry_process(controller_t * const main, const bool failsafe, const uint8_t is_entry) {

    f_status_t status = F_okay;
    f_status_t status_lock = F_okay;

    f_number_unsigned_t at_i = 0;
    f_number_unsigned_t at_j = 1;

    uint8_t options_force = 0;
    uint8_t options_process = 0;

    controller_entry_t * const entry = is_entry ? &main->process.entry : &main->process.exit;
    controller_cache_t * const cache = &main->thread.cache;
    controller_entry_action_t *entry_action = 0;
    controller_entry_actions_t *entry_actions = 0;

    // An empty stack is used here because each rule here is the first rule run in the rule's scope.
    const f_number_unsigneds_t stack = f_number_unsigneds_t_initialize;

    cache->ats.used = 0;
    cache->stack.used = 0;

    cache->action.line_action = 0;
    cache->action.line_item = 0;
    cache->action.name_action.used = 0;
    cache->action.name_item.used = 0;

    status = f_memory_array_increase(controller_common_allocation_small_d, sizeof(f_number_unsigned_t), (void **) &cache->ats.array, &cache->ats.used, &cache->ats.size);

    if (F_status_is_error(status)) {
      controller_entry_print_error(is_entry, &main->program.error, cache->action, F_status_set_fine(status), macro_controller_f(f_memory_array_increase), F_true, &main->thread);

      return status;
    }

    // utilize the ats cache as an item execution stack (at_i is for item index, and at_j (at_i + 1) is for action index).
    cache->ats.array[0] = failsafe ? main->setting.failsafe_item_id : 0;
    cache->ats.array[1] = 0;
    cache->ats.used = 2;

    cache->action.line_item = entry->items.array[cache->ats.array[0]].line;
    cache->action.name_item.used = 0;

    status = f_string_dynamic_append_nulless(entry->items.array[cache->ats.array[0]].name, &cache->action.name_item);

    if (F_status_is_error(status)) {
      controller_entry_print_error(is_entry, &main->program.error, cache->action, F_status_set_fine(status), macro_controller_f(f_string_dynamic_append_nulless), F_true, &main->thread);

      return status;
    }

    if ((main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e) || main->program.error.verbosity == f_console_verbosity_verbose_e || main->program.error.verbosity == f_console_verbosity_debug_e) {
      if ((main->program.error.verbosity > f_console_verbosity_error_e)) {
        controller_lock_print(main->program.output.to, &main->thread);

        fl_print_format("%rProcessing %r%r item '", main->program.output.to, f_string_eol_s, failsafe ? controller_entry_print_failsafe_s : f_string_empty_s, is_entry ? controller_entry_s : controller_exit_s);
        fl_print_format("%[%Q%]'.%r", main->program.output.to, main->program.context.set.title, cache->action.name_item, main->program.context.set.notable, f_string_eol_s);

        controller_unlock_print_flush(main->program.output.to, &main->thread);
      }
    }

    // The pre-process determines if ready is explicitly specified within the entry file and if it is not start as ready.
    if (main->setting.ready == controller_setting_ready_yes_e) {
      status = controller_perform_ready(main, is_entry);
      if (F_status_is_error(status)) return status;
    }

    while (controller_thread_is_enabled(is_entry, &main->thread)) {

      entry_actions = &entry->items.array[cache->ats.array[at_i]].actions;

      for (; cache->ats.array[at_j] < entry_actions->used && controller_thread_is_enabled(is_entry, &main->thread); ++cache->ats.array[at_j]) {

        entry_action = &entry_actions->array[cache->ats.array[at_j]];

        cache->action.line_action = entry_action->line;
        cache->action.name_action.used = 0;

        status = f_string_dynamic_append_nulless(controller_entry_action_type_name(entry_action->type), &cache->action.name_action);

        if (F_status_is_error(status)) {
          controller_entry_print_error(is_entry, &main->program.error, cache->action, F_status_set_fine(status), macro_controller_f(f_string_dynamic_append_nulless), F_true, &main->thread);

          return status;
        }

        if (F_status_is_error(entry_action->status)) {
          if (main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e) {
            if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
              controller_lock_print(main->program.output.to, &main->thread);

              fl_print_format("%rThe %r item action '", main->program.output.to, f_string_eol_s, is_entry ? controller_entry_s : controller_exit_s);
              fl_print_format(f_string_format_Q_single_s.string, main->program.output.to, main->program.context.set.title, cache->action.name_action, main->program.context.set.title);

              if (entry_action->parameters.used) {
                fl_print_format(" %[", main->program.output.to, main->program.context.set.notable);

                controller_entry_action_parameters_print(&main->program.output, *entry_action);

                fl_print_format("%]", main->program.output.to, main->program.context.set.notable);
              }

              fl_print_format("' is %[%r%] and is in a ", main->program.output.to, main->program.context.set.notable, entry_action->code & controller_entry_rule_code_require_d ? "required" : "optional", main->program.context.set.notable);

              fl_print_format("%[failed%] state, skipping.%r", main->program.output.to, main->program.context.set.notable, main->program.context.set.notable, main->program.context.set.notable, f_string_eol_s);

              controller_unlock_print_flush(main->program.output.to, &main->thread);
            }
          }
          else {
            if ((entry_action->code & controller_entry_rule_code_require_d) && main->program.error.verbosity > f_console_verbosity_quiet_e || !(entry_action->code & controller_entry_rule_code_require_d) && (main->program.warning.verbosity == f_console_verbosity_verbose_e || main->program.warning.verbosity == f_console_verbosity_debug_e)) {
              fl_print_t *print = 0;

              if (entry_action->code & controller_entry_rule_code_require_d) {
                print = &main->program.error;
              }
              else if (main->program.error.verbosity != f_console_verbosity_error_e) {
                print = &main->program.warning;
              }

              if (print) {
                controller_lock_print(print->to, &main->thread);

                fl_print_format("%r%[%QThe %r item action '%]", print->to, f_string_eol_s, print->context, print->prefix, is_entry ? controller_entry_s : controller_exit_s, print->context);
                fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, cache->action.name_action, print->notable);


                if (entry_action->parameters.used) {
                  fl_print_format(" %[", print->to, main->program.context.set.notable);

                  controller_entry_action_parameters_print(print, *entry_action);

                  fl_print_format("%]", print->to, main->program.context.set.notable);
                }

                if (entry_action->code & controller_entry_rule_code_require_d) {
                  fl_print_format("%[' is%] %[required%]", print->to, print->context, print->context, print->notable, print->notable);
                }
                else {
                  fl_print_format("%[' is%] %[optional%]", print->to, print->context, print->context, print->notable, print->notable);
                }

                fl_print_format(" %[and is in a%] %[failed%]", print->to, print->context, print->context, print->notable, print->notable);

                if (entry_action->code & controller_entry_rule_code_require_d) {
                  fl_print_format(" %[state, aborting.%]%r", print->to, print->context, print->context, f_string_eol_s);
                }
                else {
                  fl_print_format(" %[state, skipping.%]%r", print->to, print->context, print->context, f_string_eol_s);
                }

                controller_entry_print_error_cache(is_entry, print, cache->action);

                controller_unlock_print_flush(print->to, &main->thread);
              }
            }

            if (controller_entry_action_type_is_rule(entry_action->type) && entry_action->code & controller_entry_rule_code_require_d) {
              return F_status_is_error(F_require);
            }
          }

          continue;
        }

        if (entry_action->type == controller_entry_action_type_ready_e) {
          if ((entry_action->code & controller_entry_rule_code_wait_d) || main->setting.ready == controller_setting_ready_wait_e) {
            if ((main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e) || main->program.error.verbosity == f_console_verbosity_verbose_e || main->program.error.verbosity == f_console_verbosity_debug_e || entry->show == controller_entry_show_init_e) {
              if (main->program.output.verbosity != f_console_verbosity_quiet_e && main->program.error.verbosity != f_console_verbosity_error_e) {
                controller_lock_print(main->program.output.to, &main->thread);

                fl_print_format("%rWaiting before processing %r item action '", main->program.output.to, f_string_eol_s, is_entry ? controller_entry_s : controller_exit_s);
                fl_print_format(f_string_format_r_single_s.string, main->program.output.to, main->program.context.set.title, controller_ready_s, main->program.context.set.title);
                fl_print_format("'.%r", main->program.output.to, f_string_eol_s);

                controller_unlock_print_flush(main->program.output.to, &main->thread);
              }
            }

            if (!(main->program.parameters.array[controller_parameter_validate_e].result & f_console_result_found_e)) {
              status = controller_rule_wait_all(main, is_entry, F_false);
              if (F_status_is_error(status)) return status;
            }
          }

          if (main->setting.ready == controller_setting_ready_yes_e) {
            if ((main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e) || main->program.error.verbosity == f_console_verbosity_verbose_e || main->program.error.verbosity == f_console_verbosity_debug_e) {
              if (main->program.output.verbosity != f_console_verbosity_quiet_e && main->program.error.verbosity != f_console_verbosity_error_e) {
                controller_lock_print(main->program.output.to, &main->thread);

                fl_print_format("%rIgnoring %r item action '", main->program.output.to, f_string_eol_s, is_entry ? controller_entry_s : controller_exit_s);
                fl_print_format(f_string_format_r_single_s.string, main->program.output.to, main->program.context.set.title, controller_ready_s, main->program.context.set.title);
                fl_print_format("', state already is ready.%r", main->program.output.to, f_string_eol_s);

                controller_unlock_print_flush(main->program.output.to, &main->thread);
              }
            }
          }
          else {
            if (!failsafe && (main->program.error.verbosity == f_console_verbosity_verbose_e || entry->show == controller_entry_show_init_e) && !(main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e)) {
              if (main->program.error.verbosity > f_console_verbosity_error_e) {
                fl_print_format("%rState is now '%[%r%]'.%r", main->program.output.to, f_string_eol_s, main->program.context.set.notable, controller_ready_s, main->program.context.set.notable, f_string_eol_s);
              }
            }

            status = controller_perform_ready(main, is_entry);
            if (F_status_is_error(status)) return status;
          }
        }
        else if (entry_action->type == controller_entry_action_type_item_e) {
          if (entry_action->number == 0 || entry_action->number >= entry->items.used || failsafe && entry_action->number == main->setting.failsafe_item_id) {

            // This should not happen if the pre-process is working as intended, but in case it doesn't, return a critical error to prevent infinite recursion and similar errors.
            if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
              controller_lock_print(main->program.error.to, &main->thread);

              fl_print_format("%r%[Invalid %r item index '%]", main->program.error.to, f_string_eol_s, main->program.error.context, is_entry ? controller_entry_s : controller_exit_s, main->program.error.context);
              fl_print_format("%[%un%]", main->program.error.to, main->program.error.notable, entry_action->number, main->program.error.notable);
              fl_print_format("%[' detected.%]%r", main->program.error.to, main->program.error.context, main->program.error.context, f_string_eol_s);

              controller_entry_print_error_cache(is_entry, &main->program.error, cache->action);

              controller_unlock_print_flush(main->program.error.to, &main->thread);
            }

            return F_status_is_error(F_critical);
          }

          status = f_memory_array_increase(controller_common_allocation_small_d, sizeof(f_number_unsigned_t), (void **) &cache->ats.array, &cache->ats.used, &cache->ats.size);

          if (F_status_is_error(status)) {
            controller_entry_print_error(is_entry, &main->program.error, cache->action, F_status_set_fine(status), macro_controller_f(f_memory_array_increase), F_true, &main->thread);

            return status;
          }

          // continue into the requested item.
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
            controller_entry_print_error(is_entry, &main->program.error, cache->action, F_status_set_fine(status), macro_controller_f(f_string_dynamic_append_nulless), F_true, &main->thread);

            return status;
          }

          if ((main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e) || main->program.error.verbosity == f_console_verbosity_verbose_e || main->program.error.verbosity == f_console_verbosity_debug_e) {
            if (main->program.output.verbosity != f_console_verbosity_quiet_e && main->program.error.verbosity != f_console_verbosity_error_e) {
              controller_lock_print(main->program.output.to, &main->thread);

              fl_print_format("%rProcessing %r item '", main->program.output.to, f_string_eol_s, is_entry ? controller_entry_s : controller_exit_s);
              fl_print_format(f_string_format_Q_single_s.string, main->program.output.to, main->program.context.set.title, cache->action.name_item, main->program.context.set.title);
              fl_print_format("'.%r", main->program.output.to, f_string_eol_s);

              controller_unlock_print_flush(main->program.output.to, &main->thread);
            }
          }

          // Exit inner loop to force restarting and start processing the requested item.
          break;
        }
        else if (entry_action->type == controller_entry_action_type_consider_e || controller_entry_action_type_is_rule(entry_action->type)) {
          status_lock = controller_lock_write(is_entry, &main->thread, &main->thread.lock.rule);

          if (F_status_is_error(status_lock)) {
            controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status_lock), F_false, &main->thread);

            break;
          }

          status = controller_rules_increase(&main->setting.rules);

          f_thread_unlock(&main->thread.lock.rule);

          if (F_status_is_error(status)) {
            controller_entry_print_error(is_entry, &main->program.error, cache->action, F_status_set_fine(status), macro_controller_f(controller_rules_increase), F_true, &main->thread);

            return status;
          }

          const f_number_unsigned_t id_rule_length = entry_action->parameters.array[0].used + entry_action->parameters.array[1].used + 1;
          f_char_t id_rule_name[id_rule_length + 1];
          const f_string_static_t alias_rule = macro_f_string_static_t_initialize_1(id_rule_name, 0, id_rule_length);

          memcpy(id_rule_name, entry_action->parameters.array[0].string, sizeof(f_char_t) * entry_action->parameters.array[0].used);
          memcpy(id_rule_name + entry_action->parameters.array[0].used + 1, entry_action->parameters.array[1].string, sizeof(f_char_t) * entry_action->parameters.array[1].used);

          id_rule_name[entry_action->parameters.array[0].used] = f_path_separator_s.string[0];
          id_rule_name[id_rule_length] = 0;

          status_lock = controller_lock_read(is_entry, &main->thread, &main->thread.lock.rule);

          if (F_status_is_error(status_lock)) {
            controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status_lock), F_true, &main->thread);

            break;
          }

          status = controller_rule_find(alias_rule, main->setting.rules, 0);

          f_thread_unlock(&main->thread.lock.rule);

          if ((main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e) || main->program.error.verbosity == f_console_verbosity_verbose_e || main->program.error.verbosity == f_console_verbosity_debug_e || (entry->show == controller_entry_show_init_e && entry_action->type != controller_entry_action_type_consider_e)) {
            if (main->program.output.verbosity != f_console_verbosity_quiet_e && main->program.error.verbosity != f_console_verbosity_error_e) {
              controller_lock_print(main->program.output.to, &main->thread);

              fl_print_format("%r%r %r item rule ", main->program.output.to, f_string_eol_s, entry_action->type == controller_entry_action_type_consider_e ? controller_entry_print_considering_s : controller_entry_print_processing_s, is_entry ? controller_entry_s : controller_exit_s);
              fl_print_format("'%[%Q%]'", main->program.output.to, main->program.context.set.title, alias_rule, main->program.context.set.title);

              if (entry->show == controller_entry_show_init_e && !(main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e)) {
                fl_print_format(" [%[%r%]]", main->program.output.to, main->program.context.set.notable, entry_action->code == controller_entry_rule_code_asynchronous_d ? controller_asynchronous_s : controller_synchronous_s, main->program.context.set.notable);

                if (entry_action->code == controller_entry_rule_code_wait_d) {
                  fl_print_format(" [%[%r%]]", main->program.output.to, main->program.context.set.notable, controller_wait_s, main->program.context.set.notable);
                }

                if (entry_action->code == controller_entry_rule_code_require_d) {
                  fl_print_format(" [%[%r%]]", main->program.output.to, main->program.context.set.notable, controller_required_s, main->program.context.set.notable);
                }
              }

              fl_print_format(".%r", main->program.output.to, f_string_eol_s);

              controller_unlock_print_flush(main->program.output.to, &main->thread);
            }
          }

          if (!controller_thread_is_enabled(is_entry, &main->thread)) break;

          // The rule is not yet loaded, ensure that it is loaded.
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

            status_lock = controller_lock_write(is_entry, &main->thread, &main->thread.lock.rule);

            if (F_status_is_fine(status_lock)) {
              status = controller_rule_read(main, is_entry, alias_rule, cache, entry, &main->setting.rules.array[main->setting.rules.used]);
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
              controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status_lock), F_false, &main->thread);

              break;
            }

            if (F_status_set_fine(status) == F_interrupt || !controller_thread_is_enabled(is_entry, &main->thread)) {
              f_thread_unlock(&main->thread.lock.rule);

              break;
            }

            if (F_status_is_error(status)) {
              if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
                controller_lock_print(main->program.error.to, &main->thread);

                controller_entry_print_error_cache(is_entry, &main->program.error, cache->action);

                controller_unlock_print_flush(main->program.error.to, &main->thread);
              }

              // Designate the action as failed.
              entry_action->status = F_status_set_error(F_failure);

              if (!(main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e)) {
                f_thread_unlock(&main->thread.lock.rule);

                if (entry_action->code & controller_entry_rule_code_require_d) {
                  return F_status_set_error(F_require);
                }

                ++cache->ats.array[at_j];

                break;
              }
            }
            else {
              ++main->setting.rules.used;
            }

            f_thread_unlock(&main->thread.lock.rule);
          }

          if (F_status_is_error_not(status)) {
            options_force = 0;
            options_process = 0;

            if (main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e) {
              options_process |= controller_process_option_simulate_d;
            }

            if (entry_action->code & controller_entry_rule_code_require_d) {
              options_process |= controller_process_option_require_d;
            }

            if (entry_action->code & controller_entry_rule_code_wait_d) {
              options_process |= controller_process_option_wait_d;
            }

            if (main->program.parameters.array[controller_parameter_validate_e].result & f_console_result_found_e) {
              options_process |= controller_process_option_validate_d;
            }

            if (entry_action->code & controller_entry_rule_code_asynchronous_d) {
              if (!(main->program.parameters.array[controller_parameter_validate_e].result & f_console_result_found_e)) {
                options_force |= controller_process_option_asynchronous_d;
              }

              options_process |= controller_process_option_asynchronous_d;
            }

            status = controller_rule_process_begin(main, options_force, alias_rule, controller_entry_action_type_to_rule_action_type(entry_action->type), options_process, is_entry ? controller_data_type_entry_e : controller_data_type_exit_e, stack, *cache);

            if (F_status_set_fine(status) == F_memory_not || status == F_child || F_status_set_fine(status) == F_interrupt) {
              break;
            }

            if (F_status_is_error(status) && !(main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e) && (entry_action->code & controller_entry_rule_code_require_d)) {
              return F_status_set_error(F_require);
            }
          }
        }
        else if (entry_action->type == controller_entry_action_type_execute_e) {
          if ((main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e) || main->program.error.verbosity == f_console_verbosity_verbose_e || main->program.error.verbosity == f_console_verbosity_debug_e || entry->show == controller_entry_show_init_e) {
            if (main->program.output.verbosity != f_console_verbosity_quiet_e && main->program.error.verbosity != f_console_verbosity_error_e) {
              controller_lock_print(main->program.output.to, &main->thread);

              fl_print_format("%r%Q is executing '", main->program.output.to, f_string_eol_s, is_entry ? controller_entry_s : controller_exit_s);

              for (f_number_unsigned_t k = 0; k < entry_action->parameters.used; ++k) {

                fl_print_format(f_string_format_Q_single_s.string, main->program.output.to, main->program.context.set.title, entry_action->parameters.array[k], main->program.context.set.title);

                if (k + 1 < entry_action->parameters.used) {
                  f_print_dynamic_raw(f_string_space_s, main->program.output.to);
                }
              } // for

              fl_print_format("'.%r", main->program.output.to, f_string_eol_s);

              controller_unlock_print_flush(main->program.output.to, &main->thread);
            }
          }

          if (main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e) return F_execute;

          controller_thread_process_cancel(main, is_entry, is_entry ? controller_thread_cancel_execute_e : controller_thread_cancel_exit_execute_e);

          int result = 0;
          int option = FL_execute_parameter_option_path_d;

          if (entry->session == controller_entry_session_new_e) {
            option |= FL_execute_parameter_option_session_d;
          }

          status = fll_execute_into(f_string_empty_s, entry_action->parameters, option, 0, (void *) &result);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_file_found_not) {
              if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
                controller_lock_print(main->program.error.to, &main->thread);

                fl_print_format("%r%[%QExecution failed, unable to find program or script '%]", main->program.error.to, f_string_eol_s, main->program.error.context, main->program.error.prefix, main->program.error.context);
                fl_print_format(f_string_format_Q_single_s.string, main->program.error.to, main->program.error.notable, entry_action->parameters.array[0], main->program.error.notable);
                fl_print_format(f_string_format_sentence_end_quote_s.string, main->program.error.to, main->program.error.context, main->program.error.context, f_string_eol_s);

                controller_entry_print_error_cache(is_entry, &main->program.error, cache->action);

                controller_unlock_print_flush(main->program.error.to, &main->thread);
              }
            }
            else {
              controller_entry_print_error(is_entry, &main->program.error, cache->action, F_status_set_fine(status), macro_controller_f(fll_execute_into), F_true, &main->thread);
            }

            return F_status_set_error(F_execute);
          }
          else if (result != 0) {
            if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
              controller_lock_print(main->program.error.to, &main->thread);

              fl_print_format("%r%[%QExecution failed with return value of '%]", main->program.error.to, f_string_eol_s, main->program.error.context, main->program.error.prefix, main->program.error.context);
              fl_print_format("%[%i%]", main->program.error.to, main->program.error.notable, result, main->program.error.notable);
              fl_print_format("$['.%]%r", main->program.error.to, main->program.error.context, main->program.error.context, f_string_eol_s);

              controller_entry_print_error_cache(is_entry, &main->program.error, cache->action);

              controller_unlock_print_flush(main->program.error.to, &main->thread);
            }

            return F_status_set_error(F_execute);
          }

          return F_execute;
        }
        else if (entry_action->type == controller_entry_action_type_timeout_e) {
          if (entry_action->code == controller_entry_timeout_code_exit_d) {
            entry->timeout_exit = entry_action->number;

            controller_entry_preprocess_print_simulate_setting_value(main, is_entry, controller_timeout_s, controller_exit_s, entry->items.array[main->setting.failsafe_item_id].name, controller_entry_print_suffix_megatime_s);
          }
          else if (entry_action->code == controller_entry_timeout_code_kill_d) {
            entry->timeout_kill = entry_action->number;

            controller_entry_preprocess_print_simulate_setting_value(main, is_entry, controller_timeout_s, controller_kill_s, entry->items.array[main->setting.failsafe_item_id].name, controller_entry_print_suffix_megatime_s);
          }
          else if (entry_action->code == controller_entry_timeout_code_start_d) {
            entry->timeout_start = entry_action->number;

            controller_entry_preprocess_print_simulate_setting_value(main, is_entry, controller_timeout_s, controller_start_s, entry->items.array[main->setting.failsafe_item_id].name, controller_entry_print_suffix_megatime_s);
          }
          else if (entry_action->code == controller_entry_timeout_code_stop_d) {
            entry->timeout_stop = entry_action->number;

            controller_entry_preprocess_print_simulate_setting_value(main, is_entry, controller_timeout_s, controller_stop_s, entry->items.array[main->setting.failsafe_item_id].name, controller_entry_print_suffix_megatime_s);
          }
        }
        else if (entry_action->type == controller_entry_action_type_failsafe_e) {

          if (failsafe) {
            if (main->program.warning.verbosity == f_console_verbosity_debug_e) {
              controller_lock_print(main->program.warning.to, &main->thread);

              fl_print_format("%r%[%QFailsafe may not be specified when running in failsafe, ignoring.%]%r", main->program.warning.to, f_string_eol_s, main->program.warning.context, main->program.warning.prefix, main->program.warning.context, f_string_eol_s);

              controller_entry_print_error_cache(is_entry, &main->program.warning, cache->action);

              controller_unlock_print_flush(main->program.warning.to, &main->thread);
            }
          }
          else {
            if (entry_action->number == 0 || entry_action->number >= entry->items.used) {

              // This should not happen if the pre-process is working as designed, but in case it doesn't, return a critical error to prevent infinite recursion and similar errors.
              if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
                controller_lock_print(main->program.error.to, &main->thread);

                fl_print_format("%r%[%QInvalid %r item index '%]", main->program.error.to, f_string_eol_s, main->program.error.context, main->program.error.prefix, is_entry ? controller_entry_s : controller_exit_s, main->program.error.context);
                fl_print_format("%[%un%]", main->program.error.to, main->program.error.notable, entry_action->number, main->program.error.notable);
                fl_print_format("%[' detected.%]%r", main->program.error.to, main->program.error.context, main->program.error.context, f_string_eol_s);

                controller_entry_print_error_cache(is_entry, &main->program.error, cache->action);

                controller_unlock_print_flush(main->program.error.to, &main->thread);
              }

              return F_status_is_error(F_critical);
            }
            else {
              main->setting.flag |= controller_setting_flag_failsafe_e;
              main->setting.failsafe_item_id = entry_action->number;

              controller_entry_preprocess_print_simulate_setting_value(main, is_entry, controller_failsafe_s, f_string_empty_s, entry->items.array[main->setting.failsafe_item_id].name, f_string_empty_s);
            }
          }
        }
      } // for

      if (status == F_child || F_status_set_fine(status) == F_interrupt) break;

      cache->action.line_action = 0;
      cache->action.name_action.used = 0;

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_memory_not || F_status_set_fine(status) == F_require) {
          break;
        }
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
          controller_entry_print_error(is_entry, &main->program.error, cache->action, F_status_set_fine(status), macro_controller_f(f_string_dynamic_append_nulless), F_true, &main->thread);

          break;
        }
      }
    } // while

    if (!controller_thread_is_enabled(is_entry, &main->thread)) {
      return F_status_set_error(F_interrupt);
    }

    if (status == F_child) {
      return status;
    }

    if (F_status_is_error(status_lock)) {
      return status_lock;
    }

    // Check to see if any required processes failed, but do not do this if already operating in failsafe.
    if (F_status_is_error_not(status) && !failsafe && !(main->program.parameters.array[controller_parameter_validate_e].result & f_console_result_found_e) && main->setting.mode != controller_setting_mode_helper_e) {
      const f_status_t status_wait = controller_rule_wait_all(main, is_entry, F_true);
      if (F_status_is_error(status_wait)) return status_wait;
      if (status_wait == F_require) return F_status_set_error(F_require);
    }

    if (((main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e) && main->program.error.verbosity > f_console_verbosity_quiet_e) && main->program.error.verbosity != f_console_verbosity_error_e || main->program.error.verbosity == f_console_verbosity_verbose_e) {
      controller_lock_print(main->program.output.to, &main->thread);

      fl_print_format("%rDone processing %r item '", main->program.output.to, f_string_eol_s, is_entry ? controller_entry_s : controller_exit_s);
      fl_print_format(f_string_format_r_single_s.string, main->program.output.to, main->program.context.set.title, controller_main_s, main->program.context.set.title);
      fl_print_format("'.%r", main->program.output.to, f_string_eol_s);

      // failsafe should not print the extra newline because the failure exit from controller_main should handle this.
      if (!failsafe) {
        f_print_dynamic_raw(f_string_eol_s, main->program.output.to);
      }

      controller_unlock_print_flush(main->program.output.to, &main->thread);
    }

    return status;
  }
#endif // _di_controller_entry_process_

#ifdef __cplusplus
} // extern "C"
#endif
