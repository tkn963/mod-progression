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
            QueryResult result = WorldDatabase.PQuery("SELECT guid FROM progression_gameobject WHERE %u NOT BETWEEN min_patch AND max_patch", progression->getPatchId());

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
            QueryResult result = WorldDatabase.PQuery("SELECT guid, id, map, position_x, position_y, position_z, orientation, rotation0, rotation1, rotation2, rotation3, spawntimesecs FROM progression_gameobject WHERE %u BETWEEN min_patch AND max_patch", progression->getPatchId());

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

                if (gameObjectData->mapid != mapId || gameObjectData->posX != position_x || gameObjectData->posY != position_y ||
                    gameObjectData->posZ != position_z || gameObjectData->orientation != orientation || gameObjectData->rotation.x != rotation0 ||
                    gameObjectData->rotation.y != rotation1 || gameObjectData->rotation.z != rotation2 || gameObjectData->rotation.w != rotation3 ||
                    gameObjectData->spawntimesecs != spawnTime)
                {
                    if (gameObjectData)
                        sObjectMgr->DeleteGOData(guid);

                    if (gameObjectData->id == id)
                        sObjectMgr->AddGOData(id, mapId, position_x, position_y, position_z, orientation, spawnTime, rotation0, rotation1, rotation2, rotation3);
                }
            } while (result->NextRow());
        }

        void UpdateGameobjectTemplates()
        {
            QueryResult result = WorldDatabase.PQuery("SELECT entry, name FROM progression_gameobject_template a "
                                                      "WHERE patch=(SELECT max(patch) FROM progression_gameobject_template b WHERE a.entry=b.entry && patch <= %u)",
                                                      progression->getPatchId());

            if (!result)
                return;

            do
            {
                Field*fields     = result->Fetch();
                uint32 entry     = fields[0].GetUInt32();
                std::string name = fields[1].GetString();

                GameObjectTemplate* gameobject = const_cast<GameObjectTemplate*>(&sObjectMgr->GetGameObjectTemplates()->at(entry));

                if (!gameobject)
                    continue;

                if (gameobject->name != name)
                    gameobject->name = name;
            } while (result->NextRow());
        }
};

void AddProgressionGameObjectScripts()
{
    new ProgressionGameObject();
}
