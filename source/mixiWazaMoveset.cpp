#include <kamek.h>
#include <moves.h>
#include <mix.h>

typedef struct 
{
	u16 player;
	u16 move;
} BanMove;

static const BanMove BanList[] = { 
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
		if (!IsMiximaxPlayer(player)) return true;
	}
	return false;
}

kmBranchDefAsm(0x800F8D44, 0x800F8D48)
{
	bl WAZIsMiximax
	cmpwi r3, 0
	beq end
	check_mixi_player:
		mr r3, r22
		li r4, 0
		bl IsMiximaxPlayer
		xori r3, r3, 1
	end:
		blr
}