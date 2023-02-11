#ifndef SHDFILES
#define SHDFILES

int DCLoad(int idx, s8 unk);
int TEXLoad(int idx, int page);
int TEXLoad_Emblem(int idx);
int TEXLoad_EmblemLL(int idx, int page);
void MDLRegist(int model);
void MDLRelease(int model);
void shdUnpack(unsigned char* compressed, unsigned char* destination);

#endif