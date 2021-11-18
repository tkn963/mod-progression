#include "Config.h"
#include "Progression.h"

class ProgressionNpc : public WorldScript
{
    public:
        ProgressionNpc() : WorldScript("ProgressionNpc") {}

        void OnBeforeNpcTrainerQueried(std::string& query) override
        {
            query = Acore::StringFormat("SELECT b.ID, a.SpellID, a.MoneyCost, a.ReqSkillLine, a.ReqSkillRank, a.ReqLevel FROM npc_trainer AS a "
                                        "INNER JOIN npc_trainer AS b ON a.ID = -(b.SpellID) "
                                        "WHERE %u BETWEEN a.min_patch AND a.max_patch "
                                        "UNION SELECT ID, SpellID, MoneyCost, ReqSkillLine, ReqSkillRank, ReqLevel FROM npc_trainer WHERE SpellID > 0 "
                                        "AND %u BETWEEN min_patch AND max_patch",
                                        progression->getPatchId(),
                                        progression->getPatchId());
        }

        void OnBeforeNpcVendorQueried(std::string& query) override
        {
            query = Acore::StringFormat("SELECT entry, item, maxcount, incrtime, ExtendedCost FROM npc_vendor "
                                        "WHERE %u BETWEEN min_patch AND max_patch "
                                        "ORDER BY entry, slot ASC, item, ExtendedCost",
                                        progression->getPatchId());
        }

    private:
        Progression* progression = new Progression();
};

void AddProgressionNpcScripts()
{
    new ProgressionNpc();
}
