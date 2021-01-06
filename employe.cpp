#include "employe.h"
#include<QDebug>
employe::employe()
{
    id=0;
    date_naissance=date_naissance.currentDate();
    nom="";
    prenom="";
    email="";
    id_grade=0;
    telephone=0;
    carte="";
}
employe::employe(int id,QString nom,QString prenom,QDate date_naissance,QString email,int telephone,int id_grade,QString carte){

    this->id=id;
    this->date_naissance=date_naissance;
    this->nom=nom;
    this->prenom=prenom;
    this->email=email;
    this->telephone=telephone;
    this->id_grade=id_grade;
    this->carte=carte;
}
employe::~employe(){}

bool employe::ajouter(){

    QSqlQuery query;
    QString id_e=QString::number(id);
    query.prepare("insert into employe (id,nom,prenom,date_naissance,email,telephone,id_grade,carte) values (:id,:nom,:prenom,:date_naissance,:email,:telephone,:id_grade,:carte)");
    query.bindValue(":id",id_e);//injection
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":date_naissance",date_naissance);
    query.bindValue(":email",email);
    query.bindValue(":telephone",telephone);
    query.bindValue(":id_grade",id_grade);
    query.bindValue(":carte",carte);
    return query.exec();
}

bool employe::supprimer(int id){
    QSqlQuery q;
    q.prepare("select* from employe where id=:id");
    q.bindValue(":id",id);
    q.exec();
    int total=0;
    while(q.next()){
        total++;
    }
    if(total==1){
        QSqlQuery query;
        QString id_e=QString::number(id);
        query.prepare("delete from employe where id=:id");
        query.bindValue(":id",id_e);
        return query.exec();
    }
    else{
        return false;
    }
}

bool employe::modifier(int idr){
    QSqlQuery query;
    QString id_r=QString::number(idr);
    QString id_e=QString::number(id);
    query.prepare("update employe set id=:id,nom=:nom,prenom=:prenom,date_naissance=:date_naissance ,email=:email,id_grade=:id_grade, carte=:carte where id=:idr");
    query.bindValue(":idr",id_r);
    query.bindValue(":id",id_e);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":date_naissance",date_naissance);
    query.bindValue(":email",email);
    query.bindValue(":id_grade",id_grade);
     query.bindValue(":carte",carte);
    qDebug() <<"employe modifié";
    return query.exec();
}

QSqlQueryModel * employe::afficher(){
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select id,nom,prenom,date_naissance,email,telephone,statut,carte from employe inner join grade on grade.id_g=employe.id_grade");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE N"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("TELEPHONE"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("GRADE"));
         model->setHeaderData(7, Qt::Horizontal, QObject::tr("CARTE"));
        return model;

}

employe employe::recherche_Id(int id){
    QSqlQuery query;
    QString id_e=QString::number(id);
    query.prepare("select * from employe where id=:id");
    query.bindValue(":id",id_e);
    query.exec();
    employe e;
    while(query.next()){
        e.Setid(id);
        e.Setnom(query.value(1).toString());
        e.Setprenom(query.value(2).toString());
        e.Setdate_naissance(query.value(3).toDate());
        e.Setemail(query.value(4).toString());
        e.Setcarte(query.value(5).toString());
    }
    return e;
}

QSqlQueryModel * employe::recherche(const QString &str){
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select id,nom,prenom,date_naissance,email,telephone,statut,carte from employe inner join grade on grade.id_g=employe.id_grade where nom like '"+str+"%' or prenom like '"+str+"%' or grade.statut like '"+str+"%'");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE N"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("TELEPHONE"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("GRADE"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("CARTE"));

        return model;
}

QSqlQueryModel * employe::recherche_n(const QString &str){
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select id,nom,prenom,date_naissance,email,telephone,statut,carte from employe inner join grade on grade.id_g=employe.id_grade where nom like '"+str+"%'");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE N"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("TELEPHONE"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("GRADE"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("CARTE"));
        return model;
}

QSqlQueryModel * employe::recherche_p(const QString &str){
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select id,nom,prenom,date_naissance,email,telephone,statut,carte from employe inner join grade on grade.id_g=employe.id_grade where prenom like '"+str+"%'");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE N"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("TELEPHONE"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("GRADE"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("CARTE"));
        return model;
}
QSqlQueryModel * employe::recherche_g(const QString &str){
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select id,nom,prenom,date_naissance,email,telephone,statut,carte from employe inner join grade on grade.id_g=employe.id_grade where grade.statut like '"+str+"%'");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE N"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("TELEPHONE"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("GRADE"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("CARTE"));
        return model;
}

QSqlQueryModel * employe::recherche_n_p(const QString &str){
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select id,nom,prenom,date_naissance,email,telephone,statut,carte from employe inner join grade on grade.id_g=employe.id_grade where nom like '"+str+"%' or prenom like '"+str+"%'");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE N"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("TELEPHONE"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("GRADE"));
      model->setHeaderData(7, Qt::Horizontal, QObject::tr("CARTE"));
        return model;
}

QSqlQueryModel * employe::recherche_n_g(const QString &str){
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select id,nom,prenom,date_naissance,email,telephone,statut,carte from employe inner join grade on grade.id_g=employe.id_grade where nom like '"+str+"%' or grade.statut like '"+str+"%'");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE N"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("TELEPHONE"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("GRADE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("CARTE"));
        return model;
}

QSqlQueryModel * employe::recherche_p_g(const QString &str){
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select id,nom,prenom,date_naissance,email,telephone,statut,carte from employe inner join grade on grade.id_g=employe.id_grade where prenom like '"+str+"%' or grade.statut like '"+str+"%'");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE N"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("TELEPHONE"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("GRADE"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("CARTE"));

        return model;
}


QString employe::getEmployeCarte(QString data)
{
    QSqlQuery query;
    query.prepare("select nom,prenom from employe where carte=:carte");
    query.bindValue(":carte",data);
    query.exec();
    QString nomprenom="";
    while(query.next()){
        nomprenom+= query.value(0).toString();
        nomprenom+=" ";
        nomprenom+= query.value(1).toString();
    }
    return nomprenom;
}
