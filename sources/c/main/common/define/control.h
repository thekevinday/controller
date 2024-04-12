/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common control defines.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_common_define_control_h
#define _controller_main_common_define_control_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Provide default control settings.
 *
 * controller_control_default_*_d:
 *   - socket_backlog:     The amount of waiting client connections to support while handling a socket connection.
 *   - socket_buffer:      The preferred max size of the buffer such that if the buffer exceeds this then it is reallocated to this size at the end of processing.
 *   - socket_buffer_max:  The max size allowed in the buffer (this value must not be set smaller than the packet headers).
 *   - socket_cache:       The preferred max size of the control cache such that if the cache exceeds this then it is reallocated to this size at the end of processing.
 *   - socket_header:      The minimum size in bytes of the packet header to read to be able to process the size information.
 *   - socket_linger:      The number of seconds to linger the connection before closing.
 *   - socket_payload_max: The max size allowed for the "payload" part of a packet and must be smaller than socket_buffer_max (this is smaller than socket_buffer_max to allow for enough room to afford a header).
 *   - socket_timeout:     The number of microseconds to wait.
 */
#ifndef _di_controller_control_defaults_d_
  #define controller_control_default_socket_backlog_d     64
  #define controller_control_default_socket_buffer_d      2048
  #define controller_control_default_socket_buffer_max_d  4294967296
  #define controller_control_default_socket_cache_d       128
  #define controller_control_default_socket_header_d      5
  #define controller_control_default_socket_linger_d      2
  #define controller_control_default_socket_payload_max_d 4294965248
  #define controller_control_default_socket_timeout_d     10000 // 0.01 seconds.
#endif // _di_controller_control_defaults_d_

/**
 * A codes repesent different flags associated with a packet.
 *
 * controller_control_packet_flag_*_d:
 *   - binary:     Designate that the packet is in binary mode (when not set then packet is in string mode).
 *   - endian_big: Designate that the packet is in big endian order (when not set then packet is in little endian order).
 */
#ifndef _di_controller_control_packet_flag_d_
  #define controller_control_packet_flag_binary_d     0x10000000
  #define controller_control_packet_flag_endian_big_d 0x01000000
#endif // _di_controller_control_packet_flag_d_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_define_control_h
