#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   QIntValidator *id_validator=new QIntValidator(1,999999);
    QIntValidator *tel_validator=new QIntValidator(10000000,99999999);
    ui->id_e->setValidator(id_validator);
    ui->id_grade->setValidator(id_validator);
    ui->nbr_heures->setValidator(id_validator);
    ui->sal_gr->setValidator(id_validator);
    ui->lineEdit_tele->setValidator(tel_validator);

    QBoxLayout *toolLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    toolLayout->addWidget(ui->toolBar);
   //ui->tab->setLayout(toolLayout);
    ui->Grades->setLayout(toolLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionajouterEmploye_triggered()
{
    employe e(ui->id_e_2->text().toInt(),ui->nom_e_2->text(),ui->prenom_e_2->text(),ui->date_n_e_2->date(),ui->email_e_2->text(),ui->lineEdit_tele_2->text().toInt(),ui->comboBox_idgrade_2->currentText().toInt());
    bool test=e.ajouter();
    if(test){
        QMessageBox::information(nullptr,QObject::tr("Employe"),QObject::tr("employe ajouté\n" "click ok to exit"),QMessageBox::Ok);
        ui->id_e_2->setText("");//bech ba3ed mankamel l ajout yarja3 a 0
        ui->nom_e_2->setText("");
        ui->prenom_e_2->setText("");
        ui->email_e_2->setText("");

        ui->table_employe_2->setModel(tmpemploye.afficher());//actualisation
    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("Employe"),QObject::tr("Erreur!\n" "click ok to exit"),QMessageBox::Ok);
    }
    qDebug() <<"clicked";
}

void MainWindow::on_actionsupprimerEmp_triggered()
{
    bool test=tmpemploye.supprimer(ui->id_e_2->text().toInt());
    if(test){
        QMessageBox::information(nullptr,QObject::tr("Employe"),QObject::tr("employe supprimé\n" "click ok to exit"),QMessageBox::Ok);
        ui->id_e_2->setText("");
        ui->table_employe_2->setModel(tmpemploye.afficher());
    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("Employe"),QObject::tr("Erreur!\n" "click ok to exit"),QMessageBox::Ok);
    }
}

void MainWindow::on_actionrechercher_e_triggered()
{
    employe e=tmpemploye.recherche_Id(ui->id_e_2->text().toInt());
    ui->nom_e_2->setText(e.Getnom());
    ui->prenom_e_2->setText(e.Getprenom());
    ui->email_e_2->setText(e.Getemail());
    ui->date_n_e_2->setDate(e.Getdate_naissance());

}

void MainWindow::on_actionmodifierEmploye_triggered()
{
    employe e(ui->id_e_2->text().toInt(),ui->nom_e_2->text(),ui->prenom_e_2->text(),ui->date_n_e_2->date(),ui->email_e_2->text(),ui->lineEdit_tele_2->text().toInt(),ui->comboBox_idgrade_2->currentText().toInt());
    bool test=e.modifier(ui->id_e->text().toInt());
    if(test){
        QMessageBox::information(nullptr,QObject::tr("Employe"),QObject::tr("employe modifié\n" "click ok to exit"),QMessageBox::Ok);
        ui->id_e_2->setText("");
        ui->nom_e_2->setText("");
        ui->prenom_e_2->setText("");
        ui->email_e_2->setText("");

        ui->table_employe_2->setModel(tmpemploye.afficher());
    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("Employe"),QObject::tr("Erreur!\n" "click ok to exit"),QMessageBox::Ok);
    }
}



void MainWindow::on_actionajoutergrade_triggered()
{

    grade G(ui->id_grade->text().toInt(),ui->sal_gr->text().toInt(),ui->status_grade->text(),ui->nbr_heures->text().toInt());
    bool test=G.ajouter();
    if(test){
        QMessageBox::information(nullptr,QObject::tr("GRADE"),QObject::tr("grade ajouté\n" "click ok to exit"),QMessageBox::Ok);
        ui->id_grade->setText("");//bech ba3ed mankamel l ajout yarja3 a 0
        ui->sal_gr->setText("");
        ui->status_grade->setText("");
        ui->nbr_heures->setText("");

        ui->table_grade->setModel(tmpgrade.afficher());//actualisation

        ui->comboBox_idgrade_2->clear();
        ui->comboBox_idgrade_2->addItems(tmpgrade.listegrade());
    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("GRADE"),QObject::tr("Erreur!\n" "click ok to exit"),QMessageBox::Ok);
    }
    qDebug() <<"clicked";
}


