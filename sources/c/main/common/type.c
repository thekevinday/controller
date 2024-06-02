#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_delete_
  void controller_delete(controller_t * const main) {

    if (!main) return;

    fll_program_data_delete(&main->program);

    controller_cache_delete(&main->cache);
    controller_process_delete(&main->process);
    controller_setting_delete(&main->setting);
    controller_thread_delete(&main->thread);
  }
#endif // _di_controller_delete_

#ifndef _di_controller_setting_delete_
  void controller_setting_delete(controller_setting_t * const setting) {

    if (!setting) return;
  }
#endif // _di_controller_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif
