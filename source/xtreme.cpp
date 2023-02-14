#include "xtreme.h"

#include <enums.h>
#include <kamek.h>
#include <menu_setting.h>
#include <moves.h>
#include <players.h>
#include <shd_debug.h>

#include "discord.h"
#include "dolphinios.h"
#include "keyboard.h"
#include "music.h"
#include "xtutils.h"

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
      Settings.passAccepted = false;
      SNDSeSysCANCEL(-1);
    }
  }
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
  if (isPadDown) pos++;
  else if (isPadUp) pos--;
  if (pos > 2) pos = 0;
  else if (pos < 0) pos = 2;
  if (pos != m_pos) {
    m_pos = pos;
    SNDSeSysCLICK(-1);
  } else {
    if (!m_pos) {
      s8 openings = allowOpenings;
      if (isPadLeft) openings--;
      else if (isPadRight) openings++;
      if (openings < 0) openings = 1;
      else if (openings > 1) openings = 0;

      if (openings != allowOpenings) {
        allowOpenings = openings;
        SNDSeSysCLICK(-1);
      }
    } else if (m_pos == 1) {
      s8 keyboard = keyboardType;
      if (isPadLeft) keyboard--;
      else if (isPadRight) keyboard++;

      if (keyboard < 0) keyboard = 2;
      else if (keyboard > 2) keyboard = 0;
      if (keyboard != keyboardType) {
        keyboardType = keyboard;
        SwitchKeyboardLayout(keyboard);
        SNDSeSysCLICK(-1);
      }
    }
    if (m_pos == 2) {
      s8 values = movePower;
      if (isPadLeft) values--;
      else if (isPadRight) values++;

      if (values < 0) values = 1;
      else if (values > 1) values = 0;
      if (values != movePower) {
        movePower = values;
        SNDSeSysCLICK(-1);
      }
    }
  }
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
        revision < 14795)  // Cross-platform online desyncs were fixed in
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

int go_moves[] = {W_SHIPPUU_DASH_B, W_THE_WALL_B};
int full_moves[] = {W_KING_FIRE_B, W_GIGANTIC_BOMB_B, W_MAJIN_THE_HAND_B, W_BUTTOBI_PUNCH_ARMED_B};

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
                      "ガードンイレブン",
                      "ブロッケンボーグ",
                      "ローズグリフォン",
                      "レッドマタドール",
            
                      };

char *premixed_descs[] = {
    "フェイがティラノサウルスのオーラでミキシマックスした#R荒々(あらあら)しい#R姿(すがた)。",
    "#R優一(ゆういち)が#R弟(おとうと)の#R京介(きょうすけ)とミキシマックスした#R姿(すがた)。#R兄弟(きょうだい)なので#R相性(あいしょう)バツグン#R力(ちから)がみなぎる。",
    "#R天馬(てんま)とシュウがミキシマックスした#R姿(すがた)。#R２人(ふたり)の#R固(かた)い#R絆(きずな)が#R力(ちから)を#R増幅(ぞうふく)させている。",
    "#R神童(しんどう)と#R信長(のぶなが)がミキシマックスした#R姿(すがた)。#R人(ひと)と#R大局(たいきょく)を#R見抜(みぬ)く#R真実(しんじつ)のゲームメーカー。",
    "#R霧野(きりの)とジャンヌがミキシマックスした#R姿(すがた)。#R仲間(なかま)の#R勇気(ゆうき)を#R奮(ふる)いたたせるカリスマＤＦ。",
    "#R太陽(たいよう)と#R孔明(こうめい)がミキシマックスした#R姿(すがた)。#R未来(みらい)をも#R見通(みとお)し#R敵(てき)を#R突(つ)く#R正確無比(せいかくむひ)のＭＦ。",
    "#R信助(しんすけ)と#R劉備(りゅうび)がミキシマックスした#R姿(すがた)。#R強靭(きょうじん)な#R行動力(こうどうりょく)と#R実行力(じっこうりょく)を#R持(も)つ#R鉄壁(てっぺき)のＧＫ。",
    "トーブとトーチャンがミキシマックス。#R自由自在(じゆうじざい)に#R空(そら)を#R制(せい)するフライングＤＦ。",
    "フェイとビッグがミキシマックスした#R姿(すがた)。#R太古(たいこ)の#R力(ちから)を#R宿(やど)したダイナミックＭＦ。",
    "#R錦(にしき)と#R坂本(さかもと)#R龍馬(りょうま)がミキシマックスした#R姿(すがた)。#R攻守(こうしゅ)をつなぐスーパートリッキーＭＦ。",
    "#R剣城(つるぎ)と#R沖田(おきた)がミキシマックスした#R姿(すがた)。#R雷(いかずち)の#R如(ごと)き#R電光石火(でんこうせっか)のスピードストライカー。",
    "#R黄名子(きなこ)とドラゴンがミキシマックスした#R姿(すがた)。すべてをこなすファンタジックリベロ。",
    "#R天馬(てんま)とアーサー#R王(おう)がミキシマックスした#R姿(すがた)。 #R絶対的(ぜったいてき)な#R勇気(ゆうき)を#R持(も)ったキングオブＭＦ。",
    "ザナークと#R曹操(そうそう)がミキシマックスした#R姿(すがた)。まさに#R最強最悪(さいきょうさいあく)の#R組(く)み#R合(あ)わせだといえる。",
    "ザナークが#R台風(たいふう)とミキシマックスした#R姿(すがた)。#R自称(じしょう)『スーパーザナーク』とのことだ。",
    "#R戦(たたか)いを#R憎(にく)む#R心(こころ)がフランの#R姿(すがた)を#R変(か)える。その#R姿(すがた)はまさに#R黒(くろ)い#R魔女(まじょ)のようだ…。",
    "ＳＡＲＵの#R遺伝子(いでんし)に#R眠(ねむ)る#R力(ちから)が#R目覚(めざ)めたくましい#R大猿(おおざる)のような#R姿(すがた)になった。"};

