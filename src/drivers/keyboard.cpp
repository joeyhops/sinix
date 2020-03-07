#include <drivers/keyboard.h>
using namespace sinix::common;
using namespace sinix::drivers;
using namespace sinix::hwcom;

KeyboardEventHandler::KeyboardEventHandler() {

}

void KeyboardEventHandler::OnKeyDown(char) {

}

void KeyboardEventHandler::OnKeyUp(char) {

}

KeyboardDriver::KeyboardDriver(InterruptManager* manager, KeyboardEventHandler *handler) : InterruptHandler(0x21, manager),
  dataport(0x60),
  commandport(0x64)
{
  this->handler = handler;
}

KeyboardDriver::~KeyboardDriver() {}

void printf(char*);
void printfHex(uint8_t);

void KeyboardDriver::Activate() {

  while(commandport.Read() & 0x1)
    dataport.Read();
  commandport.Write(0xAE); // Send Interrupts
  commandport.Write(0x20); // Send current state to Kernel
  uint8_t status = (dataport.Read() | 1) & ~0x10;
  commandport.Write(0x60); // Set State of Keyboard
  dataport.Write(status);

  dataport.Write(0xF4);
}

uint32_t KeyboardDriver::HandleInterrupt(uint32_t esp) {
  uint8_t key = dataport.Read();

  if (handler == 0)
    return esp;

  if (key < 0x80) {
    switch(key) {
      case 0x45:
      case 0xC5:
      case 0xFA:
        break;
      default:
        printf("KEYBOARD 0x");
        printfHex(key);
        break;
    }
  }

  return esp;
}
