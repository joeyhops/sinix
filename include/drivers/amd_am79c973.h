#ifndef _SINIX_DRIVERS_AMD_AM79C973_H_
#define _SINIX_DRIVERS_AMD_AM79C973_H_

#include <common/types.h>
#include <drivers/driver.h>
#include <hwcom/pci.h>
#include <hwcom/interrupts.h>
#include <hwcom/port.h>

namespace sinix {
  namespace drivers {
    class amd_am79c973 : public Driver, public sinix::hwcom::InterruptHandler
    {
      struct InitializationBlock {
        sinix::common::uint16_t mode;
        unsigned reserved1 : 4;
        unsigned numSendBuffers : 4;
        unsigned reserved2 : 4;
        unsigned numRecvBuffers : 4;
        sinix::common::uint64_t physicalAddress : 48;
        sinix::common::uint16_t reserved3;
        sinix::common::uint64_t logicalAddress;
        sinix::common::uint32_t recvBufferDescrAddress;
        sinix::common::uint32_t sendBufferDescrAddress;
      } __attribute__((packed));

      struct BufferDescriptor {
        sinix::common::uint32_t address;
        sinix::common::uint32_t flags;
        sinix::common::uint32_t flags2;
        sinix::common::uint32_t avail;
      } __attribute__((packed));

      sinix::hwcom::Port16Bit MACAddressPort;
      sinix::hwcom::Port16Bit MACAddress2Port;
      sinix::hwcom::Port16Bit MACAddress4Port;
      sinix::hwcom::Port16Bit registerDataPort;
      sinix::hwcom::Port16Bit registerAddressPort;
      sinix::hwcom::Port16Bit resetPort;
      sinix::hwcom::Port16Bit busControlRegisterDataPort;

      InitializationBlock initBlock;

      BufferDescriptor* sendBufferDescr;
      sinix::common::uint8_t sendBufferDescMemory[2048+15];
      sinix::common::uint8_t sendBuffers[2*1024+15][8];
      sinix::common::uint8_t currentSendBuffer;

      BufferDescriptor* recvBufferDescr;
      sinix::common::uint8_t recvBufferDescMemory[2048+15];
      sinix::common::uint8_t recvBuffers[2*1024+15][8];
      sinix::common::uint8_t currentRecvBuffer;
      
      public:
        amd_am79c973(sinix::hwcom::PeripheralComponentInterconnectDeviceDescriptor *dev, sinix::hwcom::InterruptManager* interrupts);
        ~amd_am79c973();

        void Activate();
        int Reset();
        sinix::common::uint32_t HandleInterrupt(sinix::common::uint32_t esp);
    
        void Send(sinix::common::uint8_t* buffer, int size);
        void Recieve();
    };
  }
}

#endif
