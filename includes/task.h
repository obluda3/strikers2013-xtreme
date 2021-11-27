#ifndef SHD_TASKS
#define SHD_TASKS

#include "types.h"

typedef struct TaskHolder
{
  void* function;
  u32 ptrArgument;
  u32 field_8;
} TaskHolder;

class cTask
{
private:
	TaskHolder *stack;
	u32 _4;
	u32 _8;
	u32 remainingTasks;
	u32 taskCount;
};

#endif