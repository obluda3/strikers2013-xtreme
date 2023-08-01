#include <kamek.h>

int entry_num = 0;
struct DVDHandle {
  u32 _unk[12];
  u32 address, length;
  u32 _unk38;
};

extern "C" {
int DVDConvertPathToEntrynum(char *path);
void DVDFastOpen(int entrynum, DVDHandle *handle);
void DVDReadPrio(DVDHandle *handle, void *buffer, int size, int a4, int a5);
void DVDClose(DVDHandle *handle);
}

int is_file_modified();
void shdFileLoadBeginWrapper(int ftyp, int offset, int size,
                             unsigned char *buffer);
void shdSysFileLoad(const char *filename, int offset, void *dest, int size);
void shdSysFileExist(const char *filename);
void shdFileLoadSync(int a1);
void *MEMAlloc(unsigned long size, int align, int a3, int a4);
void MEMFree(void *buf);
void cprintf(char *format, ...);
void bprintf(char *format, ...);
void shdFileLoadBegin(int ftyp, int offset, int size, unsigned char *buffer);
void wiiFileLoadBegin(int ftyp, int offset, int size, unsigned char *buffer);

struct BinHeader {
  int filecount;
  int padfactor;
  int mulfactor;
  int shiftfactor;
  unsigned int mask[1];
};

unsigned int bswap32(unsigned int x) {
  return ((x & 0xFF000000u) >> 24) | ((x & 0xFF0000u) >> 8) |
         ((x & 0xFF00u) << 8) | ((x & 0xFF) << 24);
}

int bswap32(int x) {
  return ((x & 0xFF000000u) >> 24) | ((x & 0xFF0000u) >> 8) |
         ((x & 0xFF00u) << 8) | ((x & 0xFF) << 24);
}

BinHeader **flab_tbl = (BinHeader **)0x805255B8;
int *ftyp_cnv = (int *)0x804C6CA4;
int *ftyp_fofs = (int *)0x804C6C90;
char **ftyp_fname = (char **)0x804C6C68;
char *archive_names[] = {"grp", "scn", "scn_sh", "ui", "dat"};

int* isWiiFix = (int*)0x805060DC;

struct Reroute {
    int origFile;
    int newFile;
};

Reroute reroutedFiles[] = {
    {32525, 32525},
    {32521, 32521},
    {3650, 3640},
    {4174, 4164},
    {4543, 4533},
    {3649, 3695},
    {4173, 4222},
    {4542, 4591},
    {3648, 3683},
    {4172, 4209},
    {4541, 4578},
    {3652, 3756},
    {4176, 4283},
    {4545, 4652},
    {30030, 32235},
    {30031, 32246},
    {-1, -1}

};

int getRerouted(int index) {
    if (!*isWiiFix) return -1;
    for (Reroute* r = reroutedFiles; r->origFile != -1; r++) {
        if (r->origFile == index) return r->newFile;
    }
    return -1;
}

char *fileLoadBegin(int ftyp, int offset, int size, unsigned char *buffer) {
  BinHeader *archive = flab_tbl[ftyp];
  int shiftfactor = bswap32(archive->shiftfactor);
  int padfactor = bswap32(archive->padfactor);
  int index;
  for (index = 1; index < 9999; index++) {
    unsigned int offsize = bswap32(archive->mask[index]);
    int cur_offset = (offsize >> shiftfactor) * padfactor;
    if (cur_offset == offset)
      break;
  }

  index -= 1;
  int realIndex = index + 10000*ftyp;
  int rerouted = getRerouted(realIndex);
  if (rerouted != -1 && rerouted != realIndex) {
    ftyp = rerouted / 10000;
    BinHeader *tmpArchive = flab_tbl[ftyp];
    int shift = bswap32(tmpArchive->shiftfactor);
    int pad = bswap32(tmpArchive->padfactor);
    int mul = bswap32(tmpArchive->mulfactor);
    int mask = bswap32(archive->mask[0]);
    unsigned int offsize = bswap32(archive->mask[rerouted+1 - 10000*ftyp]);
    offset = (offsize >> shift) * pad;
    int sz = (offsize & mask) * mul;
    size = ((sz + pad - 1) & ~(pad - 1));
    MEMFree(buffer);
    buffer = (unsigned char*)MEMAlloc(size, -32, 3, 31);
  }

  char path[256];
  sprintf(path, "Modified/%s/%d.bin", archive_names[ftyp], index);
  int entrynum = DVDConvertPathToEntrynum(path);
  cprintf(" realpath=%s rerouted=%d", path, rerouted);
  if (entrynum < 0 || rerouted != -1) {
    shdFileLoadBegin(ftyp, offset, size, buffer);
    return (char *)buffer;
  }
  cprintf(" patched");
  DVDHandle handle;
  DVDFastOpen(entrynum, &handle);
  int roundedLength = (handle.length + 0x1F) & ~0x1F;
  void *newbuffer = (void *)buffer;
  if (roundedLength > size) {
    MEMFree(buffer);
    newbuffer = MEMAlloc(roundedLength, -32, 3, 31);
  }
  DVDReadPrio(&handle, newbuffer, roundedLength, 0, 2);
  DVDClose(&handle);

  return (char *)newbuffer;
}

