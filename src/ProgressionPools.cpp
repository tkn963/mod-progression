#include "Config.h"
#include "Progression.h"

class ProgressionPools : public WorldScript
{
    public:
        ProgressionPools() : WorldScript("ProgressionPools") {}

        void OnBeforePoolTemplateQueried(std::string& query) override
        {
            query = Acore::StringFormat("SELECT entry, max_limit FROM pool_template "
                                        "WHERE %u BETWEEN min_patch AND max_patch",
                                        progression->getPatchId());
        }

    private:
        Progression* progression = new Progression();
};

void AddProgressionPoolsScripts()
{
    new ProgressionPools();
}
