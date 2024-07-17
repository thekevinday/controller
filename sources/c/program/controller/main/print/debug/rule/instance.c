#include "../../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_debug_rule_instance_need_want_wish_
  f_status_t controller_print_debug_rule_instance_need_want_wish(fl_print_t * const print, controller_instance_t * const instance, const f_string_static_t need_want_wish, const f_string_static_t value, const f_string_t why) {

    if (!print || !print->custom || !instance) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_debug_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    controller_print_error_rule_item_need_want_wish(print, need_want_wish, value, why);

    controller_print_error_rule_cache(print, &instance->cache.action, F_true);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_debug_rule_instance_need_want_wish_

#ifdef __cplusplus
} // extern "C"
#endif
