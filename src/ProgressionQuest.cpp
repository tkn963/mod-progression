#include "Config.h"
#include "Progression.h"

class ProgressionQuest : public WorldScript
{
    public:
        ProgressionQuest() : WorldScript("ProgressionQuest") {}

        void OnStartup() override
        {
        }

    private:
        Progression* progression = new Progression();
};

void AddProgressionQuestScripts()
{
    new ProgressionQuest();
}
