#include "../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_rule_delete_
  void controller_rule_delete(controller_rule_t * const rule) {

    if (!rule) return;

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

    controller_rule_ons_delete(&rule->ons);
    controller_rule_items_delete(&rule->items);
  }
#endif // _di_controller_rule_delete_

#ifndef _di_controller_rule_action_delete_
  void controller_rule_action_delete(controller_rule_action_t * const action) {

    if (!action) return;

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &action->parameters.array, &action->parameters.used, &action->parameters.size, &f_string_dynamics_delete_callback);

    f_memory_array_resize(0, sizeof(f_iki_data_t), (void **) &action->ikis.array, &action->ikis.used, &action->ikis.size);
  }
#endif // _di_controller_rule_action_delete_

#ifndef _di_controller_rule_actions_delete_
  void controller_rule_actions_delete(controller_rule_actions_t * const actions) {

    if (!actions) return;

    actions->used = actions->size;

    while (actions->used) {
      controller_rule_action_delete(&actions->array[--actions->used]);
    } // while

    f_memory_array_resize(0, sizeof(controller_rule_action_t), (void **) &actions->array, &actions->used, &actions->size);
  }
#endif // _di_controller_rule_actions_delete_

#ifndef _di_controller_rule_item_delete_
  void controller_rule_item_delete(controller_rule_item_t * const item) {

    if (!item) return;

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &item->pid_file.string, &item->pid_file.used, &item->pid_file.size);

    controller_rule_actions_delete(&item->actions);
  }
#endif // _di_controller_rule_item_delete_

#ifndef _di_controller_rule_items_delete_
  void controller_rule_items_delete(controller_rule_items_t * const items) {

    if (!items) return;

    items->used = items->size;

    while (items->used) {
      controller_rule_item_delete(&items->array[--items->used]);
    } // while

    f_memory_array_resize(0, sizeof(controller_rule_item_t), (void **) &items->array, &items->used, &items->size);
  }
#endif // _di_controller_rule_items_delete_

#ifndef _di_controller_rule_on_delete_
  void controller_rule_on_delete(controller_rule_on_t * const on) {

    if (!on) return;

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &on->need.array, &on->need.used, &on->need.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &on->want.array, &on->want.used, &on->want.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &on->wish.array, &on->wish.used, &on->wish.size, &f_string_dynamics_delete_callback);
  }
#endif // _di_controller_rule_on_delete_

#ifndef _di_controller_rule_ons_delete_
  void controller_rule_ons_delete(controller_rule_ons_t * const ons) {

    if (!ons) return;

    ons->used = ons->size;

    while (ons->used) {
      controller_rule_on_delete(&ons->array[--ons->used]);
    } // while

    f_memory_array_resize(0, sizeof(controller_rule_on_t), (void **) &ons->array, &ons->used, &ons->size);
  }
#endif // _di_controller_rule_ons_delete_

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
