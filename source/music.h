#include <types.h>
#include <menu_setting.h>
#define SETTING_MODE_CONST 0x71279610

extern int g_CurrentBgm;
int updateCurrentBgm(int argToStatus);
void drawBgmName();
void SNDBgmPlay_Direct(int id);
void SNDSePlay_Direct(int id, int volLeft, int volRight);
void onlineDrawHook(CSprStudio* spriteStudio);
void resetMusic();
void initBgmPlayer();
void parsePlaylistFile(u8* data, int size);