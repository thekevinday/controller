#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_rule_item_read_
  void controller_rule_item_read(controller_t * const main, controller_cache_t * const cache, const uint8_t is_normal, controller_rule_item_t * const item, f_state_t * const state) {

    if (!state) return;

    if (!main || !cache || !item) {
      state->status = F_status_set_error(F_parameter);

      return;
    }

    f_range_t range = macro_f_range_t_initialize_2(cache->buffer_item.used);
    f_number_unsigned_t last = 0;

    uint8_t type = 0;
    uint8_t method = 0;
    uint8_t multiple = F_false;

    item->actions.used = 0;

    for (; range.start < cache->buffer_item.used && range.start <= range.stop; last = range.start, cache->delimits.used = 0, cache->comments.used = 0) {

      fl_fss_extended_list_object_read(cache->buffer_item, &range, &cache->range_action, &cache->delimits, state);

      if (F_status_is_error(state->status)) {
        controller_print_error_status(&main->program.error, macro_controller_f(fl_fss_extended_list_object_read), F_status_set_fine(state->status));

        break;
      }

      if (state->status == F_fss_found_object) {
        multiple = F_true;
      }
      else {
        range.start = last;
        multiple = F_false;
        cache->delimits.used = 0;

        // The current line is not an Extended List object, so the next possibility is a Basic List (and Extended List, both use the same Object structure).
        fl_fss_extended_object_read(cache->buffer_item, &range, &cache->range_action, 0, &cache->delimits, state);

        if (F_status_is_error(state->status)) {
          controller_print_error_status(&main->program.error, macro_controller_f(fl_fss_extended_object_read), F_status_set_fine(state->status));

          break;
        }

        // Nothing of importance here, so continue onto the next line.
        if (state->status != F_fss_found_object) continue;
      }

      f_fss_apply_delimit(cache->delimits, &cache->buffer_item, state);

      if (F_status_is_error(state->status)) {
        controller_print_error_status(&main->program.error, macro_controller_f(f_fss_apply_delimit), F_status_set_fine(state->status));

        break;
      }

      f_fss_count_lines(cache->buffer_item, cache->range_action.start, &cache->action.line_action, state);

      if (F_status_is_error(state->status)) {
        controller_print_error_status(&main->program.error, macro_controller_f(f_fss_count_lines), F_status_set_fine(state->status));

        break;
      }

      cache->action.line_action += ++item->line;
      cache->action.name_action.used = 0;

      state->status = f_rip_dynamic_partial_nulless(cache->buffer_item, cache->range_action, &cache->action.name_action);

      if (F_status_is_error(state->status)) {
        controller_print_error_status(&main->program.error, macro_controller_f(f_rip_dynamic_partial_nulless), F_status_set_fine(state->status));

        break;
      }

      if (f_compare_dynamic(controller_freeze_s, cache->action.name_action) == F_equal_to) {
        type = controller_rule_action_type_freeze_e;
      }
      else if (f_compare_dynamic(controller_group_s, cache->action.name_action) == F_equal_to) {
        type = controller_rule_action_type_group_e;
      }
      else if (f_compare_dynamic(controller_kill_s, cache->action.name_action) == F_equal_to) {
        type = controller_rule_action_type_kill_e;
      }
      else if (f_compare_dynamic(controller_pause_s, cache->action.name_action) == F_equal_to) {
        type = controller_rule_action_type_pause_e;
      }
      else if (f_compare_dynamic(controller_pid_file_s, cache->action.name_action) == F_equal_to) {
        type = controller_rule_action_type_pid_file_e;
      }
      else if (f_compare_dynamic(controller_reload_s, cache->action.name_action) == F_equal_to) {
        type = controller_rule_action_type_reload_e;
      }
      else if (f_compare_dynamic(controller_rerun_s, cache->action.name_action) == F_equal_to) {
        type = controller_rule_action_type_rerun_e;
      }
      else if (f_compare_dynamic(controller_restart_s, cache->action.name_action) == F_equal_to) {
        type = controller_rule_action_type_restart_e;
      }
      else if (f_compare_dynamic(controller_resume_s, cache->action.name_action) == F_equal_to) {
        type = controller_rule_action_type_resume_e;
      }
      else if (f_compare_dynamic(controller_start_s, cache->action.name_action) == F_equal_to) {
        type = controller_rule_action_type_start_e;
      }
      else if (f_compare_dynamic(controller_stop_s, cache->action.name_action) == F_equal_to) {
        type = controller_rule_action_type_stop_e;
      }
      else if (f_compare_dynamic(controller_thaw_s, cache->action.name_action) == F_equal_to) {
        type = controller_rule_action_type_thaw_e;
      }
      else if (f_compare_dynamic(controller_user_s, cache->action.name_action) == F_equal_to) {
        type = controller_rule_action_type_user_e;
      }
      else if (f_compare_dynamic(controller_with_s, cache->action.name_action) == F_equal_to) {
        type = controller_rule_action_type_with_e;
      }
      else {
        controller_print_warning_rule_action_unknown(&main->program.warning, &cache->action, cache->action.name_action);

        continue;
      }

      if (multiple) {
        if (type == controller_rule_action_type_group_e || type == controller_rule_action_type_pid_file_e || type == controller_rule_action_type_user_e) {
          state->status = F_status_set_error(F_support_not);

          controller_print_error_rule_action_fss_0003_unsupported(&main->program.error, &cache->action, cache->action.name_action);

          break;
        }

        method = controller_rule_action_method_extended_list_e;
      }
      else {
        method = controller_rule_action_method_extended_e;
      }

      state->status = f_memory_array_increase(controller_allocation_small_d, sizeof(controller_rule_action_t), (void **) &item->actions.array, &item->actions.used, &item->actions.size);

      if (F_status_is_error(state->status)) {
        controller_print_error_status(&main->program.error, macro_controller_f(f_memory_array_increase_by), F_status_set_fine(state->status));

        break;
      }

      controller_rule_action_read(main, cache, is_normal, type, method, item, &item->actions, &range, state);
      if (F_status_is_error(state->status)) break;
    } // for
  }
#endif // _di_controller_rule_item_read_

#ifdef __cplusplus
} // extern "C"
#endif
