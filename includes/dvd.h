#ifndef DVD_UTILS
#define DVD_UTILS
#include <shd_mem.h>
struct DVDHandle
{
	u32 _unk[12];
	u32 address, length;
	u32 _unk38;
};

extern "C" {
	int DVDConvertPathToEntrynum(const char *path);
	bool DVDFastOpen(int entrynum, DVDHandle* handle);
	int DVDReadPrio(DVDHandle* handle, void* buffer, int length, int offset, int unk);
	bool DVDClose(DVDHandle* handle);
}


#endif