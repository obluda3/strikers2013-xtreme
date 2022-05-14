#include <kamek.h>
#include <moves.h>
#include <mix.h>

typedef struct 
{
    s16 player;
    s16 move;
    u8 needsMiximax;
} BanMove;

static BanMove BanList[] = { 
    { P_12803TEMMA, W_PEGASUS_BREAK, false },
    { P_12813TEMMA, W_PEGASUS_BREAK, false },
    { P_12803TEMMA, W_OU_NO_TSURUGI, false },
    { P_12813TEMMA, W_BLACK_ASH_MIXI_MAX, false },
    { P_12815ZANAKU, W_GREAT_MAX_NA_ORE, false },
    { P_12816SZANAKU, W_SHINKUUMA_MIXI_MAX, false },
    { P_12013FUEI, W_OUJA_NO_KIBA, false },
    { P_12809FUEI, W_KODAI_NO_KIBA, false },
    { P_12330SARU, W_MORTAL_SMASH, true },
    { -1, -1 }
};

static BanMove WhiteList[] = 
{
    { P_12813TEMMA, W_SAIKYOU_ELEVEN_HADOU, false },
    { -1, -1 }
};

bool IsLocked(u32 move, register u32 player, register u32 isMiximax)
{
    asm("mr player, r22");
    asm("mr isMiximax, r24");
    for (BanMove* ban = BanList; ban->player != -1; ban++)
    {
        if (ban->player == player && ban->move == move && (ban->needsMiximax == isMiximax == true))
            return true;
    }
    for (BanMove* allow = WhiteList; allow->player != -1; allow++)
    {
        if (allow->player == player && allow->move == move && allow->needsMiximax == isMiximax == true)
            return false;
    }
    if (WAZIsMiximax(move) && !IsMiximaxPlayer(player, 0)) return true;
    return false;
}

kmCall(0x800F8D44, IsLocked);