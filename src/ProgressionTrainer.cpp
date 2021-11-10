#include "Config.h"
#include "Progression.h"

class ProgressionTrainer : public WorldScript
{
    public:
        ProgressionTrainer() : WorldScript("ProgressionTrainer") {}

        void OnStartup() override
        {
        }

    private:
        Progression* progression = new Progression();
};

void AddProgressionTrainerScripts()
{
    new ProgressionTrainer();
}
