#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_rule_expand_
  f_status_t controller_rule_expand(controller_global_t * const global, const controller_rule_action_t action, controller_instance_t * const instance) {

    if (!global || !instance) return F_status_set_error(F_parameter);

    process->cache.expanded.used = 0;

    if (!action.parameters.used) return F_okay;

    f_status_t status = f_memory_array_increase_by(action.parameters.used, sizeof(f_string_dynamic_t), (void **) &process->cache.expanded.array, &process->cache.expanded.used, &process->cache.expanded.size);
    if (F_status_is_error(status)) return status;

    f_number_unsigned_t i = 0;
    f_number_unsigned_t first = 0;
    f_range_t range = f_range_t_initialize;

    f_iki_data_t *iki_data = 0;
    f_string_dynamic_t *buffer = 0;

    for (; process->cache.expanded.used < action.parameters.used; ++process->cache.expanded.used) {

      buffer = &process->cache.expanded.array[process->cache.expanded.used];
      buffer->used = 0;

      if (action.ikis.array[process->cache.expanded.used].variable.used) {
        iki_data = &action.ikis.array[process->cache.expanded.used];

        // Allocate enough room plus an extra buffer to help reduce reallocations.
        status = f_memory_array_increase_by(action.parameters.array[process->cache.expanded.used].used + controller_allocation_large_d, sizeof(f_char_t), (void **) &buffer->string, &buffer->used, &buffer->size);

        // Apply the IKI delimits.
        for (i = 0; i < iki_data->delimits.used; ++i) {
          action.parameters.array[process->cache.expanded.used].string[iki_data->delimits.array[i]] = f_iki_syntax_placeholder_s.string[0];
        } // for

        if (iki_data->variable.used) {
          for (i = 0, first = 0; i < iki_data->variable.used; ++i) {

            // Copy everything up to the start of the IKI variable.
            if (first < iki_data->variable.array[i].start) {
              range.start = first;
              range.stop = iki_data->variable.array[i].start - 1;

              status = f_string_dynamic_partial_append_nulless(action.parameters.array[process->cache.expanded.used], range, buffer);
              if (F_status_is_error(status)) break;
            }

            status = controller_rule_expand_iki(process, action.parameters.array[process->cache.expanded.used], iki_data->vocabulary.array[i], iki_data->content.array[i], buffer);
            if (F_status_is_error(status)) break;

            first = iki_data->variable.array[i].stop + 1;
          } // for

          if (F_status_is_error(status)) break;

          // Copy everything after the last IKI variable to the end of the content.
          if (first < action.parameters.array[process->cache.expanded.used].used) {
            range.start = first;
            range.stop = action.parameters.array[process->cache.expanded.used].used - 1;

            status = f_string_dynamic_partial_append(action.parameters.array[process->cache.expanded.used], range, buffer);
          }
        }
        else {
          status = f_string_dynamic_append_nulless(action.parameters.array[process->cache.expanded.used], buffer);
        }

        // Unapply the IKI delimits.
        for (i = 0; i < iki_data->delimits.used; ++i) {
          action.parameters.array[process->cache.expanded.used].string[iki_data->delimits.array[i]] = f_iki_syntax_slash_s.string[0];
        } // for
      }
      else {
        status = f_string_dynamic_append(action.parameters.array[process->cache.expanded.used], buffer);
      }

      if (F_status_is_error(status)) return status;
    } // for

    return F_okay;
  }
#endif // _di_controller_rule_expand_

