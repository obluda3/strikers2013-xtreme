#include <kamek_asm.S>

// Swap Shinsuke with Endou
kmWrite32 0x8050F474, 1

kmCallDef 0x800e4924
    change_uniform:
        cmpwi r30, 1
        bne end
        li r26, 1
        li r4, 0
    end:
        stw r26, 0x50(r29) // orig inst
        blr
