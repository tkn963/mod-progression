#include "Config.h"
#include "Progression.h"

class ProgressionCreatures : public WorldScript
{
    public:
        ProgressionCreatures() : WorldScript("ProgressionCreatures") {}

        void OnBeforeCreatureQueried(std::string& query) override
        {
            query = Acore::StringFormat("SELECT creature.guid, id, map, modelid, equipment_id, position_x, position_y, position_z, orientation, spawntimesecs, wander_distance, currentwaypoint, "
                                        "curhealth, curmana, MovementType, spawnMask, phaseMask, eventEntry, pool_entry, creature.npcflag, creature.unit_flags, creature.dynamicflags, "
                                        "creature.ScriptName FROM creature "
                                        "LEFT OUTER JOIN game_event_creature ON creature.guid = game_event_creature.guid "
                                        "LEFT OUTER JOIN pool_creature ON creature.guid = pool_creature.guid "
                                        "WHERE %u BETWEEN min_patch AND max_patch",
                                        progression->getPatchId());
        }

        void OnBeforeCreatureTemplateQueried(std::string& query) override
        {
            query = Acore::StringFormat("SELECT entry, difficulty_entry_1, difficulty_entry_2, difficulty_entry_3, KillCredit1, KillCredit2, modelid1, modelid2, modelid3, "
                                        "modelid4, name, subname, IconName, gossip_menu_id, minlevel, maxlevel, exp, faction, npcflag, speed_walk, speed_run, detection_range, "
                                        "scale, `rank`, dmgschool, DamageModifier, BaseAttackTime, RangeAttackTime, BaseVariance, RangeVariance, unit_class, unit_flags, unit_flags2, "
                                        "dynamicflags, family, trainer_type, trainer_spell, trainer_class, trainer_race, type, type_flags, lootid, pickpocketloot, skinloot, "
                                        "PetSpellDataId, VehicleId, mingold, maxgold, AIName, MovementType, InhabitType, HoverHeight, HealthModifier, ManaModifier, ArmorModifier, "
                                        "ExperienceModifier, RacialLeader, movementId, RegenHealth, mechanic_immune_mask, spell_school_immune_mask, flags_extra, ScriptName "
                                        "FROM creature_template a WHERE patch=(SELECT max(patch) FROM creature_template b WHERE a.entry=b.entry && patch <= %u)",
                                        progression->getPatchId());
        }

    private:
        Progression* progression = new Progression();
};

void AddProgressionCreaturesScripts()
{
    new ProgressionCreatures();
}
