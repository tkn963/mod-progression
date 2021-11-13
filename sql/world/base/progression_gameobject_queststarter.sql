DROP TABLE IF EXISTS `progression_gameobject_queststarter`;
CREATE TABLE `progression_gameobject_queststarter` (
    `id` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Identifier',
    `quest` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Quest Identifier',
    `min_patch` INT(2) UNSIGNED NOT NULL DEFAULT '0',
    `max_patch` INT(2) UNSIGNED NOT NULL DEFAULT '20',
    PRIMARY KEY (`id`, `quest`, `min_patch`, `max_patch`) USING BTREE
)
COLLATE='utf8mb4_general_ci'
ENGINE=InnoDB
;
