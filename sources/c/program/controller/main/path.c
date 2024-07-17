#include "controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_path_canonical_relative_
  f_status_t controller_path_canonical_relative(controller_t * const main, const f_string_static_t current, const f_string_static_t source, f_string_dynamic_t * const destination) {

    if (!main || !destination) return F_status_set_error(F_parameter);

    {
      const f_status_t status = fl_path_canonical(source, destination);
      if (F_status_is_error(status)) return status;
    }

    if (destination->used >= current.used) {
      const f_range_t range = macro_f_range_t_initialize_2(current.used);

      if (f_compare_dynamic_partial_string(destination->string, current, destination->used, range) == F_equal_to) {
        f_number_unsigned_t length = destination->used - current.used;

        if (length) {
          memmove(destination->string, destination->string + current.used + 1, sizeof(f_char_t) * (--length));

          destination->string[length] = 0;
          destination->used = length;
        }
        else {
          destination->used = 0;
        }
      }
    }

    return F_okay;
  }
#endif // _di_controller_path_canonical_relative_

#ifdef __cplusplus
} // extern "C"
#endif
