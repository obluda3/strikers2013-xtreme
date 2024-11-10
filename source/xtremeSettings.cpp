#include <menu_setting.h>
#include <enums.h>
#include <kamek.h>

#include "xtreme.h"
#include "xtremeSettings.h"
#include "keyboard.h"
#include "music.h"

XtremeSettings* ModSettings;
int XtremeSettings::GetKeyboardType() { return m_keyboardType; }
bool XtremeSettings::AreOpeningsAllowed() { return m_allowOpenings; }
bool XtremeSettings::IsMovePowerDisplayed() { return m_movePower; }
bool XtremeSettings::IsMixiChargeMode() { return m_mixiMode; }

char *FlagToEng(int val) {
  if (val)
    return "< ON >";
  else
    return "< OFF >";
}

char *KeyboardType(int val) {
  if (val == KEY_LTN)
    return "< Latin >";
  else if (val == KEY_CRL)
    return "#x15< Кириллица >";
  return "< 日本語 >";
}

void XtremeSettings::MusicLoop(int state, void *arg) {
  MENU_SETTING::CMenuSetting *menu = (MENU_SETTING::CMenuSetting *)arg;
  if (state == 2) {
    updateCurrentBgm(0);

    ModSettings->Exec();
    ModSettings->DrawMenu();

    if (IsButtonPushed_Cancel(0)) {
      ModSettings->Save();
      menu->tasks->Pop(0);
      menu->tasks->Push(MENU_SETTING::CMenuSetting::MenuSet0Loop, arg);
      SNDSeSysCANCEL(-1);
    }
  }
}

void XtremeSettings::Save() {
  u8 flag = 0;
  flag |= (m_mixiMode << 4);
  flag |= (m_keyboardType << 2) & 12;
  flag |= m_allowOpenings;
  flag |= m_movePower << 1;
  *(u8*)(0x805F912E) = flag;
}

void XtremeSettings::Exec() {
  s8 pos = m_pos;
  bool isPadUp = UtilitySato::isPad(0, UtilitySato::PAD_UP, UtilitySato::HELD);
  bool isPadDown =
      UtilitySato::isPad(0, UtilitySato::PAD_DOWN, UtilitySato::HELD);
  bool isPadLeft =
      UtilitySato::isPad(0, UtilitySato::PAD_LEFT, UtilitySato::HELD);
  bool isPadRight =
      UtilitySato::isPad(0, UtilitySato::PAD_RIGHT, UtilitySato::HELD);
  if (isPadDown) pos++;
  else if (isPadUp) pos--;
  if (pos > 3) pos = 0;
  else if (pos < 0) pos = 2;
  if (pos != m_pos) {
    m_pos = pos;
    SNDSeSysCLICK(-1);
  } else {
    if (!m_pos) {
      s8 openings = m_allowOpenings;
      if (isPadLeft) openings--;
      else if (isPadRight) openings++;
      if (openings < 0) openings = 1;
      else if (openings > 1) openings = 0;

      if (openings != m_allowOpenings) {
        m_allowOpenings = openings;
        SNDSeSysCLICK(-1);
      }
    } else if (m_pos == 1) {
      s8 keyboard = m_keyboardType;
      if (isPadLeft) keyboard--;
      else if (isPadRight) keyboard++;

      if (keyboard < 0) keyboard = 2;
      else if (keyboard > 2) keyboard = 0;
      if (keyboard != m_keyboardType) {
        m_keyboardType = keyboard;
        SwitchKeyboardLayout(keyboard);
        SNDSeSysCLICK(-1);
      }
    }
    if (m_pos == 2) {
      s8 values = m_movePower;
      if (isPadLeft) values--;
      else if (isPadRight) values++;

      if (values < 0) values = 1;
      else if (values > 1) values = 0;
      if (values != m_movePower) {
        m_movePower = values;
        SNDSeSysCLICK(-1);
      }
    }
    
    if (m_pos == 3) {
      s8 values = m_mixiMode;
      if (isPadLeft) values--;
      else if (isPadRight) values++;

      if (values < 0) values = 1;
      else if (values > 1) values = 0;
      if (values != m_mixiMode) {
        m_mixiMode = values;
        SNDSeSysCLICK(-1);
      }
    }
  }
}

void XtremeSettings::DrawMenu() {
  char message[50];
  s32 currentBgm = g_CurrentBgm;
  if (currentBgm > 0)
    sprintf(message, "#P10#j#I1Music Track %03d", currentBgm);
  else if (currentBgm == 0)
    strcpy(message, "#P10#j#I1Default track");
  else
    strcpy(message, "#P10#j#I1Random track");

  disp_zen(message, 255, 170, 100);

  // Draw setting options
  disp_zen("テーマソング", 225, 250, 90);
  disp_zen("キーボード", 225, 280, 90);
  disp_zen("威力数値", 225, 310, 90);
  disp_zen("Miximax Charge Mode", 225, 340, 90);
  disp_zen(KeyboardType(m_keyboardType), 575, 280, 90);
  disp_zen(FlagToEng(m_allowOpenings), 575, 250, 90);
  disp_zen(FlagToEng(m_movePower), 575, 310, 90);
  disp_zen(FlagToEng(m_mixiMode), 575, 340, 90);

  s32 y = 250 + 30 * m_pos;
  disp_zen("#j#=->", 155, y, 90);
}