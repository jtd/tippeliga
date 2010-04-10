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
                                 "nettside TEXT)");

    query.exec("INSERT INTO lag VALUES(0, 'Aalesund', 'http://no.wikipedia.org/wiki/Aalesund_FK')");
    query.exec("INSERT INTO lag VALUES(1, 'Brann', 'http://no.wikipedia.org/wiki/Sportsklubben_Brann')");
    query.exec("INSERT INTO lag VALUES(2, 'Haugesund', 'http://no.wikipedia.org/wiki/Fotballklubben_Haugesund')");
    query.exec("INSERT INTO lag VALUES(3, 'Hønefoss', 'http://no.wikipedia.org/wiki/Hønefoss_BK')");
    query.exec("INSERT INTO lag VALUES(4, 'Kongsvinger', 'http://no.wikipedia.org/wiki/Kongsvinger_Idrettslag')");
    query.exec("INSERT INTO lag VALUES(5, 'Lillestrøm', 'http://no.wikipedia.org/wiki/Lillestrøm_Sportsklubb')");
    query.exec("INSERT INTO lag VALUES(6, 'Molde', 'http://no.wikipedia.org/wiki/Molde_FK')");
    query.exec("INSERT INTO lag VALUES(7, 'Odd Grenland', 'http://no.wikipedia.org/wiki/Odd_Grenland')");
    query.exec("INSERT INTO lag VALUES(8, 'Rosenborg', 'http://no.wikipedia.org/wiki/Rosenborg_Ballklub')");
    query.exec("INSERT INTO lag VALUES(9, 'Sandefjord', 'http://no.wikipedia.org/wiki/Sandefjord_fotball')");
    query.exec("INSERT INTO lag VALUES(10, 'Stabæk', 'http://no.wikipedia.org/wiki/Stabæk_fotball')");
    query.exec("INSERT INTO lag VALUES(11, 'Start', 'http://no.wikipedia.org/wiki/Start')");
    query.exec("INSERT INTO lag VALUES(12, 'Strømsgodset', 'http://no.wikipedia.org/wiki/Strømsgodset_Idrettsforening')");
    query.exec("INSERT INTO lag VALUES(13, 'Tromsø', 'http://no.wikipedia.org/wiki/Troms%C3%B8_Idrettslag')");
    query.exec("INSERT INTO lag VALUES(14, 'Viking', 'http://no.wikipedia.org/wiki/Viking_Fotballklubb')");
    query.exec("INSERT INTO lag VALUES(15, 'Vålerenga', 'http://no.wikipedia.org/wiki/Vålerenga_fotball')");

    query.exec("CREATE TABLE spiller (id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                     "fornavn VARCHAR(40),"
                                     "etternavn VARCHAR(40),"
                                     "draktnummer VARCHAR(5),"
                                     "posisjon VARCHAR(40),"
                                     "lagID INT,"
                                     "FOREIGN KEY (lagID) REFERENCES lag(id))");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, lagID) VALUES ('Leif', 'Juster', '1', 'Keeper', 0)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, lagID) VALUES('Jon Torstein', 'Dalen', '3', 'Høyre back', 7)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, lagID) VALUES('Eirik', 'Luka', '7', 'Spiss', 15)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, lagID) VALUES('Anders', 'Evenstuen', '7', 'Spiss', 8)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, lagID) VALUES('Henrik', 'Wingerei', '4', 'Midtbane', 10)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, lagID) VALUES('Øyvind', 'Midtbø', '1', 'Keeper', 4)");

    return true;
}

#endif // DATABASE_H


