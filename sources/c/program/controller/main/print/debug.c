#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_debug_directory_path_empty_
  f_status_t controller_print_debug_directory_path_empty(fl_print_t * const print, const f_string_static_t symbol, const f_string_static_t name) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_debug_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, 0);

    fl_print_format("%r%[%QThe parameter '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_rr_single_s.string, print->to, print->set->notable, symbol, name, print->set->notable);
    fl_print_format("%[' must be a file directory path but instead is an empty string, falling back to the default.%]%r", print->to, print->context, print->context, f_string_eol_s);

    controller_unlock_print_flush(print->to, 0);

    return F_okay;
  }
#endif // _di_controller_print_debug_directory_path_empty_

#ifdef __cplusplus
} // extern "C"
#endif
