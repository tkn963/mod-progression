#include "Config.h"
#include "Progression.h"

class ProgressionMap : public WorldScript
{
    public:
        ProgressionMap() : WorldScript("ProgressionMap") {}

        void OnBeforeTransportsQueried(std::string& query) override
        {
            query = Acore::StringFormat("SELECT guid, entry FROM transports "
                                        "WHERE patch <= %u",
                                        progression->getPatchId());
        }

        void OnBeforeLinkedRespawnQueried(std::string& query) override
        {
            query = Acore::StringFormat("SELECT guid, linkedGuid, linkType FROM linked_respawn a "
                                        "WHERE patch=(SELECT max(patch) FROM linked_respawn b WHERE a.guid = b.guid AND a.linkedGuid = b.linkedGuid && patch <= %u) "
                                        "ORDER BY guid ASC",
                                        progression->getPatchId());
        }

    private:
        Progression* progression = new Progression();
};

void AddProgressionMapScripts()
{
    new ProgressionMap();
}
