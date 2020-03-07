#ifndef _SINIX_DRIVERS_MOUSE_H_
#define _SINIX_DRIVERS_MOUSE_H_

#include <common/types.h>
#include <drivers/driver.h>
#include <hwcom/interrupts.h>
#include <hwcom/port.h>

namespace sinix {
  namespace drivers {  
    class MouseEventHandler {
      public:
        MouseEventHandler();
    
        virtual void onActivate();
        virtual void OnMouseDown(sinix::common::uint8_t button);
        virtual void OnMouseUp(sinix::common::uint8_t button);
        virtual void OnMouseMove(int x, int y);
    };

    class MouseDriver : public sinix::hwcom::InterruptHandler, public Driver  {
      sinix::hwcom::Port8Bit dataport;
      sinix::hwcom::Port8Bit commandport;

      sinix::common::uint8_t buffer[3];
      sinix::common::uint8_t offset;
      sinix::common::uint8_t buttons;

      MouseEventHandler* handler;
      public:
        MouseDriver(sinix::hwcom::InterruptManager* manager, MouseEventHandler *handler);
        ~MouseDriver();
        virtual sinix::common::uint32_t HandleInterrupt(sinix::common::uint32_t esp);
        virtual void Activate();
    };
  }
}
#endif
