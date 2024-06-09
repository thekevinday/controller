#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_rule_validate_
  void controller_rule_validate(controller_t * const main, controller_cache_t * const cache, const controller_rule_t rule, const uint8_t action, const uint8_t options) {

    if (!main || !cache) return;

    switch (action) {
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
          fl_print_format(f_string_format_Q_single_s.string, main->program.error.to, main->program.error.notable, controller_convert_rule_action_type_string(action), main->program.error.notable);
          fl_print_format("%[' while attempting to validate rule execution.%]%r", main->program.error.to, main->program.error.context, main->program.error.context, f_string_eol_s);

          controller_print_error_rule_cache(&main->program.error, cache->action, F_true);

          controller_unlock_print_flush(main->program.error.to, &main->thread);
        }

        return;
    }

    f_number_unsigned_t i = 0;
    f_number_unsigned_t j = 0;

    // Find at least one of the requested action.
    {
      bool missing = F_true;

      for (; i < rule.items.used; ++i) {

        for (j = 0; j < rule.items.array[i].actions.used; ++j) {

          if (!action || rule.items.array[i].actions.array[j].type == action) {
            missing = F_false;

            break;
          }
        } // for
      } // for

      if (missing) {
        controller_lock_print(main->program.output.to, &main->thread);

        if (rule.items.used) {
          fl_print_format("%rRule '", main->program.output.to, f_string_eol_s);
          fl_print_format("%[%Q%]' has no '", main->program.output.to, main->program.context.set.title, rule.name, main->program.context.set.title);
          fl_print_format("%[%r%]' action to execute and would '", main->program.output.to, main->program.context.set.title, controller_convert_rule_action_type_string(action), main->program.context.set.title);
          fl_print_format("%[%r%]' because it is '", main->program.output.to, main->program.context.set.important, options & controller_instance_option_require_e ? controller_fail_s : controller_succeed_s, main->program.context.set.important);
          fl_print_format("%[%r%]'.%r", main->program.output.to, main->program.context.set.important, options & controller_instance_option_require_e ? controller_required_s : controller_optional_s, main->program.context.set.important, f_string_eol_s);
        }
        else {
          fl_print_format("%rRule '", main->program.output.to, f_string_eol_s);
          fl_print_format("%[%Q%]' has no known '", main->program.output.to, main->program.context.set.title, rule.name, main->program.context.set.title);
          fl_print_format("%[%r %r%]' (such as ", main->program.output.to, main->program.context.set.title, controller_rule_s, controller_type_s, main->program.context.set.title);
          fl_print_format("'%[%r%]', ", main->program.output.to, main->program.context.set.title, controller_command_s, main->program.context.set.title);
          fl_print_format("'%[%r%]', ", main->program.output.to, main->program.context.set.title, controller_service_s, main->program.context.set.title);
          fl_print_format("'%[%r%]', or ", main->program.output.to, main->program.context.set.title, controller_script_s, main->program.context.set.title);
          fl_print_format("'%[%r%]'", main->program.output.to, main->program.context.set.title, controller_utility_s, main->program.context.set.title);
          fl_print_format(") and would '%[%r%]' because it is '", main->program.output.to, main->program.context.set.important, options & controller_instance_option_require_e ? controller_fail_s : controller_succeed_s, main->program.context.set.important);
          fl_print_format("%[%r%]'.%r", main->program.output.to, main->program.context.set.important, options & controller_instance_option_require_e ? controller_required_s : controller_optional_s, main->program.context.set.important, f_string_eol_s);
        }

        controller_unlock_print_flush(main->program.output.to, &main->thread);
      }
    }

    controller_lock_print(main->program.output.to, &main->thread);

    fl_print_format("%rRule %[%Q%] {%r", main->program.output.to, f_string_eol_s, main->program.context.set.title, rule.alias, main->program.context.set.title, f_string_eol_s);

    // Name.
    fl_print_format("  %[%r%] %Q%r", main->program.output.to, main->program.context.set.important, controller_name_s, main->program.context.set.important, rule.name, f_string_eol_s);

    // Capability.
    fl_print_format("  %[%r%] ", main->program.output.to, main->program.context.set.important, controller_capability_s, main->program.context.set.important);

    if (f_capability_supported()) {
      if (rule.capability) {
        cache->action.generic.used = 0;

        if (F_status_is_error_not(f_capability_to_text(rule.capability, &cache->action.generic))) {
          f_print_dynamic_safely(cache->action.generic, main->program.output.to);
        }
      }

      f_print_dynamic_raw(f_string_eol_s, main->program.output.to);
    }
    else {
      fl_print_format("%[(unsupported)%]%r", main->program.output.to, main->program.context.set.warning, main->program.context.set.warning, f_string_eol_s);
    }

    // Control Group.
    fl_print_format("  %[%r%]", main->program.output.to, main->program.context.set.important, controller_cgroup_s, main->program.context.set.important);

    if (rule.has & controller_rule_has_cgroup_d) {
      fl_print_format(" %r", main->program.output.to, rule.cgroup.as_new ? controller_new_s : controller_existing_s);

      for (i = 0; i < rule.cgroup.groups.used; ++i) {

        if (rule.cgroup.groups.array[i].used) {
          fl_print_format(" %Q", main->program.output.to, rule.cgroup.groups.array[i]);
        }
      } // for
    }

    f_print_dynamic_raw(f_string_eol_s, main->program.output.to);

    // How.
    fl_print_format("  %[%r%] %r%r", main->program.output.to, main->program.context.set.important, controller_how_s, main->program.context.set.important, options & controller_instance_option_asynchronous_e ? controller_asynchronous_s : controller_synchronous_s, f_string_eol_s);

    // Nice.
    fl_print_format("  %[%r%]", main->program.output.to, main->program.context.set.important, controller_nice_s, main->program.context.set.important);

    if (rule.has & controller_rule_has_nice_d) {
      fl_print_format(" %i", main->program.output.to, rule.nice);
    }

    f_print_dynamic_raw(f_string_eol_s, main->program.output.to);

    // Scheduler.
    fl_print_format("  %[%r%]", main->program.output.to, main->program.context.set.important, controller_scheduler_s, main->program.context.set.important);

    if (rule.has & controller_rule_has_scheduler_d) {
      f_string_static_t policy = f_string_static_t_initialize;

      if (rule.scheduler.policy == SCHED_BATCH) {
        policy = controller_batch_s;
      }
      else if (rule.scheduler.policy == SCHED_DEADLINE) {
        policy = controller_deadline_s;
      }
      else if (rule.scheduler.policy == SCHED_FIFO) {
        policy = controller_fifo_s;
      }
      else if (rule.scheduler.policy == SCHED_IDLE) {
        policy = controller_idle_s;
      }
      else if (rule.scheduler.policy == SCHED_OTHER) {
        policy = controller_other_s;
      }
      else if (rule.scheduler.policy == SCHED_RR) {
        policy = controller_round_robin_s;
      }

      fl_print_format(" %r %i", main->program.output.to, policy, rule.scheduler.priority);
    }

    f_print_dynamic_raw(f_string_eol_s, main->program.output.to);

    // Engine.
    if (rule.engine_arguments.used) {
      fl_print_format("  %[%r%] %Q", main->program.output.to, main->program.context.set.important, controller_engine_s, main->program.context.set.important, rule.engine);

      for (i = 0; i < rule.engine_arguments.used; ++i) {

        if (rule.engine_arguments.array[i].used) {
          fl_print_format(" %Q", main->program.output.to, rule.engine_arguments.array[i]);
        }
      } // for

      fl_print_format("%r", main->program.output.to, f_string_eol_s);
    }
    else {
      fl_print_format("  %[%r%] %Q%r", main->program.output.to, main->program.context.set.important, controller_engine_s, main->program.context.set.important, rule.engine, f_string_eol_s);
    }

    // User.
    fl_print_format("  %[%r%]", main->program.output.to, main->program.context.set.important, controller_user_s, main->program.context.set.important);

    if (rule.has & controller_rule_has_user_d) {
      fl_print_format(" %i", main->program.output.to, rule.user);
    }

    f_print_dynamic_raw(f_string_eol_s, main->program.output.to);

    // Wait.
    fl_print_format("  %[%r%] %r%r", main->program.output.to, main->program.context.set.important, controller_wait_s, main->program.context.set.important, options & controller_instance_option_wait_e ? controller_yes_s : controller_no_s, f_string_eol_s);

    // Affinity.
    fl_print_format("  %[%r%] {%r", main->program.output.to, main->program.context.set.important, controller_affinity_s, main->program.context.set.important, f_string_eol_s);

    for (i = 0; i < rule.affinity.used; ++i) {
      fl_print_format("    %i%r", main->program.output.to, rule.affinity.array[i], f_string_eol_s);
    } // for

    // Define.
    fl_print_format("  }%r  %[%r%] {%r", main->program.output.to, f_string_eol_s, main->program.context.set.important, controller_define_s, main->program.context.set.important, f_string_eol_s);

    for (i = 0; i < rule.define.used; ++i) {

      if (rule.define.array[i].key.used && rule.define.array[i].value.used) {
        fl_print_format("    %Q %[=%] %Q%r", main->program.output.to, rule.define.array[i].key, main->program.context.set.important, main->program.context.set.important, rule.define.array[i].value, f_string_eol_s);
      }
    } // for

    // Environment.
    fl_print_format("  }%r  %[%r%] {%r", main->program.output.to, f_string_eol_s, main->program.context.set.important, controller_environment_s, main->program.context.set.important, f_string_eol_s);

    for (i = 0; i < rule.environment.used; ++i) {

      if (rule.environment.array[i].used) {
        fl_print_format("    %Q%r", main->program.output.to, rule.environment.array[i], f_string_eol_s);
      }
    } // for

    fl_print_format("  }%r  %[%r%] {%r", main->program.output.to, f_string_eol_s, main->program.context.set.important, controller_parameter_s, main->program.context.set.important, f_string_eol_s);

    // Parameter.
    for (i = 0; i < rule.parameter.used; ++i) {

      if (rule.parameter.array[i].key.used && rule.parameter.array[i].value.used) {
        fl_print_format("    %Q %[=%] %Q%r", main->program.output.to, rule.parameter.array[i].key, main->program.context.set.important, main->program.context.set.important, rule.parameter.array[i].value, f_string_eol_s);
      }
    } // for

    // Group.
    fl_print_format("  }%r  %[%r%] {%r", main->program.output.to, f_string_eol_s, main->program.context.set.important, controller_group_s, main->program.context.set.important, f_string_eol_s);

    if (rule.has & controller_rule_has_group_d) {
      fl_print_format("    %i%r", main->program.output.to, rule.group, f_string_eol_s);

      for (i = 0; i < rule.groups.used; ++i) {
        fl_print_format("    %i%r", main->program.output.to, rule.groups.array[i], f_string_eol_s);
      } // for
    }

    // Limit.
    fl_print_format("  }%r  %[%r%] {%r", main->program.output.to, f_string_eol_s, main->program.context.set.important, controller_limit_s, main->program.context.set.important, f_string_eol_s);

    for (i = 0; i < rule.limits.used; ++i) {
      fl_print_format("    %Q %[=%] %un %un%r", main->program.output.to, controller_rule_setting_limit_type_name(rule.limits.array[i].type), main->program.context.set.important, main->program.context.set.important, rule.limits.array[i].value.rlim_cur, rule.limits.array[i].value.rlim_max, f_string_eol_s);
    } // for

    // On.
    fl_print_format("  }%r  %[%r%] {%r", main->program.output.to, f_string_eol_s, main->program.context.set.important, controller_on_s, main->program.context.set.important, f_string_eol_s);

    for (i = 0; i < rule.ons.used; ++i) {

      fl_print_format("    %[%r%] {%r", main->program.output.to, main->program.context.set.important, controller_action_s, main->program.context.set.important, f_string_eol_s);

      {
        f_string_static_t action = f_string_static_t_initialize;

        if (rule.ons.array[i].action == controller_rule_action_type_freeze_e) {
          action = controller_freeze_s;
        }
        else if (rule.ons.array[i].action == controller_rule_action_type_kill_e) {
          action = controller_kill_s;
        }
        else if (rule.ons.array[i].action == controller_rule_action_type_pause_e) {
          action = controller_pause_s;
        }
        else if (rule.ons.array[i].action == controller_rule_action_type_reload_e) {
          action = controller_reload_s;
        }
        else if (rule.ons.array[i].action == controller_rule_action_type_restart_e) {
          action = controller_restart_s;
        }
        else if (rule.ons.array[i].action == controller_rule_action_type_resume_e) {
          action = controller_resume_s;
        }
        else if (rule.ons.array[i].action == controller_rule_action_type_start_e) {
          action = controller_start_s;
        }
        else if (rule.ons.array[i].action == controller_rule_action_type_stop_e) {
          action = controller_stop_s;
        }
        else if (rule.ons.array[i].action == controller_rule_action_type_thaw_e) {
          action = controller_thaw_s;
        }

        fl_print_format("      %[%r%] %r%r", main->program.output.to, main->program.context.set.important, controller_type_s, main->program.context.set.important, action, f_string_eol_s);
      }

      fl_print_format("      %[%r%] {%r", main->program.output.to, main->program.context.set.important, controller_need_s, main->program.context.set.important, f_string_eol_s);

      for (j = 0; j < rule.ons.array[i].need.used; ++j) {

        if (rule.ons.array[i].need.array[j].used) {
          fl_print_format("        %Q%r", main->program.output.to, rule.ons.array[i].need.array[j], f_string_eol_s);
        }
      } // for

      fl_print_format("      }%r      %[%r%] {%r", main->program.output.to, f_string_eol_s, main->program.context.set.important, controller_want_s, main->program.context.set.important, f_string_eol_s);

      for (j = 0; j < rule.ons.array[i].want.used; ++j) {

        if (rule.ons.array[i].want.array[j].used) {
          fl_print_format("        %Q%r", main->program.output.to, rule.ons.array[i].want.array[j], f_string_eol_s);
        }
      } // for

      fl_print_format("      }%r      %[%r%] {%r", main->program.output.to, f_string_eol_s, main->program.context.set.important, controller_wish_s, main->program.context.set.important, f_string_eol_s);

      for (j = 0; j < rule.ons.array[i].wish.used; ++j) {

        if (rule.ons.array[i].wish.array[j].used) {
          fl_print_format("        %Q%r", main->program.output.to, rule.ons.array[i].wish.array[j], f_string_eol_s);
        }
      } // for

      fl_print_format("      }%r    }%r", main->program.output.to, f_string_eol_s, f_string_eol_s);
    } // for

    fl_print_format("  }%r", main->program.output.to, f_string_eol_s);

    // Items.
    if (rule.items.used) {
      controller_rule_action_t *action = 0;
      controller_rule_item_t *item = 0;
      controller_rule_rerun_item_t *rerun_item = 0;

      f_number_unsigned_t j = 0;
      f_number_unsigned_t k = 0;
      f_number_unsigned_t l = 0;

      for (i = 0; i < rule.items.used; ++i) {

        item = &rule.items.array[i];

        fl_print_format("  %[%r%] {%r", main->program.output.to, main->program.context.set.important, controller_item_s, main->program.context.set.important, f_string_eol_s);

        // Type.
        fl_print_format("    %[%r%] %Q%r", main->program.output.to, main->program.context.set.important, controller_type_s, main->program.context.set.important, controller_convert_rule_item_type_string(item->type), f_string_eol_s);

        // Pid file.
        fl_print_format("    %[%r%]", main->program.output.to, main->program.context.set.important, controller_pid_file_s, main->program.context.set.important);
        if (item->pid_file.used) {
          fl_print_format(" %Q", main->program.output.to, item->pid_file);
        }
        f_print_dynamic_raw(f_string_eol_s, main->program.output.to);

        // With.
        fl_print_format("    %[%r%]", main->program.output.to, main->program.context.set.important, controller_with_s, main->program.context.set.important);
        if (item->with & controller_with_full_path_d) {
          fl_print_format(" %r", main->program.output.to, controller_full_path_s);
        }
        if (item->with & controller_with_session_new_d) {
          fl_print_format(" %r", main->program.output.to, controller_session_new_s);
        }
        if (item->with & controller_with_session_same_d) {
          fl_print_format(" %r", main->program.output.to, controller_session_same_s);
        }
        f_print_dynamic_raw(f_string_eol_s, main->program.output.to);

        // Actions.
        for (j = 0; j < item->actions.used; ++j) {

          action = &item->actions.array[j];

          fl_print_format("    %[%r%] {%r", main->program.output.to, main->program.context.set.important, controller_action_s, main->program.context.set.important, f_string_eol_s);
          fl_print_format("      %[%r%] %r%r", main->program.output.to, main->program.context.set.important, controller_type_s, main->program.context.set.important, controller_convert_rule_action_type_string(action->type), f_string_eol_s);

          if (item->type == controller_rule_item_type_script_e || item->type == controller_rule_item_type_utility_e) {
            fl_print_format("      %[%r%] {%r", main->program.output.to, main->program.context.set.important, controller_parameter_s, main->program.context.set.important, f_string_eol_s);

            if (action->parameters.used) {
              if (action->parameters.array[0].used) {
                f_print_terminated("        ", main->program.output.to);

                for (k = 0; k < action->parameters.array[0].used; ++k) {

                  if (action->parameters.array[0].string[k] == f_fss_eol_s.string[0]) {
                    if (k + 1 < action->parameters.array[0].used) {
                      fl_print_format("%r        ", main->program.output.to, f_string_eol_s);
                    }
                  }
                  else {
                    f_print_character_safely(action->parameters.array[0].string[k], main->program.output.to);
                  }
                } // for
              }

              f_print_dynamic_raw(f_string_eol_s, main->program.output.to);
            }

            fl_print_format("      }%r", main->program.output.to, f_string_eol_s);
          }
          else {
            for (k = 0; k < action->parameters.used; ++k) {
              fl_print_format("      %[%r%] %Q%r", main->program.output.to, main->program.context.set.important, controller_parameter_s, main->program.context.set.important, action->parameters.array[k], f_string_eol_s);
            } // for
          }

          if (action->ikis.used) {
            fl_print_format("      %[%r%] {%r", main->program.output.to, main->program.context.set.important, controller_iki_s, main->program.context.set.important, f_string_eol_s);

            for (k = 0; k < action->ikis.used; ++k) {

              for (l = 0; l < action->ikis.array[j].vocabulary.used; ++l) {

                fl_print_format("        %[[%]%ul%[]%]", main->program.output.to, main->program.context.set.important, main->program.context.set.important, k, main->program.context.set.important, main->program.context.set.important);
                fl_print_format(" %/Q %[:%] %/Q%r", main->program.output.to, action->parameters.array[k], action->ikis.array[k].vocabulary.array[l], main->program.context.set.important, main->program.context.set.important, action->parameters.array[k], action->ikis.array[k].content.array[l], f_string_eol_s);
              } // for
            } // for

            fl_print_format("      }%r", main->program.output.to, f_string_eol_s);
          }

          fl_print_format("    }%r", main->program.output.to, f_string_eol_s);
        } // for

        // Rerun.
        fl_print_format("    %[%r%] {%r", main->program.output.to, main->program.context.set.important, controller_rerun_s, main->program.context.set.important, f_string_eol_s);
        for (j = 0; j < controller_rule_action_execute_type__enum_size_e; ++j) {

          for (k = 0; k < 2; ++k) {
            if (!k && (item->reruns[j].is & controller_rule_rerun_is_failure_d)) {
              rerun_item = &item->reruns[j].failure;
            }
            else if (k && (item->reruns[j].is & controller_rule_rerun_is_success_d)) {
              rerun_item = &item->reruns[j].success;
            }
            else {
              rerun_item = 0;
              continue;
            }

            fl_print_format("      %[", main->program.output.to, main->program.context.set.important);
            switch (j) {
              case controller_rule_action_execute_type_freeze_e:
                f_print_dynamic_raw(controller_freeze_s, main->program.output.to);
                break;

              case controller_rule_action_execute_type_kill_e:
                f_print_dynamic_raw(controller_kill_s, main->program.output.to);
                break;

              case controller_rule_action_execute_type_pause_e:
                f_print_dynamic_raw(controller_pause_s, main->program.output.to);
                break;

              case controller_rule_action_execute_type_reload_e:
                f_print_dynamic_raw(controller_reload_s, main->program.output.to);
                break;

              case controller_rule_action_execute_type_restart_e:
                f_print_dynamic_raw(controller_restart_s, main->program.output.to);
                break;

              case controller_rule_action_execute_type_resume_e:
                f_print_dynamic_raw(controller_resume_s, main->program.output.to);
                break;

              case controller_rule_action_execute_type_start_e:
                f_print_dynamic_raw(controller_start_s, main->program.output.to);
                break;

              case controller_rule_action_execute_type_stop_e:
                f_print_dynamic_raw(controller_stop_s, main->program.output.to);
                break;

              case controller_rule_action_execute_type_thaw_e:
                f_print_dynamic_raw(controller_thaw_s, main->program.output.to);
                break;

              default:
                break;
            }

            fl_print_format("%] %r", main->program.output.to, main->program.context.set.important, k ? controller_success_s : controller_failure_s);
            fl_print_format(" %r %ul %r %ul", main->program.output.to, controller_delay_s, rerun_item->delay, controller_max_s, rerun_item->max);

            if (!k && (item->reruns[j].is & controller_rule_rerun_is_failure_reset_d) || k && (item->reruns[j].is & controller_rule_rerun_is_success_reset_d)) {
              fl_print_format(" %r", main->program.output.to, controller_reset_s);
            }

            f_print_dynamic_raw(f_string_eol_s, main->program.output.to);
          } // for
        } // for
        fl_print_format("    }%r", main->program.output.to, f_string_eol_s);

        fl_print_format("  }%r", main->program.output.to, f_string_eol_s);
      } // for
    }

    fl_print_format("}%r", main->program.output.to, f_string_eol_s);

    controller_unlock_print_flush(main->program.output.to, &main->thread);
  }
#endif // _di_controller_rule_validate_

#ifdef __cplusplus
} // extern "C"
#endif
