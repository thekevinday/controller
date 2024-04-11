#include "../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_control_delete_
  f_status_t controller_control_delete(controller_control_t * const control) {

    if (!control) return F_status_set_error(F_parameter);

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &control->cache_1.string, &control->cache_1.used, &control->cache_1.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &control->cache_2.string, &control->cache_2.used, &control->cache_2.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &control->cache_3.string, &control->cache_3.used, &control->cache_3.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &control->input.string, &control->input.used, &control->input.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &control->output.string, &control->output.used, &control->output.size);

    return F_okay;
  }
#endif // _di_controller_control_delete_

#ifdef __cplusplus
} // extern "C"
#endif
