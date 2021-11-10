DROP TABLE IF EXISTS `progression_item_template`;
CREATE TABLE `progression_item_template` (
	`entry` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
    `patch` INT(2) UNSIGNED NOT NULL DEFAULT '0',
	`BuyPrice` BIGINT(20) NOT NULL DEFAULT '0',
	`SellPrice` INT(10) UNSIGNED NOT NULL DEFAULT '0',
	`ItemLevel` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0',
	`RequiredLevel` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
	`spellid_1` MEDIUMINT(9) NOT NULL DEFAULT '0',
	`spellcharges_1` SMALLINT(6) NOT NULL DEFAULT '0',
	`spellcategorycooldown_1` INT(11) NOT NULL DEFAULT -1,
	`spellcategory_1` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0',
	`spellid_2` MEDIUMINT(9) NOT NULL DEFAULT '0',
	`spelltrigger_2` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
	`description` VARCHAR(255) NOT NULL DEFAULT '' COLLATE 'utf8mb4_general_ci',
	PRIMARY KEY (`entry`, `patch`) USING BTREE
)
COLLATE='utf8mb4_general_ci'
ENGINE=InnoDB
;
