#include "connection.h"

connection::connection()
{

}

bool connection::createconnection(){
   bool test=false;
   QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

   db.setDatabaseName("Projet_2A");
   db.setUserName("yassmine");
   db.setPassword("system");

   if(db.open())
       test=true;
   return test;
}
