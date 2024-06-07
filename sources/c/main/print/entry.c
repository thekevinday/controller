#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_entry_error_
  f_status_t controller_print_entry_error(fl_print_t * const print, controller_cache_action_t * const cache, const uint8_t is_entry, const f_status_t status, const char * const function, const bool fallback) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;
    if (status == F_interrupt) return F_status_set_error(F_output_not);

    controller_t * const main = (controller_t *) print->custom;

    // fll_error_print() automatically locks, so manually handle only the mutex locking and flushing rather than calling controller_lock_print().
    f_thread_mutex_lock(&main->thread.lock.print);

    fll_error_print(print, status, function, fallback);

    f_file_stream_lock(print->to);

    controller_print_entry_error_cache(print, cache, is_entry);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_entry_error_

#ifndef _di_controller_print_entry_error_cache_
  f_status_t controller_print_entry_error_cache(fl_print_t * const print, controller_cache_action_t * const cache, const uint8_t is_entry) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fl_print_format("%r%[%QWhile processing ", print->to.stream, f_string_eol_s, print->context, print->prefix);

    if (cache->name_action.used) {
      fl_print_format("action '%]", print->to.stream, print->context);
      fl_print_format("%[%Q%]", print->to.stream, print->notable, cache->name_action, print->notable);
      fl_print_format("%[' on line%] ", print->to.stream, print->context, print->context);
      fl_print_format("%[%un%]", print->to.stream, print->notable, cache->line_action, print->notable);
      fl_print_format("%[ for ", print->to.stream, print->context);
    }

    if (cache->name_item.used) {
      fl_print_format("%r item '%]", print->to.stream, is_entry ? controller_entry_s : controller_exit_s, print->context);
      fl_print_format("%[%Q%]", print->to.stream, print->notable, cache->name_item, print->notable);
      fl_print_format("%[' on line%] ", print->to.stream, print->context, print->context);
      fl_print_format("%[%un%]", print->to.stream, print->notable, cache->line_item, print->notable);
      fl_print_format("%[ for ", print->to.stream, print->context);
    }

    if (cache->name_file.used) {
      fl_print_format("%r file '%]", print->to.stream, is_entry ? controller_entry_s : controller_exit_s, print->context);
      fl_print_format("%[%Q%]%['", print->to.stream, print->notable, cache->name_file, print->notable, print->context);
    }

    fl_print_format(".%]%r", print->to.stream, print->context, f_string_eol_s);

    return F_okay;
  }
#endif // _di_controller_print_entry_error_cache_

#ifndef _di_controller_print_entry_error_file_
  f_status_t controller_print_entry_error_file(fl_print_t * const print, controller_cache_action_t * const cache, const uint8_t is_entry, const f_status_t status, const char * const function, const bool fallback, const f_string_static_t name, const f_string_static_t operation, const uint8_t type) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;
    if (status == F_interrupt) return F_status_set_error(F_output_not);

    controller_t * const main = (controller_t *) print->custom;

    // fll_error_file_print() automatically locks, so manually handle only the mutex locking and flushing rather than calling controller_lock_print().
    f_thread_mutex_lock(&main->thread.lock.print);

    fll_error_file_print(print, status, function, fallback, name, operation, type);

    f_file_stream_lock(print->to);

    controller_print_entry_error_cache(print, cache, is_entry);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_entry_error_file_

#ifndef _di_controller_print_entry_error_item_action_execution_failure_
  f_status_t controller_print_entry_error_item_action_execution_failure(fl_print_t * const print, controller_cache_action_t * const cache, const uint8_t is_entry, const int code) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QExecution failed with return value of '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_i_single_s.string, print->to, print->notable, code, print->notable);
    fl_print_format("$['.%]%r", print->to, print->context, print->context, f_string_eol_s);

    controller_print_entry_error_cache(print, cache, is_entry);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_entry_error_item_action_execution_failure_

#ifndef _di_controller_print_entry_error_item_action_execution_missing_
  f_status_t controller_print_entry_error_item_action_execution_missing(fl_print_t * const print, controller_cache_action_t * const cache, const uint8_t is_entry, const f_string_static_t name) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QExecution failed, unable to find program or script '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, name, print->notable);
    fl_print_format(f_string_format_sentence_end_quote_s.string, print->to, print->context, print->context, f_string_eol_s);

    controller_print_entry_error_cache(print, cache, is_entry);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_entry_error_item_action_execution_missing_

#ifndef _di_controller_print_entry_error_item_failure_
  f_status_t controller_print_entry_error_item_failure(fl_print_t * const print, controller_cache_action_t * const cache, const uint8_t is_entry, const f_string_static_t name, const f_string_static_t message) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QThe %r item named '%]", print->to, f_string_eol_s, print->context, is_entry ? controller_entry_s : controller_exit_s, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, parameter, print->notable);
    fl_print_format("%[' %S.%]%r", print->to, print->context, message, print->context, f_string_eol_s);

    controller_print_entry_error_cache(print, cache, is_entry);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_entry_error_item_failure_

