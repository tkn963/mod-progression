#include "Config.h"
#include "Progression.h"

class ProgressionTransport : public WorldScript
{
    public:
        ProgressionTransport() : WorldScript("ProgressionTransport") {}

        void OnStartup() override
        {
        }

    private:
        Progression* progression = new Progression();
};

void AddProgressionTransportScripts()
{
    new ProgressionTransport();
}
