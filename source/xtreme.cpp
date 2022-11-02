#include "xtreme.h"
#include "dolphinios.h"
#include "keyboard.h"
#include "music.h"
#include <enums.h>
#include <kamek.h>
#include <menu_setting.h>
#include <moves.h>
#include <shd_debug.h>

XtremeSettings Settings;
u8 *SaveFlag = (u8 *)0x805F912E;

void XtremeSettings::MusicLoop(int state, void *arg) {
  MENU_SETTING::CMenuSetting *menu = (MENU_SETTING::CMenuSetting *)arg;
  if (state == 2) {
    updateCurrentBgm(0);

    Settings.Exec();
    Settings.DrawMenu();

    if (IsButtonPushed_Cancel(0)) {
      Settings.Save();
      menu->tasks->Pop(0);
      menu->tasks->Push(MENU_SETTING::CMenuSetting::MenuSet0Loop, arg);
      menu->tasks->Push(MENU_SETTING::CMenuSetting::MenuSet4Out, arg);
      Settings.passAccepted = false;
      SNDSeSysCANCEL(-1);
    }
  }
}

int https_list[] = {
    0x80502B90, 0x805060d0, 0x805060e0, 0x80506350, 0x8050b7b0,
    0x8050b7d8, 0x8050b7fc, 0x8050b830, 0x8050b858, 0x8050b87c,
};
int domain_urls[] = {0x805033d8, 0x805039e0, 0x805045e0, 0x80505a45, 0x805064bd,
                     0x8050665f, 0x80506683, 0x8050669f, 0x80506743, 0x805068a1,
                     0x805076f4, 0x80507710, 0x80507731, 0x80507752, 0x80507774,
                     0x80507796, 0x805077b6, 0x805077d6, 0x805077f5, 0x80507818,
                     0x8050783d, 0x8050785b, 0x8050c201};
int update_urls[] = {0x8050b7b0, 0x8050b7d8, 0x8050b7fc,
                     0x8050b830, 0x8050b858, 0x8050b87c};
char *new_update_urls[] = {
    "http://nas.test.wiimmfi.de/ac", "http://nas.wiimmfi.de/ac",
    "http://nas.dev.wiimmfi.de/ac",  "http://nas.test.wiimmfi.de/pr",
    "http://nas.wiimmfi.de/pr",      "http://nas.dev.wiimmfi.de/pr"};

char security_patchA[] = {
    0x88, 0xA1, 0x00, 0x11, 0x28, 0x05, 0x00, 0x80, 0x41, 0x81, 0x00, 0x70,
    0x54, 0xE3, 0xC2, 0x1E, 0x54, 0xE0, 0x40, 0x0E, 0x81, 0x81, 0x00, 0x0C,
    0x3C, 0xA0, 0x5A, 0x00, 0xA0, 0xC1, 0x00, 0x12, 0x7C, 0x05, 0x60, 0x00,
    0x50, 0xE3, 0xC6, 0x3E, 0x50, 0xE0, 0x44, 0x2E, 0x7C, 0xC4, 0x46, 0x70,
    0x7C, 0x60, 0x03, 0x78, 0x60, 0x00, 0x00, 0x00};
char security_patchB[] = {
    0x38, 0xE0, 0x00, 0x04, 0x7D, 0x03, 0x3C, 0x2C, 0x55, 0x46, 0xC2, 0x1E,
    0x55, 0x40, 0x40, 0x0E, 0xA1, 0x21, 0x00, 0x12, 0x91, 0x01, 0x00, 0x0C,
    0x89, 0x01, 0x00, 0x11, 0x51, 0x46, 0xC6, 0x3E, 0x51, 0x40, 0x44, 0x2E,
    0x7D, 0x27, 0x46, 0x70, 0x28, 0x08, 0x00, 0x80, 0x38, 0xA0, 0x00, 0x04,
    0x7C, 0xC6, 0x03, 0x78, 0x51, 0x27, 0x42, 0x2E, 0x60, 0x00, 0x00, 0x00,
    0xB0, 0xE1, 0x00, 0x12, 0x54, 0xC0, 0x80, 0x3E, 0x41, 0x81, 0x00, 0x14};

bool s_is_wiimmfi_done = false;
bool s_is_text_done = false;

