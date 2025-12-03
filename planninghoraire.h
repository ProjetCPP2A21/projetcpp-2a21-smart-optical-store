#ifndef PLANNINGHORAIRE_H
#define PLANNINGHORAIRE_H

#include <QDate>
#include <QString>
#include <QSqlQueryModel>

class PlanningHoraire
{
public:
    PlanningHoraire();
    PlanningHoraire(int idEmploye, const QDate &dateJour,
                    const QString &shift,
                    const QString &heureDebut,
                    const QString &heureFin);

    int getIdPlanning() const;
    int getIdEmploye() const;
    QDate getDateJour() const;
    QString getShift() const;
    QString getHeureDebut() const;
    QString getHeureFin() const;

    void setHeureDebut(const QString &h);
    void setHeureFin(const QString &h);

    bool ajouter();          // INSERT dans PLANNING_HORAIRE
    bool supprimer();        // DELETE par ID_PLANNING

    // Affichages
    static QSqlQueryModel* afficherParEmploye(int idEmploye);
    static QSqlQueryModel* afficherParJour(const QDate &date);
    static QSqlQueryModel* afficherSemaineEmploye(int idEmploye, const QDate &dateLundi);

private:
    int idPlanning;
    int idEmploye;
    QDate dateJour;
    QString shift;
    QString heureDebut;
    QString heureFin;
};

#endif // PLANNINGHORAIRE_H
