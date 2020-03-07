#ifndef _SINIX_GDT_H_
#define _SINIX_GDT_H_

#include <common/types.h>

namespace sinix {
    class GlobalDescriptorTable {
      public:
        class SegmentDescriptor {
          private:
            sinix::common::uint16_t limit_lo;
            sinix::common::uint16_t base_lo;
            sinix::common::uint8_t base_hi;
            sinix::common::uint8_t type;
            sinix::common::uint8_t flags_limit_hi;
            sinix::common::uint8_t base_vhi;
          public:
            SegmentDescriptor(sinix::common::uint32_t base, sinix::common::uint32_t limit, sinix::common::uint8_t type);
            sinix::common::uint32_t Base();
            sinix::common::uint32_t Limit();
        } __attribute__((packed));

        SegmentDescriptor nullSegmentSelector;
        SegmentDescriptor unusedSegmentSelector;
        SegmentDescriptor codeSegmentSelector;
        SegmentDescriptor dataSegmentSelector;

        GlobalDescriptorTable();
        ~GlobalDescriptorTable();

        sinix::common::uint16_t CodeSegmentSelector();
        sinix::common::uint16_t DataSegmentSelector();
    };
}

#endif
