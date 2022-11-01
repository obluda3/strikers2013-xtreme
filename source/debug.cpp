#include "kamek.h"

#if DEBUG
// Enables bprintf output
kmWrite32(0x8033a4f0, 0x60000000);
kmWrite32(0x8033a500, 0x60000000);
kmWrite32(0x8033482c, 0x60000000);
kmWrite32(0x8033483c, 0x60000000);
// Disables the ugly debug info
kmWrite32(0x8032CDA0, 0x4BFFFF04);
#endif