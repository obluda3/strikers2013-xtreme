#include <kamek.h>
#include <savedata.h>
#include <players.h>
/*
kmWrite32(0x800BC1E4, 0x3860270f); // li r3, 9999
kmWrite32(0x800bc1e8, 0x4E800020); // blr

kmWrite32(0x800BC19c, 0x38600064); // li r3, 100
kmWrite32(0x800bc1a0, 0x4E800020); // blr
*/
/*
kmWrite32(0x800C1534, 0x3860270F); // li r3, 9999
kmWrite32(0x800C189C, 0x2C17019C); // cmpwi r23, 0x19c
kmWrite32(0x800C1578, 0x7EE3BB78); // mr r3, r23
kmWrite32(0x800C15A4, 0x7EE0BB78); // mr r0, r23
kmWrite32(0x800C17E8, 0x7ee0bb78); // mr r0, r23
kmWrite32(0x800C1538, 0x7ee3bb78); // mr r3, r23
static int lo_bound = 2;
int MaxKizuna(int player)
{
	for (int j = lo_bound; j < 0x19c; j++)
		Savedata_getPlayeData_KizunaData(player, j)->value = 100;
	lo_bound++;
	return 1;
}

kmCall(0x800C153C, MaxKizuna);*/

