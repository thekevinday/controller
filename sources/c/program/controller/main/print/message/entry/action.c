#include "../../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_message_entry_action_parameters_
  f_status_t controller_print_message_entry_action_parameters(fl_print_t * const print, controller_entry_action_t * const action) {

    if (!print || !action) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    for (f_number_unsigned_t i = 0; ;) {

      f_print_dynamic_safely(action->parameters.array[i], print->to);

      ++i;

      if (i == action->parameters.used) break;

      f_print_dynamic_raw(f_string_space_s, print->to);
    } // for

    return F_okay;
  }
#endif // _di_controller_print_message_entry_action_parameters_

#ifndef _di_controller_print_message_entry_action_ready_
  f_status_t controller_print_message_entry_action_ready(fl_print_t * const print, const uint8_t is_entry, const f_string_static_t name) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_normal_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%rIgnoring %r Item Action '", print->to, f_string_eol_s, is_entry ? controller_entry_s : controller_exit_s);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->set->title, name, print->set->title);
    fl_print_format("', state already is ready.%r", print->to, f_string_eol_s);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_message_entry_action_ready_

#ifndef _di_controller_print_message_entry_action_state_
  f_status_t controller_print_message_entry_action_state(fl_print_t * const print, controller_cache_t * const cache, controller_entry_action_t * const action, const uint8_t is_entry) {

    if (!print || !print->custom || !cache || !action) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QThe %r Item Action '%]", print->to, f_string_eol_s, print->context, print->prefix, is_entry ? controller_entry_s : controller_exit_s, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, cache->action.name_action, print->notable);

    if (action->parameters.used) {
      fl_print_format(" %[", print->to, print->notable);

      controller_print_message_entry_action_parameters(print, action);

      fl_print_format("%]", print->to, print->notable);
    }

    if (action->code & controller_entry_rule_code_require_d) {
      fl_print_format("%[' is%] %[required%]", print->to, print->context, print->context, print->notable, print->notable);
    }
    else {
      fl_print_format("%[' is%] %[optional%]", print->to, print->context, print->context, print->notable, print->notable);
    }

    fl_print_format(" %[and is in a%] %[failed%]", print->to, print->context, print->context, print->notable, print->notable);

    if (action->code & controller_entry_rule_code_require_d) {
      fl_print_format(" %[state, aborting.%]%r", print->to, print->context, print->context, f_string_eol_s);
    }
    else {
      fl_print_format(" %[state, skipping.%]%r", print->to, print->context, print->context, f_string_eol_s);
    }

    controller_print_error_entry_cache(print, &cache->action, is_entry);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_message_entry_action_state_

#ifndef _di_controller_print_message_entry_action_state_failed_
  f_status_t controller_print_message_entry_action_state_failed(fl_print_t * const print, controller_cache_t * const cache, controller_entry_action_t * const action, const uint8_t is_entry) {

    if (!print || !print->custom || !cache || !action) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%rThe %r Item Action '", print->to, f_string_eol_s, is_entry ? controller_entry_s : controller_exit_s);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->set->title, cache->action.name_action, print->set->title);

    if (action->parameters.used) {
      fl_print_format(" %[", print->to, print->notable);

      controller_print_message_entry_action_parameters(print, action);

      fl_print_format("%]", print->to, print->notable);
    }

    fl_print_format("' is %[%r%] and is in a ", print->to, print->notable, action->code & controller_entry_rule_code_require_d ? "required" : "optional", print->notable);

    fl_print_format("%[failed%] state, skipping.%r", print->to, print->notable, print->notable, print->notable, f_string_eol_s);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_message_entry_action_state_failed_

#ifndef _di_controller_print_message_entry_action_wait_
  f_status_t controller_print_message_entry_action_wait(fl_print_t * const print, const uint8_t is_entry, const f_string_static_t name) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_normal_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%rWaiting before processing %r Item Action '", print->to, f_string_eol_s, is_entry ? controller_entry_s : controller_exit_s);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->set->title, name, print->set->title);
    fl_print_format(f_string_format_sentence_end_quote_s.string, print->to, f_string_eol_s);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_message_entry_action_wait_

#ifdef __cplusplus
} // extern "C"
#endif
