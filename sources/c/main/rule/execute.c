#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_rule_execute_
  f_status_t controller_rule_execute(controller_global_t * const global, const uint8_t action, const uint8_t options, controller_instance_t * const instance) {

    if (!global || !instance) return F_status_set_error(F_parameter);

    f_status_t status = F_okay;
    f_status_t success = F_false;

    f_number_unsigned_t i = 0;
    f_number_unsigned_t j = 0;
    f_number_unsigned_t k = 0;

    // Child processes should receive all signals and handle the signals as they see fit.
    f_signal_how_t signals = f_signal_how_t_initialize;
    f_signal_set_empty(&signals.block);
    f_signal_set_fill(&signals.block_not);

    f_string_maps_t environment = f_string_maps_t_initialize;

    controller_execute_set_t execute_set = macro_controller_execute_set_t_initialize_1(0, 0, &environment, &signals, 0, fl_execute_as_t_initialize);

    if (process->rule.affinity.used) {
      execute_set.as.affinity = &process->rule.affinity;
    }

    if (process->rule.capability) {
      execute_set.as.capability = process->rule.capability;
    }

    if (process->rule.has & controller_rule_has_cgroup_d) {
      execute_set.as.control_group = &process->rule.cgroup;

      // Make sure all required cgroup directories exist.
      if (controller_rule_status_is_available(action, process->rule)) {
        status = fll_control_group_prepare(process->rule.cgroup);

        if (F_status_is_error(status)) {
          controller_print_error_file(global->thread, &global->main->program.error, F_status_set_fine(status), "fll_control_group_prepare", F_true, process->rule.cgroup.path, controller_rule_print_control_groups_prepare_s, fll_error_file_type_directory_e);

          return status;
        }
      }
    }

    if (process->rule.has & controller_rule_has_group_d) {
      execute_set.as.id_group = &process->rule.group;

      if (process->rule.groups.used) {
        execute_set.as.id_groups = &process->rule.groups;
      }
    }

    if (process->rule.limits.used) {
      execute_set.as.limits = &process->rule.limits;
    }

    if (process->rule.has & controller_rule_has_scheduler_d) {
      execute_set.as.scheduler = &process->rule.scheduler;
    }

    if (process->rule.has & controller_rule_has_nice_d) {
      execute_set.as.nice = &process->rule.nice;
    }

    if (process->rule.has & controller_rule_has_user_d) {
      execute_set.as.id_user = &process->rule.user;
    }

    if (process->rule.has & controller_rule_has_environment_d) {
      status = fl_environment_load_names(process->rule.environment, &environment);

      if (F_status_is_error(status)) {
        controller_print_error(global->thread, &global->main->program.error, F_status_set_fine(status), "fl_environment_load_names", F_true);

        return status;
      }

      // When a "define" from the entry/exit is in the "environment", add it to the exported environments (and overwrite any existing environment variable of the same name).
      controller_entry_t *entry = 0;

      if (process->type == controller_data_type_entry_e) {
        entry = &global->setting->entry;
      }
      else if (process->type == controller_data_type_exit_e) {
        entry = &global->setting->exit;
      }

      if (entry) {
        for (i = 0; i < entry->define.used; ++i) {

          for (j = 0; j < process->rule.environment.used; ++j) {

            if (f_compare_dynamic(entry->define.array[i].key, process->rule.environment.array[j]) == F_equal_to) {

              for (k = 0; k < environment.used; ++k) {

                if (f_compare_dynamic(entry->define.array[i].key, environment.array[k].key) == F_equal_to) {

                  environment.array[k].value.used = 0;

                  status = f_string_dynamic_append(entry->define.array[i].value, &environment.array[k].value);

                  if (F_status_is_error(status)) {
                    controller_print_error(global->thread, &global->main->program.error, F_status_set_fine(status), "f_string_dynamic_append", F_true);

                    return status;
                  }

                  break;
                }
              } // for

              if (k == environment.used) {
                status = f_string_maps_append(entry->define.array[i], &environment);

                if (F_status_is_error(status)) {
                  controller_print_error(global->thread, &global->main->program.error, F_status_set_fine(status), "f_string_maps_append", F_true);

                  return status;
                }
              }

              break;
            }
          } // for
        } // for
      }

      // When a "define" is in the "environment", add it to the exported environments (and overwrite any existing environment variable of the same name).
      for (i = 0; i < process->rule.define.used; ++i) {

        for (j = 0; j < process->rule.environment.used; ++j) {

          if (f_compare_dynamic(process->rule.define.array[i].key, process->rule.environment.array[j]) == F_equal_to) {

            for (k = 0; k < environment.used; ++k) {

              if (f_compare_dynamic(process->rule.define.array[i].key, environment.array[k].key) == F_equal_to) {

                environment.array[k].value.used = 0;

                status = f_string_dynamic_append(process->rule.define.array[i].value, &environment.array[k].value);

                if (F_status_is_error(status)) {
                  controller_print_error(global->thread, &global->main->program.error, F_status_set_fine(status), "f_string_dynamic_append", F_true);

                  return status;
                }

                break;
              }
            } // for

            if (k == environment.used) {
              status = f_string_maps_append(process->rule.define.array[i], &environment);

              if (F_status_is_error(status)) {
                controller_print_error(global->thread, &global->main->program.error, F_status_set_fine(status), "f_string_maps_append", F_true);

                return status;
              }
            }

            break;
          }
        } // for
      } // for
    }
    else {
      controller_entry_t *entry = 0;

      if (process->type == controller_data_type_entry_e) {
        entry = &global->setting->entry;
      }
      else if (process->type == controller_data_type_exit_e) {
        entry = &global->setting->exit;
      }

      // When a custom define is specified, it needs to be exported into the environment.
      if (entry->define.used || process->rule.define.used) {

        // Copy all environment variables over when a custom define is used.
        status = f_environment_get_all(&environment);

        if (F_status_is_error(status)) {
          controller_print_error(global->thread, &global->main->program.error, F_status_set_fine(status), "f_environment_get_all", F_true);

          return status;
        }

        for (i = 0; i < entry->define.used; ++i) {

          status = f_string_maps_append(entry->define.array[i], &environment);

          if (F_status_is_error(status)) {
            controller_print_error(global->thread, &global->main->program.error, F_status_set_fine(status), "f_string_maps_append", F_true);

            return status;
          }
        } // for

        for (i = 0; i < process->rule.define.used; ++i) {

          status = f_string_maps_append(process->rule.define.array[i], &environment);

          if (F_status_is_error(status)) {
            controller_print_error(global->thread, &global->main->program.error, F_status_set_fine(status), "f_string_maps_append", F_true);

            return status;
          }
        } // for
      }
      else {

        // When no custom environment variables are defined, just let the original environment pass through.
        execute_set.parameter.environment = 0;
      }
    }

    for (i = 0; i < process->rule.items.used && controller_thread_is_enabled_process(process, global->thread); ++i) {

      if (process->rule.items.array[i].type == controller_rule_item_type_settings_e) continue;

      for (j = 0; j < process->rule.items.array[i].actions.used; ++j) {

        if (!controller_thread_is_enabled_process(process, global->thread)) {
          status = F_status_set_error(F_interrupt);

          break;
        }

        if (process->rule.items.array[i].actions.array[j].type != action) continue;

        execute_set.parameter.data = 0;
        execute_set.parameter.option = FL_execute_parameter_option_threadsafe_d | FL_execute_parameter_option_return_d;

        if (process->rule.items.array[i].with & controller_with_full_path_d) {
          execute_set.parameter.option |= FL_execute_parameter_option_path_d;
        }

        if (process->rule.items.array[i].with & controller_with_session_new_d) {
          execute_set.parameter.option |= FL_execute_parameter_option_session_d;
        }

        if (process->rule.items.array[i].type == controller_rule_item_type_command_e) {
          status = controller_rule_expand(global, process->rule.items.array[i].actions.array[j], process);

          if (F_status_is_error(status)) {
            controller_rule_print_error(global->thread, &global->main->program.error, process->cache.action, F_status_set_fine(status), "controller_rule_expand", F_true, F_false);

            break;
          }

          do {
            status = controller_rule_execute_foreground(process->rule.items.array[i].type, f_string_empty_s, process->cache.expanded, options, &execute_set, process);

            if (status == F_child || F_status_set_fine(status) == F_interrupt || F_status_set_fine(status) == F_lock) break;
            if (F_status_is_error(status) && F_status_set_fine(status) != F_failure) break;

          } while (controller_rule_execute_rerun(controller_rule_action_type_to_action_execute_type(action), process, &process->rule.items.array[i]) > 0);

          if (status == F_child || F_status_set_fine(status) == F_interrupt || F_status_set_fine(status) == F_lock) break;

          if (F_status_is_error(status)) {
            process->rule.items.array[i].actions.array[j].status = F_status_set_error(F_failure);

            if (!(options & controller_process_option_simulate_d)) break;

            success = F_status_set_error(F_failure);
          }
          else if (success == F_false || success == F_ignore) {
            success = F_true;
          }
        }
        else if (process->rule.items.array[i].type == controller_rule_item_type_script_e) {
          status = controller_rule_expand(global, process->rule.items.array[i].actions.array[j], process);

          if (F_status_is_error(status)) {
            controller_rule_print_error(global->thread, &global->main->program.error, process->cache.action, F_status_set_fine(status), "controller_rule_expand", F_true, F_false);

            break;
          }

          if (process->cache.expanded.used) {
            execute_set.parameter.data = &process->cache.expanded.array[0];
          }
          else {
            execute_set.parameter.data = 0;
          }

          do {
            if (process->rule.engine.used) {
              status = controller_rule_execute_foreground(process->rule.items.array[i].type, process->rule.engine, process->rule.engine_arguments, options, &execute_set, process);
            }
            else {
              status = controller_rule_execute_foreground(process->rule.items.array[i].type, *global->main->setting.default_engine, process->rule.engine_arguments, options, &execute_set, process);
            }

            if (status == F_child || F_status_set_fine(status) == F_lock) break;
            if (F_status_is_error(status) && F_status_set_fine(status) != F_failure) break;

          } while (controller_rule_execute_rerun(controller_rule_action_type_to_action_execute_type(action), process, &process->rule.items.array[i]) > 0);

          if (status == F_child || F_status_set_fine(status) == F_interrupt || F_status_set_fine(status) == F_lock) break;

          if (F_status_is_error(status)) {
            process->rule.items.array[i].actions.array[j].status = F_status_set_error(F_failure);

            if (!(options & controller_process_option_simulate_d)) break;

            success = F_status_set_error(F_failure);
          }
          else if (success == F_false || success == F_ignore) {
            success = F_true;
          }
        }
        else if (process->rule.items.array[i].type == controller_rule_item_type_service_e) {
          status = controller_rule_expand(global, process->rule.items.array[i].actions.array[j], process);

          if (F_status_is_error(status)) {
            controller_rule_print_error(global->thread, &global->main->program.error, process->cache.action, F_status_set_fine(status), "controller_rule_expand", F_true, F_false);

            break;
          }

          if (process->rule.items.array[i].pid_file.used) {
            do {
              status = controller_rule_execute_pid_with(process->rule.items.array[i].pid_file, process->rule.items.array[i].type, f_string_empty_s, process->cache.expanded, options, process->rule.items.array[i].with, &execute_set, process);

              if (status == F_child || F_status_set_fine(status) == F_interrupt || F_status_set_fine(status) == F_lock) break;
              if (F_status_is_error(status) && F_status_set_fine(status) != F_failure) break;

            } while (controller_rule_execute_rerun(controller_rule_action_type_to_action_execute_type(action), process, &process->rule.items.array[i]) > 0);

            if (status == F_child || F_status_set_fine(status) == F_interrupt || F_status_set_fine(status) == F_lock) break;

            if (F_status_is_error(status)) {
              process->rule.items.array[i].actions.array[j].status = F_status_set_error(F_failure);

              if (!(options & controller_process_option_simulate_d)) break;

              success = F_status_set_error(F_failure);
            }
            else if (success == F_false || success == F_ignore) {
              success = F_true;
            }
          }
          else {
            success = F_status_set_error(F_failure);

            controller_rule_action_print_error_missing_pid(&global->main->program.error, process->rule.alias);
          }
        }
        else if (process->rule.items.array[i].type == controller_rule_item_type_utility_e) {
          if (process->rule.items.array[i].pid_file.used) {
            status = controller_rule_expand(global, process->rule.items.array[i].actions.array[j], process);

            if (F_status_is_error(status)) {
              controller_rule_print_error(global->thread, &global->main->program.error, process->cache.action, F_status_set_fine(status), "controller_rule_expand", F_true, F_false);

              break;
            }

            if (process->cache.expanded.used) {
              execute_set.parameter.data = &process->cache.expanded.array[0];
            }
            else {
              execute_set.parameter.data = 0;
            }

            do {
              status = controller_rule_execute_pid_with(process->rule.items.array[i].pid_file, process->rule.items.array[i].type, process->rule.engine.used ? process->rule.engine : *global->main->setting.default_engine, process->rule.engine_arguments, options, process->rule.items.array[i].with, &execute_set, process);

              if (status == F_child || F_status_set_fine(status) == F_interrupt || F_status_set_fine(status) == F_lock) break;
              if (F_status_is_error(status) && F_status_set_fine(status) != F_failure) break;

            } while (controller_rule_execute_rerun(controller_rule_action_type_to_action_execute_type(action), process, &process->rule.items.array[i]) > 0);

            if (status == F_child || F_status_set_fine(status) == F_interrupt || F_status_set_fine(status) == F_lock) break;

            if (F_status_is_error(status)) {
              process->rule.items.array[i].actions.array[j].status = F_status_set_error(F_failure);

              if (!(options & controller_process_option_simulate_d)) break;

              success = F_status_set_error(F_failure);
            }
            else if (success == F_false || success == F_ignore) {
              success = F_true;
            }
          }
          else {
            success = F_status_set_error(F_failure);

            controller_rule_action_print_error_missing_pid(&global->main->program.error, process->rule.alias);
          }
        }
        else {
          if (global->main->program.warning.verbosity == f_console_verbosity_debug_e) {
            controller_lock_print(global->main->program.warning.to, global->thread);

            fl_print_format("%r%[%QAction type is unknown, ignoring.%]%r", global->main->program.warning.to, f_string_eol_s, global->main->program.warning.context, global->main->program.warning.prefix, global->main->program.warning.context, f_string_eol_s);

            controller_rule_print_rule_message_cache(&global->main->program.warning, process->cache.action, F_true);

            controller_unlock_print_flush(global->main->program.warning.to, global->thread);
          }

          if (success == F_false) {
            success = F_ignore;
          }

          continue;
        }
      } // for

      if (status == F_child || F_status_set_fine(status) == F_interrupt || F_status_is_error(status) && !(options & controller_process_option_simulate_d)) {
         break;
       }
    } // for

    f_memory_arrays_resize(0, sizeof(f_string_map_t), (void **) &environment.array, &environment.used, &environment.size, &f_string_maps_delete_callback);

    // Lock failed, attempt to re-establish lock before returning.
    if (F_status_set_fine(status) == F_lock) {
      status = controller_lock_read(process, global->thread, &process->lock);
      if (F_status_is_error(status)) return F_status_set_error(F_lock);

      success = F_false;
    }

    if (!controller_thread_is_enabled_process(process, global->thread)) {
      return F_status_set_error(F_interrupt);
    }

    if (status == F_child || F_status_is_error(status)) {
      return status;
    }

    if (success == F_false || success == F_failure) {
      return F_status_set_error(F_failure);
    }

    if (success == F_ignore) {
      return F_ignore;
    }

    return F_okay;
  }
