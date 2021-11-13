-- Test creature spawns by setting all spawns to max patch (requires patch < 20 in config)
INSERT INTO `progression_creature` (`guid`, `min_patch`, `max_patch`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`)
SELECT `guid`, 20, 20, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs` FROM creature;

-- Test object spawns by setting all spawns to max patch (requires patch < 20 in config)
INSERT INTO `progression_gameobject` (`guid`, `min_patch`, `max_patch`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`)
SELECT `guid`, 20, 20, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs` FROM gameobject;

-- Test quest ender NPCs by setting all to max patch (requires patch < 20 in config)
INSERT INTO `progression_creature_questender` (`id`, `quest`, `min_patch`, `max_patch`)
SELECT `id`, `quest`, 20, 20 FROM `creature_questender`;

-- Test quest starter NPCs by setting all to max patch (requires patch < 20 in config)
INSERT INTO `progression_creature_queststarter` (`id`, `quest`, `min_patch`, `max_patch`)
SELECT `id`, `quest`, 20, 20 FROM `creature_queststarter`;

-- Test quest ender objects by setting all to max patch (requires patch < 20 in config)
INSERT INTO `progression_gameobject_questender` (`id`, `quest`, `min_patch`, `max_patch`)
SELECT `id`, `quest`, 20, 20 FROM `gameobject_questender`;

-- Test quest starter objects by setting all to max patch (requires patch < 20 in config)
INSERT INTO `progression_gameobject_queststarter` (`id`, `quest`, `min_patch`, `max_patch`)
SELECT `id`, `quest`, 20, 20 FROM `gameobject_queststarter`;
