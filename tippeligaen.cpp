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
    ui->setupUi(this);

    QGroupBox *team = createTeamChooserGroupBox();
    teamOfTheRound = createTeamOfTheRoundGroupBox();
    createTeamPlayersGroupBox();
    createTeamInfoGroupBox();
    createTeamOfTheRoundChooseTeamGroupBox();
    createTeamWikiView();
    createTeamOfTheRoundShowTeam();


    makeWindowMenues();
    createMakeNewPlayerView();

    doAtStartUp();

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(team, 0, 0);
    layout->addWidget(players, 1, 0);
    layout->addWidget(teamInfo, 2 ,0);
    layout->addWidget(makePlayerGroupBox, 2, 0);
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
    connectMainMenuSlots();
}

Tippeligaen::~Tippeligaen(){
    delete ui;
}

void Tippeligaen::createLayout(){


}

void Tippeligaen::doAtStartUp(){
    teamWiki->hide();
    makePlayerGroupBox->hide();
    teamOfTheRoundChooseTeamGroupBox->hide();
    createTeamOfTheRoundShowTeamGroupBox->hide();

    updatePlayerTableView(0);
    updateTeamWiki(0);
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
    playerModel->setHeaderData(Spiller_Id, Qt::Horizontal, tr("id"));
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
    //playerTableView->setColumnHidden(Spiller_LagID, true);
    //playerTableView->setColumnHidden(Spiller_Id, true);
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
    field = new Field();

    QLabel *fieldImage = new QLabel();
    fieldImage->setPixmap(QPixmap(":/bilder/field.png"));
    box->setStyleSheet("QGroupBox { "
                            "background-image: url(:/bilder/field.png);"
                            "background-repeat: none;"
                            "border: 20px solid;"
                            "border-color: none; "
                        "}");

    //fieldLabel = new QLabel(field);
    //fieldLabel->setPixmap(QPixmap(":/bilder/fullbaneTest.png"));
    //fieldLabel->setAlignment(Qt::AlignTop);
    //field->addLabel(fieldLabel);
    //fieldLabel->show();
    //field->show();

    keeper = new QLabel;
    rightBack = new QLabel;
    rightCenterBack = new QLabel;
    leftCenterBack = new QLabel;
    leftBack = new QLabel;
    leftWing = new QLabel;
    rightWing = new QLabel;
    rightCenterMidfielder = new QLabel;
    leftCenterMidfielder = new QLabel;
    leftStriker = new QLabel;
    rightStriker = new QLabel;
    teamOfTheRoundIdLabel= new QLabel;
    teamOfTheRoundIdLabel->setText("Jasså du!");

    makeUnknownShirt();


    QGridLayout *layout = new QGridLayout;
    //QBoxLayout *layout = new QBoxLayout;
    //layout->addWidget(field);//, 0,0);
    layout->addWidget(keeper, 0, 2, 1, 4);
    layout->addWidget(rightBack, 1, 0);
    layout->addWidget(rightCenterBack, 1, 1);
    layout->addWidget(leftCenterBack, 1, 3);
    layout->addWidget(leftBack, 1, 4);
    layout->addWidget(rightWing, 2, 0);
    layout->addWidget(rightCenterMidfielder, 2, 1);
    layout->addWidget(leftCenterMidfielder, 2, 3);
    layout->addWidget(leftWing, 2, 4);
    layout->addWidget(rightStriker, 3, 1);
    layout->addWidget(leftStriker, 3, 3);
    layout->addWidget(teamOfTheRoundIdLabel, 4, 0);
    box->setLayout(layout);
    return box;
}

