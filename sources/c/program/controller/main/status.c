#include "controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_status_simplify_error_
  f_status_t controller_status_simplify_error(const f_status_t status) {

    switch (status) {
      case F_memory_not:
        return F_status_set_error(F_memory);

      case F_file_open_max:
      case F_space_not:
      case F_busy:
        return F_status_set_error(F_resource);

      case F_access_denied:
      case F_filesystem_quota_block:
      case F_prohibited:
      case F_input_output:
        return F_status_set_error(F_access);

      case F_complete_not_utf:
      case F_complete_not_utf_block:
      case F_complete_not_utf_eof:
      case F_complete_not_utf_eol:
      case F_complete_not_utf_eos:
      case F_complete_not_utf_stop:
        return F_status_set_error(F_encoding);

      case F_number:
      case F_number_negative:
      case F_number_positive:
      case F_number_overflow:
        return F_status_set_error(F_number);

      case F_parameter:
      case F_found_not:
      case F_interrupt:
      case F_support_not:
      case F_critical:
        return F_status_set_error(status);

      case F_valid_not:
        return F_status_set_error(F_valid_not);
    };

    return F_status_set_error(F_failure);
  }
#endif // _di_controller_status_simplify_error_

#ifdef __cplusplus
} // extern "C"
#endif
