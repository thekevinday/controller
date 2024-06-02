#include "../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_string_s_
  const f_string_static_t controller_action_s = macro_f_string_static_t_initialize_1(CONTROLLER_action_s, 0, CONTROLLER_action_s_length);
  const f_string_static_t controller_actions_s = macro_f_string_static_t_initialize_1(CONTROLLER_actions_s, 0, CONTROLLER_actions_s_length);
  const f_string_static_t controller_affinity_s = macro_f_string_static_t_initialize_1(CONTROLLER_affinity_s, 0, CONTROLLER_affinity_s_length);
  const f_string_static_t controller_as_s = macro_f_string_static_t_initialize_1(CONTROLLER_as_s, 0, CONTROLLER_as_s_length);
  const f_string_static_t controller_asynchronous_s = macro_f_string_static_t_initialize_1(CONTROLLER_asynchronous_s, 0, CONTROLLER_asynchronous_s_length);
  const f_string_static_t controller_bash_s = macro_f_string_static_t_initialize_1(CONTROLLER_bash_s, 0, CONTROLLER_bash_s_length);
  const f_string_static_t controller_batch_s = macro_f_string_static_t_initialize_1(CONTROLLER_batch_s, 0, CONTROLLER_batch_s_length);
  const f_string_static_t controller_capability_s = macro_f_string_static_t_initialize_1(CONTROLLER_capability_s, 0, CONTROLLER_capability_s_length);
  const f_string_static_t controller_cgroup_s = macro_f_string_static_t_initialize_1(CONTROLLER_cgroup_s, 0, CONTROLLER_cgroup_s_length);
  const f_string_static_t controller_create_s = macro_f_string_static_t_initialize_1(CONTROLLER_create_s, 0, CONTROLLER_create_s_length);
  const f_string_static_t controller_command_s = macro_f_string_static_t_initialize_1(CONTROLLER_command_s, 0, CONTROLLER_command_s_length);
  const f_string_static_t controller_consider_s = macro_f_string_static_t_initialize_1(CONTROLLER_consider_s, 0, CONTROLLER_consider_s_length);
  const f_string_static_t controller_control_s = macro_f_string_static_t_initialize_1(CONTROLLER_control_s, 0, CONTROLLER_control_s_length);
  const f_string_static_t controller_control_group_s = macro_f_string_static_t_initialize_1(CONTROLLER_control_group_s, 0, CONTROLLER_control_group_s_length);
  const f_string_static_t controller_control_has_s = macro_f_string_static_t_initialize_1(CONTROLLER_control_has_s, 0, CONTROLLER_control_has_s_length);
  const f_string_static_t controller_control_mode_s = macro_f_string_static_t_initialize_1(CONTROLLER_control_mode_s, 0, CONTROLLER_control_mode_s_length);
  const f_string_static_t controller_control_user_s = macro_f_string_static_t_initialize_1(CONTROLLER_control_user_s, 0, CONTROLLER_control_user_s_length);
  const f_string_static_t controller_controller_s = macro_f_string_static_t_initialize_1(CONTROLLER_controller_s, 0, CONTROLLER_controller_s_length);
  const f_string_static_t controller_cpu_s = macro_f_string_static_t_initialize_1(CONTROLLER_cpu_s, 0, CONTROLLER_cpu_s_length);
  const f_string_static_t controller_core_s = macro_f_string_static_t_initialize_1(CONTROLLER_core_s, 0, CONTROLLER_core_s_length);
  const f_string_static_t controller_data_s = macro_f_string_static_t_initialize_1(CONTROLLER_data_s, 0, CONTROLLER_data_s_length);
  const f_string_static_t controller_deadline_s = macro_f_string_static_t_initialize_1(CONTROLLER_deadline_s, 0, CONTROLLER_deadline_s_length);
  const f_string_static_t controller_default_s = macro_f_string_static_t_initialize_1(CONTROLLER_default_s, 0, CONTROLLER_default_s_length);
  const f_string_static_t controller_define_s = macro_f_string_static_t_initialize_1(CONTROLLER_define_s, 0, CONTROLLER_define_s_length);
  const f_string_static_t controller_delay_s = macro_f_string_static_t_initialize_1(CONTROLLER_delay_s, 0, CONTROLLER_delay_s_length);
  const f_string_static_t controller_directory_s = macro_f_string_static_t_initialize_1(CONTROLLER_directory_s, 0, CONTROLLER_directory_s_length);
  const f_string_static_t controller_disable_s = macro_f_string_static_t_initialize_1(CONTROLLER_disable_s, 0, CONTROLLER_disable_s_length);
  const f_string_static_t controller_engine_s = macro_f_string_static_t_initialize_1(CONTROLLER_engine_s, 0, CONTROLLER_engine_s_length);
  const f_string_static_t controller_entry_s = macro_f_string_static_t_initialize_1(CONTROLLER_entry_s, 0, CONTROLLER_entry_s_length);
  const f_string_static_t controller_entries_s = macro_f_string_static_t_initialize_1(CONTROLLER_entries_s, 0, CONTROLLER_entries_s_length);
  const f_string_static_t controller_environment_s = macro_f_string_static_t_initialize_1(CONTROLLER_environment_s, 0, CONTROLLER_environment_s_length);
  const f_string_static_t controller_error_s = macro_f_string_static_t_initialize_1(CONTROLLER_error_s, 0, CONTROLLER_error_s_length);
  const f_string_static_t controller_execute_s = macro_f_string_static_t_initialize_1(CONTROLLER_execute_s, 0, CONTROLLER_execute_s_length);
  const f_string_static_t controller_existing_s = macro_f_string_static_t_initialize_1(CONTROLLER_existing_s, 0, CONTROLLER_existing_s_length);
  const f_string_static_t controller_exit_s = macro_f_string_static_t_initialize_1(CONTROLLER_exit_s, 0, CONTROLLER_exit_s_length);
  const f_string_static_t controller_exits_s = macro_f_string_static_t_initialize_1(CONTROLLER_exits_s, 0, CONTROLLER_exits_s_length);
  const f_string_static_t controller_fail_s = macro_f_string_static_t_initialize_1(CONTROLLER_fail_s, 0, CONTROLLER_fail_s_length);
  const f_string_static_t controller_failsafe_s = macro_f_string_static_t_initialize_1(CONTROLLER_failsafe_s, 0, CONTROLLER_failsafe_s_length);
  const f_string_static_t controller_failure_s = macro_f_string_static_t_initialize_1(CONTROLLER_failure_s, 0, CONTROLLER_failure_s_length);
  const f_string_static_t controller_fifo_s = macro_f_string_static_t_initialize_1(CONTROLLER_fifo_s, 0, CONTROLLER_fifo_s_length);
  const f_string_static_t controller_file_s = macro_f_string_static_t_initialize_1(CONTROLLER_file_s, 0, CONTROLLER_file_s_length);
  const f_string_static_t controller_freeze_s = macro_f_string_static_t_initialize_1(CONTROLLER_freeze_s, 0, CONTROLLER_freeze_s_length);
  const f_string_static_t controller_fsize_s = macro_f_string_static_t_initialize_1(CONTROLLER_fsize_s, 0, CONTROLLER_fsize_s_length);
  const f_string_static_t controller_full_path_s = macro_f_string_static_t_initialize_1(CONTROLLER_full_path_s, 0, CONTROLLER_full_path_s_length);
  const f_string_static_t controller_group_s = macro_f_string_static_t_initialize_1(CONTROLLER_group_s, 0, CONTROLLER_group_s_length);
  const f_string_static_t controller_groups_s = macro_f_string_static_t_initialize_1(CONTROLLER_groups_s, 0, CONTROLLER_groups_s_length);
  const f_string_static_t controller_helper_s = macro_f_string_static_t_initialize_1(CONTROLLER_helper_s, 0, CONTROLLER_helper_s_length);
  const f_string_static_t controller_how_s = macro_f_string_static_t_initialize_1(CONTROLLER_how_s, 0, CONTROLLER_how_s_length);
  const f_string_static_t controller_idle_s = macro_f_string_static_t_initialize_1(CONTROLLER_idle_s, 0, CONTROLLER_idle_s_length);
  const f_string_static_t controller_iki_s = macro_f_string_static_t_initialize_1(CONTROLLER_iki_s, 0, CONTROLLER_iki_s_length);
  const f_string_static_t controller_item_s = macro_f_string_static_t_initialize_1(CONTROLLER_item_s, 0, CONTROLLER_item_s_length);
  const f_string_static_t controller_init_s = macro_f_string_static_t_initialize_1(CONTROLLER_init_s, 0, CONTROLLER_init_s_length);
  const f_string_static_t controller_kexec_s = macro_f_string_static_t_initialize_1(CONTROLLER_kexec_s, 0, CONTROLLER_kexec_s_length);
  const f_string_static_t controller_kill_s = macro_f_string_static_t_initialize_1(CONTROLLER_kill_s, 0, CONTROLLER_kill_s_length);
  const f_string_static_t controller_length_s = macro_f_string_static_t_initialize_1(CONTROLLER_length_s, 0, CONTROLLER_length_s_length);
  const f_string_static_t controller_limit_s = macro_f_string_static_t_initialize_1(CONTROLLER_limit_s, 0, CONTROLLER_limit_s_length);
  const f_string_static_t controller_locks_s = macro_f_string_static_t_initialize_1(CONTROLLER_locks_s, 0, CONTROLLER_locks_s_length);
  const f_string_static_t controller_s = macro_f_string_static_t_initialize_1(CONTROLLER_main_s, 0, CONTROLLER_main_s_length);
  const f_string_static_t controller_max_s = macro_f_string_static_t_initialize_1(CONTROLLER_max_s, 0, CONTROLLER_max_s_length);
  const f_string_static_t controller_memlock_s = macro_f_string_static_t_initialize_1(CONTROLLER_memlock_s, 0, CONTROLLER_memlock_s_length);
  const f_string_static_t controller_method_s = macro_f_string_static_t_initialize_1(CONTROLLER_method_s, 0, CONTROLLER_method_s_length);
  const f_string_static_t controller_mode_s = macro_f_string_static_t_initialize_1(CONTROLLER_mode_s, 0, CONTROLLER_mode_s_length);
  const f_string_static_t controller_msgqueue_s = macro_f_string_static_t_initialize_1(CONTROLLER_msgqueue_s, 0, CONTROLLER_msgqueue_s_length);
  const f_string_static_t controller_name_s = macro_f_string_static_t_initialize_1(CONTROLLER_name_s, 0, CONTROLLER_name_s_length);
  const f_string_static_t controller_need_s = macro_f_string_static_t_initialize_1(CONTROLLER_need_s, 0, CONTROLLER_need_s_length);
  const f_string_static_t controller_new_s = macro_f_string_static_t_initialize_1(CONTROLLER_new_s, 0, CONTROLLER_new_s_length);
  const f_string_static_t controller_nice_s = macro_f_string_static_t_initialize_1(CONTROLLER_nice_s, 0, CONTROLLER_nice_s_length);
  const f_string_static_t controller_no_s = macro_f_string_static_t_initialize_1(CONTROLLER_no_s, 0, CONTROLLER_no_s_length);
  const f_string_static_t controller_nofile_s = macro_f_string_static_t_initialize_1(CONTROLLER_nofile_s, 0, CONTROLLER_nofile_s_length);
  const f_string_static_t controller_normal_s = macro_f_string_static_t_initialize_1(CONTROLLER_normal_s, 0, CONTROLLER_normal_s_length);
  const f_string_static_t controller_nproc_s = macro_f_string_static_t_initialize_1(CONTROLLER_nproc_s, 0, CONTROLLER_nproc_s_length);
  const f_string_static_t controller_on_s = macro_f_string_static_t_initialize_1(CONTROLLER_on_s, 0, CONTROLLER_on_s_length);
  const f_string_static_t controller_optional_s = macro_f_string_static_t_initialize_1(CONTROLLER_optional_s, 0, CONTROLLER_optional_s_length);
  const f_string_static_t controller_other_s = macro_f_string_static_t_initialize_1(CONTROLLER_other_s, 0, CONTROLLER_other_s_length);
  const f_string_static_t controller_parameter_s = macro_f_string_static_t_initialize_1(CONTROLLER_parameter_s, 0, CONTROLLER_parameter_s_length);
  const f_string_static_t controller_parameters_s = macro_f_string_static_t_initialize_1(CONTROLLER_parameters_s, 0, CONTROLLER_parameters_s_length);
  const f_string_static_t controller_path_s = macro_f_string_static_t_initialize_1(CONTROLLER_path_s, 0, CONTROLLER_path_s_length);
  const f_string_static_t controller_pause_s = macro_f_string_static_t_initialize_1(CONTROLLER_pause_s, 0, CONTROLLER_pause_s_length);
  const f_string_static_t controller_payload_type_s = macro_f_string_static_t_initialize_1(CONTROLLER_payload_type_s, 0, CONTROLLER_payload_type_s_length);
  const f_string_static_t controller_pid_s = macro_f_string_static_t_initialize_1(CONTROLLER_pid_s, 0, CONTROLLER_pid_s_length);
  const f_string_static_t controller_pid_file_s = macro_f_string_static_t_initialize_1(CONTROLLER_pid_file_s, 0, CONTROLLER_pid_file_s_length);
  const f_string_static_t controller_processor_s = macro_f_string_static_t_initialize_1(CONTROLLER_processor_s, 0, CONTROLLER_processor_s_length);
  const f_string_static_t controller_program_s = macro_f_string_static_t_initialize_1(CONTROLLER_program_s, 0, CONTROLLER_program_s_length);
  const f_string_static_t controller_readonly_s = macro_f_string_static_t_initialize_1(CONTROLLER_readonly_s, 0, CONTROLLER_readonly_s_length);
  const f_string_static_t controller_ready_s = macro_f_string_static_t_initialize_1(CONTROLLER_ready_s, 0, CONTROLLER_ready_s_length);
  const f_string_static_t controller_reboot_s = macro_f_string_static_t_initialize_1(CONTROLLER_reboot_s, 0, CONTROLLER_reboot_s_length);
  const f_string_static_t controller_reload_s = macro_f_string_static_t_initialize_1(CONTROLLER_reload_s, 0, CONTROLLER_reload_s_length);
  const f_string_static_t controller_require_s = macro_f_string_static_t_initialize_1(CONTROLLER_require_s, 0, CONTROLLER_require_s_length);
  const f_string_static_t controller_required_s = macro_f_string_static_t_initialize_1(CONTROLLER_required_s, 0, CONTROLLER_required_s_length);
  const f_string_static_t controller_rerun_s = macro_f_string_static_t_initialize_1(CONTROLLER_rerun_s, 0, CONTROLLER_rerun_s_length);
  const f_string_static_t controller_reset_s = macro_f_string_static_t_initialize_1(CONTROLLER_reset_s, 0, CONTROLLER_reset_s_length);
  const f_string_static_t controller_restart_s = macro_f_string_static_t_initialize_1(CONTROLLER_restart_s, 0, CONTROLLER_restart_s_length);
  const f_string_static_t controller_resume_s = macro_f_string_static_t_initialize_1(CONTROLLER_resume_s, 0, CONTROLLER_resume_s_length);
  const f_string_static_t controller_round_robin_s = macro_f_string_static_t_initialize_1(CONTROLLER_round_robin_s, 0, CONTROLLER_round_robin_s_length);
  const f_string_static_t controller_rss_s = macro_f_string_static_t_initialize_1(CONTROLLER_rss_s, 0, CONTROLLER_rss_s_length);
  const f_string_static_t controller_rtprio_s = macro_f_string_static_t_initialize_1(CONTROLLER_rtprio_s, 0, CONTROLLER_rtprio_s_length);
  const f_string_static_t controller_rttime_s = macro_f_string_static_t_initialize_1(CONTROLLER_rttime_s, 0, CONTROLLER_rttime_s_length);
  const f_string_static_t controller_rule_s = macro_f_string_static_t_initialize_1(CONTROLLER_rule_s, 0, CONTROLLER_rule_s_length);
  const f_string_static_t controller_rules_s = macro_f_string_static_t_initialize_1(CONTROLLER_rules_s, 0, CONTROLLER_rules_s_length);
  const f_string_static_t controller_same_s = macro_f_string_static_t_initialize_1(CONTROLLER_same_s, 0, CONTROLLER_same_s_length);
  const f_string_static_t controller_scheduler_s = macro_f_string_static_t_initialize_1(CONTROLLER_scheduler_s, 0, CONTROLLER_scheduler_s_length);
  const f_string_static_t controller_script_s = macro_f_string_static_t_initialize_1(CONTROLLER_script_s, 0, CONTROLLER_script_s_length);
  const f_string_static_t controller_service_s = macro_f_string_static_t_initialize_1(CONTROLLER_service_s, 0, CONTROLLER_service_s_length);
  const f_string_static_t controller_settings_s = macro_f_string_static_t_initialize_1(CONTROLLER_settings_s, 0, CONTROLLER_settings_s_length);
  const f_string_static_t controller_session_s = macro_f_string_static_t_initialize_1(CONTROLLER_session_s, 0, CONTROLLER_session_s_length);
  const f_string_static_t controller_session_new_s = macro_f_string_static_t_initialize_1(CONTROLLER_session_new_s, 0, CONTROLLER_session_new_s_length);
  const f_string_static_t controller_session_same_s = macro_f_string_static_t_initialize_1(CONTROLLER_session_same_s, 0, CONTROLLER_session_same_s_length);
  const f_string_static_t controller_show_s = macro_f_string_static_t_initialize_1(CONTROLLER_show_s, 0, CONTROLLER_show_s_length);
  const f_string_static_t controller_shutdown_s = macro_f_string_static_t_initialize_1(CONTROLLER_shutdown_s, 0, CONTROLLER_shutdown_s_length);
  const f_string_static_t controller_sigpending_s = macro_f_string_static_t_initialize_1(CONTROLLER_sigpending_s, 0, CONTROLLER_sigpending_s_length);
  const f_string_static_t controller_stack_s = macro_f_string_static_t_initialize_1(CONTROLLER_stack_s, 0, CONTROLLER_stack_s_length);
  const f_string_static_t controller_start_s = macro_f_string_static_t_initialize_1(CONTROLLER_start_s, 0, CONTROLLER_start_s_length);
  const f_string_static_t controller_status_s = macro_f_string_static_t_initialize_1(CONTROLLER_status_s, 0, CONTROLLER_status_s_length);
  const f_string_static_t controller_stop_s = macro_f_string_static_t_initialize_1(CONTROLLER_stop_s, 0, CONTROLLER_stop_s_length);
  const f_string_static_t controller_succeed_s = macro_f_string_static_t_initialize_1(CONTROLLER_succeed_s, 0, CONTROLLER_succeed_s_length);
  const f_string_static_t controller_success_s = macro_f_string_static_t_initialize_1(CONTROLLER_success_s, 0, CONTROLLER_success_s_length);
  const f_string_static_t controller_synchronous_s = macro_f_string_static_t_initialize_1(CONTROLLER_synchronous_s, 0, CONTROLLER_synchronous_s_length);
  const f_string_static_t controller_thaw_s = macro_f_string_static_t_initialize_1(CONTROLLER_thaw_s, 0, CONTROLLER_thaw_s_length);
  const f_string_static_t controller_timeout_s = macro_f_string_static_t_initialize_1(CONTROLLER_timeout_s, 0, CONTROLLER_timeout_s_length);
  const f_string_static_t controller_type_s = macro_f_string_static_t_initialize_1(CONTROLLER_type_s, 0, CONTROLLER_type_s_length);
  const f_string_static_t controller_use_s = macro_f_string_static_t_initialize_1(CONTROLLER_use_s, 0, CONTROLLER_use_s_length);
  const f_string_static_t controller_user_s = macro_f_string_static_t_initialize_1(CONTROLLER_user_s, 0, CONTROLLER_user_s_length);
  const f_string_static_t controller_utility_s = macro_f_string_static_t_initialize_1(CONTROLLER_utility_s, 0, CONTROLLER_utility_s_length);
  const f_string_static_t controller_value_s = macro_f_string_static_t_initialize_1(CONTROLLER_value_s, 0, CONTROLLER_value_s_length);
  const f_string_static_t controller_wait_s = macro_f_string_static_t_initialize_1(CONTROLLER_wait_s, 0, CONTROLLER_wait_s_length);
  const f_string_static_t controller_want_s = macro_f_string_static_t_initialize_1(CONTROLLER_want_s, 0, CONTROLLER_want_s_length);
  const f_string_static_t controller_wish_s = macro_f_string_static_t_initialize_1(CONTROLLER_wish_s, 0, CONTROLLER_wish_s_length);
  const f_string_static_t controller_with_s = macro_f_string_static_t_initialize_1(CONTROLLER_with_s, 0, CONTROLLER_with_s_length);
  const f_string_static_t controller_yes_s = macro_f_string_static_t_initialize_1(CONTROLLER_yes_s, 0, CONTROLLER_yes_s_length);

  const f_string_static_t controller_Entry_s = macro_f_string_static_t_initialize_1(CONTROLLER_Entry_s, 0, CONTROLLER_Entry_s_length);
  const f_string_static_t controller_Exit_s = macro_f_string_static_t_initialize_1(CONTROLLER_Exit_s, 0, CONTROLLER_Exit_s_length);
  const f_string_static_t controller_Item_s = macro_f_string_static_t_initialize_1(CONTROLLER_Item_s, 0, CONTROLLER_Item_s_length);

  const f_string_static_t controller_parameter_map_option_s = macro_f_string_static_t_initialize_1(CONTROLLER_parameter_map_option_s, 0, CONTROLLER_parameter_map_option_s_length);
  const f_string_static_t controller_parameter_map_value_s = macro_f_string_static_t_initialize_1(CONTROLLER_parameter_map_value_s, 0, CONTROLLER_parameter_map_value_s_length);
#endif // _di_controller_string_s_

#ifdef __cplusplus
} // extern "C"
#endif
