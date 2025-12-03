#include "planninghoraire.h"
#include <QSqlQuery>
#include <QVariant>
#include <QString>

PlanningHoraire::PlanningHoraire()
    : idPlanning(-1),
    idEmploye(0),
    dateJour(QDate::currentDate()),
    shift("MATIN"),
    heureDebut("08:00"),
    heureFin("12:00")
{
}

PlanningHoraire::PlanningHoraire(int idEmploye, const QDate &dateJour,
                                 const QString &shift,
                                 const QString &heureDebut,
                                 const QString &heureFin)
    : idPlanning(-1),
    idEmploye(idEmploye),
    dateJour(dateJour),
    shift(shift),
    heureDebut(heureDebut),
    heureFin(heureFin)
{
}

// Getters
int PlanningHoraire::getIdPlanning() const { return idPlanning; }
int PlanningHoraire::getIdEmploye() const { return idEmploye; }
QDate PlanningHoraire::getDateJour() const { return dateJour; }
QString PlanningHoraire::getShift() const { return shift; }
QString PlanningHoraire::getHeureDebut() const { return heureDebut; }
QString PlanningHoraire::getHeureFin() const { return heureFin; }

// Setters
void PlanningHoraire::setHeureDebut(const QString &h) { heureDebut = h; }
void PlanningHoraire::setHeureFin(const QString &h) { heureFin = h; }

// Ajout d'un planning
bool PlanningHoraire::ajouter()
{
    QSqlQuery query;

    // Générer ID_PLANNING avec la séquence
    if (idPlanning == -1) {
        if (!query.exec("SELECT OPTISMART.SEQ_PLANNING.NEXTVAL FROM DUAL"))
            return false;
        if (query.next())
            idPlanning = query.value(0).toInt();
        else
            return false;
    }

    query.prepare(
        "INSERT INTO OPTISMART.PLANNING_HORAIRE "
        "(ID_PLANNING, ID_EMPLOYE, DATE_JOUR, SHIFT, HEURE_DEBUT, HEURE_FIN) "
        "VALUES (:id_planning, :id_emp, :date_jour, :shift, :h_deb, :h_fin)"
        );

    query.bindValue(":id_planning", idPlanning);
    query.bindValue(":id_emp", idEmploye);
    query.bindValue(":date_jour", dateJour);
    query.bindValue(":shift", shift);
    query.bindValue(":h_deb", heureDebut);
    query.bindValue(":h_fin", heureFin);

    return query.exec();
}

// Suppression d'un planning
bool PlanningHoraire::supprimer()
{
    if (idPlanning == -1)
        return false;

    QSqlQuery query;
    query.prepare("DELETE FROM OPTISMART.PLANNING_HORAIRE WHERE ID_PLANNING = :id");
    query.bindValue(":id", idPlanning);
    return query.exec();
}

// Afficher tous les shifts d'un employé
QSqlQueryModel* PlanningHoraire::afficherParEmploye(int idEmploye)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery(
        QString(
            "SELECT DATE_JOUR, SHIFT, HEURE_DEBUT, HEURE_FIN "
            "FROM OPTISMART.PLANNING_HORAIRE "
            "WHERE ID_EMPLOYE = %1 "
            "ORDER BY DATE_JOUR, SHIFT"
            ).arg(idEmploye)
        );

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Shift"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Début"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Fin"));

    return model;
}

// Afficher le planning d'un jour
QSqlQueryModel* PlanningHoraire::afficherParJour(const QDate &date)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString dateStr = date.toString("dd/MM/yyyy"); // Oracle peut accepter directement QDate aussi

    model->setQuery(
        QString(
            "SELECT e.ID_EMPLOYE, e.NOM, e.PRENOM, p.SHIFT, p.HEURE_DEBUT, p.HEURE_FIN "
            "FROM OPTISMART.EMPLOYE e "
            "JOIN OPTISMART.PLANNING_HORAIRE p "
            "  ON e.ID_EMPLOYE = p.ID_EMPLOYE "
            "WHERE TRUNC(p.DATE_JOUR) = TRUNC(TO_DATE('%1', 'DD/MM/YYYY')) "
            "ORDER BY p.SHIFT, p.HEURE_DEBUT"
            ).arg(dateStr)
        );

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Shift"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Début"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Fin"));

    return model;
}

// Afficher la semaine d'un employé (dateLundi = début de semaine)
QSqlQueryModel* PlanningHoraire::afficherSemaineEmploye(int idEmploye, const QDate &dateLundi)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    QDate fin = dateLundi.addDays(6); // lundi..dimanche

    QString dateDebStr = dateLundi.toString("dd/MM/yyyy");
    QString dateFinStr = fin.toString("dd/MM/yyyy");

    model->setQuery(
        QString(
            "SELECT DATE_JOUR, SHIFT, HEURE_DEBUT, HEURE_FIN "
            "FROM OPTISMART.PLANNING_HORAIRE "
            "WHERE ID_EMPLOYE = %1 "
            "  AND DATE_JOUR BETWEEN TO_DATE('%2','DD/MM/YYYY') "
            "                      AND TO_DATE('%3','DD/MM/YYYY') "
            "ORDER BY DATE_JOUR, SHIFT"
            ).arg(idEmploye).arg(dateDebStr).arg(dateFinStr)
        );

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Shift"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Début"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Fin"));

    return model;
}
