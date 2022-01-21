#ifndef INAST_TXT
#define INAST_TXT

const char **MainTexts = *((const char***)0x805131C0);
const char **ShortCommands = *((const char***)0x805131BC);
const char **WazaDesc = *((const char***)0x8050D8C8);

int disp_zen(char* text, int x, int y, int scale); // Returns disp_zen1 / 16
int disp_zen1(char* text, int x, int y, int scale, int unk1, int color, int unk2); // returns the position of the last character I think
int disp_zenf(char* text, int x, int y, int scale);

#endif