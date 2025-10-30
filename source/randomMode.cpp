#include "randomMode.h"

#include <enums.h>
#include <kamek.h>
#include <random.h>
#include <savedata.h>
#include <emblems.h>
#include <clubroom.h>
#include "music.h"
#include <snd.h>
#include <utilitysato.h>
#include <Kamek\base\rvl_sdk.h>
#include "xtutils.h"

int custom_menu = 0;
int last_room_music = 0;
bool started = false;

namespace CLUBROOM_TEAMORG {
void setNewPlayer_toSaveData(int slot, int player);
};

static RandomMode* menu = 0;
RandomMode::RandomMode() {
  m_state = 0;
  m_slot = 0;
  m_timer = 0;
  m_valid = true;
  
  m_popupKeep = new cPopup();
  m_popupKeep->alloc(4, 3878);
  m_popupKeep->add_item(0, "このチームを保存しますか？", false);
  m_popupKeep->add_item(1, "はい", true);
  m_popupKeep->add_item(2, "いいえ", true);

  m_popupInvalid = new cPopup();
  m_popupInvalid->alloc(3, 3878);
  m_popupInvalid->add_item(0, "メンバーが足りません", false);
  m_popupInvalid->add_item(1, "はい", true);
}

void RandomMode::SetPopupConfirm() {
  if (custom_menu == ROULETTE) {
    m_popupConfirm = new cPopup();
    m_popupConfirm->alloc(4, 3878);
    m_popupConfirm->add_item(0, "Xtremeルーレットを回しますか？", false);
    m_popupConfirm->add_item(1, "はい", true);
    m_popupConfirm->add_item(2, "いいえ", true);
  }
  else {
    m_popupConfirm = new cPopup();
    m_popupConfirm->alloc(4, 3878);
    m_popupConfirm->add_item(0, "XtremeDRAFTを開始しますか？", false);
    m_popupConfirm->add_item(1, "はい", true);
    m_popupConfirm->add_item(2, "いいえ", true);
  }
}

bool RandomMode::IsPlayerBanned(int player) {
  if (!player) return true;
  if (!Savedata_ChkPlayerFlag(player, RECRUITED))
    return true;
  else if (player >= P_2473NATSUMI_MAN && player <= P_KAKUMAO)
    return true;
  else if (player == P_10442HIKITA)
    return true;
  else if (player >= P_10036AOI_MAN && player <= P_10290AMEMIYA_ARMD)
    return true;
  else if (player == P_0001ENDO_TUT)
    return true;
  else if (player > P_11780SAN_MAN && player <= P_12055BETA_A)
    return true;
  else if (player > P_12502YOBI)
    return true;
  return m_picked_players[player];
}

int RandomMode::GetRandomPlayer(int pos) {
  int result = 0;
  while (true) {
    result = shdRndi(1, 0x19C);
    if (!IsPlayerBanned(result)) {
      PLAYER_DEF* player = GetPlayerDef(result);
      if (player->position == pos || pos == -1)
        return result;
    }
  }
}

int getPosition(int slot) {
  if (slot < 4) return DF;
  if (slot < 8) return MF;
  if (slot < 12) return FW;
  if (slot < 14) return GK;
  return -1;
}

void RandomMode::BackupData() {
  _SV_TEAM_INFO* cur = GetCurrentTeam();
  memcpy(&m_backup, cur, sizeof(_SV_TEAM_INFO));
}

void RandomMode::RestoreData() {
  _SV_TEAM_INFO* cur = GetCurrentTeam();
  memcpy(cur, &m_backup, sizeof(_SV_TEAM_INFO));
}
struct MenuOrganizeWindows {
  int flagOtherTab; // bitwise or with 1
  int selectedPlayer; // zero it out
  int slotWindow1;
  int slotWindow2;
};

struct MenuOrganizeTeam {
  int playerId;
  int isUsed;
};

char* RandomMode::GetTeamName() {
  if (m_slot < 4) return "#j#=DRAFT DF";
  else if (m_slot < 8) return "#j#=DRAFT MF";
  else if (m_slot < 12) return "#j#=DRAFT FW";
  else if (m_slot < 14) return "#j#=DRAFT GK";
  else return "#j#=DRAFT";
}