#ifndef _di_controller_rule_expand_iki_
  f_status_t controller_rule_expand_iki(controller_instance_t * const instance, const f_string_static_t source, const f_range_t vocabulary, const f_range_t content, f_string_dynamic_t * const destination) {

    if (!instance || !destination) return F_status_set_error(F_parameter);
    if (vocabulary.start > vocabulary.stop) return F_okay;
    if (content.start > content.stop) return F_okay;

    f_status_t status = F_okay;

    if (f_compare_dynamic_partial_string(controller_define_s.string, source, controller_define_s.used, vocabulary) == F_equal_to) {
      f_number_unsigned_t i = 0;

      // First check to see if the environment variable is overwritten by a "define".
      for (; i < process->rule.define.used; ++i) {

        if (f_compare_dynamic_partial_string(process->rule.define.array[i].key.string, source, process->rule.define.array[i].key.used, content) == F_equal_to) {
          status = f_string_dynamic_append(process->rule.define.array[i].value, destination);
          if (F_status_is_error(status)) return status;

          break;
        }
      } // for

      if (i == process->rule.define.used) {
        controller_entry_t * const entry = process->type == controller_instance_type_entry_e ? &((controller_process_t *) process->main_setting)->entry : &((controller_process_t *) process->main_setting)->exit;

        for (i = 0; i < entry->define.used; ++i) {

            if (f_compare_dynamic_partial_string(entry->define.array[i].key.string, source, entry->define.array[i].key.used, content) == F_equal_to) {
            status = f_string_dynamic_append(entry->define.array[i].value, destination);
            if (F_status_is_error(status)) return status;

            break;
          }
        } // for

        if (i == entry->define.used) {
          i = process->rule.define.used;
        }
      }

      if (i == process->rule.define.used) {
        f_string_static_t buffer = f_string_static_t_initialize;
        buffer.used = (content.stop - content.start) + 1;

        f_char_t buffer_string[buffer.used + 1];

        memcpy(buffer_string, source.string + content.start, sizeof(f_char_t) * buffer.used);
        buffer_string[buffer.used] = 0;
        buffer.string = buffer_string;
        process->cache.action.generic.used = 0;

        status = f_environment_get(buffer, &process->cache.action.generic);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamic_append(process->cache.action.generic, destination);
        if (F_status_is_error(status)) return status;
      }
    }
    else if (f_compare_dynamic_partial_string(controller_parameter_s.string, source, controller_parameter_s.used, vocabulary) == F_equal_to) {
      f_number_unsigned_t i = 0;

      for (; i < process->rule.parameter.used; ++i) {

        if (f_compare_dynamic_partial_string(process->rule.parameter.array[i].key.string, source, process->rule.parameter.array[i].key.used, content) == F_equal_to) {
          status = f_string_dynamic_append(process->rule.parameter.array[i].value, destination);
          if (F_status_is_error(status)) return status;

          break;
        }
      } // for

      if (i == process->rule.parameter.used) {
        controller_entry_t * const entry = process->type == controller_instance_type_entry_e ? &((controller_process_t *) process->main_setting)->entry : &((controller_process_t *) process->main_setting)->exit;

        for (i = 0; i < entry->parameter.used; ++i) {

            if (f_compare_dynamic_partial_string(entry->parameter.array[i].key.string, source, entry->parameter.array[i].key.used, content) == F_equal_to) {
            status = f_string_dynamic_append(entry->parameter.array[i].value, destination);
            if (F_status_is_error(status)) return status;

            break;
          }
        } // for
      }
    }
    else if (f_compare_dynamic_partial_string(controller_program_s.string, source, controller_program_s.used, vocabulary) == F_equal_to) {
      f_string_static_t * const argv = ((controller_main_t *) process->main_data)->program.parameters.arguments.array;
      f_console_parameters_t * const parameters = &((controller_main_t *) process->main_data)->program.parameters;

      const f_string_static_t options[] = {
        f_console_standard_long_light_s,
        f_console_standard_long_dark_s,
        f_console_standard_long_no_color_s,
        f_console_standard_long_quiet_s,
        f_console_standard_long_normal_s,
        f_console_standard_long_verbose_s,
        f_console_standard_long_debug_s,
        controller_long_interruptible_s,
        controller_long_daemon_s,
        controller_long_simulate_s,
        controller_long_uninterruptible_s,
        controller_long_validate_s,

        // Option and Value.
        controller_long_cgroup_s,
        controller_long_pid_s,
        controller_long_settings_s,
        controller_long_socket_s,
      };

      const f_string_static_t symbols[] = {
        f_console_symbol_short_inverse_s, // light.
        f_console_symbol_short_inverse_s, // dark.
        f_console_symbol_short_inverse_s, // no_color.
        f_console_symbol_short_inverse_s, // quiet.
        f_console_symbol_short_inverse_s, // normal.
        f_console_symbol_short_inverse_s, // verbose.
        f_console_symbol_short_inverse_s, // debug.
        f_console_symbol_short_normal_s,  // interruptible.
        f_console_symbol_short_normal_s,  // daemon.
        f_console_symbol_short_normal_s,  // simulate.
        f_console_symbol_short_normal_s,  // uninterruptible.
        f_console_symbol_short_normal_s,  // validate.

        // Option and Value.
        f_console_symbol_short_normal_s,  // cgroup.
        f_console_symbol_short_normal_s,  // pid.
        f_console_symbol_short_normal_s,  // settings.
        f_console_symbol_short_normal_s,  // socket.
      };

      const f_string_static_t expands[] = {
        f_console_standard_short_light_s,
        f_console_standard_short_dark_s,
        f_console_standard_short_no_color_s,
        f_console_standard_short_quiet_s,
        f_console_standard_short_normal_s,
        f_console_standard_short_verbose_s,
        f_console_standard_short_debug_s,
        controller_short_interruptible_s,
        controller_short_daemon_s,
        controller_short_simulate_s,
        controller_short_uninterruptible_s,
        controller_short_validate_s,

        // Option and Value.
        controller_short_cgroup_s,
        controller_short_pid_s,
        controller_short_settings_s,
        controller_short_socket_s,
      };

      const uint8_t codes[] = {
        f_console_standard_parameter_light_e,
        f_console_standard_parameter_dark_e,
        f_console_standard_parameter_no_color_e,
        f_console_standard_parameter_verbosity_quiet_e,
        f_console_standard_parameter_verbosity_normal_e,
        f_console_standard_parameter_verbosity_verbose_e,
        f_console_standard_parameter_verbosity_debug_e,
        controller_parameter_interruptible_e,
        controller_parameter_daemon_e,
        controller_parameter_simulate_e,
        controller_parameter_uninterruptible_e,
        controller_parameter_validate_e,

        // Option and Value.
        controller_parameter_cgroup_e,
        controller_parameter_pid_e,
        controller_parameter_settings_e,
        controller_parameter_socket_e,
      };

      // F_false = only with option, F_true with option and value.
      const bool values[] = {
        F_false, // light.
        F_false, // dark.
        F_false, // no_color.
        F_false, // quiet.
        F_false, // normal.
        F_false, // verbose.
        F_false, // debug.
        F_false, // interruptible.
        F_false, // daemon.
        F_false, // simulate.
        F_false, // uninterruptible.
        F_false, // validate.

        // Option and Value.
        F_true, // cgroup.
        F_true, // pid.
        F_true, // settings.
        F_true, // socket.
      };

      for (f_number_unsigned_t i = 0; i < 16; ++i) {

        if (f_compare_dynamic_partial_string(options[i].string, source, options[i].used, content) == F_equal_to) {
          if (values[i]) {
            if (parameters->array[codes[i]].result & f_console_result_value_e) {
              const f_number_unsigned_t index = parameters->array[codes[i]].values.array[parameters->array[codes[i]].values.used - 1];

              status = f_memory_array_increase_by(symbols[i].used + expands[i].used + f_string_ascii_space_s.used + argv[index].used + 1, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);
              if (F_status_is_error(status)) return status;

              status = f_string_dynamic_append(symbols[i], destination);
              if (F_status_is_error(status)) return status;

              status = f_string_dynamic_append(expands[i], destination);
              if (F_status_is_error(status)) return status;

              status = f_string_dynamic_append(f_string_ascii_space_s, destination);
              if (F_status_is_error(status)) return status;

              status = f_string_dynamic_append(argv[index], destination);
              if (F_status_is_error(status)) return status;
            }
          }
          else {
            if (parameters->array[codes[i]].result & f_console_result_found_e) {
              status = f_memory_array_increase_by(symbols[i].used + expands[i].used + 1, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);
              if (F_status_is_error(status)) return status;

              status = f_string_dynamic_append(symbols[i], destination);
              if (F_status_is_error(status)) return status;

              status = f_string_dynamic_append(expands[i], destination);
              if (F_status_is_error(status)) return status;
            }
          }

          break;
        }

        {
          f_string_static_t buffer = f_string_static_t_initialize;
          buffer.used = options[i].used + controller_parameter_map_option_s.used;

          f_char_t buffer_string[buffer.used];
          buffer.string = buffer_string;

          memcpy(buffer_string, options[i].string, sizeof(f_char_t) * options[i].used);
          memcpy(buffer_string + options[i].used, controller_parameter_map_option_s.string, sizeof(f_char_t) * controller_parameter_map_option_s.used);

          if (f_compare_dynamic_partial_string(buffer.string, source, buffer.used, content) == F_equal_to) {
            if (values[i] && parameters->array[codes[i]].result & f_console_result_value_e || !values[i] && (parameters->array[codes[i]].result & f_console_result_found_e)) {
              status = f_memory_array_increase_by(symbols[i].used + expands[i].used + 1, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);
              if (F_status_is_error(status)) return status;

              status = f_string_dynamic_append(symbols[i], destination);
              if (F_status_is_error(status)) return status;

              status = f_string_dynamic_append(expands[i], destination);
              if (F_status_is_error(status)) return status;
            }

            break;
          }
        }

        if (values[i]) {
          f_string_static_t buffer = f_string_static_t_initialize;
          buffer.used = options[i].used + controller_parameter_map_value_s.used;

          f_char_t buffer_string[buffer.used];
          buffer.string = buffer_string;

          memcpy(buffer_string, options[i].string, sizeof(f_char_t) * options[i].used);
          memcpy(buffer_string + options[i].used, controller_parameter_map_value_s.string, sizeof(f_char_t) * controller_parameter_map_value_s.used);

          if (f_compare_dynamic_partial_string(buffer.string, source, buffer.used, content) == F_equal_to) {
            if (parameters->array[codes[i]].result & f_console_result_value_e) {
              const f_number_unsigned_t index = parameters->array[codes[i]].values.array[parameters->array[codes[i]].values.used - 1];

              status = f_string_dynamic_append(argv[index], destination);
              if (F_status_is_error(status)) return status;
            }

            break;
          }
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_controller_rule_expand_iki_

#ifdef __cplusplus
} // extern "C"
#endif
