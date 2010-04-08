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

    query.exec("DROP TABLE lag");
    query.exec("DROP TABLE spiller");

    query.exec("CREATE TABLE lag (id INT PRIMARY KEY,"
                                 "lagnavn VARCHAR(40),"
                                 "lagInfo VARCHAR(50),"
                                 "nettside TEXT)");

    query.exec("INSERT INTO lag VALUES(0, 'Aalesund', 'Etablert i 1992', '')");
    query.exec("INSERT INTO lag VALUES(1, 'Brann', 'Etablert i 1992', '')");
    query.exec("INSERT INTO lag VALUES(2, 'Haugesund', 'Etablert i 1992', '')");
    query.exec("INSERT INTO lag VALUES(3, 'Hønefoss', 'Etablert i 1992', '')");
    query.exec("INSERT INTO lag VALUES(4, 'Kongsvinger', 'Etablert i 1992', '')");
    query.exec("INSERT INTO lag VALUES(5, 'Lillestrøm', 'Etablert i 1992', '')");
    query.exec("INSERT INTO lag VALUES(6, 'Molde', 'Etablert i 1992', '')");
    query.exec("INSERT INTO lag VALUES(7, 'Odd Grenland', 'Etablert i 1992', '')");
    query.exec("INSERT INTO lag VALUES(8, 'Rosenborg', 'Etablert i 1992', '')");
    query.exec("INSERT INTO lag VALUES(9, 'Sandefjord', 'Etablert i 1992', '')");
    query.exec("INSERT INTO lag VALUES(10, 'Stabæk', 'Etablert i 1992', '')");
    query.exec("INSERT INTO lag VALUES(11, 'Start', 'Etablert i 1992', '')");
    query.exec("INSERT INTO lag VALUES(12, 'Strømsgodset', 'Etablert i 1992', '')");
    query.exec("INSERT INTO lag VALUES(13, 'Tromsø', 'Etablert i 1992', '')");
    query.exec("INSERT INTO lag VALUES(14, 'Viking', 'Etablert i 1992', '')");
    query.exec("INSERT INTO lag VALUES(15, 'Vålerenga', 'Etablert i 1998', 'http://no.wikipedia.org/wiki/Vålerenga_fotball')");

    query.exec("CREATE TABLE spiller (id INT PRIMARY KEY,"
                                     "fornavn VARCHAR(40),"
                                     "etternavn VARCHAR(40),"
                                     "draktnummer VARCHAR(5),"
                                     "posisjon VARCHAR(40),"
                                     "lagID INT,"
                                     "FOREIGN KEY (lagID) REFERENCES lag(id))");
    query.exec("INSERT INTO spiller VALUES(null, 'Leif', 'Juster', '1', 'Keeper', 0)");
    query.exec("INSERT INTO spiller VALUES(null, 'Jon Torstein', 'Dalen', '3', 'Høyre back', 7)");
    query.exec("INSERT INTO spiller VALUES(null, 'Eirik', 'Luka', '7', 'Spiss', 15)");
    query.exec("INSERT INTO spiller VALUES(null, 'Anders', 'Evenstuen', '7', 'Spiss', 8)");
    query.exec("INSERT INTO spiller VALUES(null, 'Henrik', 'Wingerei', '4', 'Midtbane', 10)");
    query.exec("INSERT INTO spiller VALUES(null, 'Øyvind', 'Midtbø', '1', 'Keeper', 4)");

    return true;
}

#endif // DATABASE_H


