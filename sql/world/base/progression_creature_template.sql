DROP TABLE IF EXISTS `progression_creature_template`;
CREATE TABLE `progression_creature_template` (
	`entry` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
    `patch` INT(2) UNSIGNED NOT NULL DEFAULT '0',
	`name` CHAR(100) NOT NULL DEFAULT '0' COLLATE 'utf8mb4_general_ci',
	`subname` CHAR(100) NULL DEFAULT NULL COLLATE 'utf8mb4_general_ci',
	`minlevel` TINYINT(3) UNSIGNED NOT NULL DEFAULT '1',
	`maxlevel` TINYINT(3) UNSIGNED NOT NULL DEFAULT '1',
	`rank` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
	PRIMARY KEY (`entry`, `patch`) USING BTREE
)
COLLATE='utf8mb4_general_ci'
ENGINE=InnoDB
;
