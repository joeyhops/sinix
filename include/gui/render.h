#ifndef _SINIX_GUI_RENDER_H_
#define _SINIX_GUI_RENDER_H_

#include <drivers/vga.h>
#include <common/graphicscontext.h>

namespace sinix {
  namespace gui {
    class Pixel {
      public:
        sinix::common::uint8_t r;
        sinix::common::uint8_t g;
        sinix::common::uint8_t b;
    };

    class Render : public sinix::drivers::VideoGraphicsArray {
      private:
        Pixel pixels[320][200];

      public:
        Render(sinix::common::int32_t w, sinix::common::int32_t h);
        ~Render();

        void display(sinix::common::GraphicsContext* gc);
        void PutPixel(sinix::common::int32_t x, sinix::common::int32_t y, sinix::common::uint8_t r, sinix::common::uint8_t g, sinix::common::uint8_t b);
    };
  }
}

#endif
