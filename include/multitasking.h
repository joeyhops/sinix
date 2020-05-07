#ifndef _SINIX_MULTITASKING_H_
#define _SINIX_MULTITASKING_H_

#include <common/types.h>
#include <gdt.h>

namespace sinix {
  struct CPUState {
    sinix::common::uint32_t eax;
    sinix::common::uint32_t ebx;
    sinix::common::uint32_t ecx;
    sinix::common::uint32_t edx;
  
    sinix::common::uint32_t esi;
    sinix::common::uint32_t edi;
    sinix::common::uint32_t ebp;

    /**
    sinix::common::uint32_t gs;
    sinix::common::uint32_t fs;
    sinix::common::uint32_t es;
    sinix::common::uint32_t ds;
    */

    sinix::common::uint32_t err;
  
    sinix::common::uint32_t eip;
    sinix::common::uint32_t cs;
    sinix::common::uint32_t eflags;
    sinix::common::uint32_t esp;
    sinix::common::uint32_t ss;
  } __attribute__((packed));

  class Task {
    friend class TaskManager;
    private:
      sinix::common::uint8_t stack[4096]; //4 KB
      CPUState* cpuState;

    public:
      Task(GlobalDescriptorTable *gdt, void entryPoint());
      ~Task();
  };

  class TaskManager {
    private:
      Task* tasks[256];
      int numTasks;
      int currentTask;

    public:
      TaskManager();
      ~TaskManager();
      
      bool AddTask(Task* task);
      CPUState* Schedule(CPUState* cpustate);
  };
}

#endif
