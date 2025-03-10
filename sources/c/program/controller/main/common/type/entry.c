#include "../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_entry_action_delete_
  void controller_entry_action_delete(controller_entry_action_t * const action) {

    if (!action) return;

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &action->parameters.array, &action->parameters.used, &action->parameters.size, &f_string_dynamics_delete_callback);
  }
#endif // _di_controller_entry_action_delete_

#ifndef _di_controller_entry_actions_delete_
  void controller_entry_actions_delete(controller_entry_actions_t * const actions) {

    if (!actions) return;

    actions->used = actions->size;

    while (actions->used) {
      controller_entry_action_delete(&actions->array[--actions->used]);
    } // while

    f_memory_array_resize(0, sizeof(controller_entry_action_t), (void **) &actions->array, &actions->used, &actions->size);
  }
#endif // _di_controller_entry_actions_delete_

#ifndef _di_controller_entry_item_delete_
  void controller_entry_item_delete(controller_entry_item_t * const item) {

    if (!item) return;

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &item->name.string, &item->name.used, &item->name.size);

    controller_entry_actions_delete(&item->actions);
  }
#endif // _di_controller_entry_item_delete_

#ifndef _di_controller_entry_items_delete_
  void controller_entry_items_delete(controller_entry_items_t * const items) {

    if (!items) return;

    items->used = items->size;

    while (items->used) {
      controller_entry_item_delete(&items->array[--items->used]);
    } // while

    f_memory_array_resize(0, sizeof(controller_entry_item_t), (void **) &items->array, &items->used, &items->size);
  }
#endif // _di_controller_entry_items_delete_

#ifdef __cplusplus
} // extern "C"
#endif
