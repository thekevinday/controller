/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides validate functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_validate_h
#define _controller_validate_h

/**
 * Validate that the given string is a valid environment variable name.
 *
 * A valid environment variable name must begin with an alpha-character or an underscore.
 * Every character after that may be alphanumeric or underscore.
 * All other characters, including Unicode characters, are invalid.
 *
 * @param name
 *   The string to validate.
 *
 * @return
 *   F_true on valid.
 *   F_false on invalid.
 *   F_okay if there is no string to validate (used = 0).
 *
 *   Errors (with error bit) from: f_utf_is_alphabetic().
 *   Errors (with error bit) from: f_utf_is_alphabetic_digit().
 *
 * @see f_utf_is_alphabetic()
 * @see f_utf_is_alphabetic_digit()
 */
#ifndef _di_controller_validate_define_name_
  extern f_status_t controller_validate_environment_name(const f_string_static_t name);
#endif // _di_controller_validate_define_name_

/**
 * Validate that the given string has at least one graph character.
 *
 * @param name
 *   The string to validate.
 *
 * @return
 *   F_true on valid.
 *   F_false on invalid.
 *   F_okay if there is no string to validate (used = 0).
 *
 *   Errors (with error bit) from: f_utf_is_graph().
 *
 * @see f_utf_is_graph()
 */
#ifndef _di_controller_validate_has_graph_
  extern f_status_t controller_validate_has_graph(const f_string_static_t name);
#endif // _di_controller_validate_has_graph_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_validate_h
