#ifndef POPUP
#define POPUP
#include <types.h>

class cPopup {
 public:
  void alloc(int count, int textureLayer);
  void set_itemtext(int index, int textId);
  void set_itemtext(int index, const char* text);
  int exec(int arg);
  void add_item(int index, int textEntry, unsigned short isOption);
  void add_item(int index, const char* text, unsigned short isOption);
  void draw();
  void open(s32 a1, u16 a2);

 private:
  u8 _00[0xF0];
};
#endif