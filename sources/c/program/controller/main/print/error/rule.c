#include "../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_error_rule_
  f_status_t controller_print_error_rule(fl_print_t * const print, controller_cache_action_t * const action, const f_status_t status, const f_string_t function, const uint8_t fallback, const uint8_t item) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;
    if (status == F_interrupt) return F_status_set_error(F_output_not);

    controller_t * const main = (controller_t *) print->custom;

    // fll_error_print() automatically locks, so manually handle only the mutex locking and flushing rather than calling controller_lock_print().
    f_thread_mutex_lock(&main->thread.lock.print);

    fll_error_print(print, status, function, fallback);

    f_file_stream_lock(print->to);

    controller_print_error_rule_cache(print, action, item);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_rule_

#ifndef _di_controller_print_error_rule_cache_
  f_status_t controller_print_error_rule_cache(fl_print_t * const print, controller_cache_action_t * const action, const uint8_t item) {

    if (!print || !action) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fl_print_format("%r%[%QWhile processing ", print->to, f_string_eol_s, print->context, print->prefix);

    if (action->name_action.used) {
      fl_print_format("%r '%]", print->to, item ? controller_action_s : controller_value_s, print->context);
      fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, action->name_action, print->notable);
      fl_print_format("%[' on line%] ", print->to, print->context, print->context);
      fl_print_format(f_string_format_un_single_s.string, print->to, print->notable, action->line_action, print->notable);
      fl_print_format("%[ for ", print->to, print->context);
    }

    if (action->name_item.used) {
      fl_print_format("Rule %r '%]", print->to, item ? controller_item_s : controller_settings_s, print->context);
      fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, action->name_item, print->notable);
      fl_print_format("%[' on line%] ", print->to, print->context, print->context);
      fl_print_format(f_string_format_un_single_s.string, print->to, print->notable, action->line_item, print->notable);
      fl_print_format("%[ for ", print->to, print->context);
    }

    if (action->name_file.used) {
      fl_print_format("Rule file '%]%[%Q%]%['", print->to, print->context, print->notable, action->name_file, print->notable, print->context);
    }

    fl_print_format(".%]%r", print->to, print->context, f_string_eol_s);

    return F_okay;
  }
#endif // _di_controller_print_error_rule_cache_

#ifndef _di_controller_print_error_rule_stack_already_
  f_status_t controller_print_error_rule_stack_already(fl_print_t * const print, controller_cache_action_t * const action, const f_string_static_t name, const uint8_t item) {

    if (!print || !print->custom || !action) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QThe Rule '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, name, print->notable);
    fl_print_format("%[' is already on the execution dependency stack, this recursion is prohibited.%]%r", print->to, print->context, print->context, f_string_eol_s);

    controller_print_error_rule_cache(print, action, item);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_rule_stack_already_

#ifdef __cplusplus
} // extern "C"
#endif
