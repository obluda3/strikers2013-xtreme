#pragma once
#include <enums.h>

namespace MENU_TP_DATA {
struct UniformData {
  s32 User;
  u32 Uniform;
  u32 Emblem;
  u32 TextEntry;
  u8 _10;
};
struct EmblemData {
  u32 Emblem;
  u32 TextEntry;
  char *Name;
};

struct TeamOrgData {
  int teamId;
  int _04;
};

void Initialize();
void GetTeamSortPriority(u32 a1);
void GetTeamOrgData(u32 a1);
void GetUniformData(u32 index);
int IsUniformNoHomeAwayFromTeam(s32 uniform);
int IsUniformNoPositionFromTeam(s32 uniform);
int GetTeamOrgEmblemID(const TeamOrgData* team);
}  // namespace MENU_TP_DATA

int GetTeamIDToEmblemLL(int teamId);