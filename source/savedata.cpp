#include <kamek.h>

// sys magic number
kmWrite32(0x80041040, 0x38600028);
kmWrite32(0x80041F10, 0x38800028);
kmWrite32(0x80044750, 0x38600028);
kmWrite32(0x80044d40, 0x28000028);
kmWrite32(0x80046868, 0x38600028);

// usr magic number
kmWrite32(0x800410AC, 0x39000049);
kmWrite32(0x80041F04, 0x38800049);
kmWrite32(0x80044744, 0x38000049);
kmWrite32(0x8004685C, 0x38000049);
kmWrite32(0x80041378, 0x38600049);
kmWrite32(0x80041FE4, 0x28000049);
kmWrite32(0x80044d68, 0x20650049);
kmWrite32(0x80044d6C, 0x3805FFB7);