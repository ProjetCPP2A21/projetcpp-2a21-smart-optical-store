#include "chatbot.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QRegularExpression>
#include <QMessageBox>
#include <QDate>
#include <QTime>
#include <QDateTime>

Chatbot::Chatbot()
{
}

Chatbot::IntentType Chatbot::analyserIntention(const QString &message)
{
    QString msg = message.toLower().simplified();
    
    bool mentionPatients = msg.contains("patient");
    bool mentionMedecin = msg.contains("médecin") || msg.contains("medecin") ||
                          msg.contains("docteur") || msg.contains("dr") || msg.contains("dr.");
    bool patientsDuMedecin = msg.contains("patients du") || msg.contains("patients de") || msg.contains("patients d'") ||
                             msg.contains("patient du") || msg.contains("patient de") || msg.contains("patient d'");
    bool mentionOrdonnance = msg.contains("ordonnance");

    // PRIORITÉ 1: Statistiques - Vérifier EN PREMIER si c'est une question de statistiques
    // Cela évite que "mois", "aujourd'hui" soient détectés comme RECHERCHE_DATE
    if (msg.contains("combien") || msg.contains("nombre") || msg.contains("statistique") ||
        msg.contains("total") || msg.contains("stat")) {
        // PRIORITÉ: "aujourd'hui", "hier", "ce mois", "cette semaine" -> STATISTIQUE_NOMBRE
        if (msg.contains("aujourd'hui") || msg.contains("hier") || msg.contains("ce mois") || 
            msg.contains("cette semaine") || msg.contains("semaine") || msg.contains("mois") || 
            msg.contains("jour")) {
            return STATISTIQUE_NOMBRE;
        }
        // Si mention d'une date spécifique (format dd/MM/yyyy) -> STATISTIQUE_DATE
        if (msg.contains("date") || QRegularExpression("\\d{1,2}/\\d{1,2}/\\d{4}").match(msg).hasMatch()) {
            return STATISTIQUE_DATE;
        }
        if (msg.contains("médecin") || msg.contains("docteur")) {
            return STATISTIQUE_MEDECIN;
        }
        return STATISTIQUE_NOMBRE;
    }

    // PRIORITÉ 2: Recherche par date - Seulement si ce n'est PAS une statistique
    // Détecter les formats de date : dd/MM/yyyy, dd-MM-yyyy, yyyy-MM-dd
    QRegularExpression dateRegex("\\b(\\d{1,2}[/-]\\d{1,2}[/-]\\d{4}|\\d{4}[/-]\\d{2}[/-]\\d{2})\\b");
    bool contientDate = dateRegex.match(message).hasMatch();
    
    if (contientDate || (msg.contains("date") && !msg.contains("combien") && !msg.contains("nombre"))) {
        return RECHERCHE_DATE;
    }

    // Recherche par médecin
    if (mentionMedecin || patientsDuMedecin) {
        return RECHERCHE_MEDECIN;
    }
    
    // Recherche par patient (seulement si pas de date détectée)
    if (mentionPatients || mentionOrdonnance || msg.contains("montre") || msg.contains("affiche") ||
        msg.contains("trouve") || msg.contains("cherche")) {
        if (mentionMedecin || patientsDuMedecin) {
            return RECHERCHE_MEDECIN;
        }
        return RECHERCHE_PATIENT;
    }
    
    // Alertes d'anomalies
    if (msg.contains("anomalie") || msg.contains("erreur") || msg.contains("problème") ||
        msg.contains("doublon") || msg.contains("invalide")) {
        return ALERTE_ANOMALIES;
    }
    
    // Rapport d'activité
    if (msg.contains("rapport") || msg.contains("activité") || msg.contains("activite") ||
        msg.contains("résumé") || msg.contains("resume")) {
        return RAPPORT_ACTIVITE;
    }
    
    // Aide
    if (msg.contains("aide") || msg.contains("help") || msg.contains("comment") ||
        msg.contains("que puis") || msg.contains("que peux")) {
        return AIDE;
    }
    
    return INCONNU;
}

