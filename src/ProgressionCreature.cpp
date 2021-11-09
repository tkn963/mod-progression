#include "Config.h"
#include "Progression.h"

class ProgressionCreature : public WorldScript
{
    public:
        ProgressionCreature() : WorldScript("ProgressionCreature") {}

        void OnStartup() override
        {
            DeleteCreatureData();
            CheckCreatureData();
        }

    private:
        Progression* progression = new Progression();

        void DeleteCreatureData()
        {
            QueryResult result = WorldDatabase.PQuery("SELECT guid FROM progression_creature WHERE patch > %u", progression->getPatchId());

            if (!result)
                return;

            uint32 count = 0;
            do
            {
                Field* fields = result->Fetch();
                uint32 guid   = fields[0].GetUInt32();

                sObjectMgr->DeleteCreatureData(guid);
                ++count;
            } while (result->NextRow());

            LOG_INFO("server.loading", ">> Removed %u creatures", count);
        }

        void CheckCreatureData()
        {
            QueryResult result = WorldDatabase.PQuery("SELECT guid, map, position_x, position_y, position_z, orientation, spawntimesecs FROM progression_creature a WHERE patch = (SELECT max(patch) FROM progression_creature b WHERE a.guid = b.guid && patch <= %u)", progression->getPatchId());

            if (!result)
                return;

            uint32 count = 0;
            do
            {
                Field* fields      = result->Fetch();
                uint32 guid        = fields[0].GetUInt32();
                uint32 mapId       = fields[1].GetUInt32();
                float position_x   = fields[2].GetFloat();
                float position_y   = fields[3].GetFloat();
                float position_z   = fields[4].GetFloat();
                float orientation  = fields[5].GetFloat();
                uint32 spawnTime   = fields[6].GetUInt32();

                const CreatureData* creatureData = sObjectMgr->GetCreatureData(guid);

                if (creatureData->mapid != mapId ||
                    creatureData->posX != position_x ||
                    creatureData->posY != position_y ||
                    creatureData->posZ != position_z ||
                    creatureData->orientation != orientation ||
                    creatureData->spawntimesecs != spawnTime)
                {
                    sObjectMgr->DeleteCreatureData(guid);
                    sObjectMgr->AddCreData(creatureData->id, mapId, position_x, position_y, position_z, orientation, spawnTime);
                    ++count;
                }
            } while (result->NextRow());

            LOG_INFO("server.loading", ">> Updated %u creatures", count);
        }
};

void AddProgressionCreatureScripts()
{
    new ProgressionCreature();
}
