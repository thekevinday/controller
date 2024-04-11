#include "../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_process_delete_
  f_status_t controller_process_delete(controller_process_t * const process) {

    if (!process) return F_status_set_error(F_parameter);

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &process->name_entry.string, &process->name_entry.used, &process->name_entry.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &process->path_cgroup.string, &process->path_cgroup.used, &process->path_cgroup.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &process->path_control.string, &process->path_control.used, &process->path_control.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &process->path_current.string, &process->path_current.used, &process->path_current.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &process->path_pid.string, &process->path_pid.used, &process->path_pid.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &process->path_setting.string, &process->path_setting.used, &process->path_setting.size);

    controller_control_delete(&process->control);

    f_memory_arrays_resize(0, sizeof(f_string_map_t), (void **) &process->entry.define.array, &process->entry.define.used, &process->entry.define.size, &f_string_maps_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_map_t), (void **) &process->entry.parameter.array, &process->entry.parameter.used, &process->entry.parameter.size, &f_string_maps_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_map_t), (void **) &process->exit.define.array, &process->exit.define.used, &process->exit.define.size, &f_string_maps_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_map_t), (void **) &process->exit.parameter.array, &process->exit.parameter.used, &process->exit.parameter.size, &f_string_maps_delete_callback);

    controller_entry_items_delete(&process->entry.items);
    controller_entry_items_delete(&process->exit.items);

    controller_rules_delete(&process->rules);

    return F_okay;
  }
#endif // _di_controller_process_delete_

#ifdef __cplusplus
} // extern "C"
#endif
