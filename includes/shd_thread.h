#include <types.h>

struct SHD_THREAD {
};

int shdCreateThread(SHD_THREAD* thread);
bool shdIsFinishedThread(SHD_THREAD* thread);
int shdResumeThread(SHD_THREAD* thread);
bool wiiIsExecThread();
void shdLockMutex(int a1);
void shdUnlockMutex(int a1);