#endif // _di_controller_rule_execute_

#ifndef _di_controller_rule_execute_foreground_
  f_status_t controller_rule_execute_foreground(const uint8_t type, const f_string_static_t program, const f_string_statics_t arguments, const uint8_t options, controller_execute_set_t * const execute_set, controller_instance_t * const instance) {

    if (!instance) return F_status_set_error(F_parameter);

    f_status_t status = F_okay;
    f_status_t status_lock = F_okay;

    controller_main_t * const main = (controller_main_t *) process->main_data;
    controller_thread_t * const thread = (controller_thread_t *) process->main_thread;

    f_execute_result_t result = f_execute_result_t_initialize;

    status = controller_pids_increase(&process->childs);

    if (F_status_is_error(status)) {
      controller_print_error(thread, &global->main->program.error, F_status_set_fine(status), "controller_pids_increase", F_true);

      return status;
    }

    pid_t *child = 0;

    {
      f_number_unsigned_t i = 0;

      while (i < process->childs.used && process->childs.array[i]) {
        ++i;
      } // while

      child = &process->childs.array[i];

      if (i == process->childs.used) {
        ++process->childs.used;
      }
    }

    if (options & controller_process_option_simulate_d) {
      if (main->program.output.verbosity != f_console_verbosity_quiet_e) {
        controller_lock_print(main->program.output.to, thread);

        fl_print_format("%rSimulating execution of '%[", main->program.output.to, f_string_eol_s, main->program.context.set.title);

        if (program.used) {
          f_print_dynamic_safely(program, main->program.output.to);
        }
        else {
          f_print_dynamic_safely(arguments.array[0], main->program.output.to);
        }

        fl_print_format("%]' with the arguments: '%[", main->program.output.to, main->program.context.set.title, main->program.context.set.important);

        for (f_number_unsigned_t i = program.used ? 0 : 1; i < arguments.used; ++i) {

          if (program.used && i || !program.used && i > 1) {
            f_print_dynamic_raw(f_string_space_s, main->program.output.to);
          }

          f_print_dynamic_safely(arguments.array[i], main->program.output.to);
        } // for

        fl_print_format("%]' from '", main->program.output.to, main->program.context.set.important);
        fl_print_format("%[%Q%]'.%r", main->program.output.to, main->program.context.set.notable, process->rule.name, main->program.context.set.notable, f_string_eol_s);

        controller_unlock_print_flush(main->program.output.to, thread);
      }

      // Sleep for less than a second to better show simulation of synchronous vs asynchronous.
      {
        const f_time_spec_t delay = controller_time_milliseconds(controller_thread_simulation_timeout_d);

        if (controller_time_sleep_nanoseconds(main, (controller_process_t *) process->main_setting, delay) == -1) {
          status = F_status_set_error(F_interrupt);
        }
      }

      if (F_status_set_fine(status) != F_interrupt) {
        fl_execute_parameter_t simulated_parameter = macro_fl_execute_parameter_t_initialize_1(execute_set->parameter.option, execute_set->parameter.wait, process->rule.has & controller_rule_has_environment_d ? execute_set->parameter.environment : 0, execute_set->parameter.signals, &f_string_empty_s);

        status = fll_execute_program(*main->setting.default_engine, process->rule.engine_arguments, &simulated_parameter, &execute_set->as, (void *) &result);
      }
    }
    else {
      status = fll_execute_program(program, arguments, &execute_set->parameter, &execute_set->as, (void *) &result);
    }

    if (status == F_parent) {
      const pid_t id_child = result.pid;
      result.status = 0;

      f_thread_unlock(&process->lock);

      status_lock = controller_lock_write_process(process, thread, &process->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(&global->main->program.error, F_status_set_fine(status_lock), F_false, thread);

        if (F_status_set_fine(status_lock) != F_interrupt) {
          status = controller_lock_read_process(process, thread, &process->lock);

          if (status == F_okay) {
            return status_lock;
          }
        }

        return F_status_set_error(F_lock);
      }

      // Assign the child process id to allow for the cancel process to send appropriate termination signals to the child process.
      *child = id_child;

      f_thread_unlock(&process->lock);

      status_lock = controller_lock_read_process(process, thread, &process->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(&global->main->program.error, F_status_set_fine(status_lock), F_true, thread);
      }

      if (F_status_set_fine(status_lock) != F_interrupt) {

        // Have the parent wait for the child process to finish.
        waitpid(id_child, &result.status, 0);
      }

      if (F_status_set_fine(status_lock) == F_interrupt || !controller_thread_is_enabled_process(process, thread)) {
        if (status_lock == F_okay) {
          return F_status_set_error(F_interrupt);
        }

        return F_status_set_error(F_lock);
      }

      if (status_lock == F_okay) {
        f_thread_unlock(&process->lock);
      }

      status_lock = controller_lock_write_process(process, thread, &process->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(&global->main->program.error, F_status_set_fine(status_lock), F_false, thread);

        if (F_status_set_fine(status_lock) != F_interrupt) {
          status = controller_lock_read_process(process, thread, &process->lock);

          if (status == F_okay) {
            return status_lock;
          }
        }

        return F_status_set_error(F_lock);
      }

      process->result = result.status;

      // Remove the pid now that waidpid() has returned.
      *child = 0;

      f_thread_unlock(&process->lock);

      status_lock = controller_lock_read_process(process, thread, &process->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(&global->main->program.error, F_status_set_fine(status_lock), F_true, thread);

        return F_status_set_error(F_lock);
      }

      if (WIFEXITED(result.status) ? WEXITSTATUS(result.status) : 0) {
        status = F_status_set_error(F_failure);
      }
      else {
        status = F_okay;
      }
    }
    else {
      main->program.child = result.status;

      if (!controller_thread_is_enabled_process(process, thread)) {
        return F_status_set_error(F_interrupt);
      }
    }

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      if (status == F_child || status == F_capability || status == F_group || status == F_nice || status == F_user) {
        status = F_child;
      }
      else {
        status = F_status_set_error(status);
      }
    }

    if (status == F_child || F_status_set_fine(status) == F_interrupt) {
      return status;
    }

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      if ((WIFEXITED(process->result) && WEXITSTATUS(process->result)) || status == F_control_group || status == F_failure || status == F_limit || status == F_processor || status == F_schedule) {
        controller_rule_item_print_error_execute(type == controller_rule_item_type_script_e, program.used ? program : arguments.array[0], status, process);
      }
      else {
        controller_print_error(thread, &global->main->program.error, F_status_set_fine(status), "fll_execute_program", F_true);
      }

      status = F_status_set_error(status);
    }

    return status;
  }
