#ifndef SHD_MEM
#define SHD_MEM

void* MEMAlloc(unsigned long size, int align, int a3, int a4);
void MEMFree(void* buffer);
void shdMemGet(unsigned long size, int a2, signed char a3);
void shdMemFree(void*);

#endif