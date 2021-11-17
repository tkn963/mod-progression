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

CALL AddProgressionColumn('creature', 'min_patch', 'INT', '4125', 'id');
CALL AddProgressionColumn('creature', 'max_patch', 'INT', '12340', 'min_patch');
ALTER TABLE `creature`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`guid`, `min_patch`, `max_patch`) USING BTREE;

CALL AddProgressionColumn('creature_addon', 'patch', 'INT', '4125', 'guid');
ALTER TABLE `creature_addon`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`guid`, `patch`) USING BTREE;

CALL AddProgressionColumn('creature_template', 'patch', 'INT', '4125', 'entry');
ALTER TABLE `creature_template`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`entry`, `patch`) USING BTREE;

CALL AddProgressionColumn('disables', 'min_patch', 'INT', '4125', 'entry');
CALL AddProgressionColumn('disables', 'max_patch', 'INT', '12340', 'min_patch');
ALTER TABLE `disables`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`sourceType`, `entry`, `min_patch`, `max_patch`) USING BTREE;

CALL AddProgressionColumn('gameobject', 'min_patch', 'INT', '4125', 'id');
CALL AddProgressionColumn('gameobject', 'max_patch', 'INT', '12340', 'min_patch');
ALTER TABLE `gameobject`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`guid`, `min_patch`, `max_patch`) USING BTREE;

CALL AddProgressionColumn('gameobject_addon', 'patch', 'INT', '4125', 'guid');
ALTER TABLE `gameobject_addon`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`guid`, `patch`) USING BTREE;

CALL AddProgressionColumn('gameobject_template', 'patch', 'INT', '4125', 'entry');
ALTER TABLE `gameobject_template`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`entry`, `patch`) USING BTREE;

CALL AddProgressionColumn('quest_template', 'patch', 'INT', '4125', 'ID');
ALTER TABLE `quest_template`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`ID`, `patch`) USING BTREE;

CALL AddProgressionColumn('transports', 'patch', 'INT', '4125', 'entry');
ALTER TABLE `transports`
	DROP PRIMARY KEY,
	ADD PRIMARY KEY (`guid`, `patch`) USING BTREE;

DROP PROCEDURE IF EXISTS `AddProgressionColumn`;
