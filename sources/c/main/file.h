/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides file functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_file_h
#define _controller_file_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Load a file from the controller settings directory.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 * @param cache
 *   The following within the cache is updated:
 *   - name_file: The partial path of the file is inserted.
 *   - buffer_file: The contents of the file is inserted.
 *   - timestamp: This is updated to reflect the last changed timestamp.
 *
 *   Must not be NULL.
 *
 * @param required
 *   If TRUE, the file is required to exist and will throw an error if not found.
 *   If FALSE, the file is not required to exist and will return without error if not found.
 * @param path_prefix
 *   The path prefix, such as 'entries' from '/etc/controller/entries/default.entry'.
 * @param path_name
 *   The path name, such as 'default' from '/etc/controller/entries/default.entry'.
 * @param path_suffix
 *   The path suffix, such as 'entry' from '/etc/controller/entries/default.entry'.
 *
 * @return
 *   F_okay on success.
 *   F_file_found_not if required is FALSE and the file is not found.
 *
 *   Errors (with error bit) from: f_file_stat().
 *   Errors (with error bit) from: f_file_stream_open().
 *   Errors (with error bit) from: f_file_stream_read().
 *   Errors (with error bit) from: f_string_append().
 *
 * @see f_file_stat()
 * @see f_file_stream_open()
 * @see f_file_stream_read()
 * @see f_string_append()
 */
#ifndef _di_controller_file_load_
  extern f_status_t controller_file_load(controller_t * const main, controller_cache_t * const cache, const bool required, const f_string_static_t path_prefix, const f_string_static_t path_name, const f_string_static_t path_suffix);
#endif // _di_controller_file_load_

/**
 * Create the pid file, if possible.
 *
 * @param pid
 *   The PID (process id).
 * @param path
 *   The file path to the pid file to create.
 *
 * @return
 *   F_okay on success.
 *   F_access_denied if pid file is not created due to access denied errors.
 *   F_directory_not if pid file is not created due to a parent directory is unavailable or invalid.
 *
 *   Errors (with error bit) from: f_directory_exists().
 *   Errors (with error bit) from: f_file_name_directory().
 *   Errors (with error bit) from: f_file_stream_open().
 *
 * @see f_directory_exists()
 * @see f_file_name_directory()
 * @see f_file_stream_open()
 */
#ifndef _di_controller_file_pid_create_
  f_status_t controller_file_pid_create(const pid_t pid, const f_string_static_t path);
#endif // _di_controller_file_pid_create_

/**
 * Delete the pid file, if exists and is valid.
 *
 * This is meant to be called on exit and avoids checking status codes, returning void.
 *
 * @param pid
 *   The PID (process id).
 * @param path
 *   The file path to the pid file to create.
 *
 * @return
 *   F_okay on success.
 *
 *   F_number_not (with error bit) if the number from the pid file doesn't match the expected pid.
 *
 *   Errors (with error bit) from: f_file_stream_close().
 *   Errors (with error bit) from: f_file_stream_open().
 *   Errors (with error bit) from: f_file_stream_read().
 *   Errors (with error bit) from: fl_conversion_dynamic_partial_to_unsigned()
 */
#ifndef _di_controller_file_pid_delete_
  f_status_t controller_file_pid_delete(const pid_t pid, const f_string_static_t path);
#endif // _di_controller_file_pid_delete_

/**
 * Read the PID from a PID file.
 *
 * @param path
 *   The file path to the pid file to create.
 * @param pid
 *   The PID to be read.
 *
 * @return
 *   F_okay on success.
 *
 *   Errors (with error bit) from: f_file_stream_close().
 *   Errors (with error bit) from: f_file_stream_open().
 *   Errors (with error bit) from: f_file_stream_read().
 *   Errors (with error bit) from: fl_conversion_dynamic_partial_to_unsigned()
 */
#ifndef _di_controller_file_pid_read_
  f_status_t controller_file_pid_read(const f_string_static_t path, pid_t * const pid);
#endif // _di_controller_file_pid_read_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_file_h
