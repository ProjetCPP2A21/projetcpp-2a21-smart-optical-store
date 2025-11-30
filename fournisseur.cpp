#include "fournisseur.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QRegularExpression>

Fournisseur::Fournisseur() {}

Fournisseur::Fournisseur(QString ID_FOURNISSEUR, QString NOM, QString ADRESSE, QString EMAIL, QString NUMERO_TELEPHONE, QString CONDITION_PAIEMENT)
{
    this->ID_FOURNISSEUR = ID_FOURNISSEUR;
    this->NOM = NOM;
    this->ADRESSE = ADRESSE;
    this->EMAIL = EMAIL;
    this->NUMERO_TELEPHONE = NUMERO_TELEPHONE;
    this->CONDITION_PAIEMENT = CONDITION_PAIEMENT;
}

// ==================== AJOUTER ====================

bool Fournisseur::ajouter()
{
    QSqlQuery query;

    query.prepare("INSERT INTO FOURNISSEUR (ID_FOURNISSEUR, NOM, ADRESSE, EMAIL, NUMERO_TELEPHONE, CONDITION_PAIEMENT) "
                  "VALUES (:ID_FOURNISSEUR, :NOM, :ADRESSE, :EMAIL, :NUMERO_TELEPHONE, :CONDITION_PAIEMENT)");

    query.bindValue(":ID_FOURNISSEUR", ID_FOURNISSEUR);
    query.bindValue(":NOM", NOM);
    query.bindValue(":ADRESSE", ADRESSE);
    query.bindValue(":EMAIL", EMAIL);
    query.bindValue(":NUMERO_TELEPHONE", NUMERO_TELEPHONE);
    query.bindValue(":CONDITION_PAIEMENT", CONDITION_PAIEMENT);

    if (query.exec()) {
        qDebug() << "✅ Fournisseur ajouté avec succès!";
        return true;
    } else {
        qDebug() << "❌ Erreur lors de l'ajout:" << query.lastError().text();
        return false;
    }
}

// ==================== MODIFIER ====================

bool Fournisseur::modifier(QString ID_FOURNISSEUR, QString NOM, QString ADRESSE, QString EMAIL, QString NUMERO_TELEPHONE, QString CONDITION_PAIEMENT)
{
    QSqlQuery query;

    query.prepare("UPDATE FOURNISSEUR SET "
                  "NOM = :NOM, "
                  "ADRESSE = :ADRESSE, "
                  "EMAIL = :EMAIL, "
                  "NUMERO_TELEPHONE = :NUMERO_TELEPHONE, "
                  "CONDITION_PAIEMENT = :CONDITION_PAIEMENT "
                  "WHERE ID_FOURNISSEUR = :ID_FOURNISSEUR");

    query.bindValue(":ID_FOURNISSEUR", ID_FOURNISSEUR);
    query.bindValue(":NOM", NOM);
    query.bindValue(":ADRESSE", ADRESSE);
    query.bindValue(":EMAIL", EMAIL);
    query.bindValue(":NUMERO_TELEPHONE", NUMERO_TELEPHONE);
    query.bindValue(":CONDITION_PAIEMENT", CONDITION_PAIEMENT);

    if (query.exec()) {
        qDebug() << "✅ Fournisseur avec ID_FOURNISSEUR" << ID_FOURNISSEUR << "modifié avec succès!";
        return true;
    } else {
        qDebug() << "❌ Erreur lors de la modification:" << query.lastError().text();
        return false;
    }
}

// ==================== AFFICHER ====================

