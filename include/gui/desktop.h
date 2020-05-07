#ifndef _SINIX_GUI_DESKTOP_H_
#define _SINIX_GUI_DESKTOP_H_

#include <gui/widget.h>
#include <drivers/mouse.h>

namespace sinix {
  namespace gui {
    class Desktop : public CompositeWidget, public sinix::drivers::MouseEventHandler {
      protected:
        sinix::common::uint32_t MouseX;
        sinix::common::uint32_t MouseY;

      public:
        Desktop(sinix::common::int32_t w, sinix::common::int32_t h, sinix::common::uint8_t r, sinix::common::uint8_t g, sinix::common::uint8_t b);
        ~Desktop();

        void Draw(sinix::common::GraphicsContext* gc);

        void OnMouseDown(sinix::common::uint8_t button);
        void OnMouseUp(sinix::common::uint8_t button);
        void OnMouseMove(int x, int y);
    };
  }
}

#endif
