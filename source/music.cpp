#include <kamek.h>
#include <snd.h>
#include <buttonhelpers.h>
#include <text.h>
#include <shd_debug.h>
#include <utilitysato.h>
#include "music.h"

// #b84#=もどる #b83#=けってい #b87#=ルールせってい #b88#=そうさ #b85#=Next track #b86#=Previous track 
// but apparently SJIS doensn't exist!
static char s_HelpbarText[] = { 0x23, 0x62, 0x38, 0x34, 0x23, 0x3d, 0x82, 0xe0, 0x82, 0xc7, 0x82, 0xe9, 0x20, 0x23, 0x62, 0x38, 0x33, 0x23, 0x3d, 0x82, 0xaf, 0x82, 0xc1, 0x82, 0xc4, 0x82, 0xa2, 0x20, 0x23, 0x62, 0x38, 0x37, 0x23, 0x3d, 0x83, 0x8b, 0x81, 0x5b, 0x83, 0x8b, 0x82, 0xb9, 0x82, 0xc1, 0x82, 0xc4, 0x82, 0xa2, 0x20, 0x23, 0x62, 0x38, 0x38, 0x23, 0x3d, 0x82, 0xbb, 0x82, 0xa4, 0x82, 0xb3, 0x20, 0x23, 0x49, 0x31, 0x23, 0x62, 0x38, 0x36, 0x23, 0x3d, 0x50, 0x72, 0x65, 0x76, 0x69, 0x6f, 0x75, 0x73, 0x20, 0x74, 0x72, 0x61, 0x63, 0x6b, 0x20, 0x23, 0x62, 0x38, 0x35, 0x23, 0x3d, 0x4e, 0x65, 0x78, 0x74, 0x20, 0x74, 0x72, 0x61, 0x63, 0x6b, };
static char ***s_MainTexts = (char***)0x805131C0;

static int s_CurrentBgm = 0;
static bool s_OneTimeChange = false;
const int bgmMax = sizeof(bgmNames) / sizeof(bgmNames[0]);

int getSndId(const char* defaultBgm) 
{
	if (s_CurrentBgm)
		return wiiSndGetNameToID(bgmNames[s_CurrentBgm - 1]);
	return wiiSndGetNameToID(defaultBgm);
}

int updateCurrentBgm(int argToStatus) 
{
	if(!s_OneTimeChange) // one time change
	{
		char** mainTexts = *s_MainTexts;
		mainTexts[858] = s_HelpbarText;
		s_OneTimeChange = true;
	}

	int currentBgm = s_CurrentBgm;
	bool changed = false;

	if (IsButtonPushed_Ready(0)) // +
	{
		currentBgm++;
		changed = true;
	}
	else if (UtilitySato::isPad(0, 0x1000, UtilitySato::PAD_STATE1)) // -
	{
		currentBgm--;
		changed = true;
	}
	
	if (currentBgm < 0) currentBgm = bgmMax;
	if (currentBgm > bgmMax) currentBgm = 0;

	s_CurrentBgm = currentBgm;
	if (changed)
	{
		int id = getSndId("BGM_M12_TENMAS2_MASTER_01"); 
		SNDBgmPlay_Direct(id);
		SNDSeSysOK(-1);
	}
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

void SNDBgmPlay_Direct(int id)
{
	if (*IsMusicOn)
		shdBgmLoad(0, id, *IsMusicOn, 1);
	else
		shdBgmStop(0);
}

kmCall(0x80047288, getSndId);
kmCall(0x8010DC10, updateCurrentBgm);
kmBranch(0x8010E8D4, drawBgmName);