char *text_edits[] = {"ガンマ　×　ザナーク",
                      "白竜　×　孔明",
                      "フラン　×　くろいばら",
                      "ＳＡＲＵ　×　Ｓいでんし",
                      "黒の騎士団",
                      "エンシャントダーク",
                      "アンリミテッドシャイニング",
                      "稲妻KFC",
                      "エルドラドチーム01",
                      "エルドラドチーム02",
                      "エルドラドチーム03",
                      "クロノストーム",
                      "ザン",
                      "ガル",
                      "ギル",
                      "ツキガミの一族",
                      "ヴァンプティム",
                      "ジ・エグゼラー",
                      "アースイレブン",
                      "レジスタンスジャパン",
                      "ファイアードラゴン",
                      "ビッグウェイブス",
                      "シャムシール",
                      "マッハタイガー",
                      "ストームウルフ",
                      "サザナーライレブン",
                      "サンドリアスイレブン",
                      "ラトニークイレブン",
                      "ガードンイレブン",
                      "ファラム・ディーテ",
                      "イクサルフリート",
                      "ビッグバン",
                      "スーパーノヴァ",
                      "スペースランカーズ",
                      "ガードンイレブン"};

char NewMoveNames[6][50];
int go_moves[] = {W_SHIPPUU_DASH_B, W_THE_WALL_B};
int full_moves[] = {W_KING_FIRE_B, W_GIGANTIC_BOMB_B, W_MAJIN_THE_HAND_B,
                    W_BUTTOBI_PUNCH_ARMED_B};

static bool outdated_dolphin = false;
static int call_cnt = 0;

void OutdatedDolphinVersion() {
  if (outdated_dolphin) {
    u32 fg = 0xFFFFFFFF, bg = 0;
    char *message =
        "Unsupported Dolphin version. Use Dolphin 5.0-14795 or newer versions.";
    if (call_cnt < 2) {
      disp_zen(message, 0, 0, 100);
      call_cnt++;
    } else
      OSFatal(&fg, &bg, message);
  }
}

void CheckForDolphin() {
  if (Dolphin::IsOpen()) {
    char *versionName = Dolphin::GetVersion();
    int version;
    int subVersion;
    int revision;
    sscanf(versionName, "%d.%d-%d", &version, &subVersion, &revision);
    if (version == 5 && subVersion == 0 &&
        revision < 14795) // Cross-platform online desyncs were fixed in
                          // Dolphin 5.0-14795
    {
      outdated_dolphin = true;
    }
  }
  // We're either on a Wii or Dolphin pre 5.0-11186
  else {
    // https://github.com/TheLordScruffy/mkw-tournament-museum/blob/master/loader/loader.cpp
    int handle = IOS_Open("/title", 1);
    if (handle == -106)
      outdated_dolphin = true;
    IOS_Close(handle);
  }
}

void XtremeSettings::Init() {
  Dolphin::Init();
  u8 flag = *SaveFlag;
  Settings.allowOpenings = flag & 1;
  Settings.movePower = flag & 2;
  Settings.keyboardType = (flag >> 2) & 3;
  SwitchKeyboardLayout(Settings.keyboardType);

  // Init text edits
  if (!s_is_text_done) {
    char **maintext = *((char ***)0x805131C0);
    maintext[1675] = "ザナーク　×　クララジェーン";
    for (int i = 0; i < sizeof(text_edits) / sizeof(char *); i++) {
      maintext[i + 5640] = text_edits[i];
    }
    WazaInfo *moveInfo = *((WazaInfo **)0x8051EBD4);
    for (int i = 0; i < 2; i++) {
      WazaInfo *curMove = &moveInfo[go_moves[i]];
      int textIndex = curMove->MoveName;
      strncpy(NewMoveNames[i], maintext[textIndex], 50);
      strcat(NewMoveNames[i], "（ＧＯ）");
      int newTextIndex = 5640 + sizeof(text_edits) / sizeof(char *) + i;
      curMove->MoveName = newTextIndex;
      curMove->OtherName = newTextIndex;
      maintext[newTextIndex] = NewMoveNames[i];
      int test = curMove->MoveName;
      cprintf("%s \n", maintext[test]);
    }
    for (int i = 0; i < 4; i++) {
      WazaInfo *curMove = &moveInfo[full_moves[i]];
      int textIndex = curMove->MoveName;
      strncpy(NewMoveNames[i + 2], maintext[textIndex], 50);
      strcat(NewMoveNames[i + 2], "（Ｆ）");
      int newTextIndex = 5640 + sizeof(text_edits) / sizeof(char *) + i + 2;
      curMove->MoveName = newTextIndex;
      curMove->OtherName = newTextIndex;
      maintext[newTextIndex] = NewMoveNames[i + 2];
    }
    s_is_text_done = true;
  }

  if (!s_is_wiimmfi_done) {
    if (!memcmp((char *)domain_urls[0], "wiimmfi.de", strlen("wiimmfi.de"))) {
      s_is_wiimmfi_done = true;
    } else {
      // ToadKing/wiilauncher-nossl
      for (int i = 0; i < sizeof(https_list) / 4; i++) {
        char *cur = (char *)https_list[i];
        int len = strlen(cur);
        memmove(cur + 4, cur + 5, len - 5);
        cur[len - 1] = 0;
      }

      // wiidev/usbloadergx
      for (int i = 0; i < sizeof(domain_urls) / 4; i++) {
        char *cur = (char *)domain_urls[i];
        int len = strlen(cur);
        memcpy(cur, "wiimmfi.de", strlen("wiimmfi.de"));
        memmove(cur + strlen("wiimmfi.de"), cur + 16, len - 16);
        for (int i = 16 - strlen("wiimmfi.de"); i > 0; i--)
          cur[len - i] = 0;
      }

      for (int i = 0; i < sizeof(update_urls) / 4; i++) {
        char *cur = (char *)update_urls[i];
        char *newurl = new_update_urls[i];
        strcpy(cur, newurl);
      }
      s_is_wiimmfi_done = true;
    }
    memcpy((char *)0x80472A3C, security_patchA, 56);
    memcpy((char *)0x80472BD0, security_patchB, 72);

    strcpy((char *)0x8050bacc, "X-3-1");
  }
  CheckForDolphin();
}