void MainWindow::on_actionsupprimergrade_triggered()
{
    bool test=tmpgrade.supprimer(ui->id_grade->text().toInt());
    if(test){
        QMessageBox::information(nullptr,QObject::tr("GRADE"),QObject::tr("Grade supprimé\n" "click ok to exit"),QMessageBox::Ok);
        ui->id_grade->setText("");
        ui->table_grade->setModel(tmpgrade.afficher());
    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("GRADE"),QObject::tr("Erreur!\n" "click ok to exit"),QMessageBox::Ok);
    }

}

void MainWindow::on_actionrecherchergrade_triggered()
{
    grade G=tmpgrade.recherche_Id(ui->id_grade->text().toInt());
    ui->status_grade->setText(G.Getstatut());
    ui->sal_gr->setText(QString::number(G.Getsalaire()));
    ui->nbr_heures->setText(QString::number(G.Getnb_heures()));

}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    ui->table_grade->setModel(tmpgrade.afficher());
    ui->table_employe_2->setModel(tmpemploye.afficher());

    ui->comboBox_idgrade_2->clear();
    ui->comboBox_idgrade_2->addItems(tmpgrade.listegrade());
}

void MainWindow::on_comboBox_idgrade_currentTextChanged(const QString &arg1)
{
    grade G=tmpgrade.recherche_Id(ui->comboBox_idgrade_2->currentText().toInt());
    ui->label_grade_2->setText(G.Getstatut());
}

void MainWindow::on_id_e_textChanged(const QString &arg1)
{
    employe e=tmpemploye.recherche_Id(ui->id_e->text().toInt());
    if(e.Getnom()!=""){
        ui->label_test_id_emp_2->setText("employe existe!");
    }
    else{
        ui->label_test_id_emp_2->setText("");
    }
}

void MainWindow::on_lineEdit_rechercher_emp_textChanged(const QString &arg1)
{
    bool nom=ui->checkBox_nom_2->isChecked();
    bool prenom=ui->checkBox_prenom_2->isChecked();
    bool grade=ui->checkBox_grade_2->isChecked();

    if((nom && prenom && grade) ||(!nom && !prenom && !grade)){
        ui->table_employe->setModel(tmpemploye.recherche(ui->lineEdit_rechercher_emp->text()));
    }
    else if(nom){
        if(prenom){
           ui->table_employe->setModel(tmpemploye.recherche_n_p(ui->lineEdit_rechercher_emp->text()));
        }
        else if(grade){
            ui->table_employe->setModel(tmpemploye.recherche_n_g(ui->lineEdit_rechercher_emp->text()));
        }
        else{
            ui->table_employe->setModel(tmpemploye.recherche_n(ui->lineEdit_rechercher_emp->text()));
        }
    }
    else if(prenom){
        if(grade){
            ui->table_employe->setModel(tmpemploye.recherche_p_g(ui->lineEdit_rechercher_emp->text()));
        }
        else{
            ui->table_employe->setModel(tmpemploye.recherche_p(ui->lineEdit_rechercher_emp->text()));
        }
    }
    else{
        ui->table_employe->setModel(tmpemploye.recherche_g(ui->lineEdit_rechercher_emp->text()));
    }
}

void MainWindow::on_actionstatistique_triggered()
{
    statistiques *s=new statistiques();
    s->show();
}

void MainWindow::on_actionmodifiergrade_triggered()
{
    grade G(ui->id_grade->text().toInt(),ui->sal_gr->text().toInt(),ui->status_grade->text(),ui->nbr_heures->text().toInt());
    bool test=G.modifier(ui->id_grade->text().toInt());
    if(test){
        QMessageBox::information(nullptr,QObject::tr("GRADE"),QObject::tr("grade modifié\n" "click ok to exit"),QMessageBox::Ok);
        ui->id_grade->setText("");//bech ba3ed mankamel l ajout yarja3 a 0
        ui->sal_gr->setText("");
        ui->status_grade->setText("");
        ui->nbr_heures->setText("");

        ui->table_grade->setModel(tmpgrade.afficher());//actualisation

        ui->comboBox_idgrade->clear();
        ui->comboBox_idgrade->addItems(tmpgrade.listegrade());
    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("GRADE"),QObject::tr("Erreur!\n" "click ok to exit"),QMessageBox::Ok);
    }
}



