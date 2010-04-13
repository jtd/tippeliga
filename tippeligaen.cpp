#include "tippeligaen.h"
#include "ui_tippeligaen.h"



Tippeligaen::Tippeligaen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Tippeligaen)
{
    ui->setupUi(this);


    QGroupBox *team = createTeamChooserGroupBox();
    teamOfTheRound = createTeamOfTheRoundGroupBox();
    createTeamPlayersGroupBox();
    createTeamInfoGroupBox();
    createTeamOfTheRoundChooseTeamGroupBox();
    createTeamWikiView();
    createTeamOfTheRoundShowTeam();
    crateNewTeamOfTheRound();

    makeWindowMenues();
    createMakeNewPlayerView();

    doAtStartUp();

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(team, 0, 0);
    layout->addWidget(players, 1, 0);
    layout->addWidget(playerInfoGroupBox, 2 ,0);
    layout->addWidget(makePlayerGroupBox, 2, 0);
    layout->addWidget(crateNewTeamOfTheRoundGroupBox, 2, 0);
    layout->addWidget(teamOfTheRound, 0, 1, 3, 1);
    layout->addWidget(teamWiki, 0, 1, 3, 1);
    layout->addWidget(teamOfTheRoundChooseTeamGroupBox, 0, 1);
    layout->addWidget(createTeamOfTheRoundShowTeamGroupBox, 1, 1);
    layout->setColumnStretch(1, 1);
    layout->setColumnMinimumWidth(0, 500);
    layout->setColumnMinimumWidth(1, 500);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);

    this->adjustSize();
    setWindowTitle(tr("Tippeligaen 2010"));


    connect(playerTableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(updatePlayerInformation()));
    connect(teamComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateTeamWiki(int)));
    connect(deletePlayerButton, SIGNAL(clicked()),
            this, SLOT(deletePlayer()));
    connect(createNewPlayer, SIGNAL(clicked()),
            this, SLOT(actionAddNewPlayerToDataBase()));
    connect(addToTeamOfTheRoundButton, SIGNAL(clicked()),
            this, SLOT(addPlayerToTeamOfTheRound()));
    connect(teamOfTheRoundChooseTeamComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateTeamOfTheRoundTable()));
    connect(teamOfTheRoundButton, SIGNAL(clicked()),
            this, SLOT(teamOfTheRoundButtonClicked()));
    connectMainMenuSlots();
}

Tippeligaen::~Tippeligaen(){
    delete ui;
    delete _keeper;
    delete _rightBack;
    delete _rightCenterBack;
    delete _leftCenterBack;
    delete _leftBack;
    delete _rightWing;
    delete _rightCenterMidfielder;
    delete _leftCenterMidfielder;
    delete _leftWing;
    delete _rightStriker;
    delete _leftStriker;
    delete _teamOfTheRoundIdLabel;
}

void Tippeligaen::doAtStartUp(){
    teamWiki->hide();
    makePlayerGroupBox->hide();
    teamOfTheRoundChooseTeamGroupBox->hide();
    createTeamOfTheRoundShowTeamGroupBox->hide();
    updatePlayerTableView(0);
    updateTeamWiki(0);
    playerInfoGroupBox->hide();
    crateNewTeamOfTheRoundGroupBox->show();
}

void Tippeligaen::setUrl(QString url){
    _url = url;
}
QString Tippeligaen::url()
{
    return _url;
}

