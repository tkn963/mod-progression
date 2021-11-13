#include "Config.h"
#include "Progression.h"

class ProgressionGameObject : public WorldScript
{
    public:
        ProgressionGameObject() : WorldScript("ProgressionGameObject") {}

        void OnStartup() override
        {
            DeleteGameObjects();
            UpdateGameObjects();
            UpdateGameobjectTemplates();
        }

    private:
        Progression* progression = new Progression();

        void DeleteGameObjects()
        {
            QueryResult result = WorldDatabase.PQuery("SELECT `guid` FROM `progression_gameobject` WHERE %u NOT BETWEEN `min_patch` AND `max_patch`", progression->getPatchId());

            if (!result)
                return;

            do
            {
                Field* fields = result->Fetch();
                uint32 guid   = fields[0].GetUInt32();

                if (sObjectMgr->GetGOData(guid))
                    sObjectMgr->DeleteGOData(guid);
            } while (result->NextRow());
        }

        void UpdateGameObjects()
        {
            QueryResult result = WorldDatabase.PQuery("SELECT `guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, "
                                                      "`orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, "
                                                      "`spawntimesecs` FROM `progression_gameobject` WHERE %u BETWEEN `min_patch` AND `max_patch`", progression->getPatchId());

            if (!result)
                return;

            do
            {
                Field* fields      = result->Fetch();
                uint32 guid        = fields[0].GetUInt32();
                uint32 id          = fields[1].GetUInt32();
                uint32 mapId       = fields[2].GetUInt32();
                float position_x   = fields[3].GetFloat();
                float position_y   = fields[4].GetFloat();
                float position_z   = fields[5].GetFloat();
                float orientation  = fields[6].GetFloat();
                float rotation0    = fields[7].GetFloat();
                float rotation1    = fields[8].GetFloat();
                float rotation2    = fields[9].GetFloat();
                float rotation3    = fields[10].GetFloat();
                uint32 spawnTime   = fields[11].GetUInt32();

                const GameObjectData* gameObjectData = sObjectMgr->GetGOData(guid);

                    if (gameObjectData)
                        sObjectMgr->DeleteGOData(guid);

                    sObjectMgr->AddGOData(id, mapId, position_x, position_y, position_z, orientation, spawnTime, rotation0, rotation1, rotation2, rotation3);
            } while (result->NextRow());
        }

        void UpdateGameobjectTemplates()
        {
            QueryResult result = WorldDatabase.PQuery("SELECT `entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `size`, `Data0`, "
                                                      "`Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `Data6`, `Data7`, `Data8`, `Data9`, `Data10`, `Data11`, "
                                                      "`Data12`, `Data13`, `Data14`, `Data15`, `Data16`, `Data17`, `Data18`, `Data19`, `Data20`, `Data21`, "
                                                      "`Data22`, `Data23` FROM `progression_gameobject_template` a "
                                                      "WHERE `patch`=(SELECT max(patch) FROM `progression_gameobject_template` b WHERE a.`entry`=b.`entry` && `patch` <= %u)",
                                                      progression->getPatchId());

            if (!result)
                return;

            do
            {
                Field*fields               = result->Fetch();
                uint32 entry               = fields[0].GetUInt32();
                uint32 type                = uint32(fields[1].GetUInt8());
                uint32 displayId           = fields[2].GetUInt32();
                std::string name           = fields[3].GetString();
                std::string iconName       = fields[4].GetString();
                std::string castBarCaption = fields[5].GetString();
                std::string unk1           = fields[6].GetString();
                float size                 = fields[7].GetFloat();

                GameObjectTemplate* gameObject = const_cast<GameObjectTemplate*>(&sObjectMgr->GetGameObjectTemplates()->at(entry));

                if (!gameObject)
                    continue;

                gameObject->type = type;
                gameObject->displayId = displayId;
                gameObject->name = name;
                gameObject->IconName = iconName;
                gameObject->castBarCaption = castBarCaption;
                gameObject->unk1 = unk1;
                gameObject->size = size;

                for (uint8 i = 0; i < MAX_GAMEOBJECT_DATA; ++i)
                    gameObject->raw.data[i] = fields[8 + i].GetUInt32();
            } while (result->NextRow());
        }
};

void AddProgressionGameObjectScripts()
{
    new ProgressionGameObject();
}
