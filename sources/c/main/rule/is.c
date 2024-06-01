#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_main_rule_status_is_available_
  f_status_t controller_main_rule_status_is_available(const uint8_t action, const controller_rule_t rule) {

    return F_status_is_error_not(rule.status[0]) && rule.status[action] == F_known_not;
  }
#endif // _di_controller_main_rule_status_is_available_

#ifndef _di_controller_main_rule_status_is_error_
  f_status_t controller_main_rule_status_is_error(const uint8_t action, const controller_rule_t rule) {

    return F_status_is_error(rule.status[0]) || F_status_is_error(rule.status[action]);
  }
#endif // _di_controller_main_rule_status_is_error_

#ifdef __cplusplus
} // extern "C"
#endif