void Tippeligaen::setKeeper(QLabel *keeper){
    _keeper = keeper;
}
QLabel* Tippeligaen::keeper(){
    return _keeper;
}
void Tippeligaen::setRightBack(QLabel *rightBack){
    _rightBack = rightBack;
}
QLabel* Tippeligaen::rightBack(){
    return _rightBack;
}
void Tippeligaen::setRightCenterBack(QLabel *rightCenterBack){
    _rightCenterBack = rightCenterBack;
}
QLabel* Tippeligaen::rightCenterBack(){
    return _rightCenterBack;
}
void Tippeligaen::setLeftCenterBack(QLabel *leftCenterBack){
    _leftCenterBack = leftCenterBack;
}
QLabel* Tippeligaen::leftCenterBack(){
    return _leftCenterBack;
}
void Tippeligaen::setLeftBack(QLabel *leftBack){
    _leftBack = leftBack;
}
QLabel* Tippeligaen::leftBack(){
    return _leftBack;
}
void Tippeligaen::setRightWing(QLabel *rightWing){
    _rightWing = rightWing;
}
QLabel* Tippeligaen::rightWing(){
    return _rightWing;
}
void Tippeligaen::setRightCenterMidfielder(QLabel *rightCenterMidfielder){
    _rightCenterMidfielder = rightCenterMidfielder;
}
QLabel* Tippeligaen::rightCenterMidfielder(){
    return _rightCenterMidfielder;
}
void Tippeligaen::setLeftCenterMidfielder(QLabel *leftCenterMidfielder){
    _leftCenterMidfielder = leftCenterMidfielder;
}
QLabel* Tippeligaen::leftCenterMidfielder(){
    return _leftCenterMidfielder;
}
void Tippeligaen::setLeftWing(QLabel *leftWing){
    _leftWing = leftWing;
}
QLabel* Tippeligaen::leftWing(){
    return _leftWing;
}
void Tippeligaen::setRightStriker(QLabel *rightStriker){
    _rightStriker = rightStriker;
}
QLabel* Tippeligaen::rightStriker(){
    return _rightStriker;
}
void Tippeligaen::setLeftStriker(QLabel *leftStriker){
    _leftStriker = leftStriker;
}
QLabel* Tippeligaen::leftStriker(){
    return _leftStriker;
}
void Tippeligaen::setTeamOfTheRoundIdLabel(QLabel *teamOfTheRoundIdLabel){
    _teamOfTheRoundIdLabel = teamOfTheRoundIdLabel;
}
QLabel* Tippeligaen::teamOfTheRoundIdLabel(){
    return _teamOfTheRoundIdLabel;
}

void Tippeligaen::setShirtNumberLabel(QLabel *shirtNumberLabel){
    _shirtNumberLabel = shirtNumberLabel;
}
QLabel* Tippeligaen::shirtNumberLabel(){
    return _shirtNumberLabel;
}

void Tippeligaen::setPlayerFirstNameLabel(QLabel *playerFirstNameLabel){
    _playerFirstNameLabel = playerFirstNameLabel;
}
QLabel* Tippeligaen::playerFirstNameLabel(){
    return _playerFirstNameLabel;
}

void Tippeligaen::setPlayerLastNameLabel(QLabel *playerLastNameLabel){
    _playerLastNameLabel = playerLastNameLabel;
}
QLabel* Tippeligaen::playerLastNameLabel(){
    return _playerLastNameLabel;
}

void Tippeligaen::setFieldLabel(QLabel *fieldLabel){
    _fieldLabel = fieldLabel;
}
QLabel* Tippeligaen::fieldLabel(){
    return _fieldLabel;
}

void Tippeligaen::setShirtLabel(QLabel *shirtLabel){
    _shirtLabel = shirtLabel;
}
QLabel* Tippeligaen::shirtLabel(){
    return _shirtLabel;
}

void Tippeligaen::setPlayerNameLabel(QLabel *playerNameLabel){
    _playerNameLabel = playerNameLabel;
}
QLabel* Tippeligaen::playerNameLabel(){
    return _playerNameLabel;
}

void Tippeligaen::setPlayerTeamLabel(QLabel *playerTeamLabel){
    _playerTeamLabel = playerTeamLabel;
}
QLabel* Tippeligaen::playerTeamLabel(){
    return _playerTeamLabel;
}

void Tippeligaen::setPlayerPositionLabel(QLabel *playerPositionLabel){
    _playerPositionLabel = playerPositionLabel;
}
QLabel* Tippeligaen::playerPositionLabel(){
    return _playerPositionLabel;
}

void Tippeligaen::setPlayerName(QLabel *playerName){
    _playerName = playerName;
}
QLabel* Tippeligaen::playerName(){
    return _playerName;
}

void Tippeligaen::setPlayerTeam(QLabel *playerTeam){
    _playerTeam = playerTeam;
}
QLabel* Tippeligaen::playerTeam(){
    return _playerTeam;
}

void Tippeligaen::setPlayerPosition(QLabel *playerPosition){
    _playerPosition = playerPosition;
}
QLabel* Tippeligaen::playerPosition(){
    return _playerPosition;
}

