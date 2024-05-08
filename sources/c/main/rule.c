#include "controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_rule_copy_
  f_status_t controller_rule_copy(const controller_rule_t source, controller_rule_t *destination) {

    // Delete the third party structures.
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &destination->cgroup.path.string, &destination->cgroup.path.used, &destination->cgroup.path.size);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &destination->cgroup.groups.array, &destination->cgroup.groups.used, &destination->cgroup.groups.size, &f_string_dynamics_delete_callback);

    f_capability_delete(&destination->capability);

    f_number_unsigned_t i = 0;

    for (; i < controller_rule_action_type__enum_size_e; ++i) {
      destination->status[i] = source.status[i];
    } // for

    destination->timeout_kill = source.timeout_kill;
    destination->timeout_start = source.timeout_start;
    destination->timeout_stop = source.timeout_stop;

    destination->has = source.has;
    destination->nice = source.nice;
    destination->user = source.user;
    destination->group = source.group;

    destination->timestamp.seconds = source.timestamp.seconds;
    destination->timestamp.seconds_nano = source.timestamp.seconds_nano;

    destination->alias.used = 0;
    destination->engine.used = 0;
    destination->engine_arguments.used = 0;
    destination->name.used = 0;
    destination->path.used = 0;

    destination->define.used = 0;
    destination->parameter.used = 0;
    destination->environment.used = 0;

    destination->affinity.used = 0;
    destination->groups.used = 0;
    destination->limits.used = 0;
    destination->scheduler.policy = source.scheduler.policy;
    destination->scheduler.priority = source.scheduler.priority;

    for (i = 0; i < destination->ons.size; ++i) {

      destination->ons.array[i].action = 0;
      destination->ons.array[i].need.used = 0;
      destination->ons.array[i].want.used = 0;
      destination->ons.array[i].wish.used = 0;
    } // for

    for (i = 0; i < destination->engine_arguments.size; ++i) {
      destination->engine_arguments.array[i].used = 0;
    } // for

    destination->ons.used = 0;
    destination->items.used = 0;

    f_status_t status = F_okay;

    status = f_string_dynamic_append(source.alias, &destination->alias);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_append(source.engine, &destination->engine);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_append(source.name, &destination->name);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_append(source.path, &destination->path);
    if (F_status_is_error(status)) return status;

    status = f_string_maps_append_all(source.define, &destination->define);
    if (F_status_is_error(status)) return status;

    status = f_string_maps_append_all(source.parameter, &destination->parameter);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamics_append_all(source.engine_arguments, &destination->engine_arguments);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamics_append_all(source.environment, &destination->environment);
    if (F_status_is_error(status)) return status;

    if (source.ons.used) {
      if (destination->ons.used < source.ons.used) {
        status = f_memory_array_resize(source.ons.used, sizeof(controller_rule_on_t), (void **) &destination->ons.array, &destination->ons.used, &destination->ons.size);
        if (F_status_is_error(status)) return status;
      }

      for (i = 0; i < source.ons.used; ++i) {

        destination->ons.array[i].action = source.ons.array[i].action;

        if (source.ons.array[i].need.used) {
          destination->ons.array[i].need.used = 0;

          status = f_string_dynamics_append_all(source.ons.array[i].need, &destination->ons.array[i].need);
          if (F_status_is_error(status)) return status;
        }

        if (source.ons.array[i].want.used) {
          destination->ons.array[i].want.used = 0;

          status = f_string_dynamics_append_all(source.ons.array[i].want, &destination->ons.array[i].want);
          if (F_status_is_error(status)) return status;
        }

        if (source.ons.array[i].wish.used) {
          destination->ons.array[i].wish.used = 0;

          status = f_string_dynamics_append_all(source.ons.array[i].wish, &destination->ons.array[i].wish);
          if (F_status_is_error(status)) return status;
        }
      } // for

      destination->ons.used = source.ons.used;
    }

    status = f_memory_array_append_all(source.affinity.array, source.affinity.used, sizeof(int32_t), (void **) &destination->affinity.array, &destination->affinity.used, &destination->affinity.size);
    if (F_status_is_error(status)) return status;

    if (source.capability) {
      status = f_capability_copy(source.capability, &destination->capability);
      if (F_status_is_error(status)) return status;
    }

    status = f_control_group_copy(source.cgroup, &destination->cgroup);
    if (F_status_is_error(status)) return status;

    status = f_memory_array_append_all(source.groups.array, source.groups.used, sizeof(int32_t), (void **) &destination->groups.array, &destination->groups.used, &destination->groups.size);
    if (F_status_is_error(status)) return status;

    destination->limits.used = 0;
    status = f_memory_array_append_all(source.limits.array, source.limits.used, sizeof(f_limit_set_t), (void **) &destination->limits.array, &destination->limits.used, &destination->limits.size);
    if (F_status_is_error(status)) return status;

    if (source.items.used) {
      controller_rule_item_t *item_source = 0;
      controller_rule_item_t *item_destination = 0;

      controller_rule_action_t *action_source = 0;
      controller_rule_action_t *action_destination = 0;

      if (source.items.used > destination->items.size) {
        status = f_memory_arrays_resize(source.items.used, sizeof(controller_rule_item_t), (void **) &destination->items.array, &destination->items.used, &destination->items.size, &controller_rule_items_delete_callback);
        if (F_status_is_error(status)) return status;
      }

      f_number_unsigned_t j = 0;

      for (i = 0; i < source.items.used; ++i) {

        item_source = &source.items.array[i];
        item_destination = &destination->items.array[i];

        if (item_source->actions.used > item_destination->actions.size) {
          status = f_memory_arrays_resize(item_source->actions.used, sizeof(controller_rule_action_t), (void **) &item_destination->actions.array, &item_destination->actions.used, &item_destination->actions.size, &controller_rule_actions_delete_callback);
          if (F_status_is_error(status)) return status;
        }

        item_destination->type = item_source->type;
        item_destination->with = item_source->with;
        item_destination->line = item_source->line;
        item_destination->pid_file.used = 0;

        status = f_string_dynamic_append(item_source->pid_file, &item_destination->pid_file);
        if (F_status_is_error(status)) return status;

        for (j = 0; j < controller_rule_action_execute_type__enum_size_e; ++j) {

          item_destination->reruns[j].is = item_source->reruns[j].is;
          item_destination->reruns[j].failure.count = item_source->reruns[j].failure.count;
          item_destination->reruns[j].failure.delay = item_source->reruns[j].failure.delay;
          item_destination->reruns[j].failure.max = item_source->reruns[j].failure.max;
          item_destination->reruns[j].success.count = item_source->reruns[j].success.count;
          item_destination->reruns[j].success.delay = item_source->reruns[j].success.delay;
          item_destination->reruns[j].success.max = item_source->reruns[j].success.max;
        } // for

        for (j = 0; j < item_source->actions.used; ++j) {

          action_source = &item_source->actions.array[j];
          action_destination = &item_destination->actions.array[j];

          action_destination->type = action_source->type;
          action_destination->line = action_source->line;
          action_destination->status = action_source->status;

          action_destination->parameters.used = 0;
          action_destination->ikis.used = 0;

          status = f_string_dynamics_append_all(action_source->parameters, &action_destination->parameters);
          if (F_status_is_error(status)) return status;

          status = f_iki_datas_append_all(action_source->ikis, &action_destination->ikis);
          if (F_status_is_error(status)) return status;
        } // for

        item_destination->actions.used = item_source->actions.used;
      } // for

      destination->items.used = source.items.used;
    }

    return status;
  }
