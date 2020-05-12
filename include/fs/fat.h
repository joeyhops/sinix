#ifndef _SINIX_FS_FAT_H_
#define _SINIX_FS_FAT_H_

#include <common/types.h>
#include <drivers/ata.h>

namespace sinix {
  namespace fs {
    struct BiosParameterBlock32 {
      sinix::common::uint8_t jump[3];
      sinix::common::uint8_t softName[8];
      sinix::common::uint16_t bytesPerSector;
      sinix::common::uint8_t sectorsPerCluster;
      sinix::common::uint16_t reservedSectors;
      sinix::common::uint8_t fatCopies;
      sinix::common::uint16_t rootDirEntries;
      sinix::common::uint16_t totalSectors;
      sinix::common::uint8_t mediaType;
      sinix::common::uint16_t fatSectorCount;
      sinix::common::uint16_t sectorsPerTrack;
      sinix::common::uint16_t headCount;
      sinix::common::uint32_t hiddenSectors;
      sinix::common::uint32_t totalSectorCount;

      sinix::common::uint32_t tableSize;
      sinix::common::uint16_t extFlags;
      sinix::common::uint16_t fatVersion;
      sinix::common::uint32_t rootCluster;
      sinix::common::uint16_t fatInfo;
      sinix::common::uint16_t backupSector;
      sinix::common::uint8_t reserved0[12];
      sinix::common::uint8_t driveNumber;
      sinix::common::uint8_t reserved;
      sinix::common::uint8_t bootSignature;
      sinix::common::uint32_t volumeId;
      sinix::common::uint8_t volumeLabel[11];
      sinix::common::uint8_t fatTypeLabel[8];
    } __attribute__((packed));

    struct DirectoryEntryFat32 {
      sinix::common::uint8_t name[8];
      sinix::common::uint8_t ext[3];
      sinix::common::uint8_t attributes;
      sinix::common::uint8_t reserved;
      sinix::common::uint8_t cTimeTenth;
      sinix::common::uint16_t cTime;
      sinix::common::uint16_t cDate;
      sinix::common::uint16_t aTime;

      sinix::common::uint16_t firstCluterHi;
      
      sinix::common::uint16_t wTime;
      sinix::common::uint16_t wDate;

      sinix::common::uint16_t firstClusterLow;
      sinix::common::uint32_t size;
    } __attribute__((packed));

    void ReadBiosBlock(sinix::drivers::AdvancedTechnologyAttachment *hd, sinix::common::uint32_t partitionOffset);
  }
}

#endif
