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

static BanMove WhiteListMix[] = 
{
    { P_12813TEMMA, W_SAIKYOU_ELEVEN_HADOU, false },
    { P_12803TEMMA, W_WONDER_TRAP_ARMED, false },
    { -1, -1 }
};

static BanMove WhiteListReg[] = 
{
    { P_10249MAHORO, W_ILLUSION_BALL, false },
    { P_12009DORIRU, W_ILLUSION_BALL, false },
    { P_1092DOMON, W_KILLER_SLIDE, false },
    { P_12011FUEI, W_SARGASSO, false },
    { P_12013FUEI, W_SARGASSO, false },
    { P_12809FUEI, W_SARGASSO, false },
    { P_12803TEMMA, W_WONDER_TRAP_ARMED, false },
    { -1, -1 }
};

bool IsAllowedRegular(s32 isFound, s32 player, s32 move)
{
    if (isFound) return 1;
    for (BanMove* ban = WhiteListReg; ban->player != -1; ban++)
    {
        if (ban->player == player && ban->move == move)
            return 1;
    }
    return 0;
}

bool IsLockedMiximax(u32 move, register u32 player, register u32 isMiximax)
{
    asm("mr player, r22");
    asm("mr isMiximax, r24");
    for (BanMove* ban = BanList; ban->player != -1; ban++)
    {
        if (ban->player == player && ban->move == move && (ban->needsMiximax == isMiximax == true))
            return true;
    }
    for (BanMove* ban = WhiteListMix; ban->player != -1; ban++)
    {
        if (ban->player == player && ban->move == move && (ban->needsMiximax == isMiximax == true))
            return 1;
    }
    if (WAZIsMiximax(move) && !IsMiximaxPlayer(player, 0)) return true;
    return false;
}

kmCall(0x800F8D44, IsLockedMiximax);
kmBranchDefAsm(0x800F8D38, 0x800F8D3C)
{
    nofralloc
    mr r3, r0
    mr r4, r22
    mr r5, r26
    bl IsAllowedRegular
    mr r0, r3
    cmpwi r0, 0
    blr
}
