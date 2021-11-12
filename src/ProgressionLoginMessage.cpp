#include "Config.h"
#include "Progression.h"

class ProgressionLoginMessage : public PlayerScript
{
    public:
        ProgressionLoginMessage() : PlayerScript("ProgressionLoginMessage") {}

        void OnLogin(Player* player) override
        {
            if (sConfigMgr->GetBoolDefault("Progression.LoginMessage", 0))
                ChatHandler(player->GetSession()).SendSysMessage(progression->getPatchTitle());
        }

    private:
        Progression* progression = new Progression();
};

void AddProgressionLoginMessageScripts()
{
    new ProgressionLoginMessage();
}
