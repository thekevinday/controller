#include "controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_entry_read_
  f_status_t controller_entry_read(controller_t * const main, controller_cache_t * const cache, const uint8_t is_entry) {

    if (!main || !cache) return F_status_set_error(F_parameter);

    f_status_t status = F_okay;

    controller_entry_t * const entry = is_entry ? &main->process.entry : &main->process.exit;

    entry->status = F_known_not;
    entry->items.used = 0;
    entry->session = controller_entry_session_same_e;

    if (main->callback.process_entry_setup) {
      status = main->callback.process_entry_setup(main, cache, entry, is_entry);
    }

    cache->action.line_action = 0;
    cache->action.line_item = 0;

    cache->timestamp.seconds = 0;
    cache->timestamp.seconds_nano = 0;

    cache->comments.used = 0;
    cache->delimits.used = 0;

    cache->content_action.used = 0;

    {
      f_number_unsigned_t i = 0;

      for (; i < cache->content_actions.used; ++i) {
        cache->content_actions.array[i].used = 0;
      } // for

      for (i = 0; i < cache->content_items.used; ++i) {
        cache->content_items.array[i].used = 0;
      } // for
    }

    cache->content_actions.used = 0;
    cache->content_items.used = 0;

    cache->object_actions.used = 0;
    cache->object_items.used = 0;

    cache->buffer_file.used = 0;
    cache->buffer_path.used = 0;

    cache->action.name_file.used = 0;
    cache->action.name_action.used = 0;
    cache->action.name_item.used = 0;

    if (F_status_is_error_not(status)) {
      if (is_entry) {
        status = controller_file_load(main, cache, F_true, controller_entries_s, main->process.name_entry, controller_entry_s);
      }
      else {
        status = controller_file_load(main, cache, F_false, controller_exits_s, main->process.name_entry, controller_exit_s);
        if (status == F_file_found_not) return F_file_found_not;
      }
    }

    if (F_status_is_error_not(status)) {
      if (cache->buffer_file.used) {
        controller_interrupt_t custom = macro_controller_interrupt_t_initialize_1(is_entry, main);
        f_state_t state = macro_f_state_t_initialize_1(controller_allocation_large_d, controller_allocation_small_d, F_okay, 0, 0, 0, &controller_thread_signal_state_fss, 0, (void *) &custom, 0);
        f_range_t range = macro_f_range_t_initialize_2(cache->buffer_file.used);

        fll_fss_basic_list_read(cache->buffer_file, &range, &cache->object_items, &cache->content_items, &cache->delimits, 0, &cache->comments, &state);

        if (F_status_is_error(status)) {
          controller_print_error_status(&main->program.error, macro_controller_f(fll_fss_basic_list_read), F_status_set_fine(status));
        }
        else {
          f_fss_apply_delimit(cache->delimits, &cache->buffer_file, &state);

          if (F_status_is_error(status)) {
            controller_print_error_entry(&main->program.error, cache, is_entry, F_status_set_fine(status), macro_controller_f(f_fss_apply_delimit), F_true);
          }
        }
      }
      else {
        if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
          controller_lock_print(main->program.error.to, &main->thread);

          fll_print_format("%r%[%QThe %r file is empty.%]%r", main->program.error.to, f_string_eol_s, main->program.error.context, main->program.error.prefix, is_entry ? controller_entry_s : is_entry ? controller_entry_s : controller_exit_s, main->program.error.context, f_string_eol_s);

          controller_unlock_print_flush(main->program.error.to, &main->thread);
        }

        status = F_status_set_error(F_data_not);
      }
    }

    if (F_status_is_error_not(status) && cache->object_items.used) {
      status = f_memory_array_increase_by(cache->object_items.used, sizeof(f_range_t), (void **) &cache->object_items.array, &cache->object_items.used, &cache->object_items.size);

      if (F_status_is_error(status)) {
        controller_print_error_entry(&main->program.error, cache, is_entry, F_status_set_fine(status), macro_controller_f(f_memory_array_increase_by), F_true);
      }
      else {

        // 0x1 = main found, 0x2 = found existing.
        uint8_t code = 0;

        f_range_t *range = 0;

        f_number_unsigned_t at = 0;
        f_number_unsigned_t i = 0;
        f_number_unsigned_t j = 0;

        f_state_t state = f_state_t_initialize;

        for (; i < cache->object_items.used && controller_thread_is_enabled(is_entry, &main->thread); ++i) {

          if (code & 0x2) {
            code -= 0x2;
          }

          at = 0;
          range = 0;

          cache->action.line_action = 0;
          cache->action.line_item = 0;

          cache->comments.used = 0;
          cache->delimits.used = 0;

          cache->content_action.used = 0;
          cache->content_actions.used = 0;

          cache->object_actions.used = 0;

          cache->buffer_path.used = 0;

          cache->action.name_action.used = 0;
          cache->action.name_item.used = 0;

          status = f_memory_array_increase(controller_allocation_small_d, sizeof(controller_entry_item_t), (void **) &entry->items.array, &entry->items.used, &entry->items.size);

          if (F_status_is_error(status)) {
            controller_print_error_entry(&main->program.error, cache, is_entry, F_status_set_fine(status), macro_controller_f(f_memory_array_increase), F_true);

            break;
          }

          status = f_string_dynamic_partial_append(cache->buffer_file, cache->object_items.array[i], &cache->action.name_item);

          if (F_status_is_error(status)) {
            controller_print_error_entry(&main->program.error, cache, is_entry, F_status_set_fine(status), macro_controller_f(f_string_dynamic_partial_append), F_true);

            break;
          }

          f_fss_count_lines(cache->buffer_file, cache->object_items.array[i].start, &cache->action.line_item, &main->setting.state);

          if (F_status_is_error(status)) {
            controller_print_error_entry(&main->program.error, cache, is_entry, F_status_set_fine(status), macro_controller_f(f_fss_count_lines), F_true);

            break;
          }

          ++cache->action.line_item;

          for (j = (code & 0x1) ? 1 : 0; j < entry->items.used; ++j) {

            if (f_compare_dynamic(entry->items.array[j].name, cache->action.name_item) == F_equal_to) {
              if (main->program.warning.verbosity == f_console_verbosity_debug_e) {
                controller_lock_print(main->program.warning.to, &main->thread);

                fl_print_format("%r%[%QIgnoring duplicate %r item '%]", main->program.warning.to, f_string_eol_s, main->program.warning.context, main->program.warning.prefix, is_entry ? controller_entry_s : controller_exit_s, main->program.warning.context);
                fl_print_format(f_string_format_Q_single_s.string, main->program.warning.to, main->program.warning.notable, cache->action.name_file, main->program.warning.notable);
                fl_print_format(f_string_format_sentence_end_quote_s.string, main->program.warning.to, main->program.warning.context, main->program.warning.context, f_string_eol_s);

                controller_print_error_entry_cache(&main->program.warning, &cache->action, is_entry);

                controller_unlock_print_flush(main->program.warning.to, &main->thread);
              }

              code |= 0x2;

              break;
            }
          } // for

          if (code & 0x2) continue;

          range = &cache->content_items.array[i].array[0];

          if (f_compare_dynamic(controller_main_s, cache->action.name_item) == F_equal_to) {
            code |= 0x1;

            at = 0;

            if (!entry->items.used) {
              entry->items.used = 1;
            }
          }
          else if (f_compare_dynamic(controller_settings_s, cache->action.name_item) == F_equal_to) {
            status = controller_entry_setting_read(main, cache, is_entry, *range);

            continue;
          }
          else if (entry->items.used) {
            at = entry->items.used++;
          }
          else {

            // skip position 0, which is reserved for "main".
            entry->items.array[0].name.used = 0;

            at = 1;
            entry->items.used = 2;
          }

          entry->items.array[at].line = cache->action.line_item;

          status = f_string_dynamic_append_nulless(cache->action.name_item, &entry->items.array[at].name);

          if (F_status_is_error(status)) {
            controller_print_error(main->thread, &main->program.error, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true);

            break;
          }

          status = controller_entry_actions_read(main, cache, is_entry, *range, &entry->items.array[at].actions);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) != F_interrupt) {
              controller_lock_print(main->program.error.to, &main->thread);

              controller_print_error_entry_cache(is_entry, &main->program.error, &cache->action);

              controller_unlock_print_flush(main->program.error.to, &main->thread);
            }

            if (F_status_set_fine(status) == F_memory_not) break;
          }
        } // for

        if (is_entry && F_status_set_fine(status) == F_interrupt) return status;

        if (F_status_is_error_not(status)) {
          cache->action.name_action.used = 0;
          cache->action.name_item.used = 0;

          if (!(code & 0x1)) {
            if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
              controller_lock_print(main->program.error.to, &main->thread);

              fl_print_format("%r%[%QThe required %r item '%]", main->program.error.to, f_string_eol_s, main->program.error.context, main->program.error.prefix, is_entry ? controller_entry_s : controller_exit_s, main->program.error.context);
              fl_print_format(f_string_format_r_single_s.string, main->program.error.to, main->program.error.notable, controller_main_s, main->program.error.notable);
              fl_print_format("%[' is not found.%]%r", main->program.error.to, main->program.error.context, main->program.error.context, f_string_eol_s);

              controller_unlock_print_flush(main->program.error.to, &main->thread);
            }

            status = F_status_set_error(F_found_not);
          }

          if (F_status_is_error_not(status)) {
            controller_entry_action_t *action = 0;

            f_number_unsigned_t k = 0;

            // 0x1 = missing or not, 0x2 = one or more missing.
            uint8_t missing = 0;

            for (i = 0; i < entry->items.used; ++i) {

              for (j = 0; j < entry->items.array[i].actions.used; ++j) {

                if (!controller_thread_is_enabled(is_entry, &main->thread)) {
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

                    cache->action.line_action = action->line;
                    cache->action.line_item = entry->items.array[i].line;

                    status = f_string_dynamic_append_nulless(entry->items.array[i].name, &cache->action.name_item);

                    if (F_status_is_error(status)) {
                      controller_print_error(main->thread, &main->program.error, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true);

                      break;
                    }

                    if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
                      controller_lock_print(main->program.error.to, &main->thread);

                      fl_print_format("%r%[%QThe required %r item '%]", main->program.error.to, f_string_eol_s, main->program.error.context, main->program.error.prefix, is_entry ? controller_entry_s : controller_exit_s, main->program.error.context);
                      fl_print_format(f_string_format_Q_single_s.string, main->program.error.to, main->program.error.notable, action->parameters.array[0], main->program.error.notable);
                      fl_print_format("%[' does not exist.%]%r", main->program.error.to, main->program.error.context, main->program.error.context, f_string_eol_s);

                      controller_print_error_entry_cache(is_entry, &main->program.error, &cache->action);

                      controller_unlock_print_flush(main->program.error.to, &main->thread);
                    }

                    action->number = 0;
                    action->status = controller_status_simplify_error(F_found_not);

                    cache->action.name_action.used = 0;
                    cache->action.name_item.used = 0;
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
        controller_print_error_entry_cache(is_entry, &main->program.error, &cache->action);
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
