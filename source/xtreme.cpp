#include "xtreme.h"

#include <enums.h>
#include <kamek.h>
#include <menu_setting.h>
#include <moves.h>
#include <players.h>
#include <shd_debug.h>
#include <nhttp.h>
#include <shd_mem.h>

#include "discord.h"
#include "xtremeSettings.h"
#include "dolphinios.h"
#include "partners.h"
#include "keyboard.h"
#include "music.h"
#include "xtutils.h"

Xtreme Mod;
u8 *SaveFlag = (u8 *)0x805F912E;

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

void Xtreme::CheckForDolphin() {
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
                      "ガーディアンシールド",
                      "ガーディアンシールド（Ｆ）"
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
    "ＳＡＲＵの#R遺伝子(いでんし)に#R眠(ねむ)る#R力(ちから)が#R目覚(めざ)めたくましい#R大猿(おおざる)のような#R姿(すがた)になった。",
	"白竜と孔明がミキシマックスした姿。未来をも見通し敵を突く正確無比のMF。",
	"パーフェクト・カスケイドのキャプテン。その正体はサカマキが作ったアンドロイド。",
	"ザナークに強制ミキシマックスされた姿。身も心も洗脳され従順になってしまった。"};
	
	

int premixed_list[] = { P_12013FUEI, P_12802TSURUGI, P_12803TEMMA, P_12804SHINDO, P_12805KIRINO, P_12806AMEMIYA, P_12807SHINSUKE, P_12808TOBU, P_12809FUEI, P_12810NISHIKI, P_12811TSURUGI, P_12812KINAKO, P_12813TEMMA, P_12815ZANAKU, P_12816SZANAKU, P_12502YOBI, P_12817SARU, P_10444RINNO, P_11780SAN_MAN, P_10443OKAZEYA };

struct URL_Patch {
  u32 address;
  char *text;
};

URL_Patch so_server[] = {
    {0x80502B90, "http://"},
    {0x805060d0, "http://"},
    {0x805060e0, "http://"},
    {0x80506350, "http://"},
    
    {0x805064b0, "inazumafrance.fr:2201"},
    {0x80506894, "inazumafrance.fr:2201"},
    {0x80507724, "inazumafrance.fr:2201"},
    {0x80507744, "inazumafrance.fr:2201"},
    {0x8050780B, "inazumafrance.fr:2201"},
    {0x8050782F, "inazumafrance.fr:2201"},
    {0x8050C1F3, "inazumafrance.fr:2201"}
};

URL_Patch wiimmfi_server[] = {
  {0x80502B90, "http://"},
  {0x805060d0, "http://"},
  {0x805060e0, "http://"},
  {0x80506350, "http://"},

  {0x805064b0, "rnk.xtreme13.com:2201"},
  {0x80506894, "rnk.xtreme13.com:2201"},
  {0x80507724, "rnk.xtreme13.com:2201"},
  {0x80507744, "rnk.xtreme13.com:2201"},
  {0x8050780B, "rnk.xtreme13.com:2201"},
  {0x8050782F, "rnk.xtreme13.com:2201"},
  {0x8050C1F3, "rnk.xtreme13.com:2201/"}
};

int domain_urls[] = { 0x805033d8, 0x805039e0, 0x805045e0, 0x80505a45,
                      0x8050665f, 0x80506683, 0x8050669f, 0x80506743,
                      0x805076f4, 0x80507710, 0x80507774, 0x80507796, 
                      0x805077b6, 0x805077d6, 0x805077f5, 0x8050785b };
int update_urls[] = {0x8050b7b0, 0x8050b7d8, 0x8050b7fc,
                     0x8050b830, 0x8050b858, 0x8050b87c};
char *new_update_urls[] = {
    "http://nas.test.%s/ac", "http://nas.%s/ac",
    "http://nas.dev.%s/ac", "http://nas.test.%s/pr",
    "http://nas.%s/pr", "http://nas.dev.%s/pr"};

