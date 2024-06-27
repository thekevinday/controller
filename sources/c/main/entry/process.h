/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the entry process functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_entry_process_h
#define _controller_main_entry_process_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Process (execute) all Items for the loaded Entry or Exit.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 * @param failsafe
 *   If TRUE, operate in failsafe mode (starts at designated failsafe Item).
 *   If FALSE, operate in normal mode (starts at "main" Item).
 * @param is_entry
 *   If TRUE, then this operates as an entry.
 *   If FALSE, then this operates as an exit.
 *
 * @return
 *   F_okay on success.
 *   F_execute on success and program exiting (scripts may result in this) or when execute would have been executed but is instead simulated.
 *
 *   F_require (with error bit) if a required Item failed.
 *   F_critical (with error bit) on any critical error.
 *   F_execute (with error bit) if the "execute" Item Action failed.
 *
 *   Errors (with error bit) from: f_string_dynamic_append_nulless().
 *
 *   Errors (with error bit) from: macro_f_number_unsigneds_t_increase_by().
 *   Errors (with error bit) from: controller_perform_ready().
 *
 * @see f_string_dynamic_append_nulless()
 *
 * @see macro_f_number_unsigneds_t_increase_by()
 * @see controller_perform_ready()
 */
#ifndef _di_controller_entry_process_
  extern f_status_t controller_entry_process(controller_t * const main, const uint8_t failsafe, const uint8_t is_entry);
#endif // _di_controller_entry_process_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_entry_process_h
