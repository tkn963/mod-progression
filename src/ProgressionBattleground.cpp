#include "Config.h"
#include "Progression.h"

class ProgressionBattleground : public WorldScript
{
    public:
        ProgressionBattleground() : WorldScript("ProgressionBattleground") {}

        void OnStartup() override
        {
        }

    private:
        Progression* progression = new Progression();
};

void AddProgressionBattlegroundScripts()
{
    new ProgressionBattleground();
}
