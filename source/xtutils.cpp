#include "xtutils.h"
#include <utilitysato.h>
PLAYER_DEF *GetTeamPlayerDefBase(int team) {
  return *((PLAYER_DEF **)(0x8051D610 + 4 * team));
}

WAZA_DEF *GetMoveDef(int move) { return *((WAZA_DEF **)0x8051EBD8) + move; }

PLAYER_DEF *GetPlayerDef(int id) {
  return UtilitySato::getPlayerDefAddrBase(id);
}