void RandomMode::Update(UtilitySato::CModeSwitch* menuOrganize) {
  switch (m_state) {
    case INIT: {
      // show button info and yes no
      // save current team
      m_slot = 0;
      memset(m_picked_players, 0, sizeof(m_picked_players));
      SNDSeSysOK(-1);
      m_popupConfirm->open(1, 0);
      m_state = POPUP_CONFIRM;
      break;
    }

    case POPUP_CONFIRM:
      // ask for confirmation
      m_popupConfirm->draw();
      if (m_popupConfirm->exec(0)) {
        if (m_popupConfirm->result == 1) {
          // check if enough players
          int dfCnt = 0;
          int fwCnt = 0;
          int mfCnt = 0;
          int gkCnt = 0;
          for (int i = 0; i < P_12502YOBI; i++) {
            if (!Savedata_ChkPlayerFlag(i, RECRUITED)) continue;
            int position = GetPlayerDef(i)->position;
            if (position == GK)
              gkCnt++;
            else if (position == MF)
              mfCnt++;
            else if (position == DF)
              dfCnt++;
            else
              fwCnt++;
          }


          if (!(fwCnt > 16 && mfCnt > 16 && gkCnt > 8 && dfCnt > 16)) {
            m_popupInvalid->open(0,0);
            SNDSeSysBAD(-1);
            m_valid = false;
          }
          m_state = POPUP_HELP;
        }
        else
          m_state = END;
      }
      break;

    case POPUP_HELP:
      if (m_valid) {
        shdRndInit(OSGetTick()); // reset rng seed
        BackupData();
        SNDBgmPlay_Direct(wiiSndGetNameToID("JINGLE_GOAL_01"));
        m_state = custom_menu == DRAFT ? UPDATE_SLOT : MAIN_LOOP;
        for (int i = 0; i < 16; i++) {
          CLUBROOM_TEAMORG::setNewPlayer_toSaveData(i, 0);
        }
        started = true;
      }
      else {
        m_popupInvalid->draw();
        if (m_popupInvalid->exec(0)) m_state = END;
      }
      break;

    case MAIN_LOOP:
      // main loop
      m_timer++;
      if (m_timer % 5 == 0) {
        for (int i = m_slot; i < 16; i++) {
          CLUBROOM_TEAMORG::setNewPlayer_toSaveData(i, GetRandomPlayer(getPosition(i)));
        }
      }

      if (m_timer % 40 == 0) {
        int player = GetRandomPlayer(getPosition(m_slot));
        m_picked_players[player] = true;
        CLUBROOM_TEAMORG::setNewPlayer_toSaveData(m_slot, player);
        SNDSeSysOK(-1);
        m_timer = 0;
        m_slot++;
        if (m_slot < 16) 
          *(int*)((int)menuOrganize + 572) = m_slot;
      }

      if (m_slot > 15) {
        memset(m_picked_players, 0, sizeof(m_picked_players));
        m_state = POPUP_KEEP;
        SNDSeSysOK(-1);
        m_popupKeep->open(1, 0);
      }
      break;

    case UPDATE_SLOT: {
      if (m_timer == 0) {
        MenuOrganizeWindows* windows = (MenuOrganizeWindows*)((int)menuOrganize+0x234);
        MenuOrganizeTeam* team = (MenuOrganizeTeam*)((int)menuOrganize+0x258);
        OSReport("%x windows\n", windows);
        windows->slotWindow1 = m_slot;
        windows->slotWindow2 = 0;
        windows->flagOtherTab |= 1;
        windows->selectedPlayer = m_slot;
        m_state = SELECTION;
        for (int i = 0; i < 3; i++) {
          OSReport("%x", &team[i]);
          team[i].playerId = GetRandomPlayer(getPosition(m_slot));
          team[i].isUsed = 0;
          OSReport(" %x %d\n", &team[i].playerId, team[i].playerId);
          m_picked_players[team[i].playerId] = true;
        }
        for (int i = 3; i < 16; i++) team[i].playerId = 0;
        break;
      }
      else m_timer--;
    }
      
    case SELECTION: {
      MenuOrganizeWindows* windows = (MenuOrganizeWindows*)((int)menuOrganize+0x234);
      MenuOrganizeTeam* team = (MenuOrganizeTeam*)((int)menuOrganize+0x258);
      int slot = windows->slotWindow2;
      if (UtilitySato::isPad(0, UtilitySato::PAD_LEFT, UtilitySato::PRESSED)) slot--;
      if (UtilitySato::isPad(0, UtilitySato::PAD_RIGHT, UtilitySato::PRESSED)) slot++;

      if (slot < 0) slot = 2;
      if (slot > 2) slot = 0;
      
      if (windows->slotWindow2 != slot) {
        windows->slotWindow2 = slot;
        SNDSeSysCLICK(-1);
      }
      
      if (IsButtonPushed_OK(0)) {
        CLUBROOM_TEAMORG::setNewPlayer_toSaveData(m_slot, team[slot].playerId);
        windows->slotWindow2 = -1;
        windows->slotWindow1 = m_slot+1;
        windows->selectedPlayer = -1;
        windows->flagOtherTab &= 0xFFFFFFFE;
        m_slot++;
        SNDSeSysOK(-1);
        if (m_slot > 15) {
          m_state = POPUP_KEEP;
          m_popupKeep->open(1, 0);
          windows->slotWindow1 = 0;
        }
        else {
          m_state = UPDATE_SLOT;
          m_timer = 0;
        }
      }
      break;
    }

    case POPUP_KEEP:
      // show button keep team or not
      // if keep end
      // if not restart maybe
      m_popupKeep->draw();
      if (m_popupKeep->exec(0)) {
        if (m_popupKeep->result != 1)
          RestoreData();
        else {
          // apply correct formation
          _SV_TEAM_INFO* team = (_SV_TEAM_INFO*)0x8058A05C;
          team->Formation = 2;  
          static int formationIndex[] = { 48, 50, 49, 52, 51, 57, 54, 53, 55, 56, 57, 57, 0, 57, 52, 53, };
          ClubroomManager* manager = ClubroomManager::getInstance();
          for (int i = 0; i < 16; i++) {
            team->players[i].FormationIndex = formationIndex[i];
            int flag = team->players[i].Flag;
            int isGoalkeeper = (flag & 2) != 0 ? 0 : 31;
            int isCaptain = (flag >> 2) & 1;
            manager->actors[i].reqReLoad(team->players[i].Id, team->players[i].Kit, team->players[i].ClubroomKit, isCaptain, isGoalkeeper);
          }
        }
        m_state = DONE;
      }
      break;
    case DONE:
      SNDBgmPlayRoom(last_room_music);
    case END:
      // end
      custom_menu = false;
      started = false;
      menuOrganize->currentValue = 2;
      m_state = INIT;
      CClubroomMenuTeamOrganize* teamOrganize = (CClubroomMenuTeamOrganize*)menuOrganize;
      teamOrganize->CreateOrgList(25, 1, false);
      break;
  }
}

