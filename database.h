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
    query.exec("CREATE TABLE lag (id INT PRIMARY KEY,"
                                 "lagnavn VARCHAR(40),"
                                 "lagInfo VARCHAR(50))");



    query.exec("INSERT INTO lag VALUES(0, 'Vålerenga', 'Etablert i 1998')");
    query.exec("INSERT INTO lag VALUES(1, 'Rosenborg', 'Etablert i 1992')");
    query.exec("INSERT INTO lag VALUES(2, 'Odd Grenland', 'Etablert i 1992')");
    query.exec("INSERT INTO lag VALUES(3, 'Molde', 'Etablert i 1992')");
    query.exec("INSERT INTO lag VALUES(4, 'Stabæk', 'Etablert i 1992')");
    query.exec("INSERT INTO lag VALUES(5, 'Tromsø', 'Etablert i 1992')");
    query.exec("INSERT INTO lag VALUES(6, 'Aalesund', 'Etablert i 1992')");
    query.exec("INSERT INTO lag VALUES(7, 'Start', 'Etablert i 1992')");
    query.exec("INSERT INTO lag VALUES(8, 'Lillestrøm', 'Etablert i 1992')");
    query.exec("INSERT INTO lag VALUES(9, 'Haugesund', 'Etablert i 1992')");
    query.exec("INSERT INTO lag VALUES(10, 'Viking', 'Etablert i 1992')");
    query.exec("INSERT INTO lag VALUES(11, 'Sandefjord', 'Etablert i 1992')");
    query.exec("INSERT INTO lag VALUES(12, 'Kongsvinger', 'Etablert i 1992')");
    query.exec("INSERT INTO lag VALUES(13, 'Hønefoss', 'Etablert i 1992')");
    query.exec("INSERT INTO lag VALUES(14, 'Brann', 'Etablert i 1992')");
    query.exec("INSERT INTO lag VALUES(15, 'Strømsgodset', 'Etablert i 1992')");

    query.exec("CREATE TABLE spiller (id INT PRIMARY KEY,"
                                     "fornavn VARCHAR(40),"
                                     "etternavn VARCHAR(40),"
                                     "draktnummer VARCHAR(5),"
                                     "posisjon VARCHAR(40),"
                                     "lagID INT,"
                                     "FOREIGN KEY (lagID) REFERENCES lag(id))");

    query.exec("INSERT INTO spiller VALUES(0, 'Jon Torstein', 'Dalen', '3', 'Høyre back', 2)");
    query.exec("INSERT INTO spiller VALUES(1, 'Eirik', 'Luka', '7', 'Spiss', 2)");

    return true;
}

#endif // DATABASE_H


