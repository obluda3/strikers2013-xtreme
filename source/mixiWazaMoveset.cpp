#include <kamek.h>
#include <moves.h>
#include <mix.h>

typedef struct 
{
	s16 player;
	s16 move;
} BanMove;

static BanMove BanList[] = { 
	{ P_12803TEMMA, W_PEGASUS_BREAK },
	{ P_12813TEMMA, W_PEGASUS_BREAK },
	{ P_12803TEMMA, W_OU_NO_TSURUGI },
	{ P_12813TEMMA, W_BLACK_ASH_MIXI_MAX },
	{ P_12815ZANAKU, W_GREAT_MAX_NA_ORE },
	{ P_12816SZANAKU, W_SHINKUUMA_MIXI_MAX },
	{ P_12013FUEI, W_OUJA_NO_KIBA },
	{ P_12809FUEI, W_KODAI_NO_KIBA },
	{ -1, -1 }
};

bool IsLocked(u32 move, u32 player)
{
	for (BanMove* ban = BanList; ban->player != -1; ban++)
	{
		if (ban->player == player && ban->move == move)
			return true;
	}
	if (WAZIsMiximax(move))
	{
		if (!IsMiximaxPlayer(player, 0)) return true;
	}
	return false;
}

kmBranchDefAsm(0x800F8D44, 0x800F8D48)
{
	mr r4, r22
	bl IsLocked
	blr
}