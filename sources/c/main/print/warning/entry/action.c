#include "../../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_warning_entry_action_failsafe_twice_
  f_status_t controller_print_warning_entry_action_failsafe_twice(fl_print_t * const print, controller_cache_t * const cache, const uint8_t is_entry) {

    if (!print || !print->custom || !cache) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_debug_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QFailsafe may not be specified when running in failsafe, ignoring.%]%r", print->to, f_string_eol_s, print->context, print->prefix, print->context, f_string_eol_s);

    controller_print_error_entry_cache(print, &cache->action, is_entry);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_warning_entry_action_failsafe_twice_

#ifndef _di_controller_print_warning_entry_action_multiple_
  f_status_t controller_print_warning_entry_action_multiple(fl_print_t * const print, controller_cache_t * const cache, const uint8_t is_entry, const f_string_static_t name) {

    if (!print || !print->custom || !cache) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_debug_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QMultiple '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, name, print->notable);
    fl_print_format("%[' %r item actions detected; only the first will be used.%]%r", print->to, print->context, is_entry ? controller_entry_s : controller_exit_s, print->context, f_string_eol_s);

    controller_print_error_entry_cache(print, &cache->action, is_entry);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_warning_entry_action_multiple_

#ifndef _di_controller_print_warning_entry_action_unknown_
  f_status_t controller_print_warning_entry_action_unknown(fl_print_t * const print, controller_cache_t * const cache, const uint8_t is_entry, const f_string_static_t name) {

    if (!print || !print->custom || !cache) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_debug_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QUnknown %r item action '%]", print->to, f_string_eol_s, print->context, print->prefix, is_entry ? controller_entry_s : controller_exit_s, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, name, print->notable);
    fl_print_format(f_string_format_sentence_end_quote_s.string, print->to, print->context, print->context, f_string_eol_s);

    controller_print_error_rule_cache(print, &cache->action, F_true);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_warning_entry_action_unknown_

#ifdef __cplusplus
} // extern "C"
#endif
