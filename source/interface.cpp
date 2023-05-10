#include <kamek.h>
#include <spritestudio.h>
#include <text.h>
#include <xtreme.h>
#include <match.h>
#include <shd_mem.h>

namespace GUI_TG { void Draw(); }
namespace GUI_SCORE { void Draw(); }

struct CompactInterface {
  PRIM_SPR barLeft;
  PRIM_SPR barRight;
  PRIM_SPR rectangle1;
  PRIM_SPR rectangle2;
};

struct RetroInterface {
  PRIM_SPR scoreDigit1;
  PRIM_SPR scoreDigit2;
  PRIM_SPR scoreDigit3;
  PRIM_SPR scoreDigit4;
  PRIM_SPR barLeft;
  PRIM_SPR barRight;
  PRIM_SPR background1;
  PRIM_SPR background2;
  PRIM_SPR rectangle;
};

CompactInterface* compact_interface = 0;
RetroInterface* retro_interface = 0;

SHD_TEXCUT background = { 487, 432, 11, 20, 2, 0x80808080 };
SHD_TEXCUT digits[] = {
  { 493, 101, 8, 14, 2, 0x80808080 },
  { 503, 101, 8, 14, 2, 0x80808080 },
  { 493, 117, 8, 14, 2, 0x80808080 },
  { 503, 117, 8, 14, 2, 0x80808080 },
  { 493, 133, 8, 14, 2, 0x80808080 },
  { 503, 133, 8, 14, 2, 0x80808080 },
  { 493, 149, 8, 14, 2, 0x80808080 },
  { 503, 149, 8, 14, 2, 0x80808080 },
  { 493, 165, 8, 14, 2, 0x80808080 },
  { 503, 165, 8, 14, 2, 0x80808080 },
};

SHD_TEXCUT barre_retroLeft[] = {
  { 7, 8, 189, 35, 2, 0x80808080 },
  { 7, 45, 189, 35, 2, 0x80808080 },
  { 7, 84, 189, 35, 2, 0x80808080 },
  { 7, 122, 189, 35, 2, 0x80808080 },
  { 7, 161, 189, 35, 2, 0x80808080 },
  { 7, 199, 189, 35, 2, 0x80808080 },
};

SHD_TEXCUT barre_retroRight[] = {
  { 230, 8, 189, 35, 2, 0x80808080 },
  { 230, 45, 189, 35, 2, 0x80808080 },
  { 230, 84, 189, 35, 2, 0x80808080 },
  { 230, 122, 189, 35, 2, 0x80808080 },
  { 230, 161, 189, 35, 2, 0x80808080 },
  { 230, 199, 189, 35, 2, 0x80808080 },
};

SHD_TEXCUT barre[] = {
  {9, 308, 30, 152, 2, 0x80808080},
  {55, 308, 30, 152, 2, 0x80808080},
  {101, 308, 30, 152, 2, 0x80808080},
  {150, 308, 30, 152, 2, 0x80808080},
  {196, 308, 30, 152, 2, 0x80808080},
  {243, 308, 30, 152, 2, 0x80808080},
  {289, 308, 30, 152, 2, 0x80808080},
  {336, 308, 30, 152, 2, 0x80808080},
  {383, 308, 30, 152, 2, 0x80808080},
  {427, 308, 30, 152, 2, 0x80808080},
  {473, 308, 30, 152, 2, 0x80808080},
};

SHD_TEXCUT rectangle = { 430, 430, 24, 24, 2, 0x80808080 };

struct pos {
  s16 x, y;
};

struct SpecialInterface {
  pos scoreLeft;
  pos scoreRight;
  pos dash;
  pos emblem1;
  pos emblem2;
  pos half;
  pos firstDigitM;
  pos secondDigitM;
  pos colon;
  pos firstDigitS;
  pos secondDigitS;

  pos scoreDigit1;
  pos scoreDigit2;
  pos scoreDigit3;
  pos scoreDigit4;
};

SpecialInterface compact = { {68, 14}, {134, 14}, {103, 25}, {12, 16}, {187, 16}, {38, 52}, {85, 52}, {98, 52}, {112, 52}, {121, 52}, {134, 52}, {50, 14}, {71, 14}, {126, 14}, {147, 14}};
SpecialInterface retro;

