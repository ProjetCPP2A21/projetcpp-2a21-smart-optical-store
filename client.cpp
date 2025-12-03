#include "client.h"
#include <QSqlQuery>
#include <QSqlError>
#include<QFontDatabase>
#include <QDebug>
#include <QVariant>
#include <QMessageBox>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QFileInfo>
#include <QDateTime>
#include <QTextDocument>
#include <QStandardPaths>
#include <QPrinter>
#include <QTextDocument>
#include <QFileInfo>
#include <QDateTime>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardPaths>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QPainter>
#include <QRandomGenerator>
#include <QDate>
#include <QRandomGenerator>
#include "smtp.h"
//email
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
//api
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>
#include <QEventLoop>
client::client(int id_client, QString nom, QString prenom, QString date_naissance,
               QString email, int num_tel, QString date_inscri, int point_fedelite)
{
    this->id_client = id_client;
    this->nom = nom;
    this->prenom = prenom;
    this->date_naissance = date_naissance;
    this->email = email;
    this->num_tel = num_tel;
    this->date_inscri = date_inscri;
    this->point_fedelite = point_fedelite;
}
bool client::ajouter_client()
{
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM client WHERE id_client = :id_client");
    checkQuery.bindValue(":id_client", id_client);
    checkQuery.exec();
    checkQuery.next();
    if (checkQuery.value(0).toInt() > 0) {
        QMessageBox::warning(nullptr, "Erreur", "L'ID existe déjà !");
        return false;
    }
    QSqlQuery query;

    query.prepare("INSERT INTO client (id_client, nom, prenom, date_naissance, email, num_tel, date_inscri, point_fedelite) "
                  "VALUES (:id_client, :nom, :prenom, :date_naissance, :email, :num_tel, :date_inscri, :point_fedelite)");

    query.bindValue(":id_client", id_client);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":date_naissance", date_naissance);
    query.bindValue(":email", email);
    query.bindValue(":num_tel", num_tel);
    query.bindValue(":date_inscri", date_inscri);
    query.bindValue(":point_fedelite", point_fedelite);


    return query.exec();
}
bool client::supprimer_client(int id_client)
{
    QSqlQuery query;
    query.prepare("DELETE FROM client WHERE id_client = :id_client"); // nom exact de la colonne
    query.bindValue(":id_client", id_client); // pas besoin de QString
    bool test = query.exec();
    if(!test) {
        qDebug() << "Erreur SQL :" << query.lastError().text();
    }
    return test;

    return query.exec();
}

QSqlQueryModel * client::afficher_client()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model ->setQuery("select * from client ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_client"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("date_naissance"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("email"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("num_tel"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("date_inscri"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("point_fedelite"));
    return model;
}

bool client::modifier_client(int id_client, QString nom, QString prenom,
                             QString date_naissance, QString email,
                             int num_tel, QString date_inscri, int point_fedelite)
{
    QSqlQuery query;
    query.prepare("UPDATE client SET nom=:nom, prenom=:prenom, date_naissance=:date_naissance, "
                  "email=:email, num_tel=:num_tel, date_inscri=:date_inscri, point_fedelite=:point_fedelite "
                  "WHERE id_client=:id_client");

    query.bindValue(":id_client", id_client);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":date_naissance", date_naissance);
    query.bindValue(":email", email);
    query.bindValue(":num_tel", num_tel);
    query.bindValue(":date_inscri", date_inscri);
    query.bindValue(":point_fedelite", point_fedelite);

    bool test = query.exec();
    if(!test)
        qDebug() << "Erreur SQL :" << query.lastError().text();



    return test;
}
QSqlQueryModel* client::rechercher_client(int id)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("SELECT * FROM client WHERE id_client = :id_client");
    query.bindValue(":id_client", id);
    query.exec();

    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, "ID Client");
    model->setHeaderData(1, Qt::Horizontal, "Nom");
    model->setHeaderData(2, Qt::Horizontal, "Prénom");
    model->setHeaderData(3, Qt::Horizontal, "Date Naissance");
    model->setHeaderData(4, Qt::Horizontal, "Email");
    model->setHeaderData(5, Qt::Horizontal, "Téléphone");
    model->setHeaderData(6, Qt::Horizontal, "Date Inscription");
    model->setHeaderData(7, Qt::Horizontal, "point_fedelite Fidélité");

    return model;
}
QSqlQueryModel * client::trier_client()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM client ORDER BY nom ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date d'inscription"));
    return model;
}

