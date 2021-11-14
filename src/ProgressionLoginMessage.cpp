#include "Config.h"
#include "Progression.h"

class ProgressionLoginMessage : public PlayerScript
{
    public:
        ProgressionLoginMessage() : PlayerScript("ProgressionLoginMessage") {}

        void OnLogin(Player* player) override
        {
            if (sConfigMgr->GetBoolDefault("Progression.LoginMessage", 0))
            {
                switch (progression->getPatchId())
                {
                    case Patches::LAUNCH:
                        ChatHandler(player->GetSession()).SendSysMessage("Patch 1.1: World of Warcraft");
                        break;
                    case Patches::MYSTERIES_OF_MARAUDON:
                        ChatHandler(player->GetSession()).SendSysMessage("Patch 1.2: Mysteries of Maraudon");
                        break;
                    case Patches::RUINS_OF_DIRE_MAUL:
                        ChatHandler(player->GetSession()).SendSysMessage("Patch 1.3: Ruins of the Dire Maul");
                        break;
                    case Patches::THE_CALL_OF_WAR:
                        ChatHandler(player->GetSession()).SendSysMessage("Patch 1.4: The Call to War");
                        break;
                    case Patches::BATTLEGROUNDS:
                        ChatHandler(player->GetSession()).SendSysMessage("Patch 1.5: Battlegrounds");
                        break;
                    case Patches::ASSAULT_ON_BLACKWING_LAIR:
                        ChatHandler(player->GetSession()).SendSysMessage("Patch 1.6: Assault on Blackwing Lair");
                        break;
                    case Patches::RISE_OF_THE_BLOOD_GOD:
                        ChatHandler(player->GetSession()).SendSysMessage("Patch 1.7: Rise of the Blood God");
                        break;
                    case Patches::DRAGONS_OF_NIGHTMARE:
                        ChatHandler(player->GetSession()).SendSysMessage("Patch 1.8: Dragons of Nightmare");
                        break;
                    case Patches::THE_GATES_OF_AHN_QIRAJ:
                        ChatHandler(player->GetSession()).SendSysMessage("Patch 1.9: The Gates of Ahn'Qiraj");
                        break;
                    case Patches::STORMS_OF_AZEROTH:
                        ChatHandler(player->GetSession()).SendSysMessage("Patch 1.10: Storms of Azeroth");
                        break;
                    case Patches::SHADOW_OF_THE_NECROPOLIS:
                        ChatHandler(player->GetSession()).SendSysMessage("Patch 1.11: Shadow of the Necropolis");
                        break;
                    case Patches::DRUMS_OF_WAR:
                        ChatHandler(player->GetSession()).SendSysMessage("Patch 1.12: Drums of War");
                        break;
                    case Patches::BEFORE_THE_STORM:
                        ChatHandler(player->GetSession()).SendSysMessage("Patch 2.0: Before the Storm");
                        break;
                    case Patches::THE_BLACK_TEMPLE:
                        ChatHandler(player->GetSession()).SendSysMessage("Patch 2.1: The Black Temple");
                        break;
                    case Patches::VOICE_CHAT:
                        ChatHandler(player->GetSession()).SendSysMessage("Patch 2.2: Voice Chat!");
                        break;
                    case Patches::THE_GODS_OF_ZUL_AMAN:
                        ChatHandler(player->GetSession()).SendSysMessage("Patch 2.3: The Gods of Zul'Aman");
                        break;
                    case Patches::FURY_OF_THE_SUNWELL:
                        ChatHandler(player->GetSession()).SendSysMessage("Patch 2.4: Fury of the Sunwell");
                        break;
                    case Patches::ECHO_OF_DOOM:
                        ChatHandler(player->GetSession()).SendSysMessage("Patch 3.0: Echo of Doom");
                        break;
                    case Patches::SECRETS_OF_ULDUAR:
                        ChatHandler(player->GetSession()).SendSysMessage("Patch 3.1: Secrets of Ulduar");
                        break;
                    case Patches::CALL_OF_THE_CRUSADE:
                        ChatHandler(player->GetSession()).SendSysMessage("Patch 3.2: Call of the Crusade");
                        break;
                    case Patches::FALL_OF_THE_LICH_KING:
                        ChatHandler(player->GetSession()).SendSysMessage("Patch 3.3: Fall of the Lich King");
                        break;
                    default:
                        break;
                }
            }
        }

    private:
        Progression* progression = new Progression();
};

void AddProgressionLoginMessageScripts()
{
    new ProgressionLoginMessage();
}
