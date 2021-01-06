#include "connection.h"


connection::connection()
{

}

bool connection::createconnection(){
   bool test=false;
   QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

   db.setDatabaseName("Projet_2A");
   db.setUserName("system");
   db.setPassword("system");

   /*QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
   db.setDatabaseName("yasmine");
   db.setHostName("127.0.0.1");
   db.setUserName("root");//inserer nom de l'utilisateur
   db.setPassword("");//inserer mot de passe de cet utilisateur
   db.setPort(3306);*/


   if(db.open())
       test=true;
   return test;
}
