#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_rule_execute_
  f_status_t controller_rule_execute(controller_t * const main, const uint8_t action, const uint8_t options, controller_instance_t * const instance) {

    if (!main || !instance) return F_status_set_error(F_parameter);

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
          controller_print_error_file(&main->program.error, macro_controller_f(fll_control_group_prepare), instance->rule.cgroup.path, controller_print_rule_control_groups_prepare_s, fll_error_file_type_directory_e);

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
        controller_print_error_status(&main->program.error, macro_controller_f(fl_environment_load_names), F_status_set_fine(status));

        return status;
      }

      // When a "define" from the entry/exit is in the "environment", add it to the exported environments (and overwrite any existing environment variable of the same name).
      controller_entry_t *entry = 0;

      if (instance->type == controller_instance_type_entry_e) {
        entry = &main->process.entry;
      }
      else if (instance->type == controller_instance_type_exit_e) {
        entry = &main->process.exit;
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
                    controller_print_error_status(&main->program.error, macro_controller_f(f_string_dynamic_append), F_status_set_fine(status));

                    return status;
                  }

                  break;
                }
              } // for

              if (k == environment.used) {
                status = f_string_maps_append(entry->define.array[i], &environment);

                if (F_status_is_error(status)) {
                  controller_print_error_status(&main->program.error, macro_controller_f(f_string_maps_append), F_status_set_fine(status));

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
                  controller_print_error_status(&main->program.error, macro_controller_f(f_string_dynamic_append), F_status_set_fine(status));

                  return status;
                }

                break;
              }
            } // for

            if (k == environment.used) {
              status = f_string_maps_append(instance->rule.define.array[i], &environment);

              if (F_status_is_error(status)) {
                controller_print_error_status(&main->program.error, macro_controller_f(f_string_maps_append), F_status_set_fine(status));

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
        entry = &main->process.entry;
      }
      else if (instance->type == controller_instance_type_exit_e) {
        entry = &main->process.exit;
      }

      // When a custom define is specified, it needs to be exported into the environment.
      if (entry->define.used || instance->rule.define.used) {

        // Copy all environment variables over when a custom define is used.
        status = f_environment_get_all(&environment);

        if (F_status_is_error(status)) {
          controller_print_error_status(&main->program.error, macro_controller_f(f_environment_get_all), F_status_set_fine(status));

          return status;
        }

        for (i = 0; i < entry->define.used; ++i) {

          status = f_string_maps_append(entry->define.array[i], &environment);

          if (F_status_is_error(status)) {
            controller_print_error_status(&main->program.error, macro_controller_f(f_string_maps_append), F_status_set_fine(status));

            return status;
          }
        } // for

        for (i = 0; i < instance->rule.define.used; ++i) {

          status = f_string_maps_append(instance->rule.define.array[i], &environment);

          if (F_status_is_error(status)) {
            controller_print_error_status(&main->program.error, macro_controller_f(f_string_maps_append), F_status_set_fine(status));

            return status;
          }
        } // for
      }
      else {

        // When no custom environment variables are defined, just let the original environment pass through.
        execute_set.parameter.environment = 0;
      }
    }

    for (i = 0; i < instance->rule.items.used && controller_thread_is_enabled_instance(instance); ++i) {

      if (instance->rule.items.array[i].type == controller_rule_item_type_settings_e) continue;

      for (j = 0; j < instance->rule.items.array[i].actions.used; ++j) {

        if (!controller_thread_is_enabled_instance(instance)) {
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
          status = controller_rule_expand(main, instance->rule.items.array[i].actions.array[j], instance);

          if (F_status_is_error(status)) {
            controller_print_error_rule(&main->program.error, &instance->cache.action, F_status_set_fine(status), macro_controller_f(controller_rule_expand), F_true, F_false);

            break;
          }

          do {
            status = controller_rule_execute_foreground(instance->rule.items.array[i].type, f_string_empty_s, instance->cache.expanded, options, &execute_set, instance);

            if (status == F_child || F_status_set_fine(status) == F_interrupt || F_status_set_fine(status) == F_lock) break;
            if (F_status_is_error(status) && F_status_set_fine(status) != F_failure) break;

          } while (controller_rule_execute_rerun(instance, &instance->rule.items.array[i], controller_rule_action_type_to_action_execute_type(action)) > 0);

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
          status = controller_rule_expand(main, instance->rule.items.array[i].actions.array[j], instance);

          if (F_status_is_error(status)) {
            controller_print_error_rule(&main->program.error, &instance->cache.action, F_status_set_fine(status), macro_controller_f(controller_rule_expand), F_true, F_false);

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
              status = controller_rule_execute_foreground(instance->rule.items.array[i].type, controller_default_engine_s, instance->rule.engine_arguments, options, &execute_set, instance);
            }

            if (status == F_child || F_status_set_fine(status) == F_lock) break;
            if (F_status_is_error(status) && F_status_set_fine(status) != F_failure) break;

          } while (controller_rule_execute_rerun(instance, &instance->rule.items.array[i], controller_rule_action_type_to_action_execute_type(action)) > 0);

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
          status = controller_rule_expand(main, instance->rule.items.array[i].actions.array[j], instance);

          if (F_status_is_error(status)) {
            controller_print_error_rule(&main->program.error, &instance->cache.action, F_status_set_fine(status), macro_controller_f(controller_rule_expand), F_true, F_false);

            break;
          }

          if (instance->rule.items.array[i].pid_file.used) {
            do {
              status = controller_rule_execute_pid_with(instance->rule.items.array[i].pid_file, instance->rule.items.array[i].type, f_string_empty_s, instance->cache.expanded, options, instance->rule.items.array[i].with, &execute_set, instance);

              if (status == F_child || F_status_set_fine(status) == F_interrupt || F_status_set_fine(status) == F_lock) break;
              if (F_status_is_error(status) && F_status_set_fine(status) != F_failure) break;

            } while (controller_rule_execute_rerun(instance, &instance->rule.items.array[i], controller_rule_action_type_to_action_execute_type(action)) > 0);

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

            controller_print_error_rule_action_missing_pid(&main->program.error, instance->rule.alias);
          }
        }
        else if (instance->rule.items.array[i].type == controller_rule_item_type_utility_e) {
          if (instance->rule.items.array[i].pid_file.used) {
            status = controller_rule_expand(main, instance->rule.items.array[i].actions.array[j], instance);

            if (F_status_is_error(status)) {
              controller_print_error_rule(&main->program.error, &instance->cache.action, F_status_set_fine(status), macro_controller_f(controller_rule_expand), F_true, F_false);

              break;
            }

            if (instance->cache.expanded.used) {
              execute_set.parameter.data = &instance->cache.expanded.array[0];
            }
            else {
              execute_set.parameter.data = 0;
            }

            do {
              status = controller_rule_execute_pid_with(instance->rule.items.array[i].pid_file, instance->rule.items.array[i].type, instance->rule.engine.used ? instance->rule.engine : controller_default_engine_s, instance->rule.engine_arguments, options, instance->rule.items.array[i].with, &execute_set, instance);

              if (status == F_child || F_status_set_fine(status) == F_interrupt || F_status_set_fine(status) == F_lock) break;
              if (F_status_is_error(status) && F_status_set_fine(status) != F_failure) break;

            } while (controller_rule_execute_rerun(instance, &instance->rule.items.array[i], controller_rule_action_type_to_action_execute_type(action)) > 0);

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

            controller_print_error_rule_action_missing_pid(&main->program.error, instance->rule.alias);
          }
        }
        else {
          controller_print_warning_rule_action_unknown(&main->program.warning, &instance->cache);

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
      status = controller_lock_read(instance->type != controller_instance_type_exit_e, &main->thread, &instance->lock);
      if (F_status_is_error(status)) return F_status_set_error(F_lock);

      success = F_false;
    }

    if (!controller_thread_is_enabled_instance(instance)) return F_status_set_error(F_interrupt);
    if (status == F_child || F_status_is_error(status)) return status;
    if (success == F_false || success == F_failure) return F_status_set_error(F_failure);
    if (success == F_ignore) return F_ignore;

    return F_okay;
  }
