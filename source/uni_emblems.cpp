#include <emblems.h>
#include <kamek.h>
#include <shd_mem.h>
#define UNIFORM_COUNT sizeof(UniformDataTbl) / sizeof(UniformData)
#define EMBLEM_COUNT sizeof(EmblemDataTbl) / sizeof(EmblemData)

namespace MENU_TP_DATA {
UniformData UniformDataTbl[] = {
    {-1, E_RAIMON, 0, 0xFE3, 1},
    {-1, E_INAZUMA_JAPAN, 0, 0xFEA, 1},
    {-1, E_TEIKOKU_GAKUEN, 0, 0xFE4, 1},
    {-1, E_SHIN_TEIKOKU_GAKUEN, 0, 0xFF8, 1},
    {-1, E_ZEUS, 0, 0xFE5, 1},
    {-1, E_ALIEA_GAKUEN, 0, 0xFE7, 1},
    {-1, E_CHAOS, 0, 0xFE8, 1},
    {-1, E_GENESIS, 0, 0xFF1, 1},
    {-1, E_DIAMOND_DUST, 0, 0xFF2, 1},
    {-1, E_PROMINENCE, 0, 0xFF3, 1},
    {-1, E_GEMINI_STORM, 0, 0xFF4, 1},
    {-1, E_EPSILON, 0, 0xFF5, 1},
    {-1, E_DARK_EMPERORS, 0, 0xFE9, 1},
    {-1, E_NEO_JAPAN, 0, 0xFEB, 1},
    {-1, E_SEKAI_SENBATSU_KAI, 0, 0xFEC, 1},
    {-1, E_LITTLE_GIGANT, 0, 0xFF6, 1},
    {-1, E_ORPHEUS, 0, 0xFF7, 1},
    {-1, E_UNICORN, 0, 0xFF9, 1},
    {-1, E_THE_KINGDOM, 0, 0xFFA, 1},
    {-1, E_FIRE_DRAGONS, 0, 0xFFB, 1},
    {-1, E_KNIGHTS_OF_QUEEN, 0, 0xFFC, 1},
    {-1, E_THE_EMPERORS, 0, 0xFFD, 1},
    {-1, E_DARK_ANGELS, 0, 0xFED, 1},
    {-1, E_GIRLS_TEAM, 0, 0xFEF, 1},
    {-1, E_OGRE, 0, 0xFEE, 1},
    {-1, E_RAIMON_GO, 0, 0xFF0, 1},
    {-1, E_ZERO, 0, 0x1002, 1},
    {-1, E_TENMAS, 0, 0x1004, 1},
    {-1, E_PROTOCOL_OMEGA, 0, 0x1005, 1},
    {-1, E_KAKUMEI_SENBATSU, 0, 0x1006, 1},
    {-1, E_FIFTH_SECTOR, 0, 0x1007, 1},
    {-1, E_ZANARK_DOMAIN, 0, 0x1008, 1},
    {-1, E_DESTRUCTCHERS, 0, 0x1009, 1},
    {-1, E_SHINSEI_INAZUMA_JAPAN, 0, 0x100A, 1},
    {-1, E_INAZUMA_LEGEND_JAPAN, 0, 0x100B, 1},
    {-1, E_DRAGON_LINK, 0, 0x100C, 1},
    {-1, E_HAKUREN_GO, 0, 0x100D, 1},
    {-1, E_ARAKUMO_GAKUEN, 0, 0x100E, 1},
    {0, E_RAIMON_TRACKSUIT_GO, E_RAIMON_GO, 0x1003, 7},
    {0, E_RAIMON_TRACKSUIT, E_RAIMON, 0xFFF, 7},
    {0, E_INAZUMA_JAPAN_TRACKSUIT, E_INAZUMA_JAPAN, 0xFFE, 7},
    {P_10010TSURUGI, E_TSURUGI_SCHOOL, E_RAIMON_GO, 0x1001, 4},
    {P_2475KINO, E_AKI_B, E_RAIMON, 0x1000, 6},
    {P_2474HARUNA, E_HARUNA_B, E_RAIMON, 0x1000, 6},
    {P_2473NATSUMI, E_NATSUMI_B, E_RAIMON, 0x1000, 6},
    {P_3008HUYUKA, E_HUYUKA_B, E_RAIMON, 0x1000, 6},
    {P_10036AOI, E_AOI_B, E_RAIMON_GO, 0x1000, 6},
    {P_10037AKANE, E_AKANE_B, E_RAIMON_GO, 0x1000, 6},
    {P_11780SAN, E_SAN, E_DESTRUCTCHERS, 6451, 6},
};

EmblemData EmblemDataTbl[] = {
    {E_RAIMON, 0x103B, "GDS_emb_raimon"},
    {E_RAIMON_2, 0x1056, "GDS_emb_raimon2"},
    {E_INAZUMA_JAPAN, 0x103C, "GDS_emb_inazumajp"},
    {E_TEIKOKU_GAKUEN, 0x103D, "GDS_emb_teikoku"},
    {E_SHIN_TEIKOKU_GAKUEN, 0x103E, "GDS_emb_sinteikoku"},
    {E_ZEUS, 0x103F, "GDS_emb_zeus"},
    {E_ALIEA_GAKUEN, 0x1040, "GDS_emb_aliegakuen"},
    {E_CHAOS, 0x1041, "GDS_emb_chaos"},
    {E_GENESIS, 0x1042, "GDS_emb_genesis"},
    {E_DIAMOND_DUST, 0x1043, "GDS_emb_diamond"},
    {E_PROMINENCE, 0x1044, "GDS_emb_prominence"},
    {E_GEMINI_STORM, 0x1045, "GDS_emb_gemini"},
    {E_EPSILON, 0x1046, "GDS_emb_epsilon"},
    {E_DARK_EMPERORS, 0x1047, "GDS_emb_demperors"},
    {E_NEO_JAPAN, 0x1048, "GDS_emb_neojp"},
    {E_SEKAI_SENBATSU_KAI, 0x1049, "GDS_emb_sekaisen"},
    {E_LITTLE_GIGANT, 0x104A, "GDS_emb_littleg"},
    {E_ORPHEUS, 0x104B, "GDS_emb_orpheus"},
    {E_UNICORN, 0x104C, "GDS_emb_unicorn"},
    {E_THE_KINGDOM, 0x104D, "GDS_emb_kingdom"},
    {E_FIRE_DRAGONS, 0x104E, "GDS_emb_firedragon"},
    {E_KNIGHTS_OF_QUEEN, 0x104F, "GDS_emb_knights"},
    {E_THE_EMPERORS, 0x1050, "GDS_emb_empire"},
    {99, 5674, "GDS_emb_germany"},
    {100, 5675, "GDS_emb_france"},
    {101, 5676, "GDS_emb_spain"},
    {E_DARK_ANGELS, 0x1051, "GDS_emb_darkangel"},
    {E_GIRLS_TEAM, 0x1052, "GDS_emb_girls"},
    {E_OGRE, 0x1053, "GDS_emb_ogre"},
    {E_RAIMON_GO, 0x1054, "GDS_emb_raimon3"},
    {83, 5644, "GDS_emb_kurokishidan"},
    {73, 5645, "GDS_emb_ancientdark"},
    {74, 5646, "GDS_emb_unlimitedshining"},
    {E_ZERO, 0x1055, "GDS_emb_zero"},
    {E_TENMAS, 0x1064, "GDS_emb_tenmas"},
    {E_PROTOCOL_OMEGA, 0x1065, "GDS_emb_protocolomega"},
    {E_KAKUMEI_SENBATSU, 0x105D, "GDS_emb_kakumeisenbatsu"},
    {E_FIFTH_SECTOR, 0x1057, "GDS_emb_fifthsectors"},
    {E_ZANARK_DOMAIN, 0x1069, "GDS_emb_zanacdomain"},
    {E_DESTRUCTCHERS, 0x106A, "GDS_emb_destructures"},
    {E_SHINSEI_INAZUMA_JAPAN, 0x106C, "GDS_emb_shinnihon"},
    {E_INAZUMA_LEGEND_JAPAN, 0x106B, "GDS_emb_otonanihon"},
    {E_DRAGON_LINK, 0x105C, "GDS_emb_dragonlink"},
    {E_HAKUREN_GO, 0x105F, "GDS_emb_hakuren"},
    {E_ARAKUMO_GAKUEN, 0x1062, "GDS_emb_arakumo"},
    {E_SHIROSHIKA, 0x1070, "GDS_emb_shiroshikagumi"},
    {E_MIKAGE_SENNOU, 0x106E, "GDS_emb_mikagesennou"},
    {E_KIDOKAWA_SEISHUU, 0x1060, "GDS_emb_kidokawa"},
    {E_TEAM_GARSHIELD, 0x106F, "GDS_emb_teamgarushirudo"},
    {97, 5647, "GDS_emb_kfc"},
    {E_AKIZORA_CHALLENGERS, 0x106D, "GDS_emb_akizora"},
    {E_PROTOCOL_OMEGA_A, 0x1066, "GDS_emb_protocolomega1"},
    {E_PROTOCOL_OMEGA_B, 0x1067, "GDS_emb_protocolomega2"},
    {E_PROTOCOL_OMEGA_C, 0x1068, "GDS_emb_protocolomega3"},
    {E_GENEI_GAKUEN, 0x1061, "GDS_emb_geneigakuen"},
    {E_SEIDOUZAN, 0x1063, "GDS_emb_seidouzan"},
    {E_TEIKOKU_GAKUEN_GO, 0x105A, "GDS_emb_goteikoku"},
    {E_MANNOUZAKA, 0x1059, "GDS_emb_mannouzaka"},
    {E_AMAKAWA, 0x1058, "GDS_emb_tengawara"},
    {E_EITO_GAKUEN, 0x105B, "GDS_emb_kaiou"},
    {E_GASSAN_KUNIMITSU, 0x105E, "GDS_emb_gassankunimitsu"},
    {E_PERFECT_CASCADE, 0x1071, "GDS_emb_pcascade"},
    {88, 5648, "GDS_emb_eldorado1"},
    {86, 5649, "GDS_emb_eldorado2"},
    {85, 5650, "GDS_emb_eldorado3"},
    {92, 5651, "GDS_emb_chronostorm"},
    {90, 5652, "GDS_emb_zan"},
    {70, 5653, "GDS_emb_garu"},
    {89, 5654, "GDS_emb_giru"},
    {E_RAGNA, 0x1072, "GDS_emb_lagoon"},
    {77, 5655, "GDS_emb_tsukigami"},
    {78, 5656, "GDS_emb_vamptym"},
    {95, 5657, "GDS_emb_excellar"},
    {75, 5658, "GDS_emb_eartheleven"},
    {82, 5659, "GDS_emb_resistance"},
    {81, 5660, "GDS_emb_firedragon2"},
    {96, 5661, "GDS_emb_bigwaves"},
    {98, 5662, "GDS_emb_shamushiru"},
    {71, 5663, "GDS_emb_machtiger"},
    {69, 5664, "GDS_emb_stormwolf"},
    {80, 5665, "GDS_emb_sazaanara"},
    {72, 5666, "GDS_emb_sandorius"},
    {79, 5667, "GDS_emb_ratoniik"},
    {84, 5668, "GDS_emb_flem"},
    {87, 5669, "GDS_emb_faram"},
    {76, 5670, "GDS_emb_ixal"},
    {91, 5671, "GDS_emb_bigbang"},
    {93, 5672, "GDS_emb_supernova"},
    {94, 5673, "GDS_emb_spacerankers"},
};

EmblemData *newGetEmblemData(int index) {
  if (index >= 0 && index < EMBLEM_COUNT)
    return &EmblemDataTbl[index];
  return 0;
}

EmblemData *newGetEmblemDataFromTeam(int team) {
  for (int i = 0; i < EMBLEM_COUNT; i++) {
    EmblemData *current = &EmblemDataTbl[i];
    if (current->Emblem == team)
      return current;
  }
  return 0;
}

bool newIsUniformNoPositionFromTeam(int uniform) {
  int count = sizeof(UniformDataTbl) / sizeof(UniformData);
  for (int i = 0; i < count; i++) {
    if (UniformDataTbl[i].Uniform == uniform)
      return (UniformDataTbl[i]._10 >> 2) & 1;
  }
  return 0;
}

bool newIsUniformNoHomeAwayFromTeam(int uniform) {
  int count = sizeof(UniformDataTbl) / sizeof(UniformData);
  for (int i = 0; i < count; i++) {
    if (UniformDataTbl[i].Uniform == uniform)
      return (UniformDataTbl[i]._10 >> 1) & 1;
  }
  return 0;
}

UniformData *newGetUniformData(int index) {
  if (index < 0 || index >= (sizeof(UniformDataTbl) / sizeof(UniformData))) {
    return 0;
  } else {
    return &UniformDataTbl[index];
  }
}
kmBranch(0x80286218, newIsUniformNoHomeAwayFromTeam);
kmBranch(0x802861d0, newGetUniformData);
kmBranch(0x802862f4, newIsUniformNoHomeAwayFromTeam);
kmBranch(0x802863D0, newGetEmblemData);
kmBranch(0x802863FC, newGetEmblemDataFromTeam);

// Makes it so added uniforms are unlocked by default
kmWrite32(0x8004311C, 0x38600001);
kmWrite32(0x801E0B1C, 0x2c1b0000 + UNIFORM_COUNT); // cmpwi r27, UNIFORM_COUNT
kmWrite32(0x8026B0E4, 0x2C1C0000 + UNIFORM_COUNT); // cmpwi r28, UNIFORM_COUNT
kmWrite32(0x8023F230, 0x2C1E0000 + EMBLEM_COUNT);
} // namespace MENU_TP_DATA

