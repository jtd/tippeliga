#ifndef TIPPELIGAEN_H
#define TIPPELIGAEN_H

#include <QMainWindow>
#include <QtGui>
#include <QSqlRelationalTableModel>
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
    void createTeamWikiView();
    void createMakeNewPlayerView();
    void makeWindowMenues();
    QString url();

    QComboBox *teamComboBox;
    QGroupBox *createTeamChooserGroupBox();
    QTableView *playerTableView;
    QGroupBox *createTeamPlayersGroupBox();
    QGroupBox *createTeamOfTheRoundGroupBox();
    QGroupBox *createTeamWikiGroupBox();
    QLabel *fieldLabel;
    QGroupBox *createTeamInfoGroupBox();
    QLabel *drakt;
    QLabel *valerengaInfo;
    QSqlRelationalTableModel *model;
    QSqlRelationalTableModel *teamModel;
    QSqlRelationalTableModel *playerModel;
    QWebView *wiki;
    QGroupBox *teamOfTheRound;
    QGroupBox *teamWiki;
    QGridLayout *wikiLayout;
    QLabel *playerNameLabel, *playerTeamLabel, *playerPositionLabel;
    QLabel *playerName;
    QLabel *playerTeam;
    QLabel *playerPosition;
    QString selectedTeamUrl;
    QMenu *createPlayerMenu;
    QAction *createPlayerAction;

    QString *test;

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Tippeligaen *ui;
    QString _url;

private slots:
    void on_actionLaginfo_triggered();
    void on_actionUkens_lag_triggered();
    void on_actionAvslutt_triggered();
    void updatePlayerTableView(int row);
    void updateTeamWiki(int row);
    void updatePlayerInformation();
};

#endif // TIPPELIGAEN_H
