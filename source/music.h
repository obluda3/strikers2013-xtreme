#include <types.h>

int getSndId(const char* defaultBgm);
int updateCurrentBgm(int argToStatus);
void drawBgmName();
void SNDBgmPlay_Direct(int id);

u16* IsMusicOn = (u16*)0x80904212;

const char* bgmNames[] = { 
	"BGM_TGS_BATTLE01",
	"BGM_TGS_BATTLE02",
	"BGM_TGS_BATTLE03",
	"BGM_TGS_BATTLE04",
	"BGM_TGS_BATTLE05",
	"BGM_TGS_TITLE",
	"JINGLE_TGS_VS",
	"InazumaTheme",
	"Jingle1",
	"Jingle2",
	"Jingle3",
	"Jingle4",
	"Jingle5",
	"Jingle6",
	"Jingle7",
	"Jingle7_Loop",
	"Jingle9",
	"Jingle10",
	"Jingle11",
	"Jingle13",
	"Jingle14",
	"Jingle15_Win",
	"Jingle16_Lose",
	"Jingle17_Loop",
	"Teikoku",
	"BGM_GAME_NORMAL_01",
	"BGM_GAME_NORMAL_02",
	"BGM_HERO_TIME_02",
	"BGM_HERO_TIME_01",
	"JINGLE_GOAL_01",
	"BGM_OTHER_01",
	"BGM_OTHER_02",
	"BGM_OTHER_03",
	"BGM_OTHER_04",
	"BGM_OTHER_05",
	"BGM_OTHER_06",
	"BGM_OTHER_07",
	"BGM_GO_TRACK05",
	"BGM_GO_TRACK06",
	"BGM_GO_TRACK14",
	"BGM_GO_TRACK29",
	"BGM_TGS_TITLE2",
	"BGM_TGS_RESULT",
	"JINGLE_TGS_PRE_BATTLE",
	"BGM_MINIGAME_CARAVAN",
	"BGM_MINIGAME_TIRE_PUNCH",
	"BGM_MINIGAME_WALL_PASS",
	"BGM_MINIGAME_TIRE_PULL",
	"BGM_MINIGAME_GUM_BELT",
	"BGM_MINIGAME_MENU",
	"BGM_MINIGAME_TUTORIAL",
	"BGM_MINIGAME_RECORD",
	"JINGLE_MINIGAME_CLEAR",
	"BGM_MINIGAME_RESULT",
	"BGM_INA3_D01_WORLDCUP_2MIX",
	"BGM_INA3_D03_TEAM_UK2_2MIX",
	"BGM_INA3_D04_TEAMUSA1_2MIX",
	"BGM_INA3_D05_TEAMUSA2_2MIX",
	"BGM_INA3_D09_CHINA_2MIX",
	"BGM_INA3_D11_TEAMEU2_2MIX",
	"BGM_INA3_D12_ZENNIPPON_2MIX",
	"BGM_INA3_D13_SHINHISSATSUWAZA",
	"BGM_INA3_D14_HISSATSUWAZA2_2MIX",
	"BGM_JINGLE_EX01_JINGLE_2MIX",
	"BGM_JINGLE_INA3_J02",
	"BGM_JINGLE_INA3_J21",
	"BGM_JINGLE_INA3_J21_CHAPTER",
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
	"JINGLE_VICTORY",
	"BGM_APPLAUSE",
	"BGM_OWN_GOAL",
	"BGM_OWN_GOAL_2",
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
	"BGM_J_02",
	"BGM_J_05",
	"BGM_J_07",
	"BGM_J_08",
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
	"BGM_M36_FRAN2_MASTER" 
};