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
    query.exec("DROP TABLE rundenslag");

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
                                     "posisjonsId INT,"
                                     "lagID INT,"
                                     "FOREIGN KEY (lagID) REFERENCES lag(id))");

    //Stabæk
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Jon ', 'Knudsen', '1', 'Keeper', 0, 10)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Bjarni', 'Ólafur Eiríksson', '2', 'Venstre back', 2, 10)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Jon Inge', 'Høiland', '3', 'Venstre midtstopper', 3, 10)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Kristian', 'Onstad', '4', 'Høyre back', 1, 10)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Tom', 'Stenvoll', '5', 'Høyre midtstopper', 4, 10)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Henning', 'Hauger', '6', 'Høyre midtbane', 8, 10)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Espen', 'Hoff', '7', 'Venstre midtbane', 7, 10)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Pálmi', 'Rafn Pálmason', '8', 'Venstre ving', 6, 10)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Diogo', 'da Costa Oliveira', '9', 'Høyre ving', 5, 10)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Daniel', 'Nannskog', '10', 'Høyre spiss', 10, 10)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Veigar', 'Pall Gunnarsson', '11', 'Venstre spiss', 9, 10)");

    //Start
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Rune', 'Nilssen', '1', 'Keeper', 0, 11)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Hunter', 'Freeman', '2', 'Venstre back', 2, 11)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Branislav', 'Milicevic', '3', 'Venstre midtstopper', 3, 11)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Clarence', 'Goodson', '4', 'Høyre back', 1, 11)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Olufemi', 'Oladapo', '5', 'Høyre midtstopper', 4, 11)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Aram', 'Khalili', '6', 'Høyre midtbane', 8, )");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Knut Henry', 'Haraldsen', '7', 'Venstre midtbane', 7, 11)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Espen', 'Børufsen', '8', 'Venstre ving', 6, 11)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Petter', 'Bruer Hanssen', '9', 'Høyre ving', 5, 11)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Christian', 'Bolaños', '10', 'Høyre spiss', 10, 11)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Geir', 'L. Fevang', '11', 'Venstre spiss', 9, 11)");

    //Strømsgodset
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Adam', 'Larsen Kwarasey', '1', 'Keeper', 0, 12)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Alexander', 'Aas', '2', 'Venstre back', 2, 12)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Glenn', 'Andersen', '3', 'Venstre midtstopper', 3, 12)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Joel', 'Riddez', '4', 'Høyre back', 1, 12)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Kim André', 'Madsen', '5', 'Høyre midtstopper', 4, 12)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Komlan', 'Amewou', '6', 'Høyre midtbane', 8, 12)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Lars Christopher', 'Vilsvik', '7', 'Venstre midtbane', 7, 12)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Mads', 'Ryghseter', '8', 'Venstre ving', 6, 12)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Fredrik', 'Nordkvelle', '9', 'Høyre ving', 5, 12)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Steffen', 'Nystrøm', '10', 'Høyre spiss', 10, 12)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Øyvind', 'Storflor', '11', 'Venstre spiss', 9, 12)");

    //Tromsø
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Sead', 'Ramovic', '1', 'Keeper', 0, 13)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Hans Julius', 'Eriksen Norbye', '2', 'Venstre back', 2, 13)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Dominique', 'Taboga', '3', 'Venstre midtstopper', 3, 13)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Jade', 'Bronson North', '4', 'Høyre back', 1, 13)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Ruben', 'Yttergård Jenssen', '5', 'Høyre midtstopper', 4, 13)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Remi', 'Johansen', '6', 'Høyre midtbane', 8, 13)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Mads', 'Reginiussen', '7', 'Venstre midtbane', 7, 13)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Helge', 'Haugen', '8', 'Venstre ving', 6, 13)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Tommy', 'Knarvik', '9', 'Høyre ving', 5, 13)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Sigurd', 'Rushfeldt', '11', 'Høyre spiss', 10, 13)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Vegard', 'Braaten', '10', 'Venstre spiss', 9, 13)");

    //Viking
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Rune', 'Almenning Jarstein', '1', 'Keeper', 0, 14)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Trond Erik', 'Bertelsen', '2', 'Venstre back', 2, 14)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Børre', 'Steenslid', '3', 'Venstre midtstopper', 3, 14)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Håkon', 'Skogseid', '6', 'Høyre back', 1, 14)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Christian', 'Landu Landu', '13', 'Høyre midtstopper', 4, 14)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Stefan', 'Gislason', '5', 'Høyre midtbane', 8, 14)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Tomasz', 'Sokolowski', '7', 'Venstre midtbane', 7, 14)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Vidar', 'Nisja', '8', 'Venstre ving', 6, 14)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Andrè', 'Danielsen', '14', 'Høyre ving', 5, 14)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Patrik', 'Ingelsten', '25', 'Høyre spiss', 10, 14)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Alexander', 'Ødegaard', '20', 'Venstre spiss', 9, 14)");

    //Vålerenga
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Lars', 'Hirschfeld', '1', 'Keeper', 0, 15)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Andreas', 'Nordvik', '3', 'Venstre back', 2, 15)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('André', 'Muri', '4', 'Venstre midtstopper', 3, 15)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Freddy', 'dos Santos', '6', 'Høyre back', 1, 15)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Birger', 'Madsen', '22', 'Høyre midtstopper', 4, 15)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Kristofer', 'Hæstad', '23', 'Høyre midtbane', 8, 15)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Mohammed', 'Fellah', '17', 'Venstre midtbane', 7, 15)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Morten', 'Berre', '11', 'Venstre ving', 6, 15)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Lars Iver', 'Strand', '10', 'Høyre ving', 5, 15)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Mohammed', 'Abdellaoue', '25', 'Høyre spiss', 10, 15)");
    query.exec("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID) VALUES ('Mostafa', 'Abdellaoue', '20', 'Venstre spiss', 9, 15)");


    query.exec("CREATE TABLE rundenslag (id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                        "rundensLagNavn VARCHAR(40),"
                                        "navn VARCHAR(40),"
                                        "posisjon VARCHAR(40),"
                                        "lagNavn VARCHAR(40))");

    return true;
}

#endif // DATABASE_H


