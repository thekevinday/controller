#include "../../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_output_rule_execute_setting_simulate_adding_range_3_
  f_status_t controller_print_output_rule_execute_setting_simulate_adding_range_3(fl_print_t * const print, const f_string_static_t name, const f_string_static_t buffer, const f_range_t range_1, const f_range_t range_2, const f_range_t range_3) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);

    controller_t * const main = (controller_t *) print->custom;

    if (print->verbosity < f_console_verbosity_debug_e && !((main->setting.flag & controller_main_flag_simulate_e) && print->verbosity > f_console_verbosity_normal_e)) {
      return F_output_not;
    }

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%rProcessing Rule Item Action '%[%r%]', adding ", print->to, f_string_eol_s, main->program.context.set.title, name, main->program.context.set.title);
    fl_print_format("'%[%/Q%]' of ", print->to, main->program.context.set.notable, buffer, range_1, main->program.context.set.notable);
    fl_print_format("'%[%/Q%]/", print->to, main->program.context.set.important, buffer, range_2, main->program.context.set.important);
    fl_print_format("%[%/Q%]'.%r", print->to, main->program.context.set.important, buffer, range_3, main->program.context.set.important, f_string_eol_s);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_output_rule_execute_setting_simulate_adding_range_3_

#ifdef __cplusplus
} // extern "C"
#endif
