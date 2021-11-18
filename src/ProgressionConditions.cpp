#include "Config.h"
#include "Progression.h"

class ProgressionConditions : public WorldScript
{
    public:
        ProgressionConditions() : WorldScript("ProgressionConditions") {}

        void OnBeforeConditionsQueried(std::string& query) override
        {
            query = Acore::StringFormat("SELECT SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, "
                                        "ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ErrorTextId, ScriptName FROM conditions "
                                        "WHERE %u BETWEEN min_patch AND max_patch",
                                        progression->getPatchId());
        }

    private:
        Progression* progression = new Progression();
};

void AddProgressionConditionsScripts()
{
    new ProgressionConditions();
}
