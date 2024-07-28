#include "../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_error_lock_critical_
  f_status_t controller_print_error_lock_critical(fl_print_t * const print, const f_status_t status, const uint8_t is_read) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e || status == F_interrupt) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QThe pid file '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format("%['Critical failure while attempting to establish '%]", print->to, print->context, print->context);
    fl_print_format("%[%r lock%]", print->to, print->notable, is_read ? f_file_operation_read_s : f_file_operation_write_s, print->notable);

    if (status != F_failure) {
      fl_print_format(" %['due to%] ", print->to, print->context, print->context);

      if (status == F_parameter) {
        fl_print_format("%[Invalid Parameter%]", print->to, print->notable, print->notable);
      }
      else if (status == F_deadlock) {
        fl_print_format("%[Deadlock%]", print->to, print->notable, print->notable);
      }
      else if (status == F_resource_not) {
        fl_print_format("%[Too Many Locks%]", print->to, print->notable, print->notable);
      }
      else {
        fl_print_format("%[Unknown Error%]", print->to, print->notable, print->notable);
      }
    }

    fl_print_format(f_string_format_sentence_end_single_quote_s.string, print->to, print->context, print->context, f_string_eol_s);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_lock_critical_

#ifdef __cplusplus
} // extern "C"
#endif
