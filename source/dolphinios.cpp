#include "dolphinios.h"
#include <Kamek/base/c_stdlib.h>
#include <shd_debug.h>

namespace Dolphin
{
    static int sDevDolphinHandle = -1;

    void Init()
    {
        sDevDolphinHandle = IOS_Open("/dev/dolphin", 0);
    }

    bool IsOpen()
    {
        return sDevDolphinHandle >= 0;
    }

    int ReturnValue(int ioctl)
    {
        IOVector command;
        s32 value;
        command.data = &value;
        command.size = sizeof(s32);
        int result = IOS_Ioctlv(sDevDolphinHandle, ioctl, 0, 1, &command);
        return value;
    }

    int GetSystemTime()
    {
        return ReturnValue(IOCTL_DOLPHIN_GET_SYSTEM_TIME);
    }

    int GetSpeedLimit()
    {
        return ReturnValue(IOCTL_DOLPHIN_GET_SPEED_LIMIT);
    }
    
    int GetCPUSpeed()
    {
        return ReturnValue(IOCTL_DOLPHIN_GET_CPU_SPEED);
    }

    char* ReturnValue(int ioctl, int size)
    {
        IOVector command;
        char* value = new char[size];
        command.data = value;
        command.size = size;
        IOS_Ioctlv(sDevDolphinHandle, ioctl, 0, 1, &command);
        return value;
    }

    char* GetVersion()
    {
        char* returnvalue = ReturnValue(IOCTL_DOLPHIN_GET_VERSION, 16);
        cprintf(returnvalue);
        return returnvalue;
    }

    char* GetRealProductCode()
    {
        return ReturnValue(IOCTL_DOLPHIN_GET_REAL_PRODUCTCODE, 4);
    }

    void SetSpeedLimit(int value)
    {
        IOVector command;
        int val = value;
        command.data = &val;
        command.size = sizeof(int);
        IOS_Ioctlv(sDevDolphinHandle, IOCTL_DOLPHIN_SET_SPEED_LIMIT, 1, 0, &command);
    }

    void SetClient(char* id)
    {
        IOVector command;
        command.data = id;
        command.size = strlen(id);
        IOS_Ioctlv(sDevDolphinHandle, IOCTL_DOLPHIN_SET_SPEED_LIMIT, 1, 0, &command);
    }

    void SetDiscordPresence(DiscordRichPresence* value)
    {
        IOVector command[10];
        command[0].data = value->details;
        command[0].size = strlen(value->details);
        command[1].data = value->state;
        command[1].size = strlen(value->state);
        command[2].data = value->largeImageKey;
        command[2].size = strlen(value->largeImageKey);
        command[3].data = value->largeImageText;
        command[3].size = strlen(value->largeImageText);
        command[4].data = value->smallImageKey;
        command[4].size = strlen(value->smallImageKey);
        command[5].data = value->smallImageText;
        command[5].size = strlen(value->smallImageText);
        command[6].data = &value->startTimestamp;
        command[6].size = sizeof(s64);
        command[7].data = &value->endTimestamp;
        command[7].size = sizeof(s64);
        command[8].data = &value->partySize;
        command[8].size = sizeof(s32);
        command[9].data = &value->partyMax;
        command[9].size = sizeof(s32);
        IOS_Ioctlv(sDevDolphinHandle, IOCTL_DOLPHIN_DISCORD_SET_CLIENT, 10, 0, command);
    }

    void ResetDiscord()
    {
        IOS_Ioctlv(sDevDolphinHandle, IOCTL_DOLPHIN_DISCORD_RESET, 0, 0, 0);
    }
}