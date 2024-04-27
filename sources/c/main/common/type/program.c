#include "../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_program_delete_
  void controller_program_delete(controller_program_t * const program) {

    if (!program) return;

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &program->name_entry.string, &program->name_entry.used, &program->name_entry.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &program->path_cgroup.string, &program->path_cgroup.used, &program->path_cgroup.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &program->path_control.string, &program->path_control.used, &program->path_control.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &program->path_current.string, &program->path_current.used, &program->path_current.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &program->path_pid.string, &program->path_pid.used, &program->path_pid.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &program->path_setting.string, &program->path_setting.used, &program->path_setting.size);

    f_memory_arrays_resize(0, sizeof(f_string_map_t), (void **) &program->entry.define.array, &program->entry.define.used, &program->entry.define.size, &f_string_maps_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_map_t), (void **) &program->entry.parameter.array, &program->entry.parameter.used, &program->entry.parameter.size, &f_string_maps_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_map_t), (void **) &program->exit.define.array, &program->exit.define.used, &program->exit.define.size, &f_string_maps_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_map_t), (void **) &program->exit.parameter.array, &program->exit.parameter.used, &program->exit.parameter.size, &f_string_maps_delete_callback);

    controller_control_delete(&program->control);
    controller_entry_items_delete(&program->entry.items);
    controller_entry_items_delete(&program->exit.items);
    controller_rules_delete(&program->rules);
  }
#endif // _di_controller_program_delete_

#ifdef __cplusplus
} // extern "C"
#endif
