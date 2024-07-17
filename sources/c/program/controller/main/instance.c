#include "controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_instance_find_
  f_status_t controller_instance_find(const f_number_unsigned_t action, const f_string_static_t alias, const controller_instances_t instances, f_number_unsigned_t * const at) {

    if (!alias.used) return F_okay;
    if (!instances.used) return F_false;

    for (f_number_unsigned_t i = 0; i < instances.used; ++i) {

      if (instances.array[i] && instances.array[i]->action == action && f_compare_dynamic(alias, instances.array[i]->rule.alias) == F_equal_to) {
        if (at) *at = i;

        return F_true;
      }
    } // for

    return F_false;
  }
#endif // _di_controller_instance_find_

#ifdef __cplusplus
} // extern "C"
#endif
