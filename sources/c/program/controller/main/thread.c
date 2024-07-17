#include "controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_thread_detach_
  f_status_t controller_thread_detach(f_thread_id_t * const id) {

    if (!id || !*id) return F_data_not;

    const f_status_t status = f_thread_detach(*id);

    if (F_status_is_error_not(status) || F_status_set_fine(status) == F_found_not) {
      *id = 0;
    }

    return status;
  }
#endif // _di_controller_thread_detach_

#ifndef _di_controller_thread_join_
  f_status_t controller_thread_join(f_thread_id_t * const id) {

    if (!id || !*id) return F_data_not;

    const f_status_t status = f_thread_join(*id, 0);

    if (F_status_is_error_not(status) || F_status_set_fine(status) == F_found_not) {
      *id = 0;
    }

    return status;
  }
#endif // _di_controller_thread_join_

#ifdef __cplusplus
} // extern "C"
#endif
