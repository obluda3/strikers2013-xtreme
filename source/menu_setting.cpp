#include "music.h"
#include "helpbar.h"
#include <snd.h>
#include <savedata.h>
#include <menubg.h>
#include <kamek.h>
#include <menu_setting.h>
#include "jukeboxMenu.h"

static bool s_passAccepted = false;
void SettingLoop(int state, void* menu);
void SettingPassLoop(int state, void* arg);

JukeboxSetting g_Jukebox;

void SettingLoop(int state, void* arg)
{
	MENU_SETTING::CMenuSetting* menu = (MENU_SETTING::CMenuSetting*)arg;
	cTASK* tasks = menu->tasks;
	if (state == 2 && !s_passAccepted) 
	{
		int helpStrId = menu->nameWindow->getHelpStrID();
		if (HelpBar_GetTextID() != helpStrId) HelpBar_SetTextID(helpStrId);
		if (menu->nameWindow->exec()) 
		{ 
			tasks->Pop(0);
			const char pass[] = { 0x82, 0x50, 0x82, 0x4f, 0x82, 0x4f, 0x81, 0x7c, 0x81, 0x93, 0x81, 0x49, 0x81, 0x49, 0x81, 0x49, 0x0 };
			if (menu->nameWindow->getResult()) 
			{
				int index = -1;
				menu->textEntry = -1;

				char* curHashedPass = MENU_SETTING::CMenuSetting::szPassword;
				char hashedInput[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
				char* input = menu->nameWindow->getResultString();
				memcpy(hashedInput, input, sizeof(hashedInput));
				u8 key = 0xF;
				for (int j = 0; j < sizeof(hashedInput); j++) 
				{ 
					hashedInput[j] ^= key;
					key += 0xF;
				}
				for (int i = 0; i < 8; i++) 
				{ 
					if (!memcmp(hashedInput, curHashedPass, 16)) 
					{ 
						index = i;
						break;
					}
					curHashedPass += 18;
				}

				if (index != -1) 
				{
					int plyId = MENU_SETTING::CMenuSetting::m_sSecretPLYID[index];

					if (Savedata_ChkPlayerFlag(plyId, UNLOCKED)) 
					{
						SNDSePlay(90, 128, 128);
						menu->textEntry = 7566;
						menu->popup->set_itemtext(1, 7567);
					}
					else 
					{
						SNDSePlay(238, 128, 128);
						Savedata_SetPlayerFlag(plyId, 0, 1);
						menu->textEntry = 317;
						menu->popup->set_itemtext(1, 7569 + index);
						menu->popup->set_itemtext(2, 7568);
					}
					tasks->Push(MENU_SETTING::CMenuSetting::AlgoConfirmPassword, menu);
				}
				else if (memcmp(input, pass, 16) != 0)
				{
					SNDSePlay(90, 128, 128);
					menu->textEntry = 7565;
					menu->popup2->set_itemtext(1, "");
					tasks->Push(MENU_SETTING::CMenuSetting::AlgoConfirmPassword, menu);
				}
				else
				{
					s_passAccepted = true;
					updateCurrentBgm(0);
					SNDSePlay(238, 128, 128);
					menu->popup->set_itemtext(0, "#I1Congratulations!");
					menu->popup->set_itemtext(1, "#I1The secret password has been entered.");
					menu->popup->set_itemtext(2, "#I1You can now access the #P10#=music player#C#I1#=!");
					menu->nameWindow->setWindowAnm(1);
					tasks->Push(SettingPassLoop, menu);
				}
			}
			else 
			{
				menu->textEntry = 0;
				tasks->Pop(0);
				tasks->Push(MENU_SETTING::CMenuSetting::MenuSet0Loop, menu);
				tasks->Push(MENU_SETTING::CMenuSetting::MenuSet4Out, menu);
				menu->nameWindow->setWindowAnm(2);
			}
		}
		menu->nameWindow->draw();
	}
	else if (!state)
	{
		menu->nameWindow->setName("");
		menu->nameWindow->reset();
		menu->nameWindow->enableCollisionTest(true);
	}
	else if (s_passAccepted) 
	{
		updateCurrentBgm(0);
		if (IsButtonPushed_Cancel(0)) 
		{
			tasks->Pop(0);
		}
		drawBgmName();	
	}
}

void JukeboxSetting::MusicLoop(int state, void* arg)
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
			s_passAccepted = false;
			SNDSeSysCANCEL(-1);
		}
	}
}

void JukeboxSetting::Exec()
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
	if (pos != m_pos) {
		m_pos = pos;
		SNDSeSysCLICK(-1);
	}
	
	if (pos)
	{
		s32 curMode = mode;
		if (isPadLeft) curMode--;
		else if (isPadRight) curMode++;

		if (curMode < 0) curMode = MUSIC_RANDOM;
		else if (curMode > MUSIC_RANDOM) curMode = 0;

		if(curMode != mode) {
			mode = (JukeboxMode) curMode;
			SNDSeSysCLICK(-1);
		}
	}
	else
	{
		s8 openings = allowOpenings;
		if (isPadLeft) openings--;
		else if (isPadRight) openings++;

		if (openings < 0) openings = 1;
		else if (openings > 1) openings = 0;

		if(openings != allowOpenings) {
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

void JukeboxSetting::DrawMenu()
{
	char extendedMessage[100];
	char message[50];
	s32 currentBgm = g_CurrentBgm;
	if (currentBgm > 0)
		sprintf(message, "#P10#j#I1Music Track %03d", currentBgm);
	else if (currentBgm == 0)
	{
		strcpy(message, "#P10#j#I1Default track");
	}

	disp_zen(message, 255, 170, 100);

	// Draw setting options
	disp_zen("#I1Theme songs", 205, 250, 90);
	disp_zen("#I1After music ends", 205, 280, 90);
	s32 y = 250;
	if (m_pos) y = 280;
	disp_zen("#j#=->", 155, y, 90);
	char* messageMode;
	switch (mode)
	{
		case MUSIC_LOOP:
			messageMode = "#I1#=< Loop >";
			break;
		case MUSIC_RANDOM:
			messageMode = "#I1#=< Play next ( random ) >";
			break;
		case MUSIC_SEQUENTIAL:
			messageMode = "#I1#=< Play next >";
			break;
	}
	disp_zen(messageMode, 555, 280, 90);

	char* messageOpening;
	if (allowOpenings) messageOpening = "#I1#=< Enabled >";
	else messageOpening = "#I1#=< Disabled >";
	disp_zen(messageOpening, 555, 250, 90);
}

void SettingPassLoop(int state, void* arg) 
{
	MENU_SETTING::CMenuSetting* menu = (MENU_SETTING::CMenuSetting*)arg;
	cPopup* popup = menu->popup;
	if (state == 2)
	{
		if (popup->exec(0))
		{
			menu->tasks->Pop(0);
			menu->tasks->Push(JukeboxSetting::MusicLoop, arg);
			/*
			s32 fileIdx = 30032;
			s32 allocatedTex = TEX_Alloc(fileIdx, 158, 422);
			TEXLoad(fileIdx, allocatedTex);
			gpMenuBG_Work->textures[2] = allocatedTex;
			gpMenuBG_Work->spriteStudio->SSA_set_textureIdx(3, allocatedTex, fileIdx);
			*/
			HelpBar_SetTextID(532);
		}
		menu->nameWindow->exec();
		menu->nameWindow->draw();
		popup->draw();
	}
	else if (!state)
	{
		popup->open(0, 144);
		HelpBar_SetTextID(2530);
	}
}

kmBranch(0x8013f794, SettingLoop);