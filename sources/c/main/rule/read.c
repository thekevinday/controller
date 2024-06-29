#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_rule_read_
  f_status_t controller_rule_read(controller_t * const main, controller_cache_t * const cache, const uint8_t is_normal, const f_string_static_t alias, controller_entry_t * const entry, controller_rule_t * const rule) {

    if (!main || !cache || !entry || !rule) return F_status_set_error(F_parameter);

    bool for_item = F_true;

    rule->timeout_kill = entry->timeout_kill ? entry->timeout_kill : 0;
    rule->timeout_start = entry->timeout_start ? entry->timeout_start : 0;
    rule->timeout_stop = entry->timeout_stop ? entry->timeout_stop : 0;

    rule->has = 0;
    rule->group = 0;
    rule->user = 0;
    rule->nice = 0;

    rule->timestamp.seconds = 0;
    rule->timestamp.seconds_nano = 0;

    rule->alias.used = 0;
    rule->engine.used = 0;
    rule->engine_arguments.used = 0;
    rule->name.used = 0;
    rule->path.used = 0;

    rule->define.used = 0;
    rule->parameter.used = 0;
    rule->environment.used = 0;

    rule->affinity.used = 0;

    if (rule->capability) {
      f_capability_delete(&rule->capability);
      rule->capability = 0;
    }

    rule->cgroup.as_new = F_false;
    rule->cgroup.path.used = 0;
    rule->cgroup.groups.used = 0;

    macro_f_control_group_t_clear(rule->cgroup);

    rule->groups.used = 0;
    rule->limits.used = 0;

    rule->scheduler.policy = 0;
    rule->scheduler.priority = 0;

    rule->ons.used = 0;
    rule->items.used = 0;

    cache->action.line_item = 0;
    cache->action.line_action = 0;

    cache->range_action.start = 1;
    cache->range_action.stop = 0;

    cache->comments.used = 0;
    cache->delimits.used = 0;

    cache->buffer_file.used = 0;
    cache->buffer_item.used = 0;
    cache->buffer_path.used = 0;

    cache->content_items.used = 0;
    cache->object_items.used = 0;

    cache->action.name_action.used = 0;
    cache->action.name_file.used = 0;
    cache->action.name_item.used = 0;

    {
      f_number_unsigned_t i = 0;
      f_number_unsigned_t j = 0;
      f_number_unsigned_t k = 0;
      f_number_unsigned_t l = 0;

      for (i = 0; i < rule->cgroup.groups.size; ++i) {
        rule->cgroup.groups.array[i].used = 0;
      } // for

      for (; i < controller_rule_action_type__enum_size_e; ++i) {
        rule->status[i] = F_known_not;
      } // for

      for (i = 0; i < cache->content_items.size; ++i) {
        cache->content_items.array[i].used = 0;
      } // for

      for (i = 0; i < rule->engine_arguments.size; ++i) {
        rule->engine_arguments.array[i].used = 0;
      } // for

      for (i = 0; i < rule->ons.size; ++i) {
        rule->ons.array[i].need.used = 0;
        rule->ons.array[i].want.used = 0;
        rule->ons.array[i].wish.used = 0;
      } // for

      for (i = 0; i < rule->items.size; ++i) {

        rule->items.array[i].type = 0;
        rule->items.array[i].with = 0;
        rule->items.array[i].line = 0;
        rule->items.array[i].pid_file.used = 0;
        rule->items.array[i].actions.used = 0;

        for (j = 0; j < controller_rule_action_execute_type__enum_size_e; ++j) {

          rule->items.array[i].reruns[j].is = 0;

          macro_controller_rule_rerun_item_initialize(rule->items.array[i].reruns[j].failure);
          macro_controller_rule_rerun_item_initialize(rule->items.array[i].reruns[j].success);
        } // for

        for (j = 0; j < rule->items.array[i].actions.size; ++j) {

          rule->items.array[i].actions.array[j].type = 0;
          rule->items.array[i].actions.array[j].line = 0;
          rule->items.array[i].actions.array[j].status = F_okay;
          rule->items.array[i].actions.array[j].parameters.used = 0;
          rule->items.array[i].actions.array[j].ikis.used = 0;

          for (k = 0; k < rule->items.array[i].actions.array[j].parameters.size; ++k) {
            rule->items.array[i].actions.array[j].parameters.array[k].used = 0;
          } // for

          for (k = 0; k < rule->items.array[i].actions.array[j].ikis.size; ++k) {

            rule->items.array[i].actions.array[j].ikis.array[k].content.used = 0;
            rule->items.array[i].actions.array[j].ikis.array[k].delimits.used = 0;
            rule->items.array[i].actions.array[j].ikis.array[k].variable.used = 0;
            rule->items.array[i].actions.array[j].ikis.array[k].vocabulary.used = 0;

            for (l = 0; l < rule->items.array[i].actions.array[j].ikis.array[k].content.size; ++l) {

              rule->items.array[i].actions.array[j].ikis.array[k].content.array[l].start = 1;
              rule->items.array[i].actions.array[j].ikis.array[k].content.array[l].stop = 0;
            } // for

            for (l = 0; l < rule->items.array[i].actions.array[j].ikis.array[k].delimits.size; ++l) {
              rule->items.array[i].actions.array[j].ikis.array[k].delimits.array[l] = 0;
            } // for

            for (l = 0; l < rule->items.array[i].actions.array[j].ikis.array[k].variable.size; ++l) {

              rule->items.array[i].actions.array[j].ikis.array[k].variable.array[l].start = 1;
              rule->items.array[i].actions.array[j].ikis.array[k].variable.array[l].stop = 0;
            } // for

            for (l = 0; l < rule->items.array[i].actions.array[j].ikis.array[k].vocabulary.size; ++l) {

              rule->items.array[i].actions.array[j].ikis.array[k].vocabulary.array[l].start = 1;
              rule->items.array[i].actions.array[j].ikis.array[k].vocabulary.array[l].stop = 0;
            } // for
          } // for
        } // for
      } // for
    }

    controller_interrupt_t custom = macro_controller_interrupt_t_initialize_1(is_normal, main);
    f_state_t state = macro_f_state_t_initialize_1(controller_allocation_large_d, controller_allocation_small_d, F_okay, 0, 0, 0, &controller_thread_signal_state_fss, 0, (void *) &custom, 0);
    state.status = f_string_dynamic_append_nulless(alias, &rule->alias);

    if (F_status_is_error(state.status)) {
      controller_print_error_status(&main->program.error, macro_controller_f(f_string_dynamic_append_nulless), F_status_set_fine(state.status));
    }
    else {
      state.status = controller_file_load(main, F_true, controller_rules_s, rule->alias, controller_rule_s);
    }

    if (F_status_is_error_not(state.status)) {
      rule->timestamp = cache->timestamp;

      if (cache->buffer_file.used) {
        f_range_t range = macro_f_range_t_initialize_2(cache->buffer_file.used);

        fll_fss_basic_list_read(cache->buffer_file, &range, &cache->object_items, &cache->content_items, &cache->delimits, 0, &cache->comments, &state);

        if (F_status_is_error(state.status)) {
          controller_print_error_status(&main->program.error, macro_controller_f(fll_fss_basic_list_read), F_status_set_fine(state.status));
        }
        else {
          f_fss_apply_delimit(cache->delimits, &cache->buffer_file, &state);

          if (F_status_is_error(state.status)) {
            controller_print_error_status(&main->program.error, macro_controller_f(f_fss_apply_delimit), F_status_set_fine(state.status));
          }
        }
      }
    }

    if (F_status_is_error_not(state.status) && cache->object_items.used) {
      if (rule->items.size < cache->object_items.size) {
        state.status = f_memory_arrays_resize(cache->object_items.size, sizeof(controller_rule_item_t), (void **) &rule->items.array, &rule->items.used, &rule->items.size, &controller_rule_items_delete_callback);
      }

      if (F_status_is_error(state.status)) {
        controller_print_error_status(&main->program.error, macro_controller_f(f_memory_arrays_resize), F_status_set_fine(state.status));
      }
      else {
        f_number_unsigned_t i = 0;
        f_number_unsigned_t j = 0;
        f_state_t state = f_state_t_initialize;

        for (; i < cache->object_items.used; ++i) {

          cache->action.line_item = 0;
          cache->action.line_action = 0;

          cache->range_action.start = 1;
          cache->range_action.stop = 0;

          cache->comments.used = 0;
          cache->delimits.used = 0;

          cache->content_action.used = 0;

          for (j = 0; j < cache->content_actions.used; ++j) {
            cache->content_actions.array[j].used = 0;
          } // for

          cache->content_actions.used = 0;
          cache->object_actions.used = 0;

          cache->buffer_item.used = 0;
          cache->buffer_path.used = 0;

          cache->action.name_action.used = 0;
          cache->action.name_item.used = 0;

          for_item = F_true;

          f_fss_count_lines(cache->buffer_file, cache->object_items.array[i].start, &cache->action.line_item, &state);

          if (F_status_is_error(state.status)) {
            controller_print_error_status(&main->program.error, macro_controller_f(f_fss_count_lines), F_status_set_fine(state.status));

            break;
          }

          rule->items.array[rule->items.used].line = ++cache->action.line_item;

          state.status = f_rip_dynamic_partial_nulless(cache->buffer_file, cache->object_items.array[i], &cache->action.name_item);

          if (F_status_is_error(state.status)) {
            controller_print_error_status(&main->program.error, macro_controller_f(f_rip_dynamic_partial_nulless), F_status_set_fine(state.status));

            break;
          }

          if (f_compare_dynamic(controller_settings_s, cache->action.name_item) == F_equal_to) {
            rule->items.array[rule->items.used].type = 0;
          }
          else if (f_compare_dynamic(controller_command_s, cache->action.name_item) == F_equal_to) {
            rule->items.array[rule->items.used].type = controller_rule_item_type_command_e;
          }
          else if (f_compare_dynamic(controller_script_s, cache->action.name_item) == F_equal_to) {
            rule->items.array[rule->items.used].type = controller_rule_item_type_script_e;
          }
          else if (f_compare_dynamic(controller_service_s, cache->action.name_item) == F_equal_to) {
            rule->items.array[rule->items.used].type = controller_rule_item_type_service_e;
          }
          else if (f_compare_dynamic(controller_utility_s, cache->action.name_item) == F_equal_to) {
            rule->items.array[rule->items.used].type = controller_rule_item_type_utility_e;
          }
          else {
            controller_print_warning_rule_item_unknown(&main->program.warning, &cache->action, cache->action.name_item);

            continue;
          }

          state.status = f_string_dynamic_partial_append(cache->buffer_file, cache->content_items.array[i].array[0], &cache->buffer_item);

          if (F_status_is_error(state.status)) {
            controller_print_error_status(&main->program.error, macro_controller_f(f_rip_dynamic_partial_nulless), F_status_set_fine(state.status));

            break;
          }

          if (rule->items.array[rule->items.used].type) {

            // Initialize the item with settings.
            rule->items.array[rule->items.used].with = 0;

            if (entry->session == controller_entry_session_new_e) {
              rule->items.array[rule->items.used].with |= controller_with_session_new_d;
            }
            else {
              rule->items.array[rule->items.used].with |= controller_with_session_same_d;
            }

            state.status = controller_rule_item_read(main, cache, is_normal, &rule->items.array[rule->items.used]);
            if (F_status_is_error(state.status)) break;

            ++rule->items.used;
          }
          else {
            for_item = F_false;

            state.status = controller_rule_setting_read(main, cache, is_normal, rule);

            if (F_status_is_error(state.status)) {
              if (F_status_set_fine(state.status) == F_memory_not) break;
            }
          }
        } // for
      }
    }

    if (F_status_is_error(state.status)) {
      controller_print_error_rule_item(&main->program.error, &cache->action, for_item, F_status_set_fine(state.status));

      rule->status[0] = controller_error_simplify(F_status_set_fine(state.status));

      return rule->status[0];
    }

    return F_okay;
  }
#endif // _di_controller_rule_read_

#ifdef __cplusplus
} // extern "C"
#endif
