-- ============================================
-- Script SQL Server pour modifier la table ordonnance
-- pour permettre plusieurs ordonnances pour le même patient (CIN)
-- ============================================
-- 
-- INSTRUCTIONS:
-- 1. Exécutez ce script dans SQL Server Management Studio
-- 2. Assurez-vous d'avoir une sauvegarde de vos données
-- 3. Exécutez chaque section une par une et vérifiez les résultats

-- ============================================
-- ÉTAPE 1: Vérifier la structure actuelle
-- ============================================
-- Décommentez pour voir la structure:
-- SELECT * FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS WHERE TABLE_NAME = 'ordonnance';
-- SELECT * FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = 'ordonnance';

-- ============================================
-- ÉTAPE 2: Sauvegarder les données existantes
-- ============================================
SELECT * INTO ordonnance_backup FROM ordonnance;

-- ============================================
-- ÉTAPE 3: Supprimer la contrainte de clé primaire sur CIN
-- ============================================
IF EXISTS (SELECT * FROM sys.key_constraints WHERE parent_object_id = OBJECT_ID('ordonnance') AND type = 'PK')
BEGIN
    DECLARE @sql NVARCHAR(MAX);
    SELECT @sql = 'ALTER TABLE ordonnance DROP CONSTRAINT ' + name
    FROM sys.key_constraints 
    WHERE parent_object_id = OBJECT_ID('ordonnance') AND type = 'PK';
    EXEC sp_executesql @sql;
    PRINT 'Contrainte de clé primaire supprimée.';
END
ELSE
BEGIN
    PRINT 'Aucune contrainte de clé primaire trouvée.';
END

-- ============================================
-- ÉTAPE 4: Ajouter la colonne ID auto-incrémentée
-- ============================================
IF NOT EXISTS (SELECT * FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = 'ordonnance' AND COLUMN_NAME = 'ID')
BEGIN
    -- Ajouter la colonne ID au début de la table
    ALTER TABLE ordonnance ADD ID INT IDENTITY(1,1);
    
    -- Définir ID comme nouvelle clé primaire
    ALTER TABLE ordonnance ADD CONSTRAINT PK_ordonnance_ID PRIMARY KEY (ID);
    
    PRINT 'Colonne ID ajoutée avec succès.';
END
ELSE
BEGIN
    PRINT 'La colonne ID existe déjà.';
END

-- ============================================
-- ÉTAPE 5: Vérifier le résultat
-- ============================================
-- Vérifier la structure de la table
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

PRINT 'Modification terminée avec succès!';
PRINT 'Vous pouvez maintenant ajouter plusieurs ordonnances pour le même patient.';

-- ============================================
-- ÉTAPE 6: Nettoyer (optionnel)
-- ============================================
-- Décommentez UNIQUEMENT après avoir vérifié que tout fonctionne:
-- DROP TABLE ordonnance_backup;






