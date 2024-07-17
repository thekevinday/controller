#include "controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_validate_define_name_
  f_status_t controller_validate_environment_name(const f_string_static_t name) {

    if (!name.used) return F_okay;

    f_status_t status = F_okay;

    if (name.string[0] != '_') {
      status = f_utf_is_alphabetic(name.string, name.used);

      if (F_status_is_error(status)) return status;
      if (status == F_false) return F_false;
    }

    for (f_number_unsigned_t i = macro_f_utf_byte_width(name.string[0]); i < name.used; i += macro_f_utf_byte_width(name.string[i])) {

      if (name.string[i] == '_') continue;

      status = f_utf_is_alphabetic_digit(name.string, name.used, 0);

      if (F_status_is_error(status)) return status;
      if (status == F_false) return F_false;
    } // for

    return F_true;
  }
#endif // _di_controller_validate_define_name_

#ifndef _di_controller_validate_has_graph_
  f_status_t controller_validate_has_graph(const f_string_static_t name) {

    if (!name.used) return F_okay;

    f_status_t status = F_okay;

    for (f_number_unsigned_t i = 0; i < name.used; i += macro_f_utf_byte_width(name.string[i])) {

      status = f_utf_is_graph(name.string, name.used);

      if (F_status_is_error(status)) return status;
      if (status == F_true) return F_true;
    } // for

    return F_false;
  }
#endif // _di_controller_validate_has_graph_

#ifdef __cplusplus
} // extern "C"
#endif
