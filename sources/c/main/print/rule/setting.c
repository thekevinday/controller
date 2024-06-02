#include "../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_rule_setting_read_error_
  void controller_print_rule_setting_read_error(fl_print_t * const print, const f_string_t message, const f_number_unsigned_t index, const f_number_unsigned_t line_item, controller_thread_t * const thread, controller_cache_t * const cache) {

    if (!print->custom) return;
    if (print->verbosity == f_console_verbosity_quiet_e) return;

    controller_t * const main = (controller_t *) print->custom;

    f_state_t state = f_state_t_initialize;

    // Get the current line number within the settings item.
    cache->action.line_item = line_item;
    f_fss_count_lines(cache->buffer_item, cache->object_actions.array[index].start, &cache->action.line_item, &main->setting.state);

    cache->action.line_action = ++cache->action.line_item;

    controller_lock_print(print->to, thread);

    fl_print_format("%r%[%QRule setting %S.%]%r", print->to, f_string_eol_s, print->context, print->prefix, message, print->context, f_string_eol_s);

    controller_print_rule_error_cache(print, cache->action, F_false);

    controller_unlock_print_flush(print->to, thread);
  }
#endif // _di_controller_print_rule_setting_read_error_

#ifndef _di_controller_print_rule_setting_read_error_with_range_
  void controller_print_rule_setting_read_error_with_range(fl_print_t * const print, const f_string_t before, const f_range_t range, const f_string_t after, const f_number_unsigned_t index, const f_number_unsigned_t line_item, controller_thread_t * const thread, controller_cache_t * const cache) {

    if (!print->custom) return;
    if (print->verbosity == f_console_verbosity_quiet_e) return;

    controller_t * const main = (controller_t *) print->custom;

    f_state_t state = f_state_t_initialize;

    // Get the current line number within the settings item.
    cache->action.line_item = line_item;
    f_fss_count_lines(cache->buffer_item, cache->object_actions.array[index].start, &cache->action.line_item, &main->setting.state);

    cache->action.line_action = ++cache->action.line_item;

    controller_lock_print(print->to, thread);

    fl_print_format("%r%[%QRule setting%S '%]", print->to, f_string_eol_s, print->context, print->prefix, before, print->context);
    fl_print_format(f_string_format_Q_range_single_s.string, print->to, print->notable, cache->buffer_item, range, print->notable);
    fl_print_format("%['%S.%]%r", print->to, print->context, after, print->context, f_string_eol_s);

    controller_print_rule_error_cache(print, cache->action, F_false);

    controller_unlock_print_flush(print->to, thread);
  }
#endif // _di_controller_print_rule_setting_read_error_with_range_

#ifndef _di_controller_print_rule_setting_read_mapping_
  void controller_print_rule_setting_read_mapping(const controller_global_t global, const f_string_static_t name, const f_string_map_t map) {

    if (global.main->program.error.verbosity != f_console_verbosity_debug_e) {
      if (!(global.main->program.error.verbosity == f_console_verbosity_verbose_e && (global.main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e))) {
        return;
      }
    }

    controller_lock_print(global.main->program.output.to, global.thread);

    fl_print_format("%rProcessing rule item action '%[%Q%]'", global.main->program.output.to, f_string_eol_s, global.main->program.context.set.title, name, global.main->program.context.set.title);
    fl_print_format(" mapping '%[%Q%]'", global.main->program.output.to, global.main->program.context.set.important, map.key, global.main->program.context.set.important);
    fl_print_format(" to value '%[%Q%]'.%r", global.main->program.output.to, global.main->program.context.set.important, map.value, global.main->program.context.set.important, f_string_eol_s);

    controller_unlock_print_flush(global.main->program.output.to, global.thread);
  }
#endif // _di_controller_print_rule_setting_read_mapping_

#ifndef _di_controller_print_rule_setting_read_value_
  void controller_print_rule_setting_read_value(const controller_global_t global, const f_string_static_t name, const f_string_static_t name_sub, const f_string_static_t value, const f_string_t suffix) {

    if (global.main->program.error.verbosity != f_console_verbosity_debug_e) {
      if (!(global.main->program.error.verbosity == f_console_verbosity_verbose_e && (global.main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e))) {
        return;
      }
    }

    controller_lock_print(global.main->program.output.to, global.thread);

    fl_print_format("%rProcessing rule item action '%[%Q%]' setting ", global.main->program.output.to, f_string_eol_s, global.main->program.context.set.title, name, global.main->program.context.set.title);

    if (name_sub.used) {
      fl_print_format("'%[%Q%]'", global.main->program.output.to, global.main->program.context.set.notable, name_sub, global.main->program.context.set.notable);
    }
    else {
      f_print_terminated("value", global.main->program.output.to);
    }

    fl_print_format(" to '%[%Q%]'", global.main->program.output.to, global.main->program.context.set.important, value, global.main->program.context.set.important);
    fl_print_format("%S.%r", global.main->program.output.to, suffix, f_string_eol_s);

    controller_unlock_print_flush(global.main->program.output.to, global.thread);
  }
#endif // _di_controller_print_rule_setting_read_value_

#ifndef _di_controller_print_rule_setting_read_values_
  void controller_print_rule_setting_read_values(const controller_global_t global, const f_string_static_t name, const f_number_unsigned_t index, controller_cache_t * const cache) {

    if (global.main->program.error.verbosity != f_console_verbosity_debug_e) {
      if (!(global.main->program.error.verbosity == f_console_verbosity_verbose_e && (global.main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e))) {
        return;
      }
    }

    controller_lock_print(global.main->program.output.to, global.thread);

    fl_print_format("%rProcessing rule item action '%[%Q%]' setting value to", global.main->program.output.to, f_string_eol_s, global.main->program.context.set.title, name, global.main->program.context.set.title);

    for (f_number_unsigned_t j = 0; j < cache->content_actions.array[index].used; ++j) {

      fl_print_format(" '%[%/Q%]'", global.main->program.output.to, global.main->program.context.set.important, cache->buffer_item, cache->content_actions.array[index].array[j], global.main->program.context.set.important);

      if (j + 2 == cache->content_actions.array[index].used) {
        if (cache->content_actions.array[index].used > 2) {
          f_print_terminated(",", global.main->program.output.to);
        }

        f_print_terminated(" and", global.main->program.output.to);
      }
      else if (j + 1 < cache->content_actions.array[index].used) {
        f_print_terminated(",", global.main->program.output.to);
      }
    } // for

    fl_print_format(".%r", global.main->program.output.to, f_string_eol_s);

    controller_unlock_print_flush(global.main->program.output.to, global.thread);
  }
#endif // _di_controller_print_rule_setting_read_value_

#ifdef __cplusplus
} // extern "C"
#endif
