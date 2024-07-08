#include "../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_instance_delete_
  void controller_instance_delete(controller_instance_t * const instance) {

    if (!instance) return;

    if (instance->id_thread) {
      f_thread_signal_write(instance->id_thread, F_signal_kill);
      f_thread_join(instance->id_thread, 0);

      instance->id_thread = 0;
    }

    f_thread_condition_delete(&instance->wait);
    f_thread_lock_delete(&instance->lock);
    f_thread_lock_delete(&instance->active);
    f_thread_mutex_delete(&instance->wait_lock);

    controller_cache_delete(&instance->cache);
    controller_rule_delete(&instance->rule);

    f_memory_array_resize(0, sizeof(pid_t), (void **) &instance->childs.array, &instance->childs.used, &instance->childs.size);
    f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &instance->stack.array, &instance->stack.used, &instance->stack.size);

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &instance->path_pids.array, &instance->path_pids.used, &instance->path_pids.size, &f_string_dynamics_delete_callback);
  }
#endif // _di_controller_instance_delete_

#ifndef _di_controller_instances_delete_callback_
  f_status_t controller_instances_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      controller_instance_t ** const instances = (controller_instance_t **) void_array;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        if (instances[i]) {
          controller_instance_delete(instances[i]);

          f_memory_delete(1, sizeof(controller_instance_t), (void **) &instances[i]);

          instances[i] = 0;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_controller_instances_delete_callback_

#ifndef _di_controller_instance_initialize_
  f_status_t controller_instance_initialize(controller_instance_t ** restrict const instance) {

    if (!instance) return F_status_set_error(F_parameter);
    if (*instance) return F_okay;

    f_status_t status = f_memory_new(1, sizeof(controller_instance_t), (void **) instance);

    if (F_status_is_error_not(status)) {
      status = f_thread_lock_create(0, &(*instance)->lock);
    }

    if (F_status_is_error_not(status)) {
      status = f_thread_lock_create(0, &(*instance)->active);
    }

    if (F_status_is_error_not(status)) {
      status = f_thread_condition_create(0, &(*instance)->wait);
    }

    if (F_status_is_error_not(status)) {
      status = f_thread_mutex_create(0, &(*instance)->wait_lock);
    }

    for (f_number_unsigned_t i = 0; i < controller_rule_action_type__enum_size_e; ++i) {
      (*instance)->rule.status[i] = F_known_not;
    } // for

    return F_status_is_error(status) ? status : F_okay;
  }
#endif // _di_controller_instance_initialize_

#ifdef __cplusplus
} // extern "C"
#endif
