#ifndef TEXTURES
#define TEXTURES

void TEX_isUse(int idx);
void TEX_getFileLabel(int idx);
void TEX_PageSet(int a1, int a2);
int TEX_Alloc(int fileLabel, int a2, int a3);
int TEXGetTPageToFlab(int tex);
int TEXLoad_Alloc(int fileIndex);
int TEXLoad(int idx, int page);
int TEXLoad_Emblem(int idx);
int TEXLoad_EmblemLL(int idx, int page);

struct PRIM_SPR {
  s32 color;
  s32 entryInfo;
  s16 texFlag;
  s16 ot;
  s16 x;
  s16 y;
  s16 width;
  s16 height;
  s16 field_14;
  s16 field_16;
  s32 field_18;
  s16 block_x;
  s16 block_y;
  s16 block_width;
  s16 block_height;
  s32 field_24;
  s32 field_28;
};
struct SHD_TEXCUT {
  s16 x;
  s16 y;
  s16 width;
  s16 height;
  s16 field_8;
  s16 field_A;
  int field_C;
};
void shdSetSprtM(PRIM_SPR* a1);
void set_tcut_to_uv(SHD_TEXCUT const* a1, PRIM_SPR* a2, signed char a3);

#endif