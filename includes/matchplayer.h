#ifndef TEAM
#define TEAM
#include "players.h"

PLAYER_DEF* GetPLYIDToPlayerEntryTeam(int player, int team);
int GetPLYIDToIndex(int player, int team);
PLAYER_DEF* GetPLYIDToPlayerEntry(int player, int unk);
int GetPLYIDToListID(int id, int unk);
// TODO: add other functions to make this file useful

#endif