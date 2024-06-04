#include "../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_entry_preprocess_print_simulate_setting_value_
  f_status_t controller_entry_preprocess_print_simulate_setting_value(fl_print_t * const print, const uint8_t is_entry, const f_string_static_t name, const f_string_static_t name_sub, const f_string_static_t value, const f_string_static_t suffix) {

    if (main->error.verbosity != f_console_verbosity_debug_e && !(main->error.verbosity == f_console_verbosity_verbose_e && main->parameters.array[controller_parameter_simulate_e].result == f_console_result_found_e)) {
      return;
    }

    controller_lock_print(main->output.to, &main->thread);

    fl_print_format("%rProcessing %r item action '", main->output.to.stream, f_string_eol_s, is_entry ? controller_entry_s : controller_exit_s);

    fl_print_format("%[%Q%]' setting ", main->output.to.stream, main->context.set.title, name, main->context.set.title);

    if (name_sub.used) {
      fl_print_format("'%[%Q%]'", main->output.to.stream, main->context.set.notable, name_sub, main->context.set.notable);
    }
    else {
      fl_print_format("value", main->output.to.stream);
    }

    fl_print_format(" to '%[%Q%]", main->output.to.stream, main->context.set.important, value, main->context.set.important);

    fl_print_format("'%Q.%r", main->output.to.stream, suffix, f_string_eol_s);

    controller_unlock_print_flush(main->output.to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_entry_preprocess_print_simulate_setting_value_

#ifdef __cplusplus
} // extern "C"
#endif
