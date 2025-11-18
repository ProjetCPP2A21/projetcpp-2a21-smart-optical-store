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
    model->setHeaderData(7, Qt::Horizontal, "Points Fidélité");

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
/*bool client::exporter_client_pdf()
{
    QPdfWriter pdf("clients.pdf");
    QPainter painter(&pdf);
    int i = 4000;

    QFont titleFont("Arial", 18, QFont::Bold);
    painter.setFont(titleFont);
    painter.drawText(2200, 1500, "Liste des Clients");

    painter.setPen(Qt::black);
    painter.drawRect(1000, 2000, 7000, 500); // cadre pour l'entête

    painter.drawText(1200, 2300, "ID");
    painter.drawText(1800, 2300, "Nom");
    painter.drawText(3000, 2300, "Prénom");
    painter.drawText(4300, 2300, "Téléphone");
    painter.drawText(6000, 2300, "Email");

    QSqlQuery query;
    query.prepare("SELECT id, nom, prenom, telephone, email FROM client");
    query.exec();

    while (query.next()) {
        painter.drawText(1200, i, query.value(0).toString());
        painter.drawText(1800, i, query.value(1).toString());
        painter.drawText(3000, i, query.value(2).toString());
        painter.drawText(4300, i, query.value(3).toString());
        painter.drawText(6000, i, query.value(4).toString());
        i = i + 500;
    }

    painter.end();
    return true;
}
*/
/*bool client::exporter_client_pdf()
{
    // 🔹 Ouvrir une boîte de dialogue pour choisir le chemin et le nom du fichier PDF
    QString fileName = QFileDialog::getSaveFileName(nullptr,
                                                    "Enregistrer PDF",
                                                    "clients.pdf",
                                                    "*.pdf");
    if (fileName.isEmpty()) {
        QMessageBox::warning(nullptr, "Annulé", "Exportation annulée !");
        return false;
    }

    // 🔹 Créer le QPdfWriter
    QPdfWriter pdf(fileName);
    pdf.setPageSize(QPageSize(QPageSize::A4));
    QPainter painter(&pdf);

    // 🔹 Ajouter un titre
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.drawText(200, 100, "Liste des Clients");

    // 🔹 Requête SQL pour récupérer les clients
    QSqlQuery query("SELECT id_client, nom, prenom, date_naissance, email, num_tel, date_inscri, point_fedelite FROM client");

    int y = 150; // position verticale pour commencer le tableau
    painter.setFont(QFont("Arial", 12));

    // 🔹 En-têtes de colonnes
    painter.drawText(50, y, "ID");
    painter.drawText(100, y, "Nom");
    painter.drawText(200, y, "Prenom");
    painter.drawText(300, y, "Date Naissance");
    painter.drawText(420, y, "Email");
    painter.drawText(550, y, "Tel");
    painter.drawText(650, y, "Date Inscription");
    painter.drawText(780, y, "Points");

    y += 30;

    // 🔹 Parcourir les résultats
    while (query.next()) {
        painter.drawText(50, y, query.value(0).toString());
        painter.drawText(100, y, query.value(1).toString());
        painter.drawText(200, y, query.value(2).toString());
        painter.drawText(300, y, query.value(3).toString());
        painter.drawText(420, y, query.value(4).toString());
        painter.drawText(550, y, query.value(5).toString());
        painter.drawText(650, y, query.value(6).toString());
        painter.drawText(780, y, query.value(7).toString());

        y += 30;

        // 🔹 Si on arrive en bas de page, créer une nouvelle page
        if (y > pdf.height() - 50) {
            pdf.newPage();
            y = 100; // recommencer en haut de la nouvelle page
        }
    }

    painter.end();

    QMessageBox::information(nullptr, "Exportation PDF", "✅ Exportation réussie !");
    return true;
}*/
bool client::exporter_client_pdf(const QString &fichier)
{
    // 🔹 Récupérer les données de la table client
    QSqlQuery query;
    if (!query.exec("SELECT id_client, nom, prenom, date_naissance, email, num_tel, date_inscri, point_fedelite FROM client ORDER BY id_client")) {
        QMessageBox::critical(nullptr, "Erreur SQL", query.lastError().text());
        return false;
    }

    // 🔹 Générer le HTML
    QString now = QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm");
    QString html = "<html><head><meta charset='utf-8'><style>"
                   "body{font-family:Arial,Helvetica,sans-serif;}"
                   "table{width:100%;border-collapse:collapse;}"
                   "th,td{border:1px solid #888;padding:6px;text-align:left;}"
                   "th{background:#f0f0f0;}"
                   "tr:nth-child(even){background:#fafafa;}"
                   "</style></head><body>";
    html += "<h2>Liste des clients</h2><p>Généré le " + now + "</p><table>";
    html += "<tr><th>ID</th><th>Nom</th><th>Prénom</th><th>Date Naissance</th><th>Email</th><th>Téléphone</th><th>Date Inscription</th><th>Points Fidélité</th></tr>";

    while (query.next()) {
        html += "<tr>";
        for (int i = 0; i < 8; ++i)
            html += "<td>" + query.value(i).toString().toHtmlEscaped() + "</td>";
        html += "</tr>";
    }
    html += "</table></body></html>";

    // 🔹 Définir le chemin du fichier
    QString outputPath = fichier;
    if (outputPath.isEmpty()) {
        outputPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/clients.pdf";
    }
    if (QFileInfo(outputPath).suffix().toLower() != "pdf")
        outputPath += ".pdf";

    // 🔹 Créer le PDF
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

