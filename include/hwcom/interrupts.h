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
        
        sinix::common::uint16_t hwInterruptOffset;
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
        static void HandleInterruptRequest0x02();
        static void HandleInterruptRequest0x03();
        static void HandleInterruptRequest0x04();
        static void HandleInterruptRequest0x05();
        static void HandleInterruptRequest0x06();
        static void HandleInterruptRequest0x07();
        static void HandleInterruptRequest0x08();
        static void HandleInterruptRequest0x09();
        static void HandleInterruptRequest0x0A();
        static void HandleInterruptRequest0x0B();
        static void HandleInterruptRequest0x0C();
        static void HandleInterruptRequest0x0D();
        static void HandleInterruptRequest0x0E();
        static void HandleInterruptRequest0x0F();
        static void HandleInterruptRequest0x31();

        
        static void HandleException0x00();
        static void HandleException0x01();
        static void HandleException0x02();
        static void HandleException0x03();
        static void HandleException0x04();
        static void HandleException0x05();
        static void HandleException0x06();
        static void HandleException0x07();
        static void HandleException0x08();
        static void HandleException0x09();
        static void HandleException0x0A();
        static void HandleException0x0B();
        static void HandleException0x0C();
        static void HandleException0x0D();
        static void HandleException0x0E();
        static void HandleException0x0F();
        static void HandleException0x10();
        static void HandleException0x11();
        static void HandleException0x12();
        static void HandleException0x13();

        Port8BitSlow picMasterCommand;
        Port8BitSlow picSlaveCommand;
        Port8BitSlow picMasterData;
        Port8BitSlow picSlaveData;

      public:
        InterruptManager(sinix::common::uint16_t hwInterruptOffset, sinix::GlobalDescriptorTable* gdt, sinix::TaskManager* taskManager);
        ~InterruptManager();

        sinix::common::uint16_t GetHwInterruptOffset();

        void Activate();
        void Deactivate();

        sinix::common::uint32_t DoHandleInterrupt(sinix::common::uint8_t interruptNumber, sinix::common::uint32_t esp);
    };

  }
}

#endif
