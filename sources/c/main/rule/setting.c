#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_rule_setting_limit_type_identify_
  uint8_t controller_rule_setting_limit_type_identify(const f_string_static_t limit) {

    if (f_compare_dynamic(limit, controller_as_s)         == F_equal_to) return controller_resource_limit_type_as_e;
    if (f_compare_dynamic(limit, controller_core_s)       == F_equal_to) return controller_resource_limit_type_core_e;
    if (f_compare_dynamic(limit, controller_cpu_s)        == F_equal_to) return controller_resource_limit_type_cpu_e;
    if (f_compare_dynamic(limit, controller_data_s)       == F_equal_to) return controller_resource_limit_type_data_e;
    if (f_compare_dynamic(limit, controller_fsize_s)      == F_equal_to) return controller_resource_limit_type_fsize_e;
    if (f_compare_dynamic(limit, controller_locks_s)      == F_equal_to) return controller_resource_limit_type_locks_e;
    if (f_compare_dynamic(limit, controller_memlock_s)    == F_equal_to) return controller_resource_limit_type_memlock_e;
    if (f_compare_dynamic(limit, controller_msgqueue_s)   == F_equal_to) return controller_resource_limit_type_msgqueue_e;
    if (f_compare_dynamic(limit, controller_nice_s)       == F_equal_to) return controller_resource_limit_type_nice_e;
    if (f_compare_dynamic(limit, controller_nofile_s)     == F_equal_to) return controller_resource_limit_type_nofile_e;
    if (f_compare_dynamic(limit, controller_nproc_s)      == F_equal_to) return controller_resource_limit_type_nproc_e;
    if (f_compare_dynamic(limit, controller_rss_s)        == F_equal_to) return controller_resource_limit_type_rss_e;
    if (f_compare_dynamic(limit, controller_rtprio_s)     == F_equal_to) return controller_resource_limit_type_rtprio_e;
    if (f_compare_dynamic(limit, controller_rttime_s)     == F_equal_to) return controller_resource_limit_type_rttime_e;
    if (f_compare_dynamic(limit, controller_sigpending_s) == F_equal_to) return controller_resource_limit_type_sigpending_e;
    if (f_compare_dynamic(limit, controller_stack_s)      == F_equal_to) return controller_resource_limit_type_stack_e;

    return 0;
  }
#endif // _di_controller_rule_setting_limit_type_identify_

#ifndef _di_controller_rule_setting_limit_type_name_
  f_string_static_t controller_rule_setting_limit_type_name(const uint8_t type) {

    switch (type) {
      case controller_resource_limit_type_as_e:
        return controller_as_s;

      case controller_resource_limit_type_core_e:
        return controller_core_s;

      case controller_resource_limit_type_cpu_e:
        return controller_cpu_s;

      case controller_resource_limit_type_data_e:
        return controller_data_s;

      case controller_resource_limit_type_fsize_e:
        return controller_fsize_s;

      case controller_resource_limit_type_locks_e:
        return controller_locks_s;

      case controller_resource_limit_type_memlock_e:
        return controller_memlock_s;

      case controller_resource_limit_type_msgqueue_e:
        return controller_msgqueue_s;

      case controller_resource_limit_type_nice_e:
        return controller_nice_s;

      case controller_resource_limit_type_nofile_e:
        return controller_nofile_s;

      case controller_resource_limit_type_nproc_e:
        return controller_nproc_s;

      case controller_resource_limit_type_rss_e:
        return controller_rss_s;

      case controller_resource_limit_type_rtprio_e:
        return controller_rtprio_s;

      case controller_resource_limit_type_rttime_e:
        return controller_rttime_s;

      case controller_resource_limit_type_sigpending_e:
        return controller_sigpending_s;

      case controller_resource_limit_type_stack_e:
        return controller_stack_s;
    }

    return f_string_empty_s;
  }
#endif // _di_controller_rule_setting_limit_type_name_

