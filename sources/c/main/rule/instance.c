#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_rule_instance_
  f_status_t controller_rule_instance(controller_instance_t * const instance) {

    if (!instance || !instance->main) return F_status_set_error(F_parameter);

    controller_t * const main = instance->main;

    switch (instance->action) {
      case controller_rule_action_type_freeze_e:
      case controller_rule_action_type_kill_e:
      case controller_rule_action_type_pause_e:
      case controller_rule_action_type_reload_e:
      case controller_rule_action_type_restart_e:
      case controller_rule_action_type_resume_e:
      case controller_rule_action_type_start_e:
      case controller_rule_action_type_stop_e:
      case controller_rule_action_type_thaw_e:
        break;

      default:
        if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
          controller_lock_print(main->program.error.to, &main->thread);

          fl_print_format("%r%[%QUnsupported action type '%]", main->program.error.to, f_string_eol_s, main->program.error.context, main->program.error.prefix, main->program.error.context);
          fl_print_format(f_string_format_r_single_s.string, main->program.error.to, main->program.error.notable, controller_convert_rule_action_type_string(instance->action), main->program.error.notable);
          fl_print_format("%[' while attempting to execute rule.%]%r", main->program.error.to, main->program.error.context, main->program.error.context, f_string_eol_s);

          controller_print_rule_error_cache(&main->program.error, instance->cache.action, F_true);

          controller_unlock_print_flush(main->program.error.to, &main->thread);
        }

        return F_status_set_error(F_parameter);
    }

    f_status_t status = F_okay;
    f_status_t status_lock = F_okay;

    instance->cache.action.name_action.used = 0;
    instance->cache.action.name_item.used = 0;
    instance->cache.action.name_file.used = 0;

    status = f_string_dynamic_append(controller_rules_s, &instance->cache.action.name_file);

    if (F_status_is_error_not(status)) {
      status = f_string_dynamic_append(f_path_separator_s, &instance->cache.action.name_file);
    }

    if (F_status_is_error(status)) {
      controller_print_rule_error(&main->program.error, instance->cache.action, F_status_set_fine(status), "f_string_dynamic_append", F_true, F_true);

      return status;
    }

    status = f_string_dynamic_append(instance->rule.alias, &instance->cache.action.name_file);

    if (F_status_is_error(status)) {
      controller_print_rule_error(&main->program.error, instance->cache.action, F_status_set_fine(status), "f_string_dynamic_append", F_true, F_true);

      return status;
    }

    status = f_string_dynamic_append(f_path_extension_separator_s, &instance->cache.action.name_file);

    if (F_status_is_error_not(status)) {
      status = f_string_dynamic_append(controller_rule_s, &instance->cache.action.name_file);
    }

    if (F_status_is_error(status)) {
      controller_print_rule_error(&main->program.error, instance->cache.action, F_status_set_fine(status), "f_string_dynamic_append", F_true, F_true);

      return status;
    }

    if ((instance->options & controller_instance_option_simulate_validate_e) == controller_instance_option_simulate_validate_e) {
      controller_rule_validate(main, instance->rule, instance->action, instance->options, &instance->cache);
    }

    f_number_unsigned_t i = 0;

    {
      f_number_unsigned_t j = 0;
      f_number_unsigned_t id_rule = 0;
      f_number_unsigned_t id_dependency = 0;

      bool found = F_false;

      controller_instance_t *dependency = 0;

      uint8_t options_instance = 0;

      const f_string_static_t strings[3] = {
        controller_rule_needed_s,
        controller_rule_wanted_s,
        controller_rule_wished_s,
      };

      f_string_dynamics_t empty = f_string_dynamics_t_initialize;
      f_string_dynamics_t *dynamics[3] = { &empty, &empty, &empty };

      if (instance->action) {

        for (i = 0; i < instance->rule.ons.used; ++i) {

          if (instance->rule.ons.array[i].action == instance->action) {
            dynamics[0] = &instance->rule.ons.array[i].need;
            dynamics[1] = &instance->rule.ons.array[i].want;
            dynamics[2] = &instance->rule.ons.array[i].wish;

            break;
          }
        } // for
      }

      // i==0 is need, i==1 is want, i==2 is wish.
      // Loop through all dependencies: wait for depedency, execute dependency, fail due to missing required dependency, or skip unrequired missing dependencies.
      for (i = 0; i < 3 && controller_thread_is_enabled_instance(instance); ++i) {

        for (j = 0; j < dynamics[i]->used && controller_thread_is_enabled_instance(instance); ++j) {

          id_dependency = 0;
          dependency = 0;
          found = F_false;

          status_lock = controller_lock_read_instance(instance, &main->thread.lock.instance);

          if (F_status_is_error(status_lock)) {
            controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status_lock), F_true);
          }
          else {
            status = controller_instance_prepare_instance_type(main, instance->type, instance->action, dynamics[i]->array[j], &id_dependency);

            if (F_status_is_error(status)) {
              if (F_status_set_fine(status) == F_lock) {
                if (!controller_thread_is_enabled_instance_type(instance->type, &main->thread)) {
                  return F_status_set_error(F_interrupt);
                }
              }

              if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
                controller_lock_print(main->program.error.to, &main->thread);

                controller_print_rule_item_error_rule_not_loaded(&main->program.error, dynamics[i]->array[j]);
                controller_print_rule_error_cache(&main->program.error, instance->cache.action, F_false);

                controller_unlock_print_flush(main->program.error.to, &main->thread);
              }

              return status;
            }

            status = F_true;
          }

          if (status == F_true) {
            found = F_true;

            dependency = main->thread.instances.array[id_dependency];

            status_lock = controller_lock_read_instance(instance, &dependency->active);

            if (F_status_is_error(status_lock)) {
              controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status_lock), F_true);

              status = F_false;
              dependency = 0;

              f_thread_unlock(&main->thread.lock.instance);
            }
            else {
              f_thread_unlock(&main->thread.lock.instance);

              status_lock = controller_lock_read_instance(instance, &main->thread.lock.rule);

              if (F_status_is_error(status_lock)) {
                controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status_lock), F_true);

                status = F_false;
              }
              else {
                status = controller_rule_find(dynamics[i]->array[j], main->process.rules, &id_rule);

                f_thread_unlock(&main->thread.lock.rule);
              }
            }
          }
          else {
            f_thread_unlock(&main->thread.lock.instance);
          }

          if (status != F_true) {
            found = F_false;
            id_rule = 0;

            if (i == 0) {
              controller_lock_print(main->program.error.to, &main->thread);

              controller_print_rule_item_error_need_want_wish(&main->program.error, strings[i], dynamics[i]->array[j], "is not found");
              controller_print_rule_error_cache(&main->program.error, instance->cache.action, F_true);

              controller_unlock_print_flush(main->program.error.to, &main->thread);

              status = F_status_set_error(F_found_not);

              if (!(instance->options & controller_instance_option_simulate_e)) {
                if (dependency) {
                  f_thread_unlock(&dependency->active);
                }

                break;
              }
            }
            else {
              if (main->program.warning.verbosity == f_console_verbosity_debug_e) {
                controller_lock_print(main->program.warning.to, &main->thread);

                controller_print_rule_item_error_need_want_wish(&main->program.warning, strings[i], dynamics[i]->array[j], "is not found");

                controller_print_rule_error_cache(&main->program.warning, instance->cache.action, F_true);

                controller_unlock_print_flush(main->program.warning.to, &main->thread);
              }
            }
          }
          else if (found) {
            status_lock = controller_lock_read_instance(instance, &main->thread.lock.rule);

            if (F_status_is_error(status_lock)) {
              controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status_lock), F_true);

              found = F_false;
              status = status_lock;
            }
          }

          if (found) {

            // The dependency may have write locks, which needs to be avoided, so copy the alias from the rule.
            f_string_static_t alias_other_buffer = f_string_static_t_initialize;
            alias_other_buffer.used = main->process.rules.array[id_rule].alias.used;

            f_char_t alias_other_buffer_string[alias_other_buffer.used + 1];
            alias_other_buffer.string = alias_other_buffer_string;

            memcpy(alias_other_buffer_string, main->process.rules.array[id_rule].alias.string, sizeof(f_char_t) * alias_other_buffer.used);
            alias_other_buffer_string[alias_other_buffer.used] = 0;

            f_thread_unlock(&main->thread.lock.rule);

            status_lock = controller_lock_read_instance(instance, &dependency->lock);

            if (F_status_is_error(status_lock)) {
              controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status_lock), F_true);

              status = status_lock;
            }
            else if (dependency->state == controller_instance_state_active_e || dependency->state == controller_instance_state_busy_e) {
              f_thread_unlock(&dependency->lock);

              status = controller_instance_wait(dependency);

              if (F_status_is_error(status) && !(instance->options & controller_instance_option_simulate_e)) break;

              status = dependency->rule.status[instance->action];
            }
            else {
              status_lock = controller_lock_read_instance(instance, &main->thread.lock.rule);

              if (F_status_is_error(status_lock)) {
                controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status_lock), F_true);

                f_thread_unlock(&dependency->lock);

                status = status_lock;
              }
              else if (controller_rule_status_is_available(instance->action, main->process.rules.array[id_rule])) {
                f_thread_unlock(&main->thread.lock.rule);
                f_thread_unlock(&dependency->lock);

                options_instance = 0;

                if (main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e) {
                  options_instance |= controller_instance_option_simulate_e;
                }

                if (instance->options & controller_instance_option_validate_e) {
                  options_instance |= controller_instance_option_validate_e;
                }

                // Synchronously execute dependency.
                status = controller_rule_instance_begin(main, 0, alias_other_buffer, instance->action, options_instance, instance->type, instance->stack, dependency->cache);

                if (status == F_child || F_status_set_fine(status) == F_interrupt) {
                  f_thread_unlock(&dependency->active);

                  break;
                }

                if (F_status_is_error(status)) {
                  if (i == 0 || i == 1 || F_status_set_fine(status) == F_memory_not) {
                    controller_lock_print(main->program.error.to, &main->thread);

                    controller_print_rule_item_error_need_want_wish(&main->program.error, strings[i], alias_other_buffer, "failed during execution");
                    controller_print_rule_error_cache(&main->program.error, instance->cache.action, F_true);

                    controller_unlock_print_flush(main->program.error.to, &main->thread);

                    if (!(dependency->options & controller_instance_option_simulate_e) || F_status_set_fine(status) == F_memory_not) {
                      f_thread_unlock(&dependency->active);

                      break;
                    }
                  }
                  else {
                    if (main->program.warning.verbosity == f_console_verbosity_debug_e) {
                      controller_lock_print(main->program.warning.to, &main->thread);

                      controller_print_rule_item_error_need_want_wish(&main->program.warning, strings[i], alias_other_buffer, "failed during execution");

                      controller_print_rule_error_cache(&main->program.warning, instance->cache.action, F_true);

                      controller_unlock_print_flush(main->program.warning.to, &main->thread);
                    }
                  }
                }
              }
              else {
                status = main->process.rules.array[id_rule].status[instance->action];

                f_thread_unlock(&main->thread.lock.rule);
                f_thread_unlock(&dependency->lock);
              }
            }

            if (!controller_thread_is_enabled_instance(instance)) {
              f_thread_unlock(&dependency->active);

              break;
            }

            if (F_status_is_error_not(status_lock)) {
              status_lock = controller_lock_read_instance(instance, &main->thread.lock.rule);

              if (F_status_is_error(status_lock)) {
                controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status_lock), F_false);
              }
            }

            if (F_status_is_error(status_lock)) {
              if (F_status_is_error(status_lock)) {
                controller_print_rule_item_error_need_want_wish(&main->program.error, strings[i], alias_other_buffer, "due to lock failure");
              }

              status = status_lock;
            }
            else if (controller_rule_status_is_error(instance->action, main->process.rules.array[id_rule])) {
              f_thread_unlock(&main->thread.lock.rule);

              if (i == 0 || i == 1) {
                controller_lock_print(main->program.error.to, &main->thread);

                controller_print_rule_item_error_need_want_wish(&main->program.error, strings[i], alias_other_buffer, "is in a failed state");

                controller_print_rule_error_cache(&main->program.error, instance->cache.action, F_true);

                controller_unlock_print_flush(main->program.error.to, &main->thread);

                status = F_status_set_error(F_found_not);

                if (!(dependency->options & controller_instance_option_simulate_e)) {
                  f_thread_unlock(&dependency->active);

                  break;
                }
              }
              else {
                if (main->program.warning.verbosity == f_console_verbosity_debug_e) {
                  controller_lock_print(main->program.warning.to, &main->thread);

                  controller_print_rule_item_error_need_want_wish(&main->program.warning, strings[i], alias_other_buffer, "is in a failed state");

                  controller_print_rule_error_cache(&main->program.warning, instance->cache.action, F_true);

                  controller_unlock_print_flush(main->program.warning.to, &main->thread);
                }
              }
            }
            else {
              f_thread_unlock(&main->thread.lock.rule);
            }
          }

          if (dependency) {
            f_thread_unlock(&dependency->active);
          }
        } // for

        if (status == F_child || F_status_set_fine(status) == F_interrupt) break;

        if (F_status_is_error(status) && !(instance->options & controller_instance_option_simulate_e)) break;
      } // for
    }

    if (status == F_child || F_status_set_fine(status) == F_interrupt) {
      return status;
    }

    if (!controller_thread_is_enabled_instance(instance)) {
      return F_status_set_error(F_interrupt);
    }

    if ((instance->options & controller_instance_option_wait_e) && F_status_is_error_not(status) && (instance->options & controller_instance_option_validate_e)) {
      status_lock = controller_rule_wait_all_instance_type(main, instance->type, F_false);

      if (F_status_set_fine(status_lock) == F_interrupt) {
        return status_lock;
      }
    }

    if (!(instance->options & controller_instance_option_validate_e) && F_status_is_error_not(status)) {

      // Find at least one of the requested action when the rule is required.
      if (instance->options & controller_instance_option_require_e) {
        bool missing = F_true;

        f_number_unsigned_t j = 0;

        for (i = 0; i < instance->rule.items.used; ++i) {

          for (j = 0; j < instance->rule.items.array[i].actions.used; ++j) {

            if (instance->rule.items.array[i].actions.array[j].type == instance->action) {
              missing = F_false;

              break;
            }
          } // for
        } // for

        if (missing) {
          if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
            controller_lock_print(main->program.error.to, &main->thread);

            if (instance->rule.items.used) {
              fl_print_format("%r%[%QThe rule '%]", main->program.error.to, f_string_eol_s, main->program.error.context, main->program.error.prefix, main->program.error.context);
              fl_print_format(f_string_format_Q_single_s.string, main->program.error.to, main->program.error.notable, instance->rule.name, main->program.error.notable);
              fl_print_format("%[' has no '%]", main->program.error.to, main->program.error.context, main->program.error.context);
              fl_print_format(f_string_format_r_single_s.string, main->program.error.to, main->program.error.notable, controller_convert_rule_action_type_string(instance->action), main->program.error.notable);
              fl_print_format("%[' action to execute.%]%r", main->program.error.to, main->program.error.context, main->program.error.context, f_string_eol_s);
            }
            else {
              fl_print_format("%r%[%QThe rule '%]", main->program.error.to, f_string_eol_s, main->program.error.context, main->program.error.prefix, main->program.error.context);
              fl_print_format(f_string_format_Q_single_s.string, main->program.error.to, main->program.error.notable, instance->rule.name, main->program.error.notable);
              fl_print_format("%[ has no known '%]", main->program.error.to, main->program.error.context, main->program.error.context);
              fl_print_format("%[%r %r%]", main->program.error.to, main->program.error.notable, controller_rule_s, controller_type_s, main->program.error.notable);
              fl_print_format("%[' (such as '%]", main->program.error.to, main->program.error.context, main->program.error.context);
              fl_print_format(f_string_format_r_single_s.string, main->program.error.to, main->program.error.notable, controller_command_s, main->program.error.notable);
              fl_print_format("%[', '%]", main->program.error.to, main->program.error.context, main->program.error.context);
              fl_print_format(f_string_format_r_single_s.string, main->program.error.to, main->program.error.notable, controller_service_s, main->program.error.notable);
              fl_print_format("%[', '%]", main->program.error.to, main->program.error.context, main->program.error.context);
              fl_print_format(f_string_format_r_single_s.string, main->program.error.to, main->program.error.notable, controller_script_s, main->program.error.notable);
              fl_print_format("%[', or '%]", main->program.error.to, main->program.error.context, main->program.error.context);
              fl_print_format(f_string_format_r_single_s.string, main->program.error.to, main->program.error.notable, controller_utility_s, main->program.error.notable);
              fl_print_format("%[') to execute.%]%r", main->program.error.to, main->program.error.context, main->program.error.context, f_string_eol_s);
            }

            controller_print_rule_error_cache(&main->program.error, instance->cache.action, F_true);

            controller_unlock_print_flush(main->program.error.to, &main->thread);
          }

          status = F_status_set_error(F_parameter);
        }
      }

      if (F_status_is_error_not(status)) {
        status = controller_rule_execute(main, instance->action, instance->options, instance);

        if (status == F_child || F_status_set_fine(status) == F_interrupt || F_status_set_fine(status) == F_lock) {
          return status;
        }

        if (F_status_is_error(status)) {
          controller_print_rule_item_error(&main->program.error, instance->cache.action, F_true, F_status_set_fine(status));
        }
      }
    }

    f_number_unsigned_t id_rule = 0;

    f_thread_unlock(&instance->lock);

    status_lock = controller_lock_write_instance(instance, &instance->lock);

    if (F_status_is_error(status_lock)) {
      controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status_lock), F_false);

      if (F_status_set_fine(status) != F_interrupt) {
        status = controller_lock_read_instance(instance, &instance->lock);
        if (F_status_is_error_not(status)) return status_lock;
      }

      return F_status_set_error(F_lock);
    }

    if (F_status_is_error(status)) {
      instance->rule.status[instance->action] = controller_error_simplify(F_status_set_fine(status));
    }
    else {
      instance->rule.status[instance->action] = status;
    }

    status_lock = controller_lock_write_instance(instance, &main->thread.lock.rule);

    if (F_status_is_error(status_lock)) {
      controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status_lock), F_false);

      f_thread_unlock(&instance->lock);

      status = controller_lock_read_instance(instance, &instance->lock);
      if (F_status_is_error_not(status)) return status_lock;

      return F_status_set_error(F_lock);
    }

    // Update the rule status, which is stored separately from the rule status for this instance.
    if (controller_rule_find(instance->rule.alias, main->process.rules, &id_rule) == F_true) {
      controller_rule_t *rule = &main->process.rules.array[id_rule];

      rule->status[instance->action] = instance->rule.status[instance->action];

      f_number_unsigned_t j = 0;

      controller_rule_item_t *rule_item = 0;

      // Copy all rule item action statuses from the rule instance to the rule.
      for (i = 0; i < rule->items.used; ++i) {

        rule_item = &rule->items.array[i];

        for (j = 0; j < rule_item->actions.used; ++j) {
          rule_item->actions.array[j].status = instance->rule.items.array[i].actions.array[j].status;
        } // for
      } // for
    }

    f_thread_unlock(&main->thread.lock.rule);
    f_thread_unlock(&instance->lock);

    status_lock = controller_lock_read_instance(instance, &instance->lock);

    if (F_status_is_error(status_lock)) {
      controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status_lock), F_true);

      return F_status_set_error(F_lock);
    }

    return instance->rule.status[instance->action];
  }
