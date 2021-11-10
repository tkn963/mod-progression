#include "Config.h"
#include "Progression.h"

class ProgressionVendor : public WorldScript
{
    public:
        ProgressionVendor() : WorldScript("ProgressionVendor") {}

        void OnStartup() override
        {
            DeleteVendorItems();
            SetVendorItems();
        }

    private:
        Progression* progression = new Progression();

        void DeleteVendorItems()
        {
            QueryResult result = WorldDatabase.PQuery("SELECT entry, item FROM progression_npc_vendor WHERE %u NOT BETWEEN min_patch AND max_patch", progression->getPatchId());

            if (!result)
                return;

            uint32 count = 0;
            do
            {
                Field* fields = result->Fetch();
                uint32 entry  = fields[0].GetUInt32();
                uint32 item   = fields[1].GetUInt32();

                sObjectMgr->RemoveVendorItem(entry, item);
                ++count;
            } while (result->NextRow());

            LOG_INFO("server.loading", ">> Removed %u vendor items", count);
        }

        void SetVendorItems()
        {
        }
};

void AddProgressionVendorScripts()
{
    new ProgressionVendor();
}
