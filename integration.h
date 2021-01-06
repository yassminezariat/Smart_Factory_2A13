#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <QMainWindow>
#include"employe.h"
#include"grade.h"
#include <QMessageBox>
#include"grade.h"
#include<QValidator>
#include"statistiques.h"
#include"client.h"
#include"facture.h"
#include<QMessageBox>
#include<QValidator>
#include "statistiquesfact.h"
#include<QPrinter>
#include<QPrintDialog>
#include"arduino.h"
#include"intervenant.h"
#include"equipement.h"
#include <QMediaPlayer>
namespace Ui {
class integration;
}

class integration : public QMainWindow
{
    Q_OBJECT

public:
    explicit integration(QWidget *parent = nullptr);
    ~integration();
    bool login(QString,QString);
private slots:

    void on_actionajoutergrade_triggered();

    void on_actionsupprimergrade_triggered();

    void on_actionmodifiergrade_triggered();

    void on_actionrecherchergrade_triggered();

    void on_actionajouteremploye_triggered();

    void on_actionsupprimeremploye_triggered();

    void on_actionmodifieremploye_triggered();

    void on_actionrechercheremploye_triggered();

    void on_actionstatistiqueemploye_triggered();

    void on_tabWidget_2_currentChanged(int index);

    void on_actionajouterclient_triggered();

    void on_actionsupprimerclient_triggered();

    void on_actionmodifierclient_triggered();

    void on_actionrechercherclient_triggered();

    void on_actionajouterfacture_triggered();

    void on_actionsupprimerfacture_triggered();

    void on_actionmodifierfacture_triggered();

    void on_actionrechercherfacture_triggered();

    void on_actionstatistiquefacture_triggered();

    void on_actionimprimerfacture_triggered();

    void on_tabWidget_4_currentChanged(int index);

    void on_lineEdit_rechercher_emp_2_textChanged(const QString &arg1);

    void on_checkBox_salaire_stateChanged(int arg1);

    void on_checkBox_grade2_stateChanged(int arg1);

    void on_checkBox_nombre_stateChanged(int arg1);

    void on_recherche_client_textChanged(const QString &arg1);

    void on_filtrer_client_textChanged(const QString &arg1);

    void update_label();

    void on_actionAI_triggered();

    void on_actionMI_triggered();

    void on_actionSI_triggered();

    void on_actionME_triggered();

    void on_actionSE_triggered();

    void on_actionAE_triggered();

    void on_actionRE_triggered();

    void on_actionRI_triggered();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    //void on_aj_triggered();

    //void on_mo_triggered();

    //void on_su_triggered();

    //void on_tableView_3_activated(const QModelIndex &index);

    void on_pushButton_5_clicked();

    void on_actionimprimerEMP_triggered();

    void on_stat_currentChanged(int index);

    void on_actualiser_stat_emp_clicked();

    void on_actualiser_stat_fact_clicked();

    void on_lineEdit_rechercher_emp_textChanged(const QString &arg1);

private:

    Ui::integration *ui;
    employe tmpemploye;//bech nesta3melha par defaut
    grade    tmpgrade;
    client tmpclient;
    facture tmpfacture;
    intervenant I;
    equipement E ;
    arduino A;
    QString data;
     facture f;
     QString c="";
     bool test=false;

    //commande tmpcmd;
QMediaPlayer* Player;
   // reclamation tmprc;
};

#endif // INTEGRATION_H
