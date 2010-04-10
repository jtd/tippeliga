#include "tippeligaen.h"
#include "ui_tippeligaen.h"
#include "shirt.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtSql>

Tippeligaen::Tippeligaen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Tippeligaen)
{
    this->setAcceptDrops(true);
    ui->setupUi(this);
    QGroupBox *team = createTeamChooserGroupBox();
    //QGroupBox *players = createTeamPlayersGroupBox();
    //QGroupBox *teamInfo = createTeamInfoGroupBox();
    createTeamPlayersGroupBox();
    createTeamInfoGroupBox();
    teamOfTheRound = createTeamOfTheRoundGroupBox();
    createTeamWikiView();
    teamWiki->hide();

    makeWindowMenues();

    createMakeNewPlayerView();
    makePlayerGroupBox->hide();
    //teamWiki = createTeamWikiGroupBox();
    //teamWiki->hide();


    QGridLayout *layout = new QGridLayout;
    layout->addWidget(team, 0, 0);
    layout->addWidget(players, 1, 0);
    layout->addWidget(teamInfo, 2 ,0);
    layout->addWidget(makePlayerGroupBox, 2, 0);
    layout->addWidget(teamOfTheRound, 0, 1, 3, 1);
    layout->addWidget(teamWiki, 0, 1, 3, 1);
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
    updatePlayerTableView(0);
    connect(playerTableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(updatePlayerInformation()));
    connect(teamComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateTeamWiki(int)));
    connect(createPlayerAction, SIGNAL(triggered()),
            this, SLOT(actionCreatePlayerTriggered()));
    connect(createNewPlayer, SIGNAL(clicked()),
            this, SLOT(actionAddNewPlayerToDataBase()));

}

Tippeligaen::~Tippeligaen(){
    delete ui;
}

void Tippeligaen::setUrl(QString url)
{
    _url = url;
}

QString Tippeligaen::url()
{
    return _url;
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

    QGroupBox *box = new QGroupBox(tr("Tippeligalag"));
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(teamComboBox, 0, 0);
    box->setLayout(layout);

    return box;
}

//QGroupBox*
void Tippeligaen::createTeamPlayersGroupBox(){
    //QGroupBox *box = new QGroupBox(tr("Spillere"));
    players = new QGroupBox(tr("Spillere"));

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
    players->setLayout(layout);

    //return box;
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
    //Teste litt her updateTeamWiki
    wiki = new QWebView();
    //playerName->setText(url());
    //QString url = selectedTeamUrl;
    wiki->load(QUrl("http://www.vg.no"));
    wiki->show();
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(wiki, 0,0);
    box->setLayout(layout);
    return box;
}

void Tippeligaen::createTeamWikiView(){
    teamWiki = new QGroupBox(tr("Wikipedia informasjon"));
    wikiLayout = new QGridLayout;
    teamWiki->setLayout(wikiLayout);

}

void Tippeligaen::createMakeNewPlayerView(){
    //teamInfo->hide();
    makePlayerGroupBox = new QGroupBox(tr("Registrer ny spiller"));

    playerFirstNameLabel = new QLabel;
    playerFirstNameLabel->setText(tr("Fornavn: "));
    playerLastNameLabel = new QLabel;
    playerLastNameLabel->setText(tr("Etternavn: "));
    shirtNumberLabel = new QLabel;
    shirtNumberLabel->setText(tr("Draktnummer: "));
    playerPositionLabel = new QLabel;
    playerPositionLabel->setText(tr("Posisjon: "));
    createNewPlayer = new QPushButton;
    createNewPlayer->setText(tr("Legg til ny spiller"));


    playerFirstNameEdit = new QLineEdit;
    playerLastNameEdit = new QLineEdit;
    playerPositionEdit = new QComboBox;
    shirtNumberEdit = new QLineEdit;
    playerPositionEdit->insertItem(0, tr("Keeper"));
    playerPositionEdit->insertItem(1, tr("Høyre Back"));
    playerPositionEdit->insertItem(2, tr("Venstre Back"));
    playerPositionEdit->insertItem(3, tr("MidtStopper"));
    playerPositionEdit->insertItem(4, tr("HøyreVing"));
    playerPositionEdit->insertItem(5, tr("VenstreVing"));
    playerPositionEdit->insertItem(6, tr("Midtbane"));
    playerPositionEdit->insertItem(7, tr("Spiss"));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(playerFirstNameLabel, 0, 0);
    layout->addWidget(playerFirstNameEdit, 0, 1);
    layout->addWidget(playerLastNameLabel, 1, 0);
    layout->addWidget(playerLastNameEdit, 1, 1);
    layout->addWidget(playerPositionLabel, 2, 0);
    layout->addWidget(playerPositionEdit, 2, 1);
    layout->addWidget(shirtNumberLabel, 3, 0);
    layout->addWidget(shirtNumberEdit, 3, 1);
    layout->addWidget(createNewPlayer, 4, 0);
    makePlayerGroupBox->setLayout(layout);

    makePlayerGroupBox->setMinimumHeight(170);
}

