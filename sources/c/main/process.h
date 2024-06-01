/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the main process functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_process_h
#define _controller_main_process_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Execute main program process.
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
 */
#ifndef controller_main_process
  extern void controller_main_process(controller_main_t * const main, controller_program_t * const program);
#endif // controller_main_process

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_process_h
