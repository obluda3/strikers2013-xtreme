#ifndef UTILITY_SATO
#define UTILITY_SATO
#include "types.h"

namespace UtilitySato 
{
	enum PADSTATE { PAD_STATE0, PAD_STATE1, PAD_STATE2 };
	bool isManager(u32 id);
	bool isKantoku(u32 id);
	void setFrameRate(bool is60);
	bool isWideMonitor();
	bool is43Monitor();
	int getScreenSizeX();
	int getScreenSizeY();
	int getScreenSizeRateX();
	int getScreenSizeRateY();
	int getScreenWide34OffSet();
	int getScreenWide43AutoOffSet();
	int isPad(s32 id, s32 mask, PADSTATE state);
}

#endif