#include "randomMode.h"

#include <enums.h>
#include <kamek.h>
#include <random.h>
#include <savedata.h>
#include <snd.h>
#include <utilitysato.h>

#include "xtutils.h"

namespace CLUBROOM_TEAMORG {
void setNewPlayer_toSaveData(int slot, int player);
};

static RandomMode* menu = 0;

RandomMode::RandomMode() {
  m_state = 0;
  m_slot = 0;
  m_timer = 0;
  m_popup = new cPopup();
  m_popup->alloc(4, 3878);
  m_popup->add_item(0, "Generer une equipe aleatoire ?", false);
  m_popup->add_item(1, "Oui", 1);
  m_popup->add_item(2, "Non", 1);
}

bool RandomMode::IsPlayerBanned(int player) {
  if (!player) return true;
  if (!Savedata_ChkPlayerFlag(player, RECRUITED))
    return true;
  else if (player >= P_2473NATSUMI_MAN && player <= P_KAKUMAO)
    return true;
  else if ((player >= P_10442HIKITA && player <= P_10444RINNO) || player == P_10446MUTO)
    return true;
  else if (player >= P_10036AOI_MAN && player <= P_10290AMEMIYA_ARMD)
    return true;
  else if (player == P_12150ZANAKU_EVL || player == P_0001ENDO_TUT)
    return true;
  else if (player >= P_11780SAN_MAN && player <= P_12055BETA_A)
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

bool custom_menu = false;

void RandomMode::Update(UtilitySato::CModeSwitch* menuOrganize) {
  switch (m_state) {
    case 0:
      // show button info and yes no
      // save current team
      m_slot = 0;
      memset(m_picked_players, 0, sizeof(m_picked_players));
      m_popup->open(1, 0);
      m_state = 8;
      break;
    case 8: {
      // display popup
      m_popup->draw();
      int result = m_popup->exec(0);
      if (result) {
        if (result > 0)
          m_state = 1;
        else
          m_state = 5;
      }
      break;
    }
    case 1:
      // display rows
      m_state = 2;
      break;
    case 2:
      // main loop
      m_timer++;
      if (m_timer % 5 == 0) {
        for (int i = m_slot; i < 16; i++) {
          CLUBROOM_TEAMORG::setNewPlayer_toSaveData(i, GetRandomPlayer(getPosition(i)));
        }
      }
      if (m_timer % 60 == 0) {
        int player = GetRandomPlayer(getPosition(m_slot));
        m_picked_players[player] = true;
        CLUBROOM_TEAMORG::setNewPlayer_toSaveData(m_slot, player);
        m_slot++;
        if (m_slot < 16) *(int*)((int)menuOrganize + 572) = m_slot;
        SNDSeSysOK(-1);
        m_timer = 0;
      }
      if (m_slot > 15) {
        memset(m_picked_players, 0, sizeof(m_picked_players));
        m_state = 5;
      }
      break;
    case 3:
      // show button keep team or not
      // if keep end
      // if not restart maybe
      m_state = 4;
      break;
    case 4:
      // ask restart
      m_state = 5;
      break;
    case 5:
      // end
      custom_menu = false;
      menuOrganize->currentValue = 2;
      break;
  }
}

void randomizer(UtilitySato::CModeSwitch* menuOrganize) {
  if (menuOrganize->currentValue == 2) {
    if (UtilitySato::isPad(0, UtilitySato::PAD_MINUS, UtilitySato::PRESSED)) {
      custom_menu = true;
      menuOrganize->currentValue = -1;
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

kmCall(0x801D6B68, randomizer);
kmBranch(0x801D69D8, init);
kmBranch(0x801D79EC, clean);