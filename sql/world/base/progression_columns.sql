DROP PROCEDURE IF EXISTS `AddProgressionColumn`;

DELIMITER $$

CREATE PROCEDURE `AddProgressionColumn` (
    `@TABLE` VARCHAR(100),
    `@COLUMN` VARCHAR(100),
    `@TYPE` VARCHAR(100),
    `@DEFAULT` VARCHAR(100),
    `@AFTER` VARCHAR(100))

`AddProgressionColumn` : BEGIN
    DECLARE `@EXISTS` INT UNSIGNED DEFAULT 0;

    SELECT COUNT(*) INTO `@EXISTS` 
    FROM `information_schema`.`COLUMNS` WHERE 
    `TABLE_SCHEMA` = DATABASE() AND 
    `TABLE_NAME` = `@TABLE` AND 
    `COLUMN_NAME` = `@COLUMN`;

    IF (`@EXISTS` < 1) THEN
        SET @SQL = CONCAT(
            'ALTER TABLE `', 
            `@TABLE`, 
            '` ADD COLUMN `',
            `@COLUMN`,
            '` ',
            `@TYPE`, 
            ' NOT NULL DEFAULT ',
            `@DEFAULT`,
            ' AFTER `',
            `@AFTER`,
            '`;'
        );

        PREPARE query FROM @SQL;
        EXECUTE query;
    END IF;
END $$

DELIMITER ;


-- The choice of min/max is only because I'm unsure if it only needs patch or min/max.
-- It's very easy to change.
CALL AddProgressionColumn('conditions', 'min_patch', 'INT', '4125', 'SourceTypeOrReferenceId');
CALL AddProgressionColumn('conditions', 'max_patch', 'INT', '12340', 'min_patch');
ALTER TABLE `conditions`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `min_patch`, `max_patch`) USING BTREE;

-- Certain creatures will be added in patches, and some removed in patches.
-- Having min/max here is a must.
-- A rough example is Lord Kazzak in Blasted Lands. He was added in patch 1.3 and removed in 2.0, which is when he moved to Hellfire Peninsula and turned into Doom Lord Kazzak (afaik).
CALL AddProgressionColumn('creature', 'min_patch', 'INT', '4125', 'id');
CALL AddProgressionColumn('creature', 'max_patch', 'INT', '12340', 'min_patch');
ALTER TABLE `creature`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`guid`, `min_patch`, `max_patch`) USING BTREE;

-- This is to support any missing entries from the creature table.
CALL AddProgressionColumn('creature_addon', 'patch', 'INT', '4125', 'guid');
ALTER TABLE `creature_addon`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`guid`, `patch`) USING BTREE;

-- The column I've chosen for loot templates are just for testing purposes.
-- It could just as well be just min/max, patch or even non-existant depending on the type of loot template.
CALL AddProgressionColumn('creature_loot_template', 'patch', 'INT', '4125', 'Item');
ALTER TABLE `creature_loot_template`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`Entry`, `Item`, `patch`) USING BTREE;

-- Creatures will change over time. This column helps with that.
CALL AddProgressionColumn('creature_template', 'patch', 'INT', '4125', 'entry');
ALTER TABLE `creature_template`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`entry`, `patch`) USING BTREE;

-- Certain features, like instances or battlegrounds, will be disabled at a certain point but enabled again later on.
CALL AddProgressionColumn('disables', 'min_patch', 'INT', '4125', 'entry');
CALL AddProgressionColumn('disables', 'max_patch', 'INT', '12340', 'min_patch');
ALTER TABLE `disables`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`sourceType`, `entry`, `min_patch`, `max_patch`) USING BTREE;

-- The column I've chosen for loot templates are just for testing purposes.
-- It could just as well be just min/max, patch or even non-existant depending on the type of loot template.
CALL AddProgressionColumn('disenchant_loot_template', 'patch', 'INT', '4125', 'Item');
ALTER TABLE `disenchant_loot_template`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`Entry`, `Item`, `patch`) USING BTREE;

-- The column I've chosen for loot templates are just for testing purposes.
-- It could just as well be just min/max, patch or even non-existant depending on the type of loot template.
CALL AddProgressionColumn('fishing_loot_template', 'patch', 'INT', '4125', 'Item');
ALTER TABLE `fishing_loot_template`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`Entry`, `Item`, `patch`) USING BTREE;

