INSERT INTO `progression_creature` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`)
SELECT `guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs` FROM creature;

UPDATE `progression_creature` SET `min_patch`=20;

INSERT INTO `progression_game_event` (`eventEntry`)
SELECT `eventEntry` FROM game_event;

UPDATE `progression_game_event` SET `min_patch`=20;

INSERT INTO `progression_gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`)
SELECT `guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs` FROM gameobject;

UPDATE `progression_gameobject` SET `min_patch`=20;
