#pragma once
#include <types.h>

struct ModelConfig {
  int modelFile;
  int textureIndex;
  u8 unk[0x5c - 8];
};

struct TextureConfig {
  u8 _00[0x10];
  u32 textureFile;
  u8 _14[0x14];
};