void Fournisseur::afficher(QTableWidget *tableWidget)
{
    qDebug() << "=== DÉBUT DE AFFICHER() ===";

    if (!tableWidget) {
        qDebug() << "❌ ERREUR: tableWidget est null!";
        return;
    }

    // Vider le tableau existant
    tableWidget->setRowCount(0);

    // Définir les en-têtes de colonnes
    QStringList headers;
    headers << "ID_FOURNISSEUR" << "NOM" << "ADRESSE" << "EMAIL" << "NUMERO_TELEPHONE" << "CONDITION_PAIEMENT";
    tableWidget->setColumnCount(6);
    tableWidget->setHorizontalHeaderLabels(headers);

    // Exécuter la requête SQL
    QSqlQuery query;
    if (!query.exec("SELECT * FROM FOURNISSEUR")) {
        qDebug() << "❌ Erreur requête:" << query.lastError().text();
        return;
    }

    int row = 0;
    while (query.next()) {
        tableWidget->insertRow(row);

        // Remplir chaque colonne
        for (int col = 0; col < 6; col++) {
            tableWidget->setItem(row, col, new QTableWidgetItem(query.value(col).toString()));
        }
        row++;
    }

    // Ajuster la largeur des colonnes
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

// ==================== SUPPRIMER ====================

bool Fournisseur::supprimer(QString ID_FOURNISSEUR)
{
    QSqlQuery query;

    query.prepare("DELETE FROM FOURNISSEUR WHERE ID_FOURNISSEUR = :ID_FOURNISSEUR");
    query.bindValue(":ID_FOURNISSEUR", ID_FOURNISSEUR);

    if (query.exec()) {
        qDebug() << "✅ Fournisseur avec ID_FOURNISSEUR" << ID_FOURNISSEUR << "supprimé avec succès!";
        return true;
    } else {
        qDebug() << "❌ Erreur lors de la suppression:" << query.lastError().text();
        return false;
    }
}

// ==================== VALIDATION ====================

bool Fournisseur::validerNom(const QString &nom)
{
    if (nom.isEmpty()) return true;

    QRegularExpression regex("^[a-zA-ZÀ-ÿœŒ\\s\\-\\&]{2,50}$");
    return regex.match(nom).hasMatch();
}

bool Fournisseur::validerEmail(const QString &email)
{
    if (email.isEmpty()) return true;

    QRegularExpression regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    return regex.match(email).hasMatch();
}

bool Fournisseur::validerTelephone(const QString &telephone)
{
    if (telephone.isEmpty()) return true;

    QRegularExpression regex("^[0-9]{8}$");
    return regex.match(telephone).hasMatch();
}

bool Fournisseur::validerAdresse(const QString &adresse)
{
    if (adresse.isEmpty()) return true;

    return adresse.length() >= 5 && adresse.length() <= 100;
}

bool Fournisseur::validerConditionPaiement(const QString &condition)
{
    if (condition.isEmpty()) return true;

    QStringList conditionsValides = {"payé", "30 jours", "60 jours", "comptant", "avance", "autre"};
    return conditionsValides.contains(condition.toLower());
}

bool Fournisseur::validerId(const QString &id)
{
    return !id.isEmpty() && id.length() <= 50;
}

// ==================== RECHERCHE ====================

bool Fournisseur::rechercherParId(QString ID_FOURNISSEUR, QTableWidget *tableWidget)
{
    if (!tableWidget) {
        qDebug() << "❌ ERREUR: tableWidget est null!";
        return false;
    }

    // Vider le tableau actuel
    tableWidget->setRowCount(0);

    QSqlQuery query;
    query.prepare("SELECT * FROM FOURNISSEUR WHERE ID_FOURNISSEUR = :id");
    query.bindValue(":id", ID_FOURNISSEUR);

    if (query.exec() && query.next()) {
        // Ajouter UNIQUEMENT la ligne trouvée au tableau
        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);

        // Remplir chaque colonne
        for (int col = 0; col < 6; col++) {
            tableWidget->setItem(row, col, new QTableWidgetItem(query.value(col).toString()));
        }
        return true;
    }
    return false;
}

// ==================== TRI NUMÉRIQUE ====================

