#include "tippeligaen.h"
#include "ui_tippeligaen.h"

Tippeligaen::Tippeligaen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Tippeligaen)
{
    ui->setupUi(this);
}

Tippeligaen::~Tippeligaen()
{
    delete ui;
}

void Tippeligaen::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Tippeligaen::on_actionAvslutt_triggered()
{
    exit(0);
}
