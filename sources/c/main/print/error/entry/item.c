#include "../../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_error_entry_item_failure_
  f_status_t controller_print_error_entry_item_failure(fl_print_t * const print, controller_cache_t * const cache, const uint8_t is_entry, const f_string_static_t name, const f_string_static_t message) {

    if (!print || !print->custom || !cache) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QThe %r item named '%]", print->to, f_string_eol_s, print->context, is_entry ? controller_entry_s : controller_exit_s, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, parameter, print->notable);
    fl_print_format("%[' %S.%]%r", print->to, print->context, message, print->context, f_string_eol_s);

    controller_print_error_entry_cache(print, &cache->action, is_entry);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_entry_item_failure_

#ifndef _di_controller_print_error_entry_item_invalid_
  f_status_t controller_print_error_entry_item_invalid(fl_print_t * const print, controller_cache_t * const cache, const uint8_t is_entry, const f_number_unsigned_t number) {

    if (!print || !print->custom || !cache) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[Invalid %r item index '%]", print->to, f_string_eol_s, print->context, is_entry ? controller_entry_s : controller_exit_s, print->context);
    fl_print_format(f_string_format_un_single_s.string, print->to, print->notable, number, print->notable);
    fl_print_format("%[' detected.%]%r", print->to, print->context, print->context, f_string_eol_s);

    controller_print_error_entry_cache(print, &cache->action, is_entry);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_entry_item_invalid_

#ifndef _di_controller_print_error_entry_item_setting_support_not_option_
  f_status_t controller_print_error_entry_item_setting_support_not_option(fl_print_t * const print, controller_cache_t * const cache, const uint8_t is_entry, const f_string_static_t setting) {

    if (!print || !print->custom || !cache) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QThe %r item setting '%]", print->to, f_string_eol_s, print->context, print->prefix, is_entry ? controller_entry_s : controller_exit_s, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, controller_control_s, print->notable);
    fl_print_format("%[' does not support the option '%]", print->to, print->context, print->context, f_string_eol_s);

    fl_print_format(f_string_format_Q_range_single_s.string, print->to, print->notable, cache->buffer_file, setting, print->notable);
    fl_print_format(f_string_format_sentence_end_quote_s.string, print->to, print->context, print->context, f_string_eol_s);

    controller_print_error_entry_cache(print, &cache->action, is_entry);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_error_entry_item_setting_support_not_option_

#ifdef __cplusplus
} // extern "C"
#endif
