#ifndef PLAYER_H
#define PLAYER_H
#include <QSqlRelationalTableModel>

enum {
    Spiller_Id = 0,
    Spiller_Fornavn = 1,
    Spiller_Etternavn = 2,
    Spiller_Draktnummer = 3,
    Spiller_Posisjon = 4,
    Spiller_PosisjonsId = 5,
    Spiller_LagID = 6
};

class Player
{
    public:
        Player();
        //QSqlRelationalTableModel *playerModel;

};


#endif // PLAYER_H