// we hook into the fileLoadBegin call, then replace the buffer address in the stack
// with our newly allocated one
// very beautiful hooks
asm void patch_stack_32() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    bl fileLoadBegin
    stw r3, 48(r1)
    lwz r0, 0x14(r1)
    addi r1, r1, 0x10
    mtlr r0
    blr
}
kmCall(0x80024928, patch_stack_32);
kmCall(0x80026744, patch_stack_32);
kmCall(0x80026e90, patch_stack_32);
kmCall(0x8002a6a8, patch_stack_32);
kmCall(0x8002ded4, patch_stack_32);
kmCall(0x8002e350, patch_stack_32);
kmCall(0x8002e80c, patch_stack_32);
asm void patch_stack_12() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    bl fileLoadBegin
    stw r3, 28(r1)
    lwz r0, 0x14(r1)
    addi r1, r1, 0x10
    mtlr r0
    blr
}
kmCall(0x80024ba4, patch_stack_12);
kmCall(0x80025228, patch_stack_12);
kmCall(0x80026ac8, patch_stack_12);
kmCall(0x800270b0, patch_stack_12);
kmCall(0x800281d0, patch_stack_12);
kmCall(0x80028608, patch_stack_12);
kmCall(0x80028ec8, patch_stack_12);
kmCall(0x8002910c, patch_stack_12);
kmCall(0x80029368, patch_stack_12);
kmCall(0x800296b4, patch_stack_12);
kmCall(0x800299b4, patch_stack_12);
kmCall(0x8002a884, patch_stack_12);
kmCall(0x8002bcc4, patch_stack_12);
kmCall(0x8002c188, patch_stack_12);
kmCall(0x8002c42c, patch_stack_12);
kmCall(0x8002d54c, patch_stack_12);
kmCall(0x8002d7fc, patch_stack_12);
kmCall(0x8002da70, patch_stack_12);
kmCall(0x8002e12c, patch_stack_12);
kmCall(0x8002e570, patch_stack_12);
kmCall(0x8002ea48, patch_stack_12);
asm void patch_stack_24() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    bl fileLoadBegin
    stw r3, 40(r1)
    lwz r0, 0x14(r1)
    addi r1, r1, 0x10
    mtlr r0
    blr
}
kmCall(0x80024ef4, patch_stack_24);
asm void patch_stack_16() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    bl fileLoadBegin
    stw r3, 32(r1)
    lwz r0, 0x14(r1)
    addi r1, r1, 0x10
    mtlr r0
    blr
}
kmCall(0x80025c7c, patch_stack_16);
kmCall(0x8002d018, patch_stack_16);
asm void patch_stack_52() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    bl fileLoadBegin
    stw r3, 68(r1)
    lwz r0, 0x14(r1)
    addi r1, r1, 0x10
    mtlr r0
    blr
}
kmCall(0x80026484, patch_stack_52);
kmCall(0x8002a4cc, patch_stack_52);
asm void patch_stack_60() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    bl fileLoadBegin
    stw r3, 76(r1)
    lwz r0, 0x14(r1)
    addi r1, r1, 0x10
    mtlr r0
    blr
}
kmCall(0x800289c0, patch_stack_60);
asm void patch_stack_132() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    bl fileLoadBegin
    stw r3, 148(r1)
    lwz r0, 0x14(r1)
    addi r1, r1, 0x10
    mtlr r0
    blr
}
kmCall(0x80029d64, patch_stack_132);
asm void patch_stack_112() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    bl fileLoadBegin
    stw r3, 128(r1)
    lwz r0, 0x14(r1)
    addi r1, r1, 0x10
    mtlr r0
    blr
}
kmCall(0x80029f38, patch_stack_112);
asm void patch_stack_92() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    bl fileLoadBegin
    stw r3, 108(r1)
    lwz r0, 0x14(r1)
    addi r1, r1, 0x10
    mtlr r0
    blr
}
kmCall(0x8002a114, patch_stack_92);
asm void patch_stack_72() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    bl fileLoadBegin
    stw r3, 88(r1)
    lwz r0, 0x14(r1)
    addi r1, r1, 0x10
    mtlr r0
    blr
}
kmCall(0x8002a2f0, patch_stack_72);
asm void patch_stack_152() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    bl fileLoadBegin
    stw r3, 168(r1)
    lwz r0, 0x14(r1)
    addi r1, r1, 0x10
    mtlr r0
    blr
}
kmCall(0x8002b3a8, patch_stack_152);
asm void patch_stack_76() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    bl fileLoadBegin
    stw r3, 92(r1)
    lwz r0, 0x14(r1)
    addi r1, r1, 0x10
    mtlr r0
    blr
}
kmCall(0x8002cb5c, patch_stack_76);
asm void patch_stack_56() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    bl fileLoadBegin
    stw r3, 72(r1)
    lwz r0, 0x14(r1)
    addi r1, r1, 0x10
    mtlr r0
    blr
}
kmCall(0x8002cda0, patch_stack_56);
asm void patch_stack_36() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    bl fileLoadBegin
    stw r3, 52(r1)
    lwz r0, 0x14(r1)
    addi r1, r1, 0x10
    mtlr r0
    blr
}
kmCall(0x8002d274, patch_stack_36);

