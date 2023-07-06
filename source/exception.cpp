#include <kamek.h>
#include <text.h>
#include <savedata.h>
// shitty exception handler

extern "C" {
  int* OSGetStackPointer();
}
int findex;

void exception(int context) {
  char message[1024];
  char tmp[50];
  memset(message, 0, sizeof(message));
  memset(tmp, 0, sizeof(tmp));
  
  int* sp = OSGetStackPointer();
  int cnt = 0;
  for (int* i = sp; i; i = (int*)*i) {
    if (i == (int*)-1) break;
    if (cnt++ >= 14) break;
    sprintf(tmp, "0x%08x    0x%08x\n", *i, i[1]);
    strcat(message, tmp);
  }
  //sprintf(message, "valuefileindex=%d", findex);
  unsigned int fg = 0xFFFFFFFF, bg = 0;

  OSFatal(&fg, &bg, message);
}

void log_file_read(char* text, char* arc, int fileIndex) {
  findex = fileIndex;
}
int timer = 0;
void log_key_user() {
  if (*(int*)0x8050C42C == 3 && timer++ == 100) {
    Savedata_getPlayeData_KizunaData(0x19b, 20);
    char message[64];
    memset(message, 0, sizeof(message));
    sprintf(message, "key1=%x key2=%x key3=%x key4=%x \n",*(u16*)0x807ACF14, *(u16*)0x807ACF16, *(u16*)0x807ADBB0, *(u16*)0x807ADBB2);
    OSReport(message);
    timer = 0;
  }
}

kmBranch(0x80289DA0, exception);
kmBranch(0x803347D0, log_key_user);
kmCall(0x8002EF7C, log_file_read);