QString Chatbot::extraireParametre(const QString &message, const QString &motCle)
{
    QRegularExpression regex(QString("(?:%1|du|de|le|la|les)\\s+([^\\s]+(?:\\s+[^\\s]+)*)").arg(motCle),
                            QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch match = regex.match(message);
    if (match.hasMatch()) {
        return match.captured(1).trimmed();
    }
    return "";
}

QString Chatbot::traiterMessage(const QString &message, QTableWidget *tableWidget)
{
    IntentType intention = analyserIntention(message);
    
    switch (intention) {
        case RECHERCHE_MEDECIN: {
            QString medecin = "";
            
            // PRIORITÉ 1: Extraire le nom après "Dr." ou "Dr " (avec ou sans point)
            // Exemples: "Dr. X", "Dr X", "docteur X", "médecin X"
            QRegularExpression regexDr("\\b(?:dr\\.?|docteur|médecin|medecin)\\s+([\\w]+)",
                                      QRegularExpression::CaseInsensitiveOption);
            QRegularExpressionMatch matchDr = regexDr.match(message);
            if (matchDr.hasMatch()) {
                medecin = matchDr.captured(1).trimmed();
                qDebug() << "✅ Médecin extrait après Dr:" << medecin;
            }
            
            // PRIORITÉ 2: Cas "patients du Dr. X" ou "patients du Dr. X'" - extraire ce qui vient après "Dr"
            if (medecin.isEmpty()) {
                QRegularExpression regexPatientsDr("\\bpatients?\\s+(?:du|de|des|d')\\s+(?:dr\\.?|docteur|médecin|medecin)\\s+([\\w]+)",
                                                   QRegularExpression::CaseInsensitiveOption);
                QRegularExpressionMatch matchPatientsDr = regexPatientsDr.match(message);
                if (matchPatientsDr.hasMatch()) {
                    medecin = matchPatientsDr.captured(1).trimmed();
                    qDebug() << "✅ Médecin extrait de 'patients du Dr':" << medecin;
                }
            }
            
            // PRIORITÉ 3: Essayer avec extraireParametre
            if (medecin.isEmpty()) {
                medecin = extraireParametre(message, "médecin|docteur|dr");
                // Nettoyer si le résultat contient "Dr." ou "Dr "
                if (medecin.contains("dr", Qt::CaseInsensitive)) {
                    medecin = medecin.remove(QRegularExpression("\\bdr\\.?\\s*", QRegularExpression::CaseInsensitiveOption)).trimmed();
                }
            }
            
            // PRIORITÉ 4: Cas générique "patients du/de X"
            if (medecin.isEmpty()) {
                QRegularExpression regexPatients("\\bpatients?\\s+(?:du|de|des|d')\\s+([\\w\\s]+?)(?:'|$|\\s|,|\\.)",
                                                 QRegularExpression::CaseInsensitiveOption);
                QRegularExpressionMatch match = regexPatients.match(message);
                if (match.hasMatch()) {
                    medecin = match.captured(1).trimmed();
                    // Nettoyer si le résultat contient "Dr." ou "Dr "
                    if (medecin.contains("dr", Qt::CaseInsensitive)) {
                        medecin = medecin.remove(QRegularExpression("\\bdr\\.?\\s*", QRegularExpression::CaseInsensitiveOption)).trimmed();
                    }
                    qDebug() << "✅ Médecin extrait de 'patients du':" << medecin;
                }
            }
            
            // Nettoyer le nom du médecin (enlever les apostrophes, espaces en trop, etc.)
            medecin = medecin.trimmed();
            medecin = medecin.remove("'");
            medecin = medecin.remove("\"");
            
            qDebug() << "🔍 Nom du médecin final:" << medecin;
            return rechercherParMedecin(medecin, tableWidget);
        }
        
        case RECHERCHE_PATIENT: {
            QString patient = "";
            
            // PRIORITÉ 1: Cas "ordonnance(s) de X" ou "trouve les ordonnances de X"
            // Extraire uniquement le nom qui vient après "de" ou "du"
            QRegularExpression regexOrdonnances("\\b(?:trouve|cherche|montre|affiche|ordonnance?s?)\\s+(?:les\\s+)?ordonnance?s?\\s+(?:de|du|d')\\s+([\\w]+)",
                                                QRegularExpression::CaseInsensitiveOption);
            QRegularExpressionMatch match = regexOrdonnances.match(message);
            if (match.hasMatch()) {
                patient = match.captured(1).trimmed();
                qDebug() << "✅ Patient extrait de 'ordonnances de':" << patient;
            }
            
            // PRIORITÉ 2: Cas "patient X" ou "nom X"
            if (patient.isEmpty()) {
                patient = extraireParametre(message, "patient|nom|prenom");
                qDebug() << "✅ Patient extrait avec extraireParametre:" << patient;
            }
            
            // PRIORITÉ 3: Cas générique "de X" ou "du X"
            if (patient.isEmpty()) {
                QRegularExpression regexDe("\\b(?:de|du|d')\\s+([\\w]+)",
                                          QRegularExpression::CaseInsensitiveOption);
                QRegularExpressionMatch matchDe = regexDe.match(message);
                if (matchDe.hasMatch()) {
                    patient = matchDe.captured(1).trimmed();
                    qDebug() << "✅ Patient extrait de 'de':" << patient;
                }
            }
            
            // Nettoyer le nom du patient (enlever les apostrophes, espaces en trop, etc.)
            patient = patient.trimmed();
            patient = patient.remove("'");
            patient = patient.remove("\"");
            
            qDebug() << "🔍 Nom du patient final:" << patient;
            return rechercherParPatient(patient, tableWidget);
        }
        
        case RECHERCHE_DATE: {
            QString dateStr = "";
            
            // PRIORITÉ: Extraire directement la date du message (format dd/MM/yyyy ou dd-MM-yyyy)
            QRegularExpression dateRegex("\\b(\\d{1,2}[/-]\\d{1,2}[/-]\\d{4})\\b");
            QRegularExpressionMatch match = dateRegex.match(message);
            if (match.hasMatch()) {
                dateStr = match.captured(1);
                qDebug() << "📅 Date extraite directement:" << dateStr;
            }
            
            // Si pas trouvée, essayer avec extraireParametre
            if (dateStr.isEmpty()) {
                dateStr = extraireParametre(message, "date|le|au");
                // Nettoyer la date si elle contient le mot "date"
                if (dateStr.contains("date", Qt::CaseInsensitive)) {
                    dateStr = dateStr.remove("date", Qt::CaseInsensitive).trimmed();
                }
            }
            
            // Si toujours vide, essayer format yyyy-MM-dd
            if (dateStr.isEmpty()) {
                QRegularExpression dateRegex2("(\\d{4}-\\d{2}-\\d{2})");
                QRegularExpressionMatch match2 = dateRegex2.match(message);
                if (match2.hasMatch()) {
                    dateStr = match2.captured(1);
                }
            }
            
            qDebug() << "🔍 Recherche par date avec:" << dateStr;
            return rechercherParDate(dateStr, tableWidget);
        }
        
        case STATISTIQUE_NOMBRE: {
            QString periode = "";
            if (message.contains("mois")) periode = "mois";
            else if (message.contains("semaine")) periode = "semaine";
            else if (message.contains("jour") || message.contains("aujourd'hui")) periode = "jour";
            return obtenirStatistiqueNombre(periode);
        }
        
        case STATISTIQUE_DATE: {
            QString dateStr = extraireParametre(message, "date|le|au");
            
            // Si pas de date extraite, essayer d'extraire une date du message
            if (dateStr.isEmpty()) {
                QRegularExpression dateRegex("\\b(\\d{1,2}/\\d{1,2}/\\d{4})\\b");
                QRegularExpressionMatch match = dateRegex.match(message);
                if (match.hasMatch()) {
                    dateStr = match.captured(1);
                }
            }
            
            // Si toujours vide, vérifier si c'est "aujourd'hui" ou "hier" (devrait être STATISTIQUE_NOMBRE mais au cas où)
            if (dateStr.isEmpty()) {
                if (message.contains("aujourd'hui", Qt::CaseInsensitive)) {
                    return obtenirStatistiqueNombre("jour");
                }
                if (message.contains("hier", Qt::CaseInsensitive)) {
                    // Pour hier, on ne peut pas utiliser obtenirStatistiqueNombre, donc on fait une recherche par date
                    QDate hier = QDate::currentDate().addDays(-1);
                    return obtenirStatistiqueDate(hier.toString("dd/MM/yyyy"));
                }
            }
            
            return obtenirStatistiqueDate(dateStr);
        }
        
        case STATISTIQUE_MEDECIN: {
            QString medecin = extraireParametre(message, "médecin|docteur|dr");
            return obtenirStatistiqueMedecin(medecin);
        }
        
        case ALERTE_ANOMALIES: {
            QStringList anomalies = detecterAnomalies();
            if (anomalies.isEmpty()) {
                return "✅ Aucune anomalie détectée. Toutes les données sont valides.";
            }
            return "⚠️ Anomalies détectées:\n" + anomalies.join("\n");
        }
        
        case RAPPORT_ACTIVITE: {
            return genererRapportActivite();
        }
        
        case AIDE: {
            return "🤖 **Aide du Chatbot**\n\n"
                   "Je peux vous aider avec:\n"
                   "• Recherche: 'Montre-moi les patients du Dr. X' ou 'Trouve les ordonnances de Y'\n"
                   "• Statistiques: 'Combien d'ordonnances ce mois?' ou 'Statistiques du Dr. X'\n"
                   "• Dates: 'Ordonnances du 19/11/2025' ou 'Ordonnances d'aujourd'hui'\n"
                   "• Anomalies: 'Détecte les anomalies' ou 'Vérifie les doublons'\n"
                   "• Rapports: 'Génère un rapport d'activité'\n\n"
                   "Posez-moi une question en langage naturel!";
        }
        
        default:
            return "🤔 Je n'ai pas compris votre demande. "
                   "Essayez de reformuler ou tapez 'aide' pour voir les commandes disponibles.";
    }
}

QString Chatbot::rechercherParMedecin(const QString &medecin, QTableWidget *tableWidget)
{
    QString medecinClean = medecin.trimmed();
    
    // Nettoyer le nom du médecin
    medecinClean = medecinClean.remove("'");
    medecinClean = medecinClean.remove("\"");
    medecinClean = medecinClean.trimmed();
    
    if (medecinClean.isEmpty()) {
        return "❌ Veuillez spécifier le nom du médecin (ex: 'Montre-moi les patients du Dr. X').";
    }
    
    qDebug() << "🔍 Recherche du médecin:" << medecinClean;
    
    QSqlQuery query;
    query.prepare("SELECT CIN, NOM, PRENOM, MEDECIN, DATE_ORD FROM ordonnance WHERE MEDECIN LIKE :medecin ORDER BY DATE_ORD DESC");
    query.bindValue(":medecin", "%" + medecinClean + "%");
    
    if (!query.exec()) {
        return "❌ Erreur lors de la recherche: " + query.lastError().text();
    }
    
    int row = 0;
    QStringList detailsOrdonnances;
    
    while (query.next()) {
        QString cin = query.value("CIN").toString();
        QString nom = query.value("NOM").toString();
        QString prenom = query.value("PRENOM").toString();
        QString medecin = query.value("MEDECIN").toString();
        QString date = query.value("DATE_ORD").toString();
        
        // Ajouter les détails à la liste pour le message
        detailsOrdonnances << QString("  • CIN: %1 | Nom: %2 | Prénom: %3")
                              .arg(cin)
                              .arg(nom)
                              .arg(prenom);
        
        // Remplir le tableau si disponible
        if (tableWidget) {
            if (row == 0) {
                // Initialiser le tableau seulement au premier résultat
                tableWidget->setRowCount(0);
                QStringList headers;
                headers << "CIN" << "Nom" << "Prénom" << "Médecin" << "Date";
                tableWidget->setColumnCount(5);
                tableWidget->setHorizontalHeaderLabels(headers);
            }
            
            tableWidget->insertRow(row);
            tableWidget->setItem(row, 0, new QTableWidgetItem(cin));
            tableWidget->setItem(row, 1, new QTableWidgetItem(nom));
            tableWidget->setItem(row, 2, new QTableWidgetItem(prenom));
            tableWidget->setItem(row, 3, new QTableWidgetItem(medecin));
            tableWidget->setItem(row, 4, new QTableWidgetItem(date));
        }
        
        row++;
    }
    
    // Construire le message de réponse
    QString message = QString("✅ J'ai trouvé %1 ordonnance(s) pour le médecin '%2'.").arg(row).arg(medecinClean);
    
    if (row > 0) {
        message += "\n\n📋 Détails des ordonnances:\n";
        message += detailsOrdonnances.join("\n");
    } else {
        message += "\n\nℹ️ Aucune ordonnance trouvée pour ce médecin.";
    }
    
    return message;
}

QString Chatbot::rechercherParPatient(const QString &nom, QTableWidget *tableWidget)
{
    QString nomClean = nom.trimmed();
    
    // Nettoyer le nom du patient
    nomClean = nomClean.remove("'");
    nomClean = nomClean.remove("\"");
    nomClean = nomClean.trimmed();
    
    if (nomClean.isEmpty()) {
        return "❌ Veuillez spécifier le nom du patient (ex: 'Trouve les ordonnances de b').";
    }
    
    qDebug() << "🔍 Recherche du patient:" << nomClean;
    
    if (tableWidget) {
        tableWidget->setRowCount(0);
        QStringList headers;
        headers << "CIN" << "Nom" << "Prénom" << "Médecin" << "Date";
        tableWidget->setColumnCount(5);
        tableWidget->setHorizontalHeaderLabels(headers);
        
        QSqlQuery query;
        
        // PRIORITÉ 1: Recherche exacte d'abord (nom ou prénom = exactement "b")
        query.prepare("SELECT * FROM ordonnance WHERE NOM = :nom OR PRENOM = :nom");
        query.bindValue(":nom", nomClean);
        
        if (!query.exec()) {
            return "❌ Erreur lors de la recherche: " + query.lastError().text();
        }
        
        int row = 0;
        QStringList patientsTrouves;
        
        // Si recherche exacte trouve des résultats, les utiliser
        bool rechercheExacte = false;
        while (query.next()) {
            rechercheExacte = true;
            tableWidget->insertRow(row);
            QString nom = query.value("NOM").toString();
            QString prenom = query.value("PRENOM").toString();
            tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("CIN").toString()));
            tableWidget->setItem(row, 1, new QTableWidgetItem(nom));
            tableWidget->setItem(row, 2, new QTableWidgetItem(prenom));
            tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("MEDECIN").toString()));
            tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("DATE_ORD").toString()));
            patientsTrouves << QString("%1 %2").arg(prenom).arg(nom);
            row++;
        }
        
        // Si recherche exacte ne trouve rien, faire une recherche partielle
        if (!rechercheExacte) {
            query.prepare("SELECT * FROM ordonnance WHERE NOM LIKE :nom OR PRENOM LIKE :nom");
            query.bindValue(":nom", "%" + nomClean + "%");
            
            if (!query.exec()) {
                return "❌ Erreur lors de la recherche: " + query.lastError().text();
            }
            
            while (query.next()) {
                tableWidget->insertRow(row);
                QString nom = query.value("NOM").toString();
                QString prenom = query.value("PRENOM").toString();
                tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("CIN").toString()));
                tableWidget->setItem(row, 1, new QTableWidgetItem(nom));
                tableWidget->setItem(row, 2, new QTableWidgetItem(prenom));
                tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("MEDECIN").toString()));
                tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("DATE_ORD").toString()));
                patientsTrouves << QString("%1 %2").arg(prenom).arg(nom);
                row++;
            }
        }
        
        // Construire le message de réponse
        QString message = QString("✅ J'ai trouvé %1 ordonnance(s) pour le patient '%2'.").arg(row).arg(nomClean);
        if (row > 0 && patientsTrouves.size() > 0) {
            message += QString("\n📋 Patients trouvés: %1").arg(patientsTrouves.join(", "));
        }
        
        qDebug() << "📊 Recherche terminée:" << row << "ordonnance(s) trouvée(s)";
        return message;
    }
    
    return "✅ Recherche effectuée.";
}

