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

                sObjectMgr->DeleteGOData(guid);
            } while (result->NextRow());
        }

        void UpdateGameObjects()
        {
            QueryResult result = WorldDatabase.PQuery("SELECT guid, map, position_x, position_y, position_z, orientation, rotation0, rotation1, rotation2, rotation3, spawntimesecs FROM progression_gameobject WHERE %u BETWEEN min_patch AND max_patch", progression->getPatchId());

            if (!result)
                return;

            do
            {
                Field* fields      = result->Fetch();
                uint32 guid        = fields[0].GetUInt32();
                uint32 mapId       = fields[1].GetUInt32();
                float position_x   = fields[2].GetFloat();
                float position_y   = fields[3].GetFloat();
                float position_z   = fields[4].GetFloat();
                float orientation  = fields[5].GetFloat();
                float rotation0    = fields[6].GetFloat();
                float rotation1    = fields[7].GetFloat();
                float rotation2    = fields[8].GetFloat();
                float rotation3    = fields[9].GetFloat();
                uint32 spawnTime   = fields[10].GetUInt32();

                const GameObjectData* gameObjectData = sObjectMgr->GetGOData(guid);

                if (gameObjectData->mapid != mapId || gameObjectData->posX != position_x || gameObjectData->posY != position_y ||
                    gameObjectData->posZ != position_z || gameObjectData->orientation != orientation || gameObjectData->rotation.x != rotation0 ||
                    gameObjectData->rotation.y != rotation1 || gameObjectData->rotation.z != rotation2 || gameObjectData->rotation.w != rotation3 ||
                    gameObjectData->spawntimesecs != spawnTime)
                {
                    sObjectMgr->DeleteGOData(guid);
                    sObjectMgr->AddGOData(gameObjectData->id, mapId, position_x, position_y, position_z, orientation, spawnTime, rotation0, rotation1, rotation2, rotation3);
                }
            } while (result->NextRow());
        }
};

void AddProgressionGameObjectScripts()
{
    new ProgressionGameObject();
}
