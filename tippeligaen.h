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
<<<<<<< HEAD
    QLabel *playerName;
=======
    QWebView *wiki;
    QGroupBox *teamOfTheRound;
    QGroupBox *teamWiki;
>>>>>>> 2300a9f1bb74be80ccce7c47b3cab2ea21c04a5e

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Tippeligaen *ui;

private slots:
    void on_actionLaginfo_triggered();
    void on_actionUkens_lag_triggered();
    void on_actionAvslutt_triggered();
    void updatePlayerTableView(int row);
    void playerInformation();
};

#endif // TIPPELIGAEN_H
