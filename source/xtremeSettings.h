#include <types.h>

#define FRAME_PER_COLOR 7
class XtremeSettings {
public:
  void DrawMenu();
  void Save();
  static void MusicLoop(int state, void *arg);
  void Exec();
  int GetKeyboardType();
  bool IsMovePowerDisplayed();
  bool AreOpeningsAllowed();
  bool IsMixiChargeMode();

  XtremeSettings(s8 allowOpenings, s8 movePower, s8 keyboardType, s8 mixiMode) : m_allowOpenings(allowOpenings), m_movePower(movePower), m_keyboardType(keyboardType), m_mixiMode(mixiMode) {};

private:
  u8 m_pos;
  s8 m_allowOpenings;
  s8 m_movePower;
  s8 m_keyboardType;
  s8 m_mixiMode;
};

extern XtremeSettings* ModSettings;