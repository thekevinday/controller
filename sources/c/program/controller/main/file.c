#include "controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_file_load_
  f_status_t controller_file_load(controller_t * const main, const uint8_t required, const f_string_static_t path_prefix, const f_string_static_t path_name, const f_string_static_t path_suffix) {

    if (!main) return F_status_set_error(F_parameter);

    f_file_t file = f_file_t_initialize;

    main->thread.cache.action.name_file.used = 0;
    main->thread.cache.buffer_file.used = 0;
    main->thread.cache.timestamp.seconds = 0;
    main->thread.cache.timestamp.seconds_nano = 0;

    f_status_t status = f_string_dynamic_append_nulless(path_prefix, &main->thread.cache.action.name_file);

    if (F_status_is_error_not(status)) {
      status = f_string_dynamic_append_nulless(f_path_separator_s, &main->thread.cache.action.name_file);
    }

    if (F_status_is_error_not(status)) {
      status = f_string_dynamic_append_nulless(path_name, &main->thread.cache.action.name_file);
    }

    if (F_status_is_error_not(status)) {
      status = f_string_dynamic_append_nulless(f_path_extension_separator_s, &main->thread.cache.action.name_file);
    }

    if (F_status_is_error_not(status)) {
      status = f_string_dynamic_append_nulless(path_suffix, &main->thread.cache.action.name_file);
    }

    if (F_status_is_error(status)) {
      controller_print_error_status(&main->program.error, macro_controller_f(f_string_dynamic_append_nulless), F_status_set_fine(status));

      return status;
    }

    f_string_static_t path = f_string_static_t_initialize;

    if (main->process.path_setting.used) {
      path.used = main->process.path_setting.used + main->thread.cache.action.name_file.used;

      if (main->process.path_setting.string[main->process.path_setting.used - 1] != f_path_separator_s.string[0]) {
        path.used += f_path_separator_s.used;
      }
    }
    else {
      path.used = main->thread.cache.action.name_file.used;
    }

    f_char_t path_string[path.used + 1];
    path.string = path_string;

    if (main->process.path_setting.used) {
      memcpy(path_string, main->process.path_setting.string, sizeof(f_char_t) * main->process.path_setting.used);

      if (main->process.path_setting.string[main->process.path_setting.used - 1] == f_path_separator_s.string[0]) {
        memcpy(path_string + main->process.path_setting.used, main->thread.cache.action.name_file.string, sizeof(f_char_t) * main->thread.cache.action.name_file.used);
      }
      else {
        memcpy(path_string + main->process.path_setting.used + F_path_separator_s_length, main->thread.cache.action.name_file.string, sizeof(f_char_t) * main->thread.cache.action.name_file.used);

        path_string[main->process.path_setting.used] = f_path_separator_s.string[0];
      }
    }
    else {
      memcpy(path_string, main->thread.cache.action.name_file.string, sizeof(f_char_t) * main->thread.cache.action.name_file.used);
    }

    path_string[path.used] = 0;

    status = f_file_stream_open(path, f_string_empty_s, &file);

    if (F_status_is_error(status)) {
      if (!required && F_status_set_fine(status) == F_file_found_not) {
        f_file_stream_flush(file);
        f_file_stream_close(&file);

        return F_file_found_not;
      }

      if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
        controller_print_error_file_status(&main->program.error, macro_controller_f(f_file_stream_open), path, f_file_operation_open_s, fll_error_file_type_file_e, F_status_set_fine(status));
      }
    }
    else {
      status = f_file_stream_read(file, &main->thread.cache.buffer_file);

      if (F_status_is_error(status)) {
        controller_print_error_file_status(&main->program.error, macro_controller_f(f_file_stream_read), path, f_file_operation_read_s, fll_error_file_type_file_e, F_status_set_fine(status));
      }
    }

    f_file_stream_flush(file);
    f_file_stream_close(&file);

    if (F_status_is_error_not(status)) {
      struct stat stat_file;

      status = f_file_stat(path, F_true, &stat_file);

      if (F_status_is_error(status)) {
        controller_print_error_file_status(&main->program.error, macro_controller_f(f_file_stat), path, f_file_operation_stat_s, fll_error_file_type_file_e, F_status_set_fine(status));
      }
      else {
        main->thread.cache.timestamp.seconds = stat_file.st_ctim.tv_sec;
        main->thread.cache.timestamp.seconds_nano = stat_file.st_ctim.tv_nsec;
      }
    }

    return F_status_is_error(status) ? status : F_okay;
  }
#endif // _di_controller_file_load_

