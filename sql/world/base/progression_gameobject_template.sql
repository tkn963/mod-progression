DROP TABLE IF EXISTS `progression_gameobject_template`;
CREATE TABLE `progression_gameobject_template` (
    `entry` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
    `patch` INT(2) UNSIGNED NOT NULL DEFAULT '0',
    `name` VARCHAR(100) NOT NULL DEFAULT '' COLLATE 'utf8mb4_general_ci',
    PRIMARY KEY (`entry`, `patch`) USING BTREE
)
COLLATE='utf8mb4_general_ci'
ENGINE=InnoDB
;
