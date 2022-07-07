#include <mix.h>
#include <kamek.h>
#include <enums.h>
#include "xtutils.h"
#include <match.h>
#include <utilitysato.h>

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
    { P_10008MATSUKAZE, 0, P_12803TEMMA, W_MIXIMAX_TRANSFORMATION, W_BLACK_ASH_MIXI_MAX, W_WONDER_TRAP_ARMED },
    { P_10008MATSUKAZE, 1, P_12813TEMMA, W_MIXIMAX_TRANSFORMATION, W_OU_NO_TSURUGI, W_SAIKYOU_ELEVEN_HADOU },
    { P_12012YUICHI, 0, P_12802TSURUGI, W_MIXIMAX_TRANSFORMATION, W_DEATH_DROP_B, 0 },
    { P_12150ZANAKU, 0, P_12815ZANAKU, W_MIXIMAX_TRANSFORMATION, W_SHINKUUMA_MIXI_MAX, 0 },
    { P_12150ZANAKU, 1, P_12816SZANAKU, W_MIXIMAX_TRANSFORMATION, W_GREAT_MAX_NA_ORE, 0 },
    { P_12492FURAN, 0, P_12502YOBI, W_MIXIMAX_TRANSFORMATION, W_CHAOS_METEOR_UNUSED, 0 },
    { P_12330SARU, 0, P_12817SARU, W_NORMAL_DRIBBLE_CHARGE, W_MORTAL_SMASH, W_SHELLBIT_BURST },
    { 0xFFFF, 0, 0, 0, 0, 0 },
};

Miximax* newGetMiximaxData(int playerId, int slot)
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

bool newIsMiximaxPlayer(int player, int* unk)
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

Miximax* newGetMiximaxData2(int tableIdx)
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
/*
kmBranchDefAsm(0x800bF008, 0x800bF00c)
{
    nofralloc
    lis r6, g_MiximaxTable@h
    ori r6, r6, g_MiximaxTable@l
    blr
}*/

kmBranch(0x800bed14, newGetMiximaxData);
kmBranch(0x800BEBE4, newIsMiximaxPlayer);
kmBranch(0x800BECC4, newGetMiximaxData2);

static int SaruBmdls[] = { -1, -1, -1, -1 };

PLAYER_DEF* LoadNewBodymodel(PLAYER_DEF* plyDef, _PWORK* work, int bodymodel1, int bodymodel2)
{
    int team = work->team;
    SaruBmdls[team * 2] = bodymodel1;
    SaruBmdls[team * 2 + 1] = bodymodel2;
    char* settings = (char*)(0x807ACF00 + 0xC9C * team); // too lazy to figure the struct out sry
    _PWORK* gkPwork = get_gk_pw(work->team);
    bool isFieldPlayer = gkPwork->id != work->id;
    TEAM_DEF* teamDef = getTeamDef(*(settings + 12), 0);
    SetTeamDefToBody(plyDef, isFieldPlayer, *(settings + 15), teamDef);
    MDLRegist(plyDef->bodyModel);
    MDLRegist(plyDef->bodyModel2);
    return plyDef;
}

void ResetMiximax(int team, PLAYER_DEF* player)
{
    PLAYER_DEF* base = UtilitySato::getPlayerDefAddrBase(player->id);
    player->someFlag = (player->someFlag | 0x800000) & 0xFFBFFFFF;
    player->tacticalAction = base->tacticalAction;
    player->bodytype = base->bodytype;
    player->voice = base->voice;
    player->idleAnimation = base->idleAnimation;
    if (player->id == P_12817SARU || player->id == P_12330SARU) 
    {
        player->bodyModel = SaruBmdls[team * 2];
        player->bodyModel2 = SaruBmdls[team * 2 + 1];
    }
}

void NewResetMiximaxPlayerDefB(_PWORK* pwork)
{
    int team = pwork->team;
    int id = pwork->id;
    PLAYER_DEF* playerDef = GetTeamPlayerDefBase(team);
    while (playerDef->id != id && playerDef->id > 0)
        playerDef++;
    ResetMiximax(team, playerDef);
}

bool IsMiximaxMove(int id)
{
    if (id == W_SPARK_EDGE_DRIBBLE_ARMED || id == W_MORTAL_SMASH || id == W_WONDER_TRAP_ARMED)
        return true;
    WAZA_DEF* move = GetMoveDef(id);
    return (move->powerUpIndicator >> 2) & 1;
}

kmBranchDefAsm(0x800DAE0C, 0x800DAE10)
{
    nofralloc
    check_saru:
    lwz r0, 0x0(r17)
    cmpwi r0, P_12330SARU
    bne default_inst
    check_mixi_end:
    lwz r0, 0x118(r17)
    rlwinm r0, r0, 0, 9, 9
    cmpwi r0, 0
    bne default_inst
    lwz r0, 0x6C(r3)
    b end
    default_inst:
    lwz r0, 0x6C(r17) 
    end:
    blr
}

kmBranchDefAsm(0x800BF048, 0x800BF04C)
{
    bl GetPlayerDef
    lwz r0, 0(r3)
    cmpwi r0, P_12817SARU
    bne end
    lwz r0, 0x3C(r3)
    stw r0, 0x3C(r30)
    lwz r0, 0x104(r3)
    stw r0, 0x104(r30)
    lwz r0, 0x30(r3)
    stw r0, 0x30(r30)
    end:
    blr
}

kmBranchDefAsm(0x800BF098, 0x800BF09C)
{
    lwz r0, 0(r3)
    cmpwi r0, P_12817SARU
    beq load_bodymdl
    cmpwi r0, P_12330SARU
    beq load_bodymdl
    cmpwi r3, 0
    b end
    load_bodymdl:
    mr r4, r31
    lwz r5, 0x6C(r30)
    lwz r6, 0x70(r30)
    bl LoadNewBodymodel
    cmpwi r3, 0
    mr r0, r3
    mr r3, r30
    mr r30, r0
    end:
    blr
}

kmWrite32(0x800DDAA4, 0x60000000);
kmWrite32(0x800dae38, 0x7E238B78);
kmWrite32(0x800dae3C, 0x4BFFFFD0);

kmBranch(0x800BF698, ResetMiximax);
kmBranch(0x800DA73C, IsMiximaxMove);
kmBranch(0x800BF52C, NewResetMiximaxPlayerDefB);
