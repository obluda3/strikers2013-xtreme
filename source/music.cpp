#include <kamek.h>
#include <snd.h>
#include <buttonhelpers.h>
#include <savedata.h>
#include <text.h>
#include <shd_debug.h>
#include <utilitysato.h>
#include "music.h"


// #b84#=もどる #b83#=けってい #b87#=ルールせってい #b88#=そうさ #b85#I1#=Previous track #b86#=Next track 
// but apparently SJIS doensn't exist!
static char s_HelpbarText_SP[] = { 0x23, 0x62, 0x38, 0x34, 0x23, 0x3d, 0x82, 0xe0, 0x82, 0xc7, 0x82, 0xe9, 0x20, 0x23, 0x62, 0x38, 0x33, 0x23, 0x3d, 0x82, 0xaf, 0x82, 0xc1, 0x82, 0xc4, 0x82, 0xa2, 0x20, 0x23, 0x62, 0x38, 0x37, 0x23, 0x3d, 0x83, 0x8b, 0x81, 0x5b, 0x83, 0x8b, 0x82, 0xb9, 0x82, 0xc1, 0x82, 0xc4, 0x82, 0xa2, 0x20, 0x23, 0x62, 0x38, 0x38, 0x23, 0x3d, 0x82, 0xbb, 0x82, 0xa4, 0x82, 0xb3, 0x20, 0x23, 0x49, 0x31, 0x23, 0x62, 0x38, 0x36, 0x23, 0x3d, 0x50, 0x72, 0x65, 0x76, 0x69, 0x6f, 0x75, 0x73, 0x20, 0x74, 0x72, 0x61, 0x63, 0x6b, 0x20, 0x23, 0x62, 0x38, 0x35, 0x23, 0x3d, 0x4e, 0x65, 0x78, 0x74, 0x20, 0x74, 0x72, 0x61, 0x63, 0x6b, 0x00 };
// #b84#=もどる #b83#=けってい #I1#b85#=Next track #b86#=Previous track
static char s_HelpbarText_Wifi_a[] = { 0x23, 0x62, 0x38, 0x34, 0x23, 0x3d, 0x82, 0xe0, 0x82, 0xc7, 0x82, 0xe9, 0x20, 0x23, 0x62, 0x38, 0x33, 0x23, 0x3d, 0x82, 0xaf, 0x82, 0xc1, 0x82, 0xc4, 0x82, 0xa2, 0x20, 0x23, 0x62, 0x38, 0x33, 0x23, 0x3d, 0x82, 0xaf, 0x82, 0xc1, 0x82, 0xc4, 0x82, 0xa2, 0x20, 0x23, 0x62, 0x38, 0x37, 0x23, 0x3d, 0x83, 0x8b, 0x81, 0x5b, 0x83, 0x8b, 0x82, 0xb9, 0x82, 0xc1, 0x82, 0xc4, 0x82, 0xa2, 0x20, 0x23, 0x62, 0x38, 0x38, 0x23, 0x3d, 0x82, 0xbb, 0x82, 0xa4, 0x82, 0xb3, 0x20, 0x23, 0x49, 0x31, 0x23, 0x62, 0x38, 0x36, 0x23, 0x3d, 0x50, 0x72, 0x65, 0x76, 0x69, 0x6f, 0x75, 0x73, 0x20, 0x74, 0x72, 0x61, 0x63, 0x6b, 0x20, 0x23, 0x62, 0x38, 0x35, 0x23, 0x3d, 0x4e, 0x65, 0x78, 0x74, 0x20, 0x74, 0x72, 0x61, 0x63, 0x6b, 0x00 };
// #b83#=けってい #I1#b85#=Next track #b86#=Previous track
static char s_HelpbarText_Wifi_b[] = { 0x23, 0x62, 0x38, 0x33, 0x23, 0x3d, 0x82, 0xaf, 0x82, 0xc1, 0x82, 0xc4, 0x82, 0xa2, 0x20, 0x23, 0x62, 0x38, 0x33, 0x23, 0x3d, 0x82, 0xaf, 0x82, 0xc1, 0x82, 0xc4, 0x82, 0xa2, 0x20, 0x23, 0x62, 0x38, 0x37, 0x23, 0x3d, 0x83, 0x8b, 0x81, 0x5b, 0x83, 0x8b, 0x82, 0xb9, 0x82, 0xc1, 0x82, 0xc4, 0x82, 0xa2, 0x20, 0x23, 0x62, 0x38, 0x38, 0x23, 0x3d, 0x82, 0xbb, 0x82, 0xa4, 0x82, 0xb3, 0x20, 0x23, 0x49, 0x31, 0x23, 0x62, 0x38, 0x36, 0x23, 0x3d, 0x50, 0x72, 0x65, 0x76, 0x69, 0x6f, 0x75, 0x73, 0x20, 0x74, 0x72, 0x61, 0x63, 0x6b, 0x20, 0x23, 0x62, 0x38, 0x35, 0x23, 0x3d, 0x4e, 0x65, 0x78, 0x74, 0x20, 0x74, 0x72, 0x61, 0x63, 0x6b, 0x00 };
static char s_HelpbarText_Sett[] = { 0x23, 0x62, 0x38, 0x34, 0x23, 0x3d, 0x82, 0xe0, 0x82, 0xc7, 0x82, 0xe9, 0x20, 0x23, 0x49, 0x31, 0x23, 0x62, 0x38, 0x36, 0x23, 0x3d, 0x50, 0x72, 0x65, 0x76, 0x69, 0x6f, 0x75, 0x73, 0x20, 0x74, 0x72, 0x61, 0x63, 0x6b, 0x20, 0x23, 0x62, 0x38, 0x35, 0x23, 0x3d, 0x4e, 0x65, 0x78, 0x74, 0x20, 0x74, 0x72, 0x61, 0x63, 0x6b, 0x00 };
static char ***s_MainTexts = (char***)0x805131C0;
u16* IsMusicOn = (u16*)0x80904212;

