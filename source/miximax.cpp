#include <mix.h>
#include <kamek.h>
#include <enums.h>
#include <players.h>

Miximax g_MiximaxTable[] = 
{
	{ P_10009SHINDO, 0, P_12804SHINDO, W_MIXIMAX_TRANSFORMATION, W_SETSUNA_BOOST, 0 },
	{ P_10003KIRINO, 0, P_12805KIRINO, W_MIXIMAX_TRANSFORMATION, W_LA_FLAMME, 0 },
	{ P_10290AMEMIYA, 0, P_12806AMEMIYA, W_MIXIMAX_TRANSFORMATION, W_TENCHI_RAIMEI, W_SPARK_EDGE_DRIBBLE_ARMED },
	{ P_10005NISHIZONO, 0, P_12807SHINSUKE, W_MIXIMAX_TRANSFORMATION, W_TAIKOKU_OUKA, 0 },
	{ P_12020TOBU, 0, P_12808TOBU, W_MIXIMAX_TRANSFORMATION, W_KODAI_NO_TSUBASA, 0 },
	{ P_12011FUEI, 0, P_12013FUEI, W_MIXIMAX_TRANSFORMATION, W_KODAI_NO_KIBA, 0 },
	{ P_12011FUEI, 1, P_12809FUEI, W_MIXIMAX_TRANSFORMATION, W_OUJA_NO_KIBA, 0 },
	{ P_10016NISHIKI, 0, P_12810NISHIKI, W_MIXIMAX_TRANSFORMATION, W_KUROSHIO_RIDE, 0 },
	{ P_10010TSURUGI, 0, P_12811TSURUGI, W_MIXIMAX_TRANSFORMATION, W_KIKU_ICHIMONJI, 0 },
	{ P_12014KINAKO, 0, P_12812KINAKO, W_MIXIMAX_TRANSFORMATION, W_KIRA_KIRA_ILLUSION, 0 },
	{ P_10008MATSUKAZE, 0, P_12803TEMMA, W_MIXIMAX_TRANSFORMATION, W_BLACK_ASH_MIXI_MAX, 0 },
	{ P_10008MATSUKAZE, 1, P_12813TEMMA, W_MIXIMAX_TRANSFORMATION, W_OU_NO_TSURUGI, W_SAIKYOU_ELEVEN_HADOU },
	{ P_12012YUICHI, 0, P_12802TSURUGI, W_MIXIMAX_TRANSFORMATION, W_DEATH_DROP_B, 0 },
	{ P_12150ZANAKU, 0, P_12815ZANAKU, W_MIXIMAX_TRANSFORMATION, W_SHINKUUMA_MIXI_MAX, 0 },
	{ P_12150ZANAKU, 1, P_12816SZANAKU, W_MIXIMAX_TRANSFORMATION, W_GREAT_MAX_NA_ORE, 0 },
	{ P_12492FURAN, 0, P_12502YOBI, W_MIXIMAX_TRANSFORMATION, W_CHAOS_METEOR_UNUSED, 0 },
	{ 0xFFFF, 0, 0, 0, 0, 0 },
};

// IsMiximaxPlayer(int, int*)
kmBranchDefCpp(0x800BEBE4, NULL, int, int player, int* unk)
{
	Miximax* mixiData = g_MiximaxTable;
	for (Miximax* mixiData = g_MiximaxTable; mixiData->player > 0; mixiData++)
	{
		if (mixiData->aura == player)
		{
			if(unk)
				*unk = mixiData->player;
			return 1;
		}
	}
	return 0;
}

// GetMiximaxData(int)
kmBranchDefCpp(0x800BECC4, NULL, Miximax*, int tableIdx)
{
	if (tableIdx > 0)
	{
		int realIndex = 0;
		for (Miximax* mixiData = g_MiximaxTable; mixiData->player > 0; mixiData++)
		{
			if (realIndex == tableIdx)
				return &g_MiximaxTable[realIndex];
			realIndex++;
		}
	}
	return 0;
}

// GetMiximaxData(int, int)
kmBranchDefCpp(0x800bed14, NULL, Miximax*, int playerId, int slot)
{
	int listId = GetPLYIDToListID(playerId, 0);
	for (Miximax* mixiData = g_MiximaxTable; mixiData->player > 0; ++mixiData)
	{
		int source = mixiData->player;
		if (mixiData->slot != slot)
			continue;
		if (!listId && source == playerId)
			return mixiData;
		if (listId == GetPLYIDToListID(source, 0))
			return mixiData;
	}
	return 0;
}