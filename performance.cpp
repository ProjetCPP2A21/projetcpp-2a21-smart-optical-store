#include "performance.h"
#include <QSqlQuery>
#include <QVariant>
#include <QtMath>

Performance::Performance()
    : idPerf(-1),
    idEmploye(0),
    mois(0),
    annee(0),
    nbVentes(0),
    nbRetards(0),
    noteResp(0.0),
    scoreGlobal(0.0),
    primeCalculee(0.0)
{
}

Performance::Performance(int idEmploye, int mois, int annee,
                         int nbVentes, int nbRetards, double noteResp)
    : idPerf(-1),
    idEmploye(idEmploye),
    mois(mois),
    annee(annee),
    nbVentes(nbVentes),
    nbRetards(nbRetards),
    noteResp(noteResp),
    scoreGlobal(0.0),
    primeCalculee(0.0)
{
}

// ===== Getters =====
int Performance::getIdPerf() const { return idPerf; }
int Performance::getIdEmploye() const { return idEmploye; }
int Performance::getMois() const { return mois; }
int Performance::getAnnee() const { return annee; }
int Performance::getNbVentes() const { return nbVentes; }
int Performance::getNbRetards() const { return nbRetards; }
double Performance::getNoteResp() const { return noteResp; }
double Performance::getScoreGlobal() const { return scoreGlobal; }
double Performance::getPrimeCalculee() const { return primeCalculee; }

// ===== Setters =====
void Performance::setNbVentes(int v) { nbVentes = v; }
void Performance::setNbRetards(int r) { nbRetards = r; }
void Performance::setNoteResp(double n) { noteResp = n; }

// ===== MÉTIER : calcul du score et de la prime =====
bool Performance::calculerScoreEtPrime(double primeMax)
{
    // Normalisation des ventes sur [0, 1] avec 100 = plafond
    double scoreVentes = nbVentes / 100.0;
    if (scoreVentes > 1.0) scoreVentes = 1.0;
    if (scoreVentes < 0.0) scoreVentes = 0.0;

    // Note du responsable (0..10) -> [0, 1]
    double scoreNote = noteResp / 10.0;
    if (scoreNote > 1.0) scoreNote = 1.0;
    if (scoreNote < 0.0) scoreNote = 0.0;

    // Pénalité sur les retards : 0.05 par retard
    double penalite = nbRetards * 0.05;

    // Score global avec pondération
    scoreGlobal = 0.5 * scoreVentes + 0.4 * scoreNote - penalite;

    if (scoreGlobal < 0.0) scoreGlobal = 0.0;
    if (scoreGlobal > 1.0) scoreGlobal = 1.0;

    primeCalculee = scoreGlobal * primeMax;
    return true;
}

// ===== INSERT =====
bool Performance::ajouter()
{
    QSqlQuery query;

    // Récupérer un nouvel ID via la séquence SEQ_PERF
    if (idPerf == -1) {
        if (!query.exec("SELECT OPTISMART.SEQ_PERF.NEXTVAL FROM DUAL")) {
            return false;
        }
        if (query.next()) {
            idPerf = query.value(0).toInt();
        } else {
            return false;
        }
    }

    query.prepare(
        "INSERT INTO OPTISMART.PERFORMANCE "
        "(ID_PERF, ID_EMPLOYE, MOIS, ANNEE, NB_VENTES, NB_RETARDS, "
        " NOTE_RESP, SCORE_GLOBAL, PRIME_CALCULEE) "
        "VALUES (:id_perf, :id_emp, :mois, :annee, :nbv, :nbr, "
        "        :note, :score, :prime)"
        );

    query.bindValue(":id_perf", idPerf);
    query.bindValue(":id_emp", idEmploye);
    query.bindValue(":mois", mois);
    query.bindValue(":annee", annee);
    query.bindValue(":nbv", nbVentes);
    query.bindValue(":nbr", nbRetards);
    query.bindValue(":note", noteResp);
    query.bindValue(":score", scoreGlobal);
    query.bindValue(":prime", primeCalculee);

    return query.exec();
}

