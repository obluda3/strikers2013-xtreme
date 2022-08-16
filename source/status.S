#include <kamek_asm.S>

param_to_rank:
    li r0, 10
    divw r3, r3, r0
    cmpwi r3, 11
    blelr
    li r3, 11
    blr

kmCall 0x801066E4, param_to_rank
kmWrite32 0x8010678C, 0x3803006e