-- Certain creatures will be added in patches, and some removed in patches.
-- Having min/max here is a must.
-- I can't give a specific example at this time, but I know it's needed.
CALL AddProgressionColumn('gameobject', 'min_patch', 'INT', '4125', 'id');
CALL AddProgressionColumn('gameobject', 'max_patch', 'INT', '12340', 'min_patch');
ALTER TABLE `gameobject`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`guid`, `min_patch`, `max_patch`) USING BTREE;

-- This is to support any missing entries from the gameobject table.
CALL AddProgressionColumn('gameobject_addon', 'patch', 'INT', '4125', 'guid');
ALTER TABLE `gameobject_addon`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`guid`, `patch`) USING BTREE;

-- The column I've chosen for loot templates are just for testing purposes.
-- It could just as well be just min/max, patch or even non-existant depending on the type of loot template.
CALL AddProgressionColumn('gameobject_loot_template', 'patch', 'INT', '4125', 'Item');
ALTER TABLE `gameobject_loot_template`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`Entry`, `Item`, `patch`) USING BTREE;

-- Game objects will change over time. This column helps with that.
CALL AddProgressionColumn('gameobject_template', 'patch', 'INT', '4125', 'entry');
ALTER TABLE `gameobject_template`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`entry`, `patch`) USING BTREE;

-- The column I've chosen for loot templates are just for testing purposes.
-- It could just as well be just min/max, patch or even non-existant depending on the type of loot template.
CALL AddProgressionColumn('item_loot_template', 'patch', 'INT', '4125', 'Item');
ALTER TABLE `item_loot_template`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`Entry`, `Item`, `patch`) USING BTREE;

-- Many items change over the course of the game.. so many.
CALL AddProgressionColumn('item_template', 'patch', 'INT', '4125', 'entry');
ALTER TABLE `item_template`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`entry`, `patch`) USING BTREE;

-- This is merely to help with errors when starting the server without entries from the creature table active.
-- I really don't know how to handle this...
CALL AddProgressionColumn('linked_respawn', 'patch', 'INT', '4125', 'linkType');
ALTER TABLE `linked_respawn`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`guid`, `linkType`, `patch`) USING BTREE;

-- The column I've chosen for loot templates are just for testing purposes.
-- It could just as well be just min/max, patch or even non-existant depending on the type of loot template.
CALL AddProgressionColumn('mail_loot_template', 'patch', 'INT', '4125', 'Item');
ALTER TABLE `mail_loot_template`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`Entry`, `Item`, `patch`) USING BTREE;

-- The column I've chosen for loot templates are just for testing purposes.
-- It could just as well be just min/max, patch or even non-existant depending on the type of loot template.
CALL AddProgressionColumn('milling_loot_template', 'patch', 'INT', '4125', 'Item');
ALTER TABLE `milling_loot_template`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`Entry`, `Item`, `patch`) USING BTREE;

-- Spells get added, removed or changed over the course of the game.
-- A rough example are the riding spells. Their required level and cost changed with every expansion, more or less.
CALL AddProgressionColumn('npc_trainer', 'min_patch', 'INT', '4125', 'ID');
CALL AddProgressionColumn('npc_trainer', 'max_patch', 'INT', '12340', 'min_patch');
ALTER TABLE `npc_trainer`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`ID`, `SpellID`, `min_patch`, `max_patch`) USING BTREE;

-- Items were added and removed from various vendors at many points in time.
CALL AddProgressionColumn('npc_vendor', 'min_patch', 'INT', '4125', 'entry');
CALL AddProgressionColumn('npc_vendor', 'max_patch', 'INT', '12340', 'min_patch');
ALTER TABLE `npc_vendor`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`entry`, `item`, `ExtendedCost`, `min_patch`, `max_patch`) USING BTREE;

-- The column I've chosen for loot templates are just for testing purposes.
-- It could just as well be just min/max, patch or even non-existant depending on the type of loot template.
CALL AddProgressionColumn('pickpocketing_loot_template', 'patch', 'INT', '4125', 'Item');
ALTER TABLE `pickpocketing_loot_template`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`Entry`, `Item`, `patch`) USING BTREE;

