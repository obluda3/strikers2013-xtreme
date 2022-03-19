#include <kamek.h>
#include <wifi.h>
#include <buttonhelpers.h>
#include <snd.h>

kmWrite32(0x804a9ae0, 0);

kmBranchDefAsm(0x8025B234, 0x8025B23C)
{
	li r3, 0
	bl IsButtonPushed_OK
	cmpwi r3, 1
	bne end
	cmpwi r31, 1
	beq end
	li r3, -1
	bl SNDSeSysBAD
	li r3, 0
	end:
	blr
}

//kmWrite32(0x802566f8, 0x70a6ffff); // andi r6, r5, 0xFFFF
kmWrite32(0x8025670C, 0x54C0043E); // basically a nop
kmWrite32(0x802566C8, 0x38A00001);
kmWrite32(0x8025668C, 0x38a00001);