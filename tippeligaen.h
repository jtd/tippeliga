#ifndef TIPPELIGAEN_H
#define TIPPELIGAEN_H

#include <QMainWindow>

namespace Ui {
    class Tippeligaen;
}

class Tippeligaen : public QMainWindow {
    Q_OBJECT
public:
    Tippeligaen(QWidget *parent = 0);
    ~Tippeligaen();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Tippeligaen *ui;
};

#endif // TIPPELIGAEN_H
