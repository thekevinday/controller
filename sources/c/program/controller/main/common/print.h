/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common print functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_common_print_h
#define _controller_main_common_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A special array of strings intended for representing funciton names.
 *
 * These are primarily used for printing errors with the function names.
 *
 * The macro macro_controller_f() is used to reference the array index by the enum name.
 *
 * macro_controller_f():
 *   - name: The name of the function.
 */
#ifndef _di_controller_f_a_
  extern const f_string_t controller_f_a[];

  #define macro_controller_f(name) controller_f_a[controller_f_##name##_e]
#endif // _di_controller_f_a_

/**
 * An enum representing specific indexes within the above array.
 *
 * This is a convenience enum used to make code slightly more readable.
 */
#ifndef _di_controller_f_e_
  enum {
    controller_f_controller_convert_group_id_e,
    controller_f_controller_convert_user_id_e,
    controller_f_controller_entry_setting_read_map_e,
    controller_f_controller_file_load_e,
    controller_f_controller_file_pid_create_e,
    controller_f_controller_lock_create_e,
    controller_f_controller_rule_copy_e,
    controller_f_controller_rule_expand_e,
    controller_f_controller_path_canonical_relative_e,
    controller_f_controller_validate_environment_name_e,
    controller_f_controller_validate_has_graph_e,
    controller_f_f_account_group_id_by_name_e,
    controller_f_f_capability_from_text_e,
    controller_f_f_console_parameter_process_e,
    controller_f_f_environment_get_all_e,
    controller_f_f_file_exists_e,
    controller_f_f_file_mode_to_mode_e,
    controller_f_f_file_name_base_e,
    controller_f_f_file_remove_e,
    controller_f_f_file_role_change_e,
    controller_f_f_file_stat_e,
    controller_f_f_file_stream_open_e,
    controller_f_f_file_stream_read_e,
    controller_f_f_fss_apply_delimit_e,
    controller_f_f_fss_count_lines_e,
    controller_f_f_memory_array_increase_e,
    controller_f_f_memory_array_increase_by_e,
    controller_f_f_memory_array_resize_e,
    controller_f_f_memory_arrays_resize_e,
    controller_f_f_path_current_e,
    controller_f_f_rip_dynamic_partial_e,
    controller_f_f_rip_dynamic_partial_nulless_e,
    controller_f_f_socket_bind_e,
    controller_f_f_socket_create_e,
    controller_f_f_string_dynamic_append_e,
    controller_f_f_string_append_assure_e,
    controller_f_f_string_dynamic_append_assure_e,
    controller_f_f_string_dynamic_append_nulless_e,
    controller_f_f_string_dynamic_partial_append_e,
    controller_f_f_string_dynamic_partial_append_nulless_e,
    controller_f_f_string_dynamic_partial_mash_nulless_e,
    controller_f_f_string_maps_append_e,
    controller_f_f_thread_create_e,
    controller_f_f_time_spec_millisecond_e,
    controller_f_fl_conversion_dynamic_partial_to_signed_detect_e,
    controller_f_fl_conversion_dynamic_partial_to_unsigned_detect_e,
    controller_f_fl_conversion_dynamic_to_unsigned_detect_e,
    controller_f_fl_environment_load_names_e,
    controller_f_fl_fss_extended_list_content_read_e,
    controller_f_fl_fss_extended_list_object_read_e,
    controller_f_fl_fss_extended_object_read_e,
    controller_f_fl_iki_read_e,
    controller_f_fll_control_group_prepare_e,
    controller_f_fll_execute_into_e,
    controller_f_fll_execute_program_e,
    controller_f_fll_fss_basic_list_read_e,
    controller_f_fll_fss_extended_read_e,
    controller_f_fll_fss_extended_content_read_e,
    controller_f_fll_fss_extended_list_content_read_e,
    controller_f_fll_program_parameter_process_context_standard_e,
    controller_f_fll_program_parameter_process_verbosity_standard_e,
  }; // enum
#endif // _di_controller_f_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_print_h
