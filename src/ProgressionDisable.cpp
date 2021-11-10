#include "Config.h"
#include "Progression.h"

class ProgressionDisable : public WorldScript
{
    public:
        ProgressionDisable() : WorldScript("ProgressionDisable") {}

        void OnStartup() override
        {
        }

    private:
        Progression* progression = new Progression();
};

void AddProgressionDisableScripts()
{
    new ProgressionDisable();
}
