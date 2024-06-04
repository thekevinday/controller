#include "../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_entry_setting_read_print_error_with_range_
  f_status_t controller_entry_setting_read_print_error_with_range(fl_print_t * const print, const uint8_t is_entry, const f_string_t before, const f_string_range_t range, const f_string_t after) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;
    if (main->warning.verbosity < f_console_verbosity_debug_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print.to, thread);

    fl_print_format("%r%[%Q%r setting%S '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, is_entry ? controller_Entry_s : controller_Exit_s, before, print.context);
    fl_print_format("%[%/Q%]", print.to.stream, print.notable, cache->buffer_file, range, print.notable);
    fl_print_format("%['%S.%]%r", print.to.stream, print.context, after, print.context, f_string_eol_s);

    controller_entry_print_error_cache(is_entry, print, cache->action);

    controller_unlock_print_flush(print.to, thread);

    return F_okay;
  }
#endif // _di_controller_entry_setting_read_print_error_with_range_

#ifndef _di_controller_print_entry_setting_read_ignored_
  f_status_t controller_print_entry_setting_read_ignored(fl_print_t * const print, const uint8_t is_entry, const f_array_length_t index) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;
    if (main->warning.verbosity < f_console_verbosity_debug_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    if (main->warning.verbosity < f_console_verbosity_debug_e) return F_output_not;

    controller_lock_print(main->warning.to, &main->thread);

    fl_print_format("%r%[%QThe %Q item setting '%]", main->warning.to.stream, f_string_eol_s, main->warning.context, main->warning.prefix, is_entry ? controller_entry_s : controller_exit_s, main->warning.context);
    fl_print_format("%[%Q%]", main->warning.to.stream, main->warning.notable, cache->action.name_action, main->warning.notable);
    fl_print_format("%[' is being ignored.%]%r", main->warning.to.stream, main->warning.context, main->warning.context, f_string_eol_s);

    controller_entry_print_error_cache(is_entry, main->warning, cache->action);

    controller_unlock_print_flush(main->warning.to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_entry_setting_read_ignored_

#ifndef _di_controller_print_entry_setting_read_requires_between_
  f_status_t controller_print_entry_setting_read_requires_between(fl_print_t * const print, const uint8_t is_entry, const f_number_unsigned_t minimum, const f_number_unsigned_t maximum) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    if (main->warning.verbosity < f_console_verbosity_debug_e) return F_output_not;

    controller_lock_print(main->error.to, &main->thread);

    fl_print_format("%r%[%QThe %Q item setting '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, is_entry ? controller_entry_s : controller_exit_s, main->error.context);
    fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, cache->action.name_action, main->error.notable);
    fl_print_format("%[' requires at least %]", main->error.to.stream, main->error.context, main->error.context);
    fl_print_format("%[%un%]", main->error.to.stream, main->error.notable, minimum, main->error.notable);
    fl_print_format("%[ and at most %]", main->error.to.stream, main->error.context, main->error.context);
    fl_print_format("%[%un%]", main->error.to.stream, main->error.notable, maximum, main->error.notable);
    fl_print_format("%[ Content.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

    controller_entry_print_error_cache(is_entry, main->error, cache->action);

    controller_unlock_print_flush(main->error.to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_entry_setting_read_requires_between_

#ifndef _di_controller_print_entry_setting_read_requires_exactly_
  f_status_t controller_print_entry_setting_read_requires_exactly(fl_print_t * const print, const uint8_t is_entry, const f_number_unsigned_t total) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    if (main->warning.verbosity < f_console_verbosity_debug_e) return F_output_not;

    controller_lock_print(main->error.to, &main->thread);

    fl_print_format("%r%[%QThe %Q item setting '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, is_entry ? controller_entry_s : controller_exit_s, main->error.context);
    fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, cache->action.name_action, main->error.notable);
    fl_print_format("%[' requires exactly %]", main->error.to.stream, main->error.context, main->error.context);
    fl_print_format("%[%un%]", main->error.to.stream, main->error.notable, total, main->error.notable);
    fl_print_format("%[ Content.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

    controller_entry_print_error_cache(is_entry, main->error, cache->action);

    controller_unlock_print_flush(main->error.to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_entry_setting_read_requires_exactly_

#ifndef _di_controller_print_entry_setting_read_unknown_action_
  f_status_t controller_print_entry_setting_read_unknown_action(fl_print_t * const print, const uint8_t is_entry) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    if (main->warning.verbosity < f_console_verbosity_debug_e) return F_output_not;

    controller_lock_print(main->warning.to, &main->thread);

    fl_print_format("%r%[%QUnknown %r item setting '%]", main->warning.to.stream, f_string_eol_s, main->warning.context, main->warning.prefix, is_entry ? controller_entry_s : controller_exit_s, main->warning.context);
    fl_print_format("%[%Q%]", main->warning.to.stream, main->warning.notable, cache->action.name_action, main->warning.notable);
    fl_print_format("%['.%]%r", main->warning.to.stream, main->warning.context, main->warning.context, f_string_eol_s);

    controller_entry_print_error_cache(is_entry, main->warning, cache->action);

    controller_unlock_print_flush(main->warning.to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_entry_setting_read_unknown_action_

#ifndef _di_controller_print_entry_setting_read_unknown_action_value_
  f_status_t controller_print_entry_setting_read_unknown_action_value(fl_print_t * const print, const uint8_t is_entry, const f_array_length_t index) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    if (!main || !cache) return F_status_set_error(F_output_not);
    if (main->warning.verbosity < f_console_verbosity_debug_e) return F_output_not;

    controller_lock_print(main->warning.to, &main->thread);

    fl_print_format("%r%[%QThe %Q item setting '%]", main->warning.to.stream, f_string_eol_s, main->warning.context, main->warning.prefix, is_entry ? controller_entry_s : controller_exit_s, main->warning.context);
    fl_print_format("%[%Q%]", main->warning.to.stream, main->warning.notable, cache->action.name_action, main->warning.notable);
    fl_print_format("%[' has an unknown value '%]", main->warning.to.stream, main->warning.context, main->warning.context);
    fl_print_format("%[%/Q%]", main->warning.to.stream, main->warning.notable, cache->buffer_file, cache->content_actions.array[index].array[0], main->warning.notable);
    fl_print_format("%['.%]%r", main->warning.to.stream, main->warning.context, main->warning.context, f_string_eol_s);

    controller_entry_print_error_cache(is_entry, main->warning, cache->action);

    controller_unlock_print_flush(main->warning.to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_entry_setting_read_unknown_action_value_

#ifdef __cplusplus
} // extern "C"
#endif