const char* bgmNames[] = { 
	"BGM_TGS_BATTLE01",
	"BGM_TGS_BATTLE02",
	"BGM_TGS_BATTLE03",
	"BGM_TGS_BATTLE04",
	"BGM_TGS_BATTLE05",
	"Teikoku",
	"BGM_GAME_NORMAL_01",
	"BGM_GAME_NORMAL_02",
	"BGM_HERO_TIME_02",
	"BGM_HERO_TIME_01",
	"BGM_OTHER_01",
	"BGM_OTHER_02",
	"BGM_OTHER_03",
	"BGM_OTHER_04",
	"BGM_OTHER_05",
	"BGM_OTHER_06",
	"BGM_GO_TRACK05",
	"BGM_GO_TRACK06",
	"BGM_GO_TRACK14",
	"BGM_GO_TRACK29",
	"BGM_TGS_TITLE2",
	"BGM_TGS_RESULT",
	"BGM_INA3_D01_WORLDCUP_2MIX",
	"BGM_INA3_D03_TEAM_UK2_2MIX",
	"BGM_INA3_D04_TEAMUSA1_2MIX",
	"BGM_INA3_D05_TEAMUSA2_2MIX",
	"BGM_INA3_D09_CHINA_2MIX",
	"BGM_INA3_D11_TEAMEU2_2MIX",
	"BGM_INA3_D12_ZENNIPPON_2MIX",
	"BGM_INA3_D13_SHINHISSATSUWAZA",
	"BGM_INA3_D14_HISSATSUWAZA2_2MIX",
	"BGM_OGRE_M39",
	"BGM_OGRE_M46",
	"BGM_ST1_05_RAIMONCHU_1",
	"BGM_ST1_06_RAIMONCHU_2",
	"BGM_ST1_09_DENSETSU_NO_INAZUMA_ELEVEN",
	"BGM_ST1_11_TEIKOKU_GAKUEN_THEME_1",
	"BGM_ST1_12_TEIKOKU_GAKUEN_THEME_2",
	"BGM_ST1_13_TEIKOKU_GAKUENE_TONO_SHITOU",
	"BGM_ST1_14_IKE_RAIMONCHU",
	"BGM_ST1_17_HOUKAGO_NO_RAKUEN",
	"BGM_ST1_22_ENJIN",
	"BGM_ST1_23_YARUKI_NO_NAI_BUIN",
	"BGM_ST1_24_KYOUI_NO_HISSATSUWAZA",
	"BGM_ST1_28_KAZE_TO_SEISHUN",
	"BGM_ST1_29_YAROUZE_SOCCER",
	"BGM_ST2_05_TAIYOU_NI_MUKATTE",
	"BGM_ST2_07_YUGRE_NO_TETTOU",
	"BGM_ST2_10_NATSUMI_OJOUSAMA",
	"BGM_ST2_11_NANIWA_LAND",
	"BGM_ST2_15_PITCH_NO_TODOROKI",
	"BGM_ST2_17_MOUHITORI_NO_ACE_STRIKER",
	"BGM_ST2_19_KESSHI_NO_KOUGEKI",
	"BGM_ST2_20_KOKORO_NO_CHIKAI",
	"BGM_ST2_26_KUROI_SOCCER_BALL",
	"BGM_ST2_27_GALS_NO_THEME",
	"BGM_ST2_29_SHITOU",
	"BGM_ST2_30_HOSHI_NO_SHITO",
	"BGM_INA3_D07_ASIA2_2MIX",
	"BGM_MINNAATSUMARI_YO_TD_FULL",
	"BGM_ST2_25_TAIKETSU",
	"BGM_GO_TRACK02",
	"BGM_GO_TRACK05",
	"BGM_GO_TRACK06",
	"BGM_GO_TRACK14",
	"BGM_GO_TRACK29",
	"BGM_GO_TRACK36",
	"BGM_GO_ZERO",
	"BGM_ENDING",
	"BGM_M24_25MIX",
	"BGM_M28_SHIROSHIKAGUMI_2MIX",
	"BGM_M00_NICHIJYO_2MIX",
	"BGM_M12_TENMAS2_MASTER_01",
	"BGM_M25_TOKKUN_2MIX",
	"BGM_M07_PROTOCOLOMEGA4_2MIX",
	"BGM_M14_TENMAS4_2MIX",
	"BGM_M23_KIKI_MASTER_01",
	"BGM_M24_BATTLE1_MASTER_01",
	"BGM_M30_DEADFUTURE_TOUNAMENT_MASTER_01",
	"BGM_01_KOGARASHI_SOU_NO_ASA",
	"BGM_02_RAIMON_SOCCER_BU",
	"BGM_14_SINSEI_RAIMON_SOCCER_BU",
	"BGM_16_TAIKAI_KAIMAKU",
	"BGM_17_YOAKE",
	"BGM_18_HIRU_YASUMI",
	"BGM_19_IEJI",
	"BGM_22_SHOURI_WO_TSUKAME",
	"BGM_23_YUJO",
	"BGM_25_ISSHOKU_SHOKUHATSU",
	"BGM_28_MYSTERIOUS",
	"BGM_32_HOLY_ROAD_WO_TSUKISUSUME",
	"BGM_33_KESHIN_TSUKAI",
	"BGM_34_GOAL_HE",
	"BGM_39_HAJOU_KOUGEKI",
	"BGM_M11_UNLIMITED_SHINING_2_2MIX",
	"BGM_M23_TEMMA_NO_YASASHISA_2MIX",
	"BGM_M28_TOKKUN2_2MIX",
	"BGM_M43_ENDO_NO_HISSATSUWAZA_2MIX",
	"BGM_M44_SHOURI_2MIX",
	"BGM_38_TACHIAGARE_INAZUMA_ELEVEN",
	"BGM_M17MIX",
	"BGM_M18MIX",
	"BGM_T15_MASTER",
	"BGM_M31_FRAN_NO_IKARI",
	"BGM_M34_FRAN1_MASTER",
	"BGM_M36_FRAN2_MASTER",
};
static int s_CurrentBgm = 0;
static bool s_OneTimeChange = false;

