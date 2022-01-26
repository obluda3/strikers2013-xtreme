#include <kamek.h>
#include <matchplayer.h>
#include <savedata.h>

u32* dword_8051D640 = (u32*)0x8051D640;
u32* dword_8051EB40 = (u32*)0x8051EB40;

void unlockSecretMiximaxes(PLAYER_DEF* player_def, SavePlayerParam* player_data)
{
	u32 id = player_def->id;
	bool hasMiximax = (player_data->Flag & MIXIMAX_LEVEL_ONE) == MIXIMAX_LEVEL_ONE;
	if ((id == P_12492FURAN || id == P_12330SARU) && !hasMiximax)
	{
		u32 otherPlayer = id == P_12330SARU ? P_12011FUEI : P_12490ASUTA;
		KizunaData* kizunaData = Savedata_getPlayeData_KizunaData(id, otherPlayer);
		if (kizunaData->value >= 50)
		{
			player_data->Flag |= MIXIMAX_LEVEL_ONE;
			dword_8051D640[*dword_8051EB40 + 1345] = id == P_12330SARU ? 18 : 17; // text entry of the miximax unlock

			// no idea what that is
			*dword_8051EB40 += 1;
		}
	}
}
/// MIXIMAXES : ///
kmBranchDefAsm(0x800C1D98, 0x800c1da4) 
{      
	nofralloc
    mr r3, r22					      // r22 -> player_def
	mr r4, r23                        // r23 -> player_data (save)
	bl unlockSecretMiximaxes
	addi r22, r22, 0x148 // PLAYER_DEF* r22 += 1;
	addi r21, r21, 1 // i += 1
	cmpwi r21, 0x10 // if i < 16 (size of a team)
	blr	              
}

inline void handlePopup(int id, int* clubroomMenuScout, int uglyTrick) { 
	asm 
	{
		mr r0, r3
		lwz	r3, 0xDD0(r4) 
		cmpwi	r3, 0x10 
		bge	end 
		mulli	r5, r3, 0xC 
		addi    r3, r3, 1
		stw	r3, 0xDD0(r4) 
		add	r5, r4, r5
		li  r3, 2
		stw	r3, 0xD10(r5) 
		li  r3, 0
		stw	r3, 0xD14(r5) 
		stw	r0, 0xD18(r5) 
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
	{ P_11717ISHIDO, { P_0010GOUENJI, P_0010GOUENJI_IJ, P_10308KUROSAKI, P_10321SENGUJI }, 0, 0, 0 },
	{ P_11760AFURO, { P_0190AFURO, P_0190AFURO_WORLD, P_10229KISHIBE, P_10230SOSUKE, P_10233YOSHIHIKO }, 0, 0, 0 },
	{ P_12013FUEI, { P_12011FUEI, P_10008MATSUKAZE_TNM }, 0, 0, 0 },
	{ P_12803TEMMA, { P_10008MATSUKAZE_TNM, P_10370SHU }, P_10008MATSUKAZE_TNM, P_10370SHU, 75 },
	{ P_12815ZANAKU, {P_12150ZANAKU }, 0, 0, 0},
	{ P_12802TSURUGI, { P_10008MATSUKAZE_TNM, P_12012YUICHI }, P_10010TSURUGI, P_12012YUICHI, 75 },
	{ P_12813TEMMA, { P_12189REI, P_12330SARU }, 0, 0, 0}
};

u16 ChronoStorm[] = { P_12804SHINDO, P_12805KIRINO, P_12806AMEMIYA, P_12807SHINSUKE, P_12808TOBU, P_12809FUEI, P_12810NISHIKI, P_12811TSURUGI, P_12812KINAKO, P_12816SZANAKU, };

void unlockSecretPlayers(int* clubroomMenuScout)
{
	#define UNLOCK_COUNT sizeof(Unlocks) / sizeof(UnlockData)
	for (int i = 0; i < UNLOCK_COUNT; i++)
	{
		UnlockData* unlockData = &Unlocks[i];
		s32 recruitedPlayer = unlockData->Recruited;
		if (!Savedata_ChkPlayerFlag(recruitedPlayer, UNLOCKED))
		{
			for (int j = 0; j < 5; j++)
			{
				s32 player = unlockData->Requirements[j];

				if (!player) 
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

					handlePopup(player, clubroomMenuScout, 0);
					Savedata_SetPlayerFlag(recruitedPlayer, UNLOCKED, 1);
					break;
				}
				else if(!Savedata_ChkPlayerFlag(player, RECRUITED)) break;
			}
				
		}
	}
}

kmBranchDefAsm(0x801F2124, 0x801F2128)
{
	nofralloc
	mr r3, r31
	bl unlockSecretPlayers
	lwz r3, 0xDD0(r31)
	blr
}
