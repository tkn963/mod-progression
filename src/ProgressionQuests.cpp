#include "Config.h"
#include "Progression.h"

class ProgressionQuests : public WorldScript
{
    public:
        ProgressionQuests() : WorldScript("ProgressionQuests") {}

        void OnBeforeQuestTemplateQueried(std::string& query) override
        {
            query = Acore::StringFormat("SELECT ID, QuestType, QuestLevel, MinLevel, QuestSortID, QuestInfoID, SuggestedGroupNum, TimeAllowed, AllowableRaces,"
                                        "RequiredFactionId1, RequiredFactionId2, RequiredFactionValue1, RequiredFactionValue2, "
                                        "RewardNextQuest, RewardXPDifficulty, RewardMoney, RewardMoneyDifficulty, RewardBonusMoney,  RewardDisplaySpell, RewardSpell, RewardHonor, RewardKillHonor, "
                                        "StartItem, Flags, RewardTitle, RequiredPlayerKills, RewardTalents, RewardArenaPoints, "
                                        "RewardItem1, RewardAmount1, RewardItem2, RewardAmount2, RewardItem3, RewardAmount3, RewardItem4, RewardAmount4, "
                                        "RewardChoiceItemID1, RewardChoiceItemQuantity1, RewardChoiceItemID2, RewardChoiceItemQuantity2, RewardChoiceItemID3, RewardChoiceItemQuantity3, RewardChoiceItemID4, RewardChoiceItemQuantity4, RewardChoiceItemID5, RewardChoiceItemQuantity5, RewardChoiceItemID6, RewardChoiceItemQuantity6, "
                                        "RewardFactionID1, RewardFactionValue1, RewardFactionOverride1, RewardFactionID2, RewardFactionValue2, RewardFactionOverride2, RewardFactionID3, RewardFactionValue3, RewardFactionOverride3, RewardFactionID4, RewardFactionValue4, RewardFactionOverride4, RewardFactionID5, RewardFactionValue5,  RewardFactionOverride5,"
                                        "POIContinent, POIx, POIy, POIPriority, "
                                        "LogTitle, LogDescription, QuestDescription, AreaDescription, QuestCompletionLog, "
                                        "RequiredNpcOrGo1, RequiredNpcOrGo2, RequiredNpcOrGo3, RequiredNpcOrGo4, RequiredNpcOrGoCount1, RequiredNpcOrGoCount2, RequiredNpcOrGoCount3, RequiredNpcOrGoCount4, "
                                        "ItemDrop1, ItemDrop2, ItemDrop3, ItemDrop4, ItemDropQuantity1, ItemDropQuantity2, ItemDropQuantity3, ItemDropQuantity4, "
                                        "RequiredItemId1, RequiredItemId2, RequiredItemId3, RequiredItemId4, RequiredItemId5, RequiredItemId6, RequiredItemCount1, RequiredItemCount2, RequiredItemCount3, RequiredItemCount4, RequiredItemCount5, RequiredItemCount6, "
                                        "Unknown0, ObjectiveText1, ObjectiveText2, ObjectiveText3, ObjectiveText4"
                                        " FROM quest_template a WHERE patch=(SELECT max(patch) FROM quest_template b WHERE a.ID = b.ID && patch <= %u)",
                                        progression->getPatchId());
        }

    private:
        Progression* progression = new Progression();
};

void AddProgressionQuestsScripts()
{
    new ProgressionQuests();
}
