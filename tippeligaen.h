#ifndef TIPPELIGAEN_H
#define TIPPELIGAEN_H

#include <QMainWindow>
#include <QtGui>
#include <QSqlRelationalTableModel>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtSql>
#include "team.h"
#include "player.h"

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

    void setFieldLabel(QLabel *fieldLabel);
    QLabel *fieldLabel();
    void setShirtLabel(QLabel *shirtLabel);
    QLabel *shirtLabel();
    void setTeamOfTheRoundLabel(QLabel *teamOfTheRoundLabel);
    QLabel *teamOfTheRoundLabel();

    void createTeamWikiView();
    void makeWindowMenues();
    void createTeamInfoGroupBox();
    void createMakeNewPlayerView();
    void createTeamOfTheRoundChooseTeamGroupBox();
    void createTeamPlayersGroupBox();
    void makeUnknownShirt();
    void insertPlayerToTeamOfTheRound();
    void createTeamOfTheRoundShowTeam();


    QGridLayout *wikiLayout;
    QComboBox *teamComboBox;
    QComboBox *teamOfTheRoundChooseTeamComboBox;
    QGroupBox *createTeamChooserGroupBox();
    QGroupBox *teamOfTheRoundChooseTeamGroupBox;
    QGroupBox *players;
    QGroupBox *createTeamOfTheRoundGroupBox();
    QGroupBox *createTeamOfTheRoundShowTeamGroupBox;
    QGroupBox *playerInfoGroupBox;
    QGroupBox *teamOfTheRound;
    QGroupBox *teamWiki;
    QGroupBox *makePlayerGroupBox;
    QGroupBox *crateNewTeamOfTheRoundGroupBox;
    QTableView *playerTableView;
    QTableWidget *teamOfTheRoundTableWidget; //?
    QTextBrowser *textbrowser;
    QSqlRelationalTableModel *model;
    QSqlRelationalTableModel *teamModel;
    QSqlRelationalTableModel *playerModel;
    QSqlRelationalTableModel *teamOfTheRoundModel;
    QWebView *wiki;
    QString selectedTeamUrl;

    void crateNewTeamOfTheRound();
    QLineEdit *teamOfTheRoundLineEdit;
    QPushButton *teamOfTheRoundButton;

    QLineEdit *playerFirstNameEdit;
    QLineEdit *playerLastNameEdit;
    QLineEdit *shirtNumberEdit;
    QComboBox *playerPositionEdit;

    QPushButton *createNewPlayer;
    QGridLayout *mainLayout;
    QPushButton *deletePlayerButton;
    QPushButton *addToTeamOfTheRoundButton;

    int positionId;
    int teamOfTheRoundId;

    QMenu *fileMenu;
    QMenu *showMenu;
    QMenu *helpMenu;

    QAction *actionCreatePlayer;
    QAction *actionShowTeamOfTheRound;
    QAction *actionShowTeamInfo;
    QAction *actionShowPreviousTeamOfTheRound;
    QAction *actionCreateNewTeamOfTheRound;
    QAction *actionShowAboutMessage;

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

    QLabel *_shirtLabel;
    QLabel *_teamOfTheRoundLabel;

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
    void teamOfTheRoundButtonClicked();
    void actionShowAboutMessage_triggered();


};

#endif // TIPPELIGAEN_H
