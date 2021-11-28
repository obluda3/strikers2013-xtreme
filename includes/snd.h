#ifndef SND
#define SND

void SNDInit();
void SNDSetDefVolume();
void SNDBgmPlay(s32 index, s32 unk);
void SNDBgmPlayTitle();
void SNDBgmPlaySavedata();
void SNDBgmPlayRoom(s32 unk);
void SNDBgmStopRoom();
void SNDBgmStopRoomIBox();
void SNDBgmPlayMainMenu();
void SNDBgmPlayField(u8 play);
void SNDBgmPlayHerotime(u8 play);
void SNDBgmPlayGameSet();
void SNDBgmPlayTournament(s32 unk);
void SNDBgmPlayGameSettingRally();
void SNDBgmPlayGameSettingBstTokkun();
void SNDBgmPlayOpposingGame();
void SNDBgmPlayGoal();
void SNDBgmPlayOwnGoal();
void SNDBgmPlayResult();
void SNDBgmPlayPK();
void SNDBgmPlayPKSelect();
void SNDBgmPlayPKResult();
void SNDBgmPlayKizunaResultBstTokkun();
void SNDBgmPlayKizunaResultBstSyugyo();
void SNDBgmPlayWazaZukan(s32 unk);
void SNDBgmStopWazaZukan(s32 unk);
void SNDBgmPlayCaravan(s32 unk);
void SNDBgmStop(s32 unk);
void SNDBgmFadeOut(s32 unk1, s32 unk2);
void SNDUnloadSEGrp();
void SNDSeSysOK(int unk);
void SNDSeSysOK2();
// TODO: add the other functions




#endif