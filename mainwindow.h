#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"employe.h"
#include"grade.h"
#include <QMessageBox>
#include"grade.h"
#include<QValidator>
#include"statistiques.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionajouterEmploye_triggered();

    void on_actionsupprimerEmp_triggered();

    void on_actionrechercher_e_triggered();

    void on_actionmodifierEmploye_triggered();

    void on_actionajouterGrade_triggered();

    void on_actionajoutergrade_triggered();


    
    void on_actionsupGrade_triggered();
    
    void on_actionsupprimergrade_triggered();

    void on_actionrecherchergrade_triggered();

    void on_tabWidget_currentChanged(int index);

    void on_comboBox_idgrade_currentTextChanged(const QString &arg1);

    void on_id_e_textChanged(const QString &arg1);

    void on_lineEdit_rechercher_emp_textChanged(const QString &arg1);

    void on_actionstatistique_triggered();

    void on_actionmodifiergrade_triggered();

    void on_checkBox_salaire_stateChanged(int arg1);

    void on_checkBox_grade2_stateChanged(int arg1);

    void on_checkBox_nombre_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    employe tmpemploye;//bech nesta3melha par defaut
    grade    tmpgrade;
};
#endif // MAINWINDOW_H
