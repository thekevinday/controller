/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common interrupt type structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_common_type_interrupt_h
#define _controller_main_common_type_interrupt_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A structure for passing data to the interrupt state function.
 *
 * Properties:
 *   - is_normal: Boolean designating if this is operating in a normal state.
 *   - main:      The main program data.
 */
#ifndef _di_controller_interrupt_t_
  typedef struct {
    bool is_normal;

    controller_t *main;
  } controller_interrupt_t;

  #define controller_interrupt_t_initialize { \
    F_true, \
    0, \
  }

  #define macro_controller_interrupt_t_initialize_1(is_normal, main) { \
    is_normal, \
    main, \
  }
#endif // _di_controller_interrupt_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_type_interrupt_h
