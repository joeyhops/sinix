#ifndef _SINIX_DRIVERS_ATA_H_
#define _SINIX_DRIVERS_ATA_H_

#include <common/types.h>
#include <hwcom/port.h>

namespace sinix {
  namespace drivers {
    class AdvancedTechnologyAttachment {
      protected:
        sinix::hwcom::Port16Bit dataPort;
        sinix::hwcom::Port8Bit errorPort;
        sinix::hwcom::Port8Bit sectorCountPort;
        sinix::hwcom::Port8Bit lbaLowPort;
        sinix::hwcom::Port8Bit lbaMidPort;
        sinix::hwcom::Port8Bit lbaHiPort;
        sinix::hwcom::Port8Bit devicePort;
        sinix::hwcom::Port8Bit commandPort;
        sinix::hwcom::Port8Bit controlPort;

        bool master;
        sinix::common::uint16_t bytesPerSector;

      public:
        AdvancedTechnologyAttachment(sinix::common::uint16_t portBase, bool master);
        ~AdvancedTechnologyAttachment();

        void Identify();
        void Read28(sinix::common::uint32_t sector, sinix::common::uint8_t* data, int count);
        void Write28(sinix::common::uint32_t sector, sinix::common::uint8_t* data, int count);
        void Flush();
    };
  }
}

#endif
