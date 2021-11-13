#include "Config.h"
#include "Progression.h"

class ProgressionQuest : public WorldScript
{
    public:
        ProgressionQuest() : WorldScript("ProgressionQuest") {}

        void OnStartup() override
        {
            RemoveCreatureQuestEnder();
            AddCreatureQuestEnder();
            RemoveCreatureQuestStarter();
            AddCreatureQuestStarter();

            RemoveGameObjectQuestEnder();
            AddGameObjectQuestEnder();
            RemoveGameObjectQuestStarter();
            AddGameObjectQuestStarter();

            UpdateQuestTemplates();
        }

    private:
        Progression* progression = new Progression();

        void RemoveCreatureQuestEnder()
        {
            QueryResult result = WorldDatabase.PQuery("SELECT `id`, `quest` FROM `progression_creature_questender` WHERE %u NOT BETWEEN `min_patch` AND `max_patch`", progression->getPatchId());

            if (!result)
                return;

            QuestRelationBounds questEnderBounds;
            QuestRelations* questEnderMap = sObjectMgr->GetCreatureQuestInvolvedRelationMap();

            do
            {
                Field* fields = result->Fetch();
                uint32 id     = fields[0].GetUInt32();
                uint32 quest  = fields[1].GetUInt32();

                questEnderBounds = sObjectMgr->GetCreatureQuestInvolvedRelationBounds(id);

                for (QuestRelations::const_iterator i = questEnderBounds.first; i != questEnderBounds.second; ++i)
                {
                    if (i->second == quest)
                        questEnderMap->erase(i);
                }
            } while (result->NextRow());
        }

        void AddCreatureQuestEnder()
        {
            QueryResult result = WorldDatabase.PQuery("SELECT `id`, `quest` FROM `progression_creature_questender` WHERE %u BETWEEN `min_patch` AND `max_patch`", progression->getPatchId());

            if (!result)
                return;

            QuestRelationBounds questEnderBounds;
            QuestRelations* questEnderMap = sObjectMgr->GetCreatureQuestInvolvedRelationMap();
            bool exists;

            do
            {
                Field* fields = result->Fetch();
                uint32 id     = fields[0].GetUInt32();
                uint32 quest  = fields[1].GetUInt32();

                questEnderBounds = sObjectMgr->GetCreatureQuestInvolvedRelationBounds(id);
                exists = false;

                for (QuestRelations::const_iterator i = questEnderBounds.first; i != questEnderBounds.second; ++i)
                {
                    if (i->second == quest)
                    {
                        exists = true;
                        break;
                    }
                }

                if (!exists)
                    if (sObjectMgr->GetCreatureTemplate(id))
                        if (sObjectMgr->GetCreatureTemplate(id)->npcflag & UNIT_NPC_FLAG_QUESTGIVER)
                            if (sObjectMgr->GetQuestTemplate(quest))
                                questEnderMap->insert(QuestRelations::value_type(id, quest));
            } while (result->NextRow());
        }

        void RemoveCreatureQuestStarter()
        {
            QueryResult result = WorldDatabase.PQuery("SELECT `id`, `quest` FROM `progression_creature_queststarter` WHERE %u NOT BETWEEN `min_patch` AND `max_patch`", progression->getPatchId());

            if (!result)
                return;

            QuestRelationBounds questStarterBounds;
            QuestRelations* questStarterMap = sObjectMgr->GetCreatureQuestRelationMap();

            do
            {
                Field* fields = result->Fetch();
                uint32 id     = fields[0].GetUInt32();
                uint32 quest  = fields[1].GetUInt32();

                questStarterBounds = sObjectMgr->GetCreatureQuestRelationBounds(id);

                for (QuestRelations::const_iterator i = questStarterBounds.first; i != questStarterBounds.second; ++i)
                {
                    if (i->second == quest)
                        questStarterMap->erase(i);
                }
            } while (result->NextRow());
        }

        void AddCreatureQuestStarter()
        {
            QueryResult result = WorldDatabase.PQuery("SELECT `id`, `quest` FROM `progression_creature_queststarter` WHERE %u BETWEEN `min_patch` AND `max_patch`", progression->getPatchId());

            if (!result)
                return;

            QuestRelationBounds questStarterBounds;
            QuestRelations* questStarterMap = sObjectMgr->GetCreatureQuestRelationMap();
            bool exists;

            do
            {
                Field* fields = result->Fetch();
                uint32 id     = fields[0].GetUInt32();
                uint32 quest  = fields[1].GetUInt32();

                questStarterBounds = sObjectMgr->GetCreatureQuestRelationBounds(id);
                exists = false;

                for (QuestRelations::const_iterator i = questStarterBounds.first; i != questStarterBounds.second; ++i)
                {
                    if (i->second == quest)
                    {
                        exists = true;
                        break;
                    }
                }

                if (!exists)
                    if (sObjectMgr->GetCreatureTemplate(id))
                        if (sObjectMgr->GetCreatureTemplate(id)->npcflag & UNIT_NPC_FLAG_QUESTGIVER)
                            if (sObjectMgr->GetQuestTemplate(quest))
                                questStarterMap->insert(QuestRelations::value_type(id, quest));
            } while (result->NextRow());
        }

