#ifndef TIPPELIGAEN_H
#define TIPPELIGAEN_H

#include <QMainWindow>
#include <QtGui>

namespace Ui {
    class Tippeligaen;
}

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

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Tippeligaen *ui;

private slots:
    void on_actionAvslutt_triggered();
};

#endif // TIPPELIGAEN_H
