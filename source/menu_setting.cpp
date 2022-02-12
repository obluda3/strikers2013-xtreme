#include "music.h"
#include "helpbar.h"
#include <snd.h>
#include <savedata.h>
#include <buttonhelpers.h>
#include <menubg.h>
#include <file.h>
#include <textures.h>
#include <kamek.h>
#include <menu_setting.h>
#include <helpbar.h>
#include <utilitysato.h>

static bool s_passAccepted = false;
void SettingLoop(int state, void* menu);
void SettingPassLoop(int state, void* arg);

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
		drawBgmName(SETTING_MODE_CONST);	
	}
}

void MusicLoop(int state, void* arg)
{
	MENU_SETTING::CMenuSetting* menu = (MENU_SETTING::CMenuSetting *) arg;
	if (state == 2) 
	{
		updateCurrentBgm(0);
		drawBgmName(SETTING_MODE_CONST);
		
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

void SettingPassLoop(int state, void* arg) 
{
	MENU_SETTING::CMenuSetting* menu = (MENU_SETTING::CMenuSetting*)arg;
	cPopup* popup = menu->popup;
	if (state == 2)
	{
		if (popup->exec(0))
		{
			menu->tasks->Pop(0);
			menu->tasks->Push(MusicLoop, arg);
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