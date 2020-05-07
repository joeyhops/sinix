#ifndef _SINIX_HWCOM_PCI_H_
#define _SINIX_HWCOM_PCI_H_

#include <hwcom/port.h>
#include <drivers/driver.h>
#include <common/types.h>
#include <hwcom/interrupts.h>

namespace sinix {
  namespace hwcom {
    enum BaseAddressRegisterType {
      MemoryMapping = 0,
      InputOutput = 1
    };

    class BaseAddressRegister {
      public:
        bool prefetchable;
        sinix::common::uint8_t* address;
        sinix::common::uint32_t size;
        BaseAddressRegisterType type;
    };

    class PeripheralComponentInterconnectDeviceDescriptor {
      public:
        sinix::common::uint32_t portBase;
        sinix::common::uint32_t interrupt;

        sinix::common::uint16_t bus;
        sinix::common::uint16_t device;
        sinix::common::uint16_t function;
     
        sinix::common::uint16_t vendor_id;
        sinix::common::uint16_t device_id;
        
        sinix::common::uint8_t class_id; 
        sinix::common::uint8_t subclass_id;
        sinix::common::uint8_t interface_id;
        
        sinix::common::uint16_t revision;

        PeripheralComponentInterconnectDeviceDescriptor();
        ~PeripheralComponentInterconnectDeviceDescriptor();
    };

    class PeripheralComponentInterconnectController {
      
      Port32Bit dataPort;
      Port32Bit commandPort;

      public:
        PeripheralComponentInterconnectController();
        ~PeripheralComponentInterconnectController();

        sinix::common::uint32_t Read(sinix::common::uint16_t bus, sinix::common::uint16_t device, sinix::common::uint16_t function, sinix::common::uint32_t registerOffset); 
        void Write(sinix::common::uint16_t bus, sinix::common::uint16_t device, sinix::common::uint16_t function, sinix::common::uint32_t registerOffset, sinix::common::uint32_t value);
        bool DeviceHasFunctions(sinix::common::uint16_t bus, sinix::common::uint16_t device);

        void SelectDrivers(sinix::drivers::DriverManager* driverManager, sinix::hwcom::InterruptManager* interrupts);
        sinix::drivers::Driver* GetDriver(PeripheralComponentInterconnectDeviceDescriptor dev, sinix::hwcom::InterruptManager* interrupts);
        PeripheralComponentInterconnectDeviceDescriptor GetDeviceDescriptor(sinix::common::uint16_t bus, sinix::common::uint16_t device, sinix::common::uint16_t function);
        BaseAddressRegister GetBaseAddressRegister(sinix::common::uint16_t bus, sinix::common::uint16_t device, sinix::common::uint16_t function, sinix::common::uint16_t bar);
    };
  }
}

#endif
