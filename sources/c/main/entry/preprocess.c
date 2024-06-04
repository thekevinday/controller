#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_entry_preprocess_
  f_status_t controller_entry_preprocess(controller_t * const main, const uint8_t is_entry) {

    f_status_t status = F_okay;
    f_status_t status2 = F_okay;

    f_number_unsigned_t i = 0;
    f_number_unsigned_t j = 0;

    f_number_unsigned_t at_i = 0;
    f_number_unsigned_t at_j = 1;

    controller_entry_t * const entry = is_entry ? &main->process.entry : &main->process.exit;
    controller_cache_t * const cache = &main->thread.cache;
    controller_entry_actions_t *actions = 0;

    uint8_t error_has = F_false;

    // This effectively sets the read for an entry and resets the ready for an exit.
    main->setting.ready = controller_setting_ready_no_e;

    cache->ats.used = 0;

    cache->action.line_action = 0;
    cache->action.line_item = 0;
    cache->action.name_action.used = 0;
    cache->action.name_item.used = 0;

    status = f_memory_array_increase(controller_common_allocation_small_d, sizeof(f_number_unsigned_t), (void **) &cache->ats.array, &cache->ats.used, &cache->ats.size);

    if (F_status_is_error(status)) {
      controller_entry_print_error(&main->program.error, cache->action, is_entry, F_status_set_fine(status), macro_controller_f(f_memory_array_increase), F_true);

      return status;
    }

    // Utilize the ats cache as an item execution stack (at_i is for item index, and at_j (at_i + 1) is for action index).
    cache->ats.array[0] = 0;
    cache->ats.array[1] = 0;
    cache->ats.used = 2;

    cache->action.line_item = entry->items.array[0].line;
    cache->action.name_item.used = 0;

    status = f_string_dynamic_append_nulless(entry->items.array[0].name, &cache->action.name_item);

    if (F_status_is_error(status)) {
      controller_entry_print_error(&main->program.error, cache->action, is_entry, F_status_set_fine(status), macro_controller_f(f_string_dynamic_append_nulless), F_true);

      return status;
    }

    while (controller_thread_is_enabled(is_entry, &main->thread)) {

      actions = &entry->items.array[cache->ats.array[at_i]].actions;

      for (; cache->ats.array[at_j] < actions->used && controller_thread_is_enabled(is_entry, &main->thread); ++cache->ats.array[at_j]) {

        cache->action.line_action = actions->array[cache->ats.array[at_j]].line;
        cache->action.name_action.used = 0;

        status2 = f_string_dynamic_append_nulless(controller_entry_action_type_name(actions->array[cache->ats.array[at_j]].type), &cache->action.name_action);

        if (F_status_is_error(status2)) {
          controller_entry_print_error(&main->program.error, cache->action, is_entry, F_status_set_fine(status2), macro_controller_f(f_string_dynamic_append_nulless), F_true);

          return status2;
        }

        if (actions->array[cache->ats.array[at_j]].type == controller_entry_action_type_ready_e) {

          if (main->setting.ready == controller_setting_ready_wait_e) {
            if (main->program.warning.verbosity == f_console_verbosity_debug_e) {
              controller_lock_print(main->program.warning.to, &main->thread);

              fl_print_format("%r%[%QMultiple '%]", main->program.warning.to, f_string_eol_s, main->program.warning.context, main->program.warning.prefix, main->program.warning.context);
              fl_print_format(f_string_format_r_single_s.string, main->program.warning.to, main->program.warning.notable, controller_ready_s, main->program.warning.notable);
              fl_print_format("%[' %r item actions detected; only the first will be used.%]%r", main->program.warning.to, main->program.warning.context, is_entry ? controller_entry_s : controller_exit_s, main->program.warning.context, f_string_eol_s);

              controller_entry_print_error_cache(is_entry, &main->program.warning, cache->action);

              controller_unlock_print_flush(main->program.warning.to, &main->thread);
            }
          }
          else {
            main->setting.ready = controller_setting_ready_wait_e;
          }
        }
        else if (actions->array[cache->ats.array[at_j]].type == controller_entry_action_type_item_e) {
          error_has = F_false;

          // "main" is not allowed to be used for an "item" and "setting" is not an executable "item".
          if (f_compare_dynamic(controller_main_s, actions->array[cache->ats.array[at_j]].parameters.array[0]) == F_equal_to) {
            continue;
          }
          else if (f_compare_dynamic(controller_settings_s, actions->array[cache->ats.array[at_j]].parameters.array[0]) == F_equal_to) {
            continue;
          }

          // Walk though each items and check to see if the item actually exists.
          for (i = 1; i < entry->items.used && controller_thread_is_enabled(is_entry, &main->thread); ++i) {

            if (f_compare_dynamic(entry->items.array[i].name, actions->array[cache->ats.array[at_j]].parameters.array[0]) == F_equal_to) {

              // Check to see if "i" is already in the stack (to prevent recursion) (skipping main).
              for (j = 2; j < cache->ats.used; j += 2) {

                if (cache->ats.array[j] == i) {
                  if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
                    controller_lock_print(main->program.error.to, &main->thread);

                    fl_print_format("%r%[%QThe %r item named '%]", main->program.error.to, f_string_eol_s, main->program.error.context, is_entry ? controller_entry_s : controller_exit_s, main->program.error.prefix, main->program.error.context);
                    fl_print_format(f_string_format_Q_single_s.string, main->program.error.to, main->program.error.notable, entry->items.array[i].name, main->program.error.notable);
                    fl_print_format("%[' cannot be executed because recursion is not allowed.%]%r", main->program.error.to, main->program.error.context, main->program.error.context, f_string_eol_s);

                    controller_entry_print_error_cache(is_entry, &main->program.error, cache->action);

                    controller_unlock_print_flush(main->program.error.to, &main->thread);
                  }

                  if (F_status_is_error_not(status)) {
                    status = F_status_set_error(F_recurse);
                  }

                  error_has = F_true;

                  break;
                }
              } // for

              if (error_has) break;

              status2 = f_memory_array_increase(controller_common_allocation_small_d, sizeof(f_number_unsigned_t), (void **) &cache->ats.array, &cache->ats.used, &cache->ats.size);

              if (F_status_is_error(status2)) {
                controller_entry_print_error(&main->program.error, cache->action, is_entry, F_status_set_fine(status2), macro_controller_f(f_memory_array_increase), F_true);

                return status2;
              }

              // Save the value so to avoid string comparison during normal operation.
              actions->array[cache->ats.array[at_j]].number = i;

              // Continue into the requested item.
              at_i = cache->ats.used;
              at_j = cache->ats.used + 1;

              cache->ats.array[at_i] = i;
              cache->ats.array[at_j] = 0;
              cache->ats.used += 2;

              cache->action.name_action.used = 0;
              cache->action.line_action = 0;

              cache->action.name_item.used = 0;
              cache->action.line_item = entry->items.array[i].line;

              status2 = f_string_dynamic_append_nulless(entry->items.array[i].name, &cache->action.name_item);

              if (F_status_is_error(status2)) {
                controller_entry_print_error(&main->program.error, cache->action, is_entry, F_status_set_fine(status2), macro_controller_f(f_string_dynamic_append_nulless), F_true);

                return status2;
              }

              break;
            }
          } // for

          if (error_has || i >= entry->items.used) {
            if (i >= entry->items.used) {
              if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
                controller_lock_print(main->program.error.to, &main->thread);

                fl_print_format("%r%[%QThe %r item named '%]", main->program.error.to, f_string_eol_s, main->program.error.context, is_entry ? controller_entry_s : controller_exit_s, main->program.error.prefix, main->program.error.context);
                fl_print_format(f_string_format_Q_single_s.string, main->program.error.to, main->program.error.notable, actions->array[cache->ats.array[at_j]].parameters.array[0], main->program.error.notable);
                fl_print_format("%[' does not exist.%]%r", main->program.error.to, main->program.error.context, main->program.error.context, f_string_eol_s);

                controller_entry_print_error_cache(is_entry, &main->program.error, cache->action);

                controller_unlock_print_flush(main->program.error.to, &main->thread);
              }

              if (F_status_is_error_not(status)) {
                status = F_status_set_error(F_valid_not);
              }
            }
          }
          else {
            break;
          }
        }
      } // for

      cache->action.line_action = 0;
      cache->action.name_action.used = 0;

      // End of actions found, so drop to previous loop in stack.
      if (cache->ats.array[at_j] == actions->used) {

        // All actions for "main" are processed so there is nothing left to do.
        if (at_i == 0) break;

        at_i -= 2;
        at_j -= 2;

        cache->ats.used -= 2;
        ++cache->ats.array[at_j];

        cache->action.line_item = entry->items.array[cache->ats.array[at_i]].line;
        cache->action.name_item.used = 0;

        status2 = f_string_dynamic_append_nulless(entry->items.array[cache->ats.array[at_i]].name, &cache->action.name_item);

        if (F_status_is_error(status2)) {
          controller_entry_print_error(&main->program.error, cache->action, is_entry, F_status_set_fine(status2), macro_controller_f(f_string_dynamic_append_nulless), F_true);

          return status2;
        }
      }
    } // while

    if (!controller_thread_is_enabled(is_entry, &main->thread)) return F_status_set_error(F_interrupt);

    // If ready was never found in the entry, then default to always ready.
    if (main->setting.ready == controller_setting_ready_no_e) {
      main->setting.ready = controller_setting_ready_yes_e;
    }

    return status;
  }
#endif // _di_controller_entry_preprocess_

#ifdef __cplusplus
} // extern "C"
#endif
