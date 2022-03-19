#ifndef UTILITY_SATO
#define UTILITY_SATO
#include "types.h"
#include <spritestudio.h>
#include <players.h>

namespace UtilitySato 
{
    enum PADSTATE 
    { 
        PAD_STATE0,
        PRESSED, 
        HELD 
    };

    enum BUTTONS 
    {
        PAD_PLUS = 0x2000,
        PAD_MINUS = 0x1000,
        PAD_UP = 0x800,
        PAD_DOWN = 0x400,
        PAD_LEFT = 0x100,
        PAD_RIGHT = 0x200
    };
    bool isManager(u32 id);
    bool isKantoku(u32 id);
    void setFrameRate(bool is60);
    bool isWideMonitor();
    bool is43Monitor();
    int getScreenSizeX();
    int getScreenSizeY();
    int getScreenSizeRateX();
    int getScreenSizeRateY();
    int getScreenWide34OffSet();
    int getScreenWide43AutoOffSet();
    int isPad(s32 id, s32 mask, PADSTATE state);
    PLAYER_DEF* getPlayerDefAddrBase(int player);

    class CSpriteStudioCtrl
    {
        public:
            void init();
            void rel();
            int getOt();
            int setOt(s32 value);
            int getAnm();
            void setPos(s32 x, s32 y);
            void setOffSetPos(s32 offX, s32 offY);
            int getPosX();
            int getPosY();
            int getOffSetPosX();
            int getOffSetPosY();
            CSprStudio* getSppAddr();
            void setSppAddr(CSprStudio* spriteStudio);
            void setAlpha(f32 value);
            bool isAnmEnd();
            bool isAnmLoop();
            void update(bool unk);
            void draw(bool unk);
        private:
            u32 m_anm;
            u32 m_x;
            u32 m_y;
            u32 m_offX;
            u32 m_offY;
            u32 _14;
            CSprStudio* m_spriteStudio;
            u32 _20;
            u32 m_flags;
            u32 m_ot;
            f32 m_alpha;
            u32 _30;
            u32 _34;
            u32 _38;
            u16 _3c;
            u16 _3e;
            u32 _40;
            u32 _44;
            u32 _48;
    };
}

#endif