namespace MCHG {
enum MapH {
  MAP_TITLE_SCREEN = 0,
  MAP_MAIN_MENU = 2,
  MAP_MATCH = 3,
  MAP_CLUBROOM = 4,
  MAP_TRAINING = 5,
  MAP_MOVIE = 6,
  MAP_PENALTYKICK = 491,
  MAP_CARAVAN = 492,
};

enum MainMenuMode {
  MODE_MATCH = 0,
  MODE_MATCHSTART = 6,
  MODE_MAIN = 7,
  MODE_TRAINING = 11,
  MODE_SETTINGS = 14,
  MODE_TOURNAMENT = 16,
  MODE_ONLINE = 29,
};

static void FadeOut(int param, void *ptr);
static void CleanUp(int param, void *ptr);
static void DataSet(int param, void *ptr);
static void TopLoop(int param, void *ptr);
static void FadeIn(int param, void *ptr);
static void Finish(int param, void *ptr);
static void thDataSet(void *ptr);

MapH *cur_maph = (MCHG::MapH *)0x8050C42C;
int *cur_mapl = (int *)0x8050C428;
MapH *last_maph = (MCHG::MapH *)0x8050D688;
int *last_mapl = (int *)0x8050D684;
} // namespace MCHG

void MCHGSet(int maph, int mapl, unsigned char flag);
void MCHGSet_MatchEnd();
bool MCHGIsExec();
void MCHGInit();