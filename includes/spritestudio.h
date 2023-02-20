#ifndef SPR_STUDIO
#define SPR_STUDIO
#include "textures.h"
#include "types.h"

struct STRUC_LAYOUT {
  s16 _00;
  s16 _02;
  s16 _04;
  s16 x;
  s16 y;
  s16 width;
  s16 height;
  s16 _x;
  s16 _y;
  s16 otherWidth;
  s16 otherHeight;
  s16 _16;
  s32 alpha;
};

struct unkStruct {
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

struct ssaComponent {
  u32 curFrame;
  u32 endFrame;
  u32 isPlayingFlag;
  u32 xOffset;
  u32 yOffset;
  u32 ot;
  f32 alpha;
  u32 _1C;
  unkStruct* maybeIsPlaying;
  f32* p_24;
  u32 p_28;
  u32 sprAnimCallback;
};

struct SSAL_PARTS {
  int a1;
};
struct SSAL_USER_DATA {
  int a1;
};

class SpriteAnimationCallback {
 public:
  virtual void CallbackFunction(const SSAL_PARTS* a1, const SSAL_USER_DATA* a2, long a3, long a4, float a5, PRIM_SPR* prim);
  virtual ~SpriteAnimationCallback();
  short data;
};
class CSprStudio {
 public:
  void Draw();
  void Exec(int a1, int unused);
  void UpdateFrame(long a1, long a2);
  void EndSsa(long a1);
  void SSA_set_textureIdx(int texIdx, int a2, int fileIdx);
  void PlaySsa(int ssaIdx, long ot, long xOffset, long yOffset, unsigned long flag, SpriteAnimationCallback* callback);
  u32 _0;
  u16 texSlots[64];
  u16 fileLabels[64];
  u16 m_textureMax;
  char _106;
  unkStruct* UnkStruct;
  ssaComponent* SsaComponent;
  u32 _110;
  u16 curFrameMaybe;
  u16 ssaCount;
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

#endif