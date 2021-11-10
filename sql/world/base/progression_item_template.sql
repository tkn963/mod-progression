DROP TABLE IF EXISTS `progression_item_template`;
CREATE TABLE `progression_item_template` (
    `entry` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
    `patch` INT(2) UNSIGNED NOT NULL DEFAULT '0',
    PRIMARY KEY (`entry`, `patch`) USING BTREE
)
COLLATE='utf8mb4_general_ci'
ENGINE=InnoDB
;
