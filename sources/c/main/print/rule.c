#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_main_print_rule_debug_item_action_empty_
  f_status_t controller_main_print_rule_debug_item_action_empty(fl_print_t * const print, controller_cache_t * const cache) {

    if (!print || !cache) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_debug_e) return F_output_not;

    controller_lock_print(print->to, global->thread);

    fl_print_format("%r%[%QAction is empty, nothing to do.%]%r", primt->to, f_string_eol_s, print->context, print->prefix, print->context, f_string_eol_s);

    controller_rule_print_rule_message_cache(print, cache->action, F_true);

    controller_unlock_print_flush(print->to, global->thread);

    return F_okay;
  }
#endif // _di_controller_main_print_rule_debug_item_action_empty_

#ifndef _di_controller_main_print_rule_error_item_action_first_
  f_status_t controller_main_print_rule_error_item_action_first(fl_print_t * const print, controller_cache_t * const cache) {

    if (!print || !cache) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_lock_print(print->to, global->thread);

    fl_print_format("%r%[%QRule item action '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_r_single_s.string, print->to, print->notable, controller_rerun_s, print->notable);
    fl_print_format("%[' has '%]", print->to, print->context, print->context);
    fl_print_format(f_string_format_Q_range_single_s.string, print->to, print->notable, cache->buffer_item, cache->content_action.array[0], print->notable);
    fl_print_format("%[' as the first value, only the following are allowed: '%]", print->to, print->context, print->context);
    fl_print_format("%[%r%]%[', '%]", print->to, print->notable, controller_freeze_s, print->notable, print->context, print->context);
    fl_print_format("%[%r%]%[', '%]", print->to, print->notable, controller_kill_s, print->notable, print->context, print->context);
    fl_print_format("%[%r%]%[', '%]", print->to, print->notable, controller_pause_s, print->notable, print->context, print->context);
    fl_print_format("%[%r%]%[', '%]", print->to, print->notable, controller_reload_s, print->notable, print->context, print->context);
    fl_print_format("%[%r%]%[', '%]", print->to, print->notable, controller_restart_s, print->notable, print->context, print->context);
    fl_print_format("%[%r%]%[', '%]", print->to, print->notable, controller_resume_s, print->notable, print->context, print->context);
    fl_print_format("%[%r%]%[', '%]", print->to, print->notable, controller_start_s, print->notable, print->context, print->context);
    fl_print_format("%[%r%]%[', or '%]", print->to, print->notable, controller_stop_s, print->notable, print->context, print->context);
    fl_print_format(f_string_format_r_single_s.string, print->to, print->notable, controller_thaw_s, print->notable, print->context);
    fl_print_format(f_string_format_sentence_end_quote_s.string, print->to, print->context, print->context, f_string_eol_s);

    controller_rule_print_rule_message_cache(print, cache->action, F_true);

    controller_unlock_print_flush(print->to, global->thread);

    return F_okay;
  }
#endif // _di_controller_main_print_rule_error_item_action_first_

#ifndef _di_controller_main_print_rule_error_item_action_second_
  f_status_t controller_main_print_rule_error_item_action_second(fl_print_t * const print, controller_cache_t * const cache) {

    if (!print || !cache) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_lock_print(print->to, global->thread);

    fl_print_format("%r%[%QRule item action '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_r_single_s.string, print->to, print->notable, controller_rerun_s, print->notable);
    fl_print_format("%[' has '%]", print->to, print->context, print->context);
    fl_print_format(f_string_format_Q_range_single_s.string, print->to, print->notable, cache->buffer_item, cache->content_action.array[1], print->notable);
    fl_print_format("%[' as the second value, only the following are allowed: '%]", print->to, print->context, print->context);
    fl_print_format("%[%r%]%[' or '%]", print->to, print->notable, controller_stop_s, print->notable, print->context, print->context);
    fl_print_format(f_string_format_r_single_s.string, print->to, print->notable, controller_thaw_s, print->notable, print->context);
    fl_print_format(f_string_format_sentence_end_quote_s.string, print->to, print->context, print->context, f_string_eol_s);

    controller_rule_print_rule_message_cache(print, cache->action, F_true);

    controller_unlock_print_flush(print->to, global->thread);

    return F_okay;
  }
#endif // _di_controller_main_print_rule_error_item_action_second_

#ifndef _di_controller_main_print_rule_error_item_action_unknown_
  f_status_t controller_main_print_rule_error_item_action_unknown(fl_print_t * const print, controller_cache_t * const cache, const f_string_static_t name, const f_number_unsigned_t index) {

    if (!print || !cache) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_lock_print(print->to, global->thread);

    fl_print_format("%r%[%QRule item action '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_r_single_s.string, print->to, print->notable, name, print->notable);
    fl_print_format("%[' has an unknown value '%]", print->to, print->context, print->context);
    fl_print_format(f_string_format_Q_range_single_s.string, print->to, print->notable, cache->buffer_item, cache->content_action.array[index], print->notable);
    fl_print_format(f_string_format_sentence_end_quote_s.string, print->to, print->context, print->context, f_string_eol_s);

    controller_rule_print_rule_message_cache(print, cache->action, F_true);

    controller_unlock_print_flush(print->to, global->thread);

    return F_okay;
  }
#endif // _di_controller_main_print_rule_error_item_action_unknown_

#ifndef _di_controller_rule_print_rule_message_cache_
  f_status_t controller_rule_print_rule_message_cache(fl_print_t * const print, controller_cache_action_t * const cache, const bool item) {

    if (!print || !cache) return F_status_set_error(F_output_not);

    if (print->verbosity == f_console_verbosity_quiet_e) return;

    fl_print_format("%r%[%QWhile processing ", print->to, f_string_eol_s, print->context, print->prefix);

    if (cache->name_action.used) {
      fl_print_format("%r '%]", print->to, item ? controller_action_s : controller_value_s, print->context);
      fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, cache->name_action, print->notable);
      fl_print_format("%[' on line%] ", print->to, print->context, print->context);
      fl_print_format("%[%un%]", print->to, print->notable, cache->line_action, print->notable);
      fl_print_format("%[ for ", print->to, print->context);
    }

    if (cache->name_item.used) {
      fl_print_format("rule %r '%]", print->to, item ? controller_item_s : controller_settings_s, print->context);
      fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, cache->name_item, print->notable);
      fl_print_format("%[' on line%] ", print->to, print->context, print->context);
      fl_print_format("%[%un%]", print->to, print->notable, cache->line_item, print->notable);
      fl_print_format("%[ for ", print->to, print->context);
    }

    if (cache->name_file.used) {
      fl_print_format("rule file '%]%[%Q%]%['", print->to, print->context, print->notable, cache->name_file, print->notable, print->context);
    }

    fl_print_format(".%]%r", print->to, print->context, f_string_eol_s);

    return F_okay;
  }
#endif // _di_controller_rule_print_rule_message_cache_

#ifdef __cplusplus
} // extern "C"
#endif
