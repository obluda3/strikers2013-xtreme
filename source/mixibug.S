// Remove old miximax release check and replace with own
// The bug happens because of the fact that contests aren't handled properly
// So the wrong miximax ends up being released in some cases
// The game tries to predict if the player is going to lose its miximax after their move ends
// However we could check it the other way, and wait until the move's end before checking
#include <kamek_asm.S>
.extern MI_chkMixiTime__FP6_PWORK
.extern MI_getInazmaPoint__FUc
.extern ResetMiximaxPlayerDef__FP6_PWORK
.extern ResetMiximaxPlayerDef2__FP6_PWORK
.extern GetPLYIDToPlayerEntryTeam__Fii
.extern MP_after_scene__Fi
.set WazaData, 0x807ACE4C

check_miximax_release: // (_PWORK* player, int gaugeReduction)
  stwu r1, -0x10(r1)
  mflr r0
  stw r0, 0x14(r1)
  stw r31, 0x8(r1)
  mr r31, r3
  bl MI_chkMixiTime__FP6_PWORK 
  cmpwi r3, 1
  bne epilogue
  lbz r3, 0x82(r31) // player->matchIdx
  bl MI_getInazmaPoint__FUc
  cmpwi r3, 0
  bgt epilogue
  mr r3, r31
  bl ResetMiximaxPlayerDef__FP6_PWORK
  mr r3, r31
  bl ResetMiximaxPlayerDef2__FP6_PWORK 
  lhz r3, 0x44(r31)
  lbz r4, 0x2E(r31)
  bl GetPLYIDToPlayerEntryTeam__Fii
  lis r0, 0x80
  lwz r31, 0x118(r3) // flag
  or r31, r31, r0
  stw r31, 0x118(r3)
  epilogue:
  lwz r0, 0x14(r1)
  lwz r31, 0x8(r1)
  mtlr r0
  addi r1, r1, 0x10
  blr

check_miximax_users_release:
  stwu r1, -0x10(r1)
  mflr r0
  stw r0, 0x14(r1)
  stw r31, 0x8(r1)
  lis r31, WazaData@ha
  addi r31, r31, WazaData@l
  lwz r3, 0(r31) // WazaData->user
  bl check_miximax_release
  lwz r3, 4(r31) // WazaData->opponent
  bl check_miximax_release
  lwz r3, -0x6cb0(r13) // g_nSceneType
  bl MP_after_scene__Fi
  lwz r31, 0x8(r1)
  lwz r0, 0x14(r1)
  mtlr r0
  addi r1, r1, 0x10
  blr



//kmWrite32 0x8009C47C, 0x60000000
//kmWrite32 0x8009C48C, 0x60000000
//kmWrite32 0x8008C054, 0x60000000
//kmWrite32 0x8008C038, 0x60000000

//kmCall 0x8008D010, check_miximax_users_release