char security_patchA[] = { 0x88, 0xA1, 0x00, 0x11, 0x28, 0x05, 0x00, 0x80, 0x41, 0x81, 0x00, 0x70, 0x54, 0xE3, 0xC2, 0x1E, 0x54, 0xE0, 0x40, 0x0E, 0x81, 0x81, 0x00, 0x0C, 0x3C, 0xA0, 0x5A, 0x00, 0xA0, 0xC1, 0x00, 0x12, 0x7C, 0x05, 0x60, 0x00, 0x50, 0xE3, 0xC6, 0x3E, 0x50, 0xE0, 0x44, 0x2E, 0x7C, 0xC4, 0x46, 0x70, 0x7C, 0x60, 0x03, 0x78, 0x60, 0x00, 0x00, 0x00};
char security_patchB[] = { 0x38, 0xE0, 0x00, 0x04, 0x7D, 0x03, 0x3C, 0x2C, 0x55, 0x46, 0xC2, 0x1E, 0x55, 0x40, 0x40, 0x0E, 0xA1, 0x21, 0x00, 0x12, 0x91, 0x01, 0x00, 0x0C, 0x89, 0x01, 0x00, 0x11, 0x51, 0x46, 0xC6, 0x3E, 0x51, 0x40, 0x44, 0x2E, 0x7D, 0x27, 0x46, 0x70, 0x28, 0x08, 0x00, 0x80, 0x38, 0xA0, 0x00, 0x04, 0x7C, 0xC6, 0x03, 0x78, 0x51, 0x27, 0x42, 0x2E, 0x60, 0x00, 0x00, 0x00, 0xB0, 0xE1, 0x00, 0x12, 0x54, 0xC0, 0x80, 0x3E, 0x41, 0x81, 0x00, 0x14};

bool s_is_online_done = false;
bool s_is_text_done = false;

char NewMoveNames[6][50];

bool Xtreme::IsWiimmfi() { return true; }

void Xtreme::PerformTextEdits() {
  char **maintext = *((char ***)0x805131C0);
  maintext[1675] = "ザナーク　×　クララジェーン";
  maintext[587] = "Change Xtreme's additional settings";
  maintext[529] = "Xtreme settings";
  maintext[893] = "#b84#=もどる #b83#=けってい #b87#=いれかえ #b88#=ステータス #b86#=ルーレット #b85#=DRAFT";
  maintext[858] = "#b84#=もどる #b83#=けってい #b87#=ルールせってい #b88#=そうさ #b85#=まえのＢＧＭ #b86#=つぎのＢＧＭ";
  maintext[530] = "#b84#=もどる #b83#=けってい #b85#=まえのＢＧＭ #b86#=つぎのＢＧＭ";
  maintext[531] = "#b83#=けってい #b85#=まえのＢＧＭ #b86#=つぎのＢＧＭ";
  maintext[532] = "#b84#=もどる #b85#=まえのＢＧＭ #b86#=つぎのＢＧＭ";
  maintext[1633] = "ズバ#R抜(ぬ)けた#R瞬発力(しゅんぱつりょく)と#R反射神経(はんしゃしんけい)であらゆるシュートを#R掴(つか)みとる。";
  maintext[6870] = "真 マッハウィンド";
  maintext[6871] = "マッハウィンド しん";
  maintext[6872] = "サイドワインダー #x14Ｖ３";
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

void Xtreme::PatchOnlineServer() {
  URL_Patch* server = 0;
  char* domain = 0;
  if (IsWiimmfi()) {
    server = wiimmfi_server;
    domain = "wiimmfi.de";
  }
  else {
    server = so_server;
    domain = "inazumafrance.fr";
  }
  for (int i = 0; i < sizeof(domain_urls) / 4; i++) strcpy((char*)domain_urls[i], domain);
  for (int i = 0; i < sizeof(update_urls) / 4; i++) {
    char url[64];
    sprintf(url, new_update_urls[i], domain);
    strcpy((char*)update_urls[i], url);
  }
  for (int i = 0; i < sizeof(so_server) / sizeof(URL_Patch); i++) {
    URL_Patch* cur = &server[i];
    strcpy((char*)cur->address, cur->text);
  }
  s_is_online_done = true;
}

void* nhttp_alloc(u32 size, int align) {
  return MEMAlloc(size, align, 3, 31);
}

void nhttp_free(void* block) {
  return MEMFree(block);
}

void Xtreme::Init() {
  OSReport("Initializing /dev/dolphin driver... ");
  Dolphin::Init();
  OSReport("\n");
  OSReport("Initializing Discord Rich Presence...\n");
  Discord::Init();
  u8 flag = *SaveFlag;
  ModSettings = new XtremeSettings(flag & 1, (flag & 2) != 0, (flag >> 2) & 3, (flag >> 4) & 1);
  SwitchKeyboardLayout(ModSettings->GetKeyboardType());


  if (!s_is_text_done)
    PerformTextEdits();
  if (!s_is_online_done) 
    PatchOnlineServer();

  memcpy((char *)0x80472A3C, security_patchA, 56);
  memcpy((char *)0x80472BD0, security_patchB, 72);
  
  strcpy((char *)0x8050bacc, "X-3-1");
  CheckForDolphin();
  create_new_waza_defs();
}
  

kmBranch(0x800E5B74, OutdatedDolphinVersion);
kmBranch(0x800E49A8, Xtreme::Init);
// bugfixes
kmWrite32(0x801558B8, 0x480000A0); // supplement bug
kmWrite32(0x802011dc, 0x48000028); // Wiimote team save
kmWrite32(0x80041b5c, 0x4800001c); // Restore autosave
