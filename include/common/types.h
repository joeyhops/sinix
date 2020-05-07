#ifndef _SINIX_TYPE_H_
#define _SINIX_TYPE_H_

namespace sinix {
  namespace common {
    typedef char int8_t;
    typedef unsigned char uint8_t;

    typedef short int16_t;
    typedef unsigned short uint16_t;

    typedef int int32_t;
    typedef unsigned int uint32_t;

    typedef long long int int64_t;
    typedef unsigned long long int uint64_t;
  
    typedef const char* string;
    typedef uint32_t size_t; // 32-Bit Memory Addressing
  }
}

#endif
