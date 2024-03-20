#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_cache_delete_
  void controller_cache_delete(controller_cache_t * const cache) {

    if (!cache) return;

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &cache->buffer.string, &cache->buffer.used, &cache->buffer.size);
  }
#endif // _di_controller_cache_delete_

#ifndef _di_controller_main_delete_
  void controller_main_delete(controller_main_t * const main) {

    if (!main) return;

    fll_program_data_delete(&main->program);
    controller_setting_delete(&main->setting);
  }
#endif // _di_controller_main_delete_

#ifndef _di_controller_setting_delete_
  void controller_setting_delete(controller_setting_t * const setting) {

    if (!setting) return;
  }
#endif // _di_controller_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif
