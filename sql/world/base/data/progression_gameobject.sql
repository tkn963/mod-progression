-- Meeting Stone (added in patch 1.3)
DELETE FROM `progression_gameobject` WHERE `id` IN (SELECT `entry` FROM `gameobject_template` WHERE `name` = 'Meeting Stone');
INSERT INTO `progression_gameobject` (`guid`, `min_patch`, `max_patch`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`) 
SELECT `guid`, 2, 20, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs` FROM gameobject WHERE `id` IN (
SELECT `entry` FROM `gameobject_template` WHERE `name` = 'Meeting Stone'
);

-- Guild Vault (added in patch 2.3)
DELETE FROM `progression_gameobject` WHERE `id` IN (SELECT `entry` FROM `gameobject_template` WHERE `name` = 'Guild Vault');
INSERT INTO `progression_gameobject` (`guid`, `min_patch`, `max_patch`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`) 
SELECT `guid`, 15, 20, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs` FROM gameobject WHERE `id` IN (
SELECT `entry` FROM `gameobject_template` WHERE `name` = 'Guild Vault'
);
