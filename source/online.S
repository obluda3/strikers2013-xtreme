#include <kamek_asm.S>
// Ranking URL
kmWrite32 0x804a9ae0, 0

prevent_random_matchmaking:
    li r3, 0
    kamek_bl 0x80022414 // IsButtonPushedOK
    cmpwi r3, 1
    bne end
    cmpwi r31, 1
    beq end
    li r3, -1
    kamek_bl 0x80048CE8 // SNDSeSysBad
    li r3, 0
    end:
    kamek_b 0x8025B23C
    blr

kmBranch 0x8025B234, prevent_random_matchmaking

// Overtime
kmWrite32 0x8025670C, 0x54C0043E

// Items
kmWrite32 0x802566C8, 0x38A00001
kmWrite32 0x8025668C, 0x38A00001