void MainWindow::on_checkBox_grade2_stateChanged(int arg1)
{
    bool grade=ui->checkBox_grade2->isChecked();
    bool salaire=ui->checkBox_salaire->isChecked();
    bool nombre=ui->checkBox_nombre->isChecked();
    if((grade && salaire && nombre) ||(!grade && !salaire && !nombre)){
        ui->table_grade->setModel(tmpgrade.tri());
    }
    else if(grade){
        if(salaire){
            ui->table_grade->setModel(tmpgrade.tri_g_S());
        }
        else if(nombre){
            ui->table_grade->setModel(tmpgrade.tri_g_N());
        }
        else{
            ui->table_grade->setModel(tmpgrade.tri_g());
        }
    }
    else if(salaire){
        if(nombre){
            ui->table_grade->setModel(tmpgrade.tri_S_N());
        }
        else{
            ui->table_grade->setModel(tmpgrade.tri_S());
        }
    }
    else{
        ui->table_grade->setModel(tmpgrade.tri_N());
    }
}

void MainWindow::on_checkBox_salaire_stateChanged(int arg1)
{
    bool grade=ui->checkBox_grade2->isChecked();
    bool salaire=ui->checkBox_salaire->isChecked();
    bool nombre=ui->checkBox_nombre->isChecked();
    if((grade && salaire && nombre) ||(!grade && !salaire && !nombre)){
        ui->table_grade->setModel(tmpgrade.tri());
    }
    else if(grade){
        if(salaire){
            ui->table_grade->setModel(tmpgrade.tri_g_S());
        }
        else if(nombre){
            ui->table_grade->setModel(tmpgrade.tri_g_N());
        }
        else{
            ui->table_grade->setModel(tmpgrade.tri_g());
        }
    }
    else if(salaire){
        if(nombre){
            ui->table_grade->setModel(tmpgrade.tri_S_N());
        }
        else{
            ui->table_grade->setModel(tmpgrade.tri_S());
        }
    }
    else{
        ui->table_grade->setModel(tmpgrade.tri_N());
    }
}

void MainWindow::on_checkBox_nombre_stateChanged(int arg1)
{
    bool grade=ui->checkBox_grade2->isChecked();
    bool salaire=ui->checkBox_salaire->isChecked();
    bool nombre=ui->checkBox_nombre->isChecked();
    if((grade && salaire && nombre) ||(!grade && !salaire && !nombre)){
        ui->table_grade->setModel(tmpgrade.tri());
    }
    else if(grade){
        if(salaire){
            ui->table_grade->setModel(tmpgrade.tri_g_S());
        }
        else if(nombre){
            ui->table_grade->setModel(tmpgrade.tri_g_N());
        }
        else{
            ui->table_grade->setModel(tmpgrade.tri_g());
        }
    }
    else if(salaire){
        if(nombre){
            ui->table_grade->setModel(tmpgrade.tri_S_N());
        }
        else{
            ui->table_grade->setModel(tmpgrade.tri_S());
        }
    }
    else{
        ui->table_grade->setModel(tmpgrade.tri_N());
    }
}

void MainWindow::on_lineEdit_rechercher_emp_2_textChanged(const QString &arg1)
{
    bool nom=ui->checkBox_nom_2->isChecked();
    bool prenom=ui->checkBox_prenom_2->isChecked();
    bool grade=ui->checkBox_grade_2->isChecked();

    if((nom && prenom && grade) ||(!nom && !prenom && !grade)){
        ui->table_employe_2->setModel(tmpemploye.recherche(ui->lineEdit_rechercher_emp_2->text()));
    }
    else if(nom){
        if(prenom){
           ui->table_employe_2->setModel(tmpemploye.recherche_n_p(ui->lineEdit_rechercher_emp_2->text()));
        }
        else if(grade){
            ui->table_employe_2->setModel(tmpemploye.recherche_n_g(ui->lineEdit_rechercher_emp_2->text()));
        }
        else{
            ui->table_employe_2->setModel(tmpemploye.recherche_n(ui->lineEdit_rechercher_emp_2->text()));
        }
    }
    else if(prenom){
        if(grade){
            ui->table_employe_2->setModel(tmpemploye.recherche_p_g(ui->lineEdit_rechercher_emp_2->text()));
        }
        else{
            ui->table_employe_2->setModel(tmpemploye.recherche_p(ui->lineEdit_rechercher_emp_2->text()));
        }
    }
    else{
        ui->table_employe_2->setModel(tmpemploye.recherche_g(ui->lineEdit_rechercher_emp_2->text()));
    }
}

void MainWindow::on_comboBox_idgrade_2_currentTextChanged(const QString &arg1)
{
    grade G=tmpgrade.recherche_Id(ui->comboBox_idgrade_2->currentText().toInt());
    ui->label_grade_2->setText(G.Getstatut());
}


