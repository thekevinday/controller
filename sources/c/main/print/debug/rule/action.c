#include "../../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_debug_rule_action_empty_
  f_status_t controller_print_debug_rule_action_empty(fl_print_t * const print, controller_cache_t * const cache) {

    if (!print || !print->custom || !cache) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_debug_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QAction is empty, nothing to do.%]%r", print->to, f_string_eol_s, print->context, print->prefix, print->context, f_string_eol_s);

    controller_print_error_rule_cache(print, &cache->action, F_true);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_debug_rule_action_empty_

#ifdef __cplusplus
} // extern "C"
#endif
