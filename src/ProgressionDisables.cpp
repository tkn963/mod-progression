#include "Config.h"
#include "Progression.h"

class ProgressionDisables : public WorldScript
{
    public:
        ProgressionDisables() : WorldScript("ProgressionDisables") {}

        void OnBeforeDisablesQueried(std::string& query) override
        {
            query = Acore::StringFormat("SELECT sourceType, entry, flags, params_0, params_1 FROM disables "
                                        "WHERE %u BETWEEN min_patch AND max_patch",
                                        progression->getPatchId());
        }

    private:
        Progression* progression = new Progression();
};

void AddProgressionDisablesScripts()
{
    new ProgressionDisables();
}
