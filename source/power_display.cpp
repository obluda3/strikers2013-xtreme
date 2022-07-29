#include <kamek.h>
#include <enums.h>
#include <text.h>
#include "xtutils.h"
#include "xtreme_settings.h"

struct PowerInfo
{
    int catchPower;
    int randomBonus;
    int distancePenalty;
};

PowerInfo info;
short* currentMove = (short*)0x807ACE56;
char* IsBlockMove = (char*)0x807ACE5A;
char* IsInteractionWon = (char*)0x807ACE5B;
int* ShootPower = (int*)0x807AC578;
char* MoveType = (char*)0x807ACE54;

void displayMovePower()
{
    if (g_Jukebox.movePower) 
    {
        char buffer[100];
        buffer[0] = 0; // idk how to code
        int moveType = *MoveType;
        int isBlock = *IsBlockMove;
        if (moveType == 1)
            return;
        if (moveType == 2 && !isBlock)
            return;
        if (isBlock && moveType != 3)
        {
            if (!*IsInteractionWon)
                sprintf(buffer, "#j#z120#=TOTAL %d", *ShootPower);
            else return;
        }
        if (!moveType)
        {
            int randomBonus = info.randomBonus;
            int distancePenalty = -info.distancePenalty;
            int shootPower = *ShootPower;
            int basePower = shootPower - distancePenalty - randomBonus;
            sprintf(buffer, "#j#=BASE %d#n#oy5#=DIST %d#n#oy5#=RNG %d#n#oy7#z120#=TOTAL %d", basePower, distancePenalty, randomBonus, shootPower);
        }
        else if (moveType == 3)
        {
            int randomBonus = info.randomBonus;
            int catchPower = info.catchPower;
            int basePower = catchPower - randomBonus;
            sprintf(buffer, "#j#=BASE %d#n#oy5#=RNG %d#n#oy7#z120#=TOTAL %d", basePower, randomBonus, catchPower);
        }
        disp_zen(buffer, 20, 30, 50);
    }
}

kmBranchDefAsm(0x8009E730, 0x8009E734)
{
    nofralloc
    lis r24, info@ha
    addi r24, r24, info@l
    stw r31, 4(r24)
    stw r4, 8(r24)
    lbz r0, 0x4E(r26)
    blr
}

kmBranchDefAsm(0x8009F060, 0x8009F064)
{
    nofralloc
    lis r11, info@ha
    addi r11, r11, info@l
    stw r4, 0(r11)
    stw r26, 4(r11)
    addi r11, r1, 64
    blr
}

kmBranch(0x800DD0A0, displayMovePower);
kmBranch(0x80068D48, displayMovePower);