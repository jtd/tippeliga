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

    QMenu *fileMenu;
    QMenu *showMenu;

    QAction *actionCreatePlayer;
    QAction *actionExitApplication;
    QAction *actionShowTeamOfTheRound;
    QAction *actionShowTeamInfo;

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Tippeligaen *ui;
    QString _url;

private slots:
    void updatePlayerTableView(int row);
    void updateTeamWiki(int row);
    void updatePlayerInformation();
    void deletePlayer();
    void connectMainMenuSlots();

    //Menu-actions
    void actionCreatePlayer_triggered();
    void actionExitApplication_triggered();
    void actionShowTeamOfTheRound_triggered();
    void actionShowTeamInfo_triggered();

    void actionAddNewPlayerToDataBase();
};

#endif // TIPPELIGAEN_H
