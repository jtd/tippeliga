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

    query.exec("DROP TABLE lag");
    query.exec("DROP TABLE spiller");
    query.exec("DROP TABLE rundenslag");

    query.exec("CREATE TABLE lag (id INT PRIMARY KEY,"
                                 "lagnavn VARCHAR(40),"
                                 "nettside TEXT)");

    query.exec("INSERT INTO lag VALUES(0, 'Aalesund', 'http://no.wikipedia.org/wiki/Aalesund_FK')");
    query.exec("INSERT INTO lag VALUES(1, 'Brann', 'http://no.wikipedia.org/wiki/Sportsklubben_Brann')");
    query.exec("INSERT INTO lag VALUES(2, 'Haugesund', 'http://no.wikipedia.org/wiki/Fotballklubben_Haugesund')");
    query.exec("INSERT INTO lag VALUES(3, 'H�nefoss', 'http://no.wikipedia.org/wiki/H�nefoss_BK')");
    query.exec("INSERT INTO lag VALUES(4, 'Kongsvinger', 'http://no.wikipedia.org/wiki/Kongsvinger_Idrettslag')");
    query.exec("INSERT INTO lag VALUES(5, 'Lillestr�m', 'http://no.wikipedia.org/wiki/Lillestr�m_Sportsklubb')");
    query.exec("INSERT INTO lag VALUES(6, 'Molde', 'http://no.wikipedia.org/wiki/Molde_FK')");
    query.exec("INSERT INTO lag VALUES(7, 'Odd Grenland', 'http://no.wikipedia.org/wiki/Odd_Grenland')");
    query.exec("INSERT INTO lag VALUES(8, 'Rosenborg', 'http://no.wikipedia.org/wiki/Rosenborg_Ballklub')");
    query.exec("INSERT INTO lag VALUES(9, 'Sandefjord', 'http://no.wikipedia.org/wiki/Sandefjord_fotball')");
    query.exec("INSERT INTO lag VALUES(10, 'Stab�k', 'http://no.wikipedia.org/wiki/Stab�k_fotball')");
    query.exec("INSERT INTO lag VALUES(11, 'Start', 'http://no.wikipedia.org/wiki/Start')");
    query.exec("INSERT INTO lag VALUES(12, 'Str�msgodset', 'http://no.wikipedia.org/wiki/Str�msgodset_Idrettsforening')");
    query.exec("INSERT INTO lag VALUES(13, 'Troms�', 'http://no.wikipedia.org/wiki/Troms%C3%B8_Idrettslag')");
    query.exec("INSERT INTO lag VALUES(14, 'Viking', 'http://no.wikipedia.org/wiki/Viking_Fotballklubb')");
    query.exec("INSERT INTO lag VALUES(15, 'V�lerenga', 'http://no.wikipedia.org/wiki/V�lerenga_fotball')");

    query.exec("CREATE TABLE spiller (id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                     "fornavn VARCHAR(40),"
                                     "etternavn VARCHAR(40),"
                                     "draktnummer VARCHAR(5),"
                                     "posisjon VARCHAR(40),"
                                     "posisjonsId INT,"
                                     "lagID INT,"
                                     "FOREIGN KEY (lagID) REFERENCES lag(id))");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Leif', 'Juster', '1', 'Keeper', 0, 0)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Bjarne', 'Br�nbo', '1', 'Venstre Spiss', 9, 0)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES('Jon Torstein', 'Dalen', '3', 'H�yre back', 1, 7)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES('Eirik', 'Luka', '7', 'H�yre spiss', 10, 15)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES('Anders', 'Evenstuen', '7', 'H�yre midtstopper', 4, 8)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES('Henrik', 'Wingerei', '4', 'H�yre midtbane', 8, 10)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES('�yvind', 'Midtb�', '1', 'Keeper', 0, 4)");

    query.exec("CREATE TABLE rundenslag (id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                        "rundensLagNavn VARCHAR(40),"
                                        "navn VARCHAR(40),"
                                        "posisjon VARCHAR(40),"
                                        "lagNavn VARCHAR(40))");
    return true;
}

#endif // DATABASE_H


