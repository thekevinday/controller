/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the Rule "wait" functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_rule_wait_h
#define _controller_main_rule_wait_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Wait until all currently running Rule processes are complete.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 *
 *   This does not alter main.setting.state.status.
 * @param is_normal
 *   If TRUE, then process as if this operates during a normal operation (Entry and Control).
 *   If FALSE, then process as if this operates during an Exit operation.
 *   This is ignored when caller is not NULL.
 * @param required
 *   If TRUE, then only process required rules and if a required Rule has failed, return.
 *   If FALSE, process all waits, returning normally (required rules still result in failure).
 *
 * @return
 *   F_okay on success.
 *   F_data_not on success and nothing to do.
 *   F_require on success, but a required Rule has not been run yet.
 *
 *   F_interrupt (with error bit) on receiving a process signal, such as an interrupt signal.
 *   F_require (with error bit set) if a required process is in failed status when required is TRUE.
 */
#ifndef _di_controller_rule_wait_all_
  extern f_status_t controller_rule_wait_all(controller_t * const main, const uint8_t is_normal, const uint8_t required);
#endif // _di_controller_rule_wait_all_

/**
 * Wait until all currently running Rule processes are complete for some process type.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 *
 *   This does not alter main.setting.state.status.
 * @param type
 *   The process type to use when checking if thread is enabled.
 * @param required
 *   If TRUE, then only process required rules and if a required Rule has failed, return.
 *   If FALSE, process all waits, returning normally.
 *
 * @return
 *   Success from controller_rule_wait_all().
 *
 *   Errors (with error bit) from: controller_rule_wait_all().
 *
 * @see controller_rule_wait_all()
 */
#ifndef _di_controller_rule_wait_all_instance_type_
  extern f_status_t controller_rule_wait_all_instance_type(controller_t * const main, const uint8_t type, const uint8_t required);
#endif // _di_controller_rule_wait_all_instance_type_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_rule_wait_h
