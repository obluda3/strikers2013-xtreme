#include "kamekLoader.h"

int loadKamekBinary();

typedef void *(*MEMAlloc_t) (int size, int align, int a3, int a4);
typedef void (*MEMFree_t) (void *buffer);

struct loaderFunctionsEx {
	loaderFunctions base;
	MEMAlloc_t memAlloc;
	MEMFree_t memFree;
};

void *allocAdapter(u32 size, bool isForCode, const loaderFunctions *funcs) {
	const loaderFunctionsEx *funcsEx = (const loaderFunctionsEx *)funcs;
	return funcsEx->memAlloc(size, 32, 3, 31);
}
void freeAdapter(void *buffer, bool isForCode, const loaderFunctions *funcs) {
	const loaderFunctionsEx *funcsEx = (const loaderFunctionsEx *)funcs;
	funcsEx->memFree(buffer);
}

const loaderFunctionsEx functions = {
	{(OSReport_t) 0x8028A0D0,
	(OSFatal_t) 0x8028C3C0,
	(DVDConvertPathToEntrynum_t) 0x802958B0,
	(DVDFastOpen_t) 0x80295BC0,
	(DVDReadPrio_t) 0x80295F90,
	(DVDClose_t) 0x80295D50,
	(sprintf_t) 0x802BB0B0,
	allocAdapter,
	freeAdapter},
	(MEMAlloc_t) 0x80022B3C,
	(MEMFree_t) 0x80022C70
};

int loadKamekBinary()
{
	loadKamekBinaryFromDisc(&functions.base, "Code/CustomCode.bin");
	functions.base.OSReport("Writing game id...\n");
	return 1;
}
kmCall(0x803313D0, loadKamekBinary);