QString Chatbot::rechercherParDate(const QString &dateStr, QTableWidget *tableWidget)
{
    QString dateStrClean = dateStr.trimmed();
    
    // Nettoyer la chaîne si elle contient des mots parasites
    dateStrClean = dateStrClean.remove("date", Qt::CaseInsensitive).trimmed();
    dateStrClean = dateStrClean.remove("le", Qt::CaseInsensitive).trimmed();
    dateStrClean = dateStrClean.remove("du", Qt::CaseInsensitive).trimmed();
    dateStrClean = dateStrClean.remove("de", Qt::CaseInsensitive).trimmed();
    
    qDebug() << "🔍 Parser date avec:" << dateStrClean;
    QDate date = parserDate(dateStrClean);
    
    if (!date.isValid()) {
        return QString("❌ Date invalide: '%1'. Utilisez le format dd/MM/yyyy (ex: 25/11/2025) ou 'aujourd'hui', 'hier'.").arg(dateStr);
    }
    
    if (tableWidget) {
        tableWidget->setRowCount(0);
        QStringList headers;
        headers << "CIN" << "Nom" << "Prénom" << "Médecin" << "Date";
        tableWidget->setColumnCount(5);
        tableWidget->setHorizontalHeaderLabels(headers);
        
        QSqlQuery query;
        query.prepare("SELECT * FROM ordonnance WHERE DATE_ORD = :date");
        query.bindValue(":date", date);
        
        if (!query.exec()) {
            return "❌ Erreur lors de la recherche: " + query.lastError().text();
        }
        
        int row = 0;
        while (query.next()) {
            tableWidget->insertRow(row);
            tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("CIN").toString()));
            tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("NOM").toString()));
            tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("PRENOM").toString()));
            tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("MEDECIN").toString()));
            tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("DATE_ORD").toString()));
            row++;
        }
        
        return QString("✅ J'ai trouvé %1 ordonnance(s) pour le %2.").arg(row).arg(formaterDate(date));
    }
    
    return "✅ Recherche effectuée.";
}

