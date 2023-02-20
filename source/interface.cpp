#include <kamek.h>
#include <spritestudio.h>
#include <text.h>
#include <xtreme.h>
#include <match.h>
#include <shd_mem.h>

namespace GUI_TG { void Draw(); }

struct TensionBar {
  PRIM_SPR firstPlayerDigit1;
  PRIM_SPR firstPlayerDigit2;
  PRIM_SPR secondPlayerDigit1;
  PRIM_SPR secondPlayerDigit2;
  PRIM_SPR fire;
};

TensionBar* custom_bar = 0;

SHD_TEXCUT digits[] = 
  { 
    {426, 385, 15, 17, 2, 0x80808080},
    {442, 385, 15, 17, 2, 0x80808080},
    {458, 385, 15, 17, 2, 0x80808080},
    {474, 385, 15, 17, 2, 0x80808080},
    {490, 385, 15, 17, 2, 0x80808080},
    {426, 405, 15, 17, 2, 0x80808080},
    {442, 405, 15, 17, 2, 0x80808080},
    {458, 405, 15, 17, 2, 0x80808080},
    {474, 405, 15, 17, 2, 0x80808080},
    {490, 405, 15, 17, 2, 0x80808080},
  };

SHD_TEXCUT fire = { 406, 15, 18, 18, 2, 0x80808080};

void shdSetSprtM(PRIM_SPR* a1);
void draw_bar() {
  if (Settings.IsCompactInterface()) {
    
    int team1Fire = MI_getTensionGauge(0, 1) / 2; // 0 - 200
    int team2Fire = MI_getTensionGauge(1, 1) / 2;
    /*
    char message[50];
    sprintf(message, "#c%01d842#d6600#Q3#j#=%d%", team1Fire * 8 / 200 + 1, team1Fire / 2); // opacity goes from 0-9
    disp_zen(message, 370, 450, 60);
    sprintf(message, "#c%01d842#d6600#Q3#j#=%d%", team2Fire * 8 / 200 + 1, team2Fire / 2); // opacity goes from 0-9
    disp_zen(message, 460, 450, 60);
    */

    int opacity1 = (team1Fire * 128 / 100);
    int opacity2 = (team2Fire * 128 / 100);

    if (opacity1 < 65) opacity1 = 65;
    if (opacity2 < 65) opacity2 = 65;

    if (team1Fire == 100) team1Fire = 99;
    if (team2Fire == 100) team2Fire = 99;

    PRIM_SPR* firstPlayerDigit1 = &custom_bar->firstPlayerDigit1;
    firstPlayerDigit1->color = 0x808080 | (opacity1 << 24);
    PRIM_SPR* firstPlayerDigit2 = &custom_bar->firstPlayerDigit2;
    firstPlayerDigit2->color = 0x808080 | (opacity1 << 24);

    PRIM_SPR* secondPlayerDigit1 = &custom_bar->secondPlayerDigit1;
    secondPlayerDigit1->color = 0x808080 | (opacity2 << 24);
    PRIM_SPR* secondPlayerDigit2 = &custom_bar->secondPlayerDigit2;
    secondPlayerDigit2->color = 0x808080 | (opacity2 << 24);

    int digit1 = team1Fire / 10;
    int digit2 = team1Fire % 10;
    int digit3 = team2Fire / 10;
    int digit4 = team2Fire % 10;
    set_tcut_to_uv(&digits[digit1], firstPlayerDigit1, 6);
    shdSetSprtM(firstPlayerDigit1);
    set_tcut_to_uv(&digits[digit2], firstPlayerDigit2, 6);
    shdSetSprtM(firstPlayerDigit2);
    set_tcut_to_uv(&digits[digit3], secondPlayerDigit1, 6);
    shdSetSprtM(secondPlayerDigit1);
    set_tcut_to_uv(&digits[digit4], secondPlayerDigit2, 6);
    shdSetSprtM(secondPlayerDigit2);
    custom_bar->fire.color = 0x80808080;
    set_tcut_to_uv(&fire, &custom_bar->fire, 6);
    shdSetSprtM(&custom_bar->fire);
    return;
  }
  GUI_TG::Draw();
}

