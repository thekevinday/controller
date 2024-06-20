#include "controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_entry_read_
  f_status_t controller_entry_read(controller_t * const main, controller_entry_t * const entry) {

    if (!main) return F_status_set_error(F_parameter);

    f_status_t status = F_okay;
    f_number_unsigned_t i = 0;

    entry->status = F_known_not;
    entry->items.used = 0;
    entry->session = controller_entry_session_same_e;

    if (main->callback.process_entry_setup) {
      status = main->callback.process_entry_setup(main, entry);
    }

    main->thread.cache.action.line_action = 0;
    main->thread.cache.action.line_item = 0;

    main->thread.cache.timestamp.seconds = 0;
    main->thread.cache.timestamp.seconds_nano = 0;

    main->thread.cache.comments.used = 0;
    main->thread.cache.delimits.used = 0;

    main->thread.cache.content_action.used = 0;

    for (; i < main->thread.cache.content_actions.used; ++i) {
      main->thread.cache.content_actions.array[i].used = 0;
    } // for

    for (i = 0; i < main->thread.cache.content_items.used; ++i) {
      main->thread.cache.content_items.array[i].used = 0;
    } // for

    main->thread.cache.content_actions.used = 0;
    main->thread.cache.content_items.used = 0;

    main->thread.cache.object_actions.used = 0;
    main->thread.cache.object_items.used = 0;

    main->thread.cache.buffer_file.used = 0;
    main->thread.cache.buffer_path.used = 0;

    main->thread.cache.action.name_file.used = 0;
    main->thread.cache.action.name_action.used = 0;
    main->thread.cache.action.name_item.used = 0;

    if (F_status_is_error_not(status)) {
      if (entry->flag & controller_entry_flag_is_e) {
        status = controller_file_load(main, F_true, controller_entries_s, main->process.name_entry, controller_entry_s);
      }
      else {
        status = controller_file_load(main, F_false, controller_exits_s, main->process.name_entry, controller_exit_s);
        if (status == F_file_found_not) return F_file_found_not;
      }
    }

    if (F_status_is_error_not(status)) {
      if (main->thread.cache.buffer_file.used) {
        controller_interrupt_t custom = macro_controller_interrupt_t_initialize_1(entry->flag & controller_entry_flag_is_e, main);
        f_state_t state = macro_f_state_t_initialize_1(controller_allocation_large_d, controller_allocation_small_d, F_okay, 0, 0, 0, &controller_thread_signal_state_fss, 0, (void *) &custom, 0);
        f_range_t range = macro_f_range_t_initialize_2(main->thread.cache.buffer_file.used);

        fll_fss_basic_list_read(main->thread.cache.buffer_file, &range, &main->thread.cache.object_items, &main->thread.cache.content_items, &main->thread.cache.delimits, 0, &main->thread.cache.comments, &state);

        if (F_status_is_error(status)) {
          controller_print_error_status(&main->program.error, macro_controller_f(fll_fss_basic_list_read), F_status_set_fine(status));
        }
        else {
          f_fss_apply_delimit(main->thread.cache.delimits, &main->thread.cache.buffer_file, &state);

          if (F_status_is_error(status)) {
            controller_print_error_entry(&main->program.error, entry->flag & controller_entry_flag_is_e, F_status_set_fine(status), macro_controller_f(f_fss_apply_delimit), F_true);
          }
        }
      }
      else {
        controller_print_error_file_status(&main->program.error, macro_controller_f(controller_file_load), (entry->flag & controller_entry_flag_is_e) ? controller_entry_s : controller_exit_s, f_file_operation_read_s, fll_error_file_type_file_e, F_status_set_fine(status));
    }

    if (F_status_is_error_not(status) && main->thread.cache.object_items.used) {
      status = f_memory_array_increase_by(main->thread.cache.object_items.used, sizeof(f_range_t), (void **) &main->thread.cache.object_items.array, &main->thread.cache.object_items.used, &main->thread.cache.object_items.size);

      if (F_status_is_error(status)) {
        controller_print_error_entry(&main->program.error, entry->flag & controller_entry_flag_is_e, F_status_set_fine(status), macro_controller_f(f_memory_array_increase_by), F_true);
      }
      else {

        // 0x1 = main found, 0x2 = found existing.
        uint8_t code = 0;

        f_range_t *range = 0;
        f_number_unsigned_t at = 0;
        f_number_unsigned_t j = 0;
        f_state_t state = f_state_t_initialize;

        for (; i < main->thread.cache.object_items.used && controller_thread_is_enabled(entry->flag & controller_entry_flag_is_e, &main->thread); ++i) {

          code &= ~0x2;
          at = 0;
          range = 0;

          main->thread.cache.action.line_action = 0;
          main->thread.cache.action.line_item = 0;

          main->thread.cache.comments.used = 0;
          main->thread.cache.delimits.used = 0;

          main->thread.cache.content_action.used = 0;
          main->thread.cache.content_actions.used = 0;

          main->thread.cache.object_actions.used = 0;

          main->thread.cache.buffer_path.used = 0;

          main->thread.cache.action.name_action.used = 0;
          main->thread.cache.action.name_item.used = 0;

          status = f_memory_array_increase(controller_allocation_small_d, sizeof(controller_entry_item_t), (void **) &entry->items.array, &entry->items.used, &entry->items.size);

          if (F_status_is_error(status)) {
            controller_print_error_entry(&main->program.error, entry->flag & controller_entry_flag_is_e, F_status_set_fine(status), macro_controller_f(f_memory_array_increase), F_true);

            break;
          }

          status = f_string_dynamic_partial_append(main->thread.cache.buffer_file, main->thread.cache.object_items.array[i], &main->thread.cache.action.name_item);

          if (F_status_is_error(status)) {
            controller_print_error_entry(&main->program.error, entry->flag & controller_entry_flag_is_e, F_status_set_fine(status), macro_controller_f(f_string_dynamic_partial_append), F_true);

            break;
          }

          f_fss_count_lines(main->thread.cache.buffer_file, main->thread.cache.object_items.array[i].start, &main->thread.cache.action.line_item, &main->setting.state);

          if (F_status_is_error(status)) {
            controller_print_error_entry(&main->program.error, entry->flag & controller_entry_flag_is_e, F_status_set_fine(status), macro_controller_f(f_fss_count_lines), F_true);

            break;
          }

          ++main->thread.cache.action.line_item;

          for (j = (code & 0x1) ? 1 : 0; j < entry->items.used; ++j) {

            if (f_compare_dynamic(entry->items.array[j].name, main->thread.cache.action.name_item) == F_equal_to) {
              controller_print_warning_entry_item_duplicate_ignore(&main->program.warning, &main->thread.cache, entry->flag & controller_entry_flag_is_e, main->thread.cache.action.name_item);

              code |= 0x2;

              break;
            }
          } // for

          if (code & 0x2) continue;

          range = &main->thread.cache.content_items.array[i].array[0];

          if (f_compare_dynamic(controller_main_s, main->thread.cache.action.name_item) == F_equal_to) {
            code |= 0x1;
            at = 0;

            if (!entry->items.used) {
              entry->items.used = 1;
            }
          }
          else if (f_compare_dynamic(controller_settings_s, main->thread.cache.action.name_item) == F_equal_to) {
            status = controller_entry_setting_read(main, entry->flag & controller_entry_flag_is_e, *range);

            continue;
          }
          else if (entry->items.used) {
            at = entry->items.used++;
          }
          else {

            // Skip position 0, which is reserved for "main".
            entry->items.array[0].name.used = 0;

            at = 1;
            entry->items.used = 2;
          }

          entry->items.array[at].line = main->thread.cache.action.line_item;

          status = f_string_dynamic_append_nulless(main->thread.cache.action.name_item, &entry->items.array[at].name);

          if (F_status_is_error(status)) {
            controller_print_error_status(&main->program.error, macro_controller_f(f_string_dynamic_append_nulless), F_status_set_fine(status));

            break;
          }

          status = controller_entry_action_read(main, entry->flag & controller_entry_flag_is_e, *range, &entry->items.array[at].actions);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) != F_interrupt) {
              controller_lock_print(main->program.error.to, &main->thread);

              controller_print_error_entry_cache(&main->program.error, &main->thread.cache.action, entry->flag & controller_entry_flag_is_e);

              controller_unlock_print_flush(main->program.error.to, &main->thread);
            }

            if (F_status_set_fine(status) == F_memory_not) break;
          }
        } // for

        if (entry->flag & controller_entry_flag_is_e && F_status_set_fine(status) == F_interrupt) return status;

        if (F_status_is_error_not(status)) {
          main->thread.cache.action.name_action.used = 0;
          main->thread.cache.action.name_item.used = 0;

          if (!(code & 0x1)) {
            status = F_status_set_error(F_found_not);

            controller_print_message_entry_item_required(&main->program.error, entry->flag & controller_entry_flag_is_e, "is not found");
          }

          if (F_status_is_error_not(status)) {
            controller_entry_action_t *action = 0;

            f_number_unsigned_t k = 0;

            // 0x1 = missing or not, 0x2 = one or more missing.
            uint8_t missing = 0;

            for (i = 0; i < entry->items.used; ++i) {

              for (j = 0; j < entry->items.array[i].actions.used; ++j) {

                if (!controller_thread_is_enabled(entry->flag & controller_entry_flag_is_e, &main->thread)) {
                  return F_status_set_error(F_interrupt);
                }

                action = &entry->items.array[i].actions.array[j];

                // Only process actions that don't already have an error.
                if (F_status_is_error(action->status)) continue;

                if (action->type == controller_entry_action_type_failsafe_e || action->type == controller_entry_action_type_item_e) {
                  missing |= 0x1;

                  for (k = 0; k < entry->items.used; ++k) {

                    if (f_compare_dynamic(action->parameters.array[0], entry->items.array[k].name) == F_equal_to) {
                      missing &= ~0x1;

                      break;
                    }
                  } // for

                  if (missing & 0x1) {
                    missing |= 0x2;

                    main->thread.cache.action.line_action = action->line;
                    main->thread.cache.action.line_item = entry->items.array[i].line;

                    status = f_string_dynamic_append_nulless(entry->items.array[i].name, &main->thread.cache.action.name_item);

                    if (F_status_is_error(status)) {
                      controller_print_error_status(&main->program.error, macro_controller_f(f_string_dynamic_append_nulless), F_status_set_fine(status));

                      break;
                    }

                    controller_print_message_entry_item_required(&main->program.error, entry->flag & controller_entry_flag_is_e, "does not exist");

                    action->number = 0;
                    action->status = controller_status_simplify_error(F_found_not);

                    main->thread.cache.action.name_action.used = 0;
                    main->thread.cache.action.name_item.used = 0;
                  }
                  else {
                    action->number = k;
                  }
                }
              } // for
            } // for
          }
        }
      }
    }

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) != F_interrupt) {
        controller_print_error_entry_cache(&main->program.error, &main->thread.cache.action, entry->flag & controller_entry_flag_is_e);
      }

      entry->status = controller_status_simplify_error(F_status_set_fine(status));
    }
    else {
      entry->status = F_okay;
    }

    return entry->status;
  }
#endif // _di_controller_entry_read_

#ifdef __cplusplus
} // extern "C"
#endif