void Tippeligaen::setTeamOfTheRoundLabel(QLabel *teamOfTheRoundLabel){
    _teamOfTheRoundLabel = teamOfTheRoundLabel;
}
QLabel* Tippeligaen::teamOfTheRoundLabel(){
    return _teamOfTheRoundLabel;
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
    playerModel->setSort(Spiller_Id, Qt::AscendingOrder);
    playerModel->setHeaderData(Spiller_Id, Qt::Horizontal, tr("Id"));
    playerModel->setHeaderData(Spiller_Fornavn, Qt::Horizontal, tr("Fornavn"));
    playerModel->setHeaderData(Spiller_Etternavn, Qt::Horizontal, tr("Etternavn"));
    playerModel->setHeaderData(Spiller_Draktnummer, Qt::Horizontal, tr("Draktnummer"));
    playerModel->setHeaderData(Spiller_Posisjon, Qt::Horizontal, tr("Posisjon"));
    playerModel->setHeaderData(Spiller_LagID, Qt::Horizontal, tr("Lag"));
    playerModel->setHeaderData(Spiller_PosisjonsId, Qt::Horizontal, tr("Posisjonsid"));

    playerTableView = new QTableView;
    playerTableView->setModel(playerModel);
    playerTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    playerTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    playerTableView->setColumnHidden(Spiller_Id, true);
    playerTableView->setColumnHidden(Spiller_LagID, true);
    playerTableView->setColumnHidden(Spiller_PosisjonsId, true);
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

    QLabel *fieldImage = new QLabel();
    fieldImage->setPixmap(QPixmap(":/bilder/field.png"));
    box->setStyleSheet("QGroupBox { "
                            "background-image: url(:/bilder/field.png);"
                            "background-repeat: none;"
                            "border: 20px solid;"
                            "border-color: none; "
                        "}");

    _keeper = new QLabel;
    _rightBack = new QLabel;
    _rightCenterBack = new QLabel;
    _leftCenterBack = new QLabel;
    _leftBack = new QLabel;
    _leftWing = new QLabel;
    _rightWing = new QLabel;
    _rightCenterMidfielder = new QLabel;
    _leftCenterMidfielder = new QLabel;
    _leftStriker = new QLabel;
    _rightStriker = new QLabel;
    _teamOfTheRoundIdLabel= new QLabel;
    _teamOfTheRoundIdLabel->setText("Rundens lag 1");

    makeUnknownShirt();

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(keeper(), 0, 2, 1, 4);
    layout->addWidget(rightBack(), 1, 0);
    layout->addWidget(rightCenterBack(), 1, 1);
    layout->addWidget(leftCenterBack(), 1, 3);
    layout->addWidget(leftBack(), 1, 4);
    layout->addWidget(rightWing(), 2, 0);
    layout->addWidget(rightCenterMidfielder(), 2, 1);
    layout->addWidget(leftCenterMidfielder(), 2, 3);
    layout->addWidget(leftWing(), 2, 4);
    layout->addWidget(rightStriker(), 3, 1);
    layout->addWidget(leftStriker(), 3, 3);
    layout->addWidget(teamOfTheRoundIdLabel(), 4, 0, 4, 0, Qt::AlignHCenter);
    teamOfTheRoundIdLabel()->setStyleSheet("color: #fff; font-size: 20px;");
    box->setLayout(layout);
    return box;
}

void Tippeligaen::makeUnknownShirt(){
    QPixmap unknownShirt(":/bilder/Unknown.png");
    keeper()->setPixmap(unknownShirt);
    rightBack()->setPixmap(unknownShirt);
    rightCenterBack()->setPixmap(unknownShirt);
    leftCenterBack()->setPixmap(unknownShirt);
    leftBack()->setPixmap(unknownShirt);
    rightWing()->setPixmap(unknownShirt);
    rightCenterMidfielder()->setPixmap(unknownShirt);
    leftCenterMidfielder()->setPixmap(unknownShirt);
    leftWing()->setPixmap(unknownShirt);
    rightStriker()->setPixmap(unknownShirt);
    leftStriker()->setPixmap(unknownShirt);
}

void Tippeligaen::createTeamWikiView(){
    teamWiki = new QGroupBox(tr("Wikipedia informasjon"));
    wikiLayout = new QGridLayout;
    teamWiki->setLayout(wikiLayout);

}