bool client::exporter_client_pdf(const QString &fichier)
{
    //  Récupérer les données de la table client
    QSqlQuery query;
    if (!query.exec("SELECT id_client, nom, prenom, date_naissance, email, num_tel, date_inscri, point_fedelite FROM client ORDER BY id_client")) {
        QMessageBox::critical(nullptr, "Erreur SQL", query.lastError().text());
        return false;
    }

    // Générer le HTML
    QString now = QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm");
    QString html = "<html><head><meta charset='utf-8'><style>"
                   "body{font-family:Arial,Helvetica,sans-serif;}"
                   "table{width:100%;border-collapse:collapse;}"
                   "th,td{border:1px solid #888;padding:6px;text-align:left;}"
                   "th{background:#f0f0f0;}"
                   "tr:nth-child(even){background:#fafafa;}"
                   "</style></head><body>";
    html += "<h2>Liste des clients</h2><p>Généré le " + now + "</p><table>";
    html += "<tr><th>ID</th><th>Nom</th><th>Prénom</th><th>Date Naissance</th><th>Email</th><th>Téléphone</th><th>Date Inscription</th><th>point_fedelite Fidélité</th></tr>";

    while (query.next()) {
        html += "<tr>";
        for (int i = 0; i < 8; ++i)
            html += "<td>" + query.value(i).toString().toHtmlEscaped() + "</td>";
        html += "</tr>";
    }
    html += "</table></body></html>";

    //  Définir le chemin du fichier
    QString outputPath = fichier;
    if (outputPath.isEmpty()) {
        outputPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/clients.pdf";
    }
    if (QFileInfo(outputPath).suffix().toLower() != "pdf")
        outputPath += ".pdf";

    // Créer le PDF
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(outputPath);
    printer.setPageSize(QPageSize(QPageSize::A4));

    QTextDocument doc;
    doc.setHtml(html);
    doc.print(&printer);

    QMessageBox::information(nullptr, "PDF exporté", "Le fichier a été enregistré sous :\n" + outputPath);
    return true;
}
//email de l'anniverssaire

QList<client> client::clientsAnniversaireProche()
{
    QList<client> liste;
    QSqlQuery query("SELECT id_client, nom, prenom, email, date_naissance FROM client");
    QDate today = QDate::currentDate();

    while (query.next())
    {
        QString dateStr = query.value("date_naissance").toString().trimmed();

        // test de champ
        if (dateStr.isEmpty() || dateStr.length() < 8)
        {
            qDebug() << "Date vide ou invalide pour" << query.value("prenom").toString();
            continue;
        }

        // Format date
        QDate dateNaissance = QDate::fromString(dateStr, "dd/MM/yyyy");

        if (!dateNaissance.isValid())
        {
            qDebug() << "Format date incorrect :" << dateStr << "(client:" << query.value("nom").toString() << ")";
            continue;
        }

        // Calcul du prochain anniversaire
        QDate prochainAnniv(today.year(), dateNaissance.month(), dateNaissance.day());

        // Si l'anniv est déjà passé cette année on prend l'année prochaine
        if (prochainAnniv < today)
            prochainAnniv = prochainAnniv.addYears(1);

        int joursRestants = today.daysTo(prochainAnniv);

        qDebug() << "Client:" << query.value("prenom").toString()
                 << query.value("nom").toString()
                 << "| Né le:" << dateNaissance.toString("dd/MM/yyyy")
                 << "| Prochain anniv:" << prochainAnniv.toString("dd/MM/yyyy")
                 << "| Jours restants:" << joursRestants;

        // On envoie l'email si l'anniversaire est dans 7 jours ou moins
        if (joursRestants >= 0 && joursRestants <= 7)
        {
            client c;
            c.setId(query.value("id_client").toInt());
            c.setNom(query.value("nom").toString());
            c.setPrenom(query.value("prenom").toString());
            c.setEmail(query.value("email").toString());
            liste.append(c);

            qDebug() << "EMAIL À ENVOYER →" << c.getPrenom() << c.getNom() << "dans" << joursRestants << "jour(s)";
        }
    }

    qDebug() << "Total clients avec anniversaire dans ≤ 7 jours :" << liste.size();
    return liste;
}