void XtremeSettings::Save() {
  u8 flag = 0;
  flag |= (keyboardType << 2) & 12;
  flag |= allowOpenings;
  flag |= movePower << 1;
  *SaveFlag = flag;
}

void XtremeSettings::Exec() {
  u8 pos = m_pos;
  bool isPadUp = UtilitySato::isPad(0, UtilitySato::PAD_UP, UtilitySato::HELD);
  bool isPadDown =
      UtilitySato::isPad(0, UtilitySato::PAD_DOWN, UtilitySato::HELD);
  bool isPadLeft =
      UtilitySato::isPad(0, UtilitySato::PAD_LEFT, UtilitySato::HELD);
  bool isPadRight =
      UtilitySato::isPad(0, UtilitySato::PAD_RIGHT, UtilitySato::HELD);
  if (isPadDown)
    pos++;
  else if (isPadUp)
    pos--;
  if (pos > 2)
    pos = 0;
  else if (pos < 0)
    pos = 1;
  if (pos != m_pos) {
    m_pos = pos;
    SNDSeSysCLICK(-1);
  } else {
    if (!m_pos) {
      s8 openings = allowOpenings;
      if (isPadLeft)
        openings--;
      else if (isPadRight)
        openings++;

      if (openings < 0)
        openings = 1;
      else if (openings > 1)
        openings = 0;

      if (openings != allowOpenings) {
        allowOpenings = openings;
        SNDSeSysCLICK(-1);
      }
    } else if (m_pos == 1) {
      s8 keyboard = keyboardType;
      if (isPadLeft)
        keyboard--;
      else if (isPadRight)
        keyboard++;

      if (keyboard < 0)
        keyboard = 2;
      else if (keyboard > 2)
        keyboard = 0;
      if (keyboard != keyboardType) {
        keyboardType = keyboard;
        SwitchKeyboardLayout(keyboard);
        SNDSeSysCLICK(-1);
      }
    }
    if (m_pos == 2) {
      s8 values = movePower;
      if (isPadLeft)
        values--;
      else if (isPadRight)
        values++;

      if (values < 0)
        values = 1;
      else if (values > 1)
        values = 0;

      if (values != movePower) {
        movePower = values;
        SNDSeSysCLICK(-1);
      }
    }
  }

  /*
  if (isPadDown) m_yOff++;
  if (isPadUp) m_yOff--;
  if (isPadLeft) m_xOff--;
  if (isPadRight) m_xOff++;
  */
}

char *FlagToEng(int val) {
  if (val)
    return "< ON >";
  else
    return "< OFF >";
}

char *KeyboardType(int val) {
  if (val == KEY_LTN)
    return "< Latin >";
  else if (val == KEY_CRL)
    return "#x15< Кириллица >";
  return "< 日本語 >";
}
void XtremeSettings::DrawMenu() {
  char extendedMessage[100];
  char message[50];
  s32 currentBgm = g_CurrentBgm;
  if (currentBgm > 0)
    sprintf(message, "#P10#j#I1Music Track %03d", currentBgm);
  else if (currentBgm == 0)
    strcpy(message, "#P10#j#I1Default track");

  disp_zen(message, 255, 170, 100);

  // Draw setting options
  disp_zen("テーマソング", 225, 250, 90);
  disp_zen("キーボード", 225, 280, 90);
  disp_zen("威力数値", 225, 310, 90);
  disp_zen(KeyboardType(keyboardType), 575, 280, 90);
  disp_zen(FlagToEng(allowOpenings), 575, 250, 90);
  disp_zen(FlagToEng(movePower), 575, 310, 90);

  s32 y = 250 + 30 * m_pos;
  disp_zen("#j#=->", 155, y, 90);
}

kmBranch(0x800E5B74, OutdatedDolphinVersion);
kmBranch(0x8004208C, XtremeSettings::Init);
// supplement bug
kmWrite32(0x801558B8, 0x480000A0);