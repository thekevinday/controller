#include "../../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_message_entry_item_done_
  f_status_t controller_print_message_entry_item_done(fl_print_t * const print, const uint8_t is_entry, const uint8_t failsafe, const f_string_static_t name) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%rDone processing %r item '", print->to, f_string_eol_s, is_entry ? controller_entry_s : controller_exit_s);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->set->title, name, print->set->title);
    fl_print_format("'.%r%r", print->to, f_string_eol_s, failsafe ? f_string_eol_s : f_string_empty_s);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_message_entry_item_done_

#ifndef _di_controller_print_message_entry_item_executing_
  f_status_t controller_print_message_entry_item_executing(fl_print_t * const print, const uint8_t is_entry, f_string_dynamics_t * const parameters) {

    if (!print || !print->custom || !parameters) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_normal_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%Q is executing '", print->to, f_string_eol_s, is_entry ? controller_entry_s : controller_exit_s);

    for (f_number_unsigned_t k = 0; k < parameters->used; ++k) {

      fl_print_format(f_string_format_Q_single_s.string, print->to, print->set->title, parameters->array[k], print->set->title);

      if (k + 1 < parameters->used) {
        f_print_dynamic_raw(f_string_space_s, print->to);
      }
    } // for

    fl_print_format(f_string_format_sentence_end_quote_s.string, print->to, f_string_eol_s);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_message_entry_item_executing_

#ifndef _di_controller_print_message_entry_item_process_
  f_status_t controller_print_message_entry_item_process(fl_print_t * const print, const uint8_t is_entry, const f_string_static_t prepend, const f_string_static_t name) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_normal_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%rProcessing %r", print->to, f_string_eol_s, prepend);

    if (prepend.used) {
      fl_print_format("%r ", print->to, prepend);
    }

    fl_print_format("%r item '%[%Q%]'.%r", print->to, is_entry ? controller_entry_s : controller_exit_s, print->set->title, name, print->set->title, f_string_eol_s);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_message_entry_item_process_

#ifndef _di_controller_print_message_entry_item_required_
  f_status_t controller_print_message_entry_item_required(fl_print_t * const print, const uint8_t is_entry, const f_string_static_t name, const f_string_t reason) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QThe required %r item '%]", print->to, f_string_eol_s, print->context, print->prefix, is_entry ? controller_entry_s : controller_exit_s);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->set->title, name, print->set->title);
    fl_print_format("' %Q.", print->to, reason, f_string_eol_s);

    controller_print_error_entry_cache(print, &main->thread.cache.action, is_entry);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_message_entry_item_required_

#ifndef _di_controller_print_message_entry_item_rule_
  f_status_t controller_print_message_entry_item_rule(fl_print_t * const print, controller_entry_t * const entry, controller_entry_action_t * const action, const uint8_t is_entry, const f_string_static_t alias_rule) {

    if (!print || !print->custom || !entry || !action) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_normal_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%r %r Item Rule ", print->to, f_string_eol_s, action->type == controller_entry_action_type_consider_e ? controller_print_entry_considering_s : controller_print_entry_processing_s, is_entry ? controller_entry_s : controller_exit_s);
    fl_print_format("'%[%Q%]'", print->to, print->set->title, alias_rule, print->set->title);

    if (entry->show == controller_entry_show_init_e && !(main->setting.flag & controller_main_flag_simulate_d)) {
      fl_print_format(" [%[%r%]]", print->to, print->notable, action->code == controller_entry_rule_code_asynchronous_d ? controller_asynchronous_s : controller_synchronous_s, print->notable);

      if (action->code == controller_entry_rule_code_wait_d) {
        fl_print_format(" [%[%r%]]", print->to, print->notable, controller_wait_s, print->notable);
      }

      if (action->code == controller_entry_rule_code_require_d) {
        fl_print_format(" [%[%r%]]", print->to, print->notable, controller_required_s, print->notable);
      }
    }

    fl_print_format(f_string_format_sentence_end_s.string, print->to, f_string_eol_s);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_message_entry_item_rule_

#ifdef __cplusplus
} // extern "C"
#endif
