#include "../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_error_perform_pid_file_create_
  f_status_t controller_print_error_perform_pid_file_create(fl_print_t * const print, const f_status_t status, const f_string_t function, const uint8_t is_entry) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    controller_print_error_file_status(print, function, F_true, main->setting.path_pid, f_file_operation_create_s, fll_error_file_type_file_e, status);

    f_file_stream_lock(print->to);

    controller_print_error_entry_cache(print->to, &main->thread.cache.action, is_entry);

    controller_unlock_print_flush(print->to, &main->thread);
  }
#endif // _di_controller_print_error_perform_pid_file_create_

#ifdef __cplusplus
} // extern "C"
#endif
