#include <kamek_asm.S>
// Ranking URL

url_list:
.int 0x805064BA
.int 0x8050689e
.int 0x8050772e
.int 0x8050774F
.int 0x80507815
.int 0x8050783A
.int 0x8050C1FE
.int 0

new_url:
.string "xtreme13.com"
.align 4
replace_urls:
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stmw r22, 8(r1)
    lis r22, url_list@ha
    addi r22, r22, url_list@l
    lis r23, new_url@ha
    addi r23, r23, new_url@l
    loop:
    lwz r3, 0(r22)
    mr r4, r23
    cmpwi r3, 0
    beq end
    kamek_bl 0x802BC8A8
    addi r22, r22, 4
    b loop
    end:
    lis r3, 0x2f00
    lwz r22, -4(r22)
    stw r3, 0xC(r22)
    lmw r22, 8(r1)
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
kmBranch 0x80256E88, replace_urls
// Overtime
// kmWrite32 0x8025670C, 0x54C0043E

// Timer
kmWrite32 0x80144BC4, 0x38000063

// Items
kmWrite32 0x802566C8, 0x38A00001
kmWrite32 0x8025668C, 0x38A00001

// Matchmaking filter
kmWrite32 0x804A685F, 0x58543200