void Tippeligaen::createTeamInfoGroupBox(){
    teamInfo = new QGroupBox(tr("Spillerinfo"));

    //Shirt* s = new Shirt();
    shirt = new Shirt();
    shirtLabel = new QLabel(shirt);
    shirtLabel->setAlignment(Qt::AlignRight);

    shirt->addLabel(shirtLabel);
    playerNameLabel = new QLabel;
    playerNameLabel->setText(tr("Spillernavn: "));
    playerPositionLabel = new QLabel;
    playerPositionLabel->setText(tr("Posisjon: "));
    playerTeamLabel = new QLabel;
    playerTeamLabel->setText(tr("Lag: "));

    playerName = new QLabel;
    playerTeam = new QLabel;
    playerPosition = new QLabel;

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(playerNameLabel, 0, 0);
    layout->addWidget(playerName, 0, 1);
    layout->addWidget(playerPositionLabel, 1, 0);
    layout->addWidget(playerPosition, 1, 1);
    layout->addWidget(playerTeamLabel, 2, 0);
    layout->addWidget(playerTeam, 2, 1);
    layout->addWidget(shirt, 0, 2, 4, 1);
    teamInfo->setLayout(layout);

    teamInfo->setMinimumHeight(170);
    //return box;
}

void Tippeligaen::updatePlayerTableView(int row){
    QModelIndex index = teamModel->relationModel(0)->index(row, 0);
    QSqlRecord record = teamModel->record(row);
    //QModelIndex i = tippeligaLagComboBox->currentIndex();
    if(index.isValid()){
         playerModel->setFilter(QString("lagID = %1").arg(row));

         QString teamUrl = record.value("nettside").toString();
         //selectedTeamId = new QString;
         setUrl(teamUrl);
         selectedTeamUrl = teamUrl;
         //playerName->setText(selectedTeamUrl);


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

void Tippeligaen::updateTeamWiki(int row){
    QModelIndex index = teamModel->relationModel(0)->index(row, 0);
    QSqlRecord record = teamModel->record(row);
    if(index.isValid()){
         QString teamUrl = record.value("nettside").toString();
         playerName->setText(teamUrl);
         wiki = new QWebView();
         wiki->load(QUrl(teamUrl));
         //wiki->show();
         wikiLayout->addWidget(wiki, 0,0);
         teamWiki->setLayout(wikiLayout);
    }
    else{
        playerModel->setFilter("lagID = -1");
    }
}



void Tippeligaen::on_actionUkens_lag_triggered()
{
    teamOfTheRound->show();
    teamWiki->hide();
    ui->actionLaginfo->setChecked(false);
}

void Tippeligaen::on_actionLaginfo_triggered(){
    teamWiki->show();
    teamOfTheRound->hide();
    ui->actionUkens_lag->setChecked(false);
}

void Tippeligaen::actionCreatePlayerTriggered(){
    makePlayerGroupBox->show();
    teamInfo->hide();
}

void Tippeligaen::actionAddNewPlayerToDataBase(){
   QSqlQuery insertPlayer;
   insertPlayer.prepare("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, lagID)"
                        "VALUES (:fornavn, :etternavn, :draktnummer, :posisjon, :lagID)");
   insertPlayer.bindValue(":fornavn", playerFirstNameEdit->text());
   insertPlayer.bindValue(":etternavn", playerLastNameEdit->text());
   insertPlayer.bindValue(":draktnummer", shirtNumberEdit->text());
   insertPlayer.bindValue(":posisjon", playerPositionEdit->currentText());
   insertPlayer.bindValue(":lagID", teamComboBox->currentIndex());
   insertPlayer.exec();

   playerFirstNameEdit->setText("");
   playerLastNameEdit->setText("");
   shirtNumberEdit->setText("");

   /*delete players;
   createTeamPlayersGroupBox();
   players->show();*/

}

void Tippeligaen::updatePlayerInformation(){
    makePlayerGroupBox->hide();
    teamInfo->show();
    QModelIndex index = playerTableView->currentIndex();
    QSqlRecord record = playerModel->record(index.row());

    QString playerFirstNameString = record.value("fornavn").toString();
    QString playerLastNameString = record.value("etternavn").toString();
    QString playerPositionString = record.value("posisjon").toString();
    QString teamString = record.value("lagnavn").toString();

    playerName->setText(tr("%1 %2").arg(playerFirstNameString).arg(playerLastNameString));
    playerTeam->setText(tr("%1").arg(teamString));
    playerPosition->setText(tr("%1").arg(playerPositionString));

    QString picUrl = ":/bilder/" +teamString +".png";
    shirtLabel->setPixmap(QPixmap(picUrl));
}

void Tippeligaen::makeWindowMenues(){
    //Lager hovedmeny Window og setter action for dette.
    createPlayerMenu = new QMenu(this);
    createPlayerMenu->setTitle(tr("Rediger"));

    createPlayerAction = new QAction(tr("Opprett ny spiller"), createPlayerMenu);
    createPlayerMenu->addAction(createPlayerAction);
    ui->menuBar->addMenu(createPlayerMenu);

    /*connect(cascadeAction, SIGNAL(triggered()), this, SLOT(cascadeSubWindows()));
    tileAction = new QAction(tr("Tile"), fileMenu);*/
}

