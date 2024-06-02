/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common type structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_common_type_h
#define _controller_main_common_type_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The controller main program settings.
 *
 * This is passed to the program-specific main entry point to designate program settings.
 * These program settings are often processed from the program arguments (often called the command line arguments).
 *
 * Properties:
 *   - flag: Flags passed to the main function.
 *
 *   - status_signal: A status used eclusively by the threaded signal handler.
 *   - state:         The state data used when processing the FSS data.
 *
 *   - path_pid:     The name of the program.
 *   - path_setting: The long name of the program.
 */
#ifndef _di_controller_setting_t_
  typedef struct {
    uint16_t flag;

    f_status_t status_signal;
    f_state_t state;

    f_string_dynamic_t path_pid;
    f_string_dynamic_t path_setting;
  } controller_setting_t;

  #define controller_setting_t_initialize \
    { \
      controller_main_flag_none_e, \
      F_okay, \
      f_state_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
    }
#endif // _di_controller_setting_t_

/**
 * The main program data.
 *
 * The typedef for this is located in the defs.h header.
 *
 * Properties:
 *   - program: The main program data.
 *
 *   - cache:   The cache.
 *   - process: The process data.
 *   - setting: The settings data.
 *   - thread:  The thread data.
 */
#ifndef _di_controller_t_
  struct controller_t_ {
    fll_program_data_t program;

    controller_cache_t cache;
    controller_process_t process;
    controller_setting_t setting;
    controller_thread_t thread;
  };

  #define controller_t_initialize \
    { \
      fll_program_data_t_initialize, \
      controller_cache_t_initialize, \
      controller_process_t_initialize, \
      controller_setting_t_initialize, \
      controller_thread_t_initialize, \
    }
#endif // _di_controller_t_

/**
 * De-allocate main program data.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 *
 *   This does not alter main.setting.state.status.
 *
 * @see controller_cache_delete()
 * @see controller_process_delete()
 * @see controller_setting_delete()
 * @see controller_thread_delete()
 *
 * @see fll_program_data_delete()
 */
#ifndef _di_controller_delete_
  extern void controller_delete(controller_t * const main);
#endif // _di_controller_delete_

/**
 * Delete the program main setting data.
 *
 * @param setting
 *   The program main setting data.
 *
 *   Must not be NULL.
 *
 *   This does not alter setting.state.status.
 */
#ifndef _di_controller_setting_delete_
  extern void controller_setting_delete(controller_setting_t * const setting);
#endif // _di_controller_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_type_h
