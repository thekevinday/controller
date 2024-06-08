#include "../../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_entry_error_setting_with_range_
  f_status_t controller_print_entry_error_setting_with_range(fl_print_t * const print, controller_cache_t * const cache, const uint8_t is_entry, const f_string_t before, const f_range_t range, const f_string_t after) {

    if (!print || !print->custom || !cache) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%Q%r setting%S '%]", print->to.stream, f_string_eol_s, print->context, print->prefix, is_entry ? controller_Entry_s : controller_Exit_s, before, print->context);
    fl_print_format("%[%/Q%]", print->to.stream, print->notable, cache->buffer_file, range, print->notable);
    fl_print_format("%['%S.%]%r", print->to.stream, print->context, after, print->context, f_string_eol_s);

    controller_print_entry_error_cache(print, &cache->action, is_entry);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_entry_error_setting_with_range_

#ifndef _di_controller_print_entry_error_setting_ignored_
  f_status_t controller_print_entry_error_setting_ignored(fl_print_t * const print, controller_cache_t * const cache, const uint8_t is_entry) {

    if (!print || !print->custom || !cache) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_debug_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QThe %Q item setting '%]", print->to.stream, f_string_eol_s, print->context, print->prefix, is_entry ? controller_entry_s : controller_exit_s, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to.stream, print->notable, cache->action.name_action, print->notable);
    fl_print_format("%[' is being ignored.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);

    controller_print_entry_error_cache(print, &cache->action, is_entry);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_entry_error_setting_ignored_

#ifndef _di_controller_print_entry_error_setting_requires_between_
  f_status_t controller_print_entry_error_setting_requires_between(fl_print_t * const print, controller_cache_t * const cache, const uint8_t is_entry, const f_number_unsigned_t minimum, const f_number_unsigned_t maximum) {

    if (!print || !print->custom || !cache) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QThe %Q item setting '%]", print->to.stream, f_string_eol_s, print->context, print->prefix, is_entry ? controller_entry_s : controller_exit_s, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to.stream, print->notable, cache->action.name_action, print->notable);
    fl_print_format("%[' requires at least %]", print->to.stream, print->context, print->context);
    fl_print_format(f_string_format_un_single_s.string, print->to.stream, print->notable, minimum, print->notable);
    fl_print_format("%[ and at most %]", print->to.stream, print->context, print->context);
    fl_print_format(f_string_format_un_single_s.string, print->to.stream, print->notable, maximum, print->notable);
    fl_print_format("%[ Content.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);

    controller_print_entry_error_cache(print, &cache->action, is_entry);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_entry_error_setting_requires_between_

#ifndef _di_controller_print_entry_error_setting_requires_exactly_
  f_status_t controller_print_entry_error_setting_requires_exactly(fl_print_t * const print, controller_cache_t * const cache, const uint8_t is_entry, const f_number_unsigned_t total) {

    if (!print || !print->custom || !cache) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QThe %Q item setting '%]", print->to.stream, f_string_eol_s, print->context, print->prefix, is_entry ? controller_entry_s : controller_exit_s, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to.stream, print->notable, cache->action.name_action, print->notable);
    fl_print_format("%[' requires exactly %]", print->to.stream, print->context, print->context);
    fl_print_format(f_string_format_un_single_s.string, print->to.stream, print->notable, total, print->notable);
    fl_print_format("%[ Content.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);

    controller_print_entry_error_cache(print, &cache->action, is_entry);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_entry_error_setting_requires_exactly_

#ifndef _di_controller_print_entry_error_setting_support_not_number_
  f_status_t controller_print_entry_error_setting_support_not_number(fl_print_t * const print, const uint8_t is_entry, const f_string_static_t buffer, const f_range_t range) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QThe %r setting '%]", print->to, f_string_eol_s, print->context, print->prefix, is_entry ? controller_entry_s : controller_exit_s, print->context);
    fl_print_format(f_string_format_Q_range_single_s.string, print->to, print->notable, buffer, range, print->notable);
    fl_print_format("%[' is not a valid supported number.%]", print->to, print->context, print->context, f_string_eol_s);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_entry_error_setting_support_not_number_

#ifdef __cplusplus
} // extern "C"
#endif