asm void patch_buffer_r24() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    bl fileLoadBegin
    stw r3, 4(r24)
    lwz r0, 0x14(r1)
    addi r1, r1, 0x10
    mtlr r0
    blr
}
kmCall(0x8002ED70, patch_buffer_r24);

asm void patch_buffer_r22() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    bl fileLoadBegin
    stw r3, 4(r22)
    lwz r0, 0x14(r1)
    addi r1, r1, 0x10
    mtlr r0
    blr
}
kmCall(0x8002EF90, patch_buffer_r22);

asm void patch_buffer_r26() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    bl fileLoadBegin
    stw r3, 4(r26)
    lwz r0, 0x14(r1)
    addi r1, r1, 0x10
    mtlr r0
    blr
}
kmCall(0x8002F868, patch_buffer_r26);
kmCall(0x8002fbbc, patch_buffer_r26);
kmCall(0x80030024, patch_buffer_r26);
kmCall(0x80030fd8, patch_buffer_r26);
kmCall(0x80030c28, patch_buffer_r26);
kmCall(0x8003084c, patch_buffer_r26);
kmCall(0x80030478, patch_buffer_r26);

kmWrite32(0x80024958, 0x60000000);
kmWrite32(0x80024BD4, 0x60000000);
kmWrite32(0x80024F24, 0x60000000);
kmWrite32(0x80025258, 0x60000000);
kmWrite32(0x80025CAC, 0x60000000);
kmWrite32(0x800264B4, 0x60000000);
kmWrite32(0x80026774, 0x60000000);
kmWrite32(0x80026AF8, 0x60000000);
kmWrite32(0x80026EC0, 0x60000000);
kmWrite32(0x800270E0, 0x60000000);
kmWrite32(0x80028200, 0x60000000);
kmWrite32(0x80028638, 0x60000000);
kmWrite32(0x800289F0, 0x60000000);
kmWrite32(0x80028EF8, 0x60000000);
kmWrite32(0x8002913C, 0x60000000);
kmWrite32(0x80029398, 0x60000000);
kmWrite32(0x800296E4, 0x60000000);
kmWrite32(0x800299E4, 0x60000000);
kmWrite32(0x80029D94, 0x60000000);
kmWrite32(0x80029F68, 0x60000000);
kmWrite32(0x8002A144, 0x60000000);
kmWrite32(0x8002A320, 0x60000000);
kmWrite32(0x8002A4FC, 0x60000000);
kmWrite32(0x8002A6D8, 0x60000000);
kmWrite32(0x8002A8B4, 0x60000000);
kmWrite32(0x8002B3D8, 0x60000000);
kmWrite32(0x8002BCF4, 0x60000000);
kmWrite32(0x8002C1B8, 0x60000000);
kmWrite32(0x8002C45C, 0x60000000);
kmWrite32(0x8002CB8C, 0x60000000);
kmWrite32(0x8002CDD0, 0x60000000);
kmWrite32(0x8002D048, 0x60000000);
kmWrite32(0x8002D2A4, 0x60000000);
kmWrite32(0x8002D57C, 0x60000000);
kmWrite32(0x8002D82C, 0x60000000);
kmWrite32(0x8002DAA0, 0x60000000);
kmWrite32(0x8002DF04, 0x60000000);
kmWrite32(0x8002E15C, 0x60000000);
kmWrite32(0x8002E380, 0x60000000);
kmWrite32(0x8002E5A0, 0x60000000);
kmWrite32(0x8002E83C, 0x60000000);
kmWrite32(0x8002EA78, 0x60000000);
kmWrite32(0x8002EDAC, 0x60000000);
kmWrite32(0x8002EFC8, 0x60000000);

// handle bigger mcb1 size
kmCallDefCpp(0x80336568, void, ) { cprintf("mcb sz over\n"); }

kmWrite32(0x8033656C, 0x48000108);