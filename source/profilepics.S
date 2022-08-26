#include <kamek_asm.S>
.set pics_count, 252

kmWrite16 0x800F8486, pics_count
kmWrite16 0x800f8456, pics_count / 7 - 5 // rows
kmWrite16 0x800F8056, pics_count / 7 - 5 // rows
kmWrite16 0x800f88f6, pics_count / 7
kmWrite32 0x800F8948, 0x38000008 // scrollbar
kmWrite16 0x8013D1B2, 0xfC0
kmWrite16 0x80260E62, 0xFC0
kmWrite16 0x8026238E, 0xFC0
// fix online profile
kmWrite32 0x8023a250, 0x60000000
kmWrite32 0x80260e4c, 0x2c0000ff // signed -> unsigned
kmWrite32 0x8026237C, 0x2c0000ff
kmWrite32 0x80260e54, 0x40820014
kmWrite32 0x80262380, 0x40820014