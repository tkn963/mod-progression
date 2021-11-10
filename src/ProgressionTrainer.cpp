#include "Config.h"
#include "Progression.h"

class ProgressionTrainer : public WorldScript
{
    public:
        ProgressionTrainer() : WorldScript("ProgressionTrainer") {}

        void OnStartup() override
        {
            RemoveTrainerSpells();
            SetTrainerSpells();
        }

    private:
        Progression* progression = new Progression();

        void RemoveTrainerSpells() {}

        void SetTrainerSpells() {}
};

void AddProgressionTrainerScripts()
{
    new ProgressionTrainer();
}