QString client::genererCodePromo() {
    const QString chars("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
    QString code;
    for (int i = 0; i < 8; i++) {
        code += chars[QRandomGenerator::global()->bounded(chars.length())];

    }
    return code;
}




void client::envoyerEmailAnniversaire()
{
    QList<client> liste = clientsAnniversaireProche();
    if (liste.isEmpty()) {
        qDebug() << "Aucun anniversaire proche.";
        return;
    }

    const QString from      = "optismartclient@gmail.com";   //  expéditeur
    const QString password  = "hbsb arsw chyh gcdn";        // mot de passe d'application
    const QString host     = "smtp.gmail.com";
    const int     port     = 587;

    for (const client &clientData : liste)
    {
        QString emailDest = clientData.getEmail();
        QString prenom    = clientData.getPrenom();
        QString codePromo = genererCodePromo();

        QString body = QString(
                           "Bonjour %1,\n\n"
                           "Toute l'équipe OptiSmart te souhaite un très joyeux anniversaire !\n\n"
                           "Voici ton code promo exclusif :\n"
                           "%2\n\n"
                           "Valable 30 jours.\n\n"
                           "L'équipe OptiSmart "
                           ).arg(prenom, codePromo);

        Smtp* smtp = new Smtp(from, password, host, port);
        QEventLoop loop;   //  pour garder la boucle locale

        // On capture loop PAR RÉFÉRENCE et emailDest PAR VALEUR
        QObject::connect(smtp, &Smtp::envoiTermine, &loop, [emailDest, &loop]() {
            qDebug() << "EMAIL REÇU SUR GMAIL →" << emailDest;
            loop.quit();
        });

        QObject::connect(smtp, &Smtp::errorReceived, &loop, [emailDest, &loop]() {
            qDebug() << "Échec envoi vers" << emailDest;
            loop.quit();
        });

        qDebug() << "Envoi Gmail vers :" << emailDest;
        smtp->sendMail(from, emailDest, "Joyeux anniversaire !", body);

        loop.exec();   // attend vraiment la fin

        delete smtp;   // propre
    }

    qDebug() << "Tous les emails d'anniversaire envoyés avec succès !";
}

int client::joursRestantsAnniversaire() const
{
    QDate today = QDate::currentDate();
    QDate dateN = QDate::fromString(this->date_naissance, "dd/MM/yyyy");
    if (!dateN.isValid()) return 9999;

    QDate prochainAniv(today.year(), dateN.month(), dateN.day());
    if (prochainAniv < today)
        prochainAniv = prochainAniv.addYears(1);

    return today.daysTo(prochainAniv);
}
// client.cpp

QSqlQueryModel* client::afficherTousClients()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT id_client, nom, prenom, date_naissance, email, "
                    "num_tel, date_inscri, point_fedelite FROM client "
                    "ORDER BY nom");
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Nom");
    model->setHeaderData(2, Qt::Horizontal, "Prénom");
    model->setHeaderData(3, Qt::Horizontal, "Date Naissance");
    model->setHeaderData(4, Qt::Horizontal, "Email");
    model->setHeaderData(5, Qt::Horizontal, "Téléphone");
    model->setHeaderData(6, Qt::Horizontal, "Date Inscription");
    model->setHeaderData(7, Qt::Horizontal, "Points Fidélité");
    return model;
}

QSqlQueryModel* client::rechercherClientParId(int id)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT id_client, nom, prenom, date_naissance, email, "
                  "num_tel, date_inscri, point_fedelite FROM client WHERE id_client = ?");
    query.addBindValue(id);
    query.exec();
    model->setQuery(query);
    return model;
}

QSqlQueryModel* client::trierClientsParNom()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT id_client, nom, prenom, date_naissance, email, "
                    "num_tel, date_inscri, point_fedelite FROM client ORDER BY nom ASC");
    return model;
}

QSqlQueryModel* client::trierClientsParPoints()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT id_client, nom, prenom, date_naissance, email, "
                    "num_tel, date_inscri, point_fedelite FROM client ORDER BY point_fedelite DESC");
    return model;
}

QMap<QString, int> client::getStatistiquesAge()
{
    QMap<QString, int> stats;
    stats["Moins de 25 ans"] = 0;
    stats["25 - 40 ans"] = 0;
    stats["40 - 60 ans"] = 0;
    stats["Plus de 60 ans"] = 0;

    QSqlQuery query("SELECT date_naissance FROM client");
    while (query.next()) {
        QDate dateNais = QDate::fromString(query.value(0).toString(), "dd/MM/yyyy");
        if (!dateNais.isValid())
            dateNais = QDate::fromString(query.value(0).toString(), "yyyy-MM-dd");

        if (!dateNais.isValid()) continue;

        int age = dateNais.daysTo(QDate::currentDate()) / 365.2425;

        if (age < 25) stats["Moins de 25 ans"]++;
        else if (age < 40) stats["25 - 40 ans"]++;
        else if (age < 60) stats["40 - 60 ans"]++;
        else stats["Plus de 60 ans"]++;
    }
    return stats;
}
QPair<QString, int> client::rechercherNomEtPointsParId(int id_client) const
{
    QSqlQuery query;
    query.prepare("SELECT NOM, POINT_FEDELITE FROM client WHERE ID_CLIENT = :id");
    query.bindValue(":id", id_client);

    if (query.exec() && query.next()) {
        QString nom = query.value("NOM").toString();
        int points = query.value("POINT_FEDELITE").toInt();
        return qMakePair(nom, points);
    }
    return qMakePair(QString("INCONNU"), 0); // client non trouvé
}





