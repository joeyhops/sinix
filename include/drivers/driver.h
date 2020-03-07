#ifndef _SINIX_DRIVERS_DRIVER_H_
#define _SINIX_DRIVERS_DRIVER_H_

namespace sinix {
  namespace drivers {
    class Driver {
      public:
        Driver();
        ~Driver();

        virtual void Activate();
        virtual int Reset();
        virtual void Deactivate();
    };

    class DriverManager {
      private:
        Driver* drivers[255];
        int numDrivers;

      public:
        DriverManager();
        void AddDriver(Driver*);
        void ActivateAll();

    };
  }
}

#endif
