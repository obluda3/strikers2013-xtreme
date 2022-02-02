#ifndef SPR_STUDIO
#define SPR_STUDIO

#include "types.h"
struct unkStruct
{
	u32 _0;
	u32 _4;
	u32 _8;
	u32 _C;
	u32 _10;
	u32 _14;
	u32 endFrame;
	u32 _1C;
	u32 _20;
	u32 _24;
};

struct ssaComponent
{
	u32 curFrame;
	u32 endFrame;
	u32 isPlayingFlag;
	u32 xOffset;
	u32 yOffset;
	u32 ot;
	f32 alpha;
	u32 _1C;
	unkStruct *maybeIsPlaying;
	f32 *p_24;
	u32 p_28;
	u32 sprAnimCallback;
	u32 _30;
	u32 _34;
	u32 _38;
	u32 _3C;
	u32 _40;
	u32 _44;
	u32 _48;
	u32 _4C;
	u32 _50;
	u32 _54;
	u32 _58;
	u32 _5C;
	u32 _60;
	u32 _64;
	u32 _68;
	u32 _6C;
	u32 _70;
	u16 _74;
};

class CSprStudio
{
	public:
		void Draw();
	//todo
	private:
		u32 _0;
		u16 texSlots[64];
		u16 fileLabels[64];
		u16 m_textureMax;
		char _106;
		unkStruct *pUnkStruct;
		ssaComponent *m_pSsaComponent;
		u32 _110;
		u16 m_curFrameMaybe;
		u16 m_ssaCount;
		u16 _118;
		u16 _11A;
		u32 _11C;
		u32 _120;
		u32 _124;
		u32 _128;
		u32 _12C;
		u32 _130;
		u32 _134;
		u32 _138;
		u32 _13C;
		u32 _140;
		u32 _144;
		u32 _148;
		u32 _14C;
		u32 _150;
		u32 _154;
		u32 _158;
		u32 _15C;
		u32 _160;
		u32 _164;
		u32 _168;
		u32 _16C;
		u32 _170;
		u32 _174;
		u32 _178;	
};



namespace WATAM_UTILITY 
{
	class CSetCallback
	{
	private:
		CSprStudio* SpriteStudio;
	public:
		virtual int CallbackFunction(int a1, int a2, int a3, int a4, int a5, int a6) = 0;
		virtual ~CSetCallback() = 0; 
	};
}

#endif