void Fournisseur::trierParIdNumerique(QTableWidget *tableWidget, bool ordreCroissant)
{
    if (!tableWidget || tableWidget->rowCount() == 0) return;

    // Créer une liste de paires (valeur numérique, ligne)
    QList<QPair<int, int>> lignesAvecId;

    // Récupérer toutes les lignes avec leur ID converti en nombre
    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        QTableWidgetItem *item = tableWidget->item(row, 0); // Colonne ID
        if (item && !item->text().isEmpty()) {
            bool ok;
            int idNumerique = item->text().toInt(&ok);
            if (ok) {
                lignesAvecId.append(QPair<int, int>(idNumerique, row));
            } else {
                // Si conversion échoue, mettre -1 pour les mettre en premier
                lignesAvecId.append(QPair<int, int>(-1, row));
            }
        }
    }

    // Trier la liste par ID numérique (toujours croissant)
    std::sort(lignesAvecId.begin(), lignesAvecId.end(),
              [](const QPair<int, int> &a, const QPair<int, int> &b) {
                  return a.first < b.first;
              });

    // Créer un nouveau tableau trié
    QTableWidget *tableauTrie = new QTableWidget();
    tableauTrie->setColumnCount(tableWidget->columnCount());
    tableauTrie->setHorizontalHeaderLabels(QStringList()
                                           << "ID_FOURNISSEUR" << "NOM" << "ADRESSE" << "EMAIL" << "NUMERO_TELEPHONE" << "CONDITION_PAIEMENT");

    // Copier les lignes dans l'ordre trié
    for (const auto &paire : lignesAvecId) {
        int nouvelleLigne = tableauTrie->rowCount();
        tableauTrie->insertRow(nouvelleLigne);

        for (int col = 0; col < tableWidget->columnCount(); ++col) {
            QTableWidgetItem *itemOriginal = tableWidget->item(paire.second, col);
            if (itemOriginal) {
                tableauTrie->setItem(nouvelleLigne, col, new QTableWidgetItem(itemOriginal->text()));
            }
        }
    }

    // Remplacer l'ancien tableau par le nouveau trié
    tableWidget->setRowCount(0);
    for (int row = 0; row < tableauTrie->rowCount(); ++row) {
        tableWidget->insertRow(row);
        for (int col = 0; col < tableauTrie->columnCount(); ++col) {
            QTableWidgetItem *item = tableauTrie->item(row, col);
            if (item) {
                tableWidget->setItem(row, col, new QTableWidgetItem(item->text()));
            }
        }
    }

    delete tableauTrie;
}

// ==================== STATISTIQUES ====================

QMap<QString, int> Fournisseur::getStatistiquesParConditionPaiement()
{
    QMap<QString, int> stats;
    QSqlQuery query;

    if (query.exec("SELECT CONDITION_PAIEMENT, COUNT(*) FROM FOURNISSEUR GROUP BY CONDITION_PAIEMENT")) {
        while (query.next()) {
            QString condition = query.value(0).toString();
            int count = query.value(1).toInt();
            stats[condition.isEmpty() ? "Non spécifié" : condition] = count;
        }
    }

    return stats;
}
// ==================== CARTE DES FOURNISSEURS ====================

