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
public:
	TaskHolder *stack;
	void Create(int size);
	void Push(void* function, void* arg);
	void Pop(bool unused);
	void Update(); 
private:
	u32 m_elapsedTime;
	u32 m_callCount;
	u32 m_remainingTasks;
	u32 m_taskCount;
};

#endif