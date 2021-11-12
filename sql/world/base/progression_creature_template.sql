DROP TABLE IF EXISTS `progression_creature_template`;
CREATE TABLE `progression_creature_template` (
    `entry` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
    `patch` INT(2) UNSIGNED NOT NULL DEFAULT '0',
    `difficulty_entry_1` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
    `difficulty_entry_2` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
    `difficulty_entry_3` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
    `KillCredit1` INT(10) UNSIGNED NOT NULL DEFAULT '0',
    `KillCredit2` INT(10) UNSIGNED NOT NULL DEFAULT '0',
    `modelid1` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
    `modelid2` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
    `modelid3` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
    `modelid4` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
    `name` CHAR(100) NOT NULL DEFAULT '0' COLLATE 'utf8mb4_general_ci',
    `subname` CHAR(100) NULL DEFAULT NULL COLLATE 'utf8mb4_general_ci',
    `IconName` CHAR(100) NULL DEFAULT NULL COLLATE 'utf8mb4_general_ci',
    `gossip_menu_id` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
    `minlevel` TINYINT(3) UNSIGNED NOT NULL DEFAULT '1',
    `maxlevel` TINYINT(3) UNSIGNED NOT NULL DEFAULT '1',
    `exp` SMALLINT(6) NOT NULL DEFAULT '0',
    `faction` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0',
    `npcflag` INT(10) UNSIGNED NOT NULL DEFAULT '0',
    `speed_walk` FLOAT NOT NULL DEFAULT '1' COMMENT 'Result of 2.5/2.5, most common value',
    `speed_run` FLOAT NOT NULL DEFAULT '1.14286' COMMENT 'Result of 8.0/7.0, most common value',
    `detection_range` FLOAT NOT NULL DEFAULT '20',
    `scale` FLOAT NOT NULL DEFAULT '1',
    `rank` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
    `dmgschool` TINYINT(4) NOT NULL DEFAULT '0',
    `DamageModifier` FLOAT NOT NULL DEFAULT '1',
    `BaseAttackTime` INT(10) UNSIGNED NOT NULL DEFAULT '0',
    `RangeAttackTime` INT(10) UNSIGNED NOT NULL DEFAULT '0',
    `BaseVariance` FLOAT NOT NULL DEFAULT '1',
    `RangeVariance` FLOAT NOT NULL DEFAULT '1',
    `unit_class` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
    `unit_flags` INT(10) UNSIGNED NOT NULL DEFAULT '0',
    `unit_flags2` INT(10) UNSIGNED NOT NULL DEFAULT '0',
    `dynamicflags` INT(10) UNSIGNED NOT NULL DEFAULT '0',
    `family` TINYINT(4) NOT NULL DEFAULT '0',
    `trainer_type` TINYINT(4) NOT NULL DEFAULT '0',
    `trainer_spell` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
    `trainer_class` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
    `trainer_race` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
    `type` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
    `type_flags` INT(10) UNSIGNED NOT NULL DEFAULT '0',
    `lootid` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
    `pickpocketloot` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
    `skinloot` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
    `PetSpellDataId` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
    `VehicleId` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
    `mingold` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
    `maxgold` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
    `AIName` CHAR(64) NOT NULL DEFAULT '' COLLATE 'utf8mb4_general_ci',
    `MovementType` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
    `InhabitType` TINYINT(3) UNSIGNED NOT NULL DEFAULT '3',
    `HoverHeight` FLOAT NOT NULL DEFAULT '1',
    `HealthModifier` FLOAT NOT NULL DEFAULT '1',
    `ManaModifier` FLOAT NOT NULL DEFAULT '1',
    `ArmorModifier` FLOAT NOT NULL DEFAULT '1',
    `ExperienceModifier` FLOAT NOT NULL DEFAULT '1',
    `RacialLeader` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
    `movementId` INT(10) UNSIGNED NOT NULL DEFAULT '0',
    `RegenHealth` TINYINT(3) UNSIGNED NOT NULL DEFAULT '1',
    `mechanic_immune_mask` INT(10) UNSIGNED NOT NULL DEFAULT '0',
    `spell_school_immune_mask` INT(10) UNSIGNED NOT NULL DEFAULT '0',
    `flags_extra` INT(10) UNSIGNED NOT NULL DEFAULT '0',
    `ScriptName` CHAR(64) NOT NULL DEFAULT '' COLLATE 'utf8mb4_general_ci',
    PRIMARY KEY (`entry`, `patch`) USING BTREE
)
COLLATE='utf8mb4_general_ci'
ENGINE=InnoDB
;
