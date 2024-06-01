/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common control type structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_common_type_control_h
#define _controller_main_common_type_control_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Controller control data.
 *
 * Properties:
 *   - flag:  Flags from controller_control_flag_*_e.
 *   - user:  The user ID, if specified.
 *   - group: The group ID, if specified.
 *   - mode:  The file mode, if specified.
 *
 *   - server: The server socket connection.
 *   - client: The client socket connection.
 *
 *   - cache_1: A generic buffer used for caching control related data.
 *   - cache_2: A generic buffer used for caching control related data.
 *   - cache_3: A generic buffer used for caching control related data.
 *
 *   - input:   A buffer used for receiving data from the client.
 *   - output:  A buffer used for transmitting data to the client.
 */
#ifndef _di_controller_control_t_
  typedef struct {
    uint8_t flag;
    uid_t user;
    gid_t group;
    mode_t mode;

    f_socket_t server;
    f_socket_t client;

    f_string_dynamic_t cache_1;
    f_string_dynamic_t cache_2;
    f_string_dynamic_t cache_3;

    f_string_dynamic_t input;
    f_string_dynamic_t output;
  } controller_control_t;

  #define controller_control_t_initialize { \
    0, \
    -1, \
    -1, \
    0, \
    f_socket_t_initialize, \
    f_socket_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
  }
#endif // _di_controller_control_t_

/**
 * Delete the Controller control data.
 *
 * @param control
 *   The controller control data.
 */
#ifndef _di_controller_control_delete_
  extern void controller_control_delete(controller_control_t * const control);
#endif // _di_controller_control_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_type_control_h
