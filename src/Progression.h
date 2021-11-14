#ifndef PROGRESSION_H
#define PROGRESSION_H

enum Patches
{
    LAUNCH                    = 4125,
    MYSTERIES_OF_MARAUDON     = 4222,
    RUINS_OF_DIRE_MAUL        = 4297,
    THE_CALL_OF_WAR           = 4375,
    BATTLEGROUNDS             = 4449,
    ASSAULT_ON_BLACKWING_LAIR = 4544,
    RISE_OF_THE_BLOOD_GOD     = 4695,
    DRAGONS_OF_NIGHTMARE      = 4878,
    THE_GATES_OF_AHN_QIRAJ    = 5086,
    STORMS_OF_AZEROTH         = 5302,
    SHADOW_OF_THE_NECROPOLIS  = 5464,
    DRUMS_OF_WAR              = 5875,
    BEFORE_THE_STORM          = 6546,
    THE_BLACK_TEMPLE          = 6898,
    VOICE_CHAT                = 7359,
    THE_GODS_OF_ZUL_AMAN      = 7799,
    FURY_OF_THE_SUNWELL       = 8478,
    ECHO_OF_DOOM              = 9551,
    SECRETS_OF_ULDUAR         = 9947,
    CALL_OF_THE_CRUSADE       = 10505,
    FALL_OF_THE_LICH_KING     = 12340
};

class Progression
{
    private:
        int patchId = sConfigMgr->GetIntDefault("Progression.Patch", Patches::FALL_OF_THE_LICH_KING);
        int expansion;

    public:
        int getPatchId()
        {
            if (patchId != Patches::LAUNCH &&
                patchId != Patches::MYSTERIES_OF_MARAUDON &&
                patchId != Patches::RUINS_OF_DIRE_MAUL &&
                patchId != Patches::THE_CALL_OF_WAR &&
                patchId != Patches::BATTLEGROUNDS &&
                patchId != Patches::ASSAULT_ON_BLACKWING_LAIR &&
                patchId != Patches::RISE_OF_THE_BLOOD_GOD &&
                patchId != Patches::DRAGONS_OF_NIGHTMARE &&
                patchId != Patches::THE_GATES_OF_AHN_QIRAJ &&
                patchId != Patches::STORMS_OF_AZEROTH &&
                patchId != Patches::SHADOW_OF_THE_NECROPOLIS &&
                patchId != Patches::DRUMS_OF_WAR &&
                patchId != Patches::BEFORE_THE_STORM &&
                patchId != Patches::THE_BLACK_TEMPLE &&
                patchId != Patches::VOICE_CHAT &&
                patchId != Patches::ECHO_OF_DOOM &&
                patchId != Patches::SECRETS_OF_ULDUAR &&
                patchId != Patches::CALL_OF_THE_CRUSADE &&
                patchId != FALL_OF_THE_LICH_KING)
                patchId = Patches::FALL_OF_THE_LICH_KING;

            return patchId;
        }

        int getExpansion()
        {
            if (patchId <= Patches::DRUMS_OF_WAR)
            {
                expansion = Expansions::EXPANSION_CLASSIC;
            }
            else if (patchId <= Patches::FURY_OF_THE_SUNWELL)
            {
                expansion = Expansions::EXPANSION_THE_BURNING_CRUSADE;
            }
            else
            {
                expansion = Expansions::EXPANSION_WRATH_OF_THE_LICH_KING;
            }

            return expansion;
        }
};

#endif