void modify_interface() {
  if (Settings.IsCompactInterface()) {
    char* GuiScore = *(char**)(0x8050D7D0);
    PRIM_SPR* dash = (PRIM_SPR*)GuiScore;
    PRIM_SPR* scoreRight = (PRIM_SPR*)(GuiScore + 0xF0);
    PRIM_SPR* scoreLeft = (PRIM_SPR*)(GuiScore + 0x3C);
    PRIM_SPR* firstDigitRight = (PRIM_SPR*)(GuiScore + 0x12C);
    PRIM_SPR* firstDigitLeft = (PRIM_SPR*)(GuiScore + 0x78);
    PRIM_SPR* secondDigitRight = (PRIM_SPR*)(GuiScore + 0x168);
    PRIM_SPR* secondDigitLeft = (PRIM_SPR*)(GuiScore + 0xB4);

    char* GuiPhase = *(char**)(0x8050D7D4);
    PRIM_SPR* currentHalf = (PRIM_SPR*)GuiPhase;
    PRIM_SPR* colon = (PRIM_SPR*)(GuiPhase + 0x3C);
    PRIM_SPR* firstDigitMinutes = (PRIM_SPR*)(GuiPhase + 0x78);
    PRIM_SPR* secondDigitMinutes = (PRIM_SPR*)(GuiPhase + 0xB4);
    PRIM_SPR* firstDigitSeconds = (PRIM_SPR*)(GuiPhase + 0xF0);
    PRIM_SPR* secondDigitSeconds = (PRIM_SPR*)(GuiPhase + 0x12C);

    char* Emblems = *(char**)(0x807B0FDC);
    PRIM_SPR* emblem1 = (PRIM_SPR*)Emblems;
    PRIM_SPR* emblem2 = (PRIM_SPR*)(Emblems + 0x3C);

    scoreLeft->x = 120;
    scoreRight->x = 186;
    dash->x = 155;
    emblem1->x = 80;
    emblem2->x = 223;
    currentHalf->x = 15;
    currentHalf->y = 20;
    firstDigitMinutes->x = 12;
    firstDigitMinutes->y = 35;
    secondDigitMinutes->x = 25;
    secondDigitMinutes->y = 35;
    colon->x = 39;
    colon->y = 35;
    firstDigitSeconds->x = 48;
    firstDigitSeconds->y = 35;
    secondDigitSeconds->x = 61;
    secondDigitSeconds->y = 35;

    custom_bar = (TensionBar*)MEMAlloc(sizeof(TensionBar), 4, 2, 20);
    custom_bar->firstPlayerDigit1.entryInfo = 33;

    custom_bar->firstPlayerDigit1.x = 380;
    custom_bar->firstPlayerDigit1.y = 450;
    custom_bar->firstPlayerDigit2.x = 396;
    custom_bar->firstPlayerDigit2.y = 450;
    custom_bar->secondPlayerDigit1.x = 444;
    custom_bar->secondPlayerDigit1.y = 450;
    custom_bar->secondPlayerDigit2.x = 460;
    custom_bar->secondPlayerDigit2.y = 450;

    custom_bar->fire.x = 418;
    custom_bar->fire.y = 450;

    for (int i = 0; i < 5; i++) {
      PRIM_SPR* cur = (PRIM_SPR*)custom_bar + i;
      cur->entryInfo = 33;
      cur->ot = 4100;
      cur->texFlag = 12;
      cur->width = 15;
      cur->height = 17;
    }
    custom_bar->fire.width = 18;
    custom_bar->fire.height = 18;
  }
}
kmBranch(0x800C6B24, modify_interface);
kmCall(0x800C72D0, draw_bar);
