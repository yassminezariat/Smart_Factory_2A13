#include "integration.h"
#include "ui_integration.h"
#include<QToolBar>
integration::integration(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::integration)
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
    ui->Grades->setLayout(toolLayout);

    QBoxLayout *toolLayout1 = new QBoxLayout(QBoxLayout::TopToBottom, this);
    toolLayout1->addWidget(ui->toolBar_2);
    ui->Employes->setLayout(toolLayout1);

    QBoxLayout *toolLayout2 = new QBoxLayout(QBoxLayout::TopToBottom, this);
    toolLayout2->addWidget(ui->toolBar_3);
    ui->tab_3->setLayout(toolLayout2);

    QBoxLayout *toolLayout3 = new QBoxLayout(QBoxLayout::TopToBottom, this);
    toolLayout3->addWidget(ui->toolBar_4);
    ui->tab_4->setLayout(toolLayout3);

    QBoxLayout *toolLayout4 = new QBoxLayout(QBoxLayout::TopToBottom, this);
    toolLayout4->addWidget(ui->toolBar_7);
    ui->tab_7->setLayout(toolLayout4);

    QBoxLayout *toolLayout5 = new QBoxLayout(QBoxLayout::TopToBottom, this);
    toolLayout5->addWidget(ui->toolBar_6);
    ui->tab_8->setLayout(toolLayout5);



     //setCentralWidget( this);
     //move(0,100);
    //toolLayout5->setFixedSize(150, 150);
   // QRect( QBoxLayout &toolLayout, QBoxLayout &bottomRight);
   //toolLayout->setGeometry(0,0,1011,491);

    int result=A.connect_arduino(); // lancer la connexion � arduino
        switch(result){
        case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
            break;
        case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
           break;
        case(-1):qDebug() << "arduino is not available";
        }
         QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
         //le slot update_label suite � la reception du signal readyRead (reception des donn�es).


}

integration::~integration()
{
    delete ui;
}


void integration::update_label()
{

    data=A.read_from_arduino();
    if (c.length()+data.length()>11)
    {int j=0;
        for (int i=c.length();i<11;i++)
        {
            c[i]=data[j];
            j++;
        }
    test=true;
    }
    else
    {
        c+=data;
    }

    A.write_to_arduino(tmpemploye.getEmployeCarte(c).toStdString().c_str());
    ui->carte_e->setText(c);
    if(test)
    {

        test=false;
        c="";
    }
    if(c.length()==11){
        ui->carte_e->setText(c);
    }
    qDebug()<<c;
}
bool integration::login(QString username,QString password){
    QSqlQuery query;
    query.prepare("select * from login where username=:username and password=:password ");
    query.bindValue(":username",username);
    query.bindValue(":password",password);
    query.exec();
    int total=0;
    while(query.next()){
        total++;
    }
    if(total!=0){
        return true;
    }
    else{
        return false;
    }
}


void integration::on_actionajoutergrade_triggered()
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

        ui->comboBox_idgrade->clear();
        ui->comboBox_idgrade->addItems(tmpgrade.listegrade());
    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("GRADE"),QObject::tr("Erreur!\n" "click ok to exit"),QMessageBox::Ok);
    }
}

void integration::on_actionsupprimergrade_triggered()
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

void integration::on_actionmodifiergrade_triggered()
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

void integration::on_actionrecherchergrade_triggered()
{
    grade G=tmpgrade.recherche_Id(ui->id_grade->text().toInt());
    ui->status_grade->setText(G.Getstatut());
    ui->sal_gr->setText(QString::number(G.Getsalaire()));
    ui->nbr_heures->setText(QString::number(G.Getnb_heures()));
}

void integration::on_actionajouteremploye_triggered()
{
    employe e(ui->id_e->text().toInt(),ui->nom_e->text(),ui->prenom_e->text(),ui->date_n_e->date(),ui->email_e->text(),ui->lineEdit_tele->text().toInt(),ui->comboBox_idgrade->currentText().toInt(),ui->carte_e->text());
    bool test=e.ajouter();
    if(test){
        QMessageBox::information(nullptr,QObject::tr("Employe"),QObject::tr("employe ajouté\n" "click ok to exit"),QMessageBox::Ok);
        ui->id_e->setText("");//bech ba3ed mankamel l ajout yarja3 a 0
        ui->nom_e->setText("");
        ui->prenom_e->setText("");
        ui->email_e->setText("");
        ui->carte_e->setText("");

        ui->table_employe->setModel(tmpemploye.afficher());//actualisation
    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("Employe"),QObject::tr("Erreur!\n" "click ok to exit"),QMessageBox::Ok);
    }

}


