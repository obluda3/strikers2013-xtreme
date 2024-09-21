#include <types.h>

#define FRAME_PER_COLOR 7
class Xtreme {
public:
  void DrawMenu();
  static void Init();
  void Save();
  static void MusicLoop(int state, void *arg);
  void Exec();
  static bool IsWiimmfi();


private:
  u8 m_pos;
  s8 m_allowOpenings;
  s8 m_movePower;
  s8 m_keyboardType;
  s8 m_interface;

  static void PerformTextEdits();
  static void CheckForDolphin();
  static void PatchOnlineServer();
  static void CheckForUpdates();
  // s32 m_xOff;
  // s32 m_yOff;
};

extern Xtreme Mod;