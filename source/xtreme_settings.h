#include <types.h>

static s16 rainbowColors[] = 
{ 
    8700,
    8840,
    8880,
    8480,
    8271,
    8174,
    8276,
    8137,
    8317,
    8617,
    8716,
};

#define FRAME_PER_COLOR 7
class XtremeSettings 
{
    public:
        void DrawMenu();
        s8 allowOpenings;
        s8 passAccepted;
        static void MusicLoop(int state, void* arg);
        void Exec();
    private:
        u8 m_pos;
        // s32 m_xOff;
        // s32 m_yOff;
};

extern XtremeSettings g_Jukebox;