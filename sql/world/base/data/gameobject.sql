-- Meeting Stone (added in patch 1.3)
UPDATE gameobject SET `min_patch`='4297' WHERE `id` IN (
SELECT `entry` FROM `gameobject_template` WHERE `name` = 'Meeting Stone'
);

-- Guild Vault (added in patch 2.3)
UPDATE gameobject SET `min_patch`='7799' WHERE `id` IN (
SELECT `entry` FROM `gameobject_template` WHERE `name` = 'Guild Vault'
);