void integration::on_actionsupprimeremploye_triggered()
{
    bool test=tmpemploye.supprimer(ui->id_e->text().toInt());
    if(test){
        QMessageBox::information(nullptr,QObject::tr("Employe"),QObject::tr("employe supprimé\n" "click ok to exit"),QMessageBox::Ok);
        ui->id_e->setText("");
        ui->table_employe->setModel(tmpemploye.afficher());
    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("Employe"),QObject::tr("Erreur!\n" "click ok to exit"),QMessageBox::Ok);
    }
}


void integration::on_actionmodifieremploye_triggered()
{
    employe e(ui->id_e->text().toInt(),ui->nom_e->text(),ui->prenom_e->text(),ui->date_n_e->date(),ui->email_e->text(),ui->lineEdit_tele->text().toInt(),ui->comboBox_idgrade->currentText().toInt(),ui->carte_e->text());
    bool test=e.modifier(ui->id_e->text().toInt());
    if(test){
        QMessageBox::information(nullptr,QObject::tr("Employe"),QObject::tr("employe modifié\n" "click ok to exit"),QMessageBox::Ok);
        ui->id_e->setText("");
        ui->nom_e->setText("");
        ui->prenom_e->setText("");
        ui->email_e->setText("");

        ui->table_employe->setModel(tmpemploye.afficher());
    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("Employe"),QObject::tr("Erreur!\n" "click ok to exit"),QMessageBox::Ok);
    }
}

void integration::on_actionrechercheremploye_triggered()
{
    employe e=tmpemploye.recherche_Id(ui->id_e->text().toInt());
    ui->nom_e->setText(e.Getnom());
    ui->prenom_e->setText(e.Getprenom());
    ui->email_e->setText(e.Getemail());
    ui->date_n_e->setDate(e.Getdate_naissance());
    ui->lineEdit_tele->setText(QString::number(e.Gettel()));
}

void integration::on_actionstatistiqueemploye_triggered()
{
    statistiques *s=new statistiques();
    s->show();
}

void integration::on_tabWidget_2_currentChanged(int index)
{
    ui->table_employe->setModel(tmpemploye.afficher());
    ui->table_grade->setModel(tmpgrade.afficher());//actualisation
    ui->comboBox_idgrade->clear();
    ui->comboBox_idgrade->addItems(tmpgrade.listegrade());

    QBarSet *set1=new QBarSet("Nombre des employes");

    set1->append(tmpgrade.nombreEmp());
    QBarSeries *series=new QBarSeries();
    series->append(set1);

    QChart *chart =new QChart();
    chart->addSeries(series);
    chart->setTitle("statistiques des employes");
    chart->setAnimationOptions(QChart::AllAnimations);
    QStringList categories=tmpgrade.listStatuts();

    QBarCategoryAxis *axis=new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis,series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartview=new QChartView(chart);

    QGridLayout *mainLayout=new QGridLayout();
    mainLayout->addWidget(chartview,0,0);
    ui->widget_EG->setLayout(mainLayout);





}

void integration::on_actionajouterclient_triggered()
{
    int id=ui->id_client->text().toInt();
    QString nom=ui->nom_client->text();
    QString prenom=ui->prenom_client->text();
    QDate date_n=ui->date_n_client->date();
    QString email=ui->email_client->text();
    int num_tel=ui->tel_client->text().toInt();




    client c(id,nom,prenom,date_n,email,num_tel);
    bool test=c.ajouter();
    if(test){
        QMessageBox::information(nullptr,QObject::tr("client"),QObject::tr("Client ajouté avec succés"),QMessageBox::Ok);
        ui->table_client->setModel(tmpclient.afficher());
        ui->id_client->setText("");
        ui->nom_client->setText("");
        ui->prenom_client->setText("");
        ui->date_n_client->setDate(QDate(2000,01,01));
        ui->email_client->setText("");
        ui->tel_client->setText("");

        ui->combo_client->clear();
        ui->combo_client->addItems(tmpclient.listeClients());
    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("client"),QObject::tr("erreur"),QMessageBox::Ok);
    }
}

