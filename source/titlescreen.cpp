#include "kamek.h"
// Swap Shinsuke with Endou 1st
kmWrite32(0x8050F474, 1);

// Changes a2 in SetTeamDefToBody if it's the second player (Endou)
// And changes the team from Raimon GO to Raimon
// That way, he can have his goalkeeper uniform
kmCallDefAsm(0x800E4924) 
{
	change_uniform:
		cmpwi r30, 1 //if Shinsuke
		bne end
		li r26, 1 // Raimon 1 Team_def
		li r4, 0 // Load goalkeeper uniform
	end:
		stw r26, 0x50(r29) // Original instruction
		blr	
}