#ifndef _di_controller_file_pid_create_
  f_status_t controller_file_pid_create(const pid_t pid, const f_string_static_t path) {

    f_status_t status = F_okay;

    // The file exists, do not attempt to overwrite.
    if (f_file_exists(path, F_true) == F_true) return F_status_set_error(F_file_found);

    {
      f_string_dynamic_t path_directory = f_string_dynamic_t_initialize;

      status = f_file_name_directory(path, &path_directory);

      if (F_status_is_error_not(status)) {
        status = f_directory_exists(path_directory);
      }

      f_memory_array_resize(0, sizeof(f_char_t), (void **) &path_directory.string, &path_directory.used, &path_directory.size);
      if (F_status_is_error(status)) return status;

      // The directory does not exist so do not bother attempting to create a pid file.
      if (status == F_false) return F_status_set_error(F_directory_not);
    }

    f_file_t file = f_file_t_initialize;

    file.flag = F_file_flag_write_only_d;

    status = f_file_stream_open(path, f_file_open_mode_read_truncate_s, &file);
    if (F_status_is_error(status)) return status;

    fll_print_format("%i%r", file, pid, f_string_eol_s);

    f_file_stream_flush(file);
    f_file_stream_close(&file);

    return F_status_is_error(status) ? status : F_okay;
  }
#endif // _di_controller_file_pid_create_

#ifndef _di_controller_file_pid_delete_
  f_status_t controller_file_pid_delete(const pid_t pid, const f_string_static_t path) {

    // Only delete if the file exists and there is no error while checking.
    if (f_file_exists(path, F_true) != F_true) return F_okay;

    f_status_t status = F_okay;
    f_file_t pid_file = f_file_t_initialize;

    status = f_file_stream_open(path, f_file_open_mode_read_s, &pid_file);
    if (F_status_is_error(status)) return status;

    f_string_dynamic_t pid_buffer = f_string_dynamic_t_initialize;

    status = f_file_stream_read(pid_file, &pid_buffer);

    if (F_status_is_error_not(status)) {
      status = f_file_stream_flush(pid_file);
    }

    if (F_status_is_error_not(status)) {
      status = f_file_stream_close(&pid_file);
    }

    if (F_status_is_error_not(status)) {
      f_number_unsigned_t number = 0;
      f_range_t range = macro_f_range_t_initialize_2(pid_buffer.used);

      for (; range.start < pid_buffer.used; ++range.start) {
        if (!isspace(pid_buffer.string[range.start])) break;
      } // for

      for (; range.stop > 0; --range.stop) {
        if (!isspace(pid_buffer.string[range.stop])) break;
      } // for

      status = fl_conversion_dynamic_partial_to_unsigned(fl_conversion_data_base_10_c, pid_buffer, range, &number);

      if (F_status_is_error_not(status) && number == pid) {
        status = f_file_remove(path);
      }
      else {
        status = F_status_set_error(F_number_not);
      }
    }

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &pid_buffer.string, &pid_buffer.used, &pid_buffer.size);

    return status;
  }
#endif // _di_controller_file_pid_delete_

#ifndef _di_controller_file_pid_read_
  f_status_t controller_file_pid_read(const f_string_static_t path, pid_t * const pid) {

    *pid = 0;

    f_status_t status = f_file_exists(path, F_true);
    if (F_status_is_error(status)) return status;
    if (status != F_true) return F_data_not;

    f_file_t pid_file = f_file_t_initialize;

    status = f_file_stream_open(path, f_file_open_mode_read_s, &pid_file);
    if (F_status_is_error(status)) return status;

    f_string_dynamic_t pid_buffer = f_string_dynamic_t_initialize;

    status = f_file_stream_read(pid_file, &pid_buffer);

    if (F_status_is_error_not(status)) {
      status = f_file_stream_flush(pid_file);
    }

    if (F_status_is_error_not(status)) {
      status = f_file_stream_close(&pid_file);
    }

    if (F_status_is_error_not(status)) {
      f_number_unsigned_t number = 0;
      f_range_t range = macro_f_range_t_initialize_2(pid_buffer.used);

      for (; range.start < pid_buffer.used; ++range.start) {
        if (!isspace(pid_buffer.string[range.start])) break;
      } // for

      for (; range.stop > 0; --range.stop) {
        if (!isspace(pid_buffer.string[range.stop])) break;
      } // for

      status = fl_conversion_dynamic_partial_to_unsigned(fl_conversion_data_base_10_c, pid_buffer, range, &number);

      if (F_status_is_error_not(status)) {
        *pid = (pid_t) number;
      }
    }

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &pid_buffer.string, &pid_buffer.used, &pid_buffer.size);

    return status;
  }
#endif // _di_controller_file_pid_read_

#ifdef __cplusplus
} // extern "C"
#endif
