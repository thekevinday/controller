#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_lock_print_error_critical_
  void controller_lock_print_error_critical(fl_print_t * const print, const f_status_t status, const uint8_t is_read) {

    // A signal is not an error.
    if (!print || !print->custom || status == F_interrupt) return;

    controller_t * const main = (controller_t *) print->custom;

    if (print->verbosity != f_console_verbosity_quiet_e) {
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

      fl_print_format(f_string_format_sentence_end_quote_s.string, print->to, print->context, print->context, f_string_eol_s);

      controller_unlock_print_flush(print->to, &main->thread);
    }
  }
#endif // _di_controller_lock_print_error_critical_

#ifndef _di_controller_lock_print_
  void controller_lock_print(const f_file_t to, controller_thread_t * const thread) {

    if (thread) {
      f_thread_mutex_lock(&thread->lock.print);
    }

    f_file_stream_lock(to);
  }
#endif // _di_controller_lock_print_

#ifndef _di_controller_unlock_print_flush_
  void controller_unlock_print_flush(const f_file_t to, controller_thread_t * const thread) {

    f_file_stream_flush(to);
    f_file_stream_unlock(to);

    if (thread) {
      f_thread_mutex_unlock(&thread->lock.print);
    }
  }
#endif // _di_controller_unlock_print_flush_

#ifdef __cplusplus
} // extern "C"
#endif
