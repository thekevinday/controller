#include "../../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_entry_warning_setting_unknown_action_
  f_status_t controller_print_entry_warning_setting_unknown_action(fl_print_t * const print, controller_cache_t * const cache, const uint8_t is_entry) {

    if (!print || !print->custom || !cache) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_debug_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QUnknown %r item setting '%]", print->to.stream, f_string_eol_s, print->context, print->prefix, is_entry ? controller_entry_s : controller_exit_s, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to.stream, print->notable, cache->action.name_action, print->notable);
    fl_print_format(f_string_format_sentence_end_quote_s.string, print->to.stream, print->context, print->context, f_string_eol_s);

    controller_print_entry_error_cache(print, &cache->action, is_entry);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_entry_warning_setting_unknown_action_

#ifdef __cplusplus
} // extern "C"
#endif
