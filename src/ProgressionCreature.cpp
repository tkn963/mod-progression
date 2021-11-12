#include "Config.h"
#include "Progression.h"

class ProgressionCreature : public WorldScript
{
    public:
        ProgressionCreature() : WorldScript("ProgressionCreature") {}

        void OnStartup() override
        {
            DeleteCreatures();
            UpdateCreatures();
            UpdateCreatureTemplates();
        }

    private:
        Progression* progression = new Progression();

        void DeleteCreatures()
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

        void UpdateCreatures()
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

        void UpdateCreatureTemplates()
        {
            QueryResult result = WorldDatabase.PQuery("SELECT `entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, "
                                                      "`modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, "
                                                      "`maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `detection_range`, `scale`, `rank`, `dmgschool`, "
                                                      "`DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, "
                                                      "`unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, "
                                                      "`type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, "
                                                      "`MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `ExperienceModifier`, "
                                                      "`RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra` "
                                                      "FROM `progression_creature_template` a "
                                                      "WHERE patch=(SELECT max(patch) FROM progression_creature_template b WHERE a.entry=b.entry && patch <= %u)", progression->getPatchId());

            if (!result)
                return;

            do
            {
                Field* fields            = result->Fetch();
                uint32 entry             = fields[0].GetUInt32();
                uint32 difficultyEntry1  = fields[1].GetUInt32();
                uint32 difficultyEntry2  = fields[2].GetUInt32();
                uint32 difficultyEntry3  = fields[3].GetUInt32();
                uint32 killCredit1       = fields[4].GetUInt32();
                uint32 killCredit2       = fields[5].GetUInt32();
                uint32 modelId1          = fields[6].GetUInt32();
                uint32 modelId2          = fields[7].GetUInt32();
                uint32 modelId3          = fields[8].GetUInt32();
                uint32 modelId4          = fields[9].GetUInt32();
                std::string name         = fields[10].GetString();
                std::string subName      = fields[11].GetString();
                std::string iconName     = fields[12].GetString();
                uint32 gossipMenuId      = fields[13].GetUInt32();
                uint32 minlevel          = uint32(fields[14].GetUInt8());
                uint32 maxlevel          = uint32(fields[15].GetUInt8());
                uint32 expansion         = uint32(fields[16].GetUInt16());
                uint32 faction           = uint32(fields[17].GetUInt16());
                uint32 npcFlag           = fields[18].GetUInt32();
                float speedWalk          = fields[19].GetFloat();
                float speedRun           = fields[20].GetFloat();
                float detectionRange     = fields[21].GetFloat();
                float scale              = fields[22].GetFloat();
                uint32 rank              = fields[23].GetUInt32();
                uint32 dmgSchool         = fields[24].GetUInt32();
                float damageModifier     = fields[25].GetFloat();
                uint32 baseAttackTime    = fields[26].GetUInt32();
                uint32 rangeAttackTime   = fields[27].GetUInt32();
                float baseVariance       = fields[28].GetFloat();
                float rangeVariance      = fields[29].GetFloat();
                uint32 unitClass         = uint32(fields[30].GetUInt8());
                uint32 unitFlags         = fields[31].GetUInt32();
                uint32 unitFlags2        = fields[32].GetUInt32();
                uint32 dynamicFlags      = fields[33].GetUInt32();
                uint32 family            = uint32(fields[34].GetUInt8());
                uint32 trainerType       = uint32(fields[35].GetUInt8());
                uint32 trainerSpell      = fields[36].GetUInt32();
                uint32 trainerClass      = uint32(fields[37].GetUInt8());
                uint32 trainerRace       = uint32(fields[38].GetUInt8());
                uint32 type              = uint32(fields[39].GetUInt8());
                uint32 typeFlags         = fields[40].GetUInt32();
                uint32 lootId            = fields[41].GetUInt32();
                uint32 pickPocketLootId  = fields[42].GetUInt32();
                uint32 skinningLootId    = fields[43].GetUInt32();
                uint32 petSpellDataId    = fields[44].GetUInt32();
                uint32 vehicleId         = fields[45].GetUInt32();
                uint32 minGold           = fields[46].GetUInt32();
                uint32 maxGold           = fields[47].GetUInt32();
                std::string aiName       = fields[48].GetString();
                uint32 movementType      = fields[49].GetUInt32();
                uint32 inhabitType       = fields[50].GetUInt32();
                float hoverHeight        = fields[51].GetFloat();
                float healthModifier     = fields[52].GetFloat();
                float manaModifier       = fields[53].GetFloat();
                float armorModifier      = fields[54].GetFloat();
                float experienceModifier = fields[55].GetFloat();
                uint32 racialLeader      = fields[56].GetUInt32();
                uint32 movementId        = fields[57].GetUInt32();
                uint32 regenHealth       = fields[58].GetUInt32();
                uint32 immuneMask        = fields[59].GetUInt32();
                uint32 spellImmuneMask   = fields[60].GetUInt32();
                uint32 flagsExtra        = fields[61].GetUInt32();

                CreatureTemplate* creatureTemplate = const_cast<CreatureTemplate*>(&sObjectMgr->GetCreatureTemplates()->at(entry));

                if (!creatureTemplate)
                    continue;

                if (creatureTemplate->DifficultyEntry[0] != difficultyEntry1)
                    creatureTemplate->DifficultyEntry[0] = difficultyEntry1;

                if (creatureTemplate->DifficultyEntry[1] != difficultyEntry2)
                    creatureTemplate->DifficultyEntry[1] = difficultyEntry2;

                if (creatureTemplate->DifficultyEntry[2] != difficultyEntry3)
                    creatureTemplate->DifficultyEntry[2] = difficultyEntry3;

                if (creatureTemplate->KillCredit[0] != killCredit1)
                    creatureTemplate->KillCredit[0] = killCredit1;

                if (creatureTemplate->KillCredit[1] != killCredit2)
                    creatureTemplate->KillCredit[1] = killCredit2;

                if (creatureTemplate->Modelid1 != modelId1)
                    creatureTemplate->Modelid1 = modelId1;

                if (creatureTemplate->Modelid2 != modelId2)
                    creatureTemplate->Modelid2 = modelId2;

                if (creatureTemplate->Modelid3 != modelId3)
                    creatureTemplate->Modelid3 = modelId3;

                if (creatureTemplate->Modelid4 != modelId4)
                    creatureTemplate->Modelid4 = modelId4;

                if (creatureTemplate->Name != name)
                    creatureTemplate->Name = name;

                if (creatureTemplate->SubName != subName)
                    creatureTemplate->SubName = subName;

                if (creatureTemplate->IconName != iconName)
                    creatureTemplate->IconName = iconName;

                if (creatureTemplate->GossipMenuId != gossipMenuId)
                    creatureTemplate->GossipMenuId = gossipMenuId;

                if (creatureTemplate->minlevel != minlevel)
                    creatureTemplate->minlevel = minlevel;

                if (creatureTemplate->maxlevel != maxlevel)
                    creatureTemplate->maxlevel = maxlevel;

                if (creatureTemplate->expansion != expansion)
                    creatureTemplate->expansion = expansion;

                if (creatureTemplate->faction != faction)
                    creatureTemplate->faction = faction;

                if (creatureTemplate->npcflag != npcFlag)
                    creatureTemplate->npcflag = npcFlag;

                if (creatureTemplate->speed_walk != speedWalk)
                    creatureTemplate->speed_walk = speedWalk;

                if (creatureTemplate->speed_run != speedRun)
                    creatureTemplate->speed_run = speedRun;

                if (creatureTemplate->detection_range != detectionRange)
                    creatureTemplate->detection_range = detectionRange;

                if (creatureTemplate->scale != scale)
                    creatureTemplate->scale = scale;

                if (creatureTemplate->rank != rank)
                    creatureTemplate->rank = rank;

                if (creatureTemplate->dmgschool != dmgSchool)
                    creatureTemplate->dmgschool = dmgSchool;

                if (creatureTemplate->DamageModifier != damageModifier)
                    creatureTemplate->DamageModifier = damageModifier;

                if (creatureTemplate->BaseAttackTime != baseAttackTime)
                    creatureTemplate->BaseAttackTime = baseAttackTime;

                if (creatureTemplate->RangeAttackTime != rangeAttackTime)
                    creatureTemplate->RangeAttackTime = rangeAttackTime;

                if (creatureTemplate->BaseVariance != baseVariance)
                    creatureTemplate->BaseVariance = baseVariance;

                if (creatureTemplate->RangeVariance != rangeVariance)
                    creatureTemplate->RangeVariance = rangeVariance;

                if (creatureTemplate->unit_class != unitClass)
                    creatureTemplate->unit_class = unitClass;

                if (creatureTemplate->unit_flags != unitFlags)
                    creatureTemplate->unit_flags = unitFlags;

                if (creatureTemplate->unit_flags2 != unitFlags2)
                    creatureTemplate->unit_flags2 = unitFlags2;

                if (creatureTemplate->dynamicflags != dynamicFlags)
                    creatureTemplate->dynamicflags = dynamicFlags;

                if (creatureTemplate->family != family)
                    creatureTemplate->family = family;

                if (creatureTemplate->trainer_type != trainerType)
                    creatureTemplate->trainer_type = trainerType;

                if (creatureTemplate->trainer_spell != trainerSpell)
                    creatureTemplate->trainer_spell = trainerSpell;

                if (creatureTemplate->trainer_class != trainerClass)
                    creatureTemplate->trainer_class = trainerClass;

                if (creatureTemplate->trainer_race != trainerRace)
                    creatureTemplate->trainer_race = trainerRace;

                if (creatureTemplate->type != type)
                    creatureTemplate->type = type;

                if (creatureTemplate->type_flags != typeFlags)
                    creatureTemplate->type_flags = typeFlags;

                if (creatureTemplate->lootid != lootId)
                    creatureTemplate->lootid = lootId;

                if (creatureTemplate->pickpocketLootId != pickPocketLootId)
                    creatureTemplate->pickpocketLootId = pickPocketLootId;

                if (creatureTemplate->SkinLootId != skinningLootId)
                    creatureTemplate->SkinLootId = skinningLootId;

                if (creatureTemplate->PetSpellDataId != petSpellDataId)
                    creatureTemplate->PetSpellDataId = petSpellDataId;

                if (creatureTemplate->VehicleId != vehicleId)
                    creatureTemplate->VehicleId = vehicleId;

                if (creatureTemplate->mingold != minGold)
                    creatureTemplate->mingold = minGold;

                if (creatureTemplate->maxgold != maxGold)
                    creatureTemplate->maxgold = maxGold;

                if (creatureTemplate->AIName != aiName)
                    creatureTemplate->AIName = aiName;

                if (creatureTemplate->MovementType != movementType)
                    creatureTemplate->MovementType = movementType;

                if (creatureTemplate->InhabitType != inhabitType)
                    creatureTemplate->InhabitType = inhabitType;

                if (creatureTemplate->HoverHeight != hoverHeight)
                    creatureTemplate->HoverHeight = hoverHeight;

                if (creatureTemplate->ModHealth != healthModifier)
                    creatureTemplate->ModHealth = healthModifier;

                if (creatureTemplate->ModMana != manaModifier)
                    creatureTemplate->ModMana = manaModifier;

                if (creatureTemplate->ModArmor != armorModifier)
                    creatureTemplate->ModArmor = armorModifier;

                if (creatureTemplate->ModExperience != experienceModifier)
                    creatureTemplate->ModExperience = experienceModifier;

                if (creatureTemplate->RacialLeader != racialLeader)
                    creatureTemplate->RacialLeader = racialLeader;

                if (creatureTemplate->movementId != movementId)
                    creatureTemplate->movementId = movementId;

                if (creatureTemplate->RegenHealth != regenHealth)
                    creatureTemplate->RegenHealth = regenHealth;

                if (creatureTemplate->MechanicImmuneMask != immuneMask)
                    creatureTemplate->MechanicImmuneMask = immuneMask;

                if (creatureTemplate->SpellSchoolImmuneMask != spellImmuneMask)
                    creatureTemplate->SpellSchoolImmuneMask = spellImmuneMask;

                if (creatureTemplate->flags_extra != flagsExtra)
                    creatureTemplate->flags_extra = flagsExtra;
            } while (result->NextRow());
        }
};

void AddProgressionCreatureScripts()
{
    new ProgressionCreature();
}