static char emblemList[0x600];

// Struct patching
// expand the emblem menu
asm void makeEmblemList() {
  stwu r1, -0x10(r1)
  mflr r0
  stw r0, 0x8(r1)
  lis r3, emblemList@ha
  addi r3, r3, emblemList@l
  lwz r12, -0x6900(r13)
  stw r3, 0x54(r12)
  lwz r0, 0x8(r1)
  mtlr r0
  addi r1, r1, 0x10
  blr
}

kmBranch(0x8023ED9C, makeEmblemList);

asm void loadCustomStruct() {
  nofralloc
  lwz r12, -0x6900(r13)
  lwz r0, 0x54(r12)
  blr  
}

asm void loadCustomStruct2() {
  nofralloc
  mtctr r5 // restore
  lwz r3, 0x54(r3)
  blr
}

asm void loadCustomStruct3() {     
  nofralloc
  lwz r3, 0x54(r5)
  add r3, r3, r0
  blr  
}

asm void loadCustomStruct4() {
  nofralloc
  mr r12, r5
  lwz r5, 0x54(r5)
  add r4, r5, r0
  mr r5, r12
  blr
}

asm void loadCustomStruct5() { 
  nofralloc
  lwz r3, 0x54(r3)
  add r3, r3, r0
  blr  
}

asm void loadCustomStruct6() {
  nofralloc
  lwz r5, 0x54(r5)
  add r5, r5, r0
  blr
}

kmCall(0x8023F1DC, loadCustomStruct);
kmCall(0x8023F1F8, loadCustomStruct);
kmCall(0x8023F218, loadCustomStruct);
kmCall(0x8023F228, loadCustomStruct);
kmCall(0x8023F294, loadCustomStruct2);
kmCall(0x8023F6E0, loadCustomStruct3);
kmCall(0x8023F4A8, loadCustomStruct5);
kmCall(0x8023F740, loadCustomStruct4);
kmCall(0x8023F428, loadCustomStruct6);
kmWrite32(0x8023F1C8, 0x38600001);