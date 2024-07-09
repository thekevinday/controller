/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common Rule defines.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_common_define_rule_h
#define _controller_main_common_define_rule_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Controller Rule "has" defines.
 *
 * Bitwise codes representing properties on controller_rule_t that have been found in the Rule file.
 *
 * controller_rule_has_*_d:
 *   - cgroup:    Has type representing a control group.
 *   - group:     Has type representing a group.
 *   - nice:      Has type representing a nice.
 *   - scheduler: Has type representing a scheduler.
 *   - user:      Has type representing a user.
 */
#ifndef _di_controller_rule_has_d_
  #define controller_rule_has_cgroup_d      0x1
  #define controller_rule_has_environment_d 0x2
  #define controller_rule_has_group_d       0x4
  #define controller_rule_has_nice_d        0x8
  #define controller_rule_has_scheduler_d   0x10
  #define controller_rule_has_user_d        0x20
#endif // _di_controller_rule_has_d_

/**
 * Controller Rule "rerun" "is" defines.
 *
 * controller_rule_rerun_is_*_d:
 *   - failure:       The success re-run is enabled.
 *   - failure_reset: Reset success counter when failure is returned.
 *   - success:       The success re-run is enabled.
 *   - success_reset: Reset failure counter when success is returned.
 */
#ifndef _di_controller_rule_rerun_d_
  #define controller_rule_rerun_is_failure_d       0x1
  #define controller_rule_rerun_is_failure_reset_d 0x2
  #define controller_rule_rerun_is_success_d       0x4
  #define controller_rule_rerun_is_success_reset_d 0x8
#endif // _di_controller_rule_rerun_d_

/**
 * Controller Rule timeout code defines.
 *
 * Designate codes for timeout settings to be used during the loading of the Rule timeout settings.
 *
 * controller_rule_timeout_code_*_d:
 *   - kill:  Forcibly stop a Rule.
 *   - start: Start a Rule.
 *   - stop:  Stop a Rule.
 */
#ifndef _di_controller_rule_timeout_code_d_
  #define controller_rule_timeout_code_kill_d  1
  #define controller_rule_timeout_code_start_d 2
  #define controller_rule_timeout_code_stop_d  3
#endif // _di_controller_rule_timeout_code_d_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_define_rule_h
