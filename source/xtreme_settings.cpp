#include "xtreme_settings.h"
#include <menu_setting.h>
#include <kamek.h>
#include "music.h"

XtremeSettings g_Jukebox;
void XtremeSettings::MusicLoop(int state, void* arg)
{
    MENU_SETTING::CMenuSetting* menu = (MENU_SETTING::CMenuSetting *) arg;
    if (state == 2) 
    {
        updateCurrentBgm(0);
        
        g_Jukebox.Exec();
        g_Jukebox.DrawMenu();
        
        if (IsButtonPushed_Cancel(0))
        {
            menu->tasks->Pop(0);
            menu->tasks->Push(MENU_SETTING::CMenuSetting::MenuSet0Loop, arg);
            menu->tasks->Push(MENU_SETTING::CMenuSetting::MenuSet4Out, arg);
            g_Jukebox.passAccepted = false;
            SNDSeSysCANCEL(-1);
        }
    }
}

void XtremeSettings::Exec()
{
    u8 pos = m_pos;
    bool isPadUp = UtilitySato::isPad(0, UtilitySato::PAD_UP, UtilitySato::HELD);
    bool isPadDown = UtilitySato::isPad(0, UtilitySato::PAD_DOWN, UtilitySato::HELD);
    bool isPadLeft = UtilitySato::isPad(0, UtilitySato::PAD_LEFT, UtilitySato::HELD);
    bool isPadRight = UtilitySato::isPad(0, UtilitySato::PAD_RIGHT, UtilitySato::HELD);
    if (isPadDown)
        pos++;
    else if (isPadUp)
        pos--;
    if (pos > 1)
        pos = 0;
    else if (pos < 0)
        pos = 1;
    if (pos != m_pos) 
    {
        m_pos = pos;
        SNDSeSysCLICK(-1);
    }
    
    else
    {
        s8 openings = allowOpenings;
        if (isPadLeft) openings--;
        else if (isPadRight) openings++;

        if (openings < 0) openings = 1;
        else if (openings > 1) openings = 0;

        if(openings != allowOpenings) 
        {
            allowOpenings = openings;
            SNDSeSysCLICK(-1);
        }
    }

    /*
    if (isPadDown) m_yOff++;
    if (isPadUp) m_yOff--;
    if (isPadLeft) m_xOff--;
    if (isPadRight) m_xOff++;
    */
}

void XtremeSettings::DrawMenu()
{
    char extendedMessage[100];
    char message[50];
    s32 currentBgm = g_CurrentBgm;
    if (currentBgm > 0)
        sprintf(message, "#P10#j#I1Music Track %03d", currentBgm);
    else if (currentBgm == 0)
        strcpy(message, "#P10#j#I1Default track");

    disp_zen(message, 255, 170, 100);

    // Draw setting options
    disp_zen("#I1Theme songs", 205, 250, 90);
    s32 y = 250 + 30 * m_pos;
    disp_zen("#j#=->", 155, y, 90);
    disp_zen("#I1Preferred Keyboard", 555, 280, 90);
    disp_zen("A", 555, 280, 90);

    char* messageOpening;
    if (allowOpenings) messageOpening = "#I1#=< Enabled >";
    else messageOpening = "#I1#=< Disabled >";
    disp_zen(messageOpening, 555, 250, 90);
}
