#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_rule_parameters_read_
  f_status_t controller_rule_parameters_read(controller_global_t * const global, const f_string_static_t buffer, f_range_t * const object, f_ranges_t * const content, controller_rule_action_t * const action, f_state_t * const state) {

    if (!global || !object || !content || !action || !state) return F_status_set_error(F_parameter);

    f_status_t status = F_okay;

    action->parameters.used = 0;
    action->ikis.used = 0;

    if (object && object->start <= object->stop) {
      if (content) {
        status = f_memory_array_increase_by(content->used + 1, sizeof(f_string_dynamic_t), (void **) &action->parameters.array, &action->parameters.used, &action->parameters.size);
      }
      else {
        status = f_memory_array_increase(controller_allocation_small_d, sizeof(f_string_dynamic_t), (void **) &action->parameters.array, &action->parameters.used, &action->parameters.size);
      }

      if (F_status_is_error_not(status)) {
        if (content) {
          status = f_memory_array_increase_by(content->used + 1, sizeof(f_iki_data_t), (void **) &action->ikis.array, &action->ikis.used, &action->ikis.size);
        }
        else {
          status = f_memory_array_increase(controller_allocation_small_d, sizeof(f_iki_data_t), (void **) &action->ikis.array, &action->ikis.used, &action->ikis.size);
        }
      }

      if (F_status_is_error(status)) {
        controller_main_print_error_status(&global->main->program.error, content ? macro_controller_f(f_memory_array_increase_by) : macro_controller_f(f_memory_array_increase), F_status_set_fine(status));

        return status;
      }

      action->parameters.array[action->parameters.used].used = 0;
      action->ikis.array[action->ikis.used].content.used = 0;
      action->ikis.array[action->ikis.used].delimits.used = 0;
      action->ikis.array[action->ikis.used].variable.used = 0;
      action->ikis.array[action->ikis.used].vocabulary.used = 0;

      status = f_string_dynamic_partial_append_nulless(buffer, *object, &action->parameters.array[0]);

      if (F_status_is_error(status)) {
        controller_main_print_error_status(&global->main->program.error, macro_controller_f(f_string_dynamic_partial_append_nulless), F_status_set_fine(status));

        return status;
      }

      ++action->parameters.used;
      ++action->ikis.used;
    }

    if (content && content->used) {
      status = f_memory_array_increase_by(content->used, sizeof(f_string_dynamic_t), (void **) &action->parameters.array, &action->parameters.used, &action->parameters.size);

      if (F_status_is_error_not(status)) {
        status = f_memory_array_increase_by(content->used, sizeof(f_iki_data_t), (void **) &action->ikis.array, &action->ikis.used, &action->ikis.size);
      }

      if (F_status_is_error(status)) {
        controller_main_print_error_status(&global->main->program.error, macro_controller_f(f_memory_array_increase_by), F_status_set_fine(status));

        return status;
      }

      f_range_t range = f_range_t_initialize;

      for (f_number_unsigned_t i = 0; i < content->used; ++i) {

        if (content->array[i].start > content->array[i].stop) continue;

        action->parameters.array[action->parameters.used].used = 0;
        action->ikis.array[action->ikis.used].content.used = 0;
        action->ikis.array[action->ikis.used].delimits.used = 0;
        action->ikis.array[action->ikis.used].variable.used = 0;
        action->ikis.array[action->ikis.used].vocabulary.used = 0;

        status = f_string_dynamic_partial_append_nulless(buffer, content->array[i], &action->parameters.array[action->parameters.used]);

        if (F_status_is_error(status)) {
          controller_main_print_error_status(&global->main->program.error, macro_controller_f(f_string_dynamic_partial_append_nulless), F_status_set_fine(status));

          return status;
        }

        if (action->parameters.array[action->parameters.used].used) {
          range.start = 0;
          range.stop = action->parameters.array[action->parameters.used].used - 1;

          fl_iki_read(&action->parameters.array[action->parameters.used], &range, &action->ikis.array[action->ikis.used], state);

          if (F_status_is_error(status)) {
            controller_main_print_error_status(&global->main->program.error, macro_controller_f(fl_iki_read), F_status_set_fine(status));

            action->parameters.array[action->parameters.used].used = 0;

            return status;
          }
        }

        ++action->parameters.used;
        ++action->ikis.used;
      } // for
    }

    return F_okay;
  }
#endif // _di_controller_rule_parameters_read_

#ifdef __cplusplus
} // extern "C"
#endif