        void RemoveGameObjectQuestEnder()
        {
            QueryResult result = WorldDatabase.PQuery("SELECT `id`, `quest` FROM `progression_gameobject_questender` WHERE %u NOT BETWEEN `min_patch` AND `max_patch`", progression->getPatchId());

            if (!result)
                return;

            QuestRelationBounds questEnderBounds;
            QuestRelations* questEnderMap = sObjectMgr->GetGOQuestInvolvedRelationMap();

            do
            {
                Field* fields = result->Fetch();
                uint32 id     = fields[0].GetUInt32();
                uint32 quest  = fields[1].GetUInt32();

                questEnderBounds = sObjectMgr->GetGOQuestInvolvedRelationBounds(id);

                for (QuestRelations::const_iterator i = questEnderBounds.first; i != questEnderBounds.second; ++i)
                {
                    if (i->second == quest)
                        questEnderMap->erase(i);
                }
            } while (result->NextRow());
        }

        void AddGameObjectQuestEnder()
        {
            QueryResult result = WorldDatabase.PQuery("SELECT `id`, `quest` FROM `progression_gameobject_questender` WHERE %u BETWEEN `min_patch` AND `max_patch`", progression->getPatchId());

            if (!result)
                return;

            QuestRelationBounds questEnderBounds;
            QuestRelations* questEnderMap = sObjectMgr->GetGOQuestInvolvedRelationMap();
            bool exists;

            do
            {
                Field* fields = result->Fetch();
                uint32 id     = fields[0].GetUInt32();
                uint32 quest  = fields[1].GetUInt32();

                questEnderBounds = sObjectMgr->GetGOQuestInvolvedRelationBounds(id);
                exists = false;

                for (QuestRelations::const_iterator i = questEnderBounds.first; i != questEnderBounds.second; ++i)
                {
                    if (i->second == quest)
                    {
                        exists = true;
                        break;
                    }
                }

                if (!exists)
                    if (sObjectMgr->GetGameObjectTemplate(id))
                        if (sObjectMgr->GetGameObjectTemplate(id)->type == GAMEOBJECT_TYPE_QUESTGIVER)
                            if (sObjectMgr->GetQuestTemplate(quest))
                                questEnderMap->insert(QuestRelations::value_type(id, quest));
            } while (result->NextRow());
        }

        void RemoveGameObjectQuestStarter()
        {
            QueryResult result = WorldDatabase.PQuery("SELECT `id`, `quest` FROM `progression_gameobject_queststarter` WHERE %u NOT BETWEEN `min_patch` AND `max_patch`", progression->getPatchId());

            if (!result)
                return;

            QuestRelationBounds questStarterBounds;
            QuestRelations* questStarterMap = sObjectMgr->GetGOQuestRelationMap();

            do
            {
                Field* fields = result->Fetch();
                uint32 id     = fields[0].GetUInt32();
                uint32 quest  = fields[1].GetUInt32();

                questStarterBounds = sObjectMgr->GetGOQuestRelationBounds(id);

                for (QuestRelations::const_iterator i = questStarterBounds.first; i != questStarterBounds.second; ++i)
                {
                    if (i->second == quest)
                        questStarterMap->erase(i);
                }
            } while (result->NextRow());
        }

        void AddGameObjectQuestStarter()
        {
            QueryResult result = WorldDatabase.PQuery("SELECT `id`, `quest` FROM `progression_gameobject_queststarter` WHERE %u BETWEEN `min_patch` AND `max_patch`", progression->getPatchId());

            if (!result)
                return;

            QuestRelationBounds questStarterBounds;
            QuestRelations* questStarterMap = sObjectMgr->GetGOQuestRelationMap();
            bool exists;

            do
            {
                Field* fields = result->Fetch();
                uint32 id     = fields[0].GetUInt32();
                uint32 quest  = fields[1].GetUInt32();

                questStarterBounds = sObjectMgr->GetGOQuestRelationBounds(id);
                exists = false;

                for (QuestRelations::const_iterator i = questStarterBounds.first; i != questStarterBounds.second; ++i)
                {
                    if (i->second == quest)
                    {
                        exists = true;
                        break;
                    }
                }

                if (!exists)
                    if (sObjectMgr->GetGameObjectTemplate(id))
                        if (sObjectMgr->GetGameObjectTemplate(id)->type == GAMEOBJECT_TYPE_QUESTGIVER)
                            if (sObjectMgr->GetQuestTemplate(quest))
                                questStarterMap->insert(QuestRelations::value_type(id, quest));
            } while (result->NextRow());
        }

