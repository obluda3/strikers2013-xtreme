#ifndef SHD_TASKS
#define SHD_TASKS
typedef void (*task_t)(int, void *);
#include "types.h"

struct TaskHolder {
  task_t function;
  u32 ptrArgument;
  u32 field_8;
};

class cTASK {
public:
  TaskHolder *stack;
  void Create(int size);
  void Push(void (*function)(int, void *), void *arg);
  void Pop(bool unused);
  void Update();

private:
  u32 m_elapsedTime;
  u32 m_callCount;
  u32 m_remainingTasks;
  u32 m_taskCount;
};

#endif