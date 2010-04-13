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
    QString url();
    void setTeamOfTheRoundIdLabel(QLabel *teamOfTheRoundIdLabel);
    QLabel *teamOfTheRoundIdLabel();

    void setKeeper(QLabel *keeper);
    void setRightBack(QLabel *rightBack);
    void setRightCenterBack(QLabel *rightCenterBack);
    void setLeftCenterBack(QLabel *leftCenterBack);
    void setLeftBack(QLabel *leftBack);
    void setRightWing(QLabel *rightWing);
    void setRightCenterMidfielder(QLabel *rightCenterMidfielder);
    void setLeftCenterMidfielder(QLabel *leftCenterMidfielder);
    void setLeftWing(QLabel *leftWing);
    void setRightStriker(QLabel *rightStriker);
    void setLeftStriker(QLabel *leftStriker);
    QLabel *keeper();
    QLabel *rightBack();
    QLabel *rightCenterBack();
    QLabel *leftCenterBack();
    QLabel *leftBack();
    QLabel *rightWing();
    QLabel *rightCenterMidfielder();
    QLabel *leftCenterMidfielder();
    QLabel *leftWing();
    QLabel *rightStriker();
    QLabel *leftStriker();

    void setShirtNumberLabel(QLabel *shirtNumberLabel);
    void setPlayerFirstNameLabel(QLabel *playerFirstNameLabel);
    void setPlayerLastNameLabel(QLabel *playerLastNameLabel);
    void setPlayerNameLabel(QLabel *playerNameLabel);
    void setPlayerTeamLabel(QLabel *playerTeamLabel);
    void setPlayerPositionLabel(QLabel *playerPositionLabel);
    void setPlayerName(QLabel *playerName);
    void setPlayerTeam(QLabel *playerTeam);
    void setPlayerPosition(QLabel *playerPosition);
    QLabel *shirtNumberLabel();
    QLabel *playerFirstNameLabel();
    QLabel *playerLastNameLabel();
    QLabel *playerNameLabel();
    QLabel *playerTeamLabel();
    QLabel *playerPositionLabel();
    QLabel *playerName();
    QLabel *playerTeam();
    QLabel *playerPosition();


    void createTeamWikiView();

    void makeWindowMenues();
    void createTeamInfoGroupBox();
    void createMakeNewPlayerView();
    void createTeamOfTheRoundChooseTeamGroupBox();
    void createTeamPlayersGroupBox();
    void makeUnknownShirt();
    void insertPlayerToTeamOfTheRound();
    void createTeamOfTheRoundShowTeam();



    QComboBox *teamComboBox;
    QGroupBox *createTeamChooserGroupBox();
    QTableView *playerTableView;
    QComboBox *teamOfTheRoundChooseTeamComboBox;
    QGroupBox *teamOfTheRoundChooseTeamGroupBox;
    QGroupBox *players;
    //QGroupBox *createTeamPlayersGroupBox();
    QGroupBox *createTeamOfTheRoundGroupBox();
    QGroupBox *createTeamOfTheRoundShowTeamGroupBox;
    QTableWidget *teamOfTheRoundTableWidget;
    QTextBrowser *textbrowser;
    //QTableView *teamOfTheRoundTableView;
    QLabel *fieldLabel;
    QGroupBox *playerInfoGroupBox;
    //QGroupBox *createTeamInfoGroupBox();
    QLabel *shirtLabel;
    QLabel *valerengaInfo;
    QSqlRelationalTableModel *model;
    QSqlRelationalTableModel *teamModel;
    QSqlRelationalTableModel *playerModel;
    QSqlRelationalTableModel *teamOfTheRoundModel;
    QWebView *wiki;
    QGroupBox *teamOfTheRound;
    QGroupBox *teamWiki;
    QGridLayout *wikiLayout;
    QGroupBox *makePlayerGroupBox;
    QString selectedTeamUrl;

    QLineEdit *playerFirstNameEdit;
    QLineEdit *playerLastNameEdit;
    QComboBox *playerPositionEdit;
    QLineEdit *shirtNumberEdit;

    QPushButton *createNewPlayer;
    QGridLayout *mainLayout;
    QPushButton *deletePlayerButton;
    QPushButton *addToTeamOfTheRoundButton;

    //Legger til ting som skal ligge i rundens lag.

    int positionId;
    int teamOfTheRoundId;


    QString *test;
    Shirt *shirt;
    Field *field;

    QMenu *fileMenu;
    QMenu *showMenu;

    QAction *actionCreatePlayer;
    QAction *actionExitApplication;
    QAction *actionShowTeamOfTheRound;
    QAction *actionShowTeamInfo;
    QAction *actionShowPreviousTeamOfTheRound;
    QAction *actionCreateNewTeamOfTheRound;

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Tippeligaen *ui;
    QString _url;

    QLabel *_teamOfTheRoundIdLabel;

    QLabel *_keeper;
    QLabel *_rightBack;
    QLabel *_rightCenterBack;
    QLabel *_leftCenterBack;
    QLabel *_leftBack;
    QLabel *_rightWing;
    QLabel *_rightCenterMidfielder;
    QLabel *_leftCenterMidfielder;
    QLabel *_leftWing;
    QLabel *_rightStriker;
    QLabel *_leftStriker;

    QLabel *_shirtNumberLabel;
    QLabel *_playerFirstNameLabel;
    QLabel *_playerLastNameLabel;
    QLabel *_playerNameLabel;
    QLabel *_playerTeamLabel;
    QLabel *_playerPositionLabel;
    QLabel *_playerName;
    QLabel *_playerTeam;
    QLabel *_playerPosition;

private slots:
    void doAtStartUp();

    void updatePlayerTableView(int row);
    void updateTeamWiki(int row);
    void updatePlayerInformation();
    void deletePlayer();
    void connectMainMenuSlots();
    void addPlayerToTeamOfTheRound();
    void updateTeamOfTheRoundChooseTeamGroupBox();
    void updateTeamOfTheRoundTable();
    void actionAddNewPlayerToDataBase();

    //Menu-actions
    void actionCreatePlayer_triggered();
    void actionExitApplication_triggered();
    void actionShowTeamOfTheRound_triggered();
    void actionShowTeamInfo_triggered();
    void actionShowPreviousTeamOfTheRound_triggered();
    void actionCreateNewTeamOfTheRound_triggered();


};

#endif // TIPPELIGAEN_H
