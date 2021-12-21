#include <kamek.h>
#include <matchplayer.h>
#include <savedata.h>
#include <shd_debug.h>

u32* dword_8051D640 = (u32*)0x8051D640;
u32* dword_8051EB40 = (u32*)0x8051EB40;

/// MIXIMAXES : ///
/// Not proud of that one, i should figure out what these dwords are ///
kmCallDefAsm(0x800C1D98) 
{                                     // we move the registers that we'll need and set them up as arguments
    mr r3, r22 						  // mainly : r22 -> player_def
	mr r4, r23                        // r23 -> player_data (save)
	blr  		              
}

// handles the miximax unlock
kmCallDefCpp(0x800C1D9C, void, PLAYER_DEF* player_def, SavePlayerParam* player_data)
{
	if(player_def->id == P_12492FURAN)
	{
		SavePlayerParam* playerParam = Savedata_getPlayerData(P_12492FURAN);
		if(playerParam->Flag & MIXIMAX_LEVEL_ONE != MIXIMAX_LEVEL_ONE)
		{
			KizunaData* kizunaData = Savedata_getPlayeData_KizunaData(player_def->id, P_12490ASUTA);
			if (kizunaData->value >= 50) {
				player_data->Flag |= MIXIMAX_LEVEL_ONE;
				dword_8051D640[*dword_8051EB40 + 1345] = 17; // text entry of the miximax unlock

				// no idea what that is
				u32 tmp = *dword_8051D640;	
				*dword_8051EB40 = tmp + 1; 
		}
	}
}

kmCallDefAsm(0x800C1DA0)
{
	// last part of our series of shitty hacks: restoring the original instructions
	nofralloc
	addi r22, r22, 0x148 // PLAYER_DEF* r22 += 1;
	addi r21, r21, 1 // i += 1
	cmpwi r21, 0x10 // if i < 16 (size of a team)
	blr
}


/// Secret players
/// Extremely ugly since i haven't RE'd the class yet
/// So I'm abusing macro directive: Very Bad Code™ 
inline void handlePopup(int id, int* clubroomMenuScout, int uglyTrick){ 
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

kmWrite32(0x801f2124,0x7FE3FB78); // mr r3, r31
kmCallDefAsm(0x801F212C)
{
	nofralloc
	lwz r3, 0xDD0(r31)
	lwz r31, 12(r1)
	neg r0, r3
	blr
}
kmCallDefCpp(0x801F2128, void, int* clubroomMenuScout)
{
	if(!Savedata_ChkPlayerFlag(P_11717ISHIDO, UNLOCKED) && Savedata_ChkPlayerFlag(P_0010GOUENJI, RECRUITED) && Savedata_ChkPlayerFlag(P_0010GOUENJI_IJ, RECRUITED)
	&& Savedata_ChkPlayerFlag(P_10308KUROSAKI, RECRUITED) && Savedata_ChkPlayerFlag(P_10321SENGUJI, RECRUITED))
	{
		handlePopup(P_11717ISHIDO, clubroomMenuScout, 0);
		Savedata_SetPlayerFlag(P_11717ISHIDO, UNLOCKED, 1);
	}
	if(!Savedata_ChkPlayerFlag(P_11760AFURO, UNLOCKED) && Savedata_ChkPlayerFlag(P_0190AFURO, RECRUITED) && Savedata_ChkPlayerFlag(P_0190AFURO_WORLD, RECRUITED) 
	&& Savedata_ChkPlayerFlag(P_10229KISHIBE, RECRUITED) && Savedata_ChkPlayerFlag(P_10230SOSUKE, RECRUITED) && Savedata_ChkPlayerFlag(P_10233YOSHIHIKO, RECRUITED))
	{
		handlePopup(P_11760AFURO, clubroomMenuScout, 0);
		Savedata_SetPlayerFlag(P_11760AFURO, UNLOCKED, 1);
	}
	if(!Savedata_ChkPlayerFlag(P_12013FUEI, UNLOCKED) && Savedata_ChkPlayerFlag(P_12011FUEI, RECRUITED) && Savedata_ChkPlayerFlag(P_10008MATSUKAZE_TNM, RECRUITED))
	{
		handlePopup(P_12013FUEI, clubroomMenuScout, 0);
		Savedata_SetPlayerFlag(P_12013FUEI, UNLOCKED, 1);
	}
	if(!Savedata_ChkPlayerFlag(P_12803TEMMA, UNLOCKED) && Savedata_ChkPlayerFlag(P_10008MATSUKAZE_TNM, RECRUITED) && Savedata_ChkPlayerFlag(P_10370SHU, RECRUITED))
	{
		KizunaData* kizunaData = Savedata_getPlayeData_KizunaData(P_12803TEMMA, P_10370SHU);
		if(kizunaData->value > 75)
		{
			handlePopup(P_12803TEMMA, clubroomMenuScout, 0);
			Savedata_SetPlayerFlag(P_12803TEMMA, UNLOCKED, 1);
		}
	}
	if(!Savedata_ChkPlayerFlag(P_12815ZANAKU, UNLOCKED) && Savedata_ChkPlayerFlag(P_12150ZANAKU, RECRUITED))
	{
		handlePopup(P_12815ZANAKU, clubroomMenuScout, 0);
		Savedata_SetPlayerFlag(P_12815ZANAKU, UNLOCKED, 1);
	}
	if(!Savedata_ChkPlayerFlag(P_12802TSURUGI, UNLOCKED) && Savedata_ChkPlayerFlag(P_10008MATSUKAZE_TNM, RECRUITED) && Savedata_ChkPlayerFlag(P_12012YUICHI, RECRUITED))
	{
		KizunaData* kizunaData = Savedata_getPlayeData_KizunaData(P_10010TSURUGI, P_12012YUICHI);
		if (kizunaData->value > 75)
		{
			handlePopup(P_12802TSURUGI, clubroomMenuScout, 0);
			Savedata_SetPlayerFlag(P_12802TSURUGI, UNLOCKED, 1);
		}
	}
	if(!Savedata_ChkPlayerFlag(P_12804SHINDO, UNLOCKED) && !Savedata_ChkPlayerFlag(P_12805KIRINO, UNLOCKED) && !Savedata_ChkPlayerFlag(P_12806AMEMIYA, UNLOCKED) && 
	!Savedata_ChkPlayerFlag(P_12807SHINSUKE, UNLOCKED) && !Savedata_ChkPlayerFlag(P_12808TOBU, UNLOCKED) && !Savedata_ChkPlayerFlag(P_12809FUEI, UNLOCKED) && 
	!Savedata_ChkPlayerFlag(P_12810NISHIKI, UNLOCKED) && !Savedata_ChkPlayerFlag(P_12811TSURUGI, UNLOCKED) && !Savedata_ChkPlayerFlag(P_12812KINAKO, UNLOCKED) && 
	!Savedata_ChkPlayerFlag(P_12813TEMMA, UNLOCKED) && !Savedata_ChkPlayerFlag(P_12816SZANAKU, UNLOCKED) && Savedata_ChkPlayerFlag(P_12330SARU, RECRUITED) && 
	Savedata_ChkPlayerFlag(P_12189REI, RECRUITED))
	{
		handlePopup(P_12813TEMMA, clubroomMenuScout, 0);
		Savedata_SetPlayerFlag(P_12804SHINDO, UNLOCKED, 1);
		Savedata_SetPlayerFlag(P_12805KIRINO, UNLOCKED, 1);
		Savedata_SetPlayerFlag(P_12806AMEMIYA, UNLOCKED, 1);
		Savedata_SetPlayerFlag(P_12807SHINSUKE, UNLOCKED, 1);
		Savedata_SetPlayerFlag(P_12808TOBU, UNLOCKED, 1);
		Savedata_SetPlayerFlag(P_12809FUEI, UNLOCKED, 1);
		Savedata_SetPlayerFlag(P_12810NISHIKI, UNLOCKED, 1);
		Savedata_SetPlayerFlag(P_12811TSURUGI, UNLOCKED, 1);
		Savedata_SetPlayerFlag(P_12812KINAKO, UNLOCKED, 1);
		Savedata_SetPlayerFlag(P_12813TEMMA, UNLOCKED, 1);
		Savedata_SetPlayerFlag(P_12816SZANAKU, UNLOCKED, 1);

	}
}
