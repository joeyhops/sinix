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
    protected:
      MemoryChunk* first;
    
    public:
      static MemoryManager *activeMemoryManager;

      MemoryManager(sinix::common::size_t start, sinix::common::size_t size);
      ~MemoryManager();

      void* malloc(sinix::common::size_t size);
      void free(void* ptr);
  };
}

void* operator new(unsigned size);
void* operator new[](unsigned size);

void operator delete(void* ptr);
void operator delete[](void* ptr);

#endif
