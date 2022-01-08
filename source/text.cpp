#include <kamek.h>
/*
int GetXAdvance(u16 character, u32 scale);

kmBranchDefAsm(0x80034148, 0x80034170) {
	nofralloc
	mr r3, r10
	mr r4, r25
	bl GetXAdvance
	mr r0, r3
	blr
}
kmBranchDefAsm(0x800342CC, 0x800342D0) {
	nofralloc
	mr r4, r31
	bl GetXAdvance
	mr r12, r3
	addi r6, r1, 12
	blr
}

kmWrite32(0x8003433C, 0x40C20008);

int GetXAdvance(u16 character, u32 scale) {
	int xAdValue;
	switch(character){
		case 0x75:
			xAdValue = 0x130;
			break;
		case 0x7a:
			xAdValue = 0x140;
			break;
		case 0x61:
			xAdValue = 0x200;
			break;
		default:
			xAdValue = 0x160;
			break;
	}
	return xAdValue * scale / 1000 / 2;
}*/