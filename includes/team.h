#pragma once
#include <types.h>

struct TEAM_PLAYER {
  s16 id;
  s16 kitNumber;
  s32 formationIndex;
  s32 statsIndex;
  s32 kakusei;
  s32 flag;
  s32 mainPortrait;
  s32 leftPortrait;
  s32 rightPortrait;
  s16 lvl1Shoot;
  s16 lvl2Shoot;
  s16 lvl3Shoot;
  s16 dribble;
  s8 _2A[6];
  s16 defense;
  s8 _32[6];
  s16 lvl1catch;
  s16 lvl2catch;
  s16 lvl3catch;
  s16 pad;
  s16 spShoot;
};

struct TEAM_DEF {
  char* name;
  int teamIndex;
  s16 formation;
  s16 coach;
  s16 manager;
  s16 strength;
  TEAM_PLAYER* players;
  s32 additionnalData; // pointer
};
TEAM_DEF* getTeamDef(int a1, int a2);