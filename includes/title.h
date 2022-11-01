#ifndef TITLE
#define TITLE
#include <spritestudio.h>
#include <task.h>

namespace TTL {
struct mpMap {
  u32 _0;
  u32 _4;
  u32 _8;
  u32 _C;
  u8 _10;
  u32 _14;
  u32 _18;
  u32 _1C;
  u32 _20;
  u32 _24;
  u32 _28;
  u32 _2C;
  u32 _30;
  u32 _34;
  u32 _38;
  u32 _3C;
  u32 _40;
  CSprStudio *SpriteStudio;
  cTASK *Tasks;
};

static mpMap *mpMapTemp;

void thDataLoad();
void title_loop4();
void mpTOPLOOP();
void mpLOOP3();
void Start(int a1, void *a2);
void Ready(int a1, void *a2);
void Mchg(int a1, void *a2);
void Loop2(int a1, void *a2);
void Loop(int a1, void *a2)

    class CSetCallback : public WATAM_UTILITY::CSetCallback {
public:
  virtual int CallbackFunction(int a1, int a2, int a3, int a4, int a5, int a6);
  virtual ~CSetCallback() {}
}

} // namespace TTL

#endif