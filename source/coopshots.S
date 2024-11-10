#include <kamek_asm.S>
.extern shdCalLen2dSQ__FPfPf
.extern OSReport
.extern WAZIsKeshinGroup__Fi
.extern WAZIsKeshinArmed__Fi
.set saikyoeleven, 0x197

remove_distance_check:
  stwu r1, -0x10(r1)
  mflr r0
  stw r0, 0x14(r1)
  li r3, 0
  fsub f1, f1, f1
  lwz r3, 4(r25) // move
  cmpwi r3, saikyoeleven
  beq normal_calculation
  bl WAZIsKeshinGroup__Fi
  beq normal_calculation
  bl WAZIsKeshinArmed__Fi
  beq normal_calculation
  b epilogue
  normal_calculation:
  addi r3, r23, 8
  addi r4, r26, 8
  bl shdCalLen2dSQ__FPfPf
  epilogue:
  lwz r0, 0x14(r1)
  addi r1, r1, 0x10
  mtlr r0
  blr

kmCall 0x800B13CC, remove_distance_check