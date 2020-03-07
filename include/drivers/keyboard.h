#ifndef _SINIX_DRIVERS_KEYBOARD_H_
#define _SINIX_DRIVERS_KEYBOARD_H_

#include <common/types.h>
#include <drivers/driver.h>
#include <hwcom/interrupts.h>
#include <hwcom/port.h>

namespace sinix {
  namespace drivers {
    class KeyboardEventHandler {
      public:
        KeyboardEventHandler();

        virtual void OnKeyDown(char);
        virtual void OnKeyUp(char);
    };

    class KeyboardDriver : public sinix::hwcom::InterruptHandler, public Driver  {
      sinix::hwcom::Port8Bit dataport;
      sinix::hwcom::Port8Bit commandport;

      KeyboardEventHandler* handler;
      public:
        KeyboardDriver(sinix::hwcom::InterruptManager* manager, KeyboardEventHandler *handler);
        ~KeyboardDriver();
        virtual sinix::common::uint32_t HandleInterrupt(sinix::common::uint32_t esp);
        virtual void Activate();
    };
  }
}

#endif
