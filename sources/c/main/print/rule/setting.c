#include "../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_rule_setting_read_error_
  f_status_t controller_print_rule_setting_read_error(fl_print_t * const print, const f_string_t message, const f_number_unsigned_t index, const f_number_unsigned_t line_item, controller_thread_t * const thread, controller_cache_t * const cache) {

    if (!print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

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

    return F_okay;
  }
#endif // _di_controller_print_rule_setting_read_error_

#ifndef _di_controller_print_rule_setting_read_error_with_range_
  f_status_t controller_print_rule_setting_read_error_with_range(fl_print_t * const print, const f_string_t before, const f_range_t range, const f_string_t after, const f_number_unsigned_t index, const f_number_unsigned_t line_item, controller_thread_t * const thread, controller_cache_t * const cache) {

    if (!print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

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

    return F_okay;
  }
#endif // _di_controller_print_rule_setting_read_error_with_range_

#ifndef _di_controller_print_rule_setting_read_mapping_
  f_status_t controller_print_rule_setting_read_mapping(controller_t * const main, const f_string_static_t name, const f_string_map_t map) {

    if (main->program.error.verbosity != f_console_verbosity_debug_e) {
      if (!(main->program.error.verbosity == f_console_verbosity_verbose_e && (main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e))) {
        return F_output_not;
      }
    }

    controller_lock_print(main->program.output.to, &main->thread);

    fl_print_format("%rProcessing rule item action '%[%Q%]'", main->program.output.to, f_string_eol_s, main->program.context.set.title, name, main->program.context.set.title);
    fl_print_format(" mapping '%[%Q%]'", main->program.output.to, main->program.context.set.important, map.key, main->program.context.set.important);
    fl_print_format(" to value '%[%Q%]'.%r", main->program.output.to, main->program.context.set.important, map.value, main->program.context.set.important, f_string_eol_s);

    controller_unlock_print_flush(main->program.output.to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_rule_setting_read_mapping_

#ifndef _di_controller_print_rule_setting_read_value_
  f_status_t controller_print_rule_setting_read_value(controller_t * const main, const f_string_static_t name, const f_string_static_t name_sub, const f_string_static_t value, const f_string_t suffix) {

    if (main->program.error.verbosity != f_console_verbosity_debug_e) {
      if (!(main->program.error.verbosity == f_console_verbosity_verbose_e && (main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e))) {
        return F_output_not;
      }
    }

    controller_lock_print(main->program.output.to, &main->thread);

    fl_print_format("%rProcessing rule item action '%[%Q%]' setting ", main->program.output.to, f_string_eol_s, main->program.context.set.title, name, main->program.context.set.title);

    if (name_sub.used) {
      fl_print_format("'%[%Q%]'", main->program.output.to, main->program.context.set.notable, name_sub, main->program.context.set.notable);
    }
    else {
      f_print_terminated("value", main->program.output.to);
    }

    fl_print_format(" to '%[%Q%]'", main->program.output.to, main->program.context.set.important, value, main->program.context.set.important);
    fl_print_format("%S.%r", main->program.output.to, suffix, f_string_eol_s);

    controller_unlock_print_flush(main->program.output.to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_rule_setting_read_value_

#ifndef _di_controller_print_rule_setting_read_values_
  f_status_t controller_print_rule_setting_read_values(controller_t * const main, const f_string_static_t name, const f_number_unsigned_t index, controller_cache_t * const cache) {

    if (main->program.error.verbosity != f_console_verbosity_debug_e) {
      if (!(main->program.error.verbosity == f_console_verbosity_verbose_e && (main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e))) {
        return F_output_not;
      }
    }

    controller_lock_print(main->program.output.to, &main->thread);

    fl_print_format("%rProcessing rule item action '%[%Q%]' setting value to", main->program.output.to, f_string_eol_s, main->program.context.set.title, name, main->program.context.set.title);

    for (f_number_unsigned_t j = 0; j < cache->content_actions.array[index].used; ++j) {

      fl_print_format(" '%[%/Q%]'", main->program.output.to, main->program.context.set.important, cache->buffer_item, cache->content_actions.array[index].array[j], main->program.context.set.important);

      if (j + 2 == cache->content_actions.array[index].used) {
        if (cache->content_actions.array[index].used > 2) {
          f_print_terminated(",", main->program.output.to);
        }

        f_print_terminated(" and", main->program.output.to);
      }
      else if (j + 1 < cache->content_actions.array[index].used) {
        f_print_terminated(",", main->program.output.to);
      }
    } // for

    fl_print_format(".%r", main->program.output.to, f_string_eol_s);

    controller_unlock_print_flush(main->program.output.to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_rule_setting_read_value_

#ifdef __cplusplus
} // extern "C"
#endif
