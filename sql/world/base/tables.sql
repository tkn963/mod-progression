-- Creature
DROP TABLE IF EXISTS `progression_creature`;
CREATE TABLE `progression_creature` (
    `guid` INT(10) UNSIGNED NOT NULL,
	`id` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Creature Identifier',
	`map` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Map Identifier',
	`position_x` FLOAT NOT NULL DEFAULT '0',
	`position_y` FLOAT NOT NULL DEFAULT '0',
	`position_z` FLOAT NOT NULL DEFAULT '0',
	`orientation` FLOAT NOT NULL DEFAULT '0',
	`spawntimesecs` INT(10) UNSIGNED NOT NULL DEFAULT '120',
    `min_patch` INT(2) UNSIGNED NOT NULL DEFAULT '0',
    `max_patch` INT(2) UNSIGNED NOT NULL DEFAULT '20',
	PRIMARY KEY (`guid`, `min_patch`, `max_patch`) USING BTREE
)
COLLATE='utf8mb4_general_ci'
ENGINE=InnoDB
;

INSERT INTO `progression_creature` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`)
SELECT `guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs` FROM creature;

UPDATE `progression_creature` SET `min_patch`=20;

/*
UPDATE ptr_world.progression_creature SET min_patch = 0 WHERE id IN (
SELECT vct.entry FROM vmangos.creature_template vct 
LEFT OUTER JOIN ptr_world.creature_template ct ON vct.entry = ct.entry AND vct.`name` = ct.`name`;
)
*/

-- Creature Template
DROP TABLE IF EXISTS `progression_creature_template`;
CREATE TABLE `progression_creature_template` (
	`entry` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
	`name` CHAR(100) NOT NULL DEFAULT '0' COLLATE 'utf8mb4_general_ci',
	`subname` CHAR(100) NULL DEFAULT NULL COLLATE 'utf8mb4_general_ci',
	`minlevel` TINYINT(3) UNSIGNED NOT NULL DEFAULT '1',
	`maxlevel` TINYINT(3) UNSIGNED NOT NULL DEFAULT '1',
	`rank` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
    `min_patch` INT(2) UNSIGNED NOT NULL DEFAULT '0',
    `max_patch` INT(2) UNSIGNED NOT NULL DEFAULT '20',
	PRIMARY KEY (`entry`, `min_patch`, `max_patch`) USING BTREE
)
COLLATE='utf8mb4_general_ci'
ENGINE=InnoDB
;

INSERT INTO `progression_creature_template` (`entry`, `name`, `subname`, `minlevel`, `maxlevel`, `rank`)
SELECT `entry`, `name`, `subname`, `minlevel`, `maxlevel`, `rank` FROM creature_template;

UPDATE `progression_creature_template` SET `min_patch`=20;

/*
UPDATE `progression_creature_template` `pct` 
JOIN `vmangos`.`creature_template` `vct` ON `pct`.`entry` = `vct`.`entry` AND `pct`.`name` = `vct`.`name` 
SET `pct`.`minlevel` = `vct`.`level_min`, `pct`.`maxlevel` = `vct`.`level_max`, `pct`.`rank` = `vct`.`rank`, `min_patch` = 0;
*/

-- GameObject
DROP TABLE IF EXISTS `progression_gameobject`;
CREATE TABLE `progression_gameobject` (
	`guid` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'Global Unique Identifier',
	`id` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Gameobject Identifier',
	`map` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Map Identifier',
	`position_x` FLOAT NOT NULL DEFAULT '0',
	`position_y` FLOAT NOT NULL DEFAULT '0',
	`position_z` FLOAT NOT NULL DEFAULT '0',
	`orientation` FLOAT NOT NULL DEFAULT '0',
	`rotation0` FLOAT NOT NULL DEFAULT '0',
	`rotation1` FLOAT NOT NULL DEFAULT '0',
	`rotation2` FLOAT NOT NULL DEFAULT '0',
	`rotation3` FLOAT NOT NULL DEFAULT '0',
	`spawntimesecs` INT(11) NOT NULL DEFAULT '0',
    `min_patch` INT(2) UNSIGNED NOT NULL DEFAULT '0',
    `max_patch` INT(2) UNSIGNED NOT NULL DEFAULT '20',
	PRIMARY KEY (`guid`, `min_patch`, `max_patch`) USING BTREE
)
COLLATE='utf8mb4_general_ci'
ENGINE=InnoDB
;

INSERT INTO `progression_gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`)
SELECT `guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs` FROM gameobject;

UPDATE `progression_gameobject` SET `min_patch`=20;

-- Events
DROP TABLE IF EXISTS `progression_game_event`;
CREATE TABLE `progression_game_event` (
	`eventEntry` TINYINT(3) UNSIGNED NOT NULL COMMENT 'Entry of the game event',
    `min_patch` INT(2) UNSIGNED NOT NULL DEFAULT '0',
    `max_patch` INT(2) UNSIGNED NOT NULL DEFAULT '20',
	PRIMARY KEY (`eventEntry`, `min_patch`, `max_patch`) USING BTREE
)
COLLATE='utf8mb4_general_ci'
ENGINE=InnoDB
;

INSERT INTO `progression_game_event` (`eventEntry`)
SELECT `eventEntry` FROM game_event;

UPDATE `progression_game_event` SET `min_patch`=20;

/*
UPDATE ptr_world.progression_gameobject SET min_patch = 0 WHERE id IN (
SELECT vgt.entry FROM vmangos.gameobject_template vgt 
LEFT OUTER JOIN ptr_world.gameobject_template gt ON vgt.entry = gt.entry AND gt.`name` = vgt.`name`;
*/

-- NPC Trainer
DROP TABLE IF EXISTS `progression_npc_trainer`;
CREATE TABLE `progression_npc_trainer` (
	`ID` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
	`SpellID` MEDIUMINT(9) NOT NULL DEFAULT '0',
	`MoneyCost` INT(10) UNSIGNED NOT NULL DEFAULT '0',
	`ReqSkillLine` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0',
	`ReqSkillRank` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0',
	`ReqLevel` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
    `min_patch` INT(2) UNSIGNED NOT NULL DEFAULT '0',
    `max_patch` INT(2) UNSIGNED NOT NULL DEFAULT '20',
	PRIMARY KEY (`ID`, `SpellID`, `min_patch`, `max_patch`) USING BTREE
)
COLLATE='utf8mb4_general_ci'
ENGINE=InnoDB
;

INSERT INTO `progression_npc_trainer` (`ID`, `SpellID`, `MoneyCost`, `ReqSkillLine`, `ReqSkillRank`, `ReqLevel`)
SELECT `ID`, `SpellID`, `MoneyCost`, `ReqSkillLine`, `ReqSkillRank`, `ReqLevel` FROM npc_trainer WHERE `ID` > 0 AND `SpellID` > 0;

UPDATE `progression_npc_trainer` SET `min_patch`=20;

-- NPC Vendor
DROP TABLE IF EXISTS `progression_npc_vendor`;
CREATE TABLE `progression_npc_vendor` (
	`entry` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
	`slot` SMALLINT(6) NOT NULL DEFAULT '0',
	`item` MEDIUMINT(9) NOT NULL DEFAULT '0',
	`maxcount` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
	`incrtime` INT(10) UNSIGNED NOT NULL DEFAULT '0',
	`ExtendedCost` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
    `min_patch` INT(2) UNSIGNED NOT NULL DEFAULT '0',
    `max_patch` INT(2) UNSIGNED NOT NULL DEFAULT '20',
	PRIMARY KEY (`entry`, `item`, `ExtendedCost`, `min_patch`, `max_patch`) USING BTREE
)
COLLATE='utf8mb4_general_ci'
ENGINE=InnoDB
;

INSERT INTO `progression_npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`)
SELECT `entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost` FROM npc_vendor WHERE `Item` > 0;

UPDATE `progression_npc_vendor` SET `min_patch`=20;
