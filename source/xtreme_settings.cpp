#include "xtreme_settings.h"
#include <menu_setting.h>
#include <kamek.h>
#include "music.h"
#include "keyboard.h"

XtremeSettings g_Jukebox;
u8* SaveFlag = (u8*)0x805F912E;

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
            g_Jukebox.Save();
            menu->tasks->Pop(0);
            menu->tasks->Push(MENU_SETTING::CMenuSetting::MenuSet0Loop, arg);
            menu->tasks->Push(MENU_SETTING::CMenuSetting::MenuSet4Out, arg);
            g_Jukebox.passAccepted = false;
            SNDSeSysCANCEL(-1);
        }
    }
}

void XtremeSettings::Init()
{
    u8 flag = *SaveFlag;
    g_Jukebox.allowOpenings = flag & 1;
    g_Jukebox.movePower = flag & 2;
    g_Jukebox.keyboardType = (flag >> 2) & 3;
    SwitchKeyboardLayout(g_Jukebox.keyboardType);
}

void XtremeSettings::Save()
{
    u8 flag = 0;
    flag |= (keyboardType << 2) & 12;
    flag |= allowOpenings;
    flag |= movePower << 1;
    *SaveFlag = flag; 
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
    if (pos > 2)
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
        if (!m_pos)
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
        else if (m_pos == 1)
        {
            s8 keyboard = keyboardType;
            if (isPadLeft) keyboard--;
            else if (isPadRight) keyboard++;

            if (keyboard < 0) keyboard = 2;
            else if (keyboard > 2) keyboard = 0;
            if(keyboard != keyboardType) 
            {
                keyboardType = keyboard;
                SwitchKeyboardLayout(keyboard);
                SNDSeSysCLICK(-1);
            }
        }
        if (m_pos == 2)
        {
            s8 values = movePower;
            if (isPadLeft) values--;
            else if (isPadRight) values++;

            if (values < 0) values = 1;
            else if (values > 1) values = 0;

            if(values != movePower) 
            {
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

char* FlagToEng(int val)
{
    if (val)
        return "< ON >";
    else
        return "< OFF >";
}

char* KeyboardType(int val)
{
    if (val == KEY_LTN)
        return "< Latin >";
    else if (val == KEY_CRL)
        return "#x15< Кириллица >";
    return "< 日本語 >";
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
    disp_zen("テーマソング", 205, 250, 90);
    disp_zen("キーボード", 205, 280, 90);
    disp_zen("威力数値", 205, 310, 90);
    disp_zen(KeyboardType(keyboardType), 555, 280, 90);
    disp_zen(FlagToEng(allowOpenings), 555, 250, 90);
    disp_zen(FlagToEng(movePower), 555, 310, 90);

    s32 y = 250 + 30 * m_pos;
    disp_zen("#j#=->", 155, y, 90);
}

kmBranch(0x8004208C, XtremeSettings::Init);