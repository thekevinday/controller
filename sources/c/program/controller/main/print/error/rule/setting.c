#include "../../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_error_rule_setting_
  f_status_t controller_print_error_rule_setting(fl_print_t * const print, controller_cache_action_t * const action, const f_string_t message) {

    if (!print || !print->custom || !action) return F_status_set_error(F_output_not);
    if (print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QRule setting %S.%]%r", print->to, f_string_eol_s, print->context, print->prefix, message, print->context, f_string_eol_s);

    controller_print_error_rule_cache(print, action, F_false);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_rule_setting_

#ifndef _di_controller_print_error_rule_setting_reason_name_
  f_status_t controller_print_error_rule_setting_reason_name(fl_print_t * const print, controller_cache_action_t * const action, const f_string_t reason, const f_string_static_t name) {

    if (!print || !print->custom || !action) return F_status_set_error(F_output_not);
    if (print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%Q%S '%]", print->to, f_string_eol_s, print->context, print->prefix, reason, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, name, print->notable);
    fl_print_format(f_string_format_sentence_end_quote_s.string, print->to, print->context, print->context, f_string_eol_s);

    controller_print_error_rule_cache(print, action, F_false);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_rule_setting_reason_name_

#ifndef _di_controller_print_error_rule_setting_with_range_
  f_status_t controller_print_error_rule_setting_with_range(fl_print_t * const print, controller_cache_action_t * const action, const f_string_t before, const f_string_static_t buffer, const f_range_t range_content, const f_string_t after, const f_number_unsigned_t start, const f_number_unsigned_t line, f_state_t * const state) {

    if (!print || !print->custom || !action) return F_status_set_error(F_output_not);
    if (print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_rule_setting_line_action(main, action, buffer, start, line, state);

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QRule setting%S '%]", print->to, f_string_eol_s, print->context, print->prefix, before, print->context);
    fl_print_format(f_string_format_Q_range_single_s.string, print->to, print->notable, buffer, range_content, print->notable);
    fl_print_format("%['%S.%]%r", print->to, print->context, after, print->context, f_string_eol_s);

    controller_print_error_rule_cache(print, action, F_false);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_rule_setting_with_range_

#ifndef _di_controller_print_error_rule_setting_mapping_
  f_status_t controller_print_error_rule_setting_mapping(fl_print_t * const print, const f_string_static_t name, const f_string_map_t map) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);

    controller_t * const main = (controller_t *) print->custom;

    if (print->verbosity != f_console_verbosity_debug_e) {
      if (!(print->verbosity == f_console_verbosity_verbose_e && (main->setting.flag & controller_main_flag_simulate_e))) {
        return F_output_not;
      }
    }

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%rProcessing Rule Item Action '%[%Q%]'", print->to, f_string_eol_s, print->set->title, name, print->set->title);
    fl_print_format(" mapping '%[%Q%]'", print->to, print->set->important, map.key, print->set->important);
    fl_print_format(" to value '%[%Q%]'.%r", print->to, print->set->important, map.value, print->set->important, f_string_eol_s);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_rule_setting_mapping_

#ifndef _di_controller_print_error_rule_setting_name_invalid_
  f_status_t controller_print_error_rule_setting_name_invalid(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t name) {

    if (!print || !print->custom || !action) return F_status_set_error(F_output_not);
    if (print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QRule setting has an invalid name '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, name, print->notable);
    fl_print_format("%[', there must be at least 1 graph character.%]%r", print->to, print->context, print->context, f_string_eol_s);

    controller_print_error_rule_cache(print, action, F_false);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_rule_setting_name_invalid_

#ifndef _di_controller_print_error_rule_setting_number_invalid_nice_
  f_status_t controller_print_error_rule_setting_number_invalid_nice(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t buffer, const f_range_t range) {

    if (!print || !print->custom || !action) return F_status_set_error(F_output_not);
    if (print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QRule setting has an invalid number '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_range_single_s.string, print->to, print->notable, buffer, range, print->notable);
    fl_print_format("%[', only the whole numbers inclusively between%] ", print->to, print->context, print->context);
    fl_print_format("%[-20%] %[and%]", print->to, print->notable, print->notable, print->context, print->context);
    fl_print_format("%[19%] %[are allowed.%]%r", print->to, print->notable, print->notable, print->context, print->context, f_string_eol_s);

    controller_print_error_rule_cache(print, action, F_false);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_rule_setting_number_invalid_nice_

#ifndef _di_controller_print_error_rule_setting_number_invalid_on_first_
  f_status_t controller_print_error_rule_setting_number_invalid_on_first(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t buffer, const f_range_t range) {

    if (!print || !print->custom || !action) return F_status_set_error(F_output_not);
    if (print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QThe first value for the Rule setting '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, controller_on_s, print->notable);
    fl_print_format("%[' has '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_range_single_s.string, print->to, print->notable, buffer, range, print->notable);
    fl_print_format("%[' but only %r, %r, %r, %r, %r", print->to, print->context, controller_freeze_s, controller_kill_s, controller_pause_s, controller_reload_s, controller_restart_s);
    fl_print_format("%r, %r, %r, and %r are supported.%]%r", print->to, controller_resume_s, controller_start_s, controller_stop_s, controller_thaw_s, print->context, f_string_eol_s);

    controller_print_error_rule_cache(print, action, F_false);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_rule_setting_number_invalid_on_first_

#ifndef _di_controller_print_error_rule_setting_number_invalid_on_second_
  f_status_t controller_print_error_rule_setting_number_invalid_on_second(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t buffer, const f_range_t range) {

    if (!print || !print->custom || !action) return F_status_set_error(F_output_not);
    if (print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QThe second value for the Rule setting '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, controller_on_s, print->notable);
    fl_print_format("%[' has '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_range_single_s.string, print->to, print->notable, buffer, range, print->notable);
    fl_print_format("%[' but only supports %r, %r, and %r.%]%r", print->to, print->context, controller_need_s, controller_want_s, controller_wish_s, print->context, f_string_eol_s);

    controller_print_error_rule_cache(print, action, F_false);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_rule_setting_number_invalid_on_second_

#ifndef _di_controller_print_error_rule_setting_number_invalid_scheduler_
  f_status_t controller_print_error_rule_setting_number_invalid_scheduler(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t buffer, const f_range_t range, const uint8_t zero_only) {

    if (!print || !print->custom || !action) return F_status_set_error(F_output_not);
    if (print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QRule setting has an invalid number '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_range_single_s.string, print->to, print->notable, buffer, range, print->notable);

    if (zero_only) {
      fl_print_format("%[', only%] ", print->to, print->context, print->context);
      fl_print_format("%[0%]%[ is", print->to, print->notable, print->notable, print->context);
    }
    else {
      fl_print_format("%[', only the whole numbers inclusively between%] ", print->to, print->context, print->context);
      fl_print_format("%[1%] %[and%] ", print->to, print->notable, print->notable, print->context, print->context);
      fl_print_format("%[99%] %[are", print->to, print->notable, print->notable, print->context);
    }

    fl_print_format(" allowed for the designated scheduler.%]%r", print->to, print->context, print->context, f_string_eol_s);

    controller_print_error_rule_cache(print, action, F_false);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_rule_setting_number_invalid_scheduler_

#ifndef _di_controller_print_error_rule_setting_number_invalid_timeout_
  f_status_t controller_print_error_rule_setting_number_invalid_timeout(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t buffer, const f_range_t range) {

    if (!print || !print->custom || !action) return F_status_set_error(F_output_not);
    if (print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QThe first value for the Rule setting '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, controller_timeout_s, print->notable);
    fl_print_format("%[' has '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_range_single_s.string, print->to, print->notable, buffer, range, print->notable);
    fl_print_format("%[' but only %r, %r, and %r are supported.%]%r", print->to, print->context, controller_kill_s, controller_start_s, controller_stop_s, print->context, f_string_eol_s);

    controller_print_error_rule_cache(print, action, F_false);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_rule_setting_number_invalid_timeout_

#ifndef _di_controller_print_error_rule_setting_value_
  f_status_t controller_print_error_rule_setting_value(fl_print_t * const print, const f_string_static_t name, const f_string_static_t name_sub, const f_string_static_t value, const f_string_t suffix) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);

    controller_t * const main = (controller_t *) print->custom;

    if (print->verbosity != f_console_verbosity_debug_e) {
      if (!(print->verbosity == f_console_verbosity_verbose_e && (main->setting.flag & controller_main_flag_simulate_e))) {
        return F_output_not;
      }
    }

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%rProcessing Rule Item Action '%[%Q%]' setting ", print->to, f_string_eol_s, print->set->title, name, print->set->title);

    if (name_sub.used) {
      fl_print_format("'%[%Q%]'", print->to, print->set->notable, name_sub, print->set->notable);
    }
    else {
      f_print_terminated("value", print->to);
    }

    fl_print_format(" to '%[%Q%]'", print->to, print->set->important, value, print->set->important);
    fl_print_format("%S.%r", print->to, suffix, f_string_eol_s);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_rule_setting_value_

#ifndef _di_controller_print_error_rule_setting_values_
  f_status_t controller_print_error_rule_setting_values(fl_print_t * const print, controller_cache_t * const cache, const f_string_static_t name, const f_number_unsigned_t index) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);

    controller_t * const main = (controller_t *) print->custom;

    if (print->verbosity != f_console_verbosity_debug_e) {
      if (!(print->verbosity == f_console_verbosity_verbose_e && (main->setting.flag & controller_main_flag_simulate_e))) {
        return F_output_not;
      }
    }

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%rProcessing Rule Item Action '%[%Q%]' setting value to", print->to, f_string_eol_s, print->set->title, name, print->set->title);

    for (f_number_unsigned_t j = 0; j < cache->content_actions.array[index].used; ++j) {

      fl_print_format(" '%[%/Q%]'", print->to, print->set->important, cache->buffer_item, cache->content_actions.array[index].array[j], print->set->important);

      if (j + 2 == cache->content_actions.array[index].used) {
        if (cache->content_actions.array[index].used > 2) {
          f_print_terminated(",", print->to);
        }

        f_print_terminated(" and", print->to);
      }
      else if (j + 1 < cache->content_actions.array[index].used) {
        f_print_terminated(",", print->to);
      }
    } // for

    fl_print_format(".%r", print->to, f_string_eol_s);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_rule_setting_value_

#ifdef __cplusplus
} // extern "C"
#endif
