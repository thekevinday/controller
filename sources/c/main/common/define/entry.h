/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common entry defines.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_common_define_entry_h
#define _controller_main_common_define_entry_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Controller Entry Item Rule Code defines.
 *
 * controller_entry_rule_code_*_d:
 *   - asynchronous: Process Rule asynchronously.
 *   - require:      Require Rule operations to succeed or the Entry/Exit will fail.
 *   - wait:         Wait for all existing asynchronous processes to finish before operating Rule.
 */
#ifndef _di_controller_entry_rule_code_d_
  #define controller_entry_rule_code_asynchronous_d 0x1
  #define controller_entry_rule_code_require_d      0x2
  #define controller_entry_rule_code_wait_d         0x4
#endif // _di_controller_entry_rule_code_d_

/**
 * Controller Entry Item Timeout Code defines.
 *
 * controller_entry_timeout_code_*_d:
 *   - exit:  The timeout Action represents an exit timeout.
 *   - kill:  The timeout Action represents a kill timeout.
 *   - start: The timeout Action represents a start timeout.
 *   - stop:  The timeout Action represents a stop timeout.
 */
#ifndef _di_controller_entry_timeout_code_d_
  #define controller_entry_timeout_code_exit_d  0x1
  #define controller_entry_timeout_code_kill_d  0x2
  #define controller_entry_timeout_code_start_d 0x4
  #define controller_entry_timeout_code_stop_d  0x8
#endif // _di_controller_entry_timeout_code_d_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_define_entry_h
