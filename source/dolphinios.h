#include <types.h>
#include <ipc.h>

enum
{
  IOCTL_DOLPHIN_GET_SYSTEM_TIME = 0x01,
  IOCTL_DOLPHIN_GET_VERSION = 0x02,
  IOCTL_DOLPHIN_GET_SPEED_LIMIT = 0x03,
  IOCTL_DOLPHIN_SET_SPEED_LIMIT = 0x04,
  IOCTL_DOLPHIN_GET_CPU_SPEED = 0x05,
  IOCTL_DOLPHIN_GET_REAL_PRODUCTCODE = 0x06,
  IOCTL_DOLPHIN_DISCORD_SET_CLIENT = 0x07,
  IOCTL_DOLPHIN_DISCORD_SET_PRESENCE = 0x08,
  IOCTL_DOLPHIN_DISCORD_RESET = 0x09
};

struct DiscordRichPresence
{
    char* details;
    char* state;
    char* largeImageKey;
    char* largeImageText;
    char* smallImageKey;
    char* smallImageText;
    s64 startTimestamp;
    s64 endTimestamp;
    s32 partySize;
    s32 partyMax;
};

namespace Dolphin
{
    void Init();
    bool IsOpen();
    int GetSystemTime();
    char* GetVersion();
    int GetSpeedLimit();
    void SetSpeedLimit(int value);
    int GetCPUSpeed();
    char* GetRealProductCode();
    void SetClient(char* id);
    void SetDiscordPresence(DiscordRichPresence* value);
    void ResetDiscord();
}