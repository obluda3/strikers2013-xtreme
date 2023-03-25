#include <kamek.h>
#include "xtreme.h"
// sys magic number
kmWrite32(0x80041040, 0x3860002A);
kmWrite32(0x80041F10, 0x3880002A);
kmWrite32(0x80044750, 0x3860002A);
kmWrite32(0x80044d40, 0x2800002A);
kmWrite32(0x80046868, 0x3860002A);

// usr magic number
kmWrite32(0x800410AC, 0x3900004B);
kmWrite32(0x80041F04, 0x3880004B);
kmWrite32(0x80044744, 0x3800004B);
kmWrite32(0x8004685C, 0x3800004B);
kmWrite32(0x80041378, 0x3860004B);
kmWrite32(0x80041FE4, 0x2800004B);
kmWrite32(0x80044d68, 0x2065004B);
kmWrite32(0x80044d6C, 0x3805FFB5);

char* new_save_name = "xt1.sav";
void patch_save_name() {
  char** filenames = *(char***)0x8051D5F4;
  
  if (!XtremeSettings::IsWiimmfi()) new_save_name = "xt2.sav";
  filenames[2652] = new_save_name;
}

kmBranch(0x800241C8, patch_save_name);