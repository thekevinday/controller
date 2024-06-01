/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * This program provides an controller base project.
 *
 * This program does nothing but can be used as a starting point for new program projects.
 */
#ifndef _controller_controller_h
#define _controller_controller_h

// Controller includes.
#include <program/controller/main/controller.h>
#include <program/controller/controller/string.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Execute main program.
 *
 * If main.signal is non-zero, then this blocks and handles the following signals:
 *   - F_signal_abort
 *   - F_signal_broken_pipe
 *   - F_signal_hangup
 *   - F_signal_interrupt
 *   - F_signal_quit
 *   - F_signal_termination
 *
 * @param main
 *   The main program data and settings.
 *
 *   Must not be NULL.
 *
 *   This alters main.setting.state.status:
 *     F_okay on success.
 *     F_true on success when performing verification and verify passed.
 *     F_false on success when performing verification and verify failed.
 *     F_interrupt on (exit) signal received.
 *
 *     F_parameter (with error bit) if main is NULL or setting is NULL.
 * @param program
 *   A pointer to the current program settings.
 *
 *   Must not be NULL.
 *
 * @see controller_main_process()
 */
#ifndef _di_controller_controller_main_
  extern void controller_controller_main(controller_main_t * const main, controller_program_t * const program);
#endif // _di_controller_controller_main_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_controller_h
