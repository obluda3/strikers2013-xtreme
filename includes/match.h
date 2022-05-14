#ifndef TEAM
#define TEAM
#include "players.h"
#include "file.h"

struct UserPwork
{
  u8 field_0;
  u8 shootType;
  s8 field_2;
  s8 field_3;
  f32 field_4;
  f32 field_8;
  u32 field_C;
  f32 position[3];
  u8 notCatchingBall;
  u8 field_1D;
  u8 field_1E;
  u8 field_1F;
  u32 effect;
};

struct ChargeData
{
  u32 idle;
  u32 holdingball;
  u32 pass;
  u32 normalShoot;
  u32 normalCatch;
  u32 goal;
  u32 recGoal;
  u32 tackle;
  u32 field_20;
  u32 tackle_opponent;
  u32 tackle_opponent2;
  u32 field_2C;
  u32 field_30;
  u32 field_34;
  u32 field_38;
  u32 field_3C;
  u32 tacticalActOpp;
  u32 tacticalAct;
  u32 tacticalActOpp2;
  u32 throughPass;
  u32 direct;
  u32 cross;
  u32 volley;
  u32 field_5C;
};
struct _PWORK
{
    u32 guid;
    u32 field_4;
    f32 position[3];
    f32 gapC;
    f32 field_18;
    f32 field_1C;
    f32 facingAngle;
    f32 field_24;
    f32 field_28;
    s8 field_2C;
    s8 index;
    s8 team;
    u32 field_30;
    u16 field_34;
    u16 field_36;
    u32 field_38;
    u32 field_3C;
    u32 field_40;
    u16 id;
    u16 field_46;
    f32 field_48;
    s8 field_4C;
    s8 field_4D;
    u8 element;
    u8 gap4F[5];
    u32 field_54;
    u32 field_58;
    u32 field_5C;
    u32 field_60;
    u32 field_64;
    u32 field_68;
    u32 field_6C;
    ChargeData *chargeData;
    u32 field_74;
    u32 field_78;
    u32 field_7C;
    u8 curTeam;
    u8 teamIdx;
    u8 matchIdx;
    u8 field_83;
    s8 field_84;
    s8 field_85;
    s8 field_86;
    s8 field_87;
    f32 field_88;
    f32 field_8C;
    f32 field_90;
    u32 field_94;
    f32 gkFlames;
    u32 field_9C;
    u32 field_A0;
    u32 field_A4;
    u32 field_A8;
    u32 state;
    u32 field_B0;
    u32 dashAnimFrame;
    UserPwork field_B8;
    u32 field_DC;
    u32 field_E0;
    f32 field_E4;
    u32 field_E8;
    u32 field_EC;
    u32 field_F0;
    u32 field_F4;
    u32 field_F8;
    u32 field_FC;
};

union MatchSetting
{
    struct Settings
    {
        u32 _0;
        u32 _4;
        u32 _8;
        u8 _C;
        u8 _D;
        u8 _E;
        u8 _F;
    } settings;
    u8 unk[0x10d];
};

struct TEAM_DEF{};
TEAM_DEF* getTeamDef(int a1, int a2);
_PWORK* get_gk_pw(u8 team);
void  SetTeamDefToBody(PLAYER_DEF *player, int isFieldPlayer, int a3, const TEAM_DEF* teamDef);
PLAYER_DEF* GetPLYIDToPlayerEntryTeam(s32 player, s32 team);
u32 GetPLYIDToIndex(u32 player, u32 team);
PLAYER_DEF* GetPLYIDToPlayerEntry(u32 player, u32 unk);
u32 GetPLYIDToListID(s32 id, s32 unk);
// TODO: add other functions to make this file useful

#endif