void integration::on_actionsupprimerclient_triggered()
{
    int id=ui->id_client->text().toInt();
    bool test=tmpclient.supprimer(id);
    if(test){
        QMessageBox::information(nullptr,QObject::tr("client"),QObject::tr("Client supprimé avec succés"),QMessageBox::Ok);
        ui->table_client->setModel(tmpclient.afficher());
        ui->id_client->setText("");
    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("client"),QObject::tr("erreur"),QMessageBox::Ok);
    }
}

void integration::on_actionmodifierclient_triggered()
{
    int id=ui->id_client->text().toInt();
    QString nom=ui->nom_client->text();
    QString prenom=ui->prenom_client->text();
    QDate date_n=ui->date_n_client->date();
    QString email=ui->email_client->text();
    int num_tel=ui->tel_client->text().toInt();

    client c(id,nom,prenom,date_n,email,num_tel);
    bool test=c.modifier(id);
    if(test){
        QMessageBox::information(nullptr,QObject::tr("client"),QObject::tr("Client modifié avec succés"),QMessageBox::Ok);
        ui->table_client->setModel(tmpclient.afficher());
        ui->id_client->setText("");
        ui->nom_client->setText("");
        ui->prenom_client->setText("");
        ui->date_n_client->setDate(QDate(2000,01,01));
        ui->email_client->setText("");
        ui->tel_client->setText("");
    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("client"),QObject::tr("erreur"),QMessageBox::Ok);
    }
}

void integration::on_actionrechercherclient_triggered()
{
    int id=ui->id_client->text().toInt();
        client c=tmpclient.trouver(id);
        ui->nom_client->setText(c.getNom());
        ui->prenom_client->setText(c.getPrenom());
        ui->date_n_client->setDate(c.getDate_n());
        ui->email_client->setText(c.getemail());
        ui->num_tel->setNum(c.getnum_tel());
    ui->table_client->setModel(tmpclient.rechercher(ui->recherche_client->text()));
}

void integration::on_actionajouterfacture_triggered()
{

    int num_fact=ui->num_fact->text().toInt();
    double montant=ui->montant_fac->text().toDouble();
    QDate date_f=date_f.currentDate();
    int id_client=ui->combo_client->currentText().toInt();
    qDebug()<<date_f;
    facture f(num_fact,montant,date_f,id_client);
    bool test=f.ajouter();
    if(test){
        QMessageBox::information(nullptr,QObject::tr("facture"),QObject::tr("facture ajouté avec succés"),QMessageBox::Ok);
        ui->table_fac->setModel(tmpfacture.afficher());
        ui->num_fact->setText("");
        ui->montant_fac->setText("");
        //ui->date_fac->setDate(QDate(2000,01,01));
        ui->type->setText("");
    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("facture"),QObject::tr("erreur"),QMessageBox::Ok);
    }
}

void integration::on_actionsupprimerfacture_triggered()
{
    int num_fact=ui->num_fact->text().toInt();
    bool test=tmpfacture.supprimer(num_fact);
    if(test){
        QMessageBox::information(nullptr,QObject::tr("facture"),QObject::tr("facture supprimé avec succés"),QMessageBox::Ok);
        ui->table_fac->setModel(tmpfacture.afficher());
        ui->num_fact->setText("");
    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("facture"),QObject::tr("erreur"),QMessageBox::Ok);
    }

}

void integration::on_actionmodifierfacture_triggered()
{

    int num_fact=ui->num_fact->text().toInt();
    double montant=ui->montant_fac->text().toDouble();
    QDate date_f;
    int id_client=ui->combo_client->currentText().toInt();
   facture f (num_fact,montant,date_f,id_client);
    bool test=f.modifier(num_fact);
    if(test){
        QMessageBox::information(nullptr,QObject::tr("facture"),QObject::tr("facture modifié avec succés"),QMessageBox::Ok);
        ui->table_fac->setModel(tmpfacture.afficher());
        ui->num_fact->setText("");
        ui->montant_fac->setText("");
        //ui->date_fac->setDate(QDate(2000,01,01));
        ui->type->setText("");
    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("facture"),QObject::tr("erreur"),QMessageBox::Ok);
    }
}

