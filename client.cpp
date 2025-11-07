   /* #include "client.h"

client::client(Ui::optismart *ui, QWidget *parent)
    : QWidget(parent), ui(ui)
{
    connect(ui->bajouter_c, &QPushButton::clicked, this, &client::ajouterClient);
    connect(ui->bmodifier_c, &QPushButton::clicked, this, &client::modifierClient);
    connect(ui->bsupprimer_c, &QPushButton::clicked, this, &client::supprimerClient);
    connect(ui->bexporter_c, &QPushButton::clicked, this, &client::exporterPdf);
    connect(ui->bstatistique_c, &QPushButton::clicked, this, &client::afficherStatistiques);
}

client::~client() {}

void client::chargerDonnees() {}
void client::ajouterClient() {}
void client::modifierClient() {}
void client::supprimerClient() {}
void client::rechercherClient(const QString &) {}
void client::exporterPdf() {}
void client::afficherStatistiques() {}*/
#include "client.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVariant>
#include <QMessageBox>
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

