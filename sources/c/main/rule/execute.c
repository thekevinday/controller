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

    if (instance->rule.affinity.used) {
      execute_set.as.affinity = &instance->rule.affinity;
    }

    if (instance->rule.capability) {
      execute_set.as.capability = instance->rule.capability;
    }

    if (instance->rule.has & controller_rule_has_cgroup_d) {
      execute_set.as.control_group = &instance->rule.cgroup;

      // Make sure all required cgroup directories exist.
      if (controller_rule_status_is_available(action, instance->rule)) {
        status = fll_control_group_prepare(instance->rule.cgroup);

        if (F_status_is_error(status)) {
          controller_main_print_error_file(&global->main->program.error, macro_controller_f(fll_control_group_prepare), instance->rule.cgroup.path, controller_print_rule_control_groups_prepare_s, fll_error_file_type_directory_e);

          return status;
        }
      }
    }

    if (instance->rule.has & controller_rule_has_group_d) {
      execute_set.as.id_group = &instance->rule.group;

      if (instance->rule.groups.used) {
        execute_set.as.id_groups = &instance->rule.groups;
      }
    }

    if (instance->rule.limits.used) {
      execute_set.as.limits = &instance->rule.limits;
    }

    if (instance->rule.has & controller_rule_has_scheduler_d) {
      execute_set.as.scheduler = &instance->rule.scheduler;
    }

    if (instance->rule.has & controller_rule_has_nice_d) {
      execute_set.as.nice = &instance->rule.nice;
    }

    if (instance->rule.has & controller_rule_has_user_d) {
      execute_set.as.id_user = &instance->rule.user;
    }

    if (instance->rule.has & controller_rule_has_environment_d) {
      status = fl_environment_load_names(instance->rule.environment, &environment);

      if (F_status_is_error(status)) {
        controller_main_print_error_status(&global->main->program.error, macro_controller_f(fl_environment_load_names), F_status_set_fine(status));

        return status;
      }

      // When a "define" from the entry/exit is in the "environment", add it to the exported environments (and overwrite any existing environment variable of the same name).
      controller_entry_t *entry = 0;

      if (instance->type == controller_instance_type_entry_e) {
        entry = &global->program->entry;
      }
      else if (instance->type == controller_instance_type_exit_e) {
        entry = &global->program->exit;
      }

      if (entry) {
        for (i = 0; i < entry->define.used; ++i) {

          for (j = 0; j < instance->rule.environment.used; ++j) {

            if (f_compare_dynamic(entry->define.array[i].key, instance->rule.environment.array[j]) == F_equal_to) {

              for (k = 0; k < environment.used; ++k) {

                if (f_compare_dynamic(entry->define.array[i].key, environment.array[k].key) == F_equal_to) {

                  environment.array[k].value.used = 0;

                  status = f_string_dynamic_append(entry->define.array[i].value, &environment.array[k].value);

                  if (F_status_is_error(status)) {
                    controller_main_print_error_status(&global->main->program.error, macro_controller_f(f_string_dynamic_append), F_status_set_fine(status));

                    return status;
                  }

                  break;
                }
              } // for

              if (k == environment.used) {
                status = f_string_maps_append(entry->define.array[i], &environment);

                if (F_status_is_error(status)) {
                  controller_main_print_error_status(&global->main->program.error, macro_controller_f(f_string_maps_append), F_status_set_fine(status));

                  return status;
                }
              }

              break;
            }
          } // for
        } // for
      }

      // When a "define" is in the "environment", add it to the exported environments (and overwrite any existing environment variable of the same name).
      for (i = 0; i < instance->rule.define.used; ++i) {

        for (j = 0; j < instance->rule.environment.used; ++j) {

          if (f_compare_dynamic(instance->rule.define.array[i].key, instance->rule.environment.array[j]) == F_equal_to) {

            for (k = 0; k < environment.used; ++k) {

              if (f_compare_dynamic(instance->rule.define.array[i].key, environment.array[k].key) == F_equal_to) {

                environment.array[k].value.used = 0;

                status = f_string_dynamic_append(instance->rule.define.array[i].value, &environment.array[k].value);

                if (F_status_is_error(status)) {
                  controller_main_print_error_status(&global->main->program.error, macro_controller_f(f_string_dynamic_append), F_status_set_fine(status));

                  return status;
                }

                break;
              }
            } // for

            if (k == environment.used) {
              status = f_string_maps_append(instance->rule.define.array[i], &environment);

              if (F_status_is_error(status)) {
                controller_main_print_error_status(&global->main->program.error, macro_controller_f(f_string_maps_append), F_status_set_fine(status));

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

      if (instance->type == controller_instance_type_entry_e) {
        entry = &global->program->entry;
      }
      else if (instance->type == controller_instance_type_exit_e) {
        entry = &global->program->exit;
      }

      // When a custom define is specified, it needs to be exported into the environment.
      if (entry->define.used || instance->rule.define.used) {

        // Copy all environment variables over when a custom define is used.
        status = f_environment_get_all(&environment);

        if (F_status_is_error(status)) {
          controller_main_print_error_status(&global->main->program.error, macro_controller_f(f_environment_get_all), F_status_set_fine(status));

          return status;
        }

        for (i = 0; i < entry->define.used; ++i) {

          status = f_string_maps_append(entry->define.array[i], &environment);

          if (F_status_is_error(status)) {
            controller_main_print_error_status(&global->main->program.error, macro_controller_f(f_string_maps_append), F_status_set_fine(status));

            return status;
          }
        } // for

        for (i = 0; i < instance->rule.define.used; ++i) {

          status = f_string_maps_append(instance->rule.define.array[i], &environment);

          if (F_status_is_error(status)) {
            controller_main_print_error_status(&global->main->program.error, macro_controller_f(f_string_maps_append), F_status_set_fine(status));

            return status;
          }
        } // for
      }
      else {

        // When no custom environment variables are defined, just let the original environment pass through.
        execute_set.parameter.environment = 0;
      }
    }

    for (i = 0; i < instance->rule.items.used && controller_main_thread_is_enabled_instance(instance, global->thread); ++i) {

      if (instance->rule.items.array[i].type == controller_rule_item_type_settings_e) continue;

      for (j = 0; j < instance->rule.items.array[i].actions.used; ++j) {

        if (!controller_main_thread_is_enabled_instance(instance, global->thread)) {
          status = F_status_set_error(F_interrupt);

          break;
        }

        if (instance->rule.items.array[i].actions.array[j].type != action) continue;

        execute_set.parameter.data = 0;
        execute_set.parameter.option = FL_execute_parameter_option_threadsafe_d | FL_execute_parameter_option_return_d;

        if (instance->rule.items.array[i].with & controller_with_full_path_d) {
          execute_set.parameter.option |= FL_execute_parameter_option_path_d;
        }

        if (instance->rule.items.array[i].with & controller_with_session_new_d) {
          execute_set.parameter.option |= FL_execute_parameter_option_session_d;
        }

        if (instance->rule.items.array[i].type == controller_rule_item_type_command_e) {
          status = controller_rule_expand(global, instance->rule.items.array[i].actions.array[j], instance);

          if (F_status_is_error(status)) {
            controller_rule_print_error(global->thread, &global->main->program.error, instance->cache.action, F_status_set_fine(status), "controller_rule_expand", F_true, F_false);

            break;
          }

          do {
            status = controller_rule_execute_foreground(instance->rule.items.array[i].type, f_string_empty_s, instance->cache.expanded, options, &execute_set, instance);

            if (status == F_child || F_status_set_fine(status) == F_interrupt || F_status_set_fine(status) == F_lock) break;
            if (F_status_is_error(status) && F_status_set_fine(status) != F_failure) break;

          } while (controller_rule_execute_rerun(controller_rule_action_type_to_action_execute_type(action), instance, &instance->rule.items.array[i]) > 0);

          if (status == F_child || F_status_set_fine(status) == F_interrupt || F_status_set_fine(status) == F_lock) break;

          if (F_status_is_error(status)) {
            instance->rule.items.array[i].actions.array[j].status = F_status_set_error(F_failure);

            if (!(options & controller_instance_option_simulate_e)) break;

            success = F_status_set_error(F_failure);
          }
          else if (success == F_false || success == F_ignore) {
            success = F_true;
          }
        }
        else if (instance->rule.items.array[i].type == controller_rule_item_type_script_e) {
          status = controller_rule_expand(global, instance->rule.items.array[i].actions.array[j], instance);

          if (F_status_is_error(status)) {
            controller_rule_print_error(global->thread, &global->main->program.error, instance->cache.action, F_status_set_fine(status), "controller_rule_expand", F_true, F_false);

            break;
          }

          if (instance->cache.expanded.used) {
            execute_set.parameter.data = &instance->cache.expanded.array[0];
          }
          else {
            execute_set.parameter.data = 0;
          }

          do {
            if (instance->rule.engine.used) {
              status = controller_rule_execute_foreground(instance->rule.items.array[i].type, instance->rule.engine, instance->rule.engine_arguments, options, &execute_set, instance);
            }
            else {
              status = controller_rule_execute_foreground(instance->rule.items.array[i].type, *global->main->setting.default_engine, instance->rule.engine_arguments, options, &execute_set, instance);
            }

            if (status == F_child || F_status_set_fine(status) == F_lock) break;
            if (F_status_is_error(status) && F_status_set_fine(status) != F_failure) break;

          } while (controller_rule_execute_rerun(controller_rule_action_type_to_action_execute_type(action), instance, &instance->rule.items.array[i]) > 0);

          if (status == F_child || F_status_set_fine(status) == F_interrupt || F_status_set_fine(status) == F_lock) break;

          if (F_status_is_error(status)) {
            instance->rule.items.array[i].actions.array[j].status = F_status_set_error(F_failure);

            if (!(options & controller_instance_option_simulate_e)) break;

            success = F_status_set_error(F_failure);
          }
          else if (success == F_false || success == F_ignore) {
            success = F_true;
          }
        }
        else if (instance->rule.items.array[i].type == controller_rule_item_type_service_e) {
          status = controller_rule_expand(global, instance->rule.items.array[i].actions.array[j], instance);

          if (F_status_is_error(status)) {
            controller_rule_print_error(global->thread, &global->main->program.error, instance->cache.action, F_status_set_fine(status), "controller_rule_expand", F_true, F_false);

            break;
          }

          if (instance->rule.items.array[i].pid_file.used) {
            do {
              status = controller_rule_execute_pid_with(instance->rule.items.array[i].pid_file, instance->rule.items.array[i].type, f_string_empty_s, instance->cache.expanded, options, instance->rule.items.array[i].with, &execute_set, instance);

              if (status == F_child || F_status_set_fine(status) == F_interrupt || F_status_set_fine(status) == F_lock) break;
              if (F_status_is_error(status) && F_status_set_fine(status) != F_failure) break;

            } while (controller_rule_execute_rerun(controller_rule_action_type_to_action_execute_type(action), instance, &instance->rule.items.array[i]) > 0);

            if (status == F_child || F_status_set_fine(status) == F_interrupt || F_status_set_fine(status) == F_lock) break;

            if (F_status_is_error(status)) {
              instance->rule.items.array[i].actions.array[j].status = F_status_set_error(F_failure);

              if (!(options & controller_instance_option_simulate_e)) break;

              success = F_status_set_error(F_failure);
            }
            else if (success == F_false || success == F_ignore) {
              success = F_true;
            }
          }
          else {
            success = F_status_set_error(F_failure);

            controller_rule_action_print_error_missing_pid(&global->main->program.error, instance->rule.alias);
          }
        }
        else if (instance->rule.items.array[i].type == controller_rule_item_type_utility_e) {
          if (instance->rule.items.array[i].pid_file.used) {
            status = controller_rule_expand(global, instance->rule.items.array[i].actions.array[j], instance);

            if (F_status_is_error(status)) {
              controller_rule_print_error(global->thread, &global->main->program.error, instance->cache.action, F_status_set_fine(status), "controller_rule_expand", F_true, F_false);

              break;
            }

            if (instance->cache.expanded.used) {
              execute_set.parameter.data = &instance->cache.expanded.array[0];
            }
            else {
              execute_set.parameter.data = 0;
            }

            do {
              status = controller_rule_execute_pid_with(instance->rule.items.array[i].pid_file, instance->rule.items.array[i].type, instance->rule.engine.used ? instance->rule.engine : *global->main->setting.default_engine, instance->rule.engine_arguments, options, instance->rule.items.array[i].with, &execute_set, instance);

              if (status == F_child || F_status_set_fine(status) == F_interrupt || F_status_set_fine(status) == F_lock) break;
              if (F_status_is_error(status) && F_status_set_fine(status) != F_failure) break;

            } while (controller_rule_execute_rerun(controller_rule_action_type_to_action_execute_type(action), instance, &instance->rule.items.array[i]) > 0);

            if (status == F_child || F_status_set_fine(status) == F_interrupt || F_status_set_fine(status) == F_lock) break;

            if (F_status_is_error(status)) {
              instance->rule.items.array[i].actions.array[j].status = F_status_set_error(F_failure);

              if (!(options & controller_instance_option_simulate_e)) break;

              success = F_status_set_error(F_failure);
            }
            else if (success == F_false || success == F_ignore) {
              success = F_true;
            }
          }
          else {
            success = F_status_set_error(F_failure);

            controller_rule_action_print_error_missing_pid(&global->main->program.error, instance->rule.alias);
          }
        }
        else {
          if (global->main->program.warning.verbosity == f_console_verbosity_debug_e) {
            controller_lock_print(global->main->program.warning.to, global->thread);

            fl_print_format("%r%[%QAction type is unknown, ignoring.%]%r", global->main->program.warning.to, f_string_eol_s, global->main->program.warning.context, global->main->program.warning.prefix, global->main->program.warning.context, f_string_eol_s);

            controller_rule_print_rule_message_cache(&global->main->program.warning, instance->cache.action, F_true);

            controller_unlock_print_flush(global->main->program.warning.to, global->thread);
          }

          if (success == F_false) {
            success = F_ignore;
          }

          continue;
        }
      } // for

      if (status == F_child || F_status_set_fine(status) == F_interrupt || F_status_is_error(status) && !(options & controller_instance_option_simulate_e)) {
         break;
       }
    } // for

    f_memory_arrays_resize(0, sizeof(f_string_map_t), (void **) &environment.array, &environment.used, &environment.size, &f_string_maps_delete_callback);

    // Lock failed, attempt to re-establish lock before returning.
    if (F_status_set_fine(status) == F_lock) {
      status = controller_lock_read(instance, global->thread, &instance->lock);
      if (F_status_is_error(status)) return F_status_set_error(F_lock);

      success = F_false;
    }

    if (!controller_main_thread_is_enabled_instance(instance, global->thread)) {
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

    controller_main_t * const main = (controller_main_t *) instance->main_data;
    controller_thread_t * const thread = (controller_thread_t *) instance->main_thread;

    f_execute_result_t result = f_execute_result_t_initialize;

    status = controller_pids_increase(&instance->childs);

    if (F_status_is_error(status)) {
      controller_main_print_error_status(&main->program.error, macro_controller_f(controller_pids_increase), F_status_set_fine(status));

      return status;
    }

    pid_t *child = 0;

    {
      f_number_unsigned_t i = 0;

      while (i < instance->childs.used && instance->childs.array[i]) {
        ++i;
      } // while

      child = &instance->childs.array[i];

      if (i == instance->childs.used) {
        ++instance->childs.used;
      }
    }

    if (options & controller_instance_option_simulate_e) {
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
        fl_print_format("%[%Q%]'.%r", main->program.output.to, main->program.context.set.notable, instance->rule.name, main->program.context.set.notable, f_string_eol_s);

        controller_unlock_print_flush(main->program.output.to, thread);
      }

      // Sleep for less than a second to better show simulation of synchronous vs asynchronous.
      {
        const f_time_spec_t delay = controller_time_milliseconds(controller_thread_simulation_timeout_d);

        if (controller_time_sleep_nanoseconds(main, (controller_process_t *) instance->main_setting, delay) == -1) {
          status = F_status_set_error(F_interrupt);
        }
      }

      if (F_status_set_fine(status) != F_interrupt) {
        fl_execute_parameter_t simulated_parameter = macro_fl_execute_parameter_t_initialize_1(execute_set->parameter.option, execute_set->parameter.wait, instance->rule.has & controller_rule_has_environment_d ? execute_set->parameter.environment : 0, execute_set->parameter.signals, &f_string_empty_s);

        status = fll_execute_program(*main->setting.default_engine, instance->rule.engine_arguments, &simulated_parameter, &execute_set->as, (void *) &result);
      }
    }
    else {
      status = fll_execute_program(program, arguments, &execute_set->parameter, &execute_set->as, (void *) &result);
    }

    if (status == F_parent) {
      const pid_t id_child = result.pid;
      result.status = 0;

      f_thread_unlock(&instance->lock);

      status_lock = controller_lock_write_process(instance, thread, &instance->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status_lock), F_false, thread);

        if (F_status_set_fine(status_lock) != F_interrupt) {
          status = controller_lock_read_process(instance, thread, &instance->lock);

          if (status == F_okay) {
            return status_lock;
          }
        }

        return F_status_set_error(F_lock);
      }

      // Assign the child instance id to allow for the cancel instance to send appropriate termination signals to the child instance.
      *child = id_child;

      f_thread_unlock(&instance->lock);

      status_lock = controller_lock_read_process(instance, thread, &instance->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status_lock), F_true, thread);
      }

      if (F_status_set_fine(status_lock) != F_interrupt) {

        // Have the parent wait for the child instance to finish.
        waitpid(id_child, &result.status, 0);
      }

      if (F_status_set_fine(status_lock) == F_interrupt || !controller_main_thread_is_enabled_instance(instance, thread)) {
        if (status_lock == F_okay) {
          return F_status_set_error(F_interrupt);
        }

        return F_status_set_error(F_lock);
      }

      if (status_lock == F_okay) {
        f_thread_unlock(&instance->lock);
      }

      status_lock = controller_lock_write_process(instance, thread, &instance->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status_lock), F_false, thread);

        if (F_status_set_fine(status_lock) != F_interrupt) {
          status = controller_lock_read_process(instance, thread, &instance->lock);

          if (status == F_okay) {
            return status_lock;
          }
        }

        return F_status_set_error(F_lock);
      }

      instance->result = result.status;

      // Remove the pid now that waidpid() has returned.
      *child = 0;

      f_thread_unlock(&instance->lock);

      status_lock = controller_lock_read_process(instance, thread, &instance->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status_lock), F_true, thread);

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

      if (!controller_main_thread_is_enabled_instance(instance, thread)) {
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

      if ((WIFEXITED(instance->result) && WEXITSTATUS(instance->result)) || status == F_control_group || status == F_failure || status == F_limit || status == F_processor || status == F_schedule) {
        controller_rule_item_print_error_execute(type == controller_rule_item_type_script_e, program.used ? program : arguments.array[0], status, instance);
      }
      else {
        controller_main_print_error_status(&main->program.error, macro_controller_f(fll_execute_program), F_status_set_fine(status));
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

    controller_main_t * const main = (controller_main_t *) instance->main_data;
    controller_thread_t * const thread = (controller_thread_t *) instance->main_thread;

    f_execute_result_t result = f_execute_result_t_initialize;

    status = controller_pids_increase(&instance->childs);

    if (F_status_is_error(status)) {
      controller_main_print_error_status(&main->program.error, macro_controller_f(controller_pids_increase), F_status_set_fine(status));

      return status;
    }

    status = f_memory_array_increase(controller_allocation_small_d, sizeof(f_string_dynamic_t), (void **) &instance->path_pids.array, &instance->path_pids.used, &instance->path_pids.size);

    if (F_status_is_error(status)) {
      controller_main_print_error_status(&main->program.error, macro_controller_f(f_memory_array_increase), F_status_set_fine(status));

      return status;
    }

    pid_t *child = 0;
    f_string_dynamic_t *child_pid_file = 0;

    {
      f_number_unsigned_t i = 0;

      while (i < instance->childs.used && instance->childs.array[i]) {
        ++i;
      } // while

      child = &instance->childs.array[i];

      if (i == instance->childs.used) {
        ++instance->childs.used;
      }

      i = 0;

      while (i < instance->path_pids.used && instance->path_pids.array[i].used) {
        ++i;
      } // while

      child_pid_file = &instance->path_pids.array[i];

      if (i == instance->path_pids.used) {
        ++instance->path_pids.used;
      }
    }

    status = f_file_exists(pid_file, F_true);

    if (F_status_is_error(status) || status == F_true) {
      controller_main_print_error_file_status(&main->program.error, macro_controller_f(f_file_exists), status == F_true ? F_file_found : F_status_set_fine(status), pid_file, f_file_operation_find_s, fll_error_file_type_file_e);

      return status;
    }

    status = f_string_dynamic_append_nulless(pid_file, child_pid_file);

    if (F_status_is_error(status)) {
      controller_main_print_error_status(&main->program.error, macro_controller_f(f_string_dynamic_append_nulless), F_status_set_fine(status));

      return status;
    }

    if (options & controller_instance_option_simulate_e) {
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
        fl_print_format("%[%Q%]'.%r", main->program.error.to, main->program.context.set.notable, instance->rule.name, main->program.context.set.notable, f_string_eol_s);

        controller_unlock_print_flush(main->program.error.to, thread);
      }

      // Sleep for less than a second to better show simulation of synchronous vs asynchronous.
      {
        const f_time_spec_t delay = controller_time_milliseconds(controller_thread_simulation_timeout_d);

        if (controller_time_sleep_nanoseconds(main, (controller_process_t *) instance->main_setting, delay) == -1) {
          status = F_status_set_error(F_interrupt);
        }
      }

      if (F_status_set_fine(status) != F_interrupt) {
        const f_string_statics_t simulated_arguments = f_string_statics_t_initialize;
        fl_execute_parameter_t simulated_parameter = macro_fl_execute_parameter_t_initialize_1(execute_set->parameter.option, execute_set->parameter.wait, instance->rule.has & controller_rule_has_environment_d ? execute_set->parameter.environment : 0, execute_set->parameter.signals, &f_string_empty_s);

        status = fll_execute_program(*main->setting.default_engine, simulated_arguments, &simulated_parameter, &execute_set->as, (void *) &result);
      }
    }
    else {
      status = fll_execute_program(program, arguments, &execute_set->parameter, &execute_set->as, (void *) &result);
    }

    if (status == F_parent) {
      const pid_t id_child = result.pid;
      result.status = 0;

      f_thread_unlock(&instance->lock);

      status_lock = controller_lock_write_process(instance, thread, &instance->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status_lock), F_false, thread);

        if (F_status_set_fine(status_lock) != F_interrupt) {
          status = controller_lock_read_process(instance, thread, &instance->lock);

          if (status == F_okay) {
            return status_lock;
          }
        }

        return F_status_set_error(F_lock);
      }

      // Assign the child instance id to allow for the cancel instance to send appropriate termination signals to the child instance.
      *child = id_child;

      f_thread_unlock(&instance->lock);

      status_lock = controller_lock_read_process(instance, thread, &instance->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status_lock), F_true, thread);
      }

      if (F_status_set_fine(status_lock) != F_interrupt) {

        // The child instance should perform the change into background, therefore it is safe to wait for the child to exit (another instance is spawned).
        waitpid(id_child, &result.status, 0);
      }

      if (!controller_main_thread_is_enabled_instance(instance, thread)) {
        if (status_lock == F_okay) {
          return F_status_set_error(F_interrupt);
        }

        return F_status_set_error(F_lock);
      }

      if (status_lock == F_okay) {
        f_thread_unlock(&instance->lock);
      }

      status_lock = controller_lock_write_process(instance, thread, &instance->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status_lock), F_false, thread);

        if (F_status_set_fine(status_lock) != F_interrupt) {
          status = controller_lock_read_process(instance, thread, &instance->lock);

          if (status == F_okay) {
            return status_lock;
          }
        }

        return F_status_set_error(F_lock);
      }

      instance->result = result.status;

      // Remove the pid now that waidpid() has returned.
      *child = 0;

      f_thread_unlock(&instance->lock);

      status_lock = controller_lock_read_process(instance, thread, &instance->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status_lock), F_true, thread);

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

      if (!controller_main_thread_is_enabled_instance(instance, thread)) {
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

      if ((WIFEXITED(instance->result) && WEXITSTATUS(instance->result)) || status == F_control_group || status == F_failure || status == F_limit || status == F_processor || status == F_schedule) {
        controller_rule_item_print_error_execute(type == controller_rule_item_type_utility_e, program.used ? program : arguments.array[0], status, instance);
      }
      else {
        controller_main_print_error_status(&main->program.error, macro_controller_f(fll_execute_program), F_status_set_fine(status));
      }

      return F_status_set_error(status);
    }

    return status;
  }
