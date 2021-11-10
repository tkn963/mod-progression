#include "Config.h"
#include "Progression.h"

class ProgressionItem : public WorldScript
{
    public:
        ProgressionItem() : WorldScript("ProgressionItem") {}

        void OnStartup() override
        {
            UpdateItemTemplates();
        }

    private:
        Progression* progression = new Progression();

        void UpdateItemTemplates()
        {
            QueryResult result = WorldDatabase.PQuery("SELECT entry FROM progression_item_template a "
                                                      "WHERE patch=(SELECT max(patch) FROM item_template b WHERE a.entry=b.entry && patch <= %u)",
                                                      progression->getPatchId());

            if (!result)
                return;

            do
            {
                Field* fields = result->Fetch();
                uint32 entry = fields[0].GetUInt32();

                ItemTemplate* itemTemplate = const_cast<ItemTemplate*>(&sObjectMgr->GetItemTemplateStore()->at(entry));

                if (!itemTemplate)
                    continue;
            } while (result->NextRow());
        }
};

void AddProgressionItemScripts()
{
    new ProgressionItem();
}
