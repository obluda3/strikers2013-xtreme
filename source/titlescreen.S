#include <kamek_asm.S>

// Tenma
kmWrite32 0x8050F470, 0xC0
// Endou
kmWrite32 0x8050F474, 1

kmCallDef 0x800e4924
    change_uniform:
        cmpwi r30, 1
        beq player_2
        player_1:
        li r26, 0xE // team 1
        b end
        player_2:
        li r26, 1 // team 2
        li r4, 0
    end:
        stw r26, 0x50(r29) // orig inst
        blr

// remove sasuke
//kmWrite16 0x800E4E8A, 3918
//kmWrite16 0x800e4e8e, 1