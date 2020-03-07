#ifndef _SINIX_HWCOM_PORT_H_
#define _SINIX_HWCOM_PORT_H_

#include <common/types.h>

namespace sinix {
  namespace hwcom {
    class Port {
      protected:
        sinix::common::uint16_t portnumber;
        Port(sinix::common::uint16_t portnumber);
        ~Port();
    };

    class Port8Bit : public Port {
      public:
        Port8Bit(sinix::common::uint16_t portnumber);
        ~Port8Bit();
        virtual void Write(sinix::common::uint8_t data);
        virtual sinix::common::uint8_t Read();
    };

    class Port8BitSlow : public Port8Bit {
      public:
        Port8BitSlow(sinix::common::uint16_t portnumber);
        ~Port8BitSlow();
        virtual void Write(sinix::common::uint8_t data);
    };

    class Port16Bit : public Port {
      public:
        Port16Bit(sinix::common::uint16_t portnumber);
        ~Port16Bit();
        virtual void Write(sinix::common::uint16_t data);
        virtual sinix::common::uint16_t Read();
    };

    class Port32Bit : public Port {
      public:
        Port32Bit(sinix::common::uint16_t portnumber);
        ~Port32Bit();
        virtual void Write(sinix::common::uint32_t data);
        virtual sinix::common::uint32_t Read();
    };
  }
}
#endif
