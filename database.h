#ifndef DATABASE_H
#define DATABASE_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

static bool createConnection(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("tippeliga.db");
    if(!db.open()){
        QMessageBox::critical(0, QObject::tr("Kan ikke åpne databasen"), db.lastError().text());
        return false;
    }
    QSqlQuery query;
    query.exec("create table lag (id int primary key, "
                                     "lag varchar(40), lagInfo varchar(50))");
    query.exec("insert into lag values(0, 'Vålerenga', 'Etablert i 1998')");
}

#endif // DATABASE_H


