#ifndef GFOURNISSEUR_H
#define GFOURNISSEUR_H

#include <QMainWindow>
#include "fournisseur.h"
#include <QChartView>
#include <QPieSeries>
#include <QChart>
#include <QGraphicsScene>
#include <QQuickWidget>
#include <QQuickItem>  // IMPORTANT POUR QT 6
#include <QQmlContext>
#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class gfournisseur;
}
QT_END_NAMESPACE

class gfournisseur : public QMainWindow
{
    Q_OBJECT

public:
    gfournisseur(QWidget *parent = nullptr);
    ~gfournisseur();

private slots:
    void on_bajouter_f_clicked();
    void on_bsupprimer_f_clicked();
    void on_bmodifier_f_clicked();

    // Validation en temps réel
    void on_nom_le_textChanged(const QString &text);
    void on_email_le_textChanged(const QString &text);
    void on_telephone_le_textChanged(const QString &text);
    void on_cp_le_textChanged(const QString &text);

    // Fonctionnalités avancées
    void on_bstatistique_f_clicked();
    void on_bexporter_f_clicked();
    void on_btrier_f_clicked();
    void on_brechercher_f_clicked();
    void on_bnouveau_f_clicked();
    void on_tableWidget_4_itemClicked(QTableWidgetItem *item);

    // NOUVEAU : Carte des fournisseurs
    void on_bcarte_f_clicked();

private:
    Ui::gfournisseur *ui;
    fournisseur fourn;

    // Carte QML
    QQuickWidget *m_mapWidget;
    QDialog *m_mapDialog;

    void actualiserAffichage();
    void clearFields();
    void afficherGraphiqueStatistiques();

    // Méthodes de validation
    bool validerNom(const QString &nom);
    bool validerEmail(const QString &email);
    bool validerTelephone(const QString &telephone);
    bool validerAdresse(const QString &adresse);
    bool validerConditionPaiement(const QString &condition);
    void afficherErreurChamp(QLineEdit *champ, bool estValide, const QString &message = "");
    void setupConditionPaiement();

    // NOUVELLE MÉTHODE POUR LA CARTE
    void setupCarte();
};

#endif // GFOURNISSEUR_H