QString Chatbot::obtenirStatistiqueNombre(const QString &periode)
{
    QSqlQuery query;
    QString condition = "";
    
    if (periode == "mois") {
        condition = "WHERE MONTH(DATE_ORD) = MONTH(GETDATE()) AND YEAR(DATE_ORD) = YEAR(GETDATE())";
    } else if (periode == "semaine") {
        condition = "WHERE DATE_ORD >= DATEADD(day, -7, GETDATE())";
    } else if (periode == "jour") {
        condition = "WHERE DATE_ORD = CAST(GETDATE() AS DATE)";
    }
    
    query.prepare("SELECT COUNT(*) as total FROM ordonnance " + condition);
    
    if (!query.exec() || !query.next()) {
        return "❌ Erreur lors du calcul des statistiques.";
    }
    
    int total = query.value("total").toInt();
    QString periodeStr = periode.isEmpty() ? "total" : 
                        (periode == "mois" ? "ce mois" : 
                        (periode == "semaine" ? "cette semaine" : "aujourd'hui"));
    
    return QString("📊 Il y a %1 ordonnance(s) %2.").arg(total).arg(periodeStr);
}

QString Chatbot::obtenirStatistiqueDate(const QString &dateStr)
{
    QString dateStrClean = dateStr.trimmed();
    
    // Si la chaîne est vide, retourner une erreur claire
    if (dateStrClean.isEmpty()) {
        return "❌ Veuillez spécifier une date. Utilisez le format dd/MM/yyyy (ex: 25/11/2025) ou 'aujourd'hui', 'hier'.";
    }
    
    QDate date = parserDate(dateStrClean);
    
    if (!date.isValid()) {
        return QString("❌ Date invalide: '%1'. Utilisez le format dd/MM/yyyy (ex: 25/11/2025) ou 'aujourd'hui', 'hier'.").arg(dateStr);
    }
    
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) as total FROM ordonnance WHERE DATE_ORD = :date");
    query.bindValue(":date", date);
    
    if (!query.exec() || !query.next()) {
        return "❌ Erreur lors du calcul des statistiques.";
    }
    
    int total = query.value("total").toInt();
    return QString("📊 Il y a %1 ordonnance(s) pour le %2.").arg(total).arg(formaterDate(date));
}

