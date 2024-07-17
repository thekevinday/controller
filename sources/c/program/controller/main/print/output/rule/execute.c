#include "../../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_entry_output_execute_simulate_
  f_status_t controller_print_entry_output_execute_simulate(fl_print_t * const print, controller_instance_t * const instance, const f_string_static_t program, const f_string_statics_t arguments) {

    if (!print || !print->custom || !instance) return F_status_set_error(F_output_not);

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%rSimulating execution of '%[", print->to, f_string_eol_s, print->set->title);

    if (program.used) {
      f_print_dynamic_safely(program, print->to);
    }
    else {
      f_print_dynamic_safely(arguments.array[0], print->to);
    }

    fl_print_format("%]' with the arguments: '%[", print->to, print->set->title, print->set->important);

    for (f_number_unsigned_t i = program.used ? 0 : 1; i < arguments.used; ++i) {

      if (program.used && i || !program.used && i > 1) {
        f_print_dynamic_raw(f_string_space_s, print->to);
      }

      f_print_dynamic_safely(arguments.array[i], print->to);
    } // for

    fl_print_format("%]' from '", print->to, print->set->important);
    fl_print_format("%[%Q%]'.%r", print->to, print->set->notable, instance->rule.name, print->set->notable, f_string_eol_s);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_entry_output_execute_simulate_

#ifdef __cplusplus
} // extern "C"
#endif
