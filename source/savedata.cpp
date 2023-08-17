#include <kamek.h>
#include <shd_mem.h>
#include "xtreme.h"
#include <dvd.h>
// sys magic number
kmWrite32(0x80041040, 0x3860002B);
kmWrite32(0x80041F10, 0x3880002B);
kmWrite32(0x80044750, 0x3860002B);
kmWrite32(0x80044d40, 0x2800002B);
kmWrite32(0x80046868, 0x3860002B);

// usr magic number
kmWrite32(0x800410AC, 0x3900004C);
kmWrite32(0x80041F04, 0x3880004C);
kmWrite32(0x80044744, 0x3800004C);
kmWrite32(0x8004685C, 0x3800004C);
kmWrite32(0x80041378, 0x3860004C);
kmWrite32(0x80041FE4, 0x2800004C);
kmWrite32(0x80044d68, 0x2065004C);
kmWrite32(0x80044d6C, 0x3805FFB4);

char* new_save_name = "xtreme2.sav";
void patch_save_name() {
  char** filenames = *(char***)0x8051D5F4;

  filenames[2652] = new_save_name;
}

void default_save_data() {
  char *path = "save.sav";

  int entrynum = DVDConvertPathToEntrynum(path);
  OSReport("default save change\n");
  if (entrynum < 0)
    OSReport("Could not find '%s' \n", path);
  else {
    DVDHandle handle;
    if (!DVDFastOpen(entrynum, &handle))
      OSReport("ERROR: Failed to open file!\n");
    else {
      u32 length = handle.length, roundedLength = (handle.length + 0x1F) & ~0x1F;
      char* buffer = (char*)MEMAlloc(roundedLength, 32, 3, 31);
      if (!buffer)
        OSReport("ERROR: Out of file memory\n");
      else {
        DVDReadPrio(&handle, buffer, roundedLength, 0, 2);
        DVDClose(&handle);
        memcpy((void*)0x80526100, buffer + 0x2590, 0x68548);
        memcpy((void*)0x8058E648, buffer + 0x2590, 0x68548);
        memcpy((char*)0x805F9120 + 0x2590, buffer + 0x2590, 0x68548);
        MEMFree(buffer);
      }
    }
  }
}

kmBranch(0x800241C8, patch_save_name);
kmBranch(0x800410E4, default_save_data);