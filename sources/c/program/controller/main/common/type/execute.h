/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common execute type structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_common_type_execute_h
#define _controller_main_common_type_execute_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A structure for passing execution arguments to the execute functions.
 *
 * Properties:
 *   - parameter: All parameters sent to the program on execution.
 *   - as:        All special properties to apply, such as cpu affinity.
 */
#ifndef _di_controller_execute_set_t_
  typedef struct {
    fl_execute_parameter_t parameter;
    fl_execute_as_t as;
  } controller_execute_set_t;

  #define controller_execute_set_t_initialize_1 { \
    fl_execute_parameter_t_initialize, \
    fl_execute_as_t_initialize \
  }

  #define macro_controller_execute_set_t_initialize_1(option, wait, environment, signals, main, as) { \
    macro_fl_execute_parameter_t_initialize_1(option, wait, environment, signals, main), \
    as, \
  }
#endif // _di_controller_execute_set_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_type_execute_h