void Tippeligaen::createMakeNewPlayerView(){
    makePlayerGroupBox = new QGroupBox(tr("Registrer ny spiller"));

    _playerFirstNameLabel = new QLabel;
    _playerFirstNameLabel->setText(tr("Fornavn: "));
    _playerLastNameLabel = new QLabel;
    _playerLastNameLabel->setText(tr("Etternavn: "));
    _shirtNumberLabel = new QLabel;
    _shirtNumberLabel->setText(tr("Draktnummer: "));
    _playerPositionLabel = new QLabel;
    _playerPositionLabel->setText(tr("Posisjon: "));
    createNewPlayer = new QPushButton;
    createNewPlayer->setText(tr("Legg til ny spiller"));


    playerFirstNameEdit = new QLineEdit;
    playerLastNameEdit = new QLineEdit;
    playerPositionEdit = new QComboBox;
    shirtNumberEdit = new QLineEdit;
    playerPositionEdit->insertItem(0, tr("Keeper"));
    playerPositionEdit->insertItem(1, tr("Høyre back"));
    playerPositionEdit->insertItem(2, tr("Venstre back"));
    playerPositionEdit->insertItem(3, tr("Venstre midtstopper"));
    playerPositionEdit->insertItem(4, tr("Høyre midtstopper"));
    playerPositionEdit->insertItem(5, tr("Høyre ving"));
    playerPositionEdit->insertItem(6, tr("Venstre ving"));
    playerPositionEdit->insertItem(7, tr("Venstre midtbane"));
    playerPositionEdit->insertItem(8, tr("Høyre midtbane"));
    playerPositionEdit->insertItem(9, tr("Venstre spiss"));
    playerPositionEdit->insertItem(10, tr("Høyre spiss"));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(playerFirstNameLabel(), 0, 0);
    layout->addWidget(playerFirstNameEdit, 0, 1);
    layout->addWidget(playerLastNameLabel(), 1, 0);
    layout->addWidget(playerLastNameEdit, 1, 1);
    layout->addWidget(playerPositionLabel(), 2, 0);
    layout->addWidget(playerPositionEdit, 2, 1);
    layout->addWidget(shirtNumberLabel(), 3, 0);
    layout->addWidget(shirtNumberEdit, 3, 1);
    layout->addWidget(createNewPlayer, 4, 0);
    makePlayerGroupBox->setLayout(layout);

    makePlayerGroupBox->setMinimumHeight(170);
}

void Tippeligaen::crateNewTeamOfTheRound(){
    crateNewTeamOfTheRoundGroupBox = new QGroupBox(tr("Lag nytt rundens lag"));

    _teamOfTheRoundLabel = new QLabel;
    _teamOfTheRoundLabel->setText(tr("Navn på rundens lag: "));
    teamOfTheRoundLineEdit = new QLineEdit;
    teamOfTheRoundButton = new QPushButton;
    teamOfTheRoundButton->setText(tr("Lag rundens lag"));
   
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(teamOfTheRoundLabel(), 0, 0);
    layout->addWidget(teamOfTheRoundLineEdit, 0, 1);
    layout->addWidget(teamOfTheRoundButton, 0, 2);
    crateNewTeamOfTheRoundGroupBox->setLayout(layout);
    crateNewTeamOfTheRoundGroupBox->setMinimumHeight(170);
}

void Tippeligaen::teamOfTheRoundButtonClicked(){
    if(teamOfTheRoundLineEdit->text() == ""){
        QMessageBox *errorMessage = new QMessageBox;
        errorMessage->setText(tr("Fyll inn navn på rundens lag"));
        errorMessage->setWindowTitle(tr("Feil"));
        errorMessage->setWindowFlags(Qt::Drawer);
        errorMessage->show();
        return;
    }

    QMessageBox *saveMessage = new QMessageBox;
    saveMessage->setText("Du kan nå legge til spillere i " + teamOfTheRoundLineEdit->text());
    saveMessage->setWindowTitle(tr("Lagret"));
    saveMessage->setWindowFlags(Qt::Drawer);
    saveMessage->show();

    actionShowTeamOfTheRound_triggered();
    makeUnknownShirt();
    teamOfTheRoundIdLabel()->setText(teamOfTheRoundLineEdit->text());
}