QString Chatbot::obtenirStatistiqueMedecin(const QString &medecin)
{
    if (medecin.isEmpty()) {
        // Statistiques pour tous les médecins
        QSqlQuery query;
        query.prepare("SELECT MEDECIN, COUNT(*) as total FROM ordonnance GROUP BY MEDECIN ORDER BY total DESC");
        
        if (!query.exec()) {
            return "❌ Erreur lors du calcul des statistiques.";
        }
        
        QStringList resultats;
        while (query.next()) {
            resultats << QString("• %1: %2 ordonnance(s)")
                         .arg(query.value("MEDECIN").toString())
                         .arg(query.value("total").toInt());
        }
        
        return "📊 Statistiques par médecin:\n" + resultats.join("\n");
    }
    
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) as total FROM ordonnance WHERE MEDECIN LIKE :medecin");
    query.bindValue(":medecin", "%" + medecin + "%");
    
    if (!query.exec() || !query.next()) {
        return "❌ Erreur lors du calcul des statistiques.";
    }
    
    int total = query.value("total").toInt();
    return QString("📊 Le médecin '%1' a %2 ordonnance(s).").arg(medecin).arg(total);
}

QStringList Chatbot::detecterAnomalies()
{
    QStringList anomalies;
    
    // Détecter les doublons
    anomalies << detecterDoublons();
    
    // Détecter les CIN invalides
    anomalies << detecterCINInvalides();
    
    // Détecter les dates anormales
    anomalies << detecterDatesAnormales();
    
    // Filtrer les chaînes vides
    anomalies.removeAll("");
    
    return anomalies;
}

