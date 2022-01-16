#include <kamek.h>
#include <snd.h>
#include "music.h"

static int s_CurrentBgm = 0;
int bgmMax = sizeof(bgmNames) / sizeof(bgmNames[0]);

int getSndId(const char* defaultBgm) {
	if (s_CurrentBgm)
	{
		const char* bgm = bgmNames[s_CurrentBgm - 1];
		return wiiSndGetNameToID(bgm);
	}
	else return wiiSndGetNameToID(defaultBgm);
}

kmCall(0x80047288, getSndId);