int premixed_list[] = {
    P_12013FUEI,
    P_12802TSURUGI,
    P_12803TEMMA,
    P_12804SHINDO,
    P_12805KIRINO,
    P_12806AMEMIYA,
    P_12807SHINSUKE,
    P_12808TOBU,
    P_12809FUEI,
    P_12810NISHIKI,
    P_12811TSURUGI,
    P_12812KINAKO,
    P_12813TEMMA,
    P_12815ZANAKU,
    P_12816SZANAKU,
    P_12502YOBI,
    P_12817SARU};

struct URL_Patch {
  u32 address;
  char *text;
};

URL_Patch new_server[] = {
    {0x80502B90, "http://"},
    {0x805060d0, "http://"},
    {0x805060e0, "http://"},
    {0x80506350, "http://"},
    {0x805064b0, "inazumafrance.fr:2201"},
    {0x80506894, "inazumafrance.fr:2201"},
};

int domain_urls[] = { 0x805033d8, 0x805039e0, 0x805045e0, 0x80505a45,
                     0x8050665f, 0x80506683, 0x8050669f, 0x80506743, 0x805068a1,
                     0x805076f4, 0x80507710, 0x80507731, 0x80507752, 0x80507774,
                     0x80507796, 0x805077b6, 0x805077d6, 0x805077f5, 0x80507818,
                     0x8050783d, 0x8050785b, 0x8050c201};
int update_urls[] = {0x8050b7b0, 0x8050b7d8, 0x8050b7fc,
                     0x8050b830, 0x8050b858, 0x8050b87c};
char *new_update_urls[] = {
    "http://nas.test.inazumafrance.fr/ac", "http://nas.inazumafrance.fr/ac",
    "http://nas.dev.inazumafrance.fr/ac", "http://nas.test.inazumafrance.fr/pr",
    "http://nas.inazumafrance.fr/pr", "http://nas.dev.inazumafrance.fr/pr"};

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

bool s_is_online_done = false;
bool s_is_text_done = false;

char NewMoveNames[6][50];

void XtremeSettings::Init() {
  OSReport("Initializing /dev/dolphin driver... ");
  Dolphin::Init();
  OSReport("\n");
  OSReport("Initializing Discord Rich Presence...\n");
  Discord::Init();
  u8 flag = *SaveFlag;
  Settings.allowOpenings = flag & 1;
  Settings.movePower = flag & 2;
  Settings.keyboardType = (flag >> 2) & 3;
  SwitchKeyboardLayout(Settings.keyboardType);
  // Init text edits
  if (!s_is_text_done) {
    char **maintext = *((char ***)0x805131C0);
    maintext[1675] = "ザナーク　×　クララジェーン";
    maintext[587] = "Change Xtreme's additional settings";
    maintext[529] = "Xtreme settings";
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
    for (int i = 0; i < sizeof(premixed_list) / 4; i++) {
      int textIndex = 5640 + sizeof(text_edits) / sizeof(char *) + i + 2 + 4;
      PLAYER_DEF *player = GetPlayerDef(premixed_list[i]);
      player->description = textIndex;
      maintext[textIndex] = premixed_descs[i];
    }
    s_is_text_done = true;
  }

  if (!s_is_online_done) {
      for (int i = 0; i < sizeof(new_server) / sizeof(URL_Patch); i++) {
        URL_Patch* cur = &new_server[i];
        strcpy((char*)cur->address, cur->text);
      }
      for (int i = 0; i < sizeof(domain_urls) / 4; i++) strcpy((char*)domain_urls[i], "inazumafrance.fr");
      for (int i = 0; i < sizeof(update_urls) / 4; i++) strcpy((char*)update_urls[i], new_update_urls[i]);
      s_is_online_done = true;
  }
  memcpy((char *)0x80472A3C, security_patchA, 56);
  memcpy((char *)0x80472BD0, security_patchB, 72);

  strcpy((char *)0x8050bacc, "X-3-1");
  CheckForDolphin();
}
  

kmBranch(0x800E5B74, OutdatedDolphinVersion);
kmBranch(0x80044E3C, XtremeSettings::Init);
// supplement bug
kmWrite32(0x801558B8, 0x480000A0);