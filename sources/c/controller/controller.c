#include "controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_controller_main_
  void controller_controller_main(controller_main_t * const main, controller_program_t * const program) {

    if (!main || !program || F_status_is_error(main->setting.state.status)) return;

    main->setting.state.status = F_okay;

    if (main->setting.flag & controller_main_flag_version_copyright_help_e) {
      if (main->setting.flag & controller_main_flag_help_e) {
        controller_main_print_message_help(&main->program.message, F_false);
      }
      else if (main->setting.flag & controller_main_flag_version_e) {
        fll_program_print_version(&main->program.message, controller_program_version_s);
      }
      else if (main->setting.flag & controller_main_flag_copyright_e) {
        fll_program_print_copyright(&main->program.message, fll_program_copyright_year_author_s);
      }

      return;
    }

    // @todo controller_main(&data, &program);
    if (main->setting.state.status == F_status_set_error(F_child)) return;

    if (main->setting.state.status == F_status_set_error(F_interrupt)) {
      fll_program_print_signal_received(&main->program.warning, main->program.signal_received);
    }
  }
#endif // _di_controller_controller_main_

#ifdef __cplusplus
} // extern "C"
#endif