void update_interface() {
  int interface = Settings.GetInterface();
  if (interface == 1) {
    char* GuiScore = *(char**)(0x8050D7D0);
    PRIM_SPR* dash = (PRIM_SPR*)GuiScore;
    PRIM_SPR* scoreRight = (PRIM_SPR*)(GuiScore + 0xF0);
    PRIM_SPR* scoreLeft = (PRIM_SPR*)(GuiScore + 0x3C);
    PRIM_SPR* firstDigitRight = (PRIM_SPR*)(GuiScore + 0x12C);
    PRIM_SPR* firstDigitLeft = (PRIM_SPR*)(GuiScore + 0x78);
    PRIM_SPR* secondDigitRight = (PRIM_SPR*)(GuiScore + 0x168);
    PRIM_SPR* secondDigitLeft = (PRIM_SPR*)(GuiScore + 0xB4);
    PRIM_SPR* scoreDigit1 = (PRIM_SPR*)(GuiScore + 0x78);
    PRIM_SPR* scoreDigit2 = (PRIM_SPR*)(GuiScore + 0x78 + 0x3C);
    PRIM_SPR* scoreDigit3 = (PRIM_SPR*)(GuiScore + 0x12C);
    PRIM_SPR* scoreDigit4 = (PRIM_SPR*)(GuiScore + 0x12C + 0x3C);

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
    
    SpecialInterface* customInterface;
    if (interface == 1) customInterface = &compact;
    else customInterface = &retro;

    scoreLeft->x = customInterface->scoreLeft.x;
    scoreLeft->y = customInterface->scoreLeft.y;
    scoreRight->x = customInterface->scoreRight.x;
    scoreRight->y = customInterface->scoreRight.y;
    scoreDigit1->x = customInterface->scoreDigit1.x;
    scoreDigit1->y = customInterface->scoreDigit1.y;
    scoreDigit2->x = customInterface->scoreDigit2.x;
    scoreDigit2->y = customInterface->scoreDigit2.y;
    scoreDigit3->x = customInterface->scoreDigit3.x;
    scoreDigit3->y = customInterface->scoreDigit3.y;
    scoreDigit4->x = customInterface->scoreDigit4.x;
    scoreDigit4->y = customInterface->scoreDigit4.y;

    dash->x = customInterface->dash.x;
    dash->y = customInterface->dash.y;

    emblem1->x = customInterface->emblem1.x;
    emblem1->y = customInterface->emblem1.y;
    emblem2->x = customInterface->emblem2.x;
    emblem2->y = customInterface->emblem2.y;

    currentHalf->x = customInterface->half.x;
    currentHalf->y = customInterface->half.y;
    firstDigitMinutes->x = customInterface->firstDigitM.x;
    firstDigitMinutes->y = customInterface->firstDigitM.y;
    secondDigitMinutes->x = customInterface->secondDigitM.x;
    secondDigitMinutes->y = customInterface->secondDigitM.y;
    colon->x = customInterface->colon.x;
    colon->y = customInterface->colon.y;
    firstDigitSeconds->x = customInterface->firstDigitS.x;
    firstDigitSeconds->y = customInterface->firstDigitS.y;
    secondDigitSeconds->x = customInterface->secondDigitS.x;
    secondDigitSeconds->y = customInterface->secondDigitS.y;
  }
}
void draw_score() {
  if (Settings.GetInterface() == 2) {
    PRIM_SPR* rectangleRetro = &retro_interface->rectangle;
    //set_tcut_to_uv(&rectangle, rectangleRetro, 6);
    //shdSetSprtM(rectangleRetro);
    
  }
  else GUI_SCORE::Draw();
}