void Tippeligaen::makeUnknownShirt(){
    QPixmap unknownShirt(":/bilder/Unknown.png");
    keeper->setPixmap(unknownShirt);
    rightBack->setPixmap(unknownShirt);
    rightCenterBack->setPixmap(unknownShirt);
    leftCenterBack->setPixmap(unknownShirt);
    leftBack->setPixmap(unknownShirt);
    rightWing->setPixmap(unknownShirt);
    rightCenterMidfielder->setPixmap(unknownShirt);
    leftCenterMidfielder->setPixmap(unknownShirt);
    leftWing->setPixmap(unknownShirt);
    rightStriker->setPixmap(unknownShirt);
    leftStriker->setPixmap(unknownShirt);
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
    playerPositionEdit->insertItem(3, tr("Venstre Midtstopper"));
    playerPositionEdit->insertItem(4, tr("Høyre Midtstopper"));
    playerPositionEdit->insertItem(5, tr("HøyreVing"));
    playerPositionEdit->insertItem(6, tr("VenstreVing"));
    playerPositionEdit->insertItem(7, tr("Venstre Midtbane"));
    playerPositionEdit->insertItem(8, tr("Høyre Midtbane"));
    playerPositionEdit->insertItem(9, tr("Venstre Spiss"));
    playerPositionEdit->insertItem(10, tr("Høyre Spiss"));

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
    shirtLabel->setPixmap(QPixmap(":/bilder/Aalesund.png"));

    shirt->addLabel(shirtLabel);
    playerNameLabel = new QLabel;
    playerNameLabel->setText(tr("Spillernavn: "));
    playerPositionLabel = new QLabel;
    playerPositionLabel->setText(tr("Posisjon: "));
    playerTeamLabel = new QLabel;
    playerTeamLabel->setText(tr("Lag: "));

    deletePlayerButton = new QPushButton;
    deletePlayerButton->setText(tr("Slett"));
    addToTeamOfTheRoundButton = new QPushButton;
    addToTeamOfTheRoundButton->setText(tr("Legg til i rundens lag"));

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
    layout->addWidget(deletePlayerButton, 3, 0);
    layout->addWidget(addToTeamOfTheRoundButton, 3, 1);
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


void Tippeligaen::updatePlayerInformation(){
    makePlayerGroupBox->hide();
    teamInfo->show();
    QModelIndex index = playerTableView->currentIndex();
    QSqlRecord record = playerModel->record(index.row());

    QString playerFirstNameString = record.value("fornavn").toString();
    QString playerLastNameString = record.value("etternavn").toString();
    QString playerPositionString = record.value("posisjon").toString();
    QString teamString = record.value("lagnavn").toString();

    positionId = record.value("posisjonsId").toInt();

    playerName->setText(tr("%1 %2").arg(playerFirstNameString).arg(playerLastNameString));
    playerTeam->setText(tr("%1").arg(teamString));
    playerPosition->setText(tr("%1").arg(playerPositionString));

    QString picUrl = ":/bilder/" +teamString +".png";
    shirtLabel->setPixmap(QPixmap(picUrl));
    shirt->addLabel(shirtLabel);
}

void Tippeligaen::makeWindowMenues(){
//-FIL
    fileMenu = new QMenu(this);
    fileMenu->setTitle(tr("Fil"));

    actionCreatePlayer = new QAction(tr("Legg til spiller"), fileMenu);
    actionExitApplication = new QAction(tr("Avslutt"), fileMenu);
    actionCreateTeamOfTheRound = new QAction(tr("Lag nytt rundenslag"), fileMenu);

    fileMenu->addAction(actionCreatePlayer);
    fileMenu->addAction(actionCreateTeamOfTheRound);
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

    showMenu->addAction(actionShowTeamOfTheRound);
    showMenu->addAction(actionShowTeamInfo);
    showMenu->addSeparator();

    ui->menuBar->addMenu(fileMenu);
    ui->menuBar->addMenu(showMenu);
    /*connect(cascadeAction, SIGNAL(triggered()), this, SLOT(cascadeSubWindows()));
    tileAction = new QAction(tr("Tile"), fileMenu);*/
}

void Tippeligaen::connectMainMenuSlots() {
    connect(actionCreatePlayer, SIGNAL(triggered()),
        this, SLOT(actionCreatePlayer_triggered()));
    connect(actionExitApplication, SIGNAL(triggered()),
        this, SLOT(actionExitApplication_triggered()));
    connect(actionShowTeamOfTheRound, SIGNAL(triggered()),
        this, SLOT(actionShowTeamOfTheRound_triggered()));
    connect(actionShowTeamInfo, SIGNAL(triggered()),
        this, SLOT(actionShowTeamInfo_triggered()));
    connect(actionCreateTeamOfTheRound, SIGNAL(triggered()),
            this, SLOT(actionAddNewTeamOfTheRound_triggered()));
    /*connect(actionCreateTeamOfTheRound, SIGNAL(triggered()),
            this, SLOT(updateTeamOfTheRoundChoosTeamGroupBox()));*/
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

void Tippeligaen::actionShowTeamOfTheRound_triggered(){
    if(!actionShowTeamOfTheRound->isChecked()) {
        actionShowTeamOfTheRound->setChecked(true);
    }

    teamOfTheRound->show();
    teamWiki->hide();
    teamOfTheRoundChooseTeamGroupBox->hide();
    actionShowTeamInfo->setChecked(false);
}

void Tippeligaen::actionShowTeamInfo_triggered(){
    if(!actionShowTeamInfo->isChecked()) {
        actionShowTeamInfo->setChecked(true);
    }

    teamWiki->show();
    teamOfTheRound->hide();
    teamOfTheRoundChooseTeamGroupBox->hide();
    actionShowTeamOfTheRound->setChecked(false);
}

void Tippeligaen::actionCreatePlayer_triggered(){
    makePlayerGroupBox->show();
    teamInfo->hide();
}

void Tippeligaen::actionExitApplication_triggered(){
    exit(0);
}

void Tippeligaen::actionAddNewTeamOfTheRound_triggered(){
    teamOfTheRound->hide();
    teamWiki->hide();

    teamOfTheRoundId = 1;
    QString teamOfTheRoundName = "Lag"+QString::number(teamOfTheRoundId);
    teamOfTheRoundIdLabel->setText(teamOfTheRoundName);    
    insertPlayerToTeamOfTheRound();
    connect(actionCreateTeamOfTheRound, SIGNAL(triggered()),
            this, SLOT(updateTeamOfTheRoundChoosTeamGroupBox()));
    teamOfTheRoundChooseTeamGroupBox->show();
    createTeamOfTheRoundShowTeamGroupBox->show();

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

    /*delete players;
    createTeamPlayersGroupBox();
    players->show();*/
}
void Tippeligaen::insertPlayerToTeamOfTheRound(){
    QSqlQuery teamOfTheRoundRow;
    teamOfTheRoundRow.prepare("INSERT INTO rundenslag (rundensLagNavn, navn, posisjon, lagNavn)"
                         "VALUES (:rundensLagNavn, :navn, :posisjon, :lagNavn");
    teamOfTheRoundRow.bindValue(":rundensLagNavn", teamOfTheRoundIdLabel->text());
    teamOfTheRoundRow.bindValue(":navn", playerNameLabel->text());
    teamOfTheRoundRow.bindValue(":posisjon", playerPosition->text());
    teamOfTheRoundRow.bindValue(":lagNavn", playerTeam->text());
    teamOfTheRoundRow.exec();
}

void Tippeligaen::addPlayerToTeamOfTheRound(){
    QString teamString = teamComboBox->currentText();
    QString picUrl = ":/bilder/" +teamString +".png";
    switch(positionId){
    case 0:
        insertPlayerToTeamOfTheRound();
        keeper->setPixmap(QPixmap(picUrl));
        break;
    case 1:
        insertPlayerToTeamOfTheRound();
        rightBack->setPixmap(QPixmap(picUrl));
        break;
    case 2:
        insertPlayerToTeamOfTheRound();
        leftBack->setPixmap(QPixmap(picUrl));
        break;
    case 3:
        insertPlayerToTeamOfTheRound();
        leftCenterBack->setPixmap(QPixmap(picUrl));
        break;
    case 4:
        insertPlayerToTeamOfTheRound();
        rightCenterBack->setPixmap(QPixmap(picUrl));
        break;
    case 5:
        insertPlayerToTeamOfTheRound();
        rightWing->setPixmap(QPixmap(picUrl));
        break;
    case 6:
        insertPlayerToTeamOfTheRound();
        leftWing->setPixmap(QPixmap(picUrl));
        break;
    case 7:
        insertPlayerToTeamOfTheRound();
        leftCenterMidfielder->setPixmap(QPixmap(picUrl));
        break;
    case 8:
        insertPlayerToTeamOfTheRound();
        rightCenterMidfielder->setPixmap(QPixmap(picUrl));
        break;
    case 9:
        insertPlayerToTeamOfTheRound();
        leftStriker->setPixmap(QPixmap(picUrl));
        break;
    case 10:
        insertPlayerToTeamOfTheRound();
        rightStriker->setPixmap(QPixmap(picUrl));
        break;
    }
}

void Tippeligaen::createTeamOfTheRoundChooseTeamGroupBox(){
    teamOfTheRoundChooseTeamGroupBox = new QGroupBox(tr("Tippeligalag"));;
    teamOfTheRoundChooseTeamComboBox = new QComboBox;
    /*teamOfTheRoundModel = new QSqlRelationalTableModel(this);
    teamOfTheRoundModel->setTable("rundenslag");
    teamOfTheRoundModel->setRelation(0, QSqlRelation("rundenslag", "id", "rundensLagNavn"));
    teamOfTheRoundModel->setSort(1, Qt::AscendingOrder);
    teamOfTheRoundModel->select();

    teamOfTheRoundChooseTeamComboBox->setModel(teamOfTheRoundModel);*/

    /*connect(teamComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updatePlayerTableView(int)));*/
    QSqlQuery teamOfTheRound ("select * from rundenslag group by rundensLagNavn" );
    while (teamOfTheRound.next()) {
        teamOfTheRoundChooseTeamComboBox->addItem(teamOfTheRound.value(1).toString());
    }

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(teamOfTheRoundChooseTeamComboBox, 0, 0);
    teamOfTheRoundChooseTeamGroupBox->setLayout(layout);
}

void Tippeligaen::updateTeamOfTheRoundChoosTeamGroupBox(){
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
    htmlTable.append("<table width=250 border=1>");
    htmlTable.append("<tr><td>rundensLagNavn</td><td>Spillernavn</td><td>posisjon</td><td>navn på lag</td></tr>");
    QSqlQuery teamOfTheRound ("select * from rundenslag where rundensLagNavn = '" +teamOfTheRoundChooseTeamComboBox->currentText() + "'");
    while (teamOfTheRound.next()) {
        htmlTable.append("<tr><td>");
        htmlTable.append(teamOfTheRound.value(1).toString());
        htmlTable.append("</td><td>");
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

