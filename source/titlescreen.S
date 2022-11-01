#include <kamek_asm.S>

// Desta
kmWrite32 0x8050F470, 0x9C
// Belzebu
kmWrite32 0x8050F474, 0x96

kmCallDef 0x800e4924
    change_uniform:
        cmpwi r30, 1
        beq player_2
        player_1:
        li r26, 0xB // team 1
        b end
        player_2:
        li r26, 0xB // team 2
    end:
        stw r26, 0x50(r29) // orig inst
        blr

// remove sasuke
kmWrite16 0x800E4E8A, 3918
kmWrite16 0x800e4e8e, 1