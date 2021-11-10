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

            do
            {
                Field* fields = result->Fetch();
                uint32 entry  = fields[0].GetUInt32();
                uint32 item   = fields[1].GetUInt32();

                sObjectMgr->RemoveVendorItem(entry, item, false);
            } while (result->NextRow());
        }

        void SetVendorItems()
        {
            QueryResult result = WorldDatabase.PQuery("SELECT entry, item, maxcount, incrtime, ExtendedCost FROM progression_npc_vendor WHERE %u BETWEEN min_patch AND max_patch", progression->getPatchId());

            if (!result)
                return;

            do
            {
                Field* fields       = result->Fetch();
                uint32 entry        = fields[0].GetUInt32();
                uint32 item         = fields[2].GetUInt32();
                uint32 maxCount     = fields[3].GetUInt32();
                uint32 incrtime     = fields[4].GetUInt32();
                uint32 extendedCost = fields[5].GetUInt32();

                sObjectMgr->RemoveVendorItem(entry, item, false);
                sObjectMgr->AddVendorItem(entry, item, maxCount, incrtime, extendedCost, false);
            } while (result->NextRow());
        }
};

void AddProgressionVendorScripts()
{
    new ProgressionVendor();
}