#endif // _di_controller_rule_instance_

#ifndef _di_controller_rule_instance_begin_
  f_status_t controller_rule_instance_begin(controller_t * const main, const uint8_t options_force, const f_string_static_t alias_rule, const uint8_t action, const uint8_t options, const uint8_t type, const f_number_unsigneds_t stack, const controller_cache_t cache) {

    if (!main) return F_status_set_error(F_parameter);

    if (!controller_thread_is_enabled_instance_type(type, &main->thread)) {
      return F_status_set_error(F_interrupt);
    }

    f_status_t status = F_okay;
    f_status_t status_lock = F_okay;

    controller_instance_t *instance = 0;

    status = controller_lock_read_instance_type(type, &main->thread, &main->thread.lock.instance);

    if (F_status_is_error(status)) {
      controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status), F_true);

      return status;
    }

    {
      f_number_unsigned_t at = 0;

      status = controller_instance_prepare(main, type != controller_instance_type_exit_e, action, alias_rule, &at);

      if (F_status_is_error(status)) {
        f_thread_unlock(&main->thread.lock.instance);

        if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
          controller_lock_print(main->program.error.to, &main->thread);

          controller_print_rule_item_error_rule_not_loaded(&main->program.error, alias_rule);
          controller_print_rule_error_cache(&main->program.error, cache.action, F_false);

          controller_unlock_print_flush(main->program.error.to, &main->thread);
        }

        return status;
      }

      instance = main->thread.instances.array[at];

      status = controller_lock_read_instance_type(type, &main->thread, &instance->active);

      if (F_status_is_error(status)) {
        controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status), F_true);
        controller_print_rule_item_error(&main->program.error, cache.action, F_false, F_status_set_fine(status));

        f_thread_unlock(&main->thread.lock.instance);

        return status;
      }

      status_lock = controller_lock_write_instance(instance, &instance->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status_lock), F_false);

        f_thread_unlock(&instance->active);
        f_thread_unlock(&main->thread.lock.instance);

        return status_lock;
      }

      // Once a write lock on the instance is achieved, it is safe to unlock the instance read lock.
      f_thread_unlock(&main->thread.lock.instance);

      // If the instance is already running, then there is nothing to do.
      if (instance->state == controller_instance_state_active_e || instance->state == controller_instance_state_busy_e) {
        f_thread_unlock(&instance->lock);
        f_thread_unlock(&instance->active);

        return F_busy;
      }

      // The thread is done, so close the thread.
      if (instance->state == controller_instance_state_done_e) {
        controller_thread_join(&instance->id_thread);

        f_thread_mutex_lock(&instance->wait_lock);
        f_thread_condition_signal_all(&instance->wait);
        f_thread_mutex_unlock(&instance->wait_lock);
      }

      instance->id = at;
    }

    f_thread_unlock(&instance->lock);

    status_lock = controller_lock_write_instance(instance, &instance->lock);

    if (F_status_is_error(status_lock)) {
      controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status_lock), F_false);

      f_thread_unlock(&instance->active);

      return status_lock;
    }

    instance->state = controller_instance_state_active_e;
    instance->action = action;
    instance->options = options;
    instance->type = type;

    instance->cache.ats.used = 0;
    instance->cache.stack.used = 0;
    instance->cache.comments.used = 0;
    instance->cache.delimits.used = 0;
    instance->cache.content_action.used = 0;
    instance->cache.content_actions.used = 0;
    instance->cache.content_items.used = 0;
    instance->cache.object_actions.used = 0;
    instance->cache.object_items.used = 0;
    instance->cache.buffer_file.used = 0;
    instance->cache.buffer_item.used = 0;
    instance->cache.buffer_path.used = 0;
    instance->cache.expanded.used = 0;
    instance->cache.action.line_action = cache.action.line_action;
    instance->cache.action.line_item = cache.action.line_item;
    instance->cache.action.name_action.used = 0;
    instance->cache.action.name_file.used = 0;
    instance->cache.action.name_item.used = 0;
    instance->cache.action.generic.used = 0;
    instance->cache.range_action.start = 1;
    instance->cache.range_action.stop = 0;
    instance->cache.timestamp.seconds = 0;
    instance->cache.timestamp.seconds_nano = 0;

    instance->stack.used = 0;

    instance->main = (void *) main;

    if (F_status_is_error_not(status) && stack.used) {
      if (instance->stack.size < stack.used) {
        status = f_memory_array_resize(stack.used, sizeof(f_number_unsigned_t), (void **) &instance->stack.array, &instance->stack.used, &instance->stack.size);
      }

      if (F_status_is_error(status)) {
        controller_print_error_status(&main->program.error, macro_controller_f(f_memory_array_resize), F_status_set_fine(status));
      }
      else {
        for (f_number_unsigned_t i = 0; i < stack.used; ++i) {
          instance->stack.array[i] = stack.array[i];
        } // for

        instance->stack.used = stack.used;
      }
    }

    if (F_status_is_error_not(status)) {
      status = f_string_dynamic_append(cache.action.name_action, &instance->cache.action.name_action);

      if (F_status_is_error_not(status)) {
        status = f_string_dynamic_append(cache.action.name_file, &instance->cache.action.name_file);
      }

      if (F_status_is_error_not(status)) {
        status = f_string_dynamic_append(cache.action.name_item, &instance->cache.action.name_item);
      }
      else {
        controller_print_error_status(&main->program.error, macro_controller_f(f_string_dynamic_append), F_status_set_fine(status));
      }
    }

    f_thread_unlock(&instance->lock);

    if (F_status_is_error_not(status)) {
      if (instance->action && (options_force & controller_instance_option_asynchronous_e)) {
        if (instance->type == controller_instance_type_exit_e) {
          status = f_thread_create(0, &instance->id_thread, controller_thread_instance_other, (void *) instance);
        }
        else {
          status = f_thread_create(0, &instance->id_thread, controller_thread_instance_normal, (void *) instance);
        }

        if (F_status_is_error(status)) {
          controller_print_error_status(&main->program.error, macro_controller_f(f_thread_create), F_status_set_fine(status));
        }
      }
      else {
        status = controller_rule_instance_do(options_force, instance);

        if (status == F_child || F_status_set_fine(status) == F_interrupt) {
          f_thread_unlock(&instance->active);

          return status;
        }
      }
    }

    if (!action || F_status_is_error(status) && (instance->state == controller_instance_state_active_e || instance->state == controller_instance_state_busy_e)) {
      {
        status_lock = controller_lock_write_instance(instance, &instance->lock);

        if (F_status_is_error(status_lock)) {
          controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status_lock), F_false);

          f_thread_unlock(&instance->active);

          return status_lock;
        }
      }

      if (!action || (options_force & controller_instance_option_asynchronous_e)) {
        instance->state = controller_instance_state_done_e;
      }
      else {
        instance->state = controller_instance_state_idle_e;
      }

      f_thread_mutex_lock(&instance->wait_lock);
      f_thread_condition_signal_all(&instance->wait);
      f_thread_mutex_unlock(&instance->wait_lock);

      f_thread_unlock(&instance->lock);
    }

    f_thread_unlock(&instance->active);

    if (F_status_is_error(status)) {
      return status;
    }

    return F_okay;
  }