-- The column I've chosen for loot templates are just for testing purposes.
-- It could just as well be just min/max, patch or even non-existant depending on the type of loot template.
CALL AddProgressionColumn('player_loot_template', 'patch', 'INT', '4125', 'Item');
ALTER TABLE `player_loot_template`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`Entry`, `Item`, `patch`) USING BTREE;

-- This is mainly to handle errors when starting without certain creatures enabled.
-- I am honestly not sure how to properly handle this.
CALL AddProgressionColumn('pool_template', 'min_patch', 'INT', '4125', 'entry');
CALL AddProgressionColumn('pool_template', 'max_patch', 'INT', '12340', 'min_patch');
ALTER TABLE `pool_template`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`entry`, `min_patch`, `max_patch`) USING BTREE;

-- The column I've chosen for loot templates are just for testing purposes.
-- It could just as well be just min/max, patch or even non-existant depending on the type of loot template.
CALL AddProgressionColumn('prospecting_loot_template', 'patch', 'INT', '4125', 'Item');
ALTER TABLE `prospecting_loot_template`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`Entry`, `Item`, `patch`) USING BTREE;

-- Quests change over time, in many ways.
CALL AddProgressionColumn('quest_template', 'patch', 'INT', '4125', 'ID');
ALTER TABLE `quest_template`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`ID`, `patch`) USING BTREE;

-- The column I've chosen for loot templates are just for testing purposes.
-- It could just as well be just min/max, patch or even non-existant depending on the type of loot template.
CALL AddProgressionColumn('reference_loot_template', 'patch', 'INT', '4125', 'Item');
ALTER TABLE `reference_loot_template`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`Entry`, `Item`, `patch`) USING BTREE;

-- The column I've chosen for loot templates are just for testing purposes.
-- It could just as well be just min/max, patch or even non-existant depending on the type of loot template.
CALL AddProgressionColumn('skinning_loot_template', 'patch', 'INT', '4125', 'Item');
ALTER TABLE `skinning_loot_template`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`Entry`, `Item`, `patch`) USING BTREE;

-- The column I've chosen for loot templates are just for testing purposes.
-- It could just as well be just min/max, patch or even non-existant depending on the type of loot template.
CALL AddProgressionColumn('spell_loot_template', 'patch', 'INT', '4125', 'Item');
ALTER TABLE `spell_loot_template`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`Entry`, `Item`, `patch`) USING BTREE;

-- Different transports are added in various patches.
-- For example, the transport to and from northrend shouldn't be active before then.
CALL AddProgressionColumn('transports', 'patch', 'INT', '4125', 'entry');
ALTER TABLE `transports`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`guid`, `patch`) USING BTREE;

DROP PROCEDURE IF EXISTS `AddProgressionColumn`;

/*
To test for errors, run this after creating all columns

UPDATE `conditions` SET `min_patch`=12340, `max_patch`=12340;
UPDATE `creature` SET `min_patch`=12340, `max_patch`=12340;
UPDATE `creature` SET `min_patch`=4125 WHERE `guid`=36625;
UPDATE `gameobject` SET `min_patch`=12340, `max_patch`=12340;
UPDATE `gameobject` SET `min_patch`=4125 WHERE `guid` IN (6781, 9263, 16735, 16736, 16737, 16738, 16740, 16741, 16742, 16743, 16969, 16970, 16971, 16972, 16973, 21607, 21611, 27142, 28288, 45612, 46424, 46425, 46429, 50455, 50456, 50457, 50459, 50460, 50461, 50462, 50463, 50464, 50465, 50466, 50467, 50468, 50469, 50470, 50471, 50472, 57571, 99774, 99775, 99776, 99777, 99778, 99779, 99780, 99781, 99782, 99783, 99784, 99896);
UPDATE `linked_respawn` SET `patch`=12340;
UPDATE `npc_trainer` SET `min_patch`=12340, `max_patch`=12340;
UPDATE `npc_vendor` SET `min_patch`=12340, `max_patch`=12340;
UPDATE `pool_template` SET `min_patch`=12340, `max_patch`=12340;
UPDATE `transports` SET `patch`=12340;
*/
