#include "tippeligaen.h"
#include "ui_tippeligaen.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

Tippeligaen::Tippeligaen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Tippeligaen)
{
    ui->setupUi(this);
    QGroupBox *tippeligaLag = createTippeligaLagVelgerGroupBox();
    QGroupBox *spillerePaLag = createSpillerePaLagGroupBox();
    QGroupBox *rundensLag = createRundensLagGroupBox();
    QGroupBox *lagInfo = createLagInfoGroupBox();

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(tippeligaLag, 0, 0);
    layout->addWidget(spillerePaLag, 1, 0);
    layout->addWidget(lagInfo, 2 ,0);
    layout->addWidget(rundensLag, 0, 1, 3, 1);
    layout->setColumnStretch(1, 1);
    layout->setColumnMinimumWidth(0, 500);
    layout->setColumnMinimumWidth(1, 500);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);
    //createMenuBar();
    this->adjustSize();
    //showImageLabel();
    //resize(850, 400);
    setWindowTitle(tr("Tippeligaen 2010"));
}

Tippeligaen::~Tippeligaen(){
    delete ui;
}

void Tippeligaen::changeEvent(QEvent *e){
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Tippeligaen::on_actionAvslutt_triggered(){
    exit(0);
}
QGroupBox* Tippeligaen::createTippeligaLagVelgerGroupBox(){

    tippeligaLagComboBox = new QComboBox;

    /*
    QSqlQuery spiller ("select * from spiller" );
    while (spiller.next()) {
        tippeligaLagComboBox->addItem(spiller.value(1).toString());
    }
    */

    QSqlQuery lag ("select * from lag order by lagnavn asc" );
    while (lag.next()) {
        tippeligaLagComboBox->addItem(lag.value(1).toString());
    }

    connect(tippeligaLagComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(changeArtist(int)));

    QGroupBox *box = new QGroupBox(tr("Tippeligalag"));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(tippeligaLagComboBox, 0, 0);
    box->setLayout(layout);

    return box;
}

QGroupBox* Tippeligaen::createSpillerePaLagGroupBox(){
    QGroupBox *box = new QGroupBox(tr("Spillere"));

    model = new QSqlTableModel(this);
    model->setTable("spiller");
    model->setSort(Spiller_Etternavn, Qt::AscendingOrder);
    model->setHeaderData(Spiller_Fornavn, Qt::Horizontal, tr("Fornavn"));
    model->setHeaderData(Spiller_Etternavn, Qt::Horizontal, tr("Etternavn"));
    model->setHeaderData(Spiller_Draktnummer, Qt::Horizontal, tr("Draktnummer"));
    model->setHeaderData(Spiller_Posisjon, Qt::Horizontal, tr("Posisjon"));
    model->select();

    spillereTableView = new QTableView;
    spillereTableView->setModel(model);
    spillereTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    spillereTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    spillereTableView->setColumnHidden(Spiller_LagID, true);
    spillereTableView->setColumnHidden(Spiller_Id, true);
    spillereTableView->resizeColumnsToContents();
    spillereTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    spillereTableView->setSortingEnabled(true);
    QHeaderView *header = spillereTableView->horizontalHeader();
    header->setStretchLastSection(true);

    spillereTableView->setShowGrid(false);
    spillereTableView->verticalHeader()->hide();
    spillereTableView->setAlternatingRowColors(true);
    //albumView->setModel(model);
    //adjustHeader();

    QLocale locale = spillereTableView->locale();
    locale.setNumberOptions(QLocale::OmitGroupSeparator);
    spillereTableView->setLocale(locale);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(spillereTableView, 0, 0);
    box->setLayout(layout);

    return box;
}

QGroupBox* Tippeligaen::createRundensLagGroupBox()
{
    QGroupBox *box = new QGroupBox(tr("Rundenslag"));

    baneLabel = new QLabel;
    baneLabel->setPixmap(QPixmap(":/bilder/fullbaneTest.png"));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(baneLabel, 0,0);
    box->setLayout(layout);

    return box;
}

QGroupBox* Tippeligaen::createLagInfoGroupBox(){
    QGroupBox *box = new QGroupBox(tr("Spillerinfo"));

    drakt = new QLabel;
    drakt->setAlignment(Qt::AlignRight);
    drakt->setPixmap(QPixmap(":/bilder/valerenga.png"));

    QLabel *testlabel1 = new QLabel;
    testlabel1->setText("Spillernavn:");
    QLabel *testlabel2 = new QLabel;
    testlabel2->setText("Lag:");
    QLabel *testlabel3 = new QLabel;
    testlabel3->setText("Posisjon:");
    QLabel *testlabel4 = new QLabel;
    testlabel4->setText("Antallganger på rundens lag:");

    QLabel *spillerLabel1 = new QLabel;
    spillerLabel1->setText("Jon Torstein Dalen");
    QLabel *spillerLabel2 = new QLabel;
    spillerLabel2->setText("Vålerenga");
    QLabel *spillerLabel3 = new QLabel;
    spillerLabel3->setText("Midtstopper");
    QLabel *spillerLabel4 = new QLabel;
    spillerLabel4->setText("4");

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(testlabel1, 0, 0);
    layout->addWidget(spillerLabel1, 0, 1);
    layout->addWidget(testlabel2, 1, 0);
    layout->addWidget(spillerLabel2, 1, 1);
    layout->addWidget(testlabel3, 2, 0);
    layout->addWidget(spillerLabel3, 2, 1);
    layout->addWidget(testlabel4, 3, 0);
    layout->addWidget(spillerLabel4, 3, 1);

    //layout->addWidget(drakt, 0, 3, 3, 2);
    layout->addWidget(drakt, 0, 2, 4, 1);
    box->setLayout(layout);

    return box;
}
