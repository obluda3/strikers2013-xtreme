#include <kamek.h>
#include <mix.h>
#include <moves.h>

struct BanMove{
  s16 player;
  s16 move;
  u8 needsMiximax;
} ;

static BanMove BanList[] = {{P_12803TEMMA, W_PEGASUS_BREAK, false},
                            {P_12813TEMMA, W_PEGASUS_BREAK, false},
                            {P_12803TEMMA, W_OU_NO_TSURUGI, false},
                            {P_12813TEMMA, W_BLACK_ASH_MIXI_MAX, false},
                            {P_12815ZANAKU, W_GREAT_MAX_NA_ORE, false},
                            {P_12816SZANAKU, W_SHINKUUMA_MIXI_MAX, false},
                            {P_12013FUEI, W_OUJA_NO_KIBA, false},
                            {P_12809FUEI, W_KODAI_NO_KIBA, false},
                            {P_12813TEMMA, W_WONDER_TRAP_ARMED, false},
                            {-1, -1}};

static BanMove WhiteListMix[] = {
    {P_12813TEMMA, W_SAIKYOU_ELEVEN_HADOU, false},
    {P_12803TEMMA, W_WONDER_TRAP_ARMED, false},
    {P_12817SARU, W_MORTAL_SMASH, false},
    {P_12492FURAN, W_CHAOS_METEOR_UNUSED, true},
    {P_10444RINNO, W_NORMAL_DRIBBLE_JUMP, false},
    {P_12330SARU, W_MORTAL_SMASH, true},
    {P_10008MATSUKAZE, W_WONDER_TRAP_ARMED, true},
    {P_10008MATSUKAZE_TNM, W_WONDER_TRAP_ARMED, true},
    {-1, -1}};

static BanMove WhiteListReg[] = {{P_10249MAHORO, W_ILLUSION_BALL, false},
                                 {P_12009DORIRU, W_ILLUSION_BALL, false},
                                 {P_1092DOMON, W_KILLER_SLIDE, false},
                                 {P_12803TEMMA, W_WONDER_TRAP, false},
                                 {P_12009DORIRU, W_KILLER_SLIDE, false},
                                 {-1, -1}};

bool IsAllowedRegular(s32 isFound, s32 player, s32 move) {
  if (isFound)
    return 1;
  for (BanMove *ban = WhiteListReg; ban->player != -1; ban++) {
    if (ban->player == player && ban->move == move)
      return 1;
  }
  return 0;
}

bool IsLockedMiximax(u32 move, register u32 player, register u32 isMiximax) {
  asm("mr player, r22");
  asm("mr isMiximax, r24");
  for (BanMove *ban = BanList; ban->player != -1; ban++) {
    if (ban->player == player && ban->move == move &&
        (ban->needsMiximax == isMiximax == true))
      return true;
  }
  for (BanMove *ban = WhiteListMix; ban->player != -1; ban++) {
    if (ban->player == player && ban->move == move &&
        (ban->needsMiximax == isMiximax == true))
      return 0;
  }
  if (WAZIsMiximax(move) && !IsMiximaxPlayer(player, 0))
    return true;
  return false;
}

kmCall(0x800F8D44, IsLockedMiximax);
kmBranchDefAsm(0x800F8D38, 0x800F8D3C){
  nofralloc
  mr r3, r0
  mr r4, r22
  mr r5, r26
  bl IsAllowedRegular
  mr r0, r3
  cmpwi r0, 0
  blr
}

kmBranchDefAsm(0x800F8D74, 0x800F8D78) {
  nofralloc
  cmpwi r28, W_WONDER_TRAP_ARMED * 0x8C
  beq end
  li r0, W_MORTAL_SMASH
  mulli r0, r0, 0x8C
  cmpw r28, r0
  beq end
  cmpwi r24, 0
  end:
  blr
}

asm void MixedSpFix(){
  nofralloc
  cmpwi r8, W_SPARK_EDGE_DRIBBLE_ARMED
  beq end
  cmpwi r8, W_WONDER_TRAP_ARMED
  beq end
  cmpwi r8, W_MORTAL_SMASH
  beq end
  end:
  blr
}

kmCall(0x800F9A34, MixedSpFix);
kmCall(0x800F9A64, MixedSpFix);
kmCall(0x800F9A98, MixedSpFix);
kmCall(0x800F9AC8, MixedSpFix);
