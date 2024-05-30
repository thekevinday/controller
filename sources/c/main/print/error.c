#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_main_print_error_
  f_status_t controller_main_print_error(fl_print_t * const print, const f_string_t function) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_main_t * const main = (controller_main_t *) print->custom;

    fll_error_print(print, F_status_set_fine(main->setting.state.status), function, fll_error_file_flag_fallback_e);

    return F_okay;
  }
#endif // _di_controller_main_print_error_

#ifndef _di_controller_main_print_error_file_
  f_status_t controller_main_print_error_file(fl_print_t * const print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

    controller_main_t * const main = (controller_main_t *) print->custom;

    fll_error_file_print(print, F_status_set_fine(main->setting.state.status), function, fll_error_file_flag_fallback_e, name, operation, type);

    return F_okay;
  }
#endif // _di_controller_main_print_error_file_

#ifndef _di_controller_main_print_error_file_status_
  f_status_t controller_main_print_error_file_status(fl_print_t * const print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type, const f_status_t status) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

    fll_error_file_print(print, status, function, fll_error_file_flag_fallback_e, name, operation, type);

    return F_okay;
  }
#endif // _di_controller_main_print_error_file_status_

#ifndef _di_controller_main_print_error_status_
  f_status_t controller_main_print_error_status(fl_print_t * const print, const f_string_t function, const f_status_t status) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_error_print(print, status, function, fll_error_file_flag_fallback_e);

    return F_okay;
  }
#endif // _di_controller_main_print_error_status_

#ifndef _di_controller_main_print_error_rule_
  f_status_t controller_main_print_error_rule(fl_print_t * const print, const f_status_t status, const f_string_t function, const bool fallback, const bool item) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    // fll_error_print() automatically locks, so manually handle only the mutex locking and flushing rather than calling controller_lock_print().
    f_thread_mutex_lock(&global->thread->lock.print);

    controller_global_t * const global = (controller_global_t *) print->custom; // @fixme The print->custom is currently controller_main_t, but threads need to change this. Thread-specific print objects?

    fll_error_print(print, F_status_set_fine(global->main->setting.state.status), function, fll_error_file_flag_fallback_e);

    fll_error_print(print, status, function, fallback);

    f_file_stream_lock(print->to);

    controller_rule_print_error_cache(print, cache, item);

    controller_unlock_print_flush(print->to, thread);

    return F_okay;
  }
#endif // _di_controller_main_print_error_rule_

#ifndef _di_controller_rule_print_error_cache_
  void controller_rule_print_error_cache(fl_print_t * const print, const controller_cache_action_t cache, const bool item) {

    if (print->verbosity == f_console_verbosity_quiet_e) return;

    fl_print_format("%r%[%QWhile processing ", print->to, f_string_eol_s, print->context, print->prefix);

    if (cache.name_action.used) {
      fl_print_format("%r '%]", print->to, item ? controller_action_s : controller_value_s, print->context);
      fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, cache.name_action, print->notable);
      fl_print_format("%[' on line%] ", print->to, print->context, print->context);
      fl_print_format("%[%un%]", print->to, print->notable, cache.line_action, print->notable);
      fl_print_format("%[ for ", print->to, print->context);
    }

    if (cache.name_item.used) {
      fl_print_format("rule %r '%]", print->to, item ? controller_item_s : controller_settings_s, print->context);
      fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, cache.name_item, print->notable);
      fl_print_format("%[' on line%] ", print->to, print->context, print->context);
      fl_print_format("%[%un%]", print->to, print->notable, cache.line_item, print->notable);
      fl_print_format("%[ for ", print->to, print->context);
    }

    if (cache.name_file.used) {
      fl_print_format("rule file '%]%[%Q%]%['", print->to, print->context, print->notable, cache.name_file, print->notable, print->context);
    }

    fl_print_format(".%]%r", print->to, print->context, f_string_eol_s);
  }
#endif // _di_controller_rule_print_error_cache_

#ifdef __cplusplus
} // extern "C"
#endif
