#include <kamek_asm.S>
.set pics_count, 252

kmWrite16 0x800F8486, pics_count
kmWrite16 0x800f8456, pics_count / 7 - 5 // rows
kmWrite16 0x800F8056, pics_count / 7 - 5 // rows
kmWrite16 0x800f88f6, pics_count / 7
kmWrite32 0x800F8948, 0x38000008 // scrollbar
kmWrite16 0x8013D1B2, 0xff0
kmWrite16 0x80260E62, 0xFF0