QStringList Chatbot::detecterDoublons()
{
    QStringList anomalies;
    
    QSqlQuery query;
    query.prepare("SELECT CIN, NOM, PRENOM, MEDECIN, DATE_ORD, COUNT(*) as count "
                  "FROM ordonnance "
                  "GROUP BY CIN, NOM, PRENOM, MEDECIN, DATE_ORD "
                  "HAVING COUNT(*) > 1");
    
    if (query.exec()) {
        while (query.next()) {
            int count = query.value("count").toInt();
            if (count > 1) {
                anomalies << QString("⚠️ Doublon détecté: %1 ordonnance(s) identique(s) pour CIN %2, %3 %4, Dr. %5, le %6")
                             .arg(count)
                             .arg(query.value("CIN").toString())
                             .arg(query.value("PRENOM").toString())
                             .arg(query.value("NOM").toString())
                             .arg(query.value("MEDECIN").toString())
                             .arg(query.value("DATE_ORD").toString());
            }
        }
    }
    
    return anomalies;
}

QStringList Chatbot::detecterCINInvalides()
{
    QStringList anomalies;
    
    QSqlQuery query("SELECT CIN, NOM, PRENOM FROM ordonnance");
    
    if (query.exec()) {
        while (query.next()) {
            QString cin = query.value("CIN").toString();
            if (!estCINValide(cin)) {
                anomalies << QString("⚠️ CIN invalide: '%1' pour %2 %3")
                             .arg(cin)
                             .arg(query.value("PRENOM").toString())
                             .arg(query.value("NOM").toString());
            }
        }
    }
    
    return anomalies;
}

