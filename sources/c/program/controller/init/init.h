/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * This program provides the base include for the init program.
 */
#ifndef _controller_init_init_h
#define _controller_init_init_h

// Controller includes.
#include <program/controller/main/controller.h>
#include <program/controller/init/string.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The init program implementation of the process_entry_setup() callback.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 * @param entry
 *   The Entry data.
 *
 *   Must not be NULL.
 * @param is_entry
 *   If TRUE, then this operates as an Entry.
 *   If FALSE, then this operates as an Exit.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_controller_init_process_entry_setup_
  extern f_status_t controller_init_process_entry_setup(controller_t * const main, controller_entry_t * const entry);
#endif // _di_controller_init_process_entry_setup_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_init_init_h
