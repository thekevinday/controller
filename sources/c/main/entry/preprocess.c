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
    main->process.ready = controller_process_ready_no_e;

    cache->ats.used = 0;

    cache->action.line_action = 0;
    cache->action.line_item = 0;
    cache->action.name_action.used = 0;
    cache->action.name_item.used = 0;

    status = f_memory_array_increase(controller_allocation_small_d, sizeof(f_number_unsigned_t), (void **) &cache->ats.array, &cache->ats.used, &cache->ats.size);

    if (F_status_is_error(status)) {
      controller_print_error_entry(&main->program.error, is_entry, F_status_set_fine(status), macro_controller_f(f_memory_array_increase), F_true);

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
      controller_print_error_entry(&main->program.error, is_entry, F_status_set_fine(status), macro_controller_f(f_string_dynamic_append_nulless), F_true);

      return status;
    }

    while (controller_thread_is_enabled(is_entry, &main->thread)) {

      actions = &entry->items.array[cache->ats.array[at_i]].actions;

      for (; cache->ats.array[at_j] < actions->used && controller_thread_is_enabled(is_entry, &main->thread); ++cache->ats.array[at_j]) {

        cache->action.line_action = actions->array[cache->ats.array[at_j]].line;
        cache->action.name_action.used = 0;

        status2 = f_string_dynamic_append_nulless(controller_entry_action_type_name(actions->array[cache->ats.array[at_j]].type), &cache->action.name_action);

        if (F_status_is_error(status2)) {
          controller_print_error_entry(&main->program.error, is_entry, F_status_set_fine(status2), macro_controller_f(f_string_dynamic_append_nulless), F_true);

          return status2;
        }

        if (actions->array[cache->ats.array[at_j]].type == controller_entry_action_type_ready_e) {
          if (main->process.ready == controller_process_ready_wait_e) {
            controller_print_warning_entry_action_multiple(&main->program.warning, cache, is_entry, controller_ready_s);
          }
          else {
            main->process.ready = controller_process_ready_wait_e;
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
                  controller_print_error_entry_item_failure(&main->program.error, cache, is_entry, entry->items.array[i].name, "cannot be executed because recursion is not allowed");

                  if (F_status_is_error_not(status)) {
                    status = F_status_set_error(F_recurse);
                  }

                  error_has = F_true;

                  break;
                }
              } // for

              if (error_has) break;

              status2 = f_memory_array_increase(controller_allocation_small_d, sizeof(f_number_unsigned_t), (void **) &cache->ats.array, &cache->ats.used, &cache->ats.size);

              if (F_status_is_error(status2)) {
                controller_print_error_entry(&main->program.error, is_entry, F_status_set_fine(status2), macro_controller_f(f_memory_array_increase), F_true);

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
                controller_print_error_entry(&main->program.error, is_entry, F_status_set_fine(status2), macro_controller_f(f_string_dynamic_append_nulless), F_true);

                return status2;
              }

              break;
            }
          } // for

          if (error_has || i >= entry->items.used) {
            if (i >= entry->items.used) {
              controller_print_error_entry_item_failure(&main->program.error, cache, is_entry, actions->array[cache->ats.array[at_j]].parameters.array[0], "does not exist");

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
          controller_print_error_entry(&main->program.error, is_entry, F_status_set_fine(status2), macro_controller_f(f_string_dynamic_append_nulless), F_true);

          return status2;
        }
      }
    } // while

    if (!controller_thread_is_enabled(is_entry, &main->thread)) return F_status_set_error(F_interrupt);

    // If ready is not found in the entry, then default to always ready.
    if (main->process.ready == controller_process_ready_no_e) {
      main->process.ready = controller_process_ready_yes_e;
    }

    return status;
  }
#endif // _di_controller_entry_preprocess_

#ifdef __cplusplus
} // extern "C"
#endif
