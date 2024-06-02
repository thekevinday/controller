#include "controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_convert_user_id_
  f_status_t controller_convert_user_id(const f_string_static_t buffer, const f_range_t range, controller_cache_t * const cache, uid_t * const id) {

    f_number_unsigned_t number = 0;

    f_status_t status = fl_conversion_dynamic_partial_to_unsigned_detect(fl_conversion_data_base_10_c, buffer, range, &number);

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_number) {
        cache->action.generic.used = 0;

        status = f_rip_dynamic_partial_nulless(buffer, range, &cache->action.generic);
        if (F_status_is_error(status)) return status;

        status = f_account_id_by_name(cache->action.generic, id);
        if (F_status_is_error(status)) return status;

        return (status == F_exist_not) ? F_status_set_error(F_exist_not) : F_okay;
      }

      return status;
    }

    return (number > F_type_size_32_unsigned_d) ? F_status_set_error(F_number_too_large) : F_okay;
  }
#endif // _di_controller_convert_user_id_

#ifndef _di_controller_convert_group_id_
  f_status_t controller_convert_group_id(const f_string_static_t buffer, const f_range_t range, controller_cache_t * const cache, gid_t * const id) {

    f_number_unsigned_t number = 0;

    f_status_t status = fl_conversion_dynamic_partial_to_unsigned_detect(fl_conversion_data_base_10_c, buffer, range, &number);

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_number) {
        cache->action.generic.used = 0;

        status = f_rip_dynamic_partial_nulless(buffer, range, &cache->action.generic);
        if (F_status_is_error(status)) return status;

        status = f_account_group_id_by_name(cache->action.generic, id);
        if (F_status_is_error(status)) return status;

        return (status == F_exist_not) ? F_status_set_error(F_exist_not) : F_okay;
      }

      return status;
    }

    return (number > F_type_size_32_unsigned_d) ? F_status_set_error(F_number_too_large) : F_okay;
  }
#endif // _di_controller_convert_group_id_

#ifndef _di_controller_convert_rule_action_execute_type_string_
  f_string_static_t controller_convert_rule_action_execute_type_string(const uint8_t type) {

    switch (type) {
      case controller_rule_action_execute_type_freeze_e:
        return controller_freeze_s;

      case controller_rule_action_execute_type_kill_e:
        return controller_kill_s;

      case controller_rule_action_execute_type_pause_e:
        return controller_pause_s;

      case controller_rule_action_execute_type_reload_e:
        return controller_reload_s;

      case controller_rule_action_execute_type_restart_e:
        return controller_restart_s;

      case controller_rule_action_execute_type_resume_e:
        return controller_resume_s;

      case controller_rule_action_execute_type_start_e:
        return controller_start_s;

      case controller_rule_action_execute_type_stop_e:
        return controller_stop_s;

      case controller_rule_action_execute_type_thaw_e:
        return controller_thaw_s;
    }

    return f_string_empty_s;
  }
#endif // _di_controller_convert_rule_action_execute_type_string_

#ifndef _di_controller_convert_rule_action_type_string_
  f_string_static_t controller_convert_rule_action_type_string(const uint8_t type) {

    switch (type) {
      case controller_rule_action_type_freeze_e:
        return controller_freeze_s;

      case controller_rule_action_type_group_e:
        return controller_group_s;

      case controller_rule_action_type_kill_e:
        return controller_kill_s;

      case controller_rule_action_type_pause_e:
        return controller_pause_s;

      case controller_rule_action_type_pid_file_e:
        return controller_pid_file_s;

      case controller_rule_action_type_reload_e:
        return controller_reload_s;

      case controller_rule_action_type_rerun_e:
        return controller_rerun_s;

      case controller_rule_action_type_restart_e:
        return controller_restart_s;

      case controller_rule_action_type_resume_e:
        return controller_resume_s;

      case controller_rule_action_type_start_e:
        return controller_start_s;

      case controller_rule_action_type_stop_e:
        return controller_stop_s;

      case controller_rule_action_type_thaw_e:
        return controller_thaw_s;

      case controller_rule_action_type_user_e:
        return controller_user_s;

      case controller_rule_action_type_with_e:
        return controller_with_s;
    }

    return f_string_empty_s;
  }
#endif // _di_controller_convert_rule_action_type_string_

#ifdef __cplusplus
} // extern "C"
#endif
