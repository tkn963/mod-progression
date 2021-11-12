#include "Config.h"
#include "Progression.h"

class ProgressionRestrictedArea : public PlayerScript
{
    public:
        ProgressionRestrictedArea() : PlayerScript("ProgressionRestrictedArea") {}

        void OnUpdateArea(Player* player, uint32 /*oldArea*/, uint32 newArea)
        {
            if (sConfigMgr->GetBoolDefault("Progression.RestrictedAreas", 1))
            {
                if (player->GetSession()->GetSecurity() >= SEC_GAMEMASTER)
                    return;

                // Argent Tournament Grounds
                if (newArea == 4658)
                {
                    if (progression->getPatchId() < Patches::SECRETS_OF_ULDUAR)
                    {
                        ChatHandler(player->GetSession()).SendSysMessage("The argent tournament grounds are currently unavailable.");
                        player->TeleportTo(571, 8163.57f, 799.76f, 484.03f, 3.18f);
                    }
                }
            }
        }

    private:
        Progression* progression = new Progression();
};

void AddProgressionRestrictedAreaScripts()
{
    new ProgressionRestrictedArea();
}
