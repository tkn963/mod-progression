#include "Config.h"
#include "Progression.h"

class ProgressionRestrictionsArea : public PlayerScript
{
    public:
        ProgressionRestrictionsArea() : PlayerScript("ProgressionRestrictionsArea") {}

        void OnUpdateArea(Player* player, uint32 /*oldArea*/, uint32 newArea)
        {
            if (sConfigMgr->GetBoolDefault("Progression.Restrictions.Areas", 1))
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

class ProgressionRestrictionsExpansion : public WorldScript
{
    public:
        ProgressionRestrictionsExpansion() : WorldScript("ProgressionRestrictionsExpansion") {}

        void OnAfterConfigLoad(bool /*reload*/) override
        {
            if (sConfigMgr->GetBoolDefault("Progression.Restrictions.Expansion", 0))
                sWorld->setIntConfig(WorldIntConfigs::CONFIG_EXPANSION, progression->getExpansion());
        }

    private:
        Progression* progression = new Progression();
};

void AddProgressionRestrictionsScripts()
{
    new ProgressionRestrictionsArea();
    new ProgressionRestrictionsExpansion();
}
