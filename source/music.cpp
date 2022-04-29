#include <kamek.h>
#include <snd.h>
#include <buttonhelpers.h>
#include <savedata.h>
#include <dvd.h>
#include <text.h>
#include <random.h>
#include <shd_debug.h>
#include <utilitysato.h>
#include "music.h"
#include "xtreme_settings.h"

static char* s_HelpbarText_SP = "#b84#=もどる #b83#=けってい #b87#=ルールせってい #b88#=そうさ #b85#=まえのＢＧＭ #b86#=つぎのＢＧＭ";
static char* s_HelpbarText_Wifi_a = "#b84#=もどる #b83#=けってい #b85#=まえのＢＧＭ #b86#=つぎのＢＧＭ";
static char* s_HelpbarText_Wifi_b = "#b83#=けってい #b85#=まえのＢＧＭ #b86#=つぎのＢＧＭ";
static char* s_HelpbarText_Sett = "#b84#=もどる #b85#=まえのＢＧＭ #b86#=つぎのＢＧＭ";

static char ***s_MainTexts = (char***)0x805131C0;
u16* IsMusicOn = (u16*)0x80904212;
int g_CurrentBgm = 0;
static char** BgmNames = (char**) 0;
static char*** DefaultBgmNames = (char***) 0x8051ECA0;
static int* g_BgmStatus = (int*)0x8050d6d8;
static void* playlistBuffer = 0;
static bool FirstExec = true;

struct PlaylistInfo
{
    u32 size;
    s32 openingFirst;
};
struct PlaylistHeader
{
    u32 magic;
    PlaylistInfo info;
};

static PlaylistInfo playlistInfo;
void parsePlaylistFile(u8* data)
{
    PlaylistHeader* header = (PlaylistHeader*) data;
    BgmNames = (char**)&header[1];
    playlistInfo = header->info;
    u32 baseAddress = (u32)data;
    data += sizeof(PlaylistHeader);
    for (int i = 0; i < header->info.size; i++)
    {
        u32 pointer = *((u32 *)data);
        u32 fixedPointer = pointer + baseAddress;
        *((u32 *)data) = fixedPointer;
        data += 4;
    }
}

void PlayBgmField(int defaultBgm)
{
    int bgmStatus = *g_BgmStatus;
    int currentBgm = g_CurrentBgm;
    char** defaultBgmNames = *DefaultBgmNames;
    char* bgmName = BgmNames[currentBgm];
    if (!currentBgm) 
    {
        currentBgm = defaultBgm;
        bgmName = defaultBgmNames[currentBgm];
    }
    if (bgmStatus != currentBgm ) 
    {
        *g_BgmStatus = currentBgm;
        int id = wiiSndGetNameToID(bgmName);
        SNDBgmPlay_Direct(id);
    }
}

void initBgmPlayer()
{
    char** mainTexts = *s_MainTexts;
    mainTexts[858] = s_HelpbarText_SP;
    mainTexts[530] = s_HelpbarText_Wifi_a;
    mainTexts[531] = s_HelpbarText_Wifi_b;
    mainTexts[532] = s_HelpbarText_Sett;
    char* path = "Playlist.bin";
    cprintf("Loading custom musics in: '%s'...\n", path);

    void* buffer = 0;
    int entrynum = DVDConvertPathToEntrynum(path);
    if (entrynum < 0)
        cprintf("Could not find '%s' \n", path);
    else 
    {
        DVDHandle handle;
        if (!DVDFastOpen(entrynum, &handle)) 
            cprintf("ERROR: Failed to open file!\n");
        else
        {
            cprintf("DVD file located: addr=%p, size=%d\n", handle.address, handle.length);

            u32 length = handle.length, roundedLength = (handle.length + 0x1F) & ~0x1F;
            buffer = MEMAlloc(roundedLength, 32, 3, 31);
            if (!buffer)
                cprintf("ERROR: Out of file memory");
            else
            {
                DVDReadPrio(&handle, buffer, roundedLength, 0, 2);
                DVDClose(&handle);
            }
        }
    }
    parsePlaylistFile((u8 *)buffer);
    playlistBuffer = buffer;
}

int updateCurrentBgm(int argBak) 
{
    if (!FirstExec)
        FirstExec = true;

    int currentBgm = g_CurrentBgm;
    bool changed = false;

    if (UtilitySato::isPad(0, UtilitySato::PAD_PLUS, UtilitySato::HELD)) // +
    {
        currentBgm++;
        changed = true;
    }
    else if (UtilitySato::isPad(0, UtilitySato::PAD_MINUS, UtilitySato::HELD)) // -
    {
        currentBgm--;
        changed = true;
    }
    
    s32 openingFirst = playlistInfo.openingFirst;
    u32 bgmMax = playlistInfo.size;
    int maxBgm = openingFirst == -1 ? bgmMax - 1 : g_Jukebox.allowOpenings ? bgmMax - 1 : openingFirst;
    if (currentBgm < 0) currentBgm = maxBgm;
    if (currentBgm > maxBgm) currentBgm = 0;

    g_CurrentBgm = currentBgm;
    if (changed)
    {      
        int songId;  
        if (currentBgm)
            songId = wiiSndGetNameToID(BgmNames[currentBgm]);
        else
            songId = wiiSndGetNameToID("BGM_M12_TENMAS2_MASTER_01");
        SNDBgmPlay_Direct(songId);
        SNDSeSysOK(-1);
    }
    return IsButtonPushed_OK(argBak); // default inst
}


void drawBgmName()
{
    char message[50];
    int currentBgm = g_CurrentBgm;

    if (currentBgm > 0)
        sprintf(message, "#j#I1Music Track %03d", currentBgm);
    else if (currentBgm == 0)
        strcpy(message, "#j#I1Default track");
    else
        strcpy(message, "#j#I1Random track");
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
    drawBgmName();
}

void resetMusic()
{
    g_CurrentBgm = 0;
}


kmWrite32(0x80047264, 0x7FE3FB78);
kmCall(0x80047268, PlayBgmField);
kmBranch(0x80046D94, initBgmPlayer);
kmWrite32(0x8004726C, 0x4800005C);
kmCall(0x8010DB88, updateCurrentBgm);
kmCall(0x8025CE40, updateCurrentBgm);
kmBranch(0x8025CB1C, onlineDrawHook);
kmBranch(0x8010E8D4, drawBgmName);
kmBranch(0x8011D608, resetMusic);

// changes helpbar text in online menu
kmWrite32(0x8025CE4C, 0x3B800212);
kmWrite32(0x8025CE60, 0x3b800213);