// ===== UPDATE =====
bool Performance::mettreAJour()
{
    if (idPerf == -1)
        return false;

    QSqlQuery query;
    query.prepare(
        "UPDATE OPTISMART.PERFORMANCE "
        "SET NB_VENTES = :nbv, "
        "    NB_RETARDS = :nbr, "
        "    NOTE_RESP = :note, "
        "    SCORE_GLOBAL = :score, "
        "    PRIME_CALCULEE = :prime "
        "WHERE ID_PERF = :id_perf"
        );

    query.bindValue(":nbv", nbVentes);
    query.bindValue(":nbr", nbRetards);
    query.bindValue(":note", noteResp);
    query.bindValue(":score", scoreGlobal);
    query.bindValue(":prime", primeCalculee);
    query.bindValue(":id_perf", idPerf);

    return query.exec();
}

// ===== Vérifier si une performance existe déjà pour (employé, mois, année) =====
bool Performance::existePour(int idEmploye, int mois, int annee)
{
    QSqlQuery query;
    query.prepare(
        "SELECT COUNT(*) FROM OPTISMART.PERFORMANCE "
        "WHERE ID_EMPLOYE = :id_emp "
        "  AND MOIS = :mois "
        "  AND ANNEE = :annee"
        );
    query.bindValue(":id_emp", idEmploye);
    query.bindValue(":mois", mois);
    query.bindValue(":annee", annee);

    if (!query.exec())
        return false;

    if (query.next()) {
        int count = query.value(0).toInt();
        return (count > 0);
    }

    return false;
}

// ===== Charger une performance existante =====
bool Performance::chargerPour(int idEmp, int m, int a, Performance &perf)
{
    QSqlQuery query;
    query.prepare(
        "SELECT ID_PERF, ID_EMPLOYE, MOIS, ANNEE, NB_VENTES, NB_RETARDS, "
        "       NOTE_RESP, SCORE_GLOBAL, PRIME_CALCULEE "
        "FROM OPTISMART.PERFORMANCE "
        "WHERE ID_EMPLOYE = :id_emp "
        "  AND MOIS = :mois "
        "  AND ANNEE = :annee"
        );
    query.bindValue(":id_emp", idEmp);
    query.bindValue(":mois", m);
    query.bindValue(":annee", a);

    if (!query.exec())
        return false;

    if (query.next()) {
        perf.idPerf        = query.value("ID_PERF").toInt();
        perf.idEmploye     = query.value("ID_EMPLOYE").toInt();
        perf.mois          = query.value("MOIS").toInt();
        perf.annee         = query.value("ANNEE").toInt();
        perf.nbVentes      = query.value("NB_VENTES").toInt();
        perf.nbRetards     = query.value("NB_RETARDS").toInt();
        perf.noteResp      = query.value("NOTE_RESP").toDouble();
        perf.scoreGlobal   = query.value("SCORE_GLOBAL").toDouble();
        perf.primeCalculee = query.value("PRIME_CALCULEE").toDouble();
        return true;
    }

    return false;
}

// ===== Afficher par mois / année =====
QSqlQueryModel* Performance::afficherParMois(int mois, int annee)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery(
        QString(
            "SELECT e.ID_EMPLOYE, e.NOM, e.PRENOM, "
            "       p.NB_VENTES, p.NB_RETARDS, p.NOTE_RESP, "
            "       p.SCORE_GLOBAL, p.PRIME_CALCULEE "
            "FROM OPTISMART.EMPLOYE e "
            "JOIN OPTISMART.PERFORMANCE p "
            "  ON e.ID_EMPLOYE = p.ID_EMPLOYE "
            "WHERE p.MOIS = %1 AND p.ANNEE = %2"
            ).arg(mois).arg(annee)
        );

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Ventes"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Retards"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Note"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Score"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Prime (DT)"));

    return model;
}

// ===== Afficher toutes les performances d'un employé =====
QSqlQueryModel* Performance::afficherParEmploye(int idEmploye)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery(
        QString(
            "SELECT MOIS, ANNEE, NB_VENTES, NB_RETARDS, NOTE_RESP, "
            "       SCORE_GLOBAL, PRIME_CALCULEE "
            "FROM OPTISMART.PERFORMANCE "
            "WHERE ID_EMPLOYE = %1 "
            "ORDER BY ANNEE DESC, MOIS DESC"
            ).arg(idEmploye)
        );

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Mois"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Année"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Ventes"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Retards"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Note"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Score"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Prime (DT)"));

    return model;
}
