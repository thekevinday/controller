/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * This program provides the base include for the init program.
 */
#ifndef _controller_init_h
#define _controller_init_h

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
 * @param cache
 *   The cache.
 *
 *   Must not be NULL.
 * @param entry
 *   The entry data.
 *
 *   Must not be NULL.
 * @param is_entry
 *   If TRUE, then this operates as an entry.
 *   If FALSE, then this operates as an exit.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_controller_init_process_entry_setup_
  extern f_status_t controller_init_process_entry_setup(controller_t * const main, controller_cache_t * const cache, controller_entry_t * const entry, const uint8_t is_entry);
#endif // _di_controller_init_process_entry_setup_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_init_h