const int bgmMax = sizeof(bgmNames) / sizeof(bgmNames[0]);

int getSndId(const char* defaultBgm) 
{
	if (s_CurrentBgm)
		return wiiSndGetNameToID(bgmNames[s_CurrentBgm - 1]);
	return wiiSndGetNameToID(defaultBgm);
}

int updateCurrentBgm(int argBak) 
{
	if(!s_OneTimeChange) // changes the helpbar text
	{
		char** mainTexts = *s_MainTexts;
		mainTexts[858] = s_HelpbarText_SP;
		mainTexts[530] = s_HelpbarText_Wifi_a;
		mainTexts[531] = s_HelpbarText_Wifi_b;
		mainTexts[532] = s_HelpbarText_Sett;
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
		// if (s_CurrentBgm)
		//	cprintf("New music: %s\n", bgmNames[s_CurrentBgm - 1]);
		
		int id = getSndId("BGM_M12_TENMAS2_MASTER_01"); 
		SNDBgmPlay_Direct(id);
		SNDSeSysOK(-1);
	}
	return IsButtonPushed_OK(argBak); // default inst
}

s16 rainbowColors[] = { 
	8700,
	8840,
	8880,
	8480,
	8271,
	8174,
	8276,
	8137,
	8317,
	8617,
	8716,
};

static int s_frameCount = 0;
#define FRAME_PER_COLOR 7
void drawBgmName(int isSettingMode)
{
	char message[50];
	int currentBgm = s_CurrentBgm;

	if (currentBgm > 0)
		sprintf(message, "#j#I1Music Track %03d", currentBgm);
	else if (currentBgm == 0)
	{
		strcpy(message, "#j#I1Default track");
	}
	else
	{
		strcpy(message, "#j#I1Random track");
	}
	if (isSettingMode == SETTING_MODE_CONST) {
		char extendedMessage[100];
		int clrIndex = s_frameCount / FRAME_PER_COLOR;

		sprintf(extendedMessage, "#c%04d", rainbowColors[clrIndex]);
		strcat(extendedMessage, message);

		disp_zen(extendedMessage, 200, 220, 100);
		s_frameCount++;
		if (s_frameCount >= FRAME_PER_COLOR * (sizeof(rainbowColors) / sizeof(u16)))
		{
			s_frameCount = 0;
		}
	}
	else
		disp_zen(message, 20, 20, 65);
}

void SNDBgmPlay_Direct(int id)
{
	if (*IsMusicOn)
		shdBgmLoad(0, id, *IsMusicOn, 1);
	else
		shdBgmStop(0);
}

void onlineDrawHook(CSprStudio* spriteStudio)
{
	spriteStudio->Draw();
	drawBgmName(0);
}

void resetMusic()
{
	s_CurrentBgm = 0;
}



kmCall(0x80047288, getSndId);
kmCall(0x8010DB88, updateCurrentBgm);
kmCall(0x8025CE40, updateCurrentBgm);
kmBranch(0x8025CB1C, onlineDrawHook);
kmBranch(0x8010E8D4, drawBgmName);
kmBranch(0x8011D608, resetMusic);


// changes helpbar text in online menu
kmWrite32(0x8025CE4C, 0x3B800212);
kmWrite32(0x8025CE60, 0x3b800213);