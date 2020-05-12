#ifndef _SINIX_FS_MSDOSPART_H_
#define _SINIX_FS_MSDOSPART_H_

#include <common/types.h>
#include <drivers/ata.h>

namespace sinix {
  namespace fs {
    class MSDOSPartitionTable {
      struct PartitionTableEntry {
        sinix::common::uint8_t bootable;

        sinix::common::uint8_t startHead;
        sinix::common::uint8_t startSector : 6;
        sinix::common::uint16_t startCylinder : 10;
      
        sinix::common::uint8_t partitionId;
      
        sinix::common::uint8_t endHead;
        sinix::common::uint8_t endSector : 6;
        sinix::common::uint16_t endCylinder : 10;
      
        sinix::common::uint32_t start_lba;
        sinix::common::uint32_t length;
      } __attribute__((packed));
      
      struct MBR {
        sinix::common::uint8_t bootloader[440];
        sinix::common::uint32_t signature;
        sinix::common::uint16_t unused;

        PartitionTableEntry primaryPartition[4];

        sinix::common::uint16_t magicNumber;
      } __attribute__((packed));

      public:
        static void ReadPartitions(sinix::drivers::AdvancedTechnologyAttachment *hd);
    };
  }
}

#endif
