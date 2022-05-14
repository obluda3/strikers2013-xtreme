#ifndef INAST_PLY
#define INAST_PLY

#include "types.h"
#include "enums.h"

enum Position
{
    GK = 0x0,
    DF = 0x23,
    MF = 0x24,
    FW = 0x25,
};
enum TacticalAction
{
    Feint = 0x14,
    Roll = 0x15,
    Short = 0x16,
    Jump = 0x17,
    White_Sprint = 0x18,
    Red_Sprint = 0x19,
    Loop = 0x1A,
};
enum Gender
{
    Male = 0x0,
    Female = 0x1,
};
enum Bodytype
{
    Man = 0x0,
    Large = 0x1,
    Chibi = 0x2,
    Muscle = 0x3,
    Girl1 = 0x4,
    Girl2 = 0x5,
};
struct PLAYER_DEF
{
    PlayerIds id;
    u32 rMatchIndex;
    u32 hiddenName;
    u32 shortName;
    u32 fullName;
    char name[24];
    Gender gender;
    u32 idleAnimation;
    u32 field_34;
    u32 description;
    Bodytype bodytype;
    u32 scale;
    u32 shadowRadius;
    TacticalAction tacticalAction;
    u32 courseAnimation;
    u32 team;
    u32 emblem;
    u32 teamPortrait;
    Position position;
    u32 matchFaceModel;
    u32 faceModel;
    u32 faceModel2;
    s32 bodyModel;
    s32 bodyModel2;
    u32 _74;
    u32 portrait;
    u32 _7C;
    u32 lBattlePortrait;
    u32 rBattlePortrait;
    u32 _88;
    u32 _8C;
    char field_90[8];
    char field_98[8];
    char field_A0[8];
    char field_A8[8];
    char field_B0[8];
    char field_B8[8];
    char field_C0[8];
    char field_C8[8];
    char field_D0[8];
    char field_D8[8];
    char field_E0[8];
    u32 neckLegColor;
    u32 armKneeColor;
    u32 unkId;
    u32 element;
    u32 chargeProfile;
    u32 _FC;
    u32 _100;
    u32 voice;
    u32 _108;
    u32 _10C;
    s16 price;
    u16 listPos;
    u32 otherListPos;
    int someFlag;
    u32 _11C;
    u32 _120;
    u32 _124;
    u32 _128;
    u32 _12C;
    u32 _130;
    u32 _134;
    u32 _138;
    u32 _13C;
    u32 kakusei;
    u16 kakuseiIndex;
    u16 rMiximaxPlaId;
};


#endif