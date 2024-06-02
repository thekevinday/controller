/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * This file is only ever included by main/main.c and should not normally be included anywhere else.
 * Anything that wants to include this should be providing the "controller" program functionality in some manner.
 */
#ifndef _controller_controller_h
#define _controller_controller_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Standard program entry point.
 *
 * @param argc
 *   The number of arguments.
 * @param argv
 *   The array of arguments.
 * @param envp
 *   The array of all environment variables on program start.
 *
 * @return
 *   0 on success.
 *   1 on error.
 */
extern int main(const int argc, const f_string_t *argv, const f_string_t *envp);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_controller_h
