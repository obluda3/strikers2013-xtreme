#ifndef SAVEDATA
#define SAVEDATA
#include "types.h"
// TODO : add the other functions
typedef struct KizunaData
{
	u16 value;
	u16 _8;
} KizunaData;

enum FlagPlayer
{
	MIXIMAX_LEVEL_ONE = 0x10,
	MIXIMAX_LEVEL_TWO = 0x20,
};

enum UnlockFlag
{
	UNLOCKED,
	LOCKED,
	RECRUITED
};

typedef struct SavePlayerData
{
	s32 Flag;
	s32 Unknown;
	u8 TP;
	u8 MaxTP;
	u8 Kick;
	u8 MaxKick;
	u8 Catch;
	u8 MaxCatch;
	u8 Body;
	u8 MaxBody;
	u8 Guard;
	u8 MaxGuard;
	u8 Control;
	u8 MaxControl;
	u8 Speed;
	u8 MaxSpeed;
	u8 _16;
	u8 _17;
	u8 _18;
	u8 _19;
	u8 _1A;
	u8 _1B;
	u8 _1C;
	u8 _1D;
	u8 _1E;
	u8 _1F;
	u8 _20;
	u8 _21;
	u8 _22;
	u8 _23;
	u8 kakusei;
	u8 _25;
	u8 _26;
	u8 _27;
	u8 _28;
	u8 _29;
	u8 _2A;
	u8 _2B;
	u8 _2C;
	u8 _2D;
	u8 _2E;
	u8 _2F;
	u8 _30;
	u8 _31;
	u8 _32;
	u8 _33;
	u8 _34;
	u8 _35;
	u8 _36;
	u8 _37;
	u8 _38;
	u8 _39;
	u8 _3A;
	u8 _3B;
} SavePlayerData;

int Savedata_GetSavedata_Emblem(int slot);
bool Savedata_ChkPlayerFlag(long player, long flagType);
bool Savedata_SetPlayerFlag(long player, long flagType, bool unk);
char* Savedata_GetSavedata_TeamName(int slot);
char* Savedata_GetSavedata_UserName(int slot);
int Savedata_GetSavedata_FaceIcon(int slot);
KizunaData* Savedata_getPlayeData_KizunaData(int player1, int player2);
SavePlayerData* Savedata_getPlayerData(int player);
#endif