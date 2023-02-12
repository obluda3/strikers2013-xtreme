#include "helpbar.h"
#include "music.h"
#include "xtreme.h"
#include <kamek.h>
#include <menu_setting.h>
#include <menubg.h>
#include <savedata.h>

void SettingLoop(int state, void *menu);
void SettingPassLoop(int state, void *arg);

namespace MENU_SETTING {
int SecretPlayerIds[] = {P_10036AOI, P_10037AKANE, P_10038MIDORI, P_10121MIYABINO, P_12110INABA, P_12012YUICHI, P_11780SAN, P_11201WANDABA};
char NewPasswords[8][18] = {
        { 0x8D, 0xB7, 0xAF, 0xD1, 0xC9, 0xF8, 0xEB, 0xD5, 0x05, 0x52, 0x27, 0x76, 0x41, 0x34, 0x63, 0x52, 0x00, 0x00, },
        { 0x8D, 0xAB, 0xAF, 0xCD, 0xC9, 0xE9, 0xEB, 0xA4, 0x05, 0x28, 0x27, 0x16, 0x41, 0x65, 0x63, 0x5B, 0x00, 0x00, },
        { 0x8D, 0xA1, 0xAF, 0xDD, 0xC9, 0xAB, 0xEB, 0xB6, 0x05, 0x71, 0x27, 0x1C, 0x41, 0x6F, 0x63, 0x5D, 0x00, 0x00, },
        { 0x8C, 0x6E, 0xAE, 0xB3, 0xCA, 0x01, 0xEA, 0x20, 0x04, 0xE6, 0x26, 0xF7, 0x40, 0x9C, 0x60, 0xB9, 0x00, 0x00, },
        { 0x8D, 0xBC, 0xAF, 0xF9, 0xC9, 0xBC, 0xEA, 0x32, 0x04, 0xEB, 0x26, 0xF7, 0x40, 0x8C, 0x62, 0x90, 0x00, 0x00, },
        { 0x8D, 0xC7, 0xAF, 0x91, 0xC9, 0xB1, 0xEB, 0xD2, 0x05, 0x49, 0x27, 0x02, 0x41, 0x3B, 0x63, 0x45, 0x00, 0x00, },
        { 0x8D, 0xB8, 0xAF, 0x9E, 0xC9, 0xF0, 0xEB, 0xBD, 0x05, 0x26, 0x27, 0x1F, 0x41, 0x14, 0x63, 0x32, 0x00, 0x00, },
        { 0x8C, 0x4C, 0xAE, 0xAF, 0xC8, 0x2C, 0xEA, 0xF2, 0x04, 0xD4, 0x26, 0xF6, 0x40, 0xB5, 0x60, 0xB9, 0x00, 0x00, },
    };
}; // namespace MENU_SETTING

void SettingLoop(int state, void *arg) {
  MENU_SETTING::CMenuSetting *menu = (MENU_SETTING::CMenuSetting *)arg;
  cTASK *tasks = menu->tasks;
  if (state == 2 && !Settings.passAccepted) {
    int helpStrId = menu->nameWindow->getHelpStrID();
    if (HelpBar_GetTextID() != helpStrId)
      HelpBar_SetTextID(helpStrId);
    if (menu->nameWindow->exec()) {
      tasks->Pop(0);
      if (menu->nameWindow->getResult()) {
        int index = -1;
        menu->textEntry = -1;

        char hashedInput[] = {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        };
        char *input = menu->nameWindow->getResultString();
        memcpy(hashedInput, input, sizeof(hashedInput));
        u8 key = 0xF;
        for (int j = 0; j < sizeof(hashedInput); j++) {
          hashedInput[j] ^= key;
          key += 0xF;
        }
        for (int i = 0; i < 8; i++) {
          if (!memcmp(hashedInput, MENU_SETTING::NewPasswords[i], 16)) {
            index = i;
            break;
          }
        }

        if (index != -1) {
          int plyId = MENU_SETTING::SecretPlayerIds[index];

          if (Savedata_ChkPlayerFlag(plyId, UNLOCKED)) {
            SNDSePlay(90, 128, 128);
            menu->textEntry = 7566;
            menu->popup->set_itemtext(1, 7567);
          } else {
            SNDSePlay(238, 128, 128);
            Savedata_SetPlayerFlag(plyId, 0, 1);
            menu->textEntry = 317;
            if (plyId != P_11201WANDABA)
              menu->popup->set_itemtext(1, 7569 + index);
            else
              menu->popup->set_itemtext(
                  1, "#I1#Y17#P11#=「#r10#=クラーク　ワンダバット」#C#I0#=を");
            menu->popup->set_itemtext(2, 7568);
          }
          tasks->Push(MENU_SETTING::CMenuSetting::AlgoConfirmPassword, menu);
        } else {
          SNDSePlay(90, 128, 128);
          menu->textEntry = 7565;
          menu->popup2->set_itemtext(1, "");
          tasks->Push(MENU_SETTING::CMenuSetting::AlgoConfirmPassword, menu);
        } 
      } else {
        menu->textEntry = 0;
        tasks->Pop(0);
        tasks->Push(MENU_SETTING::CMenuSetting::MenuSet0Loop, menu);
        tasks->Push(MENU_SETTING::CMenuSetting::MenuSet4Out, menu);
        menu->nameWindow->setWindowAnm(2);
      }
    }
    menu->nameWindow->draw();
  } else if (!state) {
    menu->nameWindow->setName("");
    menu->nameWindow->reset();
    menu->nameWindow->enableCollisionTest(true);
  } else if (Settings.passAccepted) {
    updateCurrentBgm(0);
    if (IsButtonPushed_Cancel(0)) {
      tasks->Pop(0);
    }
    drawBgmName();
  }
}

void push_xtremesetting_hook(MENU_SETTING::CMenuSetting* menu) {
  HelpBar_SetTextID(532);
  menu->tasks->Push(XtremeSettings::MusicLoop, menu);
}

kmBranchDefAsm(0x8013F2D8, 0x8013F2E8) {
  nofralloc
  mr r3, r31
  bl push_xtremesetting_hook
  blr
}

// remove fading animation for xtreme's menu
kmBranchDefAsm(0x801404D4, 0x801404E4) {
  nofralloc
  cmpwi r0, 3
  beq case_3
  cmpwi r0, 4
  bne end
  case_3:
  li r0, 5
  stw r0, 0x1BC(r31)
  end:
  blr
}

kmBranch(0x8013f794, SettingLoop);

// textures
kmWrite32(0x804C9FD0, 30019);
kmWrite32(0x8013ED34, 0x38600002);