#ifndef MENUSETTING
#define MENUSETTING

#include <types.h>
#include <cssmenu.h>
#include <task.h>
#include <popup.h>
#include <namewindow.h>

namespace MENU_SETTING {
	
	class CMenuSetting : WATAM_UTILITY::CSSComponent { 
		public:
			u32 *pu321B8;
			cTASK *tasks;
			u32 _1BC;
			u32* pset0;
			u32 _1CC;
			u32 _1D0;
			stNameWindow *nameWindow;
			cPopup *popup;
			cPopup *popup2;
			u32 textEntry;
			u32 _1DC;
			u32 _1E0;
			u32 _1E4;
			u32 _1E8;
			u32 _1EC;
			u32 _1F0;
			u32 _1F4;
			u32 _1F8;
			u32 _1FC;
			u32 _200;
			u32 _204;
			u32 _208;
			u32 _20C;
			u32 _210;

			static void AlgoConfirmPassword(int state, void* menu);
			static void MenuSet0Loop(int state, void* menu);
			static void MenuSet4Out(int state, void* menu);
		
		static int m_sSecretPLYID[];
		static char szPassword[];
	};

}
#endif