#ifndef TIPPELIGAEN_H
#define TIPPELIGAEN_H

#include <QMainWindow>
#include <QtGui>
#include <QSqlRelationalTableModel>

namespace Ui {
    class Tippeligaen;
}
enum {
    Spiller_Id = 0,
    Spiller_Fornavn = 1,
    Spiller_Etternavn = 2,
    Spiller_Draktnummer = 3,
    Spiller_Posisjon = 4,
    Spiller_LagID = 5
};

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
    QLabel *fieldLabel;
    QGroupBox *createTeamInfoGroupBox();
    QLabel *drakt;
    QLabel *valerengaInfo;
    QSqlRelationalTableModel *model;
    QSqlRelationalTableModel *teamModel;
    QSqlRelationalTableModel *playerModel;



protected:
    void changeEvent(QEvent *e);

private:
    Ui::Tippeligaen *ui;

private slots:
    void on_actionAvslutt_triggered();
    void updatePlayerTableView(int row);
};

#endif // TIPPELIGAEN_H
