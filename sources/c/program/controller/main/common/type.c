#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_delete_
  void controller_delete(controller_t * const controller) {

    if (!controller) return;

    fll_program_data_delete(&controller->program);

    controller_process_delete(&controller->process);
    controller_setting_delete(&controller->setting);
    controller_thread_delete(&controller->thread);
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
