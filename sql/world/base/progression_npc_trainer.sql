DROP TABLE IF EXISTS `progression_npc_trainer`;
CREATE TABLE `progression_npc_trainer` (
    `ID` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
    `SpellID` MEDIUMINT(9) NOT NULL DEFAULT '0',
    `min_patch` INT(2) UNSIGNED NOT NULL DEFAULT '0',
    `max_patch` INT(2) UNSIGNED NOT NULL DEFAULT '20',
    `MoneyCost` INT(10) UNSIGNED NOT NULL DEFAULT '0',
    `ReqSkillLine` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0',
    `ReqSkillRank` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0',
    `ReqLevel` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
    PRIMARY KEY (`ID`, `SpellID`, `min_patch`, `max_patch`) USING BTREE
)
COLLATE='utf8mb4_general_ci'
ENGINE=InnoDB
;
