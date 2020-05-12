#include <syscalls.h>

using namespace sinix;
using namespace sinix::common;
using namespace sinix::hwcom;

SysCallHandler::SysCallHandler(InterruptManager* interruptManager, uint8_t InterruptNumber)
: InterruptHandler(InterruptNumber + interruptManager->GetHwInterruptOffset(), interruptManager)
{

}

SysCallHandler::~SysCallHandler() {}

void printf(char*);

uint32_t SysCallHandler::HandleInterrupt(uint32_t esp) {
  CPUState* cpu = (CPUState*)esp;

  switch(cpu->eax) {
    case 4:
      printf((char*)cpu->ebx);
      break;
    default:
      break;
  }

  return esp;
}


