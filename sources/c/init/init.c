#include "init.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_init_process_entry_setup_
  f_status_t controller_init_process_entry_setup(controller_t * const main, controller_cache_t * const cache, controller_entry_t * const entry, const uint8_t is_entry) {

    if (!main || !entry || !cache) return F_status_set_error(F_parameter);

    entry->session = controller_entry_session_new_e;

    return F_okay;
  }
#endif // _di_controller_init_process_entry_setup_

#ifdef __cplusplus
} // extern "C"
#endif
