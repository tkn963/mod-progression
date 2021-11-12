#include "Config.h"
#include "Progression.h"

class ProgressionExpansion : public WorldScript
{
    public:
        ProgressionExpansion() : WorldScript("ProgressionExpansion") {}

        void OnAfterConfigLoad(bool /*reload*/) override
        {
            if (sConfigMgr->GetBoolDefault("Progression.Expansion", 1))
                sWorld->setIntConfig(WorldIntConfigs::CONFIG_EXPANSION, progression->getExpansion());
        }

    private:
        Progression* progression = new Progression();
};

void AddProgressionExpansionScripts()
{
    new ProgressionExpansion();
}