void Tippeligaen::createTeamInfoGroupBox(){
    playerInfoGroupBox = new QGroupBox(tr("Spillerinfo"));
    _shirtLabel = new QLabel();
    _shirtLabel->setAlignment(Qt::AlignRight);
    _shirtLabel->setPixmap(QPixmap(":/bilder/Aalesund.png"));

    _playerNameLabel = new QLabel;
    _playerNameLabel->setText(tr("Spillernavn: "));
    _playerPositionLabel = new QLabel;
    _playerPositionLabel->setText(tr("Posisjon: "));
    _playerTeamLabel = new QLabel;
    _playerTeamLabel->setText(tr("Lag: "));

    deletePlayerButton = new QPushButton;
    deletePlayerButton->setText(tr("Slett"));
    addToTeamOfTheRoundButton = new QPushButton;
    addToTeamOfTheRoundButton->setText(tr("Legg til i rundens lag"));

    _playerName = new QLabel;
    _playerTeam = new QLabel;
    _playerPosition = new QLabel;

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(playerNameLabel(), 0, 0);
    layout->addWidget(playerName(), 0, 1);
    layout->addWidget(playerPositionLabel(), 1, 0);
    layout->addWidget(playerPosition(), 1, 1);
    layout->addWidget(playerTeamLabel(), 2, 0);
    layout->addWidget(playerTeam(), 2, 1);
    layout->addWidget(deletePlayerButton, 3, 0);
    layout->addWidget(addToTeamOfTheRoundButton, 3, 1);
    layout->addWidget(shirtLabel(), 0, 2, 4, 1);
    playerInfoGroupBox->setLayout(layout);

    playerInfoGroupBox->setMinimumHeight(170);
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
    playerInfoGroupBox->hide();
    QModelIndex index = teamModel->relationModel(0)->index(row, 0);
    QSqlRecord record = teamModel->record(row);
    if(index.isValid()){
         QString teamUrl = record.value("nettside").toString();
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

void Tippeligaen::updatePlayerInformation(){
    makePlayerGroupBox->hide();
    crateNewTeamOfTheRoundGroupBox->hide();
    playerInfoGroupBox->show();

    QModelIndex index = playerTableView->currentIndex();
    QSqlRecord record = playerModel->record(index.row());

    QString playerFirstNameString = record.value("fornavn").toString();
    QString playerLastNameString = record.value("etternavn").toString();
    QString playerPositionString = record.value("posisjon").toString();
    QString teamString = record.value("lagnavn").toString();

    positionId = record.value("posisjonsId").toInt();

    _playerName->setText(tr("%1 %2").arg(playerFirstNameString).arg(playerLastNameString));
    _playerTeam->setText(tr("%1").arg(teamString));
    _playerPosition->setText(tr("%1").arg(playerPositionString));

    QString picUrl = ":/bilder/" +teamString +".png";
    _shirtLabel->setPixmap(QPixmap(picUrl));
}

void Tippeligaen::makeWindowMenues(){
//-FIL
    fileMenu = new QMenu(this);
    fileMenu->setTitle(tr("Fil"));

    actionCreatePlayer = new QAction(tr("Legg til spiller"), fileMenu);
    actionCreateNewTeamOfTheRound = new QAction(tr("Lag nytt \"Rundens lag\""), fileMenu);
    actionExitApplication = new QAction(tr("Avslutt"), fileMenu);

    fileMenu->addAction(actionCreatePlayer);
    fileMenu->addAction(actionCreateNewTeamOfTheRound);
    fileMenu->addSeparator();
    fileMenu->addAction(actionExitApplication);

//-VIS
    showMenu = new QMenu(this);
    showMenu->setTitle(tr("Vis"));

    actionShowTeamOfTheRound = new QAction(tr("Rundens lag"), showMenu);
    actionShowTeamOfTheRound->setCheckable(true);
    actionShowTeamOfTheRound->setChecked(true);

    actionShowTeamInfo = new QAction(tr("Laginfo"), showMenu);
    actionShowTeamInfo->setCheckable(true);

    actionShowPreviousTeamOfTheRound = new QAction(tr("Lagrede \"Rundens lag\""), fileMenu);
    actionShowPreviousTeamOfTheRound->setCheckable(true);

    showMenu->addAction(actionShowTeamOfTheRound);
    showMenu->addAction(actionShowTeamInfo);
    showMenu->addAction(actionShowPreviousTeamOfTheRound);
    showMenu->addSeparator();

    ui->menuBar->addMenu(fileMenu);
    ui->menuBar->addMenu(showMenu);
    /*connect(cascadeAction, SIGNAL(triggered()), this, SLOT(cascadeSubWindows()));
    tileAction = new QAction(tr("Tile"), fileMenu);*/
}

void Tippeligaen::connectMainMenuSlots() {
    connect(actionCreatePlayer, SIGNAL(triggered()),
        this, SLOT(actionCreatePlayer_triggered()));
    connect(actionCreateNewTeamOfTheRound, SIGNAL(triggered()),
        this, SLOT(actionCreateNewTeamOfTheRound_triggered()));
    connect(actionExitApplication, SIGNAL(triggered()),
        this, SLOT(actionExitApplication_triggered()));

    connect(actionShowTeamOfTheRound, SIGNAL(triggered()),
        this, SLOT(actionShowTeamOfTheRound_triggered()));
    connect(actionShowTeamInfo, SIGNAL(triggered()),
        this, SLOT(actionShowTeamInfo_triggered()));
    connect(actionShowPreviousTeamOfTheRound, SIGNAL(triggered()),
            this, SLOT(actionShowPreviousTeamOfTheRound_triggered()));
    connect(actionShowPreviousTeamOfTheRound, SIGNAL(triggered()),
            this, SLOT(updateTeamOfTheRoundChooseTeamGroupBox()));
    /*connect(actionCreateTeamOfTheRound, SIGNAL(triggered()),
            this, SLOT(updateTeamOfTheRoundChooseTeamGroupBox()));*/
}

void Tippeligaen::deletePlayer(){

    QModelIndex index = playerTableView->currentIndex();
    if(!index.isValid()){
        QMessageBox* m = new QMessageBox();
        m->setText(tr("Merk en spiller for å slette"));
        m->show();
        return;
    }
    QSqlRecord record = playerModel->record(index.row());
    int spillerId = record.value(Spiller_Id).toInt();
    int messageBox = QMessageBox::warning(this, tr("Slett Spiller"),
                                 tr("Sikker på du vil slette spiller %1 %2?").arg(record.value(Spiller_Fornavn).toString(), record.value(Spiller_Etternavn).toString()),
                                 QMessageBox::Yes | QMessageBox::No);

    /*messageBox.setButtonText(QMessageBox::Yes, "Ja");
    messageBox.setButtonText(QMessageBox::No, "Nei");*/

    if(messageBox == QMessageBox::No){
        return;
    }
    QSqlQuery deletePlayer ("DELETE FROM spiller WHERE id = " + spillerId);
    deletePlayer.exec();

    playerModel->removeRow(index.row());
    playerModel->submitAll();
}

void Tippeligaen::actionCreatePlayer_triggered(){
    makePlayerGroupBox->show();
    playerInfoGroupBox->hide();
    crateNewTeamOfTheRoundGroupBox->hide();
}

void Tippeligaen::actionCreateNewTeamOfTheRound_triggered(){
    playerInfoGroupBox->hide();
    makePlayerGroupBox->hide();
    crateNewTeamOfTheRoundGroupBox->show();
}

void Tippeligaen::actionExitApplication_triggered(){
    exit(0);
}

void Tippeligaen::actionShowTeamOfTheRound_triggered(){
    if(!actionShowTeamOfTheRound->isChecked()) {
        actionShowTeamOfTheRound->setChecked(true);
    }

    teamOfTheRound->show();
    teamWiki->hide();
    teamOfTheRoundChooseTeamGroupBox->hide();
    createTeamOfTheRoundShowTeamGroupBox->hide();
    actionShowTeamInfo->setChecked(false);
    actionShowPreviousTeamOfTheRound->setChecked(false);
}

void Tippeligaen::actionShowTeamInfo_triggered(){
    if(!actionShowTeamInfo->isChecked()) {
        actionShowTeamInfo->setChecked(true);
    }

    teamWiki->show();
    teamOfTheRound->hide();
    teamOfTheRoundChooseTeamGroupBox->hide();
    createTeamOfTheRoundShowTeamGroupBox->hide();
    actionShowTeamOfTheRound->setChecked(false);
    actionShowPreviousTeamOfTheRound->setChecked(false);
}

void Tippeligaen::actionShowPreviousTeamOfTheRound_triggered(){
    if(!actionShowPreviousTeamOfTheRound->isChecked()) {
        actionShowPreviousTeamOfTheRound->setChecked(true);
    }
    teamOfTheRound->hide();
    teamWiki->hide();
    playerInfoGroupBox->hide();
    crateNewTeamOfTheRoundGroupBox->hide();

    //teamOfTheRoundId = 1;
    //QString teamOfTheRoundName = "Lag " + QString::number(teamOfTheRoundId);
    //teamOfTheRoundIdLabel()->setText(teamOfTheRoundName);
    teamOfTheRoundChooseTeamGroupBox->show();
    createTeamOfTheRoundShowTeamGroupBox->show();

    actionShowTeamOfTheRound->setChecked(false);
    actionShowTeamInfo->setChecked(false);
}

void Tippeligaen::actionAddNewPlayerToDataBase(){
    if( playerFirstNameEdit->text() == "" ||
        playerLastNameEdit->text()== "" ||
        shirtNumberEdit->text() == "" ){

        QMessageBox* m = new QMessageBox();
        m->setText(QString(tr("Fyll ut alle felter")));
        m->setWindowTitle("Feil");
        m->setWindowFlags(Qt::Drawer);
        m->show();
        return;
    }

    QSqlQuery insertPlayer;
    insertPlayer.prepare("INSERT INTO spiller (fornavn, etternavn, draktnummer, posisjon, posisjonsId, lagID)"
                         "VALUES (:fornavn, :etternavn, :draktnummer, :posisjon, :posisjonsId, :lagID)");
    insertPlayer.bindValue(":fornavn", playerFirstNameEdit->text());
    insertPlayer.bindValue(":etternavn", playerLastNameEdit->text());
    insertPlayer.bindValue(":draktnummer", shirtNumberEdit->text());
    insertPlayer.bindValue(":posisjon", playerPositionEdit->currentText());
    insertPlayer.bindValue(":posisjonsId", playerPositionEdit->currentIndex());
    insertPlayer.bindValue(":lagID", teamComboBox->currentIndex());
    insertPlayer.exec();

    int lagID = teamComboBox->currentIndex();

    QMessageBox* m = new QMessageBox();
    m->setText(QString(tr("Spiller %1 %2 ble opprettet.")).arg(playerFirstNameEdit->text(), playerLastNameEdit->text()));
    m->show();
    playerFirstNameEdit->setText("");
    playerLastNameEdit->setText("");
    shirtNumberEdit->setText("");
    updatePlayerTableView(lagID);
}

void Tippeligaen::insertPlayerToTeamOfTheRound(){
    actionShowTeamOfTheRound_triggered();

    QSqlQuery insertTeamOfTheRound;
    insertTeamOfTheRound.prepare("INSERT INTO rundenslag (rundensLagNavn, navn, posisjon, lagNavn)"
                         "VALUES (:rundensLagNavn, :navn, :posisjon, :lagNavn)");
    insertTeamOfTheRound.bindValue(":rundensLagNavn", teamOfTheRoundIdLabel()->text());
    insertTeamOfTheRound.bindValue(":navn", playerName()->text());
    insertTeamOfTheRound.bindValue(":posisjon", playerPosition()->text());
    insertTeamOfTheRound.bindValue(":lagNavn", playerTeam()->text());
    insertTeamOfTheRound.exec();
}

void Tippeligaen::addPlayerToTeamOfTheRound(){
    QString teamString = teamComboBox->currentText();
    QString picUrl = ":/bilder/" +teamString +".png";
    QSqlQuery deleteOldPlayer;
    switch(positionId){
    case 0:
        deleteOldPlayer.exec("delete from rundenslag where rundensLagNavn = '" +teamOfTheRoundIdLabel()->text()+"' and posisjon = 'Keeper'");
        insertPlayerToTeamOfTheRound();
        keeper()->setPixmap(QPixmap(picUrl));
        break;
    case 1:
        deleteOldPlayer.exec("delete from rundenslag where rundensLagNavn = '" +teamOfTheRoundIdLabel()->text()+"' and posisjon = 'Høyre back'");
        insertPlayerToTeamOfTheRound();
        rightBack()->setPixmap(QPixmap(picUrl));
        break;
    case 2:
        deleteOldPlayer.exec("delete from rundenslag where rundensLagNavn = '" +teamOfTheRoundIdLabel()->text()+"' and posisjon = 'Venstre back'");
        insertPlayerToTeamOfTheRound();
        leftBack()->setPixmap(QPixmap(picUrl));
        break;
    case 3:
        deleteOldPlayer.exec("delete from rundenslag where rundensLagNavn = '" +teamOfTheRoundIdLabel()->text()+"' and posisjon = 'Venstre midtstopper'");
        insertPlayerToTeamOfTheRound();
        leftCenterBack()->setPixmap(QPixmap(picUrl));
        break;
    case 4:
        deleteOldPlayer.exec("delete from rundenslag where rundensLagNavn = '" +teamOfTheRoundIdLabel()->text()+"' and posisjon = 'Høyre midtstopper'");
        insertPlayerToTeamOfTheRound();
        rightCenterBack()->setPixmap(QPixmap(picUrl));
        break;
    case 5:
        deleteOldPlayer.exec("delete from rundenslag where rundensLagNavn = '" +teamOfTheRoundIdLabel()->text()+"' and posisjon = 'Høyre ving'");
        insertPlayerToTeamOfTheRound();
        rightWing()->setPixmap(QPixmap(picUrl));
        break;
    case 6:
        deleteOldPlayer.exec("delete from rundenslag where rundensLagNavn = '" +teamOfTheRoundIdLabel()->text()+"' and posisjon = 'Venstre ving'");
        insertPlayerToTeamOfTheRound();
        leftWing()->setPixmap(QPixmap(picUrl));
        break;
    case 7:
        deleteOldPlayer.exec("delete from rundenslag where rundensLagNavn = '" +teamOfTheRoundIdLabel()->text()+"' and posisjon = 'Venstre midtbane'");
        insertPlayerToTeamOfTheRound();
        leftCenterMidfielder()->setPixmap(QPixmap(picUrl));
        break;
    case 8:
        deleteOldPlayer.exec("delete from rundenslag where rundensLagNavn = '" +teamOfTheRoundIdLabel()->text()+"' and posisjon = 'Høyre midtbane'");
        insertPlayerToTeamOfTheRound();
        rightCenterMidfielder()->setPixmap(QPixmap(picUrl));
        break;
    case 9:
        deleteOldPlayer.exec("delete from rundenslag where rundensLagNavn = '" +teamOfTheRoundIdLabel()->text()+"' and posisjon = 'Venstre spiss'");
        insertPlayerToTeamOfTheRound();
        leftStriker()->setPixmap(QPixmap(picUrl));
        break;
    case 10:
        deleteOldPlayer.exec("delete from rundenslag where rundensLagNavn = '" +teamOfTheRoundIdLabel()->text()+"' and posisjon = 'Høyre spiss'");
        insertPlayerToTeamOfTheRound();
        rightStriker()->setPixmap(QPixmap(picUrl));
        break;
    }
}

void Tippeligaen::createTeamOfTheRoundChooseTeamGroupBox(){
    teamOfTheRoundChooseTeamGroupBox = new QGroupBox(tr("Rundens lag"));
    teamOfTheRoundChooseTeamComboBox = new QComboBox;
    QSqlQuery teamOfTheRound ("select * from rundenslag group by rundensLagNavn" );
    while (teamOfTheRound.next()) {
        teamOfTheRoundChooseTeamComboBox->addItem(teamOfTheRound.value(1).toString());
    }

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(teamOfTheRoundChooseTeamComboBox, 0, 0);
    teamOfTheRoundChooseTeamGroupBox->setLayout(layout);
}

void Tippeligaen::updateTeamOfTheRoundChooseTeamGroupBox(){
    teamOfTheRoundChooseTeamComboBox->clear();
    QSqlQuery teamOfTheRound ("select * from rundenslag group by rundensLagNavn" );
    while (teamOfTheRound.next()) {
        teamOfTheRoundChooseTeamComboBox->addItem(teamOfTheRound.value(1).toString());
    }
}

void Tippeligaen::createTeamOfTheRoundShowTeam(){
    createTeamOfTheRoundShowTeamGroupBox = new QGroupBox(tr("Rundens lag"));

    textbrowser = new QTextBrowser;
    updateTeamOfTheRoundTable();
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(textbrowser, 0,0);
    createTeamOfTheRoundShowTeamGroupBox->setLayout(layout);
}

void Tippeligaen::updateTeamOfTheRoundTable(){
    QString htmlTable("");
    htmlTable.append("<table width=400>");
    htmlTable.append("<tr style='font-weight: bold;'><td style='padding-bottom: 15px;'>Spillernavn</td>");
    htmlTable.append("<td>Posisjon</td><td>Navn på lag</td></tr>");
    QSqlQuery teamOfTheRound ("select * from rundenslag where rundensLagNavn = '" +teamOfTheRoundChooseTeamComboBox->currentText() + "'");
    QSqlQuery test ("select rundensLagNavn, count(*) as antallLag from rundenslag group by rundensLagNavn ");
    while (teamOfTheRound.next()) {
        htmlTable.append("<tr><td style='padding-bottom: 15px;'>");
        htmlTable.append(teamOfTheRound.value(2).toString());
        htmlTable.append("</td><td>");
        htmlTable.append(teamOfTheRound.value(3).toString());
        htmlTable.append("</td><td>");
        htmlTable.append(teamOfTheRound.value(4).toString());
        htmlTable.append("</td>");
        htmlTable.append("</tr>");
    }

    htmlTable.append("</table>");
    textbrowser->setHtml(htmlTable);
}

