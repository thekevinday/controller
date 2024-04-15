/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common cache type structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_common_type_cache_h
#define _controller_main_common_type_cache_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The Controller main program cache.
 *
 * buffer: A generic buffer.
 */
#ifndef _di_controller_cache_t_
  typedef struct {
    f_string_dynamic_t buffer;
  } controller_cache_t;

  #define controller_cache_t_initialize \
    { \
      f_string_dynamic_t_initialize, \
    }
#endif // _di_controller_cache_t_

/**
 * Deallocate the Controller cache.
 *
 * @param cache
 *   The cache.
 *
 *   Must not be NULL.
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_controller_cache_delete_
  extern void controller_cache_delete(controller_cache_t * const cache);
#endif // _di_controller_cache_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_type_cache_h
