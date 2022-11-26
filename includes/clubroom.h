#include <nameWindow.h>
#include <types.h>
#include <utilitysato.h>

class ClubroomManager {
 public:
  static ClubroomManager* getInstance();
  bool isAllActorLoaded();
};

namespace NSClubroomMenu {
namespace MENU_CUFM {
enum MODE {};
};
void BstCufTask_Start(int a1, MENU_CUFM::MODE mode);
int BstCufTask_Exec();
void BstCufTask_Draw();
int BstCEmbTask_Exec();
void BstCEmbTask_Draw();
void BstCEmbTask_Start();

};  // namespace NSClubroomMenu

namespace CLUBROOM_TC_CB {
namespace MENU {
class CSetCallback : public SpriteAnimationCallback {
 public:
  virtual ~CSetCallback();
  virtual void CallbackFunction(const SSAL_PARTS* a1, const SSAL_USER_DATA* a2, long a3, long a4, float a5, PRIM_SPR*);
};
}  // namespace MENU
}  // namespace CLUBROOM_TC_CB

class CClubroomNumberChange {
 public:
  void Draw();
  void Init(short a1);
  void Term();
  int Exec();
  u32 _00;
  UtilitySato::CModeSwitch modeSwitch;

 private:
  u8 _1C[0x28];
};

class CClubroomMenuTeamCustom {
 public:
  void Init(short a1);
  void RegistLoad();
  void PreExec();
  int Exec();
  void Draw();
  void Term();
  void Start();
  void SetTeamData();
  void TexTerm();
  void thTexLoad();

 private:
  UtilitySato::CModeSwitch m_modeSwitch;
  CSprStudio* m_Text;
  CSprStudio* m_Emblem;
  CSprStudio* m_buttons[5];
  CLUBROOM_TC_CB::MENU::CSetCallback* m_callback;
  s32 m_nextMenu;
  s32 m_curChoice;
  s32 _40;
  CClubroomNumberChange m_numberChange;
  u32 _88;
  u16 m_ot;
  u16 _8E;
  stNameWindow m_nameWindow;
};

struct MenuTeam {
  u8 _00[0x19C];
  s32 _19C;
  u32 _1A0;
  u32 _1A4;
  u8 _1A8[0x28];
  s32 _1D0;
  STRUC_LAYOUT* layouts[4];
  s32 emblem;
  bool isLoading;
  bool _1E9;
  s16 _1EA;
  s32 _1EC;
  s32 _1F0;
  u8 _1F4[0x10];
};