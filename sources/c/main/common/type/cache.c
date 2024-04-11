#include "../../controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_cache_delete_
  void controller_cache_delete(controller_cache_t * const cache) {

    if (!cache) return;

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &cache->buffer.string, &cache->buffer.used, &cache->buffer.size);
  }
#endif // _di_controller_cache_delete_

#ifdef __cplusplus
} // extern "C"
#endif
