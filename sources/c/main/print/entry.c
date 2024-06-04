#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_entry_action_parameters_print_
  f_status_t controller_entry_action_parameters_print(fl_print_t * const print, controller_entry_action_t * const action) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    for (f_array_length_t index = 0; ;) {

      f_print_dynamic_safely(action.parameters.array[index], stream);

      ++index;

      if (index == action.parameters.used) break;

      f_print_dynamic_raw(f_string_space_s, stream);
    } // for

    return F_okay;
  }
#endif // _di_controller_entry_action_parameters_print_

#ifndef _di_controller_entry_print_error_
  f_status_t controller_entry_print_error(fl_print_t * const print, controller_cache_action_t * const cache, const uint8_t is_entry, const f_status_t status, const char *function, const bool fallback) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    if (print.verbosity == f_console_verbosity_quiet_e) return;
    if (status == F_interrupt) return;

    // fll_error_print() automatically locks, so manually handle only the mutex locking and flushing rather than calling controller_lock_print().
    f_thread_mutex_lock(&main->thread.lock.print);

    fll_error_print(print, status, function, fallback);

    flockfile(print.to.stream);

    controller_entry_print_error_cache(is_entry, print, cache);

    controller_unlock_print_flush(print.to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_entry_print_error_

#ifndef _di_controller_entry_print_error_cache_
  f_status_t controller_entry_print_error_cache(fl_print_t * const print, controller_cache_action_t * const cache, const uint8_t is_entry) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fl_print_format("%r%[%QWhile processing ", output.to.stream, f_string_eol_s, output.context, output.prefix);

    if (cache.name_action.used) {
      fl_print_format("action '%]", output.to.stream, output.context);
      fl_print_format("%[%Q%]", output.to.stream, output.notable, cache.name_action, output.notable);
      fl_print_format("%[' on line%] ", output.to.stream, output.context, output.context);
      fl_print_format("%[%un%]", output.to.stream, output.notable, cache.line_action, output.notable);
      fl_print_format("%[ for ", output.to.stream, output.context);
    }

    if (cache.name_item.used) {
      fl_print_format("%r item '%]", output.to.stream, is_entry ? controller_entry_s : controller_exit_s, output.context);
      fl_print_format("%[%Q%]", output.to.stream, output.notable, cache.name_item, output.notable);
      fl_print_format("%[' on line%] ", output.to.stream, output.context, output.context);
      fl_print_format("%[%un%]", output.to.stream, output.notable, cache.line_item, output.notable);
      fl_print_format("%[ for ", output.to.stream, output.context);
    }

    if (cache.name_file.used) {
      fl_print_format("%r file '%]", output.to.stream, is_entry ? controller_entry_s : controller_exit_s, output.context);
      fl_print_format("%[%Q%]%['", output.to.stream, output.notable, cache.name_file, output.notable, output.context);
    }

    fl_print_format(".%]%r", output.to.stream, output.context, f_string_eol_s);

    return F_okay;
  }
#endif // _di_controller_entry_print_error_cache_

#ifndef _di_controller_entry_print_error_file_
  f_status_t controller_entry_print_error_file(fl_print_t * const print, controller_cache_action_t * const cache, const uint8_t is_entry, const f_status_t status, const char *function, const bool fallback, const f_string_static_t name, const f_string_static_t operation, const uint8_t type) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    if (print.verbosity == f_console_verbosity_quiet_e) return;
    if (status == F_interrupt) return;

    // fll_error_file_print() automatically locks, so manually handle only the mutex locking and flushing rather than calling controller_lock_print().
    f_thread_mutex_lock(&main->thread.lock.print);

    fll_error_file_print(print, status, function, fallback, name, operation, type);

    flockfile(print.to.stream);

    controller_entry_print_error_cache(is_entry, print, cache);

    controller_unlock_print_flush(print.to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_entry_print_error_file_

#ifdef __cplusplus
} // extern "C"
#endif
