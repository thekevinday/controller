#include "../../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_output_rule_validate_
  f_status_t controller_output_rule_validate(fl_print_t * const print, controller_cache_t * const cache, controller_rule_t * const rule, const uint8_t action, const uint8_t options) {

    if (!print || !print->custom || !cache || !rule) return F_status_set_error(F_output_not);

    controller_t * const main = (controller_t *) print->custom;

    f_number_unsigned_t i = 0;
    f_number_unsigned_t j = 0;

    // Find at least one of the requested action.
    {
      bool missing = F_true;

      for (; i < rule->items.used; ++i) {

        for (j = 0; j < rule->items.array[i].actions.used; ++j) {

          if (!action || rule->items.array[i].actions.array[j].type == action) {
            missing = F_false;

            break;
          }
        } // for
      } // for

      if (missing) {
        controller_lock_print(print->to, &main->thread);

        if (rule->items.used) {
          fl_print_format("%rRule '", print->to, f_string_eol_s);
          fl_print_format("%[%Q%]' has no '", print->to, print->set->title, rule->name, print->set->title);
          fl_print_format("%[%r%]' action to execute and would '", print->to, print->set->title, controller_convert_rule_action_type_string(action), print->set->title);
          fl_print_format("%[%r%]' because it is '", print->to, print->set->important, options & controller_instance_option_require_e ? controller_fail_s : controller_succeed_s, print->set->important);
          fl_print_format("%[%r%]'.%r", print->to, print->set->important, options & controller_instance_option_require_e ? controller_required_s : controller_optional_s, print->set->important, f_string_eol_s);
        }
        else {
          fl_print_format("%rRule '", print->to, f_string_eol_s);
          fl_print_format("%[%Q%]' has no known '", print->to, print->set->title, rule->name, print->set->title);
          fl_print_format("%[%r %r%]' (such as ", print->to, print->set->title, controller_rule_s, controller_type_s, print->set->title);
          fl_print_format("'%[%r%]', ", print->to, print->set->title, controller_command_s, print->set->title);
          fl_print_format("'%[%r%]', ", print->to, print->set->title, controller_service_s, print->set->title);
          fl_print_format("'%[%r%]', or ", print->to, print->set->title, controller_script_s, print->set->title);
          fl_print_format("'%[%r%]'", print->to, print->set->title, controller_utility_s, print->set->title);
          fl_print_format(") and would '%[%r%]' because it is '", print->to, print->set->important, options & controller_instance_option_require_e ? controller_fail_s : controller_succeed_s, print->set->important);
          fl_print_format("%[%r%]'.%r", print->to, print->set->important, options & controller_instance_option_require_e ? controller_required_s : controller_optional_s, print->set->important, f_string_eol_s);
        }

        controller_unlock_print_flush(print->to, &main->thread);
      }
    }

    controller_lock_print(print->to, &main->thread);

    fl_print_format("%rRule %[%Q%] {%r", print->to, f_string_eol_s, print->set->title, rule->alias, print->set->title, f_string_eol_s);

    // Name.
    fl_print_format("  %[%r%] %Q%r", print->to, print->set->important, controller_name_s, print->set->important, rule->name, f_string_eol_s);

    // Capability.
    fl_print_format("  %[%r%] ", print->to, print->set->important, controller_capability_s, print->set->important);

    if (f_capability_supported()) {
      if (rule->capability) {
        cache->action.generic.used = 0;

        if (F_status_is_error_not(f_capability_to_text(rule->capability, &cache->action.generic))) {
          f_print_dynamic_safely(cache->action.generic, print->to);
        }
      }

      f_print_dynamic_raw(f_string_eol_s, print->to);
    }
    else {
      fl_print_format("%[(unsupported)%]%r", print->to, print->set->warning, print->set->warning, f_string_eol_s);
    }

    // Control Group.
    fl_print_format("  %[%r%]", print->to, print->set->important, controller_cgroup_s, print->set->important);

    if (rule->has & controller_rule_has_cgroup_d) {
      fl_print_format(" %r", print->to, rule->cgroup.as_new ? controller_new_s : controller_existing_s);

      for (i = 0; i < rule->cgroup.groups.used; ++i) {

        if (rule->cgroup.groups.array[i].used) {
          fl_print_format(" %Q", print->to, rule->cgroup.groups.array[i]);
        }
      } // for
    }

    f_print_dynamic_raw(f_string_eol_s, print->to);

    // How.
    fl_print_format("  %[%r%] %r%r", print->to, print->set->important, controller_how_s, print->set->important, options & controller_instance_option_asynchronous_e ? controller_asynchronous_s : controller_synchronous_s, f_string_eol_s);

    // Nice.
    fl_print_format("  %[%r%]", print->to, print->set->important, controller_nice_s, print->set->important);

    if (rule->has & controller_rule_has_nice_d) {
      fl_print_format(" %i", print->to, rule->nice);
    }

    f_print_dynamic_raw(f_string_eol_s, print->to);

    // Scheduler.
    fl_print_format("  %[%r%]", print->to, print->set->important, controller_scheduler_s, print->set->important);

    if (rule->has & controller_rule_has_scheduler_d) {
      f_string_static_t policy = f_string_static_t_initialize;

      if (rule->scheduler.policy == SCHED_BATCH) {
        policy = controller_batch_s;
      }
      else if (rule->scheduler.policy == SCHED_DEADLINE) {
        policy = controller_deadline_s;
      }
      else if (rule->scheduler.policy == SCHED_FIFO) {
        policy = controller_fifo_s;
      }
      else if (rule->scheduler.policy == SCHED_IDLE) {
        policy = controller_idle_s;
      }
      else if (rule->scheduler.policy == SCHED_OTHER) {
        policy = controller_other_s;
      }
      else if (rule->scheduler.policy == SCHED_RR) {
        policy = controller_round_robin_s;
      }

      fl_print_format(" %r %i", print->to, policy, rule->scheduler.priority);
    }

    f_print_dynamic_raw(f_string_eol_s, print->to);

    // Engine.
    if (rule->engine_arguments.used) {
      fl_print_format("  %[%r%] %Q", print->to, print->set->important, controller_engine_s, print->set->important, rule->engine);

      for (i = 0; i < rule->engine_arguments.used; ++i) {

        if (rule->engine_arguments.array[i].used) {
          fl_print_format(" %Q", print->to, rule->engine_arguments.array[i]);
        }
      } // for

      fl_print_format("%r", print->to, f_string_eol_s);
    }
    else {
      fl_print_format("  %[%r%] %Q%r", print->to, print->set->important, controller_engine_s, print->set->important, rule->engine, f_string_eol_s);
    }

    // User.
    fl_print_format("  %[%r%]", print->to, print->set->important, controller_user_s, print->set->important);

    if (rule->has & controller_rule_has_user_d) {
      fl_print_format(" %i", print->to, rule->user);
    }

    f_print_dynamic_raw(f_string_eol_s, print->to);

    // Wait.
    fl_print_format("  %[%r%] %r%r", print->to, print->set->important, controller_wait_s, print->set->important, options & controller_instance_option_wait_e ? controller_yes_s : controller_no_s, f_string_eol_s);

    // Affinity.
    fl_print_format("  %[%r%] {%r", print->to, print->set->important, controller_affinity_s, print->set->important, f_string_eol_s);

    for (i = 0; i < rule->affinity.used; ++i) {
      fl_print_format("    %i%r", print->to, rule->affinity.array[i], f_string_eol_s);
    } // for

    // Define.
    fl_print_format("  }%r  %[%r%] {%r", print->to, f_string_eol_s, print->set->important, controller_define_s, print->set->important, f_string_eol_s);

    for (i = 0; i < rule->define.used; ++i) {

      if (rule->define.array[i].key.used && rule->define.array[i].value.used) {
        fl_print_format("    %Q %[=%] %Q%r", print->to, rule->define.array[i].key, print->set->important, print->set->important, rule->define.array[i].value, f_string_eol_s);
      }
    } // for

    // Environment.
    fl_print_format("  }%r  %[%r%] {%r", print->to, f_string_eol_s, print->set->important, controller_environment_s, print->set->important, f_string_eol_s);

    for (i = 0; i < rule->environment.used; ++i) {

      if (rule->environment.array[i].used) {
        fl_print_format("    %Q%r", print->to, rule->environment.array[i], f_string_eol_s);
      }
    } // for

    fl_print_format("  }%r  %[%r%] {%r", print->to, f_string_eol_s, print->set->important, controller_parameter_s, print->set->important, f_string_eol_s);

    // Parameter.
    for (i = 0; i < rule->parameter.used; ++i) {

      if (rule->parameter.array[i].key.used && rule->parameter.array[i].value.used) {
        fl_print_format("    %Q %[=%] %Q%r", print->to, rule->parameter.array[i].key, print->set->important, print->set->important, rule->parameter.array[i].value, f_string_eol_s);
      }
    } // for

    // Group.
    fl_print_format("  }%r  %[%r%] {%r", print->to, f_string_eol_s, print->set->important, controller_group_s, print->set->important, f_string_eol_s);

    if (rule->has & controller_rule_has_group_d) {
      fl_print_format("    %i%r", print->to, rule->group, f_string_eol_s);

      for (i = 0; i < rule->groups.used; ++i) {
        fl_print_format("    %i%r", print->to, rule->groups.array[i], f_string_eol_s);
      } // for
    }

    // Limit.
    fl_print_format("  }%r  %[%r%] {%r", print->to, f_string_eol_s, print->set->important, controller_limit_s, print->set->important, f_string_eol_s);

    for (i = 0; i < rule->limits.used; ++i) {
      fl_print_format("    %Q %[=%] %un %un%r", print->to, controller_rule_setting_limit_type_name(rule->limits.array[i].type), print->set->important, print->set->important, rule->limits.array[i].value.rlim_cur, rule->limits.array[i].value.rlim_max, f_string_eol_s);
    } // for

    // On.
    fl_print_format("  }%r  %[%r%] {%r", print->to, f_string_eol_s, print->set->important, controller_on_s, print->set->important, f_string_eol_s);

    for (i = 0; i < rule->ons.used; ++i) {

      fl_print_format("    %[%r%] {%r", print->to, print->set->important, controller_action_s, print->set->important, f_string_eol_s);

      {
        f_string_static_t action = f_string_static_t_initialize;

        if (rule->ons.array[i].action == controller_rule_action_type_freeze_e) {
          action = controller_freeze_s;
        }
        else if (rule->ons.array[i].action == controller_rule_action_type_kill_e) {
          action = controller_kill_s;
        }
        else if (rule->ons.array[i].action == controller_rule_action_type_pause_e) {
          action = controller_pause_s;
        }
        else if (rule->ons.array[i].action == controller_rule_action_type_reload_e) {
          action = controller_reload_s;
        }
        else if (rule->ons.array[i].action == controller_rule_action_type_restart_e) {
          action = controller_restart_s;
        }
        else if (rule->ons.array[i].action == controller_rule_action_type_resume_e) {
          action = controller_resume_s;
        }
        else if (rule->ons.array[i].action == controller_rule_action_type_start_e) {
          action = controller_start_s;
        }
        else if (rule->ons.array[i].action == controller_rule_action_type_stop_e) {
          action = controller_stop_s;
        }
        else if (rule->ons.array[i].action == controller_rule_action_type_thaw_e) {
          action = controller_thaw_s;
        }

        fl_print_format("      %[%r%] %r%r", print->to, print->set->important, controller_type_s, print->set->important, action, f_string_eol_s);
      }

      fl_print_format("      %[%r%] {%r", print->to, print->set->important, controller_need_s, print->set->important, f_string_eol_s);

      for (j = 0; j < rule->ons.array[i].need.used; ++j) {

        if (rule->ons.array[i].need.array[j].used) {
          fl_print_format("        %Q%r", print->to, rule->ons.array[i].need.array[j], f_string_eol_s);
        }
      } // for

      fl_print_format("      }%r      %[%r%] {%r", print->to, f_string_eol_s, print->set->important, controller_want_s, print->set->important, f_string_eol_s);

      for (j = 0; j < rule->ons.array[i].want.used; ++j) {

        if (rule->ons.array[i].want.array[j].used) {
          fl_print_format("        %Q%r", print->to, rule->ons.array[i].want.array[j], f_string_eol_s);
        }
      } // for

      fl_print_format("      }%r      %[%r%] {%r", print->to, f_string_eol_s, print->set->important, controller_wish_s, print->set->important, f_string_eol_s);

      for (j = 0; j < rule->ons.array[i].wish.used; ++j) {

        if (rule->ons.array[i].wish.array[j].used) {
          fl_print_format("        %Q%r", print->to, rule->ons.array[i].wish.array[j], f_string_eol_s);
        }
      } // for

      fl_print_format("      }%r    }%r", print->to, f_string_eol_s, f_string_eol_s);
    } // for

    fl_print_format("  }%r", print->to, f_string_eol_s);

    // Items.
    if (rule->items.used) {
      controller_rule_action_t *action = 0;
      controller_rule_item_t *item = 0;
      controller_rule_rerun_item_t *rerun_item = 0;

      f_number_unsigned_t j = 0;
      f_number_unsigned_t k = 0;
      f_number_unsigned_t l = 0;

      for (i = 0; i < rule->items.used; ++i) {

        item = &rule->items.array[i];

        fl_print_format("  %[%r%] {%r", print->to, print->set->important, controller_item_s, print->set->important, f_string_eol_s);

        // Type.
        fl_print_format("    %[%r%] %Q%r", print->to, print->set->important, controller_type_s, print->set->important, controller_convert_rule_item_type_string(item->type), f_string_eol_s);

        // Pid file.
        fl_print_format("    %[%r%]", print->to, print->set->important, controller_pid_file_s, print->set->important);
        if (item->pid_file.used) {
          fl_print_format(" %Q", print->to, item->pid_file);
        }
        f_print_dynamic_raw(f_string_eol_s, print->to);

        // With.
        fl_print_format("    %[%r%]", print->to, print->set->important, controller_with_s, print->set->important);
        if (item->with & controller_with_full_path_d) {
          fl_print_format(" %r", print->to, controller_full_path_s);
        }
        if (item->with & controller_with_session_new_d) {
          fl_print_format(" %r", print->to, controller_session_new_s);
        }
        if (item->with & controller_with_session_same_d) {
          fl_print_format(" %r", print->to, controller_session_same_s);
        }
        f_print_dynamic_raw(f_string_eol_s, print->to);

        // Actions.
        for (j = 0; j < item->actions.used; ++j) {

          action = &item->actions.array[j];

          fl_print_format("    %[%r%] {%r", print->to, print->set->important, controller_action_s, print->set->important, f_string_eol_s);
          fl_print_format("      %[%r%] %r%r", print->to, print->set->important, controller_type_s, print->set->important, controller_convert_rule_action_type_string(action->type), f_string_eol_s);

          if (item->type == controller_rule_item_type_script_e || item->type == controller_rule_item_type_utility_e) {
            fl_print_format("      %[%r%] {%r", print->to, print->set->important, controller_parameter_s, print->set->important, f_string_eol_s);

            if (action->parameters.used) {
              if (action->parameters.array[0].used) {
                f_print_terminated("        ", print->to);

                for (k = 0; k < action->parameters.array[0].used; ++k) {

                  if (action->parameters.array[0].string[k] == f_fss_eol_s.string[0]) {
                    if (k + 1 < action->parameters.array[0].used) {
                      fl_print_format("%r        ", print->to, f_string_eol_s);
                    }
                  }
                  else {
                    f_print_character_safely(action->parameters.array[0].string[k], print->to);
                  }
                } // for
              }

              f_print_dynamic_raw(f_string_eol_s, print->to);
            }

            fl_print_format("      }%r", print->to, f_string_eol_s);
          }
          else {
            for (k = 0; k < action->parameters.used; ++k) {
              fl_print_format("      %[%r%] %Q%r", print->to, print->set->important, controller_parameter_s, print->set->important, action->parameters.array[k], f_string_eol_s);
            } // for
          }

          if (action->ikis.used) {
            fl_print_format("      %[%r%] {%r", print->to, print->set->important, controller_iki_s, print->set->important, f_string_eol_s);

            for (k = 0; k < action->ikis.used; ++k) {

              for (l = 0; l < action->ikis.array[j].vocabulary.used; ++l) {

                fl_print_format("        %[[%]%ul%[]%]", print->to, print->set->important, print->set->important, k, print->set->important, print->set->important);
                fl_print_format(" %/Q %[:%] %/Q%r", print->to, action->parameters.array[k], action->ikis.array[k].vocabulary.array[l], print->set->important, print->set->important, action->parameters.array[k], action->ikis.array[k].content.array[l], f_string_eol_s);
              } // for
            } // for

            fl_print_format("      }%r", print->to, f_string_eol_s);
          }

          fl_print_format("    }%r", print->to, f_string_eol_s);
        } // for

        // Rerun.
        fl_print_format("    %[%r%] {%r", print->to, print->set->important, controller_rerun_s, print->set->important, f_string_eol_s);
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

            fl_print_format("      %[", print->to, print->set->important);
            switch (j) {
              case controller_rule_action_execute_type_freeze_e:
                f_print_dynamic_raw(controller_freeze_s, print->to);
                break;

              case controller_rule_action_execute_type_kill_e:
                f_print_dynamic_raw(controller_kill_s, print->to);
                break;

              case controller_rule_action_execute_type_pause_e:
                f_print_dynamic_raw(controller_pause_s, print->to);
                break;

              case controller_rule_action_execute_type_reload_e:
                f_print_dynamic_raw(controller_reload_s, print->to);
                break;

              case controller_rule_action_execute_type_restart_e:
                f_print_dynamic_raw(controller_restart_s, print->to);
                break;

              case controller_rule_action_execute_type_resume_e:
                f_print_dynamic_raw(controller_resume_s, print->to);
                break;

              case controller_rule_action_execute_type_start_e:
                f_print_dynamic_raw(controller_start_s, print->to);
                break;

              case controller_rule_action_execute_type_stop_e:
                f_print_dynamic_raw(controller_stop_s, print->to);
                break;

              case controller_rule_action_execute_type_thaw_e:
                f_print_dynamic_raw(controller_thaw_s, print->to);
                break;

              default:
                break;
            }

            fl_print_format("%] %r", print->to, print->set->important, k ? controller_success_s : controller_failure_s);
            fl_print_format(" %r %ul %r %ul", print->to, controller_delay_s, rerun_item->delay, controller_max_s, rerun_item->max);

            if (!k && (item->reruns[j].is & controller_rule_rerun_is_failure_reset_d) || k && (item->reruns[j].is & controller_rule_rerun_is_success_reset_d)) {
              fl_print_format(" %r", print->to, controller_reset_s);
            }

            f_print_dynamic_raw(f_string_eol_s, print->to);
          } // for
        } // for
        fl_print_format("    }%r", print->to, f_string_eol_s);

        fl_print_format("  }%r", print->to, f_string_eol_s);
      } // for
    }

    fl_print_format("}%r", print->to, f_string_eol_s);

    controller_unlock_print_flush(print->to, &main->thread);

    return F_okay;
  }
#endif // _di_controller_output_rule_validate_

#ifdef __cplusplus
} // extern "C"
#endif
