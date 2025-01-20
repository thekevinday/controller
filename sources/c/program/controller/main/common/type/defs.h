/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common typedefs for addressing specific cases of circular definitions.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_common_type_defs_h
#define _controller_main_common_type_defs_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Pre-define the main type so it can be used in child classes.
 */
#ifndef _di_fake_main_t_typedef_
  typedef struct controller_t_ controller_t;
#endif // _di_fake_main_t_typedef_

/**
 * The controller instance typedef.
 */
 #ifndef _di_controller_instance_t_typedef_
  typedef struct controller_instance_t_ controller_instance_t;
#endif // _di_controller_instance_t_typedef_

/**
 * The controller instances typedef.
 */
 #ifndef _di_controller_instances_t_typedef_
  typedef struct controller_instances_t_ controller_instances_t;
#endif // _di_controller_instances_t_typedef_

/**
 * The controller program typedef.
 */
#ifndef _di_controller_process_t_typedef_
  typedef struct controller_process_t_ controller_process_t;
#endif // _di_controller_process_t_typedef_

/**
 * The controller thread typedef.
 */
 #ifndef _di_controller_thread_t_typedef_
  typedef struct controller_thread_t_ controller_thread_t;
#endif // _di_controller_thread_t_typedef_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_type_defs_h
