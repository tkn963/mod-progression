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
            QueryResult result = WorldDatabase.PQuery("SELECT entry, BuyPrice, SellPrice, ItemLevel, RequiredLevel, spellid_1, spellcharges_1, "
                                                      "spellcategorycooldown_1, spellcategory_1, spellid_2, spelltrigger_2, description "
                                                      "FROM progression_item_template a "
                                                      "WHERE patch=(SELECT max(patch) FROM item_template b WHERE a.entry=b.entry && patch <= %u)",
                                                      progression->getPatchId());

            if (!result)
                return;

            do
            {
                Field* fields                 = result->Fetch();
                uint32 entry                  = fields[0].GetUInt32();
                uint32 buyPrice               = fields[1].GetUInt32();
                uint32 sellPrice              = fields[2].GetUInt32();
                uint32 itemLevel              = fields[3].GetUInt32();
                uint32 requiredLevel          = fields[4].GetUInt32();
                uint32 spellId1               = fields[5].GetUInt32();
                uint32 spellCharges1          = fields[6].GetUInt32();
                uint32 spellCategoryCooldown1 = fields[7].GetUInt32();
                uint32 spellCategory1         = fields[8].GetUInt32();
                uint32 spellId2               = fields[9].GetUInt32();
                uint32 spellTrigger2          = fields[10].GetUInt32();
                std::string description       = fields[11].GetString();

                ItemTemplate* itemTemplate = const_cast<ItemTemplate*>(&sObjectMgr->GetItemTemplateStore()->at(entry));

                if (!itemTemplate)
                    continue;

                itemTemplate->BuyPrice = buyPrice;
                itemTemplate->SellPrice = sellPrice;
                itemTemplate->ItemLevel = itemLevel;
                itemTemplate->RequiredLevel = requiredLevel;
                itemTemplate->Spells[0].SpellId = spellId1;
                itemTemplate->Spells[0].SpellCharges = spellCharges1;
                itemTemplate->Spells[0].SpellCategoryCooldown = spellCategoryCooldown1;
                itemTemplate->Spells[0].SpellCategory = spellCategory1;
                itemTemplate->Spells[1].SpellId = spellId2;
                itemTemplate->Spells[1].SpellTrigger = spellTrigger2;
                itemTemplate->Description = description;
            } while (result->NextRow());
        }
};

void AddProgressionItemScripts()
{
    new ProgressionItem();
}
