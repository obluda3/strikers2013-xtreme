#include <types.h>
#include <menu_setting.h>
#define SETTING_MODE_CONST 0x71279610

int getSndId(const char* defaultBgm);
int updateCurrentBgm(int argToStatus);
void drawBgmName(int isSettingMode);
void SNDBgmPlay_Direct(int id);
void onlineDrawHook(CSprStudio* spriteStudio);
void resetMusic();
