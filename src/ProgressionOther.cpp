#include "Config.h"
#include "Progression.h"

class ProgressionOther : public WorldScript
{
    public:
        ProgressionOther() : WorldScript("ProgressionOther") {}

        void OnBeforeLinkedRespawnQueried(std::string& query) override
        {
            query = Acore::StringFormat("SELECT guid, linkedGuid, linkType FROM linked_respawn a "
                                        "WHERE patch=(SELECT max(patch) FROM linked_respawn b WHERE a.guid=b.guid AND a.linkedGuid=b.linkedGuid && patch <= %u) "
                                        "ORDER BY guid ASC",
                                        progression->getPatchId());
        }

    private:
        Progression* progression = new Progression();
};

void AddProgressionOtherScripts()
{
    new ProgressionOther();
}
