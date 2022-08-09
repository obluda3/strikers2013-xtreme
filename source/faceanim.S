#include <kamek_asm.S>

new_anim_table:
    .int 0xae5
    .int 0x6d0
    .int 0x144
    .int 0x349
    .int 0
    .int 0

check_if_done:
    cmpwi r0, 0
    bne continue_loop
    check_other_table:
        lis r12, new_anim_table@ha
        addi r12, r12, new_anim_table@l
        cmpw r12, r5
        beq done
    load_other_table:
        li r3, 0
        li r6, 0
        mr r5, r12
    continue_loop:
        kamek_b 0x80039B2C
    done:
        kamek_b 0x80039BBC

kmBranch 0x80039BB8, check_if_done