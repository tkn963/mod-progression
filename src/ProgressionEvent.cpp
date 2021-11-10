#include "Config.h"
#include "Progression.h"

class ProgressionEvent : public WorldScript
{
    public:
        ProgressionEvent() : WorldScript("ProgressionEvent") {}

        void OnStartup() override
        {
            DisableEvents();
        }

    private:
        Progression* progression = new Progression();

        void DisableEvents()
        {
            QueryResult result = WorldDatabase.PQuery("SELECT eventEntry FROM progression_game_event WHERE %u NOT BETWEEN min_patch AND max_patch", progression->getPatchId());

            if (!result)
                return;

            uint32 count = 0;
            do
            {
                Field* fields     = result->Fetch();
                uint32 eventEntry = fields[0].GetUInt32();

                GameEventMgr::GameEventDataMap gameEvent = sGameEventMgr->GetEventMap();

                gameEvent.at(eventEntry).start     = time_t("2000-01-01 14:00:00");
                gameEvent.at(eventEntry).end       = time_t("2000-01-01 14:00:00");
                gameEvent.at(eventEntry).occurence = 5184000;
                gameEvent.at(eventEntry).length    = 1;

                ++count;
            } while (result->NextRow());

            LOG_INFO("server.loading", ">> Disabled %u events", count);
        }
};

void AddProgressionEventScripts()
{
    new ProgressionEvent();
}
