DROP TABLE IF EXISTS `progression_game_event`;
CREATE TABLE `progression_game_event` (
	`eventEntry` TINYINT(3) UNSIGNED NOT NULL COMMENT 'Entry of the game event',
    `min_patch` INT(2) UNSIGNED NOT NULL DEFAULT '0',
    `max_patch` INT(2) UNSIGNED NOT NULL DEFAULT '20',
	PRIMARY KEY (`eventEntry`, `min_patch`, `max_patch`) USING BTREE
)
COLLATE='utf8mb4_general_ci'
ENGINE=InnoDB
;

INSERT INTO `progression_game_event` (`eventEntry`)
SELECT `eventEntry` FROM game_event;

UPDATE `progression_game_event` SET `min_patch`=20;