void randomizer(UtilitySato::CModeSwitch* menuOrganize) {
  if (menuOrganize->currentValue == 2) {
    if (UtilitySato::isPad(0, UtilitySato::PAD_MINUS, UtilitySato::PRESSED)) {
      custom_menu = RandomMode::ROULETTE;
      menuOrganize->currentValue = -1;
      menu->SetPopupConfirm();
    }
    else if (UtilitySato::isPad(0, UtilitySato::PAD_PLUS, UtilitySato::PRESSED)) {
      custom_menu = RandomMode::DRAFT;
      menuOrganize->currentValue = -1;
      menu->SetPopupConfirm();
    }
  }
  if (custom_menu) {
    menu->Update(menuOrganize);
  }
  menuOrganize->update();
}

void clean() { delete menu; }
void init() {
  menu = new RandomMode();
}

kmCallDefCpp(0x801D8E14, void, char* teamName, char* format, char* command, char* team) {
  if (custom_menu == RandomMode::DRAFT && started) {
    team = menu->GetTeamName();
  }
  sprintf(teamName, format, command, team);
}

kmCallDefCpp(0x801D8EAC, int, const MENU_TP_DATA::TeamOrgData* teamOrgData) {
  if (custom_menu == RandomMode::DRAFT && started) return 0x3A;
  else return MENU_TP_DATA::GetTeamOrgEmblemID(teamOrgData);
}

// backup last room music 
kmBranchDefAsm(0x80046F7C, 0x80046F84) {
  nofralloc
  stwu r1, -0x10(r1)
  mflr r0
  stw r0, 0x14(r1)
  lis r4, last_room_music@ha
  stw r3, last_room_music@l(r4)
  blr
}

kmCall(0x801D6B68, randomizer);
kmBranch(0x801D69D8, init);
kmBranch(0x801D79EC, clean);
