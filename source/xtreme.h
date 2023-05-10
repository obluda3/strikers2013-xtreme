#include <types.h>

static s16 rainbowColors[] = {
    8700, 8840, 8880, 8480, 8271, 8174, 8276, 8137, 8317, 8617, 8716,
};

#define FRAME_PER_COLOR 7
class XtremeSettings {
public:
  void DrawMenu();
  static void Init();
  void Save();
  static void MusicLoop(int state, void *arg);
  void Exec();
  int GetKeyboardType();
  bool IsMovePowerDisplayed();
  bool AreOpeningsAllowed();
  int GetInterface();
  static bool IsWiimmfi();


private:
  u8 m_pos;
  s8 m_allowOpenings;
  s8 m_movePower;
  s8 m_keyboardType;
  s8 m_interface;
  // s32 m_xOff;
  // s32 m_yOff;
};

extern XtremeSettings Settings;