void integration::on_actionrechercherfacture_triggered()
{
    int num_fact=ui->num_fact->text().toInt();
    facture f=tmpfacture.trouver(num_fact);
    QString montant=QString::number(f.getmontant());
    ui->montant_fac->setText(montant);
    //ui->date_fac->setDate(f.getdate_f());
    ui->type->setText(QString::number(f.getid_client()));
}



void integration::on_actionimprimerfacture_triggered()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->table_fac->model()->rowCount();
    const int columnCount = ui->table_fac->model()->columnCount();

    out <<  "<html>\n"
    <<"<head>\n"
    <<"<meta Content=\"Text/html; charset=Windows-1251\">\n"
    <<  QString("<title>%1</title>\n").arg("strTitle")
    <<  "</head>\n"
    <<"<body bgcolor=#ffffff link=#5000A0>\n"
    <<"<center> <H1>Facture</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";
    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
    for (int column = 0; column < columnCount; column++){
        if (!ui->table_fac->isColumnHidden(column)){
            out << QString("<th>%1</th>").arg(ui->table_fac->model()->headerData(column, Qt::Horizontal).toString());
        }
    }
        out << "</tr></thead>\n";
        for (int row = 0; row < rowCount; row++) {
            out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
            for (int column = 0; column < columnCount; column++) {
                if (!ui->table_fac->isColumnHidden(column)) {
                    QString data = ui->table_fac->model()->data(ui->table_fac->model()->index(row, column)).toString().simplified();
                    out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                }
            }
            out << "</tr>\n";
        }
        out <<  "</table> </center>\n"
        <<"</body>\n"
        <<"</html>\n";

        QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
        if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }
        QPrinter printer (QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFileName(fileName);

        QTextDocument doc;
        doc.setHtml(strStream);
        doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
        doc.print(&printer);
}

void integration::on_tabWidget_4_currentChanged(int index)
{
    ui->table_fac->setModel(tmpfacture.afficher());
    ui->table_client->setModel(tmpclient.afficher());

    ui->combo_client->clear();
    ui->combo_client->addItems(tmpclient.listeClients());
}

void integration::on_lineEdit_rechercher_emp_2_textChanged(const QString &arg1)
{
    bool nom=ui->checkBox_nom->isChecked();
    bool prenom=ui->checkBox_prenom->isChecked();
    bool grade=ui->checkBox_grade->isChecked();

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



void integration::on_checkBox_salaire_stateChanged(int arg1)
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

void integration::on_checkBox_grade2_stateChanged(int arg1)
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

void integration::on_checkBox_nombre_stateChanged(int arg1)
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

void integration::on_recherche_client_textChanged(const QString &arg1)
{
     ui->table_client->setModel(tmpclient.rechercher(ui->recherche_client->text()));
}


void integration::on_filtrer_client_textChanged(const QString &arg1)
{
    ui->table_fac->setModel(tmpfacture.rechercher(ui->filtrer_client->text()));
}

void integration::on_actionAI_triggered()
{
    intervenant I  (ui->lineEdit_id->text().toUInt(),ui->lineEdit_num->text().toUInt(),ui->lineEdit_nom->text(),ui->lineEdit_3->text());
        I.ajouter();
          ui->tableView->setModel(I.afficher());
}

void integration::on_actionMI_triggered()
{ bool    test=I.modifier(ui->lineEdit_id->text().toUInt(),ui->lineEdit_num->text().toUInt()) ;
    if (test)
    {
          ui->tableView->setModel(I.afficher());
        QMessageBox::information(nullptr,QObject::tr("OK"),
                             QObject::tr("modification établie"),
                             QMessageBox::Ok);}
    else{
    //qDebug()<<"connexion echouer";
    QMessageBox::critical(nullptr,QObject::tr("ERROR404"),
                            QObject::tr("modification non établie"),
                            QMessageBox::Cancel);}

}

void integration::on_actionSI_triggered()
{bool    test=I.supprimer( ui->lineEdit_id->text().toUInt());
    if (test)
    {
        ui->tableView->setModel(I.afficher());

        QMessageBox::information(nullptr,QObject::tr("OK"),
                             QObject::tr("supression établie"),
                             QMessageBox::Ok);}
    else{
    //qDebug()<<"connexion echouer";
    QMessageBox::critical(nullptr,QObject::tr("ERROR404"),
                            QObject::tr("supression non établie"),
                            QMessageBox::Cancel);}

}

void integration::on_actionME_triggered()
{bool    test=E.modifier(ui->lineEdit_ide->text().toUInt(),ui->lineEdit_foncion->text()) ;
    if (test)
    {
          ui->tableView_2->setModel(E.afficher());
        QMessageBox::information(nullptr,QObject::tr("OK"),
                             QObject::tr("modification établie"),
                             QMessageBox::Ok);}
    else{
    //qDebug()<<"connexion echouer";
    QMessageBox::critical(nullptr,QObject::tr("ERROR404"),
                            QObject::tr("modification non établie"),
                            QMessageBox::Cancel);}

}


void integration::on_actionSE_triggered()
{
    bool    test=E.supprimer( ui->lineEdit_ide->text().toUInt());
            if (test)
            {
                ui->tableView_2->setModel(E.afficher());

                QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject::tr("supression établie"),
                                     QMessageBox::Ok);}
            else{
            //qDebug()<<"connexion echouer";
            QMessageBox::critical(nullptr,QObject::tr("ERROR404"),
                                    QObject::tr("supression non établie"),
                                    QMessageBox::Cancel);}
}

