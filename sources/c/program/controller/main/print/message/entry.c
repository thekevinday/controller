#include "../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_message_entry_state_
  f_status_t controller_print_message_entry_state(fl_print_t * const print, const uint8_t is_entry, const f_string_static_t name) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_normal_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%rState is now '%[%r%]'.%r", print->to, f_string_eol_s, print->notable, name, print->notable, f_string_eol_s);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_message_entry_state_

#ifdef __cplusplus
} // extern "C"
#endif
