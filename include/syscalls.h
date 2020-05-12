#ifndef _SINIX_SYSCALLS_H_
#define _SINIX_SYSCALLS_H_

#include <common/types.h>
#include <hwcom/interrupts.h>
#include <multitasking.h>

namespace sinix {
  class SysCallHandler : public sinix::hwcom::InterruptHandler
  {
    public:
      SysCallHandler(sinix::hwcom::InterruptManager* interruptManager, sinix::common::uint8_t InterruptNumber);
      ~SysCallHandler();

      sinix::common::uint32_t HandleInterrupt(sinix::common::uint32_t esp);
  };
}

#endif
