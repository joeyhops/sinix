#include <multitasking.h>

using namespace sinix;
using namespace sinix::common;

Task::Task(GlobalDescriptorTable *gdt, void entryPoint()) {
  cpuState = (CPUState*)(stack + 4096 - sizeof(CPUState));

  cpuState->eax = 0;
  cpuState->ebx = 0;
  cpuState->ecx = 0;
  cpuState->edx = 0;

  cpuState->esi = 0;
  cpuState->edi = 0;
  cpuState->ebp = 0;
  
  /**
  cpuState->gs = 0;
  cpuState->fs = 0;
  cpuState->es = 0;
  cpuState->ds = 0;
  */

  // cpuState->err = 0;
  
  // cpuState->esp = 0;
  cpuState->eip = (uint32_t)entryPoint;
  cpuState->cs = gdt->CodeSegmentSelector();
  // cpuState->ss = 0;
  cpuState->eflags = 0x202;
}

Task::~Task() {}

TaskManager::TaskManager() {
  numTasks = 0;
  currentTask = -1;
}

TaskManager::~TaskManager() {}

bool TaskManager::AddTask(Task* task) {
  if (numTasks >= 256)
    return false;
  tasks[numTasks++] = task;
  return true;
}

CPUState* TaskManager::Schedule(CPUState* cpustate) {
  if (numTasks <= 0)
    return cpustate;

  if (currentTask >= 0) {
    tasks[currentTask]->cpuState = cpustate;
  }

  if (++currentTask >= numTasks) {
    currentTask %= numTasks;
  }

  return tasks[currentTask]->cpuState;
}


