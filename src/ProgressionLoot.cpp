#include "Config.h"
#include "Progression.h"

class ProgressionLoot : public WorldScript
{
    public:
        ProgressionLoot() : WorldScript("ProgressionLoot") {}

        void OnBeforeLootTemplateQueried(char const* table, std::string& query) override
        {
            /*
            This is another way of handling the loot tables.
            It lets a user modify only required tables instead of all of them.

            if (table == "creature_loot_template") {}
            else if (table == "disenchant_loot_template") {}
            else if (table == "fishing_loot_template") {}
            else if (table == "gameobject_loot_template") {}
            else if (table == "item_loot_template") {}
            else if (table == "mail_loot_template") {}
            else if (table == "milling_loot_template") {}
            else if (table == "pickpocketing_loot_template") {}
            else if (table == "player_loot_template") {}
            else if (table == "prospecting_loot_template") {}
            else if (table == "reference_loot_template") {}
            else if (table == "skinning_loot_template") {}
            else if (table == "spell_loot_template") {}
            */

            query = Acore::StringFormat("SELECT Entry, Item, Reference, Chance, QuestRequired, LootMode, GroupId, MinCount, MaxCount FROM %s a "
                                        "WHERE patch=(SELECT max(patch) FROM %s b WHERE a.Entry = b.Entry && patch <= %u)",
                                        table,
                                        table,
                                        progression->getPatchId());
        }

    private:
        Progression* progression = new Progression();
};

void AddProgressionLootScripts()
{
    new ProgressionLoot();
}
