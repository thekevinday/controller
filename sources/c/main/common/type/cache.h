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
 * Action related cache.
 *
 * line_action: The line in some file representing an Action.
 * line_item:   The line in some file representing an Item.
 *
 * name_action: A NULL terminated name of some Action.
 * name_file:   A NULL terminated name of some File.
 * name_item:   A NULL terminated name of some Item.
 *
 * generic: A NULL terminated string for general use.
 */
#ifndef _di_controller_cache_action_t_
  typedef struct {
    f_number_unsigned_t line_action;
    f_number_unsigned_t line_item;

    f_string_dynamic_t name_action;
    f_string_dynamic_t name_file;
    f_string_dynamic_t name_item;

    f_string_dynamic_t generic;
  } controller_cache_action_t;

  #define controller_cache_action_t_initialize { \
    0, \
    0, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
  }

  #define macro_controller_cache_action_t_clear(cache) \
    cache.line_action = 0; \
    cache.line_item = 0; \
    macro_f_string_dynamic_t_clear(cache.name_action) \
    macro_f_string_dynamic_t_clear(cache.name_file) \
    macro_f_string_dynamic_t_clear(cache.name_item) \
    macro_f_string_dynamic_t_clear(cache.generic)
#endif // _di_controller_cache_action_t_

/**
 * A cache intended for re-using memory while loading and processing rules whenever possible.
 *
 * timestamp: The timestamp.
 *
 * range_action: The Range for some Action.
 *
 * ats:   Locations.
 * stack: Locations within a items history used as a history stack for circular recursion prevention.
 *
 * comments: Comments associated with a buffer string.
 * delimits: Delimits associated with a buffer string.
 *
 * content_action:  The specific Content for some Action.
 * content_actions: Content for some Action.
 * content_items:   Content for some Item.
 * object_actions:  Objects for some Action.
 * object_items:    Objects for some Item.
 *
 * buffer:      A generic buffer.
 * buffer_file: A generic file related buffer.
 * buffer_item: A generic item related buffer.
 * buffer_path: A generic path related buffer.
 *
 * expanded: An array of expanded strings, generally used by the execute functions.
 *
 * action: A cache for some Action, often used by error printing for reporting where an error happened.
 */
#ifndef _di_controller_cache_t_
  typedef struct {
    f_time_simple_t timestamp;

    f_range_t range_action;

    f_number_unsigneds_t ats;
    f_number_unsigneds_t stack;

    f_ranges_t comments;
    f_number_unsigneds_t delimits;

    f_ranges_t content_action;
    f_rangess_t content_actions;
    f_rangess_t content_items;
    f_ranges_t object_actions;
    f_ranges_t object_items;

    f_string_dynamic_t buffer;
    f_string_dynamic_t buffer_file;
    f_string_dynamic_t buffer_item;
    f_string_dynamic_t buffer_path;

    f_string_dynamics_t expanded;

    controller_cache_action_t action;
  } controller_cache_t;

  #define controller_cache_t_initialize \
    { \
      f_time_simple_t_initialize, \
      f_range_t_initialize, \
      f_number_unsigneds_t_initialize, \
      f_number_unsigneds_t_initialize, \
      f_ranges_t_initialize, \
      f_number_unsigneds_t_initialize, \
      f_ranges_t_initialize, \
      f_rangess_t_initialize, \
      f_rangess_t_initialize, \
      f_ranges_t_initialize, \
      f_ranges_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamics_t_initialize, \
      controller_cache_action_t_initialize, \
    }
#endif // _di_controller_cache_t_

/**
 * Deallocate the Controller cache.
 *
 * @param cache
 *   The cache.
 *   Must not be NULL.
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_controller_cache_delete_
  extern void controller_cache_delete(controller_cache_t * const cache);
#endif // _di_controller_cache_delete_

/**
 * Deallocate the Controller action cache.
 *
 * @param cache
 *   The action cache.
 *   Must not be NULL.
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_controller_cache_action_delete_
  extern void controller_cache_action_delete(controller_cache_action_t * const cache);
#endif // _di_controller_cache_action_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_type_cache_h