QList<QVariantMap> Fournisseur::getAllFournisseursForMap()
{
    QList<QVariantMap> fournisseursData;

    QSqlQuery query("SELECT NOM, EMAIL, NUMERO_TELEPHONE, ADRESSE FROM FOURNISSEUR");

    qDebug() << "=== DÉBUT GÉOCODAGE INTELLIGENT FOURNISSEURS ===";

    QMap<QString, QList<QPair<double, double>>> positionsVilles = {
        {"tunis", {{36.8008,10.1800},{36.8380,10.2400},{36.8065,10.1815},{36.7960,10.1760},{36.8500,10.2000},{36.8200,10.1500},{36.7800,10.2200},{36.8300,10.1650},{36.8100,10.0950}}},
        {"sfax",  {{34.7400,10.7600},{34.7500,10.7700},{34.7300,10.7500},{34.7200,10.7800},{34.7350,10.7550}}},
        {"sousse",{{35.8254,10.6360},{35.8300,10.6250},{35.8200,10.6400},{35.8150,10.6300},{35.8270,10.5920}}},
        {"nabeul",{{36.4561,10.7376},{36.4600,10.7300},{36.4500,10.7400},{36.4400,10.7500},{36.4550,10.7250}}},
        {"bizerte",{{37.2747,9.8739},{37.2800,9.8700},{37.2700,9.8800},{37.2650,9.8650}}},
        {"gabès", {{33.8815,10.0982},{33.8900,10.1000},{33.8700,10.1100},{33.8800,10.0850}}},
        {"kairouan",{{35.6781,10.0964},{35.6800,10.0900},{35.6700,10.1050},{35.6750,10.0850}}},
        {"gafsa", {{34.4250,8.7842},{34.4300,8.7800},{34.4200,8.7900},{34.4150,8.7750}}}
    };

    QMap<QString, int> compteurPositions;

    // Utility lambda to detect full words
    auto containsWord = [&](const QString &text, const QString &word) {
        QRegularExpression rx("\\b" + QRegularExpression::escape(word) + "\\b",
                              QRegularExpression::CaseInsensitiveOption);
        return text.contains(rx);
    };

    while (query.next()) {
        QVariantMap fournisseur;

        fournisseur["nom"] = query.value("NOM").toString();
        fournisseur["email"] = query.value("EMAIL").toString();
        fournisseur["telephone"] = query.value("NUMERO_TELEPHONE").toString();
        QString adresse = query.value("ADRESSE").toString();
        fournisseur["adresse"] = adresse;

        QString adresseLower = adresse.toLower();
        QString villeDetectee = "";

        // Correct full-word detection
        if (containsWord(adresseLower, "sfax")   || adresseLower.contains("صفاقس"))
            villeDetectee = "sfax";
        else if (containsWord(adresseLower, "sousse") || adresseLower.contains("سوسة"))
            villeDetectee = "sousse";
        else if (containsWord(adresseLower, "nabeul") || adresseLower.contains("نابل"))
            villeDetectee = "nabeul";
        else if (containsWord(adresseLower, "bizerte") || adresseLower.contains("بنزرت"))
            villeDetectee = "bizerte";
        else if (containsWord(adresseLower, "gabes") || containsWord(adresseLower, "gabès") || adresseLower.contains("قابس"))
            villeDetectee = "gabès";
        else if (containsWord(adresseLower, "kairouan") || adresseLower.contains("القيروان"))
            villeDetectee = "kairouan";
        else if (containsWord(adresseLower, "gafsa") || adresseLower.contains("قفصة"))
            villeDetectee = "gafsa";
        else if (containsWord(adresseLower, "tunis") || adresseLower.contains("تونس"))
            villeDetectee = "tunis";

        // ❌ If no valid city → ignore this supplier
        if (villeDetectee.isEmpty() || !positionsVilles.contains(villeDetectee)) {
            qDebug() << "⚠️ Fournisseur ignoré (ville inconnue) :" << fournisseur["nom"].toString()
                << "- Adresse:" << adresse;
            continue;
        }

        // Assign coordinates
        QList<QPair<double, double>> positions = positionsVilles[villeDetectee];
        int posIdx = compteurPositions[villeDetectee] % positions.size();

        fournisseur["latitude"] = positions[posIdx].first;
        fournisseur["longitude"] = positions[posIdx].second;
        fournisseur["ville"] = villeDetectee;

        compteurPositions[villeDetectee]++;

        qDebug() << "📍" << fournisseur["nom"].toString()
                 << "→" << villeDetectee << "(" << posIdx << ")";
        fournisseursData.append(fournisseur);
    }

    qDebug() << "=== FIN GÉOCODAGE ===";
    qDebug() << fournisseursData.length() << "fournisseurs valides";

    return fournisseursData;
}
