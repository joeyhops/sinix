#ifndef _SINIX_DRIVERS_VGA_H_
#define _SINIX_DRIVERS_VGA_H_

#include <common/types.h>
#include <hwcom/port.h>
#include <drivers/driver.h>

namespace sinix {
  namespace drivers {
    class VideoGraphicsArray {
      protected:
        hwcom::Port8Bit miscPort;
        hwcom::Port8Bit crtcIndexPort;
        hwcom::Port8Bit crtcDataPort;
        hwcom::Port8Bit sequencerIndexPort;
        hwcom::Port8Bit sequencerDataPort;
        hwcom::Port8Bit graphicsControllerIndexPort;
        hwcom::Port8Bit graphicsControllerDataPort;
        hwcom::Port8Bit attributeControllerIndexPort;
        hwcom::Port8Bit attributeControllerReadPort;
        hwcom::Port8Bit attributeControllerWritePort;
        hwcom::Port8Bit attributeControllerResetPort;

        void WriteRegisters(sinix::common::uint8_t* registers);
        sinix::common::uint8_t* GetFrameBufferSegment();

        virtual sinix::common::uint8_t GetColorIndex(sinix::common::uint8_t r, sinix::common::uint8_t g, sinix::common::uint8_t b);

      public:
        VideoGraphicsArray();
        ~VideoGraphicsArray();

        virtual bool SupportsMode(sinix::common::uint32_t width, sinix::common::uint32_t height, sinix::common::uint32_t colordepth);
        virtual bool SetMode(sinix::common::uint32_t width, sinix::common::uint32_t height, sinix::common::uint32_t colordepth);
        virtual void PutPixel(sinix::common::int32_t x, sinix::common::int32_t y, sinix::common::uint8_t r, sinix::common::uint8_t g, sinix::common::uint8_t b);
        virtual void PutPixel(sinix::common::int32_t x, sinix::common::int32_t y, sinix::common::uint8_t colorIndex);
        virtual void FillRectangle(sinix::common::uint32_t x, sinix::common::uint32_t y, sinix::common::uint32_t w, sinix::common::uint32_t h, sinix::common::uint8_t r, sinix::common::uint8_t g, sinix::common::uint8_t b);
    };
  }
}

#endif
