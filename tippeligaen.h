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
    void createTeamOfTheRoundChoosTeamGroupBox();
    void createTeamPlayersGroupBox();
    void makeUnknownShirt();
    void insertPlayerToTeamOfTheRound();
    void createTeamOfTheRoundShowTeam();

    QString url();

    QComboBox *teamComboBox;
    QGroupBox *createTeamChooserGroupBox();
    QTableView *playerTableView;
    QComboBox *teamOfTheRoundChooseTeamComboBox;
    QGroupBox *teamOfTheRoundChooseTeamGroupBox;
    QGroupBox *players;
    //QGroupBox *createTeamPlayersGroupBox();
    QGroupBox *createTeamOfTheRoundGroupBox();
    QGroupBox *createTeamWikiGroupBox();
    QGroupBox *createTeamOfTheRoundShowTeamGroupBox;
    QTableWidget *teamOfTheRoundTableWidget;
    QLabel *fieldLabel;
    QGroupBox *teamInfo;
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

    //Legger til ting som skal ligge i rundens lag.
    QLabel *k;
    QLabel *lb;
    QLabel *lcb;
    QLabel *rb;
    QLabel *rcb;
    QLabel *lw;
    QLabel *rw;
    QLabel *lcm;
    QLabel *rcm;
    QLabel *ls;
    QLabel *rs;
    QLabel *teamOfTheRoundIdLabel;

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
    QAction *actionCreateTeamOfTheRound;

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
    void addPlayerToTeamOfTheRound();
    void updateTeamOfTheRoundChoosTeamGroupBox();

    //Menu-actions
    void actionCreatePlayer_triggered();
    void actionExitApplication_triggered();
    void actionShowTeamOfTheRound_triggered();
    void actionShowTeamInfo_triggered();
    void actionAddNewTeamOfTheRound_triggered();

    void actionAddNewPlayerToDataBase();

};

#endif // TIPPELIGAEN_H
