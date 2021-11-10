#include "Config.h"
#include "Progression.h"

class ProgressionCreature : public WorldScript
{
    public:
        ProgressionCreature() : WorldScript("ProgressionCreature") {}

        void OnStartup() override
        {
            DeleteCreatureData();
            SetCreatureData();
            SetCreatureTemplateData();
        }

    private:
        Progression* progression = new Progression();

        void DeleteCreatureData()
        {
            QueryResult result = WorldDatabase.PQuery("SELECT guid FROM progression_creature WHERE %u NOT BETWEEN min_patch AND max_patch", progression->getPatchId());

            if (!result)
                return;

            do
            {
                Field* fields = result->Fetch();
                uint32 guid   = fields[0].GetUInt32();

                sObjectMgr->DeleteCreatureData(guid);
            } while (result->NextRow());
        }

        void SetCreatureData()
        {
            QueryResult result = WorldDatabase.PQuery("SELECT guid, map, position_x, position_y, position_z, orientation, spawntimesecs FROM progression_creature WHERE %u BETWEEN min_patch AND max_patch", progression->getPatchId());

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
                uint32 spawnTime   = fields[6].GetUInt32();

                const CreatureData* creatureData = sObjectMgr->GetCreatureData(guid);

                if (!creatureData)
                    continue;

                if (creatureData->mapid != mapId || creatureData->posX != position_x || creatureData->posY != position_y ||
                    creatureData->posZ != position_z || creatureData->orientation != orientation || creatureData->spawntimesecs != spawnTime)
                {
                    sObjectMgr->DeleteCreatureData(guid);
                    sObjectMgr->AddCreData(creatureData->id, mapId, position_x, position_y, position_z, orientation, spawnTime);
                }
            } while (result->NextRow());
        }

        void SetCreatureTemplateData()
        {
            QueryResult result = WorldDatabase.PQuery("SELECT entry, name, subname, minlevel, maxlevel, rank FROM progression_creature_template a "
                                                      "WHERE patch=(SELECT max(patch) FROM progression_creature_template b WHERE a.entry=b.entry && patch <= %u)", progression->getPatchId());

            if (!result)
                return;

            do
            {
                Field* fields       = result->Fetch();
                uint32 entry        = fields[0].GetUInt32();
                std::string name    = fields[1].GetString();
                std::string subname = fields[2].GetString();
                uint32 minlevel     = fields[3].GetUInt32();
                uint32 maxlevel     = fields[4].GetUInt32();
                uint32 rank         = fields[5].GetUInt32();

                CreatureTemplate* creature = const_cast<CreatureTemplate*>(&sObjectMgr->GetCreatureTemplates()->at(entry));

                if (!creature)
                    continue;

                if (creature->Name != name)
                    creature->Name = name;

                if (creature->SubName != subname)
                    creature->SubName = subname;

                if (creature->minlevel != minlevel)
                    creature->minlevel = minlevel;

                if (creature->maxlevel != maxlevel)
                    creature->maxlevel = maxlevel;

                if (creature->rank != rank)
                    creature->rank = rank;
            } while (result->NextRow());
        }
};

void AddProgressionCreatureScripts()
{
    new ProgressionCreature();
}
