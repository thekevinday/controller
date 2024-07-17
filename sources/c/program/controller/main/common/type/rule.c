#include "../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_rule_delete_
  void controller_rule_delete(controller_rule_t * const rule) {

    if (!rule) return;

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &rule->alias.string, &rule->alias.used, &rule->alias.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &rule->engine.string, &rule->engine.used, &rule->engine.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &rule->name.string, &rule->name.used, &rule->name.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &rule->path.string, &rule->path.used, &rule->path.size);

    f_memory_arrays_resize(0, sizeof(f_string_map_t), (void **) &rule->define.array, &rule->define.used, &rule->define.size, &f_string_maps_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_map_t), (void **) &rule->parameter.array, &rule->parameter.used, &rule->parameter.size, &f_string_maps_delete_callback);

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &rule->engine_arguments.array, &rule->engine_arguments.used, &rule->engine_arguments.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &rule->environment.array, &rule->environment.used, &rule->environment.size, &f_string_dynamics_delete_callback);

    f_memory_array_resize(0, sizeof(int32_t), (void **) &rule->affinity.array, &rule->affinity.used, &rule->affinity.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &rule->cgroup.path.string, &rule->cgroup.path.used, &rule->cgroup.path.size);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &rule->cgroup.groups.array, &rule->cgroup.groups.used, &rule->cgroup.groups.size, &f_string_dynamics_delete_callback);
    f_memory_array_resize(0, sizeof(int32_t), (void **) &rule->groups.array, &rule->groups.used, &rule->groups.size);
    f_memory_array_resize(0, sizeof(f_limit_set_t), (void **) &rule->limits.array, &rule->limits.used, &rule->limits.size);

    if (rule->capability) {
      f_capability_delete(&rule->capability);
    }

    f_memory_arrays_resize(0, sizeof(controller_rule_on_t), (void **) &rule->ons.array, &rule->ons.used, &rule->ons.size, &controller_rule_ons_delete_callback);
    f_memory_arrays_resize(0, sizeof(controller_rule_item_t), (void **) &rule->items.array, &rule->items.used, &rule->items.size, &controller_rule_items_delete_callback);
  }
#endif // _di_controller_rule_delete_

#ifndef _di_controller_rule_action_delete_
  void controller_rule_action_delete(controller_rule_action_t * const action) {

    if (!action) return;

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &action->parameters.array, &action->parameters.used, &action->parameters.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_iki_data_t), (void **) &action->ikis.array, &action->ikis.used, &action->ikis.size, &f_iki_datas_delete_callback);
  }
#endif // _di_controller_rule_action_delete_

#ifndef _di_controller_rule_actions_delete_callback_
  f_status_t controller_rule_actions_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      controller_rule_action_t * const controller_rule_actions = (controller_rule_action_t *) void_array;

      for (f_number_unsigned_t i = start; i < stop; ++i) {
        controller_rule_action_delete(&controller_rule_actions[i]);
      } // for
    }

    return F_okay;
  }
#endif // _di_controller_rule_actions_delete_callback_

#ifndef _di_controller_rule_item_delete_
  void controller_rule_item_delete(controller_rule_item_t * const item) {

    if (!item) return;

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &item->pid_file.string, &item->pid_file.used, &item->pid_file.size);
    f_memory_arrays_resize(0, sizeof(controller_rule_action_t), (void **) &item->actions.array, &item->actions.used, &item->actions.size, &controller_rule_actions_delete_callback);
  }
#endif // _di_controller_rule_item_delete_

#ifndef _di_controller_rule_items_delete_callback_
  f_status_t controller_rule_items_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      controller_rule_item_t * const controller_rule_items = (controller_rule_item_t *) void_array;

      for (f_number_unsigned_t i = start; i < stop; ++i) {
        controller_rule_item_delete(&controller_rule_items[i]);
      } // for
    }

    return F_okay;
  }
#endif // _di_controller_rule_items_delete_callback_

#ifndef _di_controller_rule_on_delete_
  void controller_rule_on_delete(controller_rule_on_t * const on) {

    if (!on) return;

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &on->need.array, &on->need.used, &on->need.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &on->want.array, &on->want.used, &on->want.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &on->wish.array, &on->wish.used, &on->wish.size, &f_string_dynamics_delete_callback);
  }
#endif // _di_controller_rule_on_delete_

#ifndef _di_controller_rule_ons_delete_callback_
  f_status_t controller_rule_ons_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      controller_rule_on_t * const controller_rule_ons = (controller_rule_on_t *) void_array;

      for (f_number_unsigned_t i = start; i < stop; ++i) {
        controller_rule_on_delete(&controller_rule_ons[i]);
      } // for
    }

    return F_okay;
  }
#endif // _di_controller_rule_ons_delete_callback_

#ifndef _di_controller_rules_delete_
  void controller_rules_delete(controller_rules_t * const rules) {

    if (!rules) return;

    rules->used = rules->size;

    while (rules->used) {
      controller_rule_delete(&rules->array[--rules->used]);
    } // while

    f_memory_array_resize(0, sizeof(controller_rule_t), (void **) &rules->array, &rules->used, &rules->size);
  }
#endif // _di_controller_rules_delete_

#ifdef __cplusplus
} // extern "C"
#endif
