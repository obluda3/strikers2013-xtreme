#ifndef SHDFILES
#define SHDFILES
#include <textures.h>

int DCLoad(int idx, s8 unk);
void MDLRegist(int model);
void MDLRelease(int model);
void shdUnpack(unsigned char* compressed, unsigned char* destination);

#endif