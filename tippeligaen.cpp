#include "tippeligaen.h"
#include "ui_tippeligaen.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtSql>

Tippeligaen::Tippeligaen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Tippeligaen)
{
    ui->setupUi(this);
    QGroupBox *team = createTeamChooserGroupBox();
    QGroupBox *players = createTeamPlayersGroupBox();
    QGroupBox *teamInfo = createTeamInfoGroupBox();
    teamOfTheRound = createTeamOfTheRoundGroupBox();
    teamWiki = createTeamWikiGroupBox();
    teamWiki->hide();

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(team, 0, 0);
    layout->addWidget(players, 1, 0);
    layout->addWidget(teamInfo, 2 ,0);
    layout->addWidget(teamOfTheRound, 0, 1, 3, 1);
    layout->addWidget(teamWiki, 0, 1, 3, 1);
    layout->setColumnStretch(1, 1);
    layout->setColumnMinimumWidth(0, 500);
    layout->setColumnMinimumWidth(1, 700);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);
    //createMenuBar();
    this->adjustSize();
    //showImageLabel();
    //resize(850, 400);
    setWindowTitle(tr("Tippeligaen 2010"));

    updatePlayerTableView(0);
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
QGroupBox* Tippeligaen::createTeamChooserGroupBox(){

    teamComboBox = new QComboBox;
    teamModel = new QSqlRelationalTableModel(this);
    teamModel->setTable("lag");
    teamModel->setRelation(0, QSqlRelation("lag", "id", "lagnavn"));
    teamModel->setSort(1, Qt::AscendingOrder);
    teamModel->select();

    teamComboBox->setModel(teamModel);

    connect(teamComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updatePlayerTableView(int)));

    /*QSqlQuery lag ("select * from lag order by lagnavn asc" );
    while (lag.next()) {
        tippeligaLagComboBox->addItem(lag.value(1).toString());
    }*/

    QGroupBox *box = new QGroupBox(tr("Tippeligalag"));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(teamComboBox, 0, 0);
    box->setLayout(layout);

    return box;
}

QGroupBox* Tippeligaen::createTeamPlayersGroupBox(){
    QGroupBox *box = new QGroupBox(tr("Spillere"));

    /*model = new QSqlRelationalTableModel(this);
    model->setTable("spiller");
    model->setSort(Spiller_Etternavn, Qt::AscendingOrder);
    model->setHeaderData(Spiller_Fornavn, Qt::Horizontal, tr("Fornavn"));
    model->setHeaderData(Spiller_Etternavn, Qt::Horizontal, tr("Etternavn"));
    model->setHeaderData(Spiller_Draktnummer, Qt::Horizontal, tr("Draktnummer"));
    model->setHeaderData(Spiller_Posisjon, Qt::Horizontal, tr("Posisjon"));
    model->select();*/

    playerModel = new QSqlRelationalTableModel(this);
    playerModel->setTable("spiller");
    playerModel->setRelation(Spiller_LagID, QSqlRelation("lag", "id", "lagnavn"));
    playerModel->setSort(Spiller_Etternavn, Qt::AscendingOrder);
    playerModel->setHeaderData(Spiller_Fornavn, Qt::Horizontal, tr("Fornavn"));
    playerModel->setHeaderData(Spiller_Etternavn, Qt::Horizontal, tr("Etternavn"));
    playerModel->setHeaderData(Spiller_Draktnummer, Qt::Horizontal, tr("Draktnummer"));
    playerModel->setHeaderData(Spiller_Posisjon, Qt::Horizontal, tr("Posisjon"));
    playerModel->setHeaderData(Spiller_LagID, Qt::Horizontal, tr("Lag"));

    playerTableView = new QTableView;
    playerTableView->setModel(playerModel);
    playerTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    playerTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //playerTableView->setColumnHidden(Spiller_LagID, true);
    playerTableView->setColumnHidden(Spiller_Id, true);
    playerTableView->resizeColumnsToContents();
    playerTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    playerTableView->setSortingEnabled(true);
    QHeaderView *header = playerTableView->horizontalHeader();
    header->setStretchLastSection(true);

    playerTableView->setShowGrid(false);
    playerTableView->verticalHeader()->hide();
    playerTableView->setAlternatingRowColors(true);
    //albumView->setModel(model);
    //adjustHeader();

    QLocale locale = playerTableView->locale();
    locale.setNumberOptions(QLocale::OmitGroupSeparator);
    playerTableView->setLocale(locale);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(playerTableView, 0, 0);
    box->setLayout(layout);

    return box;
}

QGroupBox* Tippeligaen::createTeamOfTheRoundGroupBox(){
    QGroupBox *box = new QGroupBox(tr("Rundens lag"));
 
    fieldLabel = new QLabel;
    fieldLabel->setPixmap(QPixmap(":/bilder/fullbaneTest.png"));
    fieldLabel->show();
    
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(fieldLabel, 0,0);
    box->setLayout(layout);

    return box;
}
QGroupBox* Tippeligaen::createTeamWikiGroupBox(){
    QGroupBox *box = new QGroupBox(tr("Wiki"));

    wiki = new QWebView();
    wiki->load(QUrl("http://no.wikipedia.org/wiki/Vålerenga_fotball"));
    wiki->show();

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(wiki, 0,0);
    box->setLayout(layout);

    return box;
}

QGroupBox* Tippeligaen::createTeamInfoGroupBox(){
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
    testlabel4->setText("Antall ganger på rundens lag:");

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

void Tippeligaen::updatePlayerTableView(int row){
    QModelIndex index = teamModel->relationModel(0)->index(row, 0);
    //QModelIndex i = tippeligaLagComboBox->currentIndex();
    if(index.isValid()){
         playerModel->setFilter(QString("lagID = %1").arg(row));

        /*QSqlRecord record = teamModel->record(row);
        int id = record.value("id").toInt();
        playerModel->setFilter(QString("lagID = %1").arg(id));*/
    }
    else{
        playerModel->setFilter("lagID = -1");
    }
    playerModel->select();
    playerTableView->horizontalHeader()->setVisible(playerModel->rowCount()>0);
}

void Tippeligaen::on_actionUkens_lag_triggered()
{
    teamOfTheRound->show();;
    teamWiki->hide();
    ui->actionLaginfo->setChecked(false);
}

void Tippeligaen::on_actionLaginfo_triggered()
{
    teamWiki->show();
    teamOfTheRound->hide();
    ui->actionUkens_lag->setChecked(false);

}
