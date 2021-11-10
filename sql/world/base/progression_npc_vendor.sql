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