        void UpdateQuestTemplates()
        {
            QueryResult result = WorldDatabase.PQuery("SELECT `ID`, `QuestType`, `QuestLevel`, `MinLevel`, `QuestSortID`, `QuestInfoID`, `SuggestedGroupNum`, "
                                                      "`RequiredFactionId1`, `RequiredFactionId2`, `RequiredFactionValue1`, `RequiredFactionValue2`, `RewardNextQuest`, "
                                                      "`RewardXPDifficulty`, `RewardMoney`, `RewardMoneyDifficulty`, `RewardBonusMoney`, `RewardDisplaySpell`, `RewardSpell`, "
                                                      "`RewardHonor`, `RewardKillHonor`, `StartItem`, `Flags`, `RequiredPlayerKills`, `RewardItem1`, `RewardAmount1`, "
                                                      "`RewardItem2`, `RewardAmount2`, `RewardItem3`, `RewardAmount3`, `RewardItem4`, `RewardAmount4`, `ItemDrop1`, "
                                                      "`ItemDropQuantity1`, `ItemDrop2`, `ItemDropQuantity2`, `ItemDrop3`, `ItemDropQuantity3`, `ItemDrop4`, `ItemDropQuantity4`, "
                                                      "`RewardChoiceItemID1`, `RewardChoiceItemQuantity1`, `RewardChoiceItemID2`, `RewardChoiceItemQuantity2`, `RewardChoiceItemID3`, "
                                                      "`RewardChoiceItemQuantity3`, `RewardChoiceItemID4`, `RewardChoiceItemQuantity4`, `RewardChoiceItemID5`, `RewardChoiceItemQuantity5`, "
                                                      "`RewardChoiceItemID6`, `RewardChoiceItemQuantity6`, `POIContinent`, `POIx`, `POIy`, `POIPriority`, `RewardTitle`, `RewardTalents`, "
                                                      "`RewardArenaPoints`, `RewardFactionID1`, `RewardFactionValue1`, `RewardFactionOverride1`, `RewardFactionID2`, `RewardFactionValue2`, "
                                                      "`RewardFactionOverride2`, `RewardFactionID3`, `RewardFactionValue3`, `RewardFactionOverride3`, `RewardFactionID4`, "
                                                      "`RewardFactionValue4`, `RewardFactionOverride4`, `RewardFactionID5`, `RewardFactionValue5`, `RewardFactionOverride5`, "
                                                      "`TimeAllowed`, `AllowableRaces`, `LogTitle`, `LogDescription`, `QuestDescription`, `AreaDescription`, `QuestCompletionLog`, "
                                                      "`RequiredNpcOrGo1`, `RequiredNpcOrGo2`, `RequiredNpcOrGo3`, `RequiredNpcOrGo4`, `RequiredNpcOrGoCount1`, `RequiredNpcOrGoCount2`, "
                                                      "`RequiredNpcOrGoCount3`, `RequiredNpcOrGoCount4`, `RequiredItemId1`, `RequiredItemId2`, `RequiredItemId3`, `RequiredItemId4`, "
                                                      "`RequiredItemId5`, `RequiredItemId6`, `RequiredItemCount1`, `RequiredItemCount2`, `RequiredItemCount3`, `RequiredItemCount4`, "
                                                      "`RequiredItemCount5`, `RequiredItemCount6`, `Unknown0`, `ObjectiveText1`, `ObjectiveText2`, `ObjectiveText3`, `ObjectiveText4` "
                                                      "FROM `progression_quest_template` WHERE %u BETWEEN `min_patch` AND `max_patch`", progression->getPatchId());

            if (!result)
                return;

            do
            {
                Field* fields = result->Fetch();
                uint32 ID     = fields[0].GetUInt32();

                Quest* quest = sObjectMgr->GetQuestTemplates().at(ID);

                if (!quest)
                    continue;
            } while (result->NextRow());
        }
};

void AddProgressionQuestScripts()
{
    new ProgressionQuest();
}
