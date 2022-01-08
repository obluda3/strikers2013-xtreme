#ifndef INAST_MOVES
#define INAST_MOVES
#include "enums.h"
#include "types.h"
enum Tier
{
	Lv1 = 0x0,
	Lv2 = 0x1,
	Lv3 = 0x2,
	SP = 0x3,
};
enum Status
{
	Normal = 0x0,
	Long = 0x1,
	ShootBlock = 0x2,
	Chain = 0x3,
	Punch1 = 0x4,
	Punch2 = 0x5,
};
typedef struct waza_info
{
	u16 tier;
	u16 basePower;
	u16 maxPower;
	u16 tp;
	Element element;
	Status status;
	u16 radius;
	u16 _E;
	u16 _10;
	u16 _12;
	u16 coopPlayerCount;
	u16 _16;
	u16 _18;
	u16 users[10];
	u16 partners[10];
	u16 _42;
	u16 _44;
	u16 _46;
	u16 _48;
	u16 _4A;
	u16 _4C;
	u16 descriptionIndex;
	u16 _50;
	u16 _52;
	u16 _54;
	u16 usersIndex;
	u16 _58;
	u16 _5A;
	u16 _5C;
	u16 _5E;
	u16 _60;
	u16 _62;
	u16 _64;
	u16 _66;
	u16 _68;
	u16 _6A;
	u16 _6C;
	u16 _6E;
	u16 _70;
	u16 _72;
	u16 _74;
	u16 _76;
	u16 _78;
	u16 _7A;
	u16 _7C;
	u16 _7E;
	u16 _80;
	u16 _82;
	u16 _84;
	u16 powerUpIndicator;
	u16 invocationAnimTime;
	u16 _8A;
} WAZA_INFO;

bool WAZIsMiximax(int id);
bool WAZIsKeshinArmed(int id);
bool WAZIsKeshinGroup(int id);


#endif