#endif // _di_controller_rule_execute_foreground_

#ifndef _di_controller_rule_execute_pid_with_
  f_status_t controller_rule_execute_pid_with(const f_string_dynamic_t pid_file, const uint8_t type, const f_string_static_t program, const f_string_statics_t arguments, const uint8_t options, const uint8_t with, controller_execute_set_t * const execute_set, controller_instance_t * const instance) {

    if (!execute_set || !instance) return F_status_set_error(F_parameter);

    f_status_t status = F_okay;
    f_status_t status_lock = F_okay;

    controller_main_t * const main = (controller_main_t *) process->main_data;
    controller_thread_t * const thread = (controller_thread_t *) process->main_thread;

    f_execute_result_t result = f_execute_result_t_initialize;

    status = controller_pids_increase(&process->childs);

    if (F_status_is_error(status)) {
      controller_print_error(thread, &global->main->program.error, F_status_set_fine(status), "controller_pids_increase", F_true);

      return status;
    }

    status = f_memory_array_increase(controller_common_allocation_small_d, sizeof(f_string_dynamic_t), (void **) &process->path_pids.array, &process->path_pids.used, &process->path_pids.size);

    if (F_status_is_error(status)) {
      controller_print_error(thread, &global->main->program.error, F_status_set_fine(status), "f_memory_array_increase", F_true);

      return status;
    }

    pid_t *child = 0;
    f_string_dynamic_t *child_pid_file = 0;

    {
      f_number_unsigned_t i = 0;

      while (i < process->childs.used && process->childs.array[i]) {
        ++i;
      } // while

      child = &process->childs.array[i];

      if (i == process->childs.used) {
        ++process->childs.used;
      }

      i = 0;

      while (i < process->path_pids.used && process->path_pids.array[i].used) {
        ++i;
      } // while

      child_pid_file = &process->path_pids.array[i];

      if (i == process->path_pids.used) {
        ++process->path_pids.used;
      }
    }

    status = f_file_exists(pid_file, F_true);

    if (F_status_is_error(status)) {
      controller_print_error_file(thread, &global->main->program.error, F_status_set_fine(status), "f_file_exists", F_true, pid_file, f_file_operation_find_s, fll_error_file_type_file_e);

      return status;
    }

    if (status == F_true) {
      controller_print_error_file(thread, &global->main->program.error, F_file_found, "f_file_exists", F_true, pid_file, f_file_operation_find_s, fll_error_file_type_file_e);

      return F_status_set_error(F_file_found);
    }

    status = f_string_dynamic_append_nulless(pid_file, child_pid_file);

    if (F_status_is_error(status)) {
      controller_print_error(thread, &global->main->program.error, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true);

      return status;
    }

    if (options & controller_process_option_simulate_d) {
      if (main->program.error.verbosity > f_console_verbosity_error_e) {
        controller_lock_print(main->program.error.to, thread);

        fl_print_format("%rSimulating execution of '%[", main->program.error.to, f_string_eol_s, main->program.context.set.title);

        if (program.used) {
          f_print_dynamic_safely(program, main->program.error.to);
        }
        else {
          f_print_dynamic_safely(arguments.array[0], main->program.error.to);
        }

        fl_print_format("%]' with the arguments: '%[", main->program.error.to, main->program.context.set.title, main->program.context.set.important);

        for (f_number_unsigned_t i = program.used ? 0 : 1; i < arguments.used; ++i) {

          if (program.used && i || !program.used && i > 1) {
            f_print_dynamic_raw(f_string_space_s, main->program.error.to);
          }

          f_print_dynamic_safely(arguments.array[i], main->program.error.to);
        } // for

        fl_print_format("%]' from '", main->program.error.to, main->program.context.set.important);
        fl_print_format("%[%Q%]'.%r", main->program.error.to, main->program.context.set.notable, process->rule.name, main->program.context.set.notable, f_string_eol_s);

        controller_unlock_print_flush(main->program.error.to, thread);
      }

      // Sleep for less than a second to better show simulation of synchronous vs asynchronous.
      {
        const f_time_spec_t delay = controller_time_milliseconds(controller_thread_simulation_timeout_d);

        if (controller_time_sleep_nanoseconds(main, (controller_process_t *) process->main_setting, delay) == -1) {
          status = F_status_set_error(F_interrupt);
        }
      }

      if (F_status_set_fine(status) != F_interrupt) {
        const f_string_statics_t simulated_arguments = f_string_statics_t_initialize;
        fl_execute_parameter_t simulated_parameter = macro_fl_execute_parameter_t_initialize_1(execute_set->parameter.option, execute_set->parameter.wait, process->rule.has & controller_rule_has_environment_d ? execute_set->parameter.environment : 0, execute_set->parameter.signals, &f_string_empty_s);

        status = fll_execute_program(*main->setting.default_engine, simulated_arguments, &simulated_parameter, &execute_set->as, (void *) &result);
      }
    }
    else {
      status = fll_execute_program(program, arguments, &execute_set->parameter, &execute_set->as, (void *) &result);
    }

    if (status == F_parent) {
      const pid_t id_child = result.pid;
      result.status = 0;

      f_thread_unlock(&process->lock);

      status_lock = controller_lock_write_process(process, thread, &process->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(&global->main->program.error, F_status_set_fine(status_lock), F_false, thread);

        if (F_status_set_fine(status_lock) != F_interrupt) {
          status = controller_lock_read_process(process, thread, &process->lock);

          if (status == F_okay) {
            return status_lock;
          }
        }

        return F_status_set_error(F_lock);
      }

      // Assign the child process id to allow for the cancel process to send appropriate termination signals to the child process.
      *child = id_child;

      f_thread_unlock(&process->lock);

      status_lock = controller_lock_read_process(process, thread, &process->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(&global->main->program.error, F_status_set_fine(status_lock), F_true, thread);
      }

      if (F_status_set_fine(status_lock) != F_interrupt) {

        // The child process should perform the change into background, therefore it is safe to wait for the child to exit (another process is spawned).
        waitpid(id_child, &result.status, 0);
      }

      if (!controller_thread_is_enabled_process(process, thread)) {
        if (status_lock == F_okay) {
          return F_status_set_error(F_interrupt);
        }

        return F_status_set_error(F_lock);
      }

      if (status_lock == F_okay) {
        f_thread_unlock(&process->lock);
      }

      status_lock = controller_lock_write_process(process, thread, &process->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(&global->main->program.error, F_status_set_fine(status_lock), F_false, thread);

        if (F_status_set_fine(status_lock) != F_interrupt) {
          status = controller_lock_read_process(process, thread, &process->lock);

          if (status == F_okay) {
            return status_lock;
          }
        }

        return F_status_set_error(F_lock);
      }

      process->result = result.status;

      // Remove the pid now that waidpid() has returned.
      *child = 0;

      f_thread_unlock(&process->lock);

      status_lock = controller_lock_read_process(process, thread, &process->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(&global->main->program.error, F_status_set_fine(status_lock), F_true, thread);

        return F_status_set_error(F_lock);
      }

      if (WIFEXITED(result.status) ? WEXITSTATUS(result.status) : 0) {
        status = F_status_set_error(F_failure);
      }
      else {
        status = F_okay;
      }
    }
    else {
      main->program.child = result.status;

      if (!controller_thread_is_enabled_process(process, thread)) {
        return F_status_set_error(F_interrupt);
      }
    }

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      if (status == F_child || status == F_capability || status == F_group || status == F_nice || status == F_user) {
        status = F_child;
      }
      else {
        status = F_status_set_error(status);
      }
    }

    if (status == F_child || F_status_set_fine(status) == F_interrupt) {
      return status;
    }

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      if ((WIFEXITED(process->result) && WEXITSTATUS(process->result)) || status == F_control_group || status == F_failure || status == F_limit || status == F_processor || status == F_schedule) {
        controller_rule_item_print_error_execute(type == controller_rule_item_type_utility_e, program.used ? program : arguments.array[0], status, process);
      }
      else {
        controller_print_error(thread, &global->main->program.error, F_status_set_fine(status), "fll_execute_program", F_true);
      }

      return F_status_set_error(status);
    }

    return status;
  }
