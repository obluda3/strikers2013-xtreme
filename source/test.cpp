#include <kamek.h>
#include "mix.h"
#include "shd_debug.h"

// Enables debug info
kmWrite32(0x8033A4F0, 0x60000000);
kmWrite32(0x8033A500, 0x60000000);
kmWrite32(0x8033482C, 0x60000000);
kmWrite32(0x8033483c, 0x60000000);

kmBranchDefCpp(0x800BEDC0, NULL, void*, void* miximaxData)
{
	Miximax* mixiData = (Miximax*) miximaxData;
	bprintf("Miximax de %04x vers %04x", mixiData->player, mixiData->aura);
	return miximaxData;
}