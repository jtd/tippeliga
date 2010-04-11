#ifndef TIPPELIGAEN_H
#define TIPPELIGAEN_H

#include <QMainWindow>
#include <QtGui>
#include <QSqlRelationalTableModel>
#include "team.h"
#include "player.h"
#include "shirt.h"
#include "field.h"

#include <QWebView>

namespace Ui {
    class Tippeligaen;
}

class Tippeligaen : public QMainWindow {
    Q_OBJECT
public:
    Tippeligaen(QWidget *parent = 0);
    ~Tippeligaen();
    void setUrl(QString url);
    void createTeamWikiView();

    void makeWindowMenues();
    void createTeamInfoGroupBox();
    void createMakeNewPlayerGroupBox();
    void createMakeNewPlayerView();
    void createTeamPlayersGroupBox();

    QString url();

    QComboBox *teamComboBox;
    QGroupBox *createTeamChooserGroupBox();
    QTableView *playerTableView;
    QGroupBox *players;
    //QGroupBox *createTeamPlayersGroupBox();
    QGroupBox *createTeamOfTheRoundGroupBox();
    QGroupBox *createTeamWikiGroupBox();
    QLabel *fieldLabel;
    QGroupBox *teamInfo;
    //QGroupBox *createTeamInfoGroupBox();
    QLabel *shirtLabel;
    QLabel *valerengaInfo;
    QSqlRelationalTableModel *model;
    QSqlRelationalTableModel *teamModel;
    QSqlRelationalTableModel *playerModel;
    QWebView *wiki;
    QGroupBox *teamOfTheRound;
    QGroupBox *teamWiki;
    QGridLayout *wikiLayout;
    QGroupBox *makePlayerGroupBox;
    QLabel *playerNameLabel, *playerTeamLabel, *playerPositionLabel;
    QLabel *playerName;
    QLabel *playerTeam;
    QLabel *playerPosition;
    QString selectedTeamUrl;
    QMenu *createPlayerMenu;
    QAction *createPlayerAction;
    QLineEdit *playerFirstNameEdit;
    QLineEdit *playerLastNameEdit;
    QLabel *shirtNumberLabel;
    QComboBox *playerPositionEdit;
    QLineEdit *shirtNumberEdit;
    QLabel *playerFirstNameLabel;
    QLabel *playerLastNameLabel;
    QPushButton *createNewPlayer;
    QGridLayout *mainLayout;
    QPushButton *deletePlayerButton;
    QPushButton *addToTeamOfTheRoundButton;

    QString *test;
    Shirt *shirt;
    Field *field;


protected:
    void changeEvent(QEvent *e);

private:
    Ui::Tippeligaen *ui;
    QString _url;

private slots:
    void on_actionLaginfo_triggered();
    void on_actionUkens_lag_triggered();
    void on_actionAvslutt_triggered();
    void actionCreatePlayerTriggered();
    void updatePlayerTableView(int row);
    void updateTeamWiki(int row);
    void updatePlayerInformation();
    void actionAddNewPlayerToDataBase();
    void deletePlayer();

};

#endif // TIPPELIGAEN_H
