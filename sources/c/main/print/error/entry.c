#include "../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_error_entry_
  f_status_t controller_print_error_entry(fl_print_t * const print, const uint8_t is_entry, const f_status_t status, const char * const function, const bool fallback) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;
    if (status == F_interrupt) return F_status_set_error(F_output_not);

    controller_t * const main = (controller_t *) print->custom;

    // fll_error_print() automatically locks, so manually handle only the mutex locking and flushing rather than calling controller_lock_print().
    f_thread_mutex_lock(&main->thread.lock.print);

    fll_error_print(print, status, function, fallback);

    f_file_stream_lock(print->to);

    controller_print_error_entry_cache(print, &main->thread.cache.action, is_entry);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_entry_

#ifndef _di_controller_print_error_entry_cache_
  f_status_t controller_print_error_entry_cache(fl_print_t * const print, controller_cache_action_t * const cache, const uint8_t is_entry) {

    if (!print || !cache) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fl_print_format("%r%[%QWhile processing ", print->to, f_string_eol_s, print->context, print->prefix);

    if (cache->name_action.used) {
      fl_print_format("action '%]", print->to, print->context);
      fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, cache->name_action, print->notable);
      fl_print_format("%[' on line%] ", print->to, print->context, print->context);
      fl_print_format(f_string_format_un_single_s.string, print->to, print->notable, cache->line_action, print->notable);
      fl_print_format("%[ for ", print->to, print->context);
    }

    if (cache->name_item.used) {
      fl_print_format("%r item '%]", print->to, is_entry ? controller_entry_s : controller_exit_s, print->context);
      fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, cache->name_item, print->notable);
      fl_print_format("%[' on line%] ", print->to, print->context, print->context);
      fl_print_format(f_string_format_un_single_s.string, print->to, print->notable, cache->line_item, print->notable);
      fl_print_format("%[ for ", print->to, print->context);
    }

    if (cache->name_file.used) {
      fl_print_format("%r file '%]", print->to, is_entry ? controller_entry_s : controller_exit_s, print->context);
      fl_print_format("%[%Q%]%['", print->to, print->notable, cache->name_file, print->notable, print->context);
    }

    fl_print_format(".%]%r", print->to, print->context, f_string_eol_s);

    return F_okay;
  }
#endif // _di_controller_print_error_entry_cache_

#ifndef _di_controller_print_error_entry_file_
  f_status_t controller_print_error_entry_file(fl_print_t * const print, const uint8_t is_entry, const f_status_t status, const char * const function, const bool fallback, const f_string_static_t name, const f_string_static_t operation, const uint8_t type) {

    if (!print || !print->custom || !cache) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;
    if (status == F_interrupt) return F_status_set_error(F_output_not);

    controller_t * const main = (controller_t *) print->custom;

    // fll_error_file_print() automatically locks, so manually handle only the mutex locking and flushing rather than calling controller_lock_print().
    f_thread_mutex_lock(&main->thread.lock.print);

    fll_error_file_print(print, status, function, fallback, name, operation, type);

    f_file_stream_lock(print->to);

    controller_print_error_entry_cache(print, &main->thread.cache.action, is_entry);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_entry_file_

#ifdef __cplusplus
} // extern "C"
#endif
