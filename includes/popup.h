#ifndef POPUP
#define POPUP
#include <types.h>

class cPopup {
public:
  void set_itemtext(int popIndex, int textId);
  void set_itemtext(int popIndex, const char *text);
  int exec(int arg);
  void draw();
  void open(s32 a1, u16 a2);
};
#endif