#endif // _di_controller_rule_instance_begin_

#ifndef _di_controller_rule_instance_do_
  f_status_t controller_rule_instance_do(const uint8_t options_force, controller_instance_t * const instance) {

    if (!instance || !instance->main) return F_status_set_error(F_parameter);

    f_status_t status_lock = F_okay;

    // The instance and active locks shall be held for the duration of this instanceing (aside from switching between read to/from write).
    if (options_force & controller_instance_option_asynchronous_e) {
      status_lock = controller_lock_read_instance(instance, &instance->active);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(&instance->main->program.error, F_status_set_fine(status_lock), F_true);

        return status_lock;
      }
    }

    status_lock = controller_lock_read_instance(instance, &instance->lock);

    if (F_status_is_error(status_lock)) {
      controller_lock_print_error_critical(&instance->main->program.error, F_status_set_fine(status_lock), F_true);

      if (options_force & controller_instance_option_asynchronous_e) {
        f_thread_unlock(&instance->active);
      }

      return status_lock;
    }

    f_status_t status = F_okay;

    f_number_unsigned_t id_rule = 0;

    const f_number_unsigned_t used_original_stack = instance->stack.used;

    status_lock = controller_lock_read_instance(instance, &instance->main->thread.lock.rule);

    if (F_status_is_error(status_lock)) {
      controller_lock_print_error_critical(&instance->main->program.error, F_status_set_fine(status_lock), F_true);

      f_thread_unlock(&instance->lock);

      if (options_force & controller_instance_option_asynchronous_e) {
        f_thread_unlock(&instance->active);
      }

      return status_lock;
    }

    if (controller_rule_find(instance->rule.alias, instance->main->process.rules, &id_rule) == F_true) {
      f_thread_unlock(&instance->lock);

      status_lock = controller_lock_write_instance(instance, &instance->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(&instance->main->program.error, F_status_set_fine(status_lock), F_false);

        f_thread_unlock(&instance->main->thread.lock.rule);

        if (options_force & controller_instance_option_asynchronous_e) {
          f_thread_unlock(&instance->active);
        }

        return status_lock;
      }

      controller_rule_delete(&instance->rule);

      status = controller_rule_copy(instance->main->process.rules.array[id_rule], &instance->rule);

      f_thread_unlock(&instance->lock);

      status_lock = controller_lock_read_instance(instance, &instance->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(&instance->main->program.error, F_status_set_fine(status_lock), F_true);

        f_thread_unlock(&instance->main->thread.lock.rule);

        if (options_force & controller_instance_option_asynchronous_e) {
          f_thread_unlock(&instance->active);
        }

        return status_lock;
      }

      f_thread_unlock(&instance->main->thread.lock.rule);

      if (F_status_is_error(status)) {
        controller_print_error_status(&instance->main->program.error, macro_controller_f(controller_rule_copy), F_status_set_fine(status));
      }
      else if (!instance->action) {

        // This is a "consider" Action, so do not actually execute the rule.
        f_thread_unlock(&instance->lock);

        if (options_force & controller_instance_option_asynchronous_e) {
          f_thread_unlock(&instance->active);
        }

        return F_process_not;
      }
      else {
        for (f_number_unsigned_t i = 0; i < instance->stack.used && controller_thread_is_enabled_instance(instance); ++i) {

          if (instance->stack.array[i] == id_rule) {
            if (instance->main->program.error.verbosity > f_console_verbosity_quiet_e) {
              controller_lock_print(instance->main->program.error.to, &instance->main->thread);

              fl_print_format("%r%[%QThe rule '%]", instance->main->program.error.to, f_string_eol_s, instance->main->program.error.context, instance->main->program.error.prefix, instance->main->program.error.context);
              fl_print_format(f_string_format_Q_single_s.string, instance->main->program.error.to, instance->main->program.error.notable, instance->rule.alias, instance->main->program.error.notable);
              fl_print_format("%[' is already on the execution dependency stack, this recursion is prohibited.%]%r", instance->main->program.error.to, instance->main->program.error.context, instance->main->program.error.context, f_string_eol_s);

              controller_print_rule_error_cache(&instance->main->program.error, instance->cache.action, F_true);

              controller_unlock_print_flush(instance->main->program.error.to, &instance->main->thread);
            }

            // Never continue on circular recursion errors even in simulate mode.
            status = F_status_set_error(F_recurse);

            break;
          }
        } // for

        if (!controller_thread_is_enabled_instance(instance)) {
          f_thread_unlock(&instance->lock);

          if (options_force & controller_instance_option_asynchronous_e) {
            f_thread_unlock(&instance->active);
          }

          return F_status_set_error(F_interrupt);
        }

        if (F_status_is_error_not(status)) {
          status = f_memory_array_increase(controller_allocation_small_d, sizeof(f_number_unsigned_t), (void **) &instance->stack.array, &instance->stack.used, &instance->stack.size);

          if (F_status_is_error(status)) {
            controller_print_error_status(&instance->main->program.error, macro_controller_f(f_memory_array_increase), F_status_set_fine(status));
          }
          else {
            f_thread_unlock(&instance->lock);

            status_lock = controller_lock_write_instance(instance, &instance->lock);

            if (F_status_is_error(status_lock)) {
              controller_lock_print_error_critical(&instance->main->program.error, F_status_set_fine(status_lock), F_false);

              if (options_force & controller_instance_option_asynchronous_e) {
                f_thread_unlock(&instance->active);
              }

              return status_lock;
            }

            instance->stack.array[instance->stack.used++] = id_rule;

            f_thread_unlock(&instance->lock);

            status_lock = controller_lock_read_instance(instance, &instance->lock);

            if (F_status_is_error(status_lock)) {
              controller_lock_print_error_critical(&instance->main->program.error, F_status_set_fine(status_lock), F_true);

              if (options_force & controller_instance_option_asynchronous_e) {
                f_thread_unlock(&instance->active);
              }

              return status_lock;
            }
          }
        }
      }

      if (F_status_is_error_not(status)) {
        status = controller_rule_instance(instance);
      }
    }
    else {
      f_thread_unlock(&instance->main->thread.lock.rule);

      status = F_status_set_error(F_found_not);

      if (instance->main->program.error.verbosity > f_console_verbosity_quiet_e) {
        controller_lock_print(instance->main->program.error.to, &instance->main->thread);

        controller_print_rule_item_error_rule_not_loaded(&instance->main->program.error, instance->rule.alias);
        controller_print_rule_error_cache(&instance->main->program.error, instance->cache.action, F_false);

        controller_unlock_print_flush(instance->main->program.error.to, &instance->main->thread);
      }
    }

    if (status == F_child) {
      f_thread_unlock(&instance->lock);

      if (options_force & controller_instance_option_asynchronous_e) {
        f_thread_unlock(&instance->active);
      }

      return status;
    }

    status_lock = controller_lock_write_instance(instance, &instance->main->thread.lock.rule);

    if (F_status_is_error(status_lock)) {
      controller_lock_print_error_critical(&instance->main->program.error, F_status_set_fine(status_lock), F_false);

      if (F_status_set_fine(status) != F_lock) {
        f_thread_unlock(&instance->lock);
      }

      if (options_force & controller_instance_option_asynchronous_e) {
        f_thread_unlock(&instance->active);
      }

      return status_lock;
    }

    if (F_status_set_fine(status) == F_lock) {
      if (controller_rule_find(instance->rule.alias, instance->main->process.rules, &id_rule) == F_true) {
        instance->main->process.rules.array[id_rule].status[instance->action] = status;
      }
    }

    f_thread_unlock(&instance->main->thread.lock.rule);

    if (F_status_set_fine(status) != F_lock) {
      f_thread_unlock(&instance->lock);
    }

    if (F_status_set_fine(status) == F_interrupt || F_status_set_fine(status) == F_lock && !controller_thread_is_enabled_instance(instance)) {
      if (options_force & controller_instance_option_asynchronous_e) {
        f_thread_unlock(&instance->active);
      }

      return F_status_set_error(F_interrupt);
    }

    status_lock = controller_lock_write_instance(instance, &instance->lock);

    if (F_status_is_error(status_lock)) {
      controller_lock_print_error_critical(&instance->main->program.error, F_status_set_fine(status_lock), F_false);

      if (options_force & controller_instance_option_asynchronous_e) {
        f_thread_unlock(&instance->active);
      }

      return status_lock;
    }

    instance->state = (options_force & controller_instance_option_asynchronous_e) ? controller_instance_state_done_e : controller_instance_state_idle_e;
    instance->stack.used = used_original_stack;

    // inform all things waiting that the instance has finished running.
    f_thread_mutex_lock(&instance->wait_lock);
    f_thread_condition_signal_all(&instance->wait);
    f_thread_mutex_unlock(&instance->wait_lock);

    f_thread_unlock(&instance->lock);

    if (options_force & controller_instance_option_asynchronous_e) {
      f_thread_unlock(&instance->active);
    }

    return controller_thread_is_enabled_instance(instance) ? status : F_status_set_error(F_interrupt);
  }
#endif // _di_controller_rule_instance_do_

#ifdef __cplusplus
} // extern "C"
#endif
