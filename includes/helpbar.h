#pragma once
#include <types.h>

void HelpBar_Init();
int HelpBar_Exec();
void HelpBar_Draw();
void HelpBar_SetTextID(int id);
int HelpBar_GetTextID();
void HelpBar_AddText(int id);
void HelpBar_Start(int text);

void InfoBar_setString(int line, int a2, int a3);

void HelpBar_Hide();