#ifndef _di_controller_rule_setting_read_
  f_status_t controller_rule_setting_read(controller_global_t * const global, const bool is_normal, controller_cache_t * const cache, controller_rule_t * const rule) {

    if (!global || !cache || !rule) return F_status_set_error(F_parameter);

    f_status_t status = F_okay;
    f_status_t status_return = F_okay;

    f_range_t range = macro_f_range_t_initialize_2(cache->buffer_item.used);
    f_range_t range2 = f_range_t_initialize;

    controller_interrupt_t custom = macro_controller_interrupt_t_initialize_1(is_normal, global);
    f_state_t state = macro_f_state_t_initialize_1(controller_allocation_large_d, controller_allocation_small_d, F_okay, 0, 0, 0, &controller_thread_signal_state_fss, 0, (void *) &custom, 0);

    fll_fss_extended_read(cache->buffer_item, &range, &cache->object_actions, &cache->content_actions, 0, 0, &cache->delimits, 0, &state);

    if (F_status_is_error(status)) {
      controller_print_rule_error(global->error, cache->action, F_status_set_fine(status), "fll_fss_extended_read", F_true, F_false);

      return status;
    }

    f_string_dynamic_t *setting_value = 0;
    f_string_dynamics_t *setting_values = 0;
    f_string_maps_t *setting_maps = 0;

    f_number_unsigned_t i = 0;
    f_number_unsigned_t j = 0;
    uint8_t type = 0;
    uint8_t action = 0;
    bool empty_disallow = F_true;

    // Save the current name item and line number to restore on return.
    const f_number_unsigned_t line_item = cache->action.line_item;
    const f_number_unsigned_t length_name_item = cache->action.name_item.used;

    f_char_t name_item[length_name_item + 1];
    name_item[length_name_item] = 0;

    memcpy(name_item, cache->action.name_item.string, sizeof(f_char_t) * length_name_item);

    for (; i < cache->content_actions.used; ++i, type = 0) {

      // The name_action is used to store all setting values for a single setting.
      cache->action.name_action.used = 0;

      // The name_item is used to store the setting name.
      cache->action.name_item.used = 0;

      status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->object_actions.array[i], &cache->action.name_item);

      if (F_status_is_error(status)) {
        controller_print_rule_error(global->error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false);

        if (F_status_set_fine(status) == F_memory_not) {
          status_return = status;

          break;
        }

        if (F_status_is_error_not(status_return)) {
          status_return = status;
        }

        // Get the current line number within the settings item.
        cache->action.line_item = line_item;
        f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global->main->setting.state);

        cache->action.line_action = ++cache->action.line_item;

        controller_print_rule_item_error(global->error, cache->action, F_false, F_status_set_fine(status));

        continue;
      }

      empty_disallow = F_true;

      if (f_compare_dynamic(controller_affinity_s, cache->action.name_item) == F_equal_to) {
        type = controller_rule_setting_type_affinity_e;
      }
      else if (f_compare_dynamic(controller_capability_s, cache->action.name_item) == F_equal_to) {
        type = controller_rule_setting_type_capability_e;
      }
      else if (f_compare_dynamic(controller_cgroup_s, cache->action.name_item) == F_equal_to) {
        type = controller_rule_setting_type_cgroup_e;
      }
      else if (f_compare_dynamic(controller_define_s, cache->action.name_item) == F_equal_to) {
        type = controller_rule_setting_type_define_e;
      }
      else if (f_compare_dynamic(controller_engine_s, cache->action.name_item) == F_equal_to) {
        type = controller_rule_setting_type_engine_e;
      }
      else if (f_compare_dynamic(controller_environment_s, cache->action.name_item) == F_equal_to) {
        type = controller_rule_setting_type_environment_e;
        empty_disallow = F_false;
      }
      else if (f_compare_dynamic(controller_group_s, cache->action.name_item) == F_equal_to) {
        type = controller_rule_setting_type_group_e;
      }
      else if (f_compare_dynamic(controller_limit_s, cache->action.name_item) == F_equal_to) {
        type = controller_rule_setting_type_limit_e;
      }
      else if (f_compare_dynamic(controller_name_s, cache->action.name_item) == F_equal_to) {
        type = controller_rule_setting_type_name_e;
      }
      else if (f_compare_dynamic(controller_nice_s, cache->action.name_item) == F_equal_to) {
        type = controller_rule_setting_type_nice_e;
      }
      else if (f_compare_dynamic(controller_on_s, cache->action.name_item) == F_equal_to) {
        type = controller_rule_setting_type_on_e;
      }
      else if (f_compare_dynamic(controller_parameter_s, cache->action.name_item) == F_equal_to) {
        type = controller_rule_setting_type_parameter_e;
      }
      else if (f_compare_dynamic(controller_path_s, cache->action.name_item) == F_equal_to) {
        type = controller_rule_setting_type_path_e;
      }
      else if (f_compare_dynamic(controller_scheduler_s, cache->action.name_item) == F_equal_to) {
        type = controller_rule_setting_type_scheduler_e;
      }
      else if (f_compare_dynamic(controller_timeout_s, cache->action.name_item) == F_equal_to) {
        type = controller_rule_setting_type_timeout_e;
      }
      else if (f_compare_dynamic(controller_user_s, cache->action.name_item) == F_equal_to) {
        type = controller_rule_setting_type_user_e;
      }
      else {
        if (global->main->program.warning.verbosity == f_console_verbosity_debug_e) {

          // Get the current line number within the settings item.
          cache->action.line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global->main->setting.state);

          cache->action.line_action = ++cache->action.line_item;

          controller_lock_print(global->main->program.warning.to, global->thread);

          fl_print_format("%r%[%QUnknown rule setting '%]", global->main->program.warning.to, f_string_eol_s, global->main->program.warning.context, global->main->program.warning.prefix, global->main->program.warning.context);
          fl_print_format(f_string_format_Q_single_s.string, global->main->program.warning.to, global->main->program.warning.notable, cache->action.name_item, global->main->program.warning.notable);
          fl_print_format(f_string_format_sentence_end_quote_s.string, global->main->program.warning.to, global->main->program.warning.context, global->main->program.warning.context, f_string_eol_s);

          controller_print_rule_error_cache(&global->main->program.warning, cache->action, F_false);

          controller_unlock_print_flush(global->main->program.warning.to, global->thread);
        }

        continue;
      }

      if (cache->content_actions.array[i].used) {
        range2.start = cache->content_actions.array[i].array[0].start;
        range2.stop = cache->content_actions.array[i].array[cache->content_actions.array[i].used - 1].stop;

        status = f_string_dynamic_partial_append_nulless(cache->buffer_item, range2, &cache->action.name_action);

        if (F_status_is_error(status)) {
          controller_print_rule_error(global->error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false);

          // Get the current line number within the settings item.
          cache->action.line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global->main->setting.state);

          cache->action.line_action = ++cache->action.line_item;

          controller_print_rule_item_error(global->error, cache->action, F_false, F_status_set_fine(status));

          if (F_status_set_fine(status) == F_memory_not) {
            status_return = status;

            break;
          }

          if (F_status_is_error_not(status_return)) {
            status_return = status;
          }

          continue;
        }
      }
      else {
        if (empty_disallow) {
          if (global->main->program.warning.verbosity == f_console_verbosity_debug_e) {

            // Get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global->main->setting.state);

            cache->action.line_action = ++cache->action.line_item;

            controller_lock_print(global->main->program.warning.to, global->thread);

            fl_print_format("%r%[%QEmpty rule setting.%]%r", global->main->program.warning.to, f_string_eol_s, global->main->program.warning.context, global->main->program.warning.prefix, global->main->program.warning.context, f_string_eol_s);

            controller_print_rule_error_cache(&global->main->program.warning, cache->action, F_false);

            controller_unlock_print_flush(global->main->program.warning.to, global->thread);
          }

          continue;
        }
      }

      if (type == controller_rule_setting_type_affinity_e) {
        if (!cache->content_actions.array[i].used) {
          controller_print_rule_setting_read_error(&global->main->program.error, "requires one or more Content", i, line_item, global->thread, cache);

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        rule->affinity.used = 0;

        f_number_signed_t number = 0;

        for (j = 0; j < cache->content_actions.array[i].used; ++j, number = 0) {

          status = f_memory_array_increase(controller_allocation_small_d, sizeof(int32_t), (void **) &rule->affinity.array, &rule->affinity.used, &rule->affinity.size);

          if (F_status_is_error(status)) {
            controller_print_rule_error(global->error, cache->action, F_status_set_fine(status), "f_memory_array_increase", F_true, F_false);

            break;
          }

          status = fl_conversion_dynamic_partial_to_signed_detect(fl_conversion_data_base_10_c, cache->buffer_item, cache->content_actions.array[i].array[j], &number);

          if (F_status_set_fine(status) == F_number_positive) {
            status = fl_conversion_dynamic_partial_to_signed_detect(fl_conversion_data_base_10_c, cache->buffer_item, controller_range_after_number_sign(cache->buffer_item, cache->content_actions.array[i].array[j]), &number);

            // Restore error on parameter problem.
            if (F_status_set_fine(status) == F_parameter) {
              status = F_status_set_error(F_number_positive);
            }
          }

          if (F_status_is_error(status)) {
            status = F_status_set_fine(status);

            if (status == F_data_not || status == F_number || status == F_number_overflow || status == F_number_underflow || status == F_number_negative || status == F_number_decimal) {
              if (status == F_number_underflow) {
                controller_print_rule_setting_read_error_with_range(&global->main->program.error, " has an unsupported number", cache->content_actions.array[i].array[j], ", the number is too small for this system", i, line_item, global->thread, cache);
              }
              else if (status == F_number_overflow || status == F_number_positive) {
                controller_print_rule_setting_read_error_with_range(&global->main->program.error, " has an unsupported number", cache->content_actions.array[i].array[j], ", the number is too large for this system", i, line_item, global->thread, cache);
              }
              else {
                controller_print_rule_setting_read_error_with_range(&global->main->program.error, " has an invalid number", cache->content_actions.array[i].array[j], ", only whole numbers are allowed for an affinity value", i, line_item, global->thread, cache);
              }

              status = F_status_set_error(F_valid_not);

              if (F_status_is_error_not(status_return)) {
                status_return = status;
              }
            }
            else {
              controller_print_rule_error(global->error, cache->action, F_status_set_fine(status), "fl_conversion_dynamic_partial_to_signed_detect", F_true, F_false);

              status = F_status_set_error(status);

              if (F_status_is_error_not(status_return)) {
                status_return = status;
              }
            }

            continue;
          }

          rule->affinity.array[rule->affinity.used++] = number;
        } // for

        controller_print_rule_setting_read_values(global, controller_affinity_s, i, cache);

        continue;
      }

      if (type == controller_rule_setting_type_define_e || type == controller_rule_setting_type_parameter_e) {
        if (cache->content_actions.array[i].used != 2) {
          controller_print_rule_setting_read_error(&global->main->program.error, "requires exactly two Content", i, line_item, global->thread, cache);

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        if (type == controller_rule_setting_type_define_e) {
          setting_maps = &rule->define;
        }
        else if (type == controller_rule_setting_type_parameter_e) {
          setting_maps = &rule->parameter;
        }

        status = f_memory_array_increase(controller_allocation_small_d, sizeof(f_string_map_t), (void **) &setting_maps->array, &setting_maps->used, &setting_maps->size);

        if (F_status_is_error(status)) {
          controller_print_rule_error(global->error, cache->action, F_status_set_fine(status), "f_memory_array_increase", F_true, F_false);

          if (F_status_set_fine(status) == F_memory_not) {
            status_return = status;

            break;
          }

          if (F_status_is_error_not(status_return)) {
            status_return = status;
          }

          // Get the current line number within the settings item.
          cache->action.line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global->main->setting.state);

          cache->action.line_action = ++cache->action.line_item;

          controller_print_rule_item_error(global->error, cache->action, F_false, F_status_set_fine(status));

          continue;
        }

        setting_maps->array[setting_maps->used].key.used = 0;
        setting_maps->array[setting_maps->used].value.used = 0;

        status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[0], &setting_maps->array[setting_maps->used].key);

        if (F_status_is_error(status)) {
          controller_print_rule_error(global->error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false);

          if (F_status_set_fine(status) == F_memory_not) {
            status_return = status;
            break;
          }

          if (F_status_is_error_not(status_return)) {
            status_return = status;
          }

          // Get the current line number within the settings item.
          cache->action.line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global->main->setting.state);

          cache->action.line_action = ++cache->action.line_item;

          controller_print_rule_item_error(global->error, cache->action, F_false, F_status_set_fine(status));

          continue;
        }

        status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[1], &setting_maps->array[setting_maps->used].value);

        if (F_status_is_error(status)) {
          controller_print_rule_error(global->error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false);

          if (F_status_set_fine(status) == F_memory_not) {
            status_return = status;

            break;
          }

          if (F_status_is_error_not(status_return)) {
            status_return = status;
          }

          // Get the current line number within the settings item.
          cache->action.line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global->main->setting.state);

          cache->action.line_action = ++cache->action.line_item;

          controller_print_rule_item_error(global->error, cache->action, F_false, F_status_set_fine(status));

          continue;
        }

        controller_print_rule_setting_read_mapping(global, type == controller_rule_setting_type_define_e ? controller_define_s : controller_parameter_s, setting_maps->array[setting_maps->used]);

        ++setting_maps->used;

        continue;
      }

      if (type == controller_rule_setting_type_cgroup_e) {
        if (cache->content_actions.array[i].used < 2 || rule->has & controller_rule_has_cgroup_d) {
          controller_print_rule_setting_read_error(&global->main->program.error, "requires two or more Content", i, line_item, global->thread, cache);

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        if (f_compare_dynamic_partial_string(controller_existing_s.string, cache->buffer_item, controller_existing_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          rule->cgroup.as_new = F_false;
        }
        else if (f_compare_dynamic_partial_string(controller_new_s.string, cache->buffer_item, controller_new_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          rule->cgroup.as_new = F_true;
        }
        else {
          controller_print_rule_setting_read_error_with_range(&global->main->program.error, " has an unknown option", cache->content_actions.array[i].array[0], "", i, line_item, global->thread, cache);

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        rule->cgroup.path.used = 0;

        status = f_string_dynamic_append(global->program->path_cgroup, &rule->cgroup.path);

        if (F_status_is_error(status)) {
          controller_print_rule_error(global->error, cache->action, F_status_set_fine(status), "f_string_dynamic_append", F_true, F_false);
        }
        else {
          rule->cgroup.groups.used = 0;

          for (j = 1; j < cache->content_actions.array[i].used; ++j) {

            status = f_memory_array_increase(controller_allocation_small_d, sizeof(f_string_dynamic_t), (void **) &rule->cgroup.groups.array, &rule->cgroup.groups.used, &rule->cgroup.groups.size);

            if (F_status_is_error(status)) {
              controller_print_rule_error(global->error, cache->action, F_status_set_fine(status), "f_memory_array_increase", F_true, F_false);

              break;
            }

            rule->cgroup.groups.array[rule->cgroup.groups.used].used = 0;

            status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[j], &rule->cgroup.groups.array[rule->cgroup.groups.used]);

            if (F_status_is_error(status)) {
              controller_print_rule_error(global->error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false);

              break;
            }

            ++rule->cgroup.groups.used;
          } // for
        }

        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) == F_memory_not) {
            status_return = status;

            break;
          }

          rule->cgroup.path.used = 0;

          if (F_status_is_error_not(status_return)) {
            status_return = status;
          }

          // Get the current line number within the settings item.
          cache->action.line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global->main->setting.state);

          cache->action.line_action = ++cache->action.line_item;

          controller_print_rule_item_error(global->error, cache->action, F_false, F_status_set_fine(status));

          continue;
        }

        rule->has |= controller_rule_has_cgroup_d;

        controller_print_rule_setting_read_values(global, controller_cgroup_s, i, cache);

        continue;
      }

      if (type == controller_rule_setting_type_limit_e) {
        if (cache->content_actions.array[i].used != 3) {
          controller_print_rule_setting_read_error(&global->main->program.error, "requires three Content", i, line_item, global->thread, cache);

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        if (f_compare_dynamic_partial_string(controller_as_s.string, cache->buffer_item, controller_as_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_as_e;
        }
        else if (f_compare_dynamic_partial_string(controller_core_s.string, cache->buffer_item, controller_core_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_core_e;
        }
        else if (f_compare_dynamic_partial_string(controller_cpu_s.string, cache->buffer_item, controller_cpu_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_cpu_e;
        }
        else if (f_compare_dynamic_partial_string(controller_data_s.string, cache->buffer_item, controller_data_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_data_e;
        }
        else if (f_compare_dynamic_partial_string(controller_fsize_s.string, cache->buffer_item, controller_fsize_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_fsize_e;
        }
        else if (f_compare_dynamic_partial_string(controller_locks_s.string, cache->buffer_item, controller_locks_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_locks_e;
        }
        else if (f_compare_dynamic_partial_string(controller_memlock_s.string, cache->buffer_item, controller_memlock_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_memlock_e;
        }
        else if (f_compare_dynamic_partial_string(controller_msgqueue_s.string, cache->buffer_item, controller_msgqueue_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_msgqueue_e;
        }
        else if (f_compare_dynamic_partial_string(controller_nice_s.string, cache->buffer_item, controller_nice_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_nice_e;
        }
        else if (f_compare_dynamic_partial_string(controller_nofile_s.string, cache->buffer_item, controller_nofile_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_nofile_e;
        }
        else if (f_compare_dynamic_partial_string(controller_nproc_s.string, cache->buffer_item, controller_nproc_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_nproc_e;
        }
        else if (f_compare_dynamic_partial_string(controller_rss_s.string, cache->buffer_item, controller_rss_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_rss_e;
        }
        else if (f_compare_dynamic_partial_string(controller_rtprio_s.string, cache->buffer_item, controller_rtprio_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_rtprio_e;
        }
        else if (f_compare_dynamic_partial_string(controller_rttime_s.string, cache->buffer_item, controller_rttime_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_rttime_e;
        }
        else if (f_compare_dynamic_partial_string(controller_sigpending_s.string, cache->buffer_item, controller_sigpending_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_sigpending_e;
        }
        else if (f_compare_dynamic_partial_string(controller_stack_s.string, cache->buffer_item, controller_stack_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_stack_e;
        }
        else {
          if (global->main->program.error.verbosity == f_console_verbosity_debug_e) {

            // Get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global->main->setting.state);

            cache->action.line_action = ++cache->action.line_item;

            controller_lock_print(global->main->program.error.to, global->thread);

            fl_print_format("%r%[%QUnknown resource limit type '%]", global->main->program.error.to, f_string_eol_s, global->main->program.error.context, global->main->program.error.prefix, global->main->program.error.context);
            fl_print_format(f_string_format_Q_single_s.string, global->main->program.error.to, global->main->program.error.notable, cache->action.name_action, global->main->program.error.notable);
            fl_print_format(f_string_format_sentence_end_quote_s.string, global->main->program.error.to, global->main->program.error.context, global->main->program.error.context, f_string_eol_s);

            controller_print_rule_error_cache(global->error, cache->action, F_true);

            controller_unlock_print_flush(global->main->program.error.to, global->thread);
          }

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        for (j = 0; j < rule->limits.used; ++j) {

          if (type == rule->limits.array[j].type) {
            if (global->main->program.error.verbosity > f_console_verbosity_quiet_e) {

              // Get the current line number within the settings item.
              cache->action.line_item = line_item;
              f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global->main->setting.state);

              cache->action.line_action = ++cache->action.line_item;

              controller_lock_print(global->main->program.error.to, global->thread);

              fl_print_format("%r%[%QThe resource limit type is already specified%]%r", global->main->program.error.to, f_string_eol_s, global->main->program.error.context, global->main->program.error.prefix, global->main->program.error.context, f_string_eol_s);

              controller_print_rule_error_cache(global->error, cache->action, F_false);

              controller_unlock_print_flush(global->main->program.error.to, global->thread);
            }

            status = F_status_set_error(F_valid_not);

            if (F_status_is_error_not(status_return)) {
              status_return = status;
            }
          }
        } // for

        if (F_status_is_error(status)) continue;

        status = f_memory_array_increase(controller_allocation_small_d, sizeof(f_limit_set_t), (void **) &rule->limits.array, &rule->limits.used, &rule->limits.size);

        if (F_status_is_error(status)) {
          controller_print_rule_error(global->error, cache->action, F_status_set_fine(status), "f_memory_array_increase", F_true, F_false);

          if (F_status_set_fine(status) == F_memory_not) {
            status_return = status;

            break;
          }

          if (F_status_is_error_not(status_return)) {
            status_return = status;
          }

          // Get the current line number within the settings item.
          cache->action.line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global->main->setting.state);

          cache->action.line_action = ++cache->action.line_item;

          controller_print_rule_item_error(global->error, cache->action, F_false, F_status_set_fine(status));

          continue;
        }

        f_number_signed_t number = 0;

        for (j = 1; j < 3; ++j, number = 0) {

          status = fl_conversion_dynamic_partial_to_signed_detect(fl_conversion_data_base_10_c, cache->buffer_item, cache->content_actions.array[i].array[j], &number);

          if (F_status_set_fine(status) == F_number_positive) {
            status = fl_conversion_dynamic_partial_to_signed_detect(fl_conversion_data_base_10_c, cache->buffer_item, controller_range_after_number_sign(cache->buffer_item, cache->content_actions.array[i].array[j]), &number);

            // Restore error on parameter problem.
            if (F_status_set_fine(status) == F_parameter) {
              status = F_status_set_error(F_number_positive);
            }
          }

          if (F_status_is_error(status)) {
            status = F_status_set_fine(status);

            if (status == F_data_not || status == F_number || status == F_number_overflow || status == F_number_underflow || status == F_number_negative || status == F_number_positive || status == F_number_decimal) {
              if (status == F_number_underflow) {
                controller_print_rule_setting_read_error_with_range(&global->main->program.error, " has an unsupported number", cache->content_actions.array[i].array[j], ", the number is too small for this system", i, line_item, global->thread, cache);
              }
              else if (status == F_number_overflow) {
                controller_print_rule_setting_read_error_with_range(&global->main->program.error, " has an unsupported number", cache->content_actions.array[i].array[j], ", the number is too large for this system", i, line_item, global->thread, cache);
              }
              else {
                controller_print_rule_setting_read_error_with_range(&global->main->program.error, " has an unsupported number", cache->content_actions.array[i].array[j], ", only whole numbers are allowed for a resource limit value", i, line_item, global->thread, cache);
              }

              status = F_status_set_error(F_valid_not);

              if (F_status_is_error_not(status_return)) {
                status_return = status;
              }
            }
            else {
              controller_print_rule_error(global->error, cache->action, F_status_set_fine(status), "fl_conversion_dynamic_partial_to_signed_detect", F_true, F_false);

              status = F_status_set_error(status);

              if (F_status_is_error_not(status_return)) {
                status_return = status;
              }
            }

            break;
          }

          if (j == 1) {
            rule->limits.array[rule->limits.used].value.rlim_cur = number;
          }
          else {
            rule->limits.array[rule->limits.used].value.rlim_max = number;
          }
        } // for

        if (F_status_is_error(status)) continue;

        rule->limits.array[rule->limits.used++].type = type;

        controller_print_rule_setting_read_values(global, controller_limit_s, i, cache);

        continue;
      }

      if (type == controller_rule_setting_type_name_e || type == controller_rule_setting_type_path_e || type == controller_rule_setting_type_engine_e) {

        if (type == controller_rule_setting_type_name_e) {
          setting_value = &rule->name;
        }
        else if (type == controller_rule_setting_type_path_e) {
          setting_value = &rule->path;
        }
        else if (type == controller_rule_setting_type_engine_e) {
          setting_value = &rule->engine;
        }

        if (setting_value->used || !cache->content_actions.array[i].used) {
          controller_print_rule_setting_read_error(&global->main->program.error, "requires one or more Content", i, line_item, global->thread, cache);

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        if (type == controller_rule_setting_type_name_e || type == controller_rule_setting_type_engine_e) {
          status = f_rip_dynamic_partial_nulless(cache->buffer_item, cache->content_actions.array[i].array[0], setting_value);

          if (type == controller_rule_setting_type_engine_e) {
            rule->engine_arguments.used = 0;

            if (cache->content_actions.array[i].used > 1) {
              status = f_memory_array_increase_by(cache->content_actions.array[i].used - 1, sizeof(f_string_dynamic_t), (void **) &rule->engine_arguments.array, &rule->engine_arguments.used, &rule->engine_arguments.size);

              for (j = 1; F_status_is_error_not(status) && j < cache->content_actions.array[i].used; ++j, ++rule->engine_arguments.used) {

                rule->engine_arguments.array[rule->engine_arguments.used].used = 0;

                status = f_string_dynamic_partial_append(cache->buffer_item, cache->content_actions.array[i].array[j], &rule->engine_arguments.array[rule->engine_arguments.used]);
              } // for
            }
          }

          if (F_status_is_error(status)) {
            setting_value->used = 0;

            if (type == controller_rule_setting_type_engine_e) {
              rule->engine_arguments.used = 0;
            }

            if (F_status_set_fine(status) == F_memory_not) {
              status_return = status;

              break;
            }

            if (F_status_is_error_not(status_return)) {
              status_return = status;
            }

            // Get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global->main->setting.state);

            cache->action.line_action = ++cache->action.line_item;

            controller_print_rule_item_error(global->error, cache->action, F_false, F_status_set_fine(status));

            continue;
          }

          status = controller_validate_has_graph(*setting_value);

          if (status == F_false || F_status_set_fine(status) == F_complete_not_utf) {
            if (global->main->program.error.verbosity > f_console_verbosity_quiet_e) {

              // Get the current line number within the settings item.
              cache->action.line_item = line_item;
              f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global->main->setting.state);

              cache->action.line_action = ++cache->action.line_item;
            }

            if (status == F_false) {
              if (global->main->program.error.verbosity > f_console_verbosity_quiet_e) {
                controller_lock_print(global->main->program.error.to, global->thread);

                fl_print_format("%r%[%QRule setting has an invalid name '%]", global->main->program.error.to, f_string_eol_s, global->main->program.error.context, global->main->program.error.prefix, global->main->program.error.context);
                fl_print_format(f_string_format_Q_single_s.string, global->main->program.error.to, global->main->program.error.notable, *setting_value, global->main->program.error.notable);
                fl_print_format("%[', there must be at least 1 graph character.%]%r", global->main->program.error.to, global->main->program.error.context, global->main->program.error.context, f_string_eol_s);

                controller_print_rule_error_cache(global->error, cache->action, F_false);

                controller_unlock_print_flush(global->main->program.error.to, global->thread);
              }

              if (F_status_is_error_not(status_return)) {
                status_return = F_status_set_error(F_valid_not);
              }
            }
            else {

              // This function should only return F_complete_not_utf on error.
              controller_print_rule_error(global->error, cache->action, F_complete_not_utf, "controller_validate_has_graph", F_true, F_false);

              if (F_status_is_error_not(status_return)) {
                status_return = status;
              }

              controller_print_rule_item_error(global->error, cache->action, F_false, F_status_set_fine(status));
            }

            setting_value->used = 0;

            continue;
          }

          controller_print_rule_setting_read_value(global, type == controller_rule_setting_type_name_e ? controller_name_s : controller_engine_s, f_string_empty_s, *setting_value, 0);
        }
        else if (type == controller_rule_setting_type_path_e) {
          status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[0], setting_value);

          if (F_status_is_error(status)) {
            controller_print_rule_error(global->error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false);

            if (F_status_set_fine(status) == F_memory_not) {
              status_return = status;

              break;
            }

            if (F_status_is_error_not(status_return)) {
              status_return = status;
            }

            setting_value->used = 0;

            // Get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global->main->setting.state);

            cache->action.line_action = ++cache->action.line_item;

            controller_print_rule_item_error(global->error, cache->action, F_false, F_status_set_fine(status));

            continue;
          }

          controller_print_rule_setting_read_value(global, controller_path_s, f_string_empty_s, *setting_value, 0);
        }

        continue;
      }

      if (type == controller_rule_setting_type_scheduler_e) {
        if (cache->content_actions.array[i].used < 1 || cache->content_actions.array[i].used > 2 || rule->has & controller_rule_has_scheduler_d) {
          controller_print_rule_setting_read_error(&global->main->program.error, "requires either one or two Content", i, line_item, global->thread, cache);

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        if (f_compare_dynamic_partial_string(controller_batch_s.string, cache->buffer_item, controller_batch_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          rule->scheduler.policy = SCHED_BATCH;
          rule->scheduler.priority = 0;
        }
        else if (f_compare_dynamic_partial_string(controller_deadline_s.string, cache->buffer_item, controller_deadline_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          rule->scheduler.policy = SCHED_DEADLINE;
          rule->scheduler.priority = 49;
        }
        else if (f_compare_dynamic_partial_string(controller_fifo_s.string, cache->buffer_item, controller_fifo_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          rule->scheduler.policy = SCHED_FIFO;
          rule->scheduler.priority = 49;
        }
        else if (f_compare_dynamic_partial_string(controller_idle_s.string, cache->buffer_item, controller_idle_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          rule->scheduler.policy = SCHED_IDLE;
          rule->scheduler.priority = 0;
        }
        else if (f_compare_dynamic_partial_string(controller_other_s.string, cache->buffer_item, controller_other_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          rule->scheduler.policy = SCHED_OTHER;
          rule->scheduler.priority = 0;
        }
        else if (f_compare_dynamic_partial_string(controller_round_robin_s.string, cache->buffer_item, controller_round_robin_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          rule->scheduler.policy = SCHED_RR;
          rule->scheduler.priority = 49;
        }
        else {
          controller_print_rule_setting_read_error_with_range(&global->main->program.error, " has an unknown scheduler", cache->content_actions.array[i].array[0], "", i, line_item, global->thread, cache);

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        if (cache->content_actions.array[i].used > 1) {
          const bool zero_only = rule->scheduler.policy == SCHED_BATCH || rule->scheduler.policy == SCHED_IDLE || rule->scheduler.policy == SCHED_OTHER;

          f_number_signed_t number = 0;

          status = fl_conversion_dynamic_partial_to_signed_detect(fl_conversion_data_base_10_c, cache->buffer_item, cache->content_actions.array[i].array[1], &number);

          if (F_status_set_fine(status) == F_number_positive) {
            status = fl_conversion_dynamic_partial_to_signed_detect(fl_conversion_data_base_10_c, cache->buffer_item, controller_range_after_number_sign(cache->buffer_item, cache->content_actions.array[i].array[1]), &number);

            // Restore error on parameter problem.
            if (F_status_set_fine(status) == F_parameter) {
              status = F_status_set_error(F_number_positive);
            }
          }

          if (F_status_is_error(status) || (zero_only && number) || (!zero_only && (number < 1 || number > 99))) {
            status = F_status_set_fine(status);

            if ((zero_only && number) || (!zero_only && (number < 1 || number > 99)) || status == F_data_not || status == F_number || status == F_number_overflow || status == F_number_negative || status == F_number_positive) {
              if (global->main->program.error.verbosity > f_console_verbosity_quiet_e) {

                // Get the current line number within the settings item.
                cache->action.line_item = line_item;
                f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global->main->setting.state);

                cache->action.line_action = ++cache->action.line_item;

                controller_lock_print(global->main->program.error.to, global->thread);

                fl_print_format("%r%[%QRule setting has an invalid number '%]", global->main->program.error.to, f_string_eol_s, global->main->program.error.context, global->main->program.error.prefix, global->main->program.error.context);
                fl_print_format(f_string_format_Q_range_single_s.string, global->main->program.error.to, global->main->program.error.notable, cache->buffer_item, cache->content_actions.array[i].array[1], global->main->program.error.notable);

                if (zero_only) {
                  fl_print_format("%[', only%] ", global->main->program.error.to, global->main->program.error.context, global->main->program.error.context);
                  fl_print_format("%[0%]%[ is", global->main->program.error.to, global->main->program.error.notable, global->main->program.error.notable, global->main->program.error.context);
                }
                else {
                  fl_print_format("%[', only the whole numbers inclusively between%] ", global->main->program.error.to, global->main->program.error.context, global->main->program.error.context);
                  fl_print_format("%[1%] %[and%] ", global->main->program.error.to, global->main->program.error.notable, global->main->program.error.notable, global->main->program.error.context, global->main->program.error.context);
                  fl_print_format("%[99%] %[are", global->main->program.error.to, global->main->program.error.notable, global->main->program.error.notable, global->main->program.error.context);
                }

                fl_print_format(" allowed for the designated scheduler.%]%r", global->main->program.error.to, global->main->program.error.context, global->main->program.error.context, f_string_eol_s);

                controller_print_rule_error_cache(global->error, cache->action, F_false);

                controller_unlock_print_flush(global->main->program.error.to, global->thread);
              }

              if (F_status_is_error_not(status_return)) {
                status_return = F_status_set_error(F_valid_not);
              }
            }
            else {
              controller_print_rule_error(global->error, cache->action, status, "fl_conversion_dynamic_partial_to_signed_detect", F_true, F_false);
              status = F_status_set_error(status);

              if (F_status_is_error_not(status_return)) {
                status_return = status;
              }
            }

            continue;
          }

          rule->scheduler.priority = number;
        }

        rule->has |= controller_rule_has_scheduler_d;

        controller_print_rule_setting_read_values(global, controller_scheduler_s, i, cache);

        continue;
      }

      if (type == controller_rule_setting_type_timeout_e) {
        if (cache->content_actions.array[i].used != 2) {
          controller_print_rule_setting_read_error(&global->main->program.error, "requires exactly two Content", i, line_item, global->thread, cache);

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        uint8_t timeout_code = 0;

        if (f_compare_dynamic_partial_string(controller_kill_s.string, cache->buffer_item, controller_kill_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          timeout_code = controller_rule_timeout_code_kill_d;
        }
        else if (f_compare_dynamic_partial_string(controller_start_s.string, cache->buffer_item, controller_start_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          timeout_code = controller_rule_timeout_code_start_d;
        }
        else if (f_compare_dynamic_partial_string(controller_stop_s.string, cache->buffer_item, controller_stop_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          timeout_code = controller_rule_timeout_code_stop_d;
        }
        else {
          if (global->main->program.error.verbosity > f_console_verbosity_quiet_e) {

            // Get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global->main->setting.state);

            cache->action.line_action = ++cache->action.line_item;

            controller_lock_print(global->main->program.error.to, global->thread);

            fl_print_format("%r%[%QRule setting's first value has '%]", global->main->program.error.to, f_string_eol_s, global->main->program.error.context, global->main->program.error.prefix, global->main->program.error.context);
            fl_print_format(f_string_format_Q_range_single_s.string, global->main->program.error.to, global->main->program.error.notable, cache->buffer_item, cache->content_actions.array[i].array[0], global->main->program.error.notable);
            fl_print_format("%[' but only supports %r, %r, and %r.%]%r", global->main->program.error.to, global->main->program.error.context, controller_kill_s, controller_start_s, controller_stop_s, global->main->program.error.context, f_string_eol_s);

            controller_print_rule_error_cache(global->error, cache->action, F_false);

            controller_unlock_print_flush(global->main->program.error.to, global->thread);
          }

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        f_number_unsigned_t number = 0;

        status = fl_conversion_dynamic_partial_to_unsigned_detect(fl_conversion_data_base_10_c, cache->buffer_item, cache->content_actions.array[i].array[1], &number);

        if (F_status_set_fine(status) == F_number_positive) {
          status = fl_conversion_dynamic_partial_to_unsigned_detect(fl_conversion_data_base_10_c, cache->buffer_item, controller_range_after_number_sign(cache->buffer_item, cache->content_actions.array[i].array[1]), &number);

          // Restore error on parameter problem.
          if (F_status_set_fine(status) == F_parameter) {
            status = F_status_set_error(F_number_positive);
          }
        }

        if (F_status_is_error(status)) {
          status = F_status_set_fine(status);

          if (status == F_number_overflow) {
            controller_print_rule_setting_read_error_with_range(&global->main->program.error, " has an unsupported number", cache->content_actions.array[i].array[1], ", the number is too large for this system", i, line_item, global->thread, cache);
          }
          else if (status == F_data_not || status == F_number || status == F_number_underflow || status == F_number_negative || status == F_number_positive || status == F_number_decimal) {
            controller_print_rule_setting_read_error_with_range(&global->main->program.error, " has an invalid number", cache->content_actions.array[i].array[1], ", only positive whole numbers are allowed", i, line_item, global->thread, cache);
          }
          else {

            // Get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global->main->setting.state);

            cache->action.line_action = ++cache->action.line_item;

            controller_print_rule_error(global->error, cache->action, status, "fl_conversion_dynamic_partial_to_signed_detect", F_true, F_false);
          }

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }
        }
        else {
          if (timeout_code == controller_rule_timeout_code_kill_d) {
            rule->timeout_kill = number;
          }
          else if (timeout_code == controller_rule_timeout_code_start_d) {
            rule->timeout_start = number;
          }
          else {
            rule->timeout_stop = number;
          }

          if (global->main->program.error.verbosity == f_console_verbosity_debug_e || (global->main->program.error.verbosity == f_console_verbosity_verbose_e && (global->main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e))) {
            f_string_static_t name_sub = controller_stop_s;

            if (timeout_code == controller_rule_timeout_code_kill_d) {
              name_sub = controller_kill_s;
            }
            else if (timeout_code == controller_rule_timeout_code_start_d) {
              name_sub = controller_start_s;
            }

            cache->action.generic.used = 0;

            status = f_rip_dynamic_partial_nulless(cache->buffer_item, cache->content_actions.array[i].array[1], &cache->action.generic);

            if (F_status_is_error(status)) {
              controller_print_error_status(&global->main->program.error, macro_controller_f(f_rip_dynamic_partial_nulless), F_status_set_fine(status));

              break;
            }

            controller_print_rule_setting_read_value(global, controller_timeout_s, name_sub, cache->action.generic, 0);
          }
        }

        continue;
      }

      if (type == controller_rule_setting_type_capability_e || type == controller_rule_setting_type_nice_e || type == controller_rule_setting_type_user_e) {
        if (cache->content_actions.array[i].used != 1 || type == controller_rule_setting_type_capability_e && rule->capability || type == controller_rule_setting_type_group_e && (rule->has & controller_rule_has_group_d) || type == controller_rule_setting_type_nice_e && (rule->has & controller_rule_has_nice_d) || type == controller_rule_setting_type_user_e && (rule->has & controller_rule_has_user_d)) {
          controller_print_rule_setting_read_error(&global->main->program.error, "requires exactly one Content", i, line_item, global->thread, cache);

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        if (type == controller_rule_setting_type_capability_e) {
          cache->action.generic.used = 0;

          status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[0], &cache->action.generic);

          if (F_status_is_error(status)) {

            // Get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global->main->setting.state);

            cache->action.line_action = ++cache->action.line_item;

            controller_lock_print(global->main->program.error.to, global->thread);

            controller_print_rule_error(global->error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false);

            controller_print_rule_error_cache(global->error, cache->action, F_false);

            controller_unlock_print_flush(global->main->program.error.to, global->thread);

            if (F_status_set_fine(status) == F_memory_not) {
              status_return = status;

              break;
            }

            if (F_status_is_error_not(status_return)) {
              status_return = F_status_set_error(F_valid_not);
            }
          }

          status = f_capability_from_text(cache->action.generic, &rule->capability);

          if (F_status_is_error(status) && F_status_set_fine(status) != F_support_not) {
            if (F_status_set_fine(status) == F_memory_not) {

              // Get the current line number within the settings item.
              cache->action.line_item = line_item;
              f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global->main->setting.state);

              cache->action.line_action = ++cache->action.line_item;

              controller_lock_print(global->main->program.error.to, global->thread);

              controller_print_rule_error(global->error, cache->action, F_status_set_fine(status), "f_capability_from_text", F_true, F_false);

              controller_print_rule_error_cache(global->error, cache->action, F_false);

              controller_unlock_print_flush(global->main->program.error.to, global->thread);

              status_return = status;

              break;
            }

            controller_print_rule_setting_read_error(&global->main->program.error, "failed to process the capabilities", i, line_item, global->thread, cache);

            if (F_status_is_error_not(status_return)) {
              status_return = F_status_set_error(F_valid_not);
            }

            continue;
          }

          controller_print_rule_setting_read_value(global, controller_capability_s, f_string_empty_s, cache->action.generic, 0);
        }
        else if (type == controller_rule_setting_type_nice_e) {
          f_number_signed_t number = 0;

          status = fl_conversion_dynamic_partial_to_signed_detect(fl_conversion_data_base_10_c, cache->buffer_item, cache->content_actions.array[i].array[0], &number);

          if (F_status_set_fine(status) == F_number_positive) {
            status = fl_conversion_dynamic_partial_to_signed_detect(fl_conversion_data_base_10_c, cache->buffer_item, controller_range_after_number_sign(cache->buffer_item, cache->content_actions.array[i].array[0]), &number);

            // Restore error on parameter problem.
            if (F_status_set_fine(status) == F_parameter) {
              status = F_status_set_error(F_number_positive);
            }
          }

          if (F_status_is_error(status) || number < -20 || number > 19) {
            status = F_status_set_fine(status);

            if (number < -20 || number > 19 || status == F_data_not || status == F_number || status == F_number_overflow || status == F_number_underflow || status == F_number_decimal) {
              if (global->main->program.error.verbosity > f_console_verbosity_quiet_e) {

                // Get the current line number within the settings item.
                cache->action.line_item = line_item;
                f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global->main->setting.state);

                cache->action.line_action = ++cache->action.line_item;

                controller_lock_print(global->main->program.error.to, global->thread);

                fl_print_format("%r%[%QRule setting has an invalid number '%]", global->main->program.error.to, f_string_eol_s, global->main->program.error.context, global->main->program.error.prefix, global->main->program.error.context);
                fl_print_format(f_string_format_Q_range_single_s.string, global->main->program.error.to, global->main->program.error.notable, cache->buffer_item, cache->content_actions.array[i].array[0], global->main->program.error.notable);
                fl_print_format("%[', only the whole numbers inclusively between%] ", global->main->program.error.to, global->main->program.error.context, global->main->program.error.context);
                fl_print_format("%[-20%]", global->main->program.error.to, global->main->program.error.notable, global->main->program.error.notable);
                fl_print_format(" %[and%] ", global->main->program.error.to, global->main->program.error.context, global->main->program.error.context);
                fl_print_format("%[19%]", global->main->program.error.to, global->main->program.error.notable, global->main->program.error.notable);
                fl_print_format(" %[are allowed.%]%r", global->main->program.error.to, global->main->program.error.context, global->main->program.error.context, f_string_eol_s);

                controller_print_rule_error_cache(global->error, cache->action, F_false);

                controller_unlock_print_flush(global->main->program.error.to, global->thread);
              }

              if (F_status_is_error_not(status_return)) {
                status_return = F_status_set_error(F_valid_not);
              }
            }
            else {
              controller_print_rule_error(global->error, cache->action, status, "fl_conversion_dynamic_partial_to_signed_detect", F_true, F_false);
              status = F_status_set_error(status);

              if (F_status_is_error_not(status_return)) {
                status_return = status;
              }
            }
          }
          else {
            rule->nice = number;
            rule->has |= controller_rule_has_nice_d;

            if ((global->main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e) || global->main->program.error.verbosity == f_console_verbosity_verbose_e) {
              cache->action.generic.used = 0;

              status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[0], &cache->action.generic);

              if (F_status_is_error(status)) {

                // Get the current line number within the settings item.
                cache->action.line_item = line_item;
                f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global->main->setting.state);

                cache->action.line_action = ++cache->action.line_item;

                controller_lock_print(global->main->program.error.to, global->thread);

                controller_print_rule_error(global->error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false);

                controller_print_rule_error_cache(global->error, cache->action, F_false);

                controller_unlock_print_flush(global->main->program.error.to, global->thread);

                if (F_status_set_fine(status) == F_memory_not) {
                  status_return = status;

                  break;
                }

                if (F_status_is_error_not(status_return)) {
                  status_return = F_status_set_error(F_valid_not);
                }
              }

              if (F_status_is_error_not(status)) {
                controller_print_rule_setting_read_value(global, controller_nice_s, f_string_empty_s, cache->action.generic, 0);
              }
            }
          }
        }
        else if (type == controller_rule_setting_type_user_e) {
          uid_t number = 0;

          status = controller_convert_user_id(cache->buffer_item, cache->content_actions.array[i].array[0], cache, &number);

          if (F_status_is_error(status)) {
            status = F_status_set_fine(status);

            if (status == F_exist_not) {
              controller_print_rule_setting_read_error_with_range(&global->main->program.error, " has an invalid user", cache->content_actions.array[i].array[0], ", because no user was found by that name", i, line_item, global->thread, cache);
            }
            else if (status == F_number_too_large) {
              controller_print_rule_setting_read_error_with_range(&global->main->program.error, " has an invalid user", cache->content_actions.array[i].array[0], ", because the given ID is too large", i, line_item, global->thread, cache);
            }
            else if (status == F_number) {
              controller_print_rule_setting_read_error_with_range(&global->main->program.error, " has an invalid user", cache->content_actions.array[i].array[0], ", because the given ID is not a valid supported number", i, line_item, global->thread, cache);
            }
            else {

              // Get the current line number within the settings item.
              cache->action.line_item = line_item;
              f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global->main->setting.state);

              cache->action.line_action = ++cache->action.line_item;

              controller_print_rule_error(global->error, cache->action, status, "controller_convert_user_id", F_true, F_false);

              controller_print_rule_item_error(global->error, cache->action, F_false, F_status_set_fine(status));
            }

            if (F_status_is_error_not(status_return)) {
              status_return = F_status_set_error(status);
            }
          }
          else {
            rule->user = number;
            rule->has |= controller_rule_has_user_d;

            if (global->main->program.error.verbosity == f_console_verbosity_debug_e || (global->main->program.error.verbosity == f_console_verbosity_verbose_e && (global->main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e))) {
              cache->action.generic.used = 0;

              status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[0], &cache->action.generic);

              controller_print_rule_setting_read_value(global, controller_user_s, f_string_empty_s, cache->action.generic, 0);
            }
          }
        }

        continue;
      }

      if (type == controller_rule_setting_type_group_e) {
        if (!cache->content_actions.array[i].used) {
          controller_print_rule_setting_read_error(&global->main->program.error, "requires one or more Content", i, line_item, global->thread, cache);

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        gid_t number = 0;

        rule->groups.used = 0;

        for (j = 0; j < cache->content_actions.array[i].used; ++j) {

          status = f_memory_array_increase(controller_allocation_small_d, sizeof(f_int32s_t), (void **) &rule->groups.array, &rule->groups.used, &rule->groups.size);

          if (F_status_is_error(status)) {
            controller_print_rule_error(global->error, cache->action, F_status_set_fine(status), "f_memory_array_increase", F_true, F_false);

            if (F_status_set_fine(status) == F_memory_not) {
              status_return = status;

              break;
            }

            if (F_status_is_error_not(status_return)) {
              status_return = status;
            }

            // Get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global->main->setting.state);

            cache->action.line_action = ++cache->action.line_item;

            controller_print_rule_item_error(global->error, cache->action, F_false, F_status_set_fine(status));

            continue;
          }

          status = controller_convert_group_id(cache->buffer_item, cache->content_actions.array[i].array[j], cache, &number);

          if (F_status_is_error(status)) {
            status = F_status_set_fine(status);

            if (status == F_exist_not) {
              controller_print_rule_setting_read_error_with_range(&global->main->program.error, " has an invalid group", cache->content_actions.array[i].array[j], ", because no group was found by that name", i, line_item, global->thread, cache);
            }
            else if (status == F_number_too_large) {
              controller_print_rule_setting_read_error_with_range(&global->main->program.error, " has an invalid group", cache->content_actions.array[i].array[j], ", because the given ID is too large", i, line_item, global->thread, cache);
            }
            else if (status == F_number) {
              controller_print_rule_setting_read_error_with_range(&global->main->program.error, " has an invalid group", cache->content_actions.array[i].array[j], ", because the given ID is not a valid supported number", i, line_item, global->thread, cache);
            }
            else {

              // Get the current line number within the settings item.
              cache->action.line_item = line_item;
              f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global->main->setting.state);

              cache->action.line_action = ++cache->action.line_item;

              controller_print_rule_error(global->error, cache->action, status, "f_account_group_id_by_name", F_true, F_false);

              controller_print_rule_item_error(global->error, cache->action, F_false, F_status_set_fine(status));
            }

            if (F_status_is_error_not(status_return)) {
              status_return = F_status_set_error(status);
            }
          }
          else {
            if (rule->has & controller_rule_has_group_d) {
              rule->groups.array[rule->groups.used++] = number;
            }
            else {
              rule->group = number;
              rule->has |= controller_rule_has_group_d;
            }
          }
        } // for

        controller_print_rule_setting_read_values(global, controller_group_s, i, cache);

        continue;
      }

      if (type == controller_rule_setting_type_environment_e) {
        setting_values = &rule->environment;

        for (j = 0; j < cache->content_actions.array[i].used; ++j) {

          status = f_memory_array_increase(controller_allocation_small_d, sizeof(f_string_dynamic_t), (void **) &setting_values->array, &setting_values->used, &setting_values->size);

          if (F_status_is_error(status)) {
            controller_print_rule_error(global->error, cache->action, F_status_set_fine(status), "f_memory_array_increase", F_true, F_false);

            if (F_status_set_fine(status) == F_memory_not) {
              status_return = status;

              break;
            }

            if (F_status_is_error_not(status_return)) {
              status_return = status;
            }

            // Get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global->main->setting.state);

            cache->action.line_action = ++cache->action.line_item;

            controller_print_rule_item_error(global->error, cache->action, F_false, F_status_set_fine(status));

            continue;
          }

          setting_values->array[setting_values->used].used = 0;

          status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[j], &setting_values->array[setting_values->used]);

          if (F_status_is_error(status)) {
            controller_print_rule_error(global->error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false);

            setting_values->array[setting_values->used].used = 0;

            if (F_status_set_fine(status) == F_memory_not) {
              status_return = status;

              break;
            }

            if (F_status_is_error_not(status_return)) {
              status_return = status;
            }

            // Get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global->main->setting.state);

            cache->action.line_action = ++cache->action.line_item;

            controller_print_rule_item_error(global->error, cache->action, F_false, F_status_set_fine(status));

            continue;
          }

          status = controller_validate_environment_name(setting_values->array[setting_values->used]);

          if (status == F_false || F_status_set_fine(status) == F_complete_not_utf) {

            // Get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global->main->setting.state);

            cache->action.line_action = ++cache->action.line_item;

            if (status == F_false) {
              if (global->main->program.error.verbosity > f_console_verbosity_quiet_e) {
                controller_lock_print(global->main->program.error.to, global->thread);

                fl_print_format("%r%[%QRule setting has an invalid environment variable name '%]", global->main->program.error.to, f_string_eol_s, global->main->program.error.context, global->main->program.error.prefix, global->main->program.error.context);
                fl_print_format(f_string_format_Q_single_s.string, global->main->program.error.to, global->main->program.error.notable, setting_values->array[setting_values->used], global->main->program.error.notable);
                fl_print_format(f_string_format_sentence_end_quote_s.string, global->main->program.error.to, global->main->program.error.context, global->main->program.error.context, f_string_eol_s);

                controller_print_rule_error_cache(global->error, cache->action, F_false);

                controller_unlock_print_flush(global->main->program.error.to, global->thread);
              }

              if (F_status_is_error_not(status_return)) {
                status_return = F_status_set_error(F_valid_not);
              }
            }
            else {

              // This function should only return F_complete_not_utf on error.
              controller_print_rule_error(global->error, cache->action, F_complete_not_utf, "controller_validate_environment_name", F_true, F_false);

              if (F_status_is_error_not(status_return)) {
                status_return = status;
              }
            }

            setting_values->array[setting_values->used].used = 0;

            controller_print_rule_item_error(global->error, cache->action, F_false, F_status_set_fine(status));

            continue;
          }

          ++setting_values->used;
        } // for

        rule->has |= controller_rule_has_environment_d;

        if (cache->content_actions.array[i].used) {
          controller_print_rule_setting_read_values(global, controller_environment_s, i, cache);
        }
        else {
          if (global->main->program.error.verbosity == f_console_verbosity_debug_e || (global->main->program.error.verbosity == f_console_verbosity_verbose_e && (global->main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e))) {
            controller_lock_print(global->main->program.output.to, global->thread);

            fl_print_format("%rProcessing rule item action '%[%r%]' setting value to an empty set.%r", global->main->program.output.to, f_string_eol_s, global->main->program.context.set.title, controller_environment_s, global->main->program.context.set.title, f_string_eol_s);

            controller_unlock_print_flush(global->main->program.output.to, global->thread);
          }
        }

        continue;
      }

      // The "on" Rule Setting.
      if (cache->content_actions.array[i].used != 4) {
        controller_print_rule_setting_read_error(&global->main->program.error, "requires exactly four Content", i, line_item, global->thread, cache);

        if (F_status_is_error_not(status_return)) {
          status_return = F_status_set_error(F_valid_not);
        }

        continue;
      }

      if (f_compare_dynamic_partial_string(controller_freeze_s.string, cache->buffer_item, controller_freeze_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
        action = controller_rule_action_type_freeze_e;
      }
      else if (f_compare_dynamic_partial_string(controller_kill_s.string, cache->buffer_item, controller_kill_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
        action = controller_rule_action_type_kill_e;
      }
      else if (f_compare_dynamic_partial_string(controller_pause_s.string, cache->buffer_item, controller_pause_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
        action = controller_rule_action_type_pause_e;
      }
      else if (f_compare_dynamic_partial_string(controller_reload_s.string, cache->buffer_item, controller_reload_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
        action = controller_rule_action_type_reload_e;
      }
      else if (f_compare_dynamic_partial_string(controller_restart_s.string, cache->buffer_item, controller_restart_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
        action = controller_rule_action_type_restart_e;
      }
      else if (f_compare_dynamic_partial_string(controller_resume_s.string, cache->buffer_item, controller_resume_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
        action = controller_rule_action_type_resume_e;
      }
      else if (f_compare_dynamic_partial_string(controller_start_s.string, cache->buffer_item, controller_start_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
        action = controller_rule_action_type_start_e;
      }
      else if (f_compare_dynamic_partial_string(controller_stop_s.string, cache->buffer_item, controller_stop_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
        action = controller_rule_action_type_stop_e;
      }
      else if (f_compare_dynamic_partial_string(controller_thaw_s.string, cache->buffer_item, controller_thaw_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
        action = controller_rule_action_type_thaw_e;
      }
      else {
        if (global->main->program.error.verbosity > f_console_verbosity_quiet_e) {

          // Get the current line number within the settings item.
          cache->action.line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global->main->setting.state);

          cache->action.line_action = ++cache->action.line_item;

          f_thread_mutex_lock(&global->thread->lock.print);

          controller_lock_print(global->main->program.error.to, global->thread);

          fl_print_format("%r%[%QRule setting's second value has '%]", global->main->program.error.to, f_string_eol_s, global->main->program.error.context, global->main->program.error.prefix, global->main->program.error.context);
          fl_print_format(f_string_format_Q_range_single_s.string, global->main->program.error.to, global->main->program.error.notable, cache->buffer_item, cache->content_actions.array[i].array[1], global->main->program.error.notable);
          fl_print_format("%[' but only supports %r, %r, %r, %r, %r", global->main->program.error.to, global->main->program.error.context, controller_freeze_s, controller_kill_s, controller_pause_s, controller_reload_s, controller_restart_s);
          fl_print_format("%r, %r, %r, and %r.%]%r", global->main->program.error.to, controller_resume_s, controller_start_s, controller_stop_s, controller_thaw_s, global->main->program.error.context, f_string_eol_s);

          controller_print_rule_error_cache(global->error, cache->action, F_false);

          controller_unlock_print_flush(global->main->program.error.to, global->thread);
        }

        if (F_status_is_error_not(status_return)) {
          status_return = F_status_set_error(F_valid_not);
        }

        continue;
      }

      for (j = 0; j < rule->ons.used; ++j) {
        if (rule->ons.array[j].action == action) break;
      } // for

      if (j == rule->ons.used) {
        status = f_memory_array_increase(controller_allocation_small_d, sizeof(controller_rule_on_t), (void **) &rule->ons.array, &rule->ons.used, &rule->ons.size);
      }

      if (F_status_is_error(status)) {
        controller_print_rule_error(global->error, cache->action, F_status_set_fine(status), macro_controller_f(f_memory_array_increase), F_true, F_false);
      }
      else {
        if (f_compare_dynamic_partial_string(controller_need_s.string, cache->buffer_item, controller_need_s.used, cache->content_actions.array[i].array[1]) == F_equal_to) {
          setting_values = &rule->ons.array[j].need;
        }
        else if (f_compare_dynamic_partial_string(controller_want_s.string, cache->buffer_item, controller_want_s.used, cache->content_actions.array[i].array[1]) == F_equal_to) {
          setting_values = &rule->ons.array[j].want;
        }
        else if (f_compare_dynamic_partial_string(controller_wish_s.string, cache->buffer_item, controller_wish_s.used, cache->content_actions.array[i].array[1]) == F_equal_to) {
          setting_values = &rule->ons.array[j].wish;
        }
        else {
          if (global->main->program.error.verbosity > f_console_verbosity_quiet_e) {

            // Get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global->main->setting.state);

            cache->action.line_action = ++cache->action.line_item;

            controller_lock_print(global->main->program.error.to, global->thread);

            fl_print_format("%r%[%QRule setting's second value has '%]", global->main->program.error.to, f_string_eol_s, global->main->program.error.context, global->main->program.error.prefix, global->main->program.error.context);
            fl_print_format(f_string_format_Q_range_single_s.string, global->main->program.error.to, global->main->program.error.notable, cache->buffer_item, cache->content_actions.array[i].array[1], global->main->program.error.notable);
            fl_print_format("%[' but only supports %r, %r, and %r.%]%r", global->main->program.error.to, global->main->program.error.context, controller_need_s, controller_want_s, controller_wish_s, global->main->program.error.context, f_string_eol_s);

            controller_print_rule_error_cache(global->error, cache->action, F_false);

            controller_unlock_print_flush(global->main->program.error.to, global->thread);
          }

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        status = f_memory_array_increase_by(controller_allocation_small_d, sizeof(f_string_dynamic_t), (void **) &setting_values->array, &setting_values->used, &setting_values->size);

        if (F_status_is_error(status)) {
          controller_print_rule_error(global->error, cache->action, F_status_set_fine(status), "f_memory_array_increase_by", F_true, F_false);
        }
      }

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_memory_not) {
          status_return = status;

          break;
        }

        if (F_status_is_error_not(status_return)) {
          status_return = status;
        }

        // Get the current line number within the settings item.
        cache->action.line_item = line_item;
        f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global->main->setting.state);

        cache->action.line_action = ++cache->action.line_item;

        controller_print_rule_item_error(global->error, cache->action, F_false, F_status_set_fine(status));

        continue;
      }

      status = controller_rule_id_construct(global, cache->buffer_item, cache->content_actions.array[i].array[2], cache->content_actions.array[i].array[3], &setting_values->array[setting_values->used]);

      if (F_status_is_error(status)) {
        setting_values->array[setting_values->used].used = 0;

        if (F_status_set_fine(status) == F_memory_not) {
          status_return = status;

          break;
        }

        if (F_status_is_error_not(status_return)) {
          status_return = status;
        }

        // Get the current line number within the settings item.
        cache->action.line_item = line_item;
        f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global->main->setting.state);

        cache->action.line_action = ++cache->action.line_item;

        controller_print_rule_item_error(global->error, cache->action, F_false, F_status_set_fine(status));

        continue;
      }

      cache->buffer_path.used = 0;

      status = f_file_name_base(setting_values->array[setting_values->used], &cache->buffer_path);

      if (F_status_is_error(status)) {
        setting_values->array[setting_values->used].used = 0;

        controller_print_rule_error(global->error, cache->action, F_status_set_fine(status), "f_file_name_base", F_true, F_false);

        if (F_status_set_fine(status) == F_memory_not) {
          status_return = status;

          break;
        }

        if (F_status_is_error_not(status_return)) {
          status_return = status;
        }

        continue;
      }

      rule->ons.array[j].action = action;

      ++setting_values->used;

      if (j == rule->ons.used) {
        ++rule->ons.used;
      }

      if (global->main->program.error.verbosity == f_console_verbosity_debug_e || (global->main->program.error.verbosity == f_console_verbosity_verbose_e && (global->main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e))) {
        controller_lock_print(global->main->program.output.to, global->thread);

        fl_print_format("%rProcessing rule item action '%[%r%]', adding ", global->main->program.output.to, f_string_eol_s, global->main->program.context.set.title, controller_on_s, global->main->program.context.set.title);
        fl_print_format("'%[%/Q%]' of ", global->main->program.output.to, global->main->program.context.set.notable, cache->buffer_item, cache->content_actions.array[i].array[1], global->main->program.context.set.notable);
        fl_print_format("'%[%/Q%]/", global->main->program.output.to, global->main->program.context.set.important, cache->buffer_item, cache->content_actions.array[i].array[2], global->main->program.context.set.important);
        fl_print_format("%[%/Q%]'.%r", global->main->program.output.to, global->main->program.context.set.important, cache->buffer_item, cache->content_actions.array[i].array[3], global->main->program.context.set.important, f_string_eol_s);

        controller_unlock_print_flush(global->main->program.output.to, global->thread);
      }
    } // for

    // Restore the current name item and line number, which there should already be enough allocated space for.
    memcpy(cache->action.name_item.string, name_item, sizeof(f_char_t) * length_name_item);

    cache->action.name_item.string[length_name_item] = 0;
    cache->action.name_item.used = length_name_item;

    cache->action.line_item = line_item;

    return status_return;
  }
#endif // _di_controller_rule_setting_read_

#ifdef __cplusplus
} // extern "C"
#endif
