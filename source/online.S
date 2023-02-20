#include <kamek_asm.S>
// Overtime
// kmWrite32 0x8025670C, 0x54C0043E

// Timer
kmWrite32 0x80144BC4, 0x38000063

// Items
kmWrite32 0x802566C8, 0x38A00001
kmWrite32 0x8025668C, 0x38A00001

// Matchmaking filter
kmWrite32 0x804A685F, 0x58543200

// Ranking region
kmWrite32 0x80231dc4, 0x38800002
kmWrite32 0x80231F6C, 0x38A00002 