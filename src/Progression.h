#ifndef PROGRESSION_H
#define PROGRESSION_H

enum Patches
{
    LAUNCH = 0,
    MYSTERIES_OF_MARAUDON,
    RUINS_OF_DIRE_MAUL,
    THE_CALL_OF_WAR,
    BATTLEGROUNDS,
    ASSAULT_ON_BLACKWING_LAIR,
    RISE_OF_THE_BLOOD_GOD,
    DRAGONS_OF_NIGHTMARE,
    THE_GATES_OF_AHN_QIRAJ,
    STORMS_OF_AZEROTH,
    SHADOW_OF_THE_NECROPOLIS,
    DRUMS_OF_WAR,
    BEFORE_THE_STORM,
    THE_BLACK_TEMPLE,
    VOICE_CHAT,
    THE_GODS_OF_ZUL_AMAN,
    FURY_OF_THE_SUNWELL,
    ECHO_OF_DOOM,
    SECRETS_OF_ULDUAR,
    CALL_OF_THE_CRUSADE,
    FALL_OF_THE_LICH_KING
};

class Progression
{
    private:
        int patchId = sConfigMgr->GetIntDefault("Progression.Patch", Patches::FALL_OF_THE_LICH_KING);
        int expansion;

        std::string patchTitle[21]
        {
            "Patch 1.1: World of Warcraft",
            "Patch 1.2: Mysteries of Maraudon",
            "Patch 1.3: Ruins of the Dire Maul",
            "Patch 1.4: The Call to War",
            "Patch 1.5: Battlegrounds",
            "Patch 1.6: Assault on Blackwing Lair",
            "Patch 1.7: Rise of the Blood God",
            "Patch 1.8: Dragons of Nightmare",
            "Patch 1.9: The Gates of Ahn'Qiraj",
            "Patch 1.10: Storms of Azeroth",
            "Patch 1.11: Shadow of the Necropolis",
            "Patch 1.12: Drums of War",
            "Patch 2.0: Before the Storm / The Burning Crusade",
            "Patch 2.1: The Black Temple",
            "Patch 2.2: Voice Chat!",
            "Patch 2.3: The Gods of Zul'Aman",
            "Patch 2.4: Fury of the Sunwell",
            "Patch 3.0: Echo of Doom / Wrath of the Lich King",
            "Patch 3.1: Secrets of Ulduar",
            "Patch 3.2: Call of the Crusade",
            "Patch 3.3: Fall of the Lich King"
        };

    public:
        int getPatchId()
        {
            if (patchId < Patches::LAUNCH || patchId > Patches::FALL_OF_THE_LICH_KING)
                patchId = Patches::FALL_OF_THE_LICH_KING;

            return patchId;
        }

        std::string getPatchTitle()
        {
            return patchTitle[getPatchId()];
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
