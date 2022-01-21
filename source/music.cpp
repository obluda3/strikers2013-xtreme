#include <kamek.h>
#include <snd.h>
#include <buttonhelpers.h>
#include <text.h>
#include <utilitysato.h>
#include "music.h"

static int s_CurrentBgm = 0;
const int bgmMax = sizeof(bgmNames) / sizeof(bgmNames[0]);

int getSndId(const char* defaultBgm) 
{
	if (s_CurrentBgm)
	{
		const char* bgm = bgmNames[s_CurrentBgm - 1];
		return wiiSndGetNameToID(bgm);
	}
	else return wiiSndGetNameToID(defaultBgm);
}

int updateCurrentBgm(int argToStatus) 
{
	int currentBgm = s_CurrentBgm;
	if (IsButtonPushed_Ready(0)) // +
	{
		currentBgm++;
	}
	else if (UtilitySato::isPad(0, 0x1000, UtilitySato::PAD_STATE1)) // -
	{
		currentBgm--;
	}
	
	if (currentBgm < 0) currentBgm = bgmMax;
	if (currentBgm > bgmMax) currentBgm = 0;

	s_CurrentBgm = currentBgm;
	return IsButtonPushed_Status(argToStatus); // default inst
}

void drawBgmName()
{
	char message[30];
	int currentBgm = s_CurrentBgm;

	if (currentBgm)
		sprintf(message, "#j#I1Music Track %03d", currentBgm);
	else
		strcpy(message, "#j#I1Default track");
	
	disp_zen(message, 20, 20, 65);
}

kmCall(0x80047288, getSndId);
kmCall(0x8010DC10, updateCurrentBgm);
kmBranch(0x8010E8D4, drawBgmName);