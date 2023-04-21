#include <kamek.h>
// shitty exception handler

extern "C" {
  int* OSGetStackPointer();
}

void exception(int context) {
  char message[1024];
  char tmp[50];
  memset(message, 0, sizeof(message));
  memset(tmp, 0, sizeof(tmp));

  int* sp = OSGetStackPointer();
  int cnt = 0;
  for (int* i = sp; i; i = (int*)*i) {
    if (i == (int*)-1) break;
    if (cnt++ >= 8) break;
    sprintf(tmp, "0x%08x:   0x%08x    0x%08x\n", i, *i, i[1]);
    strcat(message, tmp);
  }
  unsigned int fg = 0xFFFFFFFF, bg = 0;

  OSFatal(&fg, &bg, message);
}

kmBranch(0x80289DA0, exception);