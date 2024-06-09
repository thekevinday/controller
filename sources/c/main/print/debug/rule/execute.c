#include "../../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_main_print_debug_rule_execute_rerun_
  f_status_t controller_main_print_debug_rule_execute_rerun(fl_print_t * const print, controller_rule_rerun_item_t * const rerun, const uint8_t action) {

    if (!print || !print->custom || !rerun) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_debug_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%rRe-running '", print->to, f_string_eol_s);
    fl_print_format("%[%r%]' '", print->to, print->set->title, instance->rule.alias, print->set->title);
    fl_print_format("%[%r%]' with a ", print->to, print->set->notable, controller_convert_rule_action_execute_type_string(action), print->set->notable);
    fl_print_format("%[%r%] of ", print->to, print->set->notable, controller_delay_s, print->set->notable);
    fl_print_format("%[%ul%] MegaTime", print->to, print->set->notable, rerun->delay, print->set->notable);

    if (rerun->max) {
      fl_print_format(" for %[%ul%]", print->to, print->set->notable, rerun->count, print->set->notable);
      fl_print_format(" of %[%r%] ", print->to, print->set->notable, controller_max_s, print->set->notable);
      fl_print_format(f_string_format_un_single_s.string, print->to, print->set->notable, rerun->max, print->set->notable);
      fl_print_format(".%r", print->to, f_string_eol_s);
    }
    else {
      fl_print_format(" with no %[%r%].%r", print->to, print->set->notable, controller_max_s, print->set->notable, f_string_eol_s);
    }

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_main_print_debug_rule_execute_rerun_

#ifdef __cplusplus
} // extern "C"
#endif
