#ifndef _SINIX_MMU_H_
#define _SINIX_MMU_H_

#include <common/types.h>

namespace sinix {
  struct MemoryChunk {
    MemoryChunk *next;
    MemoryChunk *prev;
    bool allocated;
    sinix::common::size_t size; 
  };

  class MemoryManager {
    
  };
}

#endif
