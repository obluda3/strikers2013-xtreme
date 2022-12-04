#include <popup.h>
#include <utilitysato.h>

class RandomMode {
 public:
  void Update(UtilitySato::CModeSwitch* menuOrganize);
  RandomMode();

 private:
  int GetRandomPlayer(int pos);
  bool IsPlayerBanned(int player);

  cPopup* m_popup;
  int m_timer;
  int m_slot;
  int m_state;
  bool m_picked_players[0x19c];
};