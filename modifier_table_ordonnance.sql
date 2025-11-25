-- Script SQL pour modifier la table ordonnance (SQL Server)
-- pour permettre plusieurs ordonnances pour le même patient (CIN)
-- 
-- INSTRUCTIONS:
-- 1. Exécutez ce script dans SQL Server Management Studio ou votre outil SQL
-- 2. Assurez-vous d'avoir une sauvegarde de vos données avant d'exécuter
-- 3. Exécutez chaque section une par une et vérifiez les résultats

-- ============================================
-- ÉTAPE 1: Vérifier la structure actuelle
-- ============================================
-- Décommentez cette ligne pour voir la structure actuelle:
-- SELECT * FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS WHERE TABLE_NAME = 'ordonnance';
-- SELECT * FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = 'ordonnance';

-- ============================================
-- ÉTAPE 2: Sauvegarder les données existantes
-- ============================================
SELECT * INTO ordonnance_backup FROM ordonnance;

-- ============================================
-- ÉTAPE 3: Supprimer les contraintes existantes
-- ============================================
-- Supprimer la contrainte de clé primaire si elle existe sur CIN
IF EXISTS (SELECT * FROM sys.key_constraints WHERE parent_object_id = OBJECT_ID('ordonnance') AND type = 'PK')
BEGIN
    DECLARE @sql NVARCHAR(MAX);
    SELECT @sql = 'ALTER TABLE ordonnance DROP CONSTRAINT ' + name
    FROM sys.key_constraints 
    WHERE parent_object_id = OBJECT_ID('ordonnance') AND type = 'PK';
    EXEC sp_executesql @sql;
END

-- ============================================
-- ÉTAPE 4: Ajouter la colonne ID auto-incrémentée
-- ============================================
-- Vérifier si la colonne ID existe déjà
IF NOT EXISTS (SELECT * FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = 'ordonnance' AND COLUMN_NAME = 'ID')
BEGIN
    -- Ajouter la colonne ID au début de la table
    ALTER TABLE ordonnance ADD ID INT IDENTITY(1,1);
    
    -- Définir ID comme clé primaire
    ALTER TABLE ordonnance ADD CONSTRAINT PK_ordonnance_ID PRIMARY KEY (ID);
END

-- ============================================
-- ÉTAPE 5: Vérifier le résultat
-- ============================================
-- Vérifier que tout s'est bien passé
SELECT 
    COLUMN_NAME, 
    DATA_TYPE, 
    IS_NULLABLE,
    COLUMNPROPERTY(OBJECT_ID('ordonnance'), COLUMN_NAME, 'IsIdentity') AS IS_IDENTITY
FROM INFORMATION_SCHEMA.COLUMNS 
WHERE TABLE_NAME = 'ordonnance'
ORDER BY ORDINAL_POSITION;

-- Vérifier les contraintes
SELECT 
    CONSTRAINT_NAME, 
    CONSTRAINT_TYPE
FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS 
WHERE TABLE_NAME = 'ordonnance';

-- Afficher quelques données pour vérifier
SELECT TOP 5 * FROM ordonnance;

-- ============================================
-- ÉTAPE 6: Nettoyer (optionnel - supprimer la sauvegarde après vérification)
-- ============================================
-- Décommentez cette ligne UNIQUEMENT après avoir vérifié que tout fonctionne:
-- DROP TABLE ordonnance_backup;

-- OU si vous utilisez MySQL/MariaDB:
/*
ALTER TABLE ordonnance 
DROP PRIMARY KEY,
ADD COLUMN ID INT AUTO_INCREMENT PRIMARY KEY FIRST;
*/

-- OU si vous utilisez SQLite:
/*
-- Sauvegarder les données
CREATE TABLE ordonnance_backup AS SELECT * FROM ordonnance;

-- Supprimer l'ancienne table
DROP TABLE ordonnance;

-- Créer la nouvelle table avec ID auto-incrémenté
CREATE TABLE ordonnance (
    ID INTEGER PRIMARY KEY AUTOINCREMENT,
    CIN TEXT NOT NULL,
    NOM TEXT NOT NULL,
    PRENOM TEXT NOT NULL,
    MEDECIN TEXT NOT NULL,
    DATE_ORD DATE NOT NULL
);

-- Restaurer les données
INSERT INTO ordonnance (CIN, NOM, PRENOM, MEDECIN, DATE_ORD)
SELECT CIN, NOM, PRENOM, MEDECIN, DATE_ORD FROM ordonnance_backup;

-- Supprimer la table de sauvegarde
DROP TABLE ordonnance_backup;
*/

