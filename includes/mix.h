#ifndef INAST_MIX
#define INAST_MIX
#include "types.h"
#include "players.h"

struct Miximax
{
    s16 player;
    s16 slot;
    s16 aura;
    s16 move1;
    s16 move2;
    s16 move3;
};

int ChkMiximaxGK(int player);
Miximax* GetMiximaxData(int player, int slot);
Miximax* GetMiximaxData(int player);
int GetMiximaxPlyID(int player, int slot);
int IsMiximaxPlayer(int player, int* unk);
int GetMiximaxWazaKeeper(int player);

#endif