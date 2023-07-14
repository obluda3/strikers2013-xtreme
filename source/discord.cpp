#include <clubroom.h>
#include <discord.h>
#include <kamek.h>
#include <mchg.h>
#include <random.h>
#include <wifi.h>

#include "dolphinios.h"

extern "C" {
void ENCConvertStringSjisToUnicode(char *dest, int *destLength, char *src,
                                   int *srcLength);
}

namespace Discord {
static DiscordRichPresence richPresence = {"Inazuma Eleven GO Strikers 2013 Xtreme", "Main Menu", "logo", "Inazuma Eleven GO Strikers 2013 Xtreme", "logo", "Inazuma Eleven GO Strikers 2013 Xtreme", 0, 0, 0, 0};
static bool isDiscordEnabled = false;
void Init() {
  if (Dolphin::IsOpen()) {
    int result = Dolphin::SetDiscordClient("1037323500962201681");
    if (!result) {
      isDiscordEnabled = true;
      SendStatus();
    }
  }
}

void UpdateStatus() {
  if (isDiscordEnabled) {
    int maph = *MCHG::cur_maph;
    int mapl = *MCHG::cur_mapl;
    OSReport("##MAP UPDATE##\n");
    OSReport("XTREME: New map maph=%d mapl=%d\n", maph, mapl);
    switch (maph) {
      case MCHG::MAP_TITLE_SCREEN:
        richPresence.state = "In title screen";
        break;
      case MCHG::MAP_MAIN_MENU:
        switch (mapl) {
          case MCHG::MODE_MAIN:
            richPresence.state = "In main menu";
            break;
          case MCHG::MODE_MATCH:
            richPresence.state = "In match menu";
            break;
          case MCHG::MODE_ONLINE: {
            char **stpDwcCnt = (char **)0x809C4F70;
            if (*stpDwcCnt) {
              char *dwcStruct = *stpDwcCnt;
              int dwcState = *(int *)(dwcStruct + 0x24);
              bool isFriend = *(dwcStruct + 0x375);
              if (dwcState == 4) {
                if (isFriend)
                  richPresence.state = "In online menu: requesting a friend match";
                else
                  richPresence.state = "In online menu: looking for an opponent";
              } else
                richPresence.state = "In online menu";
            } else
              richPresence.state = "In online menu";
            break;
            shdRndInit(Calendar_GetDateID(0)); // reset rng seed
          }
          case MCHG::MODE_MATCHSTART:
            richPresence.state = "Starting a match";
            break;
          default:
            richPresence.state = "In a menu";
            break;
        }
        break;
      case MCHG::MAP_MATCH:
        if (is_wifi_mode()) {
          richPresence.state = "In an online match";
        } else
          richPresence.state = "In a match";
        break;
      case MCHG::MAP_TRAINING:
        richPresence.state = "In a training session";
        break;
      case MCHG::MAP_CARAVAN:
        richPresence.state = "In the caravan mode";
        break;
    }
    OSReport("Discord state: %s\n", richPresence.state);
    SendStatus();
  }
}

void SendStatus() { Dolphin::SetDiscordPresence(&richPresence); }
}  // namespace Discord

kmBranch(0x80031660, Discord::UpdateStatus);
kmBranch(0x804593C4, Discord::UpdateStatus);
kmBranch(0x80459660, Discord::UpdateStatus);