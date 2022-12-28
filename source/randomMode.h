#include <popup.h>
#include <utilitysato.h>
#include <savedata.h>

class RandomMode {
 public:
  void Update(UtilitySato::CModeSwitch* menuOrganize);
  enum State {
    INIT,
    POPUP_CONFIRM,
    POPUP_HELP,
    MAIN_LOOP,
    POPUP_KEEP,
    POPUP_RESTART,
    POPUP_INVALID,
    END
  };
  RandomMode();

 private:
  int GetRandomPlayer(int pos);
  bool IsPlayerBanned(int player);
  void BackupData();
  void RestoreData();

  cPopup* m_popupConfirm;
  cPopup* m_popupKeep;
  cPopup* m_popupInvalid;
  int m_timer;
  int m_slot;
  int m_state;
  bool m_valid;
  bool m_picked_players[0x19c];
  _SV_TEAM_INFO m_backup;
};