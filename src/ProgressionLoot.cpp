#include "Config.h"
#include "Progression.h"

class ProgressionLoot : public WorldScript
{
    public:
        ProgressionLoot() : WorldScript("ProgressionLoot") {}

        void OnStartup() override
        {
        }

    private:
        Progression* progression = new Progression();
};

void AddProgressionLootScripts()
{
    new ProgressionLoot();
}
