#ifndef CLIENT_H
#define CLIENT_H

#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QWidget>



class client
{

private:
    int id_client;
    QString nom;
    QString prenom;
    QString date_naissance;
    QString email;
    int num_tel;
    QString date_inscri;
    int  point_fedelite;



public:
    //constructeurs
    client(){}
    client(int,QString,QString,QString,QString,int,QString,int);
    //getters
    int getId()  { return id_client; }
    QString getNom() { return nom; }
    QString getPrenom()  { return prenom; }
    QString getDate_naissance()  { return date_naissance; }
    QString getEmail()  { return email; }
    int getNumTel()  { return num_tel; }
    int getPoint_fedelite()  { return point_fedelite; }
    //setterss
    void setId(int id){this->id_client=id;}
    void setNom(QString n) {nom=n;}
    void setPrenom(QString p) {prenom=p;}
    void setDate_naissance(QString dn) {date_naissance=dn;}
    void setEmail(QString e) {email=e;}
    void setNum_tel(int t){this->num_tel=t;}
    void setDate_inscri(QString di) {date_inscri=di;}
    //fonctionnalités
    bool ajouter_client();
    QSqlQueryModel * afficher_client();
    bool supprimer_client(int);
    bool modifier_client(int id_client, QString nom, QString prenom, QString date_naissance,QString email, int num_tel, QString date_inscri, int point_fedelite);

    QSqlQueryModel * trier_client ();
    QSqlQueryModel * rechercher_client ();
    bool exporter_client();
    void retour_client();


};
#endif // CLIENT_H
