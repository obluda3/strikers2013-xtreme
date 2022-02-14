#ifndef MENUBG
#define MENUBG
#include <types.h>
#include <cssmenu.h>
#include <spritestudio.h>

struct MenuBG {
	CSprStudio* spriteStudio;
	u32 _4;
	u32 textures[11];
	u8 isInMinigame;
};

extern MenuBG* gpMenuBG_Work;

#endif