#ifndef _di_controller_print_entry_error_item_invalid_
  f_status_t controller_print_entry_error_item_invalid(fl_print_t * const print, controller_cache_action_t * const cache, const uint8_t is_entry, const f_number_unsigned_t number) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[Invalid %r item index '%]", print->to, f_string_eol_s, print->context, is_entry ? controller_entry_s : controller_exit_s, print->context);
    fl_print_format(f_string_format_un_single_s.string, print->to, print->notable, number, print->notable);
    fl_print_format("%[' detected.%]%r", print->to, print->context, print->context, f_string_eol_s);

    controller_print_entry_error_cache(print, cache, is_entry);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_entry_error_item_invalid_

#ifndef _di_controller_print_entry_message_action_parameters_
  f_status_t controller_print_entry_message_action_parameters(fl_print_t * const print, controller_entry_action_t * const action) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    for (f_array_length_t index = 0; ;) {

      f_print_dynamic_safely(action.parameters.array[index], stream);

      ++index;

      if (index == action.parameters.used) break;

      f_print_dynamic_raw(f_string_space_s, stream);
    } // for

    return F_okay;
  }
#endif // _di_controller_print_entry_message_action_parameters_

#ifndef _di_controller_print_entry_message_action_state_
  f_status_t controller_print_entry_message_action_state(fl_print_t * const print, controller_cache_action_t * const cache, controller_entry_action_t * const action, const uint8_t is_entry, const f_string_static_t name) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QThe %r item action '%]", print->to, f_string_eol_s, print->context, print->prefix, is_entry ? controller_entry_s : controller_exit_s, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, name, print->notable);


    if (action->parameters.used) {
      fl_print_format(" %[", print->to, context->notable);

      controller_print_entry_message_action_parameters(print, action);

      fl_print_format("%]", print->to, context->notable);
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

    controller_print_entry_error_cache(is_entry, print, &cache->action);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_entry_message_action_state_

#ifndef _di_controller_print_entry_message_action_state_failed_
  f_status_t controller_print_entry_message_action_state_failed(fl_print_t * const print, controller_entry_action_t * const action, const uint8_t is_entry, const f_string_static_t name) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%rThe %r item action '", print->to, f_string_eol_s, is_entry ? controller_entry_s : controller_exit_s);
    fl_print_format(f_string_format_Q_single_s.string, print->to, context->set.title, name, context->set.title);

    if (action->parameters.used) {
      fl_print_format(" %[", print->to, context->notable);

      controller_print_entry_message_action_parameters(print->to, action);

      fl_print_format("%]", print->to, context->notable);
    }

    fl_print_format("' is %[%r%] and is in a ", print->to, context->notable, action->code & controller_entry_rule_code_require_d ? "required" : "optional", context->notable);

    fl_print_format("%[failed%] state, skipping.%r", print->to, context->notable, context->notable, context->notable, f_string_eol_s);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_entry_message_action_state_failed_

#ifndef _di_controller_print_entry_message_item_action_ready_
  f_status_t controller_print_entry_message_item_action_ready(fl_print_t * const print, const uint8_t is_entry, const f_string_static_t name) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_normal_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%rIgnoring %r item action '", print->to, f_string_eol_s, is_entry ? controller_entry_s : controller_exit_s);
    fl_print_format(f_string_format_r_single_s.string, print->to, print->set.title, name, print->set.title);
    fl_print_format("', state already is ready.%r", print->to, f_string_eol_s);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_entry_message_item_action_ready_

#ifndef _di_controller_print_entry_message_item_action_wait_
  f_status_t controller_print_entry_message_item_action_wait(fl_print_t * const print, const uint8_t is_entry, const f_string_static_t name) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_normal_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%rWaiting before processing %r item action '", print->to, f_string_eol_s, is_entry ? controller_entry_s : controller_exit_s);
    fl_print_format(f_string_format_r_single_s.string, print->to, print->set.title, name, print->set.title);
    fl_print_format("'.%r", print->to, f_string_eol_s);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_entry_message_item_action_wait_

#ifndef _di_controller_print_entry_message_item_executing_
  f_status_t controller_print_entry_message_item_executing(fl_print_t * const print, const uint8_t is_entry, f_string_dynamics_t * const parameters) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_normal_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%Q is executing '", print->to, f_string_eol_s, is_entry ? controller_entry_s : controller_exit_s);

    for (f_number_unsigned_t k = 0; k < parameters.used; ++k) {

      fl_print_format(f_string_format_Q_single_s.string, print->to, print->set.title, parameters.array[k], print->set.title);

      if (k + 1 < parameters.used) {
        f_print_dynamic_raw(f_string_space_s, print->to);
      }
    } // for

    fl_print_format("'.%r", print->to, f_string_eol_s);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_entry_message_item_executing_

#ifndef _di_controller_print_entry_message_item_process_
  f_status_t controller_print_entry_message_item_process(fl_print_t * const print, const uint8_t is_entry, const f_string_static_t prepend, const f_string_static_t name) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_normal_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%rProcessing %r", print->to, f_string_eol_s, prepend);

    if (prepend.used) {
      fl_print_format("%r ", print->to, prepend);
    }

    fl_print_format("%r item '%[%Q%]'.%r", print->to, is_entry ? controller_entry_s : controller_exit_s, print->title, name, print->title, f_string_eol_s);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_entry_message_item_process_

    if (((main->setting.flag & controller_main_flag_simulate_e) && main->program.error.verbosity > f_console_verbosity_quiet_e) && main->program.error.verbosity != f_console_verbosity_error_e || main->program.error.verbosity == f_console_verbosity_verbose_e) {
      controller_lock_print(print->to, &main->thread);

      fl_print_format("%rDone processing %r item '", print->to, f_string_eol_s, is_entry ? controller_entry_s : controller_exit_s);
      fl_print_format(f_string_format_r_single_s.string, print->to, print->set.title, controller_main_s, print->set.title);
      fl_print_format("'.%r", print->to, f_string_eol_s);

      // failsafe should not print the extra newline because the failure exit from controller_main should handle this.
      if (!failsafe) {
        f_print_dynamic_raw(f_string_eol_s, print->to);
      }

      controller_unlock_print_flush(print->to, &main->thread);
    }

#ifndef _di_controller_print_entry_message_item_rule_
  f_status_t controller_print_entry_message_item_rule(fl_print_t * const print, const uint8_t is_entry, const f_string_static_t name) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_normal_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%r %r item rule ", print->to, f_string_eol_s, entry_action->type == controller_entry_action_type_consider_e ? controller_print_entry_considering_s : controller_print_entry_processing_s, is_entry ? controller_entry_s : controller_exit_s);
    fl_print_format("'%[%Q%]'", print->to, print->set.title, alias_rule, print->set.title);

    if (entry->show == controller_entry_show_init_e && !(main->setting.flag & controller_main_flag_simulate_e)) {
      fl_print_format(" [%[%r%]]", print->to, main->program.context.set.notable, entry_action->code == controller_entry_rule_code_asynchronous_d ? controller_asynchronous_s : controller_synchronous_s, main->program.context.set.notable);

      if (entry_action->code == controller_entry_rule_code_wait_d) {
        fl_print_format(" [%[%r%]]", print->to, main->program.context.set.notable, controller_wait_s, main->program.context.set.notable);
      }

      if (entry_action->code == controller_entry_rule_code_require_d) {
        fl_print_format(" [%[%r%]]", print->to, main->program.context.set.notable, controller_required_s, main->program.context.set.notable);
      }
    }

    fl_print_format(".%r", print->to, f_string_eol_s);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_entry_message_item_rule_

#ifndef _di_controller_print_entry_message_state_
  f_status_t controller_print_entry_message_state(fl_print_t * const print, const uint8_t is_entry, const f_string_static_t name) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_normal_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%rState is now '%[%r%]'.%r", print->to, f_string_eol_s, print->notable, name, print->notable, f_string_eol_s);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_entry_message_state_

#ifndef _di_controller_print_entry_warning_item_action_failsafe_twice_
  f_status_t controller_print_entry_warning_item_action_failsafe_twice(fl_print_t * const print, controller_cache_action_t * const cache, const uint8_t is_entry) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_debug_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QFailsafe may not be specified when running in failsafe, ignoring.%]%r", print->to, f_string_eol_s, print->context, print->prefix, print->context, f_string_eol_s);

    controller_print_entry_error_cache(print, cache, is_entry);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_entry_warning_item_action_failsafe_twice_

#ifndef _di_controller_print_entry_warning_item_action_multiple_
  f_status_t controller_print_entry_warning_item_action_multiple(fl_print_t * const print, controller_cache_action_t * const cache, const uint8_t is_entry, const f_string_static_t name) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    controller_t * const main = (controller_t *) print->custom;

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%r%[%QMultiple '%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, name, print->notable);
    fl_print_format("%[' %r item actions detected; only the first will be used.%]%r", print->to, print->context, is_entry ? controller_entry_s : controller_exit_s, print->context, f_string_eol_s);

    controller_print_entry_error_cache(print, cache, is_entry);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_print_entry_warning_item_action_multiple_

#ifdef __cplusplus
} // extern "C"
#endif
