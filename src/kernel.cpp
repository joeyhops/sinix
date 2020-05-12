#include <common/types.h>
#include <gdt.h>
#include <mmu.h>
#include <drivers/driver.h>
#include <hwcom/interrupts.h>
#include <syscalls.h>
#include <hwcom/pci.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>
#include <drivers/vga.h>
#include <drivers/ata.h>
#include <fs/msdospart.h>
#include <gui/desktop.h>
#include <gui/window.h>
#include <gui/render.h>
#include <multitasking.h>

// SETTINGS
// #define SINIX_GRAPHICAL_MODE

using namespace sinix;
using namespace sinix::common;
using namespace sinix::drivers;
using namespace sinix::fs;
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

void clearScr() {
  static uint16_t* VideoMemory = (uint16_t*)0xb8000;

  for (int y = 0; y < 25; y++) {
    for (int x = 0; x < 80; x++) {
      VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0xFF00) | ' ';
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

void sysprintf(char* str) {
  asm("int $0x80" : : "a" (4), "b" (str));
}

void taskA() {
  while(true)
    sysprintf("A");
}

void taskB() {
  while(true)
    sysprintf("NOT A");
}

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors() {
  for (constructor* i = &start_ctors; i != &end_ctors; i++) {
    (*i)();
  }
}

extern "C" void kernelMain(const void* multiboot_structure, uint32_t /*magicnumber*/) {
  
  clearScr();
  GlobalDescriptorTable gdt;

  uint32_t* memupper = (uint32_t*)((((size_t)multiboot_structure)) + 8);
  size_t heap = 10*1024*1024; // 10 MB Heap Space
  MemoryManager memoryManager(heap, (*memupper)*1024 - heap - 10*1024);

  printf("heap: 0x");
  printfHex((heap >> 24) & 0xFF);
  printfHex((heap >> 16) & 0xFF);
  printfHex((heap >> 8) & 0xFF);
  printfHex(heap & 0xFF);
  
  void* allocated = memoryManager.malloc(1024);
  printf("\nallocated: 0x");
  printfHex(((size_t)allocated >> 24) & 0xFF);
  printfHex(((size_t)allocated >> 16) & 0xFF);
  printfHex(((size_t)allocated >> 8) & 0xFF);
  printfHex((size_t)allocated & 0xFF);
  printf("\n");

  TaskManager taskManager;
 // Task task1(&gdt, taskA);
 // Task task2(&gdt, taskB);
 // taskManager.AddTask(&task1);
 // taskManager.AddTask(&task2);

  InterruptManager interrupts(0x20, &gdt, &taskManager);
  SysCallHandler sysCalls(&interrupts, 0x80);

  printf("Initializing Hardware, Stage 1\n");

#ifdef SINIX_GRAPHICAL_MODE
  Desktop desktop(320, 200, 0x00, 0x00, 0xA8);
#endif

  DriverManager drvManager;

#ifdef SINIX_GRAPHICAL_MODE 
  KeyboardDriver keyboard(&interrupts, &desktop);
#else
  KeyboardEventHandler kbEvnt;
  KeyboardDriver keyboard(&interrupts, &kbEvnt);
#endif

  drvManager.AddDriver(&keyboard);  
  
#ifdef SINIX_GRAPHICAL_MODE
  MouseDriver mouse(&interrupts, &desktop);
#else
  MouseToConsole mouseHandler;
  MouseDriver mouse(&interrupts, &mouseHandler);
#endif
  drvManager.AddDriver(&mouse);

  PeripheralComponentInterconnectController PCIController;
  PCIController.SelectDrivers(&drvManager, &interrupts);

  VideoGraphicsArray vga;

#ifdef SINIX_GRAPHICAL_MODE
  Render rend(320, 200);
#endif
  
  printf("Initializing Hardware, Stage 2\n");

  drvManager.ActivateAll();

  printf("Initializing Hardware, Stage 3\n");

#ifdef SINIX_GRAPHICAL_MODE
  vga.SetMode(320, 200, 8);
  Window win1(&desktop, 10, 10, 20, 20, 0xA8, 0x00, 0x00);
  desktop.AddChild(&win1);
  Window win2(&desktop, 40, 15, 30, 30, 0x00, 0xA8, 0x00);
  desktop.AddChild(&win2);
#endif

  // Interrupt 14
  AdvancedTechnologyAttachment ata0m(0x1F0, true);
  printf("ATA Primary Master: ");
  ata0m.Identify(); 
  interrupts.Activate();

  MSDOSPartitionTable::ReadPartitions(&ata0m);

  while(1) {
#ifdef SINIX_GRAPHICAL_MODE 
    desktop.Draw(&rend);
    rend.display(&vga);
#endif
  }
}