#endif // _di_controller_rule_execute_pid_with_

#ifndef _di_controller_rule_execute_rerun_
  int8_t controller_rule_execute_rerun(const uint8_t action, controller_instance_t * const instance, controller_rule_item_t * const item) {

    if (!instance || !item) return F_status_set_error(F_parameter);

    const int result = WIFEXITED(process->result) ? WEXITSTATUS(process->result) : 0;

    if (item->reruns[action].is & (result ? controller_rule_rerun_is_failure_d : controller_rule_rerun_is_success_d)) {
      controller_main_t * const main = (controller_main_t *) process->main_data;
      controller_thread_t * const thread = (controller_thread_t *) process->main_thread;
      controller_rule_rerun_item_t *rerun_item = result ? &item->reruns[action].failure : &item->reruns[action].success;

      if (!controller_thread_is_enabled_process(process, thread)) return -2;

      if (!rerun_item->max || rerun_item->count < rerun_item->max) {
        if (main->program.error.verbosity == f_console_verbosity_debug_e) {
          controller_lock_print(main->program.output.to, thread);

          fl_print_format("%rRe-running '", main->program.output.to, f_string_eol_s);
          fl_print_format("%[%r%]' '", main->program.output.to, main->program.context.set.title, process->rule.alias, main->program.context.set.title);
          fl_print_format("%[%r%]' with a ", main->program.output.to, main->program.context.set.notable, controller_rule_action_execute_type_name(action), main->program.context.set.notable);
          fl_print_format("%[%r%] of ", main->program.output.to, main->program.context.set.notable, controller_delay_s, main->program.context.set.notable);
          fl_print_format("%[%ul%] MegaTime", main->program.output.to, main->program.context.set.notable, rerun_item->delay, main->program.context.set.notable);

          if (rerun_item->max) {
            fl_print_format(" for %[%ul%]", main->program.output.to, main->program.context.set.notable, rerun_item->count, main->program.context.set.notable);
            fl_print_format(" of %[%r%] ", main->program.output.to, main->program.context.set.notable, controller_max_s, main->program.context.set.notable);
            fl_print_format(f_string_format_un_single_s.string, main->program.output.to, main->program.context.set.notable, rerun_item->max, main->program.context.set.notable);
            fl_print_format(".%r", main->program.output.to, f_string_eol_s);
          }
          else {
            fl_print_format(" with no %[%r%].%r", main->program.output.to, main->program.context.set.notable, controller_max_s, main->program.context.set.notable, f_string_eol_s);
          }

          controller_unlock_print_flush(main->program.output.to, thread);
        }

        if (rerun_item->delay) {
          const f_time_spec_t delay = controller_time_milliseconds(rerun_item->delay);

          if (controller_time_sleep_nanoseconds(main, (controller_process_t *) process->main_setting, delay) == -1) {
            return -1;
          }

          if (!controller_thread_is_enabled_process(process, thread)) return -2;
        }

        if (item->reruns[action].is & (result ? controller_rule_rerun_is_failure_reset_d : controller_rule_rerun_is_success_reset_d)) {
          if (result) {
            item->reruns[action].success.count = 0;
          }
          else {
            item->reruns[action].failure.count = 0;
          }
        }

        if (rerun_item->max) {
          ++rerun_item->count;
        }

        return F_true;
      }
    }

    return F_false;
  }
#endif // _di_controller_rule_execute_rerun_

#ifdef __cplusplus
} // extern "C"
#endif
