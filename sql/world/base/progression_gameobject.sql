-- GameObject
DROP TABLE IF EXISTS `progression_gameobject`;
CREATE TABLE `progression_gameobject` (
    `guid` INT(10) UNSIGNED NOT NULL COMMENT 'Global Unique Identifier',
    `min_patch` INT(2) UNSIGNED NOT NULL DEFAULT '0',
    `max_patch` INT(2) UNSIGNED NOT NULL DEFAULT '20',
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
    PRIMARY KEY (`guid`, `min_patch`, `max_patch`) USING BTREE
)
COLLATE='utf8mb4_general_ci'
ENGINE=InnoDB
;
