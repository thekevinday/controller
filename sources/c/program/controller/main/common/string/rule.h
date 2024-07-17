/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common Rule string data.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_common_string_rule_h
#define _controller_main_common_string_rule_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Controller Rule Action strings.
 *
 * controller_rule_action_method_*_s:
 *   - extended:      Designate that this Action is represented using FSS Extended.
 *   - extended_list: Designate that this Action is represented using FSS Extended List.
 */
#ifndef _di_controller_rule_action_method_s_
  #define CONTROLLER_rule_action_method_extended_s      "FSS-0001 (Extended)"
  #define CONTROLLER_rule_action_method_extended_list_s "FSS-0003 (Extended List)"

  #define CONTROLLER_rule_action_method_extended_s_length      19
  #define CONTROLLER_rule_action_method_extended_list_s_length 24

  extern const f_string_static_t controller_rule_action_method_extended_s;
  extern const f_string_static_t controller_rule_action_method_extended_list_s;
#endif // _di_controller_rule_action_method_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_string_rule_h