#endif // _di_controller_rule_execute_

#ifndef _di_controller_rule_execute_foreground_
  f_status_t controller_rule_execute_foreground(const uint8_t type, const f_string_static_t program, const f_string_statics_t arguments, const uint8_t options, controller_execute_set_t * const execute_set, controller_instance_t * const instance) {

    if (!instance || !instance->main) return F_status_set_error(F_parameter);

    f_status_t status = F_okay;
    f_status_t status_lock = F_okay;

    controller_t * const main = instance->main;

    f_execute_result_t result = f_execute_result_t_initialize;

    status = f_memory_array_increase(controller_allocation_small_d, sizeof(pid_t), (void **) &instance->childs.array, &instance->childs.used, &instance->childs.size);

    if (F_status_is_error(status)) {
      controller_print_error_status(&main->program.error, macro_controller_f(f_memory_array_increase), F_status_set_fine(status));

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
      controller_print_entry_output_execute_simulate(&main->program.output, instance, program, arguments);

      // Sleep for less than a second to better show simulation of synchronous vs asynchronous.
      {
        f_time_spec_t delay = f_time_spec_t_initialize;

        status = f_time_spec_millisecond(0, controller_thread_simulation_timeout_d, &delay);

        if (F_status_is_error(status)) {
          controller_print_error_status(&main->program.error, macro_controller_f(f_time_spec_millisecond), F_status_set_fine(status));
        }
        else {
          status = controller_time_sleep_nanoseconds(instance->main, delay);
        }
      }

      if (F_status_set_fine(status) != F_interrupt) {
        fl_execute_parameter_t simulated_parameter = macro_fl_execute_parameter_t_initialize_1(execute_set->parameter.option, execute_set->parameter.wait, instance->rule.has & controller_rule_has_environment_d ? execute_set->parameter.environment : 0, execute_set->parameter.signals, &f_string_empty_s);

        status = fll_execute_program(controller_default_engine_s, instance->rule.engine_arguments, &simulated_parameter, &execute_set->as, (void *) &result);
      }
    }
    else {
      status = fll_execute_program(program, arguments, &execute_set->parameter, &execute_set->as, (void *) &result);
    }

    if (status == F_parent) {
      const pid_t id_child = result.pid;
      result.status = 0;

      f_thread_unlock(&instance->lock);

      status_lock = controller_lock_write_instance(instance, &instance->active);

      if (F_status_is_error(status_lock)) {
        controller_print_error_lock_critical(&main->program.error, F_status_set_fine(status_lock), F_false);

        if (F_status_set_fine(status_lock) != F_interrupt) {
          status = controller_lock_read_instance(instance, &instance->active);
          if (status == F_okay) return status_lock;
        }

        return F_status_set_error(F_lock);
      }

      // Assign the child instance id to allow for the cancel instance to send appropriate termination signals to the child instance.
      *child = id_child;

      f_thread_unlock(&instance->lock);

      status_lock = controller_lock_read_instance(instance, &instance->active);

      if (F_status_is_error(status_lock)) {
        controller_print_error_lock_critical(&main->program.error, F_status_set_fine(status_lock), F_true);
      }

      if (F_status_set_fine(status_lock) != F_interrupt) {

        // Have the parent wait for the child instance to finish.
        waitpid(id_child, &result.status, 0);
      }

      if (F_status_set_fine(status_lock) == F_interrupt || !controller_thread_is_enabled_instance(instance)) {
        return status_lock == F_okay ? F_status_set_error(F_interrupt) : F_status_set_error(F_lock);
      }

      if (status_lock == F_okay) {
        f_thread_unlock(&instance->lock);
      }

      status_lock = controller_lock_write_instance(instance, &instance->active);

      if (F_status_is_error(status_lock)) {
        controller_print_error_lock_critical(&main->program.error, F_status_set_fine(status_lock), F_false);

        if (F_status_set_fine(status_lock) != F_interrupt) {
          status = controller_lock_read_instance(instance, &instance->active);
          if (status == F_okay) return status_lock;
        }

        return F_status_set_error(F_lock);
      }

      instance->result = result.status;

      // Remove the pid now that waidpid() has returned.
      *child = 0;

      f_thread_unlock(&instance->lock);

      status_lock = controller_lock_read_instance(instance, &instance->active);

      if (F_status_is_error(status_lock)) {
        controller_print_error_lock_critical(&main->program.error, F_status_set_fine(status_lock), F_true);

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

      if (!controller_thread_is_enabled_instance(instance)) return F_status_set_error(F_interrupt);
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

    if (status == F_child || F_status_set_fine(status) == F_interrupt) return status;

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      if ((WIFEXITED(instance->result) && WEXITSTATUS(instance->result)) || status == F_control_group || status == F_failure || status == F_limit || status == F_processor || status == F_schedule) {
        controller_print_error_rule_item_execute(&instance->main->program.error, instance, type == controller_rule_item_type_script_e, program.used ? program : arguments.array[0], status);
      }
      else {
        controller_print_error_status(&instance->main->program.error, macro_controller_f(fll_execute_program), F_status_set_fine(status));
      }

      status = F_status_set_error(status);
    }

    return status;
  }
#endif // _di_controller_rule_execute_foreground_

#ifndef _di_controller_rule_execute_pid_with_
  f_status_t controller_rule_execute_pid_with(const f_string_dynamic_t pid_file, const uint8_t type, const f_string_static_t program, const f_string_statics_t arguments, const uint8_t options, const uint8_t with, controller_execute_set_t * const execute_set, controller_instance_t * const instance) {

    if (!execute_set || !instance || !instance->main) return F_status_set_error(F_parameter);

    f_status_t status = F_okay;
    f_status_t status_lock = F_okay;

    controller_t * const main = instance->main;

    f_execute_result_t result = f_execute_result_t_initialize;

    status = f_memory_array_increase(controller_allocation_small_d, sizeof(pid_t), (void **) &instance->childs.array, &instance->childs.used, &instance->childs.size);

    if (F_status_is_error(status)) {
      controller_print_error_status(&main->program.error, macro_controller_f(f_memory_array_increase), F_status_set_fine(status));

      return status;
    }

    status = f_memory_array_increase(controller_allocation_small_d, sizeof(f_string_dynamic_t), (void **) &instance->path_pids.array, &instance->path_pids.used, &instance->path_pids.size);

    if (F_status_is_error(status)) {
      controller_print_error_status(&main->program.error, macro_controller_f(f_memory_array_increase), F_status_set_fine(status));

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
      controller_print_error_file_status(&main->program.error, macro_controller_f(f_file_exists), pid_file, f_file_operation_find_s, fll_error_file_type_file_e, status == F_true ? F_file_found : F_status_set_fine(status));

      return status;
    }

    status = f_string_dynamic_append_nulless(pid_file, child_pid_file);

    if (F_status_is_error(status)) {
      controller_print_error_status(&main->program.error, macro_controller_f(f_string_dynamic_append_nulless), F_status_set_fine(status));

      return status;
    }

    if (options & controller_instance_option_simulate_e) {
      controller_print_entry_output_execute_simulate(&main->program.output, instance, program, arguments);

      // Sleep for less than a second to better show simulation of synchronous vs asynchronous.
      {
        f_time_spec_t delay = f_time_spec_t_initialize;

        status = f_time_spec_millisecond(0, controller_thread_simulation_timeout_d, &delay);

        if (F_status_is_error(status)) {
          controller_print_error_status(&main->program.error, macro_controller_f(f_time_spec_millisecond), F_status_set_fine(status));
        }
        else {
          status = controller_time_sleep_nanoseconds(instance->main, delay);
        }
      }

      if (F_status_set_fine(status) != F_interrupt) {
        const f_string_statics_t simulated_arguments = f_string_statics_t_initialize;
        fl_execute_parameter_t simulated_parameter = macro_fl_execute_parameter_t_initialize_1(execute_set->parameter.option, execute_set->parameter.wait, instance->rule.has & controller_rule_has_environment_d ? execute_set->parameter.environment : 0, execute_set->parameter.signals, &f_string_empty_s);

        status = fll_execute_program(controller_default_engine_s, simulated_arguments, &simulated_parameter, &execute_set->as, (void *) &result);
      }
    }
    else {
      status = fll_execute_program(program, arguments, &execute_set->parameter, &execute_set->as, (void *) &result);
    }

    if (status == F_parent) {
      const pid_t id_child = result.pid;
      result.status = 0;

      f_thread_unlock(&instance->lock);

      status_lock = controller_lock_write_instance(instance, &instance->active);

      if (F_status_is_error(status_lock)) {
        controller_print_error_lock_critical(&main->program.error, F_status_set_fine(status_lock), F_false);

        if (F_status_set_fine(status_lock) != F_interrupt) {
          status = controller_lock_read_instance(instance, &instance->active);
          if (status == F_okay) return status_lock;
        }

        return F_status_set_error(F_lock);
      }

      // Assign the child instance id to allow for the cancel instance to send appropriate termination signals to the child instance.
      *child = id_child;

      f_thread_unlock(&instance->lock);

      status_lock = controller_lock_read_instance(instance, &instance->active);

      if (F_status_is_error(status_lock)) {
        controller_print_error_lock_critical(&main->program.error, F_status_set_fine(status_lock), F_true);
      }

      if (F_status_set_fine(status_lock) != F_interrupt) {

        // The child instance should perform the change into background, therefore it is safe to wait for the child to exit (another instance is spawned).
        waitpid(id_child, &result.status, 0);
      }

      if (!controller_thread_is_enabled_instance(instance)) {
        return status_lock == F_okay ? F_status_set_error(F_interrupt) : F_status_set_error(F_lock);
      }

      if (status_lock == F_okay) {
        f_thread_unlock(&instance->lock);
      }

      status_lock = controller_lock_write_instance(instance, &instance->active);

      if (F_status_is_error(status_lock)) {
        controller_print_error_lock_critical(&main->program.error, F_status_set_fine(status_lock), F_false);

        if (F_status_set_fine(status_lock) != F_interrupt) {
          status = controller_lock_read_instance(instance, &instance->active);
          if (status == F_okay) return status_lock;
        }

        return F_status_set_error(F_lock);
      }

      instance->result = result.status;

      // Remove the pid now that waidpid() has returned.
      *child = 0;

      f_thread_unlock(&instance->lock);

      status_lock = controller_lock_read_instance(instance, &instance->active);

      if (F_status_is_error(status_lock)) {
        controller_print_error_lock_critical(&main->program.error, F_status_set_fine(status_lock), F_true);

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

      if (!controller_thread_is_enabled_instance(instance)) return F_status_set_error(F_interrupt);
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

    if (status == F_child || F_status_set_fine(status) == F_interrupt) return status;

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      if ((WIFEXITED(instance->result) && WEXITSTATUS(instance->result)) || status == F_control_group || status == F_failure || status == F_limit || status == F_processor || status == F_schedule) {
        controller_print_error_rule_item_execute(&instance->main->program.error, instance, type == controller_rule_item_type_utility_e, program.used ? program : arguments.array[0], status);
      }
      else {
        controller_print_error_status(&instance->main->program.error, macro_controller_f(fll_execute_program), F_status_set_fine(status));
      }

      return F_status_set_error(status);
    }

    return status;
  }
#endif // _di_controller_rule_execute_pid_with_

#ifndef _di_controller_rule_execute_rerun_
  int8_t controller_rule_execute_rerun(controller_instance_t * const instance, controller_rule_item_t * const item, const uint8_t action) {

    if (!instance || !instance->main || !item) return F_false;

    const int result = WIFEXITED(instance->result) ? WEXITSTATUS(instance->result) : 0;

    if (item->reruns[action].is & (result ? controller_rule_rerun_is_failure_d : controller_rule_rerun_is_success_d)) {
      controller_t * const main = instance->main;
      controller_rule_rerun_item_t * const rerun_item = result ? &item->reruns[action].failure : &item->reruns[action].success;

      if (!controller_thread_is_enabled_instance(instance)) return -2;

      if (!rerun_item->max || rerun_item->count < rerun_item->max) {
        controller_main_print_debug_rule_execute_rerun(&main->program.output, instance, rerun_item, action);

        if (rerun_item->delay) {
          f_time_spec_t delay = f_time_spec_t_initialize;

          {
            const f_status_t status = f_time_spec_millisecond(0, rerun_item->delay, &delay);

            if (F_status_is_error(status)) {
              controller_print_error_status(&main->program.error, macro_controller_f(f_time_spec_millisecond), F_status_set_fine(status));

              return -1;
            }
          }

          {
            const f_status_t status = controller_time_sleep_nanoseconds(instance->main, delay);
            if (F_status_is_error(status) || status == F_interrupt) return -1;
          }

          if (!controller_thread_is_enabled_instance(instance)) return -2;
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
