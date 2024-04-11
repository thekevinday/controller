#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

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
