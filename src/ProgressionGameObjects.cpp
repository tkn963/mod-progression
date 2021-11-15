#include "Config.h"
#include "Progression.h"

class ProgressionGameObjects : public WorldScript
{
    public:
        ProgressionGameObjects() : WorldScript("ProgressionGameObjects") {}

        void OnBeforeGameObjectQueried(std::string& query) override
        {
            query = Acore::StringFormat("SELECT gameobject.guid, id, map, position_x, position_y, position_z, orientation, rotation0, rotation1, "
                                        "rotation2, rotation3, spawntimesecs, animprogress, state, spawnMask, phaseMask, eventEntry, pool_entry, ScriptName "
                                        "FROM gameobject LEFT OUTER JOIN game_event_gameobject ON gameobject.guid = game_event_gameobject.guid "
                                        "LEFT OUTER JOIN pool_gameobject ON gameobject.guid = pool_gameobject.guid "
                                        "WHERE %u BETWEEN min_patch AND max_patch",
                                        progression->getPatchId());
        }

        void OnBeforeGameObjectTemplateQueried(std::string& query) override
        {
            query = Acore::StringFormat("SELECT entry, type, displayId, name, IconName, castBarCaption, unk1, size, "
                                        "Data0, Data1, Data2, Data3, Data4, Data5, Data6, Data7, Data8, Data9, Data10, Data11, Data12, "
                                        "Data13, Data14, Data15, Data16, Data17, Data18, Data19, Data20, Data21, Data22, Data23, AIName, ScriptName "
                                        "FROM gameobject_template a WHERE patch=(SELECT max(patch) FROM gameobject_template b WHERE a.entry=b.entry && patch <= %u)",
                                        progression->getPatchId());
        }

    private:
        Progression* progression = new Progression();
};

void AddProgressionGameObjectsScripts()
{
    new ProgressionGameObjects();
}