QStringList Chatbot::detecterDatesAnormales()
{
    QStringList anomalies;
    QDate aujourdhui = QDate::currentDate();
    QDate dateLimite = aujourdhui.addYears(-10); // Dates de plus de 10 ans
    
    QSqlQuery query("SELECT CIN, NOM, PRENOM, DATE_ORD FROM ordonnance");
    
    if (query.exec()) {
        while (query.next()) {
            QDate date = query.value("DATE_ORD").toDate();
            
            if (!date.isValid()) {
                anomalies << QString("⚠️ Date invalide pour CIN %1, %2 %3")
                             .arg(query.value("CIN").toString())
                             .arg(query.value("PRENOM").toString())
                             .arg(query.value("NOM").toString());
            } else if (date > aujourdhui) {
                anomalies << QString("⚠️ Date future: %1 pour CIN %2, %3 %4")
                             .arg(date.toString("dd/MM/yyyy"))
                             .arg(query.value("CIN").toString())
                             .arg(query.value("PRENOM").toString())
                             .arg(query.value("NOM").toString());
            } else if (date < dateLimite) {
                anomalies << QString("⚠️ Date très ancienne: %1 pour CIN %2, %3 %4")
                             .arg(date.toString("dd/MM/yyyy"))
                             .arg(query.value("CIN").toString())
                             .arg(query.value("PRENOM").toString())
                             .arg(query.value("NOM").toString());
            }
        }
    }
    
    return anomalies;
}

