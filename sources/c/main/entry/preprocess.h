/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the entry pre-process functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_entry_preprocess_h
#define _controller_main_entry_preprocess_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Pre-process all items for the loaded entry.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 * @param is_entry
 *   If TRUE, then this operate as an entry.
 *   If FALSE, then this operate as an exit.
 *
 * @return
 *   F_okay on success.
 *   F_recurse (with error bit) on a recursion error.
 *   F_valid_not (with error bit) on invalid entry item, entry item action, or entry item action value.
 *
 *   Errors (with error bit) from: macro_f_number_unsigneds_t_increase_by().
 *   Errors (with error bit) from: f_string_dynamic_append().
 *
 *   This will detect and report all errors, but only the first error is returned.
 *   Memory related errors return immediately.

 * @see macro_f_number_unsigneds_t_increase_by()
 * @see f_string_dynamic_append()
 */
#ifndef _di_controller_entry_preprocess_
  extern f_status_t controller_entry_preprocess(controller_t * const main, const uint8_t is_entry);
#endif // _di_controller_entry_preprocess_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_entry_preprocess_h
