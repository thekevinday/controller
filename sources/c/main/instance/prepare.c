#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_instance_prepare_
  f_status_t controller_instance_prepare(controller_global_t * const global, const bool is_normal, const uint8_t action, const f_string_static_t alias, f_number_unsigned_t *id) {

    if (!global) return F_status_set_error(F_parameter);

    f_status_t status = F_okay;

    if (controller_instance_find(action, alias, global->thread->instances, id) == F_false) {
      f_thread_unlock(&global->thread->lock.instance);

      status = controller_lock_write(is_normal, global->thread, &global->thread->lock.instance);

      if (F_status_is_error(status)) {
        controller_lock_print_error_critical(&global->main->program.error, F_status_set_fine(status), F_false, global->thread);
      }
      else {
        status = f_memory_array_increase(controller_allocation_small_d, sizeof(controller_instance_t), (void **) &global->thread->instances.array, &global->thread->instances.used, &global->thread->instances.size);
      }

      if (F_status_is_error_not(status) && global->thread->instances.array[global->thread->instances.used]) {

        controller_instance_t * const instance = global->thread->instances.array[global->thread->instances.used];

        status = controller_lock_write(is_normal, global->thread, &instance->lock);

        if (F_status_is_error(status)) {
          controller_lock_print_error_critical(&global->main->program.error, F_status_set_fine(status), F_false, global->thread);
        }
        else {
          instance->action = action;
          instance->rule.alias.used = 0;
          instance->global = global;

          status = f_string_dynamic_append(alias, &instance->rule.alias);

          if (F_status_is_error_not(status)) {
            instance->id = global->thread->instances.used++;
            status = F_okay;

            if (id) {
              *id = instance->id;
            }
          }

          f_thread_unlock(&instance->lock);
        }
      }

      f_thread_unlock(&global->thread->lock.instance);

      // The read lock must be restored on return.
      status = F_status_is_error(controller_lock_read(is_normal, global->thread, &global->thread->lock.instance))
        ? F_status_set_error(F_lock)
        : F_okay;
    }
    else {
      status = F_found;
    }

    return status;
  }
#endif // _di_controller_instance_prepare_

#ifndef _di_controller_instance_prepare_instance_type_
  f_status_t controller_instance_prepare_instance_type(controller_global_t * const global, const uint8_t type, const uint8_t action, const f_string_static_t alias, f_number_unsigned_t *id) {

    return controller_instance_prepare(global, type != controller_instance_type_exit_e, action, alias, id);
  }
#endif // _di_controller_instance_prepare_instance_type_

#ifdef __cplusplus
} // extern "C"
#endif
