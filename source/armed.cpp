#include <kamek.h>
#include <players.h>
#include <matchplayer.h>
#include <base\c_stdlib.h>

typedef struct ArmedInfo
{
    u16 source;
    u16 armedId;
} ArmedInfo;

ArmedInfo ArmedTable[] = 
{
    { P_12803TEMMA, P_10008MATSUKAZE_ARMD },
    { P_12813TEMMA, P_10008MATSUKAZE_ARMD },
    { P_12811TSURUGI, P_10010TSURUGI_ARMD },
    { P_12807SHINSUKE, P_10005NISHIZONO_ARMD },
    { P_12810NISHIKI, P_10016NISHIKI_ARMD },
    { P_12805KIRINO, P_10003KIRINO_ARMD },
    { P_12804SHINDO, P_10009SHINDO_ARMD },
    { P_12809FUEI, P_12011FUEI_ARMD },
    { P_12013FUEI, P_12011FUEI_ARMD },
    { P_12815ZANAKU, P_12150ZANAKU_ARMD },
    { P_12816SZANAKU, P_12150ZANAKU_ARMD },
    { P_12812KINAKO, P_12014KINAKO_ARMD },
    { P_12802TSURUGI, P_12012YUICHI_ARMD },
    { P_10008MATSUKAZE, P_10008MATSUKAZE_ARMD },
    { P_10010TSURUGI, P_10010TSURUGI_ARMD },
    { P_10009SHINDO, P_10009SHINDO_ARMD },
    { P_10005NISHIZONO, P_10005NISHIZONO_ARMD },
    { P_10016NISHIKI, P_10016NISHIKI_ARMD },
    { P_10003KIRINO, P_10003KIRINO_ARMD },
    { P_12806AMEMIYA, P_12806AMEMIYA_ARMD },
    { P_12014KINAKO, P_12014KINAKO_ARMD },
    { P_12012YUICHI, P_12012YUICHI_ARMD },
    { P_10350HAKURYU, P_10350HAKURYU_ARMD },
    { P_12050ARUFUA, P_12050ARUFUA_ARMD },
    { P_12055BETA, P_12055BETA_ARMD },
    { P_12056GAMMA, P_12056GAMMA_ARMD },
    { P_12150ZANAKU, P_12150ZANAKU_ARMD },
    { P_12492FURAN, P_12492FURAN_ARMD },
    { P_12011FUEI, P_12011FUEI_ARMD },
    { P_10290AMEMIYA, P_10290AMEMIYA_ARMD },
    { P_10008MATSUKAZE_TNM, P_10008MATSUKAZE_ARMD },
};
// changes the player def to an armed player def that has the original player's face
kmBranchDefAsm(0x800DAE48, 0x800dae4c)
{
    nofralloc
    check_not_mixplusarmed:
        cmpwi r20, P_12492FURAN
        beq epilogue
        cmpwi r20, P_10290AMEMIYA
        beq epilogue
        cmpwi r25, W_MIXIMAX_TRANSFORMATION
        beq epilogue
    setup_memcpy:
        addi r3, r1, 0x318 // player_def sitting in the stack
        mr r4, r17
        li r5, sizeof(PLAYER_DEF)
        bl memcpy    
    get_playerdef:
        li r4, 0
        function_call:
            mr r3, r20
            bl GetPLYIDToPlayerEntryTeam
            cmpwi r3, 0
            li r4, 1
            beq function_call
    change_facemodel:
        addi r17, r1, 0x318
        lwz r3, 0x60(r3) // player_def->matchfacemodel
        stw r3, 0x60(r17)
    epilogue:
        cmpwi r28, 1 // original inst
        blr
}

// Load the original player's face model instead of the armed one
kmBranchDefAsm(0x800DE884, 0x800DE888)
{
    // Fran needs to keep the bodymodel of the armed player
    lwz r3, 0x60(r24) // r3 = armedPlayerDef->matchFaceModel
    check_not_mixplusarmed:
        cmpwi r21, P_12492FURAN
        beq- end
        cmpwi r21, P_10290AMEMIYA
        beq- end
        cmpwi r31, W_MIXIMAX_TRANSFORMATION
        beq- end
        cmpwi r31, W_TAIKOKU_OUKA_TRANSFORMATION
        beq- end
    swap_facemdl:
        li r4, 0
        get_playerdef:
            mr r3, r21
            bl GetPLYIDToPlayerEntryTeam // shitty hack, i don't know which team 
            cmpwi r3, 0 // it is but we don't care about that, I just call it two times
            li r4, 1
            beq get_playerdef // if it didn't work the first time, it'll work the second time!
        lwz r3, 0x60(r3)
    end:
        blr
}

int newGetArmedPlyId(u32 player)
{
    const int size = sizeof(ArmedTable) / sizeof(ArmedInfo);
    for (int i = 0; i < size; i++)
    {
        if (ArmedTable[i].source == player)
        {
            return ArmedTable[i].armedId;
        }
    }
    return 0;
}

kmBranch(0x800beb94, newGetArmedPlyId);