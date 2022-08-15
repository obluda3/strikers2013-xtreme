#include <kamek.h>
#include <match.h>
#include <snd.h>
#include "music.h"
#include <savedata.h>

u32* dword_8051D640 = (u32*)0x8051D640;
u32* MixiAnnCount = (u32*)0x8051EB40;

int MixiUnlockList[] = { P_12492FURAN, P_12490ASUTA, P_12330SARU, P_12011FUEI, P_12056GAMMA, P_12150ZANAKU, P_10350HAKURYU, P_12806AMEMIYA };

SavePlayerParam* unlockSecretMiximaxes(register PLAYER_DEF* player_def)
{
    asm("mr player_def, r22");
    int id = player_def->id;
    SavePlayerParam* player_data = Savedata_getPlayerData(id);
    bool hasMiximax = (player_data->Flag & MIXIMAX_LEVEL_ONE) == MIXIMAX_LEVEL_ONE;
    if (!hasMiximax)
    {
        for (int i = 0; i < 3; i++) 
        {
            if (MixiUnlockList[i*2] != id) continue;
            else
            {
                int otherPlayer = MixiUnlockList[i*2 + 1];
                int textEntry = 17 + i;
                KizunaData* kizunaData = Savedata_getPlayeData_KizunaData(id, otherPlayer);
                if (kizunaData->value >= 50)
                {
                    player_data->Flag |= MIXIMAX_LEVEL_ONE;
                    dword_8051D640[*MixiAnnCount + 1345] = textEntry;
                    *MixiAnnCount += 1;
                }
            }
        }
        
    }
    return player_data;
}

inline void handlePopup(int id, int* clubroomMenuScout, int uglyTrick) { 
    asm 
    {
        mr r0, r3
        lwz    r3, 0xDD0(r4) 
        cmpwi    r3, 0x10 
        bge    end 
        mulli    r5, r3, 0xC 
        addi    r3, r3, 1
        stw    r3, 0xDD0(r4) 
        add    r5, r4, r5
        li  r3, 2
        stw    r3, 0xD10(r5) 
        li  r3, 0
        stw    r3, 0xD14(r5) 
        stw    r0, 0xD18(r5) 
        end:
    } 
}

typedef struct 
{
    u16 Recruited;
    u16 Requirements[8];
    u16 kizuna1;
    u16 kizuna2;
    u16 kizunaValue;
} UnlockData;

UnlockData Unlocks[] = { 
    { P_11717ISHIDO, { P_0010GOUENJI, P_0010GOUENJI_2nd, P_0010GOUENJI_IJ, P_10308KUROSAKI, P_10321SENGUJI, P_10441KIBAYAMA }, 0, 0, 0 },
    { P_11760AFURO, { P_0190AFURO, P_0190AFURO_WORLD, P_10229KISHIBE, P_10230SOSUKE, P_10233YOSHIHIKO }, 0, 0, 0 },
    { P_12013FUEI, { P_12011FUEI, P_10008MATSUKAZE_TNM }, 0, 0, 0 },
    { P_12803TEMMA, { P_10008MATSUKAZE_TNM, P_10370SHU }, P_10008MATSUKAZE_TNM, P_10370SHU, 75 },
    { P_12815ZANAKU, {P_12150ZANAKU }, 0, 0, 0},
    { P_12802TSURUGI, { P_10008MATSUKAZE_TNM, P_12012YUICHI }, P_10010TSURUGI, P_12012YUICHI, 75 },
    { P_12813TEMMA, { P_12189REI, P_12330SARU }, 0, 0, 0 },
    { P_12502YOBI, { P_12492FURAN, P_12490ASUTA, P_11780SAN }, 0, 0, 0 },
    { P_12817SARU, { P_12011FUEI, P_12330SARU }, P_12330SARU, P_12011FUEI, 75 }
};

u16 ChronoStorm[] = { P_12804SHINDO, P_12805KIRINO, P_12806AMEMIYA, P_12807SHINSUKE, P_12808TOBU, P_12809FUEI, P_12810NISHIKI, P_12811TSURUGI, P_12812KINAKO, P_12816SZANAKU, };

int unlockSecretPlayers(register int* clubroomMenuScout)
{
    #define UNLOCK_COUNT sizeof(Unlocks) / sizeof(UnlockData)
    
    for (int i = 0; i < UNLOCK_COUNT; i++)
    {
        UnlockData* unlockData = &Unlocks[i];
        s32 recruitedPlayer = unlockData->Recruited;
        if (!Savedata_ChkPlayerFlag(recruitedPlayer, UNLOCKED))
        {
            for (int j = 0; j < 8; j++)
            {
                s32 playerToRecruit = unlockData->Requirements[j];

                if (!playerToRecruit) 
                {
                    s32 kizunaPlayer1 = unlockData->kizuna1;
                    s32 kizunaPlayer2 = unlockData->kizuna2;
                    s32 kizunaValue = unlockData->kizunaValue;
                    if (kizunaPlayer1)
                    {
                        if (Savedata_getPlayeData_KizunaData(kizunaPlayer1, kizunaPlayer2)->value < kizunaValue) break;
                    }

                    if (recruitedPlayer == P_12813TEMMA) 
                    {
                        for (int k = 0; k < 10; k++) Savedata_SetPlayerFlag(ChronoStorm[k], UNLOCKED, 1);
                    }

                    handlePopup(recruitedPlayer, clubroomMenuScout, 0);
                    Savedata_SetPlayerFlag(recruitedPlayer, UNLOCKED, 1);
                    break;
                }
                else if(!Savedata_ChkPlayerFlag(playerToRecruit, RECRUITED)) break;
            }
                
        }
    }
    asm("li r4, 0");
    return 0x36; // default inst
}

//  fix audio bug

kmBranchDefCpp(0x801F04F0, 0x801F04F4, void, int id, int volLeft, int volRight)
{
    int new_id = wiiSndGetNameToID("Jingle2");
    SNDSePlay_Direct(new_id, volLeft, volRight);
}

kmCall(0x800C1960, unlockSecretMiximaxes);
kmCall(0x801F1D28, unlockSecretPlayers);