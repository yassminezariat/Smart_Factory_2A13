#include "mainwindow.h"
#include <QApplication>
#include"connection.h"
#include <QMessageBox>
#include <QDebug>

#include"integration.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainWindow w;

    connection C;
    integration i;
    bool test=C.createconnection();
    if (test)
    {
        qDebug() <<"Connexion reussite";
        //w.show();
        i.show();
       QMessageBox::information(nullptr,QObject::tr("database is open"),QObject::tr("connexion succ:\n" "click ok to exit"),QMessageBox::Ok);
    }
    else
    {
        qDebug() <<"erreur de connexion";
        QMessageBox::critical(nullptr,QObject::tr("database is not open"),QObject::tr("connexion failed:\n" "click cancel to exit"),QMessageBox::Cancel);
    }
    return a.exec();
}