void integration::on_actionAE_triggered()
{
    equipement E (ui->lineEdit_ide->text().toUInt(),ui->lineEdit_marque->text(),ui->lineEdit_foncion->text());
          E .ajouter();
            ui->tableView_2->setModel(E.afficher());
}

void integration::on_actionRE_triggered()
{equipement E;
    int ide = ui->lineEdit_ide->text().toInt();
   ui->tableView_2->setModel(E.rechercher(ide));
}

void integration::on_actionRI_triggered()
{
    intervenant I;
            int id = ui->lineEdit_id->text().toInt();
           ui->tableView->setModel(I.rechercher(id));
}


void integration::on_pushButton_2_clicked()
{
    equipement E;

        bool test=true;
                if(test){

                       { ui->tableView_2->setModel(E.trier_ide());
                        QMessageBox::information(nullptr, QObject::tr("trier equipement"),
                                    QObject::tr(" equipement trier.\n"
                                                "Voulez-vous enregistrer les modifications ?"),
                                           QMessageBox::Save
                                           | QMessageBox::Cancel,
                                          QMessageBox::Save);
        }

                    }
                    else
                        QMessageBox::critical(nullptr, QObject::tr("trier  equipement"),
                                    QObject::tr("Erreur !.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
}


void integration::on_pushButton_clicked()
{
    intervenant I;

        bool test=true;
                if(test){

                       { ui->tableView->setModel(I.trier_id());
                        QMessageBox::information(nullptr, QObject::tr("trier intervenant"),
                                    QObject::tr(" intervenant trier.\n"
                                                "Voulez-vous enregistrer les modifications ?"),
                                           QMessageBox::Save
                                           | QMessageBox::Cancel,
                                          QMessageBox::Save);
        }

                    }
                    else
                        QMessageBox::critical(nullptr, QObject::tr("trier  intervenant"),
                                    QObject::tr("Erreur !.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);

}









void integration::on_pushButton_5_clicked()
{
    bool test=login(ui->usename->text(),ui->password->text());
    if(test){
        integration *i=new integration();
        ui->stackedWidget->setCurrentIndex(1);
        i->show();}
}

void integration::on_actionimprimerEMP_triggered()
{QMediaPlayer * bulletsound = new QMediaPlayer();
    bulletsound->setMedia(QUrl::fromLocalFile("C:/Users/HP/Documents"));
    if (bulletsound->state() == QMediaPlayer::PlayingState){
        bulletsound->setPosition(0);
    }
    else if (bulletsound->state() == QMediaPlayer::StoppedState){
        bulletsound->play();
    }

    QString strStream;
    QTextStream out(&strStream);

    const int rowCount =ui->table_employe->model()->rowCount();
    const int columnCount =ui->table_employe->model()->columnCount();

    out <<  "<html>\n"
    <<"<head>\n"
    <<"<meta Content=\"Text/html; charset=Windows-1251\">\n"
    <<  QString("<title>%1</title>\n").arg("strTitle")
    <<  "</head>\n"
    <<"<body bgcolor=#ffffff link=#5000A0>\n"
    <<"<center> <H1>Employes</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";
    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
    for (int column = 0; column < columnCount; column++){
        if (!ui->table_employe->isColumnHidden(column)){
            out << QString("<th>%1</th>").arg(ui->table_employe->model()->headerData(column, Qt::Horizontal).toString());
        }
    }
        out << "</tr></thead>\n";
        for (int row = 0; row < rowCount; row++) {
            out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
            for (int column = 0; column < columnCount; column++) {
                if (!ui->table_employe->isColumnHidden(column)) {
                    QString data = ui->table_employe->model()->data(ui->table_employe->model()->index(row, column)).toString().simplified();
                    out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                }
            }
            out << "</tr>\n";
        }
        out <<  "</table> </center>\n"
        <<"</body>\n"
        <<"</html>\n";

        QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
        if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }
        QPrinter printer (QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFileName(fileName);

        QTextDocument doc ;
        doc.setHtml(strStream);
        doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
        doc.print(&printer);
}

void integration::on_stat_currentChanged(int index)
{
    ui->table_client->setModel(tmpclient.afficher());
    ui->table_fac->setModel(tmpfacture.afficher());

    ui->combo_client->clear();
    ui->combo_client->addItems(tmpclient.listeClients());

    QBarSet *set=new QBarSet("Nombre des factures");
    *set<<f.calculer(1)<<f.calculer(2)<<f.calculer(3)<<f.calculer(4)<<f.calculer(5)<<f.calculer(6)<<f.calculer(7)<<f.calculer(8)<<f.calculer(9)<<f.calculer(10)<<f.calculer(11)<<f.calculer(12);
    QBarSeries *series=new QBarSeries();
    series->append(set);
    QChart *chart=new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des factures");
    chart->setAnimationOptions(QChart::AllAnimations);
    QStringList mois;
    mois<<"Janvier"<<"Février"<<"Mars"<<"Avril"<<"Mai"<<"Juin"<<"Juillet"<<"Aout"<<"Septembre"<<"Octobre"<<"Novombre"<<"Décembre";
    QBarCategoryAxis *axis=new QBarCategoryAxis();
    axis->append(mois);
    chart->createDefaultAxes();
    chart->setAxisX(axis,series);

  QChartView *chartview=new QChartView(chart);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(chartview, 0, 0);
    ui->widget_fact->setLayout(mainLayout);

}

void integration::on_actualiser_stat_emp_clicked()
{
    QBarSet *set1=new QBarSet("Nombre des employes");

    set1->append(tmpgrade.nombreEmp());
    QBarSeries *series=new QBarSeries();
    series->append(set1);

    QChart *chart =new QChart();
    chart->addSeries(series);
    chart->setTitle("statistiques des employes");
    chart->setAnimationOptions(QChart::AllAnimations);
    QStringList categories=tmpgrade.listStatuts();

    QBarCategoryAxis *axis=new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis,series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartview=new QChartView(chart);

    QGridLayout *mainLayout=new QGridLayout();
    mainLayout->addWidget(chartview,0,0);
    ui->widget_EG->setLayout(mainLayout);
}

void integration::on_actualiser_stat_fact_clicked()
{
    qDebug() <<"clicked!";
    QBarSet *set=new QBarSet("Nombre des factures");
    *set<<f.calculer(1)<<f.calculer(2)<<f.calculer(3)<<f.calculer(4)<<f.calculer(5)<<f.calculer(6)<<f.calculer(7)<<f.calculer(8)<<f.calculer(9)<<f.calculer(10)<<f.calculer(11)<<f.calculer(12);
     qDebug() <<"clicked1!";
    QBarSeries *series=new QBarSeries();
    series->append(set);
    QChart *chart=new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des factures");
    chart->setAnimationOptions(QChart::AllAnimations);
    QStringList mois;
    mois<<"Janvier"<<"Février"<<"Mars"<<"Avril"<<"Mai"<<"Juin"<<"Juillet"<<"Aout"<<"Septembre"<<"Octobre"<<"Novombre"<<"Décembre";
    QBarCategoryAxis *axis=new QBarCategoryAxis();
    axis->append(mois);
    chart->createDefaultAxes();
    chart->setAxisX(axis,series);

    QChartView *chartview=new QChartView(chart);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(chartview, 0, 0);
    ui->widget_fact->setLayout(mainLayout);
}

void integration::on_lineEdit_rechercher_emp_textChanged(const QString &arg1)
{
    bool nom=ui->checkBox_nom->isChecked();
    bool prenom=ui->checkBox_prenom->isChecked();
    bool grade=ui->checkBox_grade->isChecked();

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
