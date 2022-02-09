#ifndef HELPBAR
#define HELPBAR
#include <types.h>

void HelpBar_Init();
int HelpBar_Exec();
void HelpBar_Draw();
void HelpBar_SetTextID(int id);
int HelpBar_GetTextID();
void HelpBar_AddText(int id);
#endif