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