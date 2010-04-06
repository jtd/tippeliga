#ifndef TIPPELIGAEN_H
#define TIPPELIGAEN_H

#include <QMainWindow>
#include <QtGui>
#include <QSqlTableModel>

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
    QComboBox *tippeligaLagComboBox;
    QGroupBox *createTippeligaLagVelgerGroupBox();
    QTableView *spillereTableView;
    QGroupBox *createSpillerePaLagGroupBox();
    QGroupBox *createRundensLagGroupBox();
    QLabel *baneLabel;
    QGroupBox *createLagInfoGroupBox();
    QLabel *drakt;
    QLabel *valerengaInfo;
    QSqlTableModel *model;


protected:
    void changeEvent(QEvent *e);

private:
    Ui::Tippeligaen *ui;

private slots:
    void on_actionAvslutt_triggered();
};

#endif // TIPPELIGAEN_H
