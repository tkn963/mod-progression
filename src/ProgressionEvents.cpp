#include "Config.h"
#include "Progression.h"

class ProgressionEvents : public WorldScript
{
    public:
        ProgressionEvents() : WorldScript("ProgressionEvents") {}

        void OnBeforeGameEventQueried(std::string& query) override
        {
            query = Acore::StringFormat("SELECT eventEntry, UNIX_TIMESTAMP(start_time), UNIX_TIMESTAMP(end_time), occurence, length, "
                                        "holiday, holidayStage, description, world_event, announce FROM game_event WHERE patch <= %u",
                                        progression->getPatchId());
        }

    private:
        Progression* progression = new Progression();
};

void AddProgressionEventsScripts()
{
    new ProgressionEvents();
}
