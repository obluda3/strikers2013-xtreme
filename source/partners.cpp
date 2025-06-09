#include "partners.h"
#include <kamek.h>
#include <moves.h>
#include <shd_mem.h>
#include "xtutils.h"
#include <enums.h>


struct ExtendedPartners {
    u16 move;
    u16 partners[10];
};

int partner_count = 10;

// list of the additional partners
ExtendedPartners extended_moves[] = {
    {W_SAIKYOU_ELEVEN_HADOU, P_10350HAKURYU, },
    {W_JUDGE_THROUGH_3, P_10205MAKARI, P_11201WANDABA, },
};


// we create a copy of the existing wazadef for the moves that we want to modify
// that copy is only used whenever we're in a function that's suppposed to look
// at the partners. we can overwrite the copy and extend the partner count that way !
WAZA_DEF* modified_waza_def = 0;

int get_extended_index(int move) {
    for (int i = 0; i < sizeof(extended_moves)/sizeof(ExtendedPartners); i++) {
        if (extended_moves[i].move == move)
            return i;
    }
    return -1;
}

WAZA_DEF* get_move_definition(int move) {
    int index = get_extended_index(move);
    if (index < 0)
        return GetMoveDef(move);
    return &modified_waza_def[index];
}

void create_new_waza_defs() {
    int n = sizeof(extended_moves)/sizeof(ExtendedPartners);
    OSReport("need to create %d additional wazadefs\n", n);
    modified_waza_def = (WAZA_DEF*) MEMAlloc(n*sizeof(WAZA_DEF), 32, 3, 31);
    
    for (int i = 0; i < n; i++) {
        OSReport("%x\n", modified_waza_def + i);
        OSReport("%x\n", &modified_waza_def[i].partners);
        memcpy(modified_waza_def + i, GetMoveDef(extended_moves[i].move), sizeof(WAZA_DEF));
        memcpy((char*)&(modified_waza_def[i].partners) + 20, &extended_moves[i].partners, 20); // add the additional partners
    }
}


// sel_move_type: 

// loading our own wazadef
kmWrite32(0x80074178, 0x807c9284); // lwz r4, -0x6D7C(r28) -> lwz r3, -0x6D7C(r28)
kmWrite32(0x8007417c, 0x837c9280); // lwz r0, -0x6d80(r28) -> lwz r27, -0x6d80(r28)
kmCall(0x80074180, get_move_definition);
kmWrite32(0x80074184, 0x2c1b0000); // cmpwi r0, 0 -> cmpwi r27, 0
kmWrite32(0x80074188, 0x7c7b1b78); // add r27, r3, r5 -> mr r27, r3

// change conditions to extend iteration count + check if early stop
kmBranchDefAsm(0x800741F8, 0x800741FC) {
    lha r0, 0x2E (r27)
    cmpwi r0, 0 // early stop if partner is zero
    beq end
    cmpwi r26, 0x14  // extend partner count
    end:
    blr

}
kmWrite32(0x800741FC, 0x4082ffd4); // change to a bne


// union_shoot_calc:

// get our new movedef
kmBranchDefAsm(0x800B1354, 0x800B1358) {
    nofralloc
    lwz r3, 4(r25)
    bl get_move_definition
    mr r15, r3
    blr
}

// change conditions
kmBranchDefAsm(0x800B13B0, 0x800B13B4) {
    lha r0, 0x2E (r15)
    cmpwi r0, 0 // early stop if partner is zero
    beq end
    cmpwi r16, 0x14  // extend partner count
    end:
    blr
}
kmWrite32(0x800B13B4, 0x4082ffa8); // change to a bne

// wazchkavailable:
// load new movedef
kmBranchDefAsm(0x800E2208, 0x800E220C) {
    nofralloc
    li r27, 0x8C
    divw r3, r23, r27
    bl get_move_definition
    mr r17, r3
    blr
}
kmWrite32(0x800E2264, 0x2c150014); // extend partner count

// match_make_waza_kind_list
// load new movedef
kmBranchDefAsm(0x8008D314, 0x8008D318) {
    nofralloc
    mr r3, r14
    bl get_move_definition
    mr r31, r3
    blr
}

kmWrite32(0x8008d54c, 0x2c140014); // extend partner count
kmWrite32(0x8008d3bc, 0x41820198); // early stop

// WAZGetUnited
kmWrite32(0x800E25A0, 0x2c140014); // extend partner count
kmBranchDefAsm(0x800E2404, 0x800E2408) {
    nofralloc
    lwz r3, 0x34(r1)
    bl get_move_definition
    mr r0, r3
    blr
}


// settingWazScenePlayerWindowOpPartnerByPageChange
// load new movedef
kmBranchDefAsm(0x8026e540, 0x8026e544) {
    nofralloc
    mr r3, r6
    bl get_move_definition
    mr r27, r3
    blr
}
kmWrite32(0x8026e760, 0x2c110014); // extend partner count
kmWrite32(0x8026E6B4, 0x408100b4); // early stop

// removePlayerIDOfWazMismatch
// load new movedef
kmBranchDefAsm(0x8026BFF4, 0x8026BFF8) {
    nofralloc
    mr r3, r4
    bl get_move_definition
    mr r30, r3
    blr
}
kmBranchDefAsm(0x8026C224, 0x8026C228) {
    nofralloc
    lwz r0, 0(r27)
    cmpwi r0, 0 // early stop if partner is zero
    beq end
    cmpwi r21, 0x14 // extend partner count
    end:
    blr
}
kmWrite32(0x8026c228, 0x4082ff54); // change to a bne