void draw_bar() {
  int interface = Settings.GetInterface();
  if (interface == 1) {
    update_interface();
    int idx1 = MI_getTensionGauge(0, 1) / 20;
    int idx2 = MI_getTensionGauge(1, 1) / 20;
    PRIM_SPR* barre1 = &compact_interface->barLeft;
    PRIM_SPR* barre2 = &compact_interface->barRight;
    
    set_tcut_to_uv(&barre[idx1], barre1, 6);
    set_tcut_to_uv(&barre[idx2], barre2, 6);
    shdSetSprtM(barre1);
    shdSetSprtM(barre2);
    barre1->color = 0x50808080;
    barre2->color = 0x50808080;
    barre1->x = 364;
    barre1->y = 385;

    barre2->x = 476;
    barre2->y = 385;

    PRIM_SPR* rectangle1 = &compact_interface->rectangle1;
    PRIM_SPR* rectangle2 = &compact_interface->rectangle2;
    set_tcut_to_uv(&rectangle, rectangle1, 6);
    set_tcut_to_uv(&rectangle, rectangle2, 6);
    shdSetSprtM(rectangle2);
    shdSetSprtM(rectangle1);
    rectangle1->color = 0x2A000020;
    rectangle2->color = 0x1F000020;
  }
  else if (interface == 2) {
    int idx1 = MI_getTensionGauge(0, 1) / 40;
    int idx2 = MI_getTensionGauge(1, 1) / 40;
    PRIM_SPR* barre1 = &retro_interface->barLeft;
    PRIM_SPR* barre2 = &retro_interface->barRight;

    set_tcut_to_uv(&barre_retroLeft[idx1], barre1, 6);
    set_tcut_to_uv(&barre_retroRight[idx2], barre2, 6);
    shdSetSprtM(barre1);
    shdSetSprtM(barre2);
    barre1->x = 0;
    barre1->y = 300;

    barre2->x = 640;
    barre2->y = 300;
    set_tcut_to_uv(&rectangle, &retro_interface->rectangle, 6);
    shdSetSprtM(&retro_interface->rectangle);
    retro_interface->rectangle.color = 0x2A000080;
  }
  else GUI_TG::Draw();
}

void modify_interface() {
  int interface = Settings.GetInterface();
  if (interface) {
    update_interface();
    if (interface == 1) {
      compact_interface = (CompactInterface*)MEMAlloc(sizeof(CompactInterface), 4, 2, 20);
      for (int i = 0; i < 4; i++) {
        PRIM_SPR* cur = (PRIM_SPR*)compact_interface + i;
        cur->entryInfo = 33;
        cur->ot = 4100;
        cur->texFlag = 12;
        cur->width = 15;
        cur->height = 17;
      }

      compact_interface->rectangle1.width = 140;
      compact_interface->rectangle1.height = 40;
      compact_interface->rectangle1.x = 115 - 140/2;
      compact_interface->rectangle1.y = 12;
      compact_interface->rectangle1.ot = 4009;
      compact_interface->rectangle2.width = 210;
      compact_interface->rectangle2.height = 64;
      compact_interface->rectangle2.x = 10;
      compact_interface->rectangle2.y = 8;
      compact_interface->rectangle2.ot = 4008;
      int additionalData = TEXLoad_Alloc(30035);
      compact_interface->barLeft.texFlag = additionalData;
      compact_interface->barLeft.x = 0x16C;
      compact_interface->barLeft.y = 0x181;
      compact_interface->barRight.texFlag = additionalData;
      compact_interface->barRight.x = 476;
      compact_interface->barRight.y = 0x181;
      compact_interface->barLeft.width = compact_interface->barRight.width = 12;
      compact_interface->barLeft.height = compact_interface->barRight.height = 70;
    }
    else {
      retro_interface = (RetroInterface*)MEMAlloc(sizeof(RetroInterface), 4, 2, 20);
      for (int i = 0; i < 8; i++) {
        PRIM_SPR* cur = (PRIM_SPR*)retro_interface + i;
        cur->entryInfo = 33;
        cur->ot = 4100;
        cur->texFlag = 12;
        cur->width = 8;
        cur->height = 14;
        cur->color = 0x80808080;
      }

      retro_interface->rectangle.width = 100;
      retro_interface->rectangle.height = 40;
      retro_interface->rectangle.x = 340;
      retro_interface->rectangle.y = 10;
      retro_interface->rectangle.ot = 4009;
      retro_interface->rectangle.color = 0x2A000020;

      int additionalData = TEXLoad_Alloc(30035);
      //retro_interface->
      retro_interface->barLeft.width = 189;
      retro_interface->barLeft.height = 35;
      retro_interface->barLeft.x = 0;
      retro_interface->barLeft.y = 300;
      retro_interface->barLeft.texFlag = additionalData;

      retro_interface->barRight.width = 189;
      retro_interface->barRight.height = 35;
      retro_interface->barRight.x = 200;
      retro_interface->barRight.y = 300;
      retro_interface->barRight.texFlag = additionalData;
    }
  }
}
kmBranch(0x800C6B24, modify_interface);
kmCall(0x800C72D0, draw_bar);
kmCall(0x800C7350, draw_score);
kmCall(0x800D717C, draw_score);