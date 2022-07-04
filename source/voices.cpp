#include <kamek.h>
#include <shd_mem.h>

static char** VoiceLinesList;

char* NewVoicelines[] = 
{
    "VCE_WANDABA_REQUESTPASS",
    "VCE_WANDABA_REQUESTSH",
    "VCE_WANDABA_REQUESTDEF",
    "VCE_WANDABA_CHARACHANGE",
    "VCE_WANDABA_OKPASS",
    "VCE_WANDABA_OKSHOOT",
    "VCE_WANDABA_OKSHOOT",
    "VCE_WANDABA_OKSHOOT",
    "VCE_WANDABA_SHOOT02A0",
    "VCE_WANDABA_SHOOT02A0",
    "VCE_ASSIST_OFFENSE_02_A0_11201_WANDABA",
    "VCE_WANDABA_SHOOT01A0",
    "VCE_WANDABA_SHOOT01A1",
    "VCE_WANDABA_SHOOT01A2",
    "VCE_WANDABA_DAMAGE1",
    "VCE_WANDABA_DAMAGE2",
    "VCE_WANDABA_CHARACHANGE",
    "VCE_WANDABA_GOAL01",
    "VCE_WANDABA_GOAL02",
    "VCE_WANDABA_GOAL01",
    "VCE_WANDABA_CHARACHANGE",
    "VCE_WANDABA_CHARACHANGE",
    "VCE_WANDABA_HISSTART",
    "VCE_WANDABA_HISSTART",
    "VCE_WANDABA_HISSTART",
    "VCE_WANDABA_HISSTART",
    "VCE_WANDABA_VOICEOFF",
    "VCE_WANDABA_VOICEDEF",
    "VCE_WANDABA_VOICETC",
    "VCE_SPECIAL_02_A0_11201_WANDABA",
    "VCE_REQUEST_PASS_A0_10101_SHINOYAMA",
    "VCE_REQUEST_SHOOT_A0_10101_SHINOYAMA",
    "VCE_REQUEST_DEFENSE_A0_10101_SHINOYAMA",
    "VCE_CHARACTER_CHANGE_A0_10101_SHINOYAMA",
    "VCE_OK_PASS_A0_10101_SHINOYAMA",
    "VCE_OK_SHOOT_A0_10101_SHINOYAMA",
    "VCE_OK_SHOOT_A0_10101_SHINOYAMA",
    "VCE_OK_SHOOT_A0_10101_SHINOYAMA",
    "VCE_SHOUT_02_A0_10101_SHINOYAMA",
    "VCE_SHOUT_02_A0_10101_SHINOYAMA",
    "VCE_SHOUT_01_A3_10101_SHINOYAMA",
    "VCE_SHOUT_01_A0_10101_SHINOYAMA",
    "VCE_SHOUT_01_A1_10101_SHINOYAMA",
    "VCE_SHOUT_01_A2_10101_SHINOYAMA",
    "VCE_DAMAGE_01_A0_10101_SHINOYAMA",
    "VCE_DAMAGE_02_A0_10101_SHINOYAMA",
    "VCE_CHARACTER_CHANGE_A0_10101_SHINOYAMA",
    "VCE_GOAL_01_A0_10101_SHINOYAMA",
    "VCE_GOAL_02_A0_10101_SHINOYAMA",
    "VCE_GOAL_03_A0_10101_SHINOYAMA",
    "VCE_VOICE_COMMON_A0_10101_SHINOYAMA",
    "VCE_VOICE_COMMON_A0_10101_SHINOYAMA",
    "VCE_HISSATU_SHOOT_A0_10101_SHINOYAMA",
    "VCE_HISSATU_DRIBLE_A0_10101_SHINOYAMA",
    "VCE_HISSATU_BLOCK_A0_10101_SHINOYAMA",
    "VCE_HISSATU_KEEPER_A0_10101_SHINOYAMA",
    "VCE_VOICE_OFFENSE_A0_10101_SHINOYAMA",
    "VCE_VOICE_DEFENSE_A0_10101_SHINOYAMA",
    "VCE_VOICE_ETC_A0_10101_SHINOYAMA",
    "VCE_SHOUT_01_A4_10101_SHINOYAMA",
    "VCE_ASSIST_PERSONAL_01_A0_11760_AFURO",
    "VCE_REQUEST_SHOOT_A0_0190_AFURO",
    "VCE_ASSIST_DEFENSE_01_A0_11760_AFURO",
    "VCE_CHARACTER_CHANGE_A0_0190_AFURO",
    "VCE_OK_PASS_A0_0190_AFURO",
    "VCE_OK_SHOOT_A1_0190_AFURO",
    "VCE_OK_SHOOT_A1_0190_AFURO",
    "VCE_OK_SHOOT_A1_0190_AFURO",
    "VCE_SHOUT_02_A0_0190_AFURO",
    "VCE_SHOUT_02_A0_0190_AFURO",
    "VCE_SHOUT_01_A4_0190_AFURO",
    "VCE_SHOUT_01_A0_0190_AFURO",
    "VCE_SHOUT_01_A1_0190_AFURO",
    "VCE_SHOUT_01_A3_0190_AFURO",
    "VCE_DAMAGE_01_A1_0190_AFURO",
    "VCE_DAMAGE_02_A0_0190_AFURO",
    "VCE_CHARACTER_CHANGE_A0_0190_AFURO",
    "VCE_GOAL_01_A0_0190_AFURO",
    "VCE_GOAL_02_A0_0190_AFURO",
    "VCE_GOAL_03_A0_0190_AFURO",
    "VCE_CHARACTER_CHANGE_A0_0190_AFURO",
    "VCE_CHARACTER_CHANGE_A0_0190_AFURO",
    "VCE_HISSATU_START_A1_0190_AFURO",
    "VCE_VOICE_COMMON_A0_11760_AFURO",
    "VCE_VOICE_COMMON_A0_11760_AFURO",
    "VCE_VOICE_COMMON_A0_11760_AFURO",
    "VCE_VOICE_OFFENSE_A0_11760_AFURO",
    "VCE_VOICE_DEFENSE_A0_11760_AFURO",
    "VCE_VOICE_ETC_A0_11760_AFURO",
    "VCE_VOICE_ETC_A0_11760_AFURO",
    "VCE_ASSIST_PERSONAL_01_a0_11717_ISHIDO",
    "VCE_REQUEST_SHOOT_A0_11710_GOUENJI",
    "VCE_ASSIST_DEFENSE_01_A0_11717_ISHIDO",
    "VCE_CHARACTER_CHANGE_A0_11710_GOUENJI",
    "VCE_OK_PASS_A0_11710_GOUENJI",
    "VCE_OK_SHOOT_A0_11710_GOUENJI",
    "VCE_OK_SHOOT_A0_11710_GOUENJI",
    "VCE_OK_SHOOT_A0_11710_GOUENJI",
    "VCE_SHOUT_02_A0_11710_GOUENJI",
    "VCE_SHOUT_02_A0_11710_GOUENJI",
    "VCE_SHOUT_01_A4_11710_GOUENJI",
    "VCE_SHOUT_01_A0_11710_GOUENJI",
    "VCE_SHOUT_01_A3_11710_GOUENJI",
    "VCE_SHOUT_01_A2_11710_GOUENJI",
    "VCE_DAMAGE_01_A0_11710_GOUENJI",
    "VCE_DAMAGE_02_A0_11710_GOUENJI",
    "VCE_CHARACTER_CHANGE_A0_11710_GOUENJI",
    "VCE_GOAL_01_A0_11710_GOUENJI",
    "VCE_GOAL_02_A0_11710_GOUENJI",
    "VCE_GOAL_03_A0_11710_GOUENJI",
    "VCE_VOICE_COMMON_A0_11710_GOUENJI",
    "VCE_VOICE_COMMON_A0_11710_GOUENJI",
    "VCE_HISSATU_SHOOT_A0_11710_GOUENJI",
    "VCE_ISHIDO_IMADA",
    "VCE_HISSATU_BLOCK_A0_11710_GOUENJI",
    "VCE_HISSATU_KEEPER_A0_11710_GOUENJI",
    "VCE_VOICE_OFFENSE_A0_11717_ISHIDO",
    "VCE_VOICE_DEFENSE_A1_11717_ISHIDO",
    "VCE_VOICE_ETC_A0_11717_ISHIDO",
    "VCE_SPECIAL_01_A0_11710_GOUENJI",
    "VCE_REQUEST_PASS_A0_12330_SARU",
    "VCE_REQUEST_SHOOT_A0_12817_SARU",
    "VCE_REQUEST_DEFENSE_A0_12330_SARU",
    "VCE_CHARACTER_CHANGE_A0_12330_SARU",
    "VCE_OK_PASS_A0_12330_SARU",
    "VCE_OK_SHOOT_A0_12330_SARU",
    "VCE_OK_SHOOT_A0_12330_SARU",
    "VCE_OK_SHOOT_A0_12330_SARU",
    "VCE_SHOUT_02_A0_12817_SARU",
    "VCE_SHOUT_02_A0_12817_SARU",
    "VCE_SHOUT_01_A0_12817_SARU",
    "VCE_SHOUT_01_A0_12817_SARU",
    "VCE_SHOUT_02_A0_12817_SARU",
    "VCE_SHOUT_03_A0_12817_SARU",
    "VCE_DAMAGE_01_A0_12817_SARU",
    "VCE_DAMAGE_02_A0_12817_SARU",
    "VCE_REQUEST_SHOOT_A0_12817_SARU",
    "VCE_GOAL_01_A0_12817_SARU",
    "VCE_GOAL_04_A0_12330_SARU",
    "VCE_GOAL_01_A0_12817_SARU",
    "VCE_HISSATU_DRIBLE_A0_12330_SARU",
    "VCE_REQUEST_SHOOT_A0_12817_SARU",
    "VCE_HISSATU_SHOOT_A0_12330_SARU",
    "VCE_HISSATU_DRIBLE_A0_12330_SARU",
    "VCE_HISSATU_BLOCK_A0_12330_SARU",
    "VCE_HISSATU_KEEPER_A0_12330_SARU",
    "VCE_VOICE_OFFENSE_A0_12817_SARU",
    "VCE_VOICE_DEFENSE_A0_12330_SARU",
    "VCE_VOICE_ETC_A0_12330_SARU",
    "VCE_SPECIAL_01_A0_12330_SARU",
    "VCE_HISSATU_DRIBLE_A0_12330_SARU",
    "VCE_HISSATU_DRIBLE_A0_12330_SARU",
    "VCE_HISSATU_DRIBLE_A0_12330_SARU"
};

void LoadNewVoicelines()
{
    char*** voiceLines = (char***)0x8051ECA8;
    char** defaultVoiceLines = *voiceLines;
    int defaultVoiceCount = *((int*)0x8051ECAC);
    int newVoiceCount = sizeof(NewVoicelines) / sizeof(char**);
    int count = newVoiceCount + defaultVoiceCount;
    int length = (count * sizeof(char*) + 0x1F) & ~0x1F;
    char** voices = (char**) MEMAlloc(length, 32, 3, 31);
    for (int i = 0; i < defaultVoiceCount; i++)
        voices[i] = defaultVoiceLines[i];
    for (int i = 0; i < newVoiceCount; i++)
        voices[i + defaultVoiceCount] = NewVoicelines[i];
    *voiceLines = voices;
}

kmBranch(0x8002B5DC, LoadNewVoicelines);