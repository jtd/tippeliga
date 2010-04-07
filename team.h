#ifndef TEAM_H
#define TEAM_H
#include <QSqlRelationalTableModel>

enum {
    Team_Id = 0,
    Team_Lagnavn = 1,
    Team_Laginfo= 2
};

class Team
{
    public:
        Team();
        //QSqlRelationalTableModel *teamModel;
};

#endif // TEAM_H
