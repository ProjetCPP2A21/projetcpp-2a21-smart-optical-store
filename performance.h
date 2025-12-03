#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include <QString>
#include <QSqlQueryModel>
#include <QDate>

class Performance
{
public:
    Performance();
    Performance(int idEmploye, int mois, int annee,
                int nbVentes, int nbRetards, double noteResp);

    // Getters / setters (tu peux en rajouter si besoin)
    int getIdPerf() const;
    int getIdEmploye() const;
    int getMois() const;
    int getAnnee() const;
    int getNbVentes() const;
    int getNbRetards() const;
    double getNoteResp() const;
    double getScoreGlobal() const;
    double getPrimeCalculee() const;

    void setNbVentes(int nbVentes);
    void setNbRetards(int nbRetards);
    void setNoteResp(double note);

    // Métiers
    bool calculerScoreEtPrime(double primeMax = 300.0);  // calcule SCORE_GLOBAL + PRIME
    bool ajouter();                                      // INSERT
    bool mettreAJour();                                  // UPDATE de la ligne existante

    // Affichages
    static QSqlQueryModel* afficherParMois(int mois, int annee);
    static QSqlQueryModel* afficherParEmploye(int idEmploye);

    // Utilitaires
    static bool existePour(int idEmploye, int mois, int annee);
    static bool chargerPour(int idEmploye, int mois, int annee, Performance &perf);

private:
    int idPerf;
    int idEmploye;
    int mois;
    int annee;
    int nbVentes;
    int nbRetards;
    double noteResp;
    double scoreGlobal;
    double primeCalculee;
};

#endif // PERFORMANCE_H