#endif // _di_controller_rule_copy_

#ifndef _di_controller_rule_find_
  f_status_t controller_rule_find(const f_string_static_t alias, const controller_rules_t rules, f_number_unsigned_t *at) {

    if (!alias.used) return F_okay;
    if (!rules.used) return F_false;

    for (f_number_unsigned_t i = 0; i < rules.used; ++i) {

      if (f_compare_dynamic(alias, rules.array[i].alias) == F_equal_to) {
        if (at) *at = i;

        return F_true;
      }
    } // for

    return F_false;
  }
#endif // _di_controller_rule_find_

#ifndef _di_controller_rule_id_construct_
  f_status_t controller_rule_id_construct(controller_global_t * const global, const f_string_static_t source, const f_range_t directory, const f_range_t basename, f_string_dynamic_t * const alias) {

    if (!global || !global->main || !global->thread) return F_status_set_error(F_parameter);

    alias->used = 0;

    f_status_t status = f_string_dynamic_partial_append_nulless(source, directory, alias);

    if (F_status_is_error(status)) {
      controller_main_print_error_status(&global->main->program.error, macro_controller_f(f_string_dynamic_partial_append_nulless), F_status_set_fine(status));

      return status;
    }

    status = f_string_dynamic_append(f_path_separator_s, alias);

    if (F_status_is_error(status)) {
      controller_main_print_error_status(&global->main->program.error, macro_controller_f(f_string_dynamic_append), F_status_set_fine(status));

      return status;
    }

    status = f_string_dynamic_partial_append_nulless(source, basename, alias);

    if (F_status_is_error(status)) {
      controller_main_print_error_status(&global->main->program.error, macro_controller_f(f_string_dynamic_partial_append_nulless), F_status_set_fine(status));

      return status;
    }

    return status;
  }
#endif // _di_controller_rule_id_construct_

#ifdef __cplusplus
} // extern "C"
#endif