QString Chatbot::genererRapportActivite()
{
    QSqlQuery query;
    QString rapport = "📋 **Rapport d'Activité des Ordonnances**\n\n";
    
    // Total d'ordonnances
    query.prepare("SELECT COUNT(*) as total FROM ordonnance");
    if (query.exec() && query.next()) {
        rapport += QString("📊 Total d'ordonnances: %1\n").arg(query.value("total").toInt());
    }
    
    // Ordonnances aujourd'hui
    query.prepare("SELECT COUNT(*) as total FROM ordonnance WHERE DATE_ORD = CAST(GETDATE() AS DATE)");
    if (query.exec() && query.next()) {
        rapport += QString("📅 Ordonnances aujourd'hui: %1\n").arg(query.value("total").toInt());
    }
    
    // Ordonnances ce mois
    query.prepare("SELECT COUNT(*) as total FROM ordonnance WHERE MONTH(DATE_ORD) = MONTH(GETDATE()) AND YEAR(DATE_ORD) = YEAR(GETDATE())");
    if (query.exec() && query.next()) {
        rapport += QString("📆 Ordonnances ce mois: %1\n").arg(query.value("total").toInt());
    }
    
    // Top 5 médecins
    rapport += "\n🏥 Top 5 médecins:\n";
    
    // Essayer d'abord avec TOP 5 (SQL Server)
    query.prepare("SELECT TOP 5 MEDECIN, COUNT(*) as total FROM ordonnance GROUP BY MEDECIN ORDER BY total DESC");
    bool success = query.exec();
    
    if (!success) {
        qDebug() << "⚠️ Erreur avec TOP 5, essai sans limite:" << query.lastError().text();
        // Si TOP 5 échoue, essayer sans limite et limiter en C++
        query.prepare("SELECT MEDECIN, COUNT(*) as total FROM ordonnance GROUP BY MEDECIN ORDER BY total DESC");
        success = query.exec();
    }
    
    if (success) {
        int rank = 1;
        int count = 0;
        bool hasResults = false;
        
        qDebug() << "🔍 Début de la récupération des médecins...";
        while (query.next() && count < 5) {
            QString medecin = query.value("MEDECIN").toString();
            int total = query.value("total").toInt();
            
            if (!medecin.isEmpty()) {
                rapport += QString("  %1. %2: %3 ordonnance(s)\n")
                              .arg(rank++)
                              .arg(medecin)
                              .arg(total);
                count++;
                hasResults = true;
                qDebug() << "✅ Médecin" << rank - 1 << ":" << medecin << "-" << total << "ordonnance(s)";
            } else {
                qDebug() << "⚠️ Médecin vide trouvé, ignoré";
            }
        }
        
        if (!hasResults) {
            rapport += "  Aucun médecin trouvé dans la base de données.\n";
            qDebug() << "⚠️ Aucun médecin trouvé dans les résultats de la requête";
        } else {
            qDebug() << "✅ Total de" << count << "médecin(s) ajouté(s) au rapport";
        }
    } else {
        qDebug() << "❌ Erreur lors de la récupération des médecins:" << query.lastError().text();
        rapport += QString("  ❌ Erreur: %1\n").arg(query.lastError().text());
    }
    
    // Anomalies détectées
    QStringList anomalies = detecterAnomalies();
    rapport += QString("\n⚠️ Anomalies détectées: %1\n").arg(anomalies.size());
    if (anomalies.size() > 0) {
        rapport += "  (Utilisez 'Détecte les anomalies' pour plus de détails)\n";
    }
    
    rapport += QString("\n🕐 Rapport généré le: %1")
                  .arg(QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm"));
    
    return rapport;
}

QStringList Chatbot::suggererAutoCompletion(const QString &textePartiel, int position)
{
    QStringList suggestions;
    QString texte = textePartiel.toLower();
    
    // Suggestions de commandes
    if (texte.isEmpty() || texte.startsWith("m") || texte.startsWith("t")) {
        suggestions << "Montre-moi les patients du Dr."
                    << "Trouve les ordonnances de"
                    << "Combien d'ordonnances";
    }
    
    if (texte.contains("combien") || texte.contains("stat")) {
        suggestions << "Combien d'ordonnances ce mois?"
                    << "Combien d'ordonnances aujourd'hui?"
                    << "Statistiques du Dr.";
    }
    
    if (texte.contains("montre") || texte.contains("trouve")) {
        suggestions << "Montre-moi les patients du Dr. [nom]"
                    << "Trouve les ordonnances de [nom]"
                    << "Ordonnances du [date]";
    }
    
    // Suggestions de médecins (depuis la base)
    if (texte.contains("dr") || texte.contains("médecin") || texte.contains("docteur")) {
        QSqlQuery query("SELECT DISTINCT MEDECIN FROM ordonnance");
        if (query.exec()) {
            while (query.next()) {
                suggestions << "Dr. " + query.value("MEDECIN").toString();
            }
        }
    }
    
    return suggestions;
}

QDate Chatbot::parserDate(const QString &dateStr)
{
    QString str = dateStr.toLower().trimmed();
    
    // Nettoyer la chaîne des mots parasites
    str = str.remove("date", Qt::CaseInsensitive).trimmed();
    str = str.remove("le", Qt::CaseInsensitive).trimmed();
    str = str.remove("du", Qt::CaseInsensitive).trimmed();
    str = str.remove("de", Qt::CaseInsensitive).trimmed();
    str = str.trimmed();
    
    if (str == "aujourd'hui" || str == "aujourd hui" || str == "today") {
        return QDate::currentDate();
    }
    
    if (str == "hier" || str == "yesterday") {
        return QDate::currentDate().addDays(-1);
    }
    
    // Extraire la date si elle est dans une phrase (ex: "date 25/11/2025" -> "25/11/2025")
    QRegularExpression dateRegex("(\\d{1,2}[/-]\\d{1,2}[/-]\\d{4}|\\d{4}[/-]\\d{2}[/-]\\d{2})");
    QRegularExpressionMatch match = dateRegex.match(str);
    if (match.hasMatch()) {
        str = match.captured(1);
    }
    
    // Format dd/MM/yyyy
    QDate date = QDate::fromString(str, "dd/MM/yyyy");
    if (date.isValid()) {
        qDebug() << "✅ Date parsée (dd/MM/yyyy):" << date.toString("dd/MM/yyyy");
        return date;
    }
    
    // Format dd-MM-yyyy
    date = QDate::fromString(str, "dd-MM-yyyy");
    if (date.isValid()) {
        qDebug() << "✅ Date parsée (dd-MM-yyyy):" << date.toString("dd/MM/yyyy");
        return date;
    }
    
    // Format yyyy-MM-dd
    date = QDate::fromString(str, "yyyy-MM-dd");
    if (date.isValid()) {
        qDebug() << "✅ Date parsée (yyyy-MM-dd):" << date.toString("dd/MM/yyyy");
        return date;
    }
    
    qDebug() << "❌ Date non parsée:" << dateStr;
    return QDate();
}

bool Chatbot::estCINValide(const QString &cin)
{
    // CIN doit contenir entre 6 et 12 caractères alphanumériques
    if (cin.length() < 6 || cin.length() > 12) {
        return false;
    }
    
    // CIN doit être alphanumérique
    QRegularExpression regex("^[A-Z0-9]+$", QRegularExpression::CaseInsensitiveOption);
    return regex.match(cin).hasMatch();
}

QString Chatbot::formaterDate(const QDate &date)
{
    return date.toString("dd/MM/yyyy");
}

