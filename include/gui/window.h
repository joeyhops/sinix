#ifndef _SINIX_GUI_WINDOW_H_
#define _SINIX_GUI_WINDOW_H_

#include <gui/widget.h>
#include <drivers/mouse.h>

namespace sinix {
  namespace gui {
    class Window : public CompositeWidget {
      protected:
        bool isDragging;

      public:
        Window(Widget* parent, sinix::common::int32_t x, sinix::common::int32_t y, sinix::common::int32_t w, sinix::common::int32_t h, sinix::common::uint8_t r, sinix::common::uint8_t g, sinix::common::uint8_t b);
        ~Window();
  
        void OnMouseDown(sinix::common::int32_t x, sinix::common::int32_t y, sinix::common::uint8_t button);
        void OnMouseUp(sinix::common::int32_t x, sinix::common::int32_t y, sinix::common::uint8_t button);
        void OnMouseMove(sinix::common::int32_t oldx, sinix::common::int32_t oldy, sinix::common::int32_t newx, sinix::common::int32_t newy);
    };
  }
}

#endif
