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

#ifndef _di_controller_main_print_error_status_
  f_status_t controller_main_print_error_status(fl_print_t * const print, const f_string_t function, const f_status_t status) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_error_print(print, status, function, fll_error_file_flag_fallback_e);

    return F_okay;
  }
#endif // _di_controller_main_print_error_status_

#ifdef __cplusplus
} // extern "C"
#endif
