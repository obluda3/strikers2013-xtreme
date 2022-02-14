#ifndef WATAM
#define WATAM

#include <types.h>
#include <spritestudio.h>
#include <file.h>
#include <textures.h>

namespace WATAM_UTILITY {
	class CSSComponent {
	private:
		CSprStudio csprstudio0;
		CSSComponent *m_child;
		CSSComponent *m_parent;
		CSSComponent *m_left;
		CSSComponent *m_right;
		u32 m_curPlayedSsa;
		u32 dword190;
		u32 m_xOffset;
		u32 m_yOffset;
		f32 m_alpha;
		u8 m_IsVisible;
		u8 m_isPaused;
	public:
		virtual void OnExec();
		virtual void OnDraw();
		u32 sprAnimCallback;
		u32 ot;
		u32 m_ssaCount;
	};
}

#endif