#include "../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_program_version_s_
  const f_string_static_t controller_program_version_s = macro_f_string_static_t_initialize_1(CONTROLLER_program_version_s, 0, CONTROLLER_program_version_s_length);
#endif // _di_controller_program_version_s_

#ifndef _di_controller_program_name_s_
  const f_string_static_t controller_program_name_s = macro_f_string_static_t_initialize_1(CONTROLLER_program_name_s, 0, CONTROLLER_program_name_s_length);
  const f_string_static_t controller_program_name_long_s = macro_f_string_static_t_initialize_1(CONTROLLER_program_name_long_s, 0, CONTROLLER_program_name_long_s_length);
#endif // _di_controller_program_name_s_

#ifndef _di_controller_parameter_s_
  const f_string_static_t controller_short_controller_s = macro_f_string_static_t_initialize_1(CONTROLLER_short_controller_s, 0, CONTROLLER_short_controller_s_length);

  const f_string_static_t controller_long_controller_s = macro_f_string_static_t_initialize_1(CONTROLLER_long_controller_s, 0, CONTROLLER_long_controller_s_length);
#endif // _di_controller_parameter_s_

#ifdef __cplusplus
} // extern "C"
#endif
