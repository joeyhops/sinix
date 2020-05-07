#ifndef _SINIX_HWCOM_INTERRUPTS_H_
#define _SINIX_HWCOM_INTERRUPTS_H_

#include <gdt.h>
#include <multitasking.h>
#include <common/types.h>
#include <hwcom/port.h>

namespace sinix {
  namespace hwcom {
    class InterruptManager;

    class InterruptHandler {
      protected:
        sinix::common::uint8_t interruptNumber;
        InterruptManager* interruptManager;

        InterruptHandler(sinix::common::uint8_t interruptNumber, InterruptManager* interruptManager);
        ~InterruptHandler();

      public:
        virtual sinix::common::uint32_t HandleInterrupt(sinix::common::uint32_t esp);
    };

    class InterruptManager {
      friend class InterruptHandler;
      protected:
        static InterruptManager* ActiveInterruptManager;
        InterruptHandler* handlers[256];
        TaskManager *taskManager;

        struct GateDescriptor {
          sinix::common::uint16_t handlerAddressLowBits;
          sinix::common::uint16_t gdt_codeSegmentSelector;
          sinix::common::uint8_t reserved;
          sinix::common::uint8_t access;
          sinix::common::uint16_t handlerAddressHighBits;
        } __attribute__((packed));

        static GateDescriptor interruptDescriptorTable[256];
        
        struct InterruptDescriptorPointer {
          sinix::common::uint16_t size;
          sinix::common::uint32_t base;
        } __attribute__((packed));
        
        static void SetInterruptDescriptorTableEntry(
              sinix::common::uint8_t interruptNumber,
              sinix::common::uint16_t codeSegmentSelectorOffset,
              void (*handler)(),
              sinix::common::uint8_t DescriptorPrivlegeLevel,
              sinix::common::uint8_t DescriptorType
            );

        
        static sinix::common::uint32_t HandleInterrupt(sinix::common::uint8_t interruptNumber, sinix::common::uint32_t esp);
        static void IgnoreInterruptRequest();
        static void HandleInterruptRequest0x00();
        static void HandleInterruptRequest0x01();
        static void HandleInterruptRequest0x0C();

        Port8BitSlow picMasterCommand;
        Port8BitSlow picSlaveCommand;
        Port8BitSlow picMasterData;
        Port8BitSlow picSlaveData;

      public:
        InterruptManager(sinix::GlobalDescriptorTable* gdt, sinix::TaskManager* taskManager);
        ~InterruptManager();

        void Activate();
        void Deactivate();

        sinix::common::uint32_t DoHandleInterrupt(sinix::common::uint8_t interruptNumber, sinix::common::uint32_t esp);
    };

  }
}

#endif
