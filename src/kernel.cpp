#include <common/types.h>
#include <gdt.h>
#include <drivers/driver.h>
#include <hwcom/interrupts.h>
#include <hwcom/pci.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>
#include <drivers/vga.h>
#include <gui/desktop.h>
#include <gui/window.h>

using namespace sinix;
using namespace sinix::common;
using namespace sinix::drivers;
using namespace sinix::hwcom;
using namespace sinix::gui;

void printf(char* str) {
  static uint16_t* VideoMemory = (uint16_t*)0xb8000;

  static uint8_t x = 0, y = 0; 

  for(int i = 0; str[i] != '\0'; ++i) {
    switch (str[i]) {
      case '\n':
        x = 0;
        y++;
        break;
      default:
        VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0xFF00) | str[i];
        x++;
        break;
    }

    if (x >= 80) {
      x = 0;
      y++;
    }

    if (y >= 25) {
      for (y = 0; y < 25; y++)
        for (x = 0; x < 80; x++)
          VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0xFF00) | ' ';

      x = 0;
      y = 0;
    }
  }
}

void printfHex(uint8_t key) {
  char* foo = "00";
  char* hex = "0123456789ABCDEF";
  foo[0] = hex[(key >> 4) & 0x0F];
  foo[1] = hex[key & 0x0F];
  printf(foo);
}

class MouseToConsole : public MouseEventHandler {
  int8_t x, y;
  public:
    MouseToConsole() {
      uint16_t* VideoMemory = (uint16_t*)0xb8000;
      x = 40;
      y = 12;
      VideoMemory[80 * x + y] = ((VideoMemory[80 * 12 + 40] & 0xF000) >> 4)
                                | ((VideoMemory[80 * 12 + 40] & 0x0F00) << 4)
                                | (VideoMemory[80 * 12 + 40] & 0x00FF);
    }

    void OnMouseMove(int xoffset, int yoffset) {
      uint16_t* VideoMemory = (uint16_t*)0xb8000;
      VideoMemory[80 * y + x] = ((VideoMemory[80 * y + x] & 0xF000) >> 4)
                              | ((VideoMemory[80 * y + x] & 0x0F00) << 4)
                              | (VideoMemory[80 * y + x] & 0x00FF);
        x += xoffset;
        if (x < 0) x = 0;
        if (x >= 80) x = 79;
        y += yoffset;
        if (y < 0) y = 0;
        if (y >= 25) y = 24;

        VideoMemory[80 * y + x] = ((VideoMemory[80 * y + x] & 0xF000) >> 4)
                              | ((VideoMemory[80 * y + x] & 0x0F00) << 4)
                              | (VideoMemory[80 * y + x] & 0x00FF);
    }
};

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors() {
  for (constructor* i = &start_ctors; i != &end_ctors; i++) {
    (*i)();
  }
}

extern "C" void kernelMain(const void* multiboot_structure, uint32_t /*magicnumber*/) {
  
  GlobalDescriptorTable gdt;
  InterruptManager interrupts(&gdt);
 
  printf("Initializing Hardware, Stage 1\n");

  Desktop desktop(320, 200, 0x00, 0x00, 0xA8);

  DriverManager drvManager;

  // KeyboardEventHandler kbEvnt;
  
  // KeyboardDriver keyboard(&interrupts, &kbEvnt);
  KeyboardDriver keyboard(&interrupts, &desktop);
  drvManager.AddDriver(&keyboard);
  
  // MouseToConsole mouseHandler;
  // MouseDriver mouse(&interrupts, &mouseHandler);
  MouseDriver mouse(&interrupts, &desktop);
  drvManager.AddDriver(&mouse);

  PeripheralComponentInterconnectController PCIController;
  PCIController.SelectDrivers(&drvManager, &interrupts);

  VideoGraphicsArray vga;

  printf("Initializing Hardware, Stage 2\n");

  drvManager.ActivateAll();

  printf("Initializing Hardware, Stage 3\n");
  vga.SetMode(320, 200, 8);

  Window win1(&desktop, 10, 10, 20, 20, 0xA8, 0x00, 0x00);
  desktop.AddChild(&win1);
  Window win2(&desktop, 40, 15, 30, 30, 0x00, 0xA8, 0x00);
  desktop.AddChild(&win2);

  interrupts.Activate();

  while(1) {
    desktop.Draw(&vga);
  }
}
