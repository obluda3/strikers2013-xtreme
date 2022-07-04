#include <kamek.h>
#include "xtreme_settings.h"
#include "keyboard.h"

u16** pKeybordTbl = (u16**)0x804C9DD0;
u16 EmptyKeyboard[] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
u16 LatinUppercase[] = { 'Ａ','Ｂ','Ｃ','Ｄ','Ｅ','Ｆ','Ｇ','Ｈ','Ｉ','Ｊ','Ｋ','Ｌ','Ｍ','Ｎ','Ｏ', -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 'Ｐ','Ｑ','Ｒ','Ｓ','Ｔ','Ｕ','Ｖ','Ｗ','Ｘ','Ｙ','Ｚ', -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
u16 LatinLowercase[] = { 'ａ','ｂ','ｃ','ｄ','ｅ','ｆ','ｇ','ｈ','ｉ','ｊ','ｋ','ｌ','ｍ','ｎ','ｏ', -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 'ｐ','ｑ','ｒ','ｓ','ｔ','ｕ','ｖ','ｗ','ｘ','ｙ','ｚ', -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
u16 CyrilicUppercase[] = { 'А','Б','В','Г','Д','Е','Ё','Ж','З','И','Й','К','Л','М','Н','О','П', -1, -1, -1, -1, -1, -1, -1, -1, 'Р','С', 'Т','У','Ф','Х','Ц','Ч','Ш','Щ','Ъ','Ы','Ь','Э','Ю','Я', -1, -1, -1, -1, -1 };
u16 CyrilicLowercase[] = { 'а','б','в','г','д','е','ё','ж','з','и','й','к','л','м','н','о','п', -1, -1, -1, -1, -1, -1, -1, -1, 'р','с','т','у','ф','х','ц','ч','ш','щ','ъ','ы','ь','э','ю','я', -1, -1, -1, -1, -1 };

void SwitchKeyboardLayout(int layout)
{
    switch (layout)
    {
        case KEY_JPN:
            pKeybordTbl[0] = (u16*)0x8049BB60;
            pKeybordTbl[1] = (u16*)0x8049BBBC;
            pKeybordTbl[2] = (u16*)0x8049BC08;
            pKeybordTbl[3] = (u16*)0x8049BC64;
            break;
        case KEY_LTN:
            pKeybordTbl[0] = LatinUppercase;
            pKeybordTbl[1] = EmptyKeyboard;
            pKeybordTbl[2] = LatinLowercase;
            pKeybordTbl[3] = EmptyKeyboard;
            break;
        case KEY_CRL:
            pKeybordTbl[0] = CyrilicUppercase;
            pKeybordTbl[1] = EmptyKeyboard;
            pKeybordTbl[2] = CyrilicLowercase;
            pKeybordTbl[3] = EmptyKeyboard;
            break;
    }
}