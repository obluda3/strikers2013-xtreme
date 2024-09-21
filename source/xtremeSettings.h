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
  int GetInterface();

  XtremeSettings(s8 allowOpenings, s8 movePower, s8 keyboardType, s8 interface) : m_allowOpenings(allowOpenings), m_movePower(movePower), m_keyboardType(keyboardType), m_interface(interface) {};

private:
  u8 m_pos;
  s8 m_allowOpenings;
  s8 m_movePower;
  s8 m_keyboardType;
  s8 m_interface;
};

extern XtremeSettings* ModSettings;