#endif // _di_controller_rule_execute_pid_with_

#ifndef _di_controller_rule_execute_rerun_
  int8_t controller_rule_execute_rerun(const uint8_t action, controller_instance_t * const instance, controller_rule_item_t * const item) {

    if (!instance || !item) return F_status_set_error(F_parameter);

    const int result = WIFEXITED(instance->result) ? WEXITSTATUS(instance->result) : 0;

    if (item->reruns[action].is & (result ? controller_rule_rerun_is_failure_d : controller_rule_rerun_is_success_d)) {
      controller_main_t * const main = (controller_main_t *) instance->main_data;
      controller_thread_t * const thread = (controller_thread_t *) instance->main_thread;
      controller_rule_rerun_item_t *rerun_item = result ? &item->reruns[action].failure : &item->reruns[action].success;

      if (!controller_main_thread_is_enabled_instance(instance, thread)) return -2;

      if (!rerun_item->max || rerun_item->count < rerun_item->max) {
        if (main->program.error.verbosity == f_console_verbosity_debug_e) {
          controller_lock_print(main->program.output.to, thread);

          fl_print_format("%rRe-running '", main->program.output.to, f_string_eol_s);
          fl_print_format("%[%r%]' '", main->program.output.to, main->program.context.set.title, instance->rule.alias, main->program.context.set.title);
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

          if (controller_time_sleep_nanoseconds(main, (controller_process_t *) instance->main_setting, delay) == -1) {
            return -1;
          }

          if (!controller_main_thread_is_enabled_instance(instance, thread)) return -2;
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
