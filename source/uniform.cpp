#include <emblems.h>
#include <kamek.h>
#define UNIFORM_COUNT sizeof(UniformDataTbl) / sizeof(UniformData)

namespace MENU_TP_DATA 
{
    UniformData UniformDataTbl[] = 
    {
        { -1, E_RAIMON, 0, 0xFE3, 1 },
        { -1, E_INAZUMA_JAPAN, 0, 0xFEA, 1 },
        { -1, E_TEIKOKU_GAKUEN, 0, 0xFE4, 1 },
        { -1, E_SHIN_TEIKOKU_GAKUEN, 0, 0xFF8, 1 },
        { -1, E_ZEUS, 0, 0xFE5, 1 },
        { -1, E_ALIEA_GAKUEN, 0, 0xFE7, 1 },
        { -1, E_CHAOS, 0, 0xFE8, 1 },
        { -1, E_GENESIS, 0, 0xFF1, 1 },
        { -1, E_DIAMOND_DUST, 0, 0xFF2, 1 },
        { -1, E_PROMINENCE, 0, 0xFF3, 1 },
        { -1, E_GEMINI_STORM, 0, 0xFF4, 1 },
        { -1, E_EPSILON, 0, 0xFF5, 1 },
        { -1, E_DARK_EMPERORS, 0, 0xFE9, 1 },
        { -1, E_NEO_JAPAN, 0, 0xFEB, 1 },
        { -1, E_SEKAI_SENBATSU_KAI, 0, 0xFEC, 1 },
        { -1, E_LITTLE_GIGANT, 0, 0xFF6, 1 },
        { -1, E_ORPHEUS, 0, 0xFF7, 1 },
        { -1, E_UNICORN, 0, 0xFF9, 1 },
        { -1, E_THE_KINGDOM, 0, 0xFFA, 1 },
        { -1, E_FIRE_DRAGONS, 0, 0xFFB, 1 },
        { -1, E_KNIGHTS_OF_QUEEN, 0, 0xFFC, 1 },
        { -1, E_THE_EMPERORS, 0, 0xFFD, 1 },
        { -1, E_DARK_ANGELS, 0, 0xFED, 1 },
        { -1, E_GIRLS_TEAM, 0, 0xFEF, 1 },
        { -1, E_OGRE, 0, 0xFEE, 1 },
        { -1, E_RAIMON_GO, 0, 0xFF0, 1 },
        { -1, E_ZERO, 0, 0x1002, 1 },
        { -1, E_TENMAS, 0, 0x1004, 1 },
        { -1, E_PROTOCOL_OMEGA, 0, 0x1005, 1 },
        { -1, E_KAKUMEI_SENBATSU, 0, 0x1006, 1 },
        { -1, E_FIFTH_SECTOR, 0, 0x1007, 1 },
        { -1, E_ZANARK_DOMAIN, 0, 0x1008, 1 },
        { -1, E_DESTRUCTCHERS, 0, 0x1009, 1 },
        { -1, E_SHINSEI_INAZUMA_JAPAN, 0, 0x100A, 1 },
        { -1, E_INAZUMA_LEGEND_JAPAN, 0, 0x100B, 1 },
        { -1, E_DRAGON_LINK, 0, 0x100C, 1 },
        { -1, E_HAKUREN_GO, 0, 0x100D, 1 },
        { -1, E_ARAKUMO_GAKUEN, 0, 0x100E, 1 },
        { 0, E_RAIMON_TRACKSUIT_GO, E_RAIMON_GO, 0x1003, 7 },
        { 0, E_RAIMON_TRACKSUIT, E_RAIMON, 0xFFF, 7 },
        { 0, E_INAZUMA_JAPAN_TRACKSUIT, E_INAZUMA_JAPAN, 0xFFE, 7 },
        { P_10010TSURUGI, E_TSURUGI_SCHOOL, E_RAIMON_GO, 0x1001, 4 },
        { P_2475KINO, E_AKI_B, E_RAIMON, 0x1000, 6 },
        { P_2474HARUNA, E_HARUNA_B, E_RAIMON, 0x1000, 6 },
        { P_2473NATSUMI, E_NATSUMI_B, E_RAIMON, 0x1000, 6 },
        { P_3008HUYUKA, E_HUYUKA_B, E_RAIMON, 0x1000, 6 },
        { P_10036AOI, E_AOI_B, E_RAIMON_GO, 0x1000, 6 },
        { P_10037AKANE, E_AKANE_B, E_RAIMON_GO, 0x1000, 6 },
        { P_11701ENDO, E_ENDOU_TRAINER, E_RAIMON_GO, 0x434, 1 },
        { P_11729KIDOU, E_KIDOU_TRAINER, E_TEIKOKU_GAKUEN_GO, 0x435, 1 },
        { P_11760AFURO, E_AFURO_TRAINER, E_KIDOKAWA_SEISHUU, 0x43F, 1 },
        { P_11717ISHIDO, E_ISHIDO, E_FIFTH_SECTOR, 0x440, 0x1 },
        { P_11780SAN, E_SAN, E_SAN, 0x441, 0x1 },
    };

    bool newIsUniformNoPositionFromTeam(int uniform)
    {
        int count = sizeof(UniformDataTbl) / sizeof(UniformData);
        for (int i = 0; i < count; i++)
        {
            if (UniformDataTbl[i].Uniform == uniform)
                return (UniformDataTbl[i]._10 >> 2) & 1;
        }
        return 0;
    }

    bool newIsUniformNoHomeAwayFromTeam(int uniform)
    {
        int count = sizeof(UniformDataTbl) / sizeof(UniformData);
        for (int i = 0; i < count; i++)
        {
            if (UniformDataTbl[i].Uniform == uniform)
                return (UniformDataTbl[i]._10 >> 1) & 1;
        }
        return 0;
    }

    UniformData* newGetUniformData(int index)
    {
        if (index < 0 || index >= (sizeof(UniformDataTbl) / sizeof(UniformData)))
        {
            return 0;
        }
        else
        {
            return &UniformDataTbl[index];
        }
    }
    kmBranch(0x80286218, newIsUniformNoHomeAwayFromTeam);
    kmBranch(0x802861d0, newGetUniformData);
    kmBranch(0x802862f4, newIsUniformNoHomeAwayFromTeam);

    // Makes it so added uniforms are unlocked by default
    kmWrite32(0x8004311C, 0x38600001);
    kmWrite32(0x801E0B1C, 0x2c1b0000 + UNIFORM_COUNT); // cmpwi r27, UNIFORM_COUNT
    kmWrite32(0x8026B0E4, 0x2C1C0000 + UNIFORM_COUNT); // cmpwi r28, UNIFORM_COUNT

}

