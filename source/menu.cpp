#include <Kamek\base\rvl_sdk.h>
#include <buttonhelpers.h>
#include <clubroom.h>
#include <emblems.h>
#include <helpbar.h>
#include <kamek.h>
#include <pointer.h>
#include <shd_thread.h>
#include <snd.h>
#include <teamsettingsolo.h>
#include <textures.h>
#include <titlebar.h>
bool logging = false;

void CClubroomMenuTeamCustom::Draw() {
  m_Text->Draw();
  m_Emblem->Draw();
  for (int i = 0; i < 5; i++) {
    m_buttons[i]->Draw();
  }
  if (m_modeSwitch.currentValue >= 7 && m_modeSwitch.currentValue < 10) m_nameWindow.draw();
  NSClubroomMenu::BstCufTask_Draw();
  NSClubroomMenu::BstCEmbTask_Draw();
  m_numberChange.Draw();
  MenuTeamSettingS_Room_Draw();
}

int CClubroomMenuTeamCustom::Exec() {
  MenuTeam* menuTeamCustom = *((MenuTeam**)0x8050DA70);
  m_modeSwitch.update();
  int mode = m_modeSwitch.currentValue;
  int result = 0;
  STRUC_LAYOUT* layout = menuTeamCustom->layouts[0];

  switch (mode) {
    case 1:  // init
      ClubroomManager* manager = ClubroomManager::getInstance();
      if (manager->isAllActorLoaded()) {
        CClubroomMenuTeamCustom::SetTeamData();
        m_modeSwitch.selectedOption = 2;
        m_modeSwitch._10 = 0;
      }
      break;
    case 2:  // load data
      bool loadingDone = true;
      shdLockMutex(0);
      if (menuTeamCustom->isLoading)
        loadingDone = false;
      shdUnlockMutex(0);
      if (loadingDone) {
        int emblemImage = GetTeamIDToEmblemLL(menuTeamCustom->emblem);
        m_callback->data = TEXGetTPageToFlab(emblemImage);
        m_modeSwitch.selectedOption = 3;
        m_modeSwitch._10 = 0;
      }
      break;
    case 3:  // start initial anim
      if (!m_modeSwitch.justPressed) {
        MenuCsrPointer_DisableAllUser();
        MenuCsrPointer_Show(0, 0);
        TitleBar_Start(menuTeamCustom->_19C, 0, 0);
        HelpBar_Start(4054);
        m_Text->PlaySsa(0, m_ot, 0, 0, 80, m_callback);
        m_Emblem->PlaySsa(0, m_ot, 0, 0, 80, m_callback);
        menuTeamCustom->_1E9 = true;
      }
      if (m_Text->curFrameMaybe <= 0 || (m_Text->SsaComponent->isPlayingFlag & 0x20) != 0) {
        m_Text->EndSsa(0);
        m_Emblem->EndSsa(0);
        m_modeSwitch.selectedOption = 4;
        m_modeSwitch._10 = 0;
        m_Text->PlaySsa(1, m_ot + 1, 0, 0, 72, m_callback);
        m_Emblem->PlaySsa(1, m_ot + 1, 0, 0, 72, m_callback);
        for (int i = 0; i < 5; i++) {
          m_buttons[i]->PlaySsa(0, m_ot + 1, layout[10 + i].x, layout[10 + i].y, 72, 0);
          if (!logging) {
            OSReport("x: %d y: %d\n", layout[10 + i].x, layout[10 + i].y);
          }
        }
        logging = true;

        if (m_curChoice >= 0) {
          CSprStudio* button = m_buttons[m_curChoice];
          button->EndSsa(0);
          button->EndSsa(1);
          button->EndSsa(2);
          button->PlaySsa(1, m_ot + 1, layout[10 + m_curChoice].x, layout[10 + m_curChoice].y, 72, 0);
        }
        SNDSeSysCLICK(-1);
        InfoBar_setString(m_curChoice + 4049, -1, -1);
      }
      break;
    case 4:  // main loop
      if (IsButtonPushed_OK(0) && m_curChoice >= 0) {
        SNDSeSysOK(-1);
        CSprStudio* button = m_buttons[m_curChoice];
        button->EndSsa(0);
        button->EndSsa(1);
        button->EndSsa(2);
        button->PlaySsa(2, m_ot + 1, layout[m_curChoice + 10].x, layout[m_curChoice + 10].y, 80, 0);
        m_nextMenu = m_curChoice;
        m_modeSwitch.selectedOption = 5;
        m_modeSwitch._10 = 0;
      } else if (IsButtonPushed_Cancel(0)) {
        SNDSeSysCANCEL(-1);
        m_nextMenu = -1;
        m_Text->EndSsa(1);
        m_Emblem->EndSsa(1);
        m_modeSwitch.selectedOption = 6;
        m_modeSwitch._10 = 0;
        m_Text->PlaySsa(2, m_ot + 1, 0, 0, 64, m_callback);
        m_Emblem->PlaySsa(2, m_ot + 1, 0, 0, 64, m_callback);
        for (int i = 0; i < 5; i++) {
          m_buttons[i]->EndSsa(0);
          m_buttons[i]->EndSsa(1);
          m_buttons[i]->EndSsa(2);
        }
        TitleBar_Hide(0);
        HelpBar_Hide();
        InfoBar_setString(0, -1, -1);
      } else {
        bool isPadUp = UtilitySato::isPad(0, UtilitySato::PAD_UP, UtilitySato::PRESSED);
        bool isPadDown = UtilitySato::isPad(0, UtilitySato::PAD_DOWN, UtilitySato::PRESSED);
        int newChoice = m_curChoice;
        if (isPadUp) {
          newChoice = m_curChoice - 1;
          if (newChoice < 0) newChoice = 4;
          if (newChoice == m_curChoice) break;
        }
        if (isPadDown) {
          newChoice = m_curChoice + 1;
          if (newChoice > 4) newChoice = 0;
          if (newChoice == m_curChoice) break;
        }
        if (isPadUp || isPadDown) {
          if (m_curChoice >= 0) {
            CSprStudio* button = m_buttons[m_curChoice];
            button->EndSsa(0);
            button->EndSsa(1);
            button->EndSsa(2);
            button->PlaySsa(0, m_ot + 1, layout[10 + m_curChoice].x, layout[10 + m_curChoice].y, 72, 0);
          }
          if (newChoice >= 0) {
            CSprStudio* button = m_buttons[newChoice];
            button->EndSsa(0);
            button->EndSsa(1);
            button->EndSsa(2);
            button->PlaySsa(1, m_ot + 1, layout[10 + newChoice].x, layout[10 + newChoice].y, 72, 0);
          }
        } else
          break;
        m_curChoice = newChoice;
        SNDSeSysCLICK(-1);
        InfoBar_setString(newChoice + 4049, -1, -1);
      }
      break;
    case 5:  // anim to next menu
      bool isPlaying = false;
      CSprStudio* button = m_buttons[m_curChoice];
      if (button->curFrameMaybe > 0 && (button->SsaComponent[2].isPlayingFlag & 0x20) == 0)
        isPlaying = true;
      if (!isPlaying) {
        m_Text->EndSsa(1);
        m_Emblem->EndSsa(1);
        m_modeSwitch.selectedOption = 6;
        m_modeSwitch._10 = 0;
        m_Text->PlaySsa(2, m_ot + 1, 0, 0, 64, m_callback);
        m_Emblem->PlaySsa(2, m_ot + 1, 0, 0, 64, m_callback);
        for (int i = 0; i < 5; i++) {
          CSprStudio* curButton = m_buttons[i];
          curButton->EndSsa(0);
          curButton->EndSsa(1);
          curButton->EndSsa(2);
        }
        TitleBar_Hide(0);
        HelpBar_Hide();
        InfoBar_setString(0, -1, -1);
      }
      break;
    case 6:  // branch to next menu
      if (!m_Text->SsaComponent[2].isPlayingFlag) {
        int newMode = m_nextMenu;
        if (newMode == 0) {
          m_modeSwitch.selectedOption = 7;
          m_modeSwitch._10 = 0;
        } else if (newMode > 4 || newMode <= 0) {
          m_modeSwitch.selectedOption = 0;
          m_modeSwitch._10 = 0;
          result = newMode;
        } else {
          m_modeSwitch.selectedOption = newMode + 9;
          m_modeSwitch._10 = 0;
        }
        TexTerm();
      }
      break;
    case 7:  // name menu init
      if (!m_modeSwitch.justPressed) {
        m_nameWindow.setName((char*)0x80526312);
        m_nameWindow.reset();
        m_nameWindow.enableCollisionTest(1);
        m_nameWindow.setWindowAnm(0);
        m_nameWindow._90 = 1;
        TitleBar_setOt(m_ot + 1);
        TitleBar_Start(menuTeamCustom->_1A4, 0, 0);
        HelpBar_Start(m_nameWindow.getHelpStrID());
      }
      m_nameWindow.exec();
      if (m_nameWindow.isWindowAnmEnd()) {
        m_modeSwitch.selectedOption = 8;
        m_modeSwitch._10 = 0;
      }
      break;
    case 8:  // name menu end loop
      int helpStrId = m_nameWindow.getHelpStrID();
      if (HelpBar_GetTextID() != helpStrId) HelpBar_SetTextID(helpStrId);
      if (m_nameWindow.exec() == 1) {
        if (m_nameWindow.getResult()) {
          char* name = m_nameWindow.getResultString();
          strcpy((char*)0x80526312, name);
        }
        m_modeSwitch.selectedOption = 9;
        m_modeSwitch._10 = 0;
      }
      break;
    case 9:  //
      if (!m_modeSwitch.justPressed) {
        TitleBar_setOt(3842);
        TitleBar_Hide(0);
        HelpBar_Hide();
        if (m_nameWindow.getResult())
          m_nameWindow.setWindowAnm(1);
        else
          m_nameWindow.setWindowAnm(2);
      }
      m_nameWindow.exec();
      if (m_nameWindow.isWindowAnmEnd()) {
        m_nextMenu = -1;
        m_modeSwitch.selectedOption = 1;
        m_modeSwitch._10 = 0;
      }
      break;
    case 10:  // uniform menu
      if (!m_modeSwitch.justPressed) NSClubroomMenu::BstCufTask_Start(0, (NSClubroomMenu::MENU_CUFM::MODE)0);
      if (!NSClubroomMenu::BstCufTask_Exec()) {
        m_nextMenu = -1;
        m_modeSwitch.currentValue = 1;
        m_modeSwitch._10 = 0;
      }
      break;
    case 11:  // emblem menu
      if (!m_modeSwitch.justPressed) NSClubroomMenu::BstCEmbTask_Start();
      if (!NSClubroomMenu::BstCEmbTask_Exec()) {
        m_nextMenu = -1;
        m_modeSwitch.currentValue = 1;
        m_modeSwitch._10 = 0;
      }
      break;
    case 12:  // number change menu
      if (!m_modeSwitch.justPressed) {
        m_numberChange.modeSwitch.selectedOption = 1;
        m_numberChange.modeSwitch._10 = 0;
      }
      if (m_numberChange.Exec()) {
        m_nextMenu = -1;
        m_modeSwitch.selectedOption = 1;
        m_modeSwitch._10 = 0;
      }
      break;
    case 13:  // team save menu
      if (!m_modeSwitch.justPressed)
        MenuTeamSettingS_Room_Start(2);
      if (!MenuTeamSettingS_Room_Exec()) {
        MenuTeamSettingS_Room_Tex_Term();
        m_nextMenu = -1;
        m_modeSwitch.selectedOption = 1;
        m_modeSwitch._10 = 0;
      }
      break;
  }

  m_Text->Exec(32, 0);
  m_Emblem->Exec(32, 0);
  for (int i = 0; i < 5; i++) {
    m_buttons[i]->Exec(32, 0);
  }
  return result;
}

kmBranch(0x801D29FC, callback1);
kmBranch(0x801D1DCC, callback2);