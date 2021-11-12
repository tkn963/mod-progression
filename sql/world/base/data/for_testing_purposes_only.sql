-- Test creature spawns by setting all spawns to max patch (requires patch < 20 in config)
INSERT INTO `progression_creature` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`)
SELECT `guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs` FROM creature;

UPDATE `progression_creature` SET `min_patch`=20;

-- Test object spawns by setting all spawns to max patch (requires patch < 20 in config)
INSERT INTO `progression_gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`)
SELECT `guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs` FROM gameobject;

UPDATE `progression_gameobject` SET `min_patch`=20;

-- Test quest ender NPCs by setting all to max patch (requires patch < 20 in config)
INSERT INTO `progression_creature_questender` (`id`, `quest`)
SELECT `id`, `quest` FROM `creature_questender`;

UPDATE `progression_creature_questender` SET `min_patch`=20;

-- Test quest starter NPCs by setting all to max patch (requires patch < 20 in config)
INSERT INTO `progression_creature_queststarter` (`id`, `quest`)
SELECT `id`, `quest` FROM `creature_queststarter`;

UPDATE `progression_creature_queststarter` SET `min_patch`=20;
