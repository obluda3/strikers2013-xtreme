#include <kamek_asm.S>
.set W_NORMAL_DRIBBLE_CHARGE, 0x9e
.set W_PERFECT_TOWER, 0x2b
.set W_KOUTEI_PENGUIN_X, 0x10C
.set W_DARK_MATTER, 0x12B
.set W_CHAOS_METEOR_UNUSED, 0x184 
.set W_KILLER_FIELDS, 0xA7
.set W_GUARDIAN_SHIELD, 0xBE
.set W_GUARDIAN_SHIELD_F, 0x22
.set W_GANIMEDE_PROTON, 0xFD
.set WAZATasks, 0x807B184C
.set gpWaza, 0x8050D820
fix_skip_mixi_saru:
    lwz r25, 0x124C(r6)
    cmpwi r25, W_NORMAL_DRIBBLE_CHARGE
    bne branch_back
    skip_point:
    li r0, 1
    li r3, 78
    cmpwi r0, 2
    branch_back:
    extsb. r0, r0
    blr

remove_skip_new_block:
    lwz R12, -0x6BE0(r13)
    lwz r0, 0x124C(r12)
    cmpwi r0, W_PERFECT_TOWER
    beq go_back
    cmpwi r0, W_KOUTEI_PENGUIN_X
    beq go_back
    cmpwi r0, W_CHAOS_METEOR_UNUSED
    beq go_back
    cmpwi r0, W_DARK_MATTER
    beq go_back
    cmpwi r0, W_GANIMEDE_PROTON
    beq go_back
    kamek_bl 0x800DF5E4
    go_back:
    kamek_b 0x800E184C

fix_skip_new_block:
    // orig inst
    stb r0, 0x1793(r3)
    lwz r0, 0x124C(r3)
    cmpwi r0, W_PERFECT_TOWER
    beq stop
    cmpwi r0, W_KOUTEI_PENGUIN_X
    beq stop
    cmpwi r0, W_CHAOS_METEOR_UNUSED
    beq stop
    cmpwi r0, W_DARK_MATTER
    beq stop
    cmpwi r0, W_GANIMEDE_PROTON
    beq stop
    b end
    stop:
    // stop anim
    li r0, 1
    stb r0, 0x1796(r3)
    li r3, 20
    li r4, 16
    kamek_bl 0x80021ed0 // fade
    lis r3, WAZATasks@ha
    addi r3, r3, WAZATasks@l
    li r4, 0
    kamek_bl 0x8004947C // pop
    end:
    kamek_b 0x800E1858

check_fixed_users:
    cmpwi r29, W_KILLER_FIELDS
    beq get_back
    cmpwi r29, W_PERFECT_TOWER
    get_back:
    kamek_b 0x800DCB04

fix_end_guardian_shield:
    lhz r0, 0x34(r4)
    lis r7, gpWaza@ha
    lwz r7, gpWaza@l(r7)
    lbz r7, 0x1793(r7)
    cmpwi r7, 0
    bnelr
    cmpwi r25, W_GUARDIAN_SHIELD
    bne test2
    li r0, 148
    blr
    test2:
    cmpwi r25, W_GUARDIAN_SHIELD_F
    bnelr
    li r0, 283
    blr


kmCall 0x800DBE84, fix_skip_mixi_saru
kmBranch 0x800E1854, fix_skip_new_block
kmBranch 0x800E1848, remove_skip_new_block
kmBranch 0x800DCB00, check_fixed_users
kmCall 0x800daab4, fix_end_guardian_shield