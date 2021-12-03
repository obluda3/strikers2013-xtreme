#include <kamek.h>
#include "team.h"
#include "savedata.h"
#include "shd_debug.h"

u32* dword_8051D640 = (u32*)0x8051D640;
u32* dword_8051EB40 = (u32*)0x8051EB40;

/// MIXIMAXES : ///
/// Not proud of that one, i should figure out what these dwords are ///
kmCallDefAsm(0x800C1D98) // ugly hacks but that will basically branch back to the second piece of code (in C++ => big brain moments)
{                                     // we move the registers that we'll need and set them up as arguments
    mr r3, r22 						  // mainly : r22 -> player_def
	mr r4, r23                        // r23 -> player_data (save)
	blr  		              
}

// handles the miximax unlocks
kmCallDefCpp(0x800C1D9C, void, PLAYER_DEF* player_def, SavePlayerData* player_data)
{
	if(player_def->id == P_12492FURAN)
	{
		KizunaData* kizunaData = Savedata_getPlayeData_KizunaData(player_def->id, P_12490ASUTA);
		if (kizunaData->value >= 50) {
			player_data->Flag |= 0x10u;
			dword_8051D640[*dword_8051EB40 + 1345] = 5; // text entry of the miximax unlock
			u32 tmp = *dword_8051D640;
			*dword_8051EB40 = tmp + 1; // no idea what that is
		}
	}
}

kmCallDefAsm(0x800C1DA0)
{
	// last part of our series of shitty hacks: restoring the original instructions
	addi r22, r22, 0x148 // PLAYER_DEF* r22 += 1;
	addi r21, r21, 1 // i += 1
	cmpwi r21, 0x10 // if i < 16 (size of a team)
	blr
}