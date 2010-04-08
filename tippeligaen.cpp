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
    connect(playerTableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(updatePlayerInformation()));
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
    fieldLabel->setAlignment(Qt::AlignTop);
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


    playerNameLabel = new QLabel;
    playerNameLabel->setText(tr("Spillernavn: "));
    playerPositionLabel = new QLabel;
    playerPositionLabel->setText(tr("Posisjon: "));
    playerTeamLabel = new QLabel;
    playerTeamLabel->setText(tr("Lag: "));


    playerName = new QLabel;
    playerTeam = new QLabel;
    playerPosition = new QLabel;

    /*QLabel *spillerLabel1 = new QLabel;
    spillerLabel1->setText("Jon Torstein Dalen");
    QLabel *spillerLabel2 = new QLabel;
    spillerLabel2->setText("Vålerenga");
    QLabel *spillerLabel3 = new QLabel;
    spillerLabel3->setText("Midtstopper");
    QLabel *spillerLabel4 = new QLabel;
    spillerLabel4->setText("4");
    playerInformationLabel = new QLabel;
    playerInformationLabel->setText("Hei på deg du!");*/

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(playerNameLabel, 0, 0);
    layout->addWidget(playerName, 0, 1);
    layout->addWidget(playerPositionLabel, 1, 0);
    layout->addWidget(playerPosition, 1, 1);
    layout->addWidget(playerTeamLabel, 2, 0);
    layout->addWidget(playerTeam, 2, 1);
    /*layout->addWidget(testlabel4, 3, 0);
    layout->addWidget(playerInformationLabel, 3, 1);*/

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
void Tippeligaen::updatePlayerInformation(){
    QModelIndex index = playerTableView->currentIndex();
    QSqlRecord record = playerModel->record(index.row());

    QString playerFirstNameString = record.value("fornavn").toString();
    QString playerLastNameString = record.value("etternavn").toString();
    QString playerPositionString = record.value("posisjon").toString();
    QString teamString = record.value("lagID").toString();

    playerName->setText(tr("%1 %2").arg(playerFirstNameString).arg(playerLastNameString));
    playerTeam->setText(tr("%1").arg(teamString));
    playerPosition->setText(tr("%1").arg(playerPositionString));
    //playerName->show();
    //playerInformationLabel->setText("Javell, morn!");
}
