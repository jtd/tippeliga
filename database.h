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
        QMessageBox::critical(0, QObject::tr("Kan ikke �pne databasen"), db.lastError().text());
        return false;
    }

    QSqlQuery query;
    query.exec("create table lag (id int primary key, "
                                   "lagnavn varchar(40), lagInfo varchar(50))");

    query.exec("insert into lag values(0, 'V�lerenga', 'Etablert i 1998')");
    query.exec("insert into lag values(1, 'Rosenborg', 'Etablert i 1992')");
    query.exec("insert into lag values(2, 'Odd Grenland', 'Etablert i 1992')");
    query.exec("insert into lag values(3, 'Molde', 'Etablert i 1992')");
    query.exec("insert into lag values(4, 'Stab�k', 'Etablert i 1992')");
    query.exec("insert into lag values(5, 'Troms�', 'Etablert i 1992')");
    query.exec("insert into lag values(6, 'Aalesund', 'Etablert i 1992')");
    query.exec("insert into lag values(7, 'Start', 'Etablert i 1992')");
    query.exec("insert into lag values(8, 'Lillestr�m', 'Etablert i 1992')");
    query.exec("insert into lag values(9, 'Haugesund', 'Etablert i 1992')");
    query.exec("insert into lag values(10, 'Viking', 'Etablert i 1992')");
    query.exec("insert into lag values(11, 'Sandefjord', 'Etablert i 1992')");
    query.exec("insert into lag values(12, 'Kongsvinger', 'Etablert i 1992')");
    query.exec("insert into lag values(13, 'H�nefoss', 'Etablert i 1992')");
    query.exec("insert into lag values(14, 'Brann', 'Etablert i 1992')");
    query.exec("insert into lag values(15, 'Str�msgodset', 'Etablert i 1992')");

    return true;
}

#endif // DATABASE_H


