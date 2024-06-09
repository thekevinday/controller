#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_instance_prepare_
  f_status_t controller_instance_prepare(controller_t * const main, const bool is_normal, const uint8_t action, const f_string_static_t alias, f_number_unsigned_t *id) {

    if (!main) return F_status_set_error(F_parameter);

    f_status_t status = F_okay;

    if (controller_instance_find(action, alias, main->thread.instances, id) == F_false) {
      f_thread_unlock(&main->thread.lock.instance);

      status = controller_lock_write(is_normal, &main->thread, &main->thread.lock.instance);

      if (F_status_is_error(status)) {
        controller_print_error_lock_critical(&main->program.error, F_status_set_fine(status), F_false);
      }
      else {
        status = f_memory_array_increase(controller_allocation_small_d, sizeof(controller_instance_t), (void **) &main->thread.instances.array, &main->thread.instances.used, &main->thread.instances.size);
      }

      if (F_status_is_error_not(status) && main->thread.instances.array[main->thread.instances.used]) {

        controller_instance_t * const instance = main->thread.instances.array[main->thread.instances.used];

        status = controller_lock_write(is_normal, &main->thread, &instance->lock);

        if (F_status_is_error(status)) {
          controller_print_error_lock_critical(&main->program.error, F_status_set_fine(status), F_false);
        }
        else {
          instance->action = action;
          instance->rule.alias.used = 0;
          instance->main = main;

          status = f_string_dynamic_append(alias, &instance->rule.alias);

          if (F_status_is_error_not(status)) {
            instance->id = main->thread.instances.used++;
            status = F_okay;

            if (id) {
              *id = instance->id;
            }
          }

          f_thread_unlock(&instance->lock);
        }
      }

      f_thread_unlock(&main->thread.lock.instance);

      // The read lock must be restored on return.
      status = F_status_is_error(controller_lock_read(is_normal, &main->thread, &main->thread.lock.instance))
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
  f_status_t controller_instance_prepare_instance_type(controller_t * const main, const uint8_t type, const uint8_t action, const f_string_static_t alias, f_number_unsigned_t *id) {

    return controller_instance_prepare(main, type != controller_instance_type_exit_e, action, alias, id);
  }
#endif // _di_controller_instance_prepare_instance_type_

#ifdef __cplusplus
} // extern "C"
#endif
