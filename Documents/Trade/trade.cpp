#include "trade.h"

void Trade::makeGui()
{
    QVBoxLayout * mainLayout=new QVBoxLayout(this);
    this->setLayout(mainLayout);
    _idRec=new QLabel(code,this);
    _dateRec=new QLabel(dateCreate,this);
    _statusRec=new QComboBox(this);
    _statusRec->insertItem(0,"Учитывать в отчете по поиску");
    _statusRec->insertItem(0,"Не учитывать в отчете");
    _ordersPresentation=new QLabel(this);
    _ordersRec=new QLineEdit(this);
    _dealerRec=new QLineEdit(this);
    dealerName=new QLabel(this);
    _commentRec=new QTextEdit(this);
    color_optionRec=new QLineEdit(this);
    giveAwayCarRec=new LabelChoose(this,this);
    giveAwayCarRec->setObjectName("giveAwayCarRec");
    giveAwayVinRec=new QLineEdit(this);
    giveAwayDateRec=new QDateEdit(QDate::currentDate(),this);
    giveAwayDateRec->setCalendarPopup(true);
    giveAwayDateRec->setDisplayFormat("yyyy-MM-dd");
    getCarRec=new LabelChoose(this,this);
    getCarRec->setObjectName("getCarRec");
    getVinRec=new QLineEdit(this);
    getDateRec=new QDateEdit(QDate::currentDate(),this);
    getDateRec->setCalendarPopup(true);
    getDateRec->setDisplayFormat("yyyy-MM-dd");

    QHBoxLayout *r1=new QHBoxLayout(this);
    QLabel * idLabel=new QLabel("id:",this);
    r1->addWidget(idLabel);
    r1->addWidget(_idRec);
    QLabel * dateLabel=new QLabel("Date:",this);
    r1->addWidget(dateLabel);
    r1->addWidget(_dateRec);
    r1->addWidget(_statusRec);
    QHBoxLayout *r2=new QHBoxLayout(this);
    QLabel * orderLabel=new QLabel("Order:",this);
    r2->addWidget(orderLabel);
    r2->addWidget(_ordersRec);
    r2->addWidget(_ordersPresentation);

    QLabel * dealerLabel=new QLabel("Dealer:",this);
    r2->addWidget(dealerLabel);
    r2->addWidget(_dealerRec);
    r2->addWidget(dealerName);
    mainLayout->addLayout(r1);
    mainLayout->addLayout(r2);
    QHBoxLayout *r3=new QHBoxLayout(this);
    QLabel * color_optionLabel=new QLabel("Color-option:",this);
    color_optionLabel->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
    r3->addWidget(color_optionLabel);
    r3->addWidget(color_optionRec);
    mainLayout->addLayout(r3);

    QHBoxLayout *r4=new QHBoxLayout(this);
    QLabel * giveAwayCarRecLabel=new QLabel("giveAwayCar:",this);
    giveAwayCarRecLabel->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
    r4->addWidget(giveAwayCarRecLabel);
    r4->addWidget(giveAwayCarRec);
    mainLayout->addLayout(r4);

    QHBoxLayout *r5=new QHBoxLayout(this);
    QLabel * giveAwayVinRecLabel=new QLabel("giveAwayVin:",this);
    giveAwayVinRecLabel->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
    r5->addWidget(giveAwayVinRecLabel);
    r5->addWidget(giveAwayVinRec);
    mainLayout->addLayout(r5);

    QHBoxLayout *r6=new QHBoxLayout(this);
    QLabel * giveAwayDateRecLabel=new QLabel("giveAwayDate:",this);
    giveAwayDateRecLabel->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
    r6->addWidget(giveAwayDateRecLabel);
    r6->addWidget(giveAwayDateRec);
    mainLayout->addLayout(r6);


    QHBoxLayout *r7=new QHBoxLayout(this);
    QLabel * getCarRecLabel=new QLabel("getCar:",this);
    getCarRecLabel->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
    r7->addWidget(getCarRecLabel);
    r7->addWidget(getCarRec);
    mainLayout->addLayout(r7);

    QHBoxLayout *r8=new QHBoxLayout(this);
    QLabel * getVinRecLabel=new QLabel("getVin:",this);
    getVinRecLabel->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
    r8->addWidget(getVinRecLabel);
    r8->addWidget(getVinRec);
    mainLayout->addLayout(r8);

    QHBoxLayout *r9=new QHBoxLayout(this);
    QLabel * getDateRecLabel=new QLabel("getDate:",this);
    getDateRecLabel->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
    r9->addWidget(getDateRecLabel);
    r9->addWidget(getDateRec);
    mainLayout->addLayout(r9);


    QHBoxLayout *r10=new QHBoxLayout(this);
    QLabel * _commentRecLabel=new QLabel("comment:",this);
    _commentRecLabel->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
    r10->addWidget(_commentRecLabel);
    r10->addWidget(_commentRec);
    mainLayout->addLayout(r10);

    connect(_dealerRec, SIGNAL(editingFinished()), this, SLOT(sig_selectDealers()));
    QMenuBar * mainMenu=new QMenuBar(this);
    mainLayout->setMenuBar(mainMenu);
    mainMenu->addAction("Update",this,SLOT(UPDATE_trade()));

    connect(_ordersRec, SIGNAL(editingFinished()), this, SLOT(sig_selectOrders()));
    mainMenu->addAction("Refresh all",this,SLOT(SELECT_trade()));
}

void Trade::itsNew()
{
    this->setObjectName("New trade");
    QSqlQuery query(Settings::S()->_db);
    if(!query.exec("INSERT INTO trade(_date) VALUES (datetime('now','localtime'));")){
        QMessageBox msgBox;
        msgBox.setText("Не получается создать нового order\n\n"+Settings::S()->_db.lastError().text()+" |\n "+query.lastError().text()+" |\n "+query.lastQuery());
        msgBox.exec();
        return;
    }
    Settings::S()->_db.commit();
    query.finish();
    if(!query.exec("SELECT _id,_date FROM trade WHERE rowid=last_insert_rowid();")){
        QMessageBox msgBox;
        msgBox.setText("При создании нового order что-то пошло не так с идом\n\n"+Settings::S()->_db.lastError().text()+" |\n "+query.lastError().text()+" |\n "+query.lastQuery());
        msgBox.exec();
        return;
    }
    query.next();
    code=query.value("_id").toString();
    dateCreate=query.value("_date").toString();
}

Trade::~Trade()
{
    if(DELETEIfNotCreate){
        QSqlQuery query(Settings::S()->_db);
        query.prepare("DELETE FROM  trade WHERE _id =:id;");
        query.bindValue(":id",code);
        if(!query.exec()){
            QMessageBox msgBox;
            msgBox.setText("Удалить новый не сохраненный\n\n"+Settings::S()->_db.lastError().text()+" |\n "+query.lastError().text()+" |\n "+query.lastQuery());
            msgBox.exec();
            return;
        }
        Settings::S()->_db.commit();
    }
}

Trade::Trade(QWidget *parent, QString code) : QWidget(parent),code(code)
{
    DELETEIfNotCreate=false;
    if(""==code){
        DELETEIfNotCreate=true;
        itsNew();
    }
    makeGui();
    if(!DELETEIfNotCreate){
        this->setObjectName("Trade:"+code);
        SELECT_trade();
    }
}

void Trade::setChooseCar(QString chooseIndex, QString chooseName, QString labelName)
{
    if("getCarRec"==labelName){
        getCarIndexChoose=chooseIndex;
        getCarNameChoose=chooseName;
        getCarRec->setText(getCarNameChoose);
    }else if("giveAwayCarRec"==labelName){
        GiveAwayCarNameChoose=chooseName;
        GiveAwayCarIndexChoose=chooseIndex;
        giveAwayCarRec->setText(GiveAwayCarNameChoose);
    }
}

void Trade::sig_selectDealers()
{
    QSqlQuery query(Settings::S()->_db);
    query.prepare("SELECT _name FROM dealers WHERE _code=:code;");
    query.bindValue(":code",_dealerRec->text());
    if(!query.exec()){
        return;
    }
    query.next();
    dealerName->setText(query.value("_name").toString());
}

void Trade::sig_selectOrders()
{
    QSqlQuery query(Settings::S()->_db);
    query.prepare("SELECT _presentation FROM orders WHERE _id=:code;");
    query.bindValue(":code",_ordersRec->text());
    if(!query.exec()){
        return;
    }
    query.next();
    _ordersPresentation->setText(query.value("_presentation").toString());
}

void Trade::UPDATE_trade()
{
    QSqlQuery query(Settings::S()->_db);
    query.prepare("UPDATE trade SET "
                  " _status=:_status,"
                  " _orders=:_orders,"
                  " _dealer=:_dealer, "
                  " _comment=:_comment, "
                  " _color_option_trade=:_color_option_trade,"
                  " _giveAwayCar=:_giveAwayCar,"
                  " _giveAwayVin=:_giveAwayVin,"
                  " _giveAwayDate=:_giveAwayDate,"
                  " _getCar=:_getCar,"
                  " _getVin=:_getVin,"
                  " _getDate=:_getDate "
                  " WHERE _id=:code;");
    query.bindValue(":code",code);
    query.bindValue(":_status",_statusRec->currentText());
    if(_ordersRec->text()!=""){
        query.bindValue(":_orders",_ordersRec->text());
    }else{
        query.bindValue(":_orders",QVariant());
    }

    if(_dealerRec->text()!=""){
        query.bindValue(":_dealer",_dealerRec->text());
    }else{
        query.bindValue(":_dealer",QVariant());
    }

    if(getCarIndexChoose!=""){
        query.bindValue(":_getCar",getCarIndexChoose);
    }else{
        query.bindValue(":_getCar",QVariant());
    }
    if(GiveAwayCarIndexChoose!=""){
        query.bindValue(":_giveAwayCar",GiveAwayCarIndexChoose);
    }else{
        query.bindValue(":_getCar",QVariant());
    }

    query.bindValue(":_comment",_commentRec->toPlainText());
    query.bindValue(":_color_option_trade",color_optionRec->text());
    query.bindValue(":_giveAwayVin",giveAwayVinRec->text());
    query.bindValue(":_giveAwayDate",giveAwayDateRec->text());
    query.bindValue(":_getVin",getVinRec->text());
    query.bindValue(":_getDate",getDateRec->text());
    if(!query.exec()){
        QMessageBox msgBox;
        msgBox.setText("Не получается сохранить trade\n\n"+Settings::S()->_db.lastError().text()+" |\n "+query.lastError().text()+" |\n "+query.lastQuery());
        msgBox.exec();
        return;
    }
    Settings::S()->_db.commit();
    DELETEIfNotCreate=false;
    SELECT_trade();
}

void Trade::SELECT_trade()
{
    QSqlQuery query(Settings::S()->_db);
    query.prepare("SELECT "
                  " trade._id as _id, "
                  " trade._date as _date, "
                  " trade._status as _status, "
                  " trade._orders as _orders, "
                  " trade._dealer as _dealer, "
                  " trade._comment as _comment, "
                  " trade._color_option_trade as _color_option_trade, "
                  " trade._giveAwayCar as _giveAwayCarID, "
                  " trade._giveAwayVin as _giveAwayVin, "
                  " trade._giveAwayDate as _giveAwayDate, "
                  " trade._getCar as _getCarID, "
                  " trade._getVin as _getVin, "
                  " trade._getDate as _getDate, "
                  " (SELECT cars._name FROM cars WHERE cars._id=_giveAwayCar) as _giveAwayCar_name, "
                  " (SELECT cars._name FROM cars WHERE cars._id=_getCar) as _getCar_name, "
                  " (SELECT orders._presentation FROM orders WHERE orders._id=_orders) as presentation_orders "
                  " FROM trade "
                  " WHERE trade._id=:code;");
    query.bindValue(":code",code);
    if(!query.exec()){
        QMessageBox msgBox;
        msgBox.setText("Не получается SELECT_trade\n\n"+Settings::S()->_db.lastError().text()+" |\n "+query.lastError().text()+" |\n "+query.lastQuery());
        msgBox.exec();
        return;
    }
    query.next();

    code=query.value("_id").toString();
    _dateRec->setText(query.value("_date").toString());
    _statusRec->setCurrentText(query.value("_status").toString());
    _ordersRec->setText(query.value("_orders").toString());
    _dealerRec->setText(query.value("_dealer").toString());
    getCarIndexChoose=query.value("_getCarID").toString();
    GiveAwayCarIndexChoose=query.value("_giveAwayCarID").toString();
    _commentRec->setPlainText(query.value("_comment").toString());
    color_optionRec->setText(query.value("_color_option_trade").toString());
    giveAwayVinRec->setText(query.value("_giveAwayVin").toString());
    giveAwayDateRec->setDate(query.value("_giveAwayDate").toDate());
    getVinRec->setText(query.value("_getVin").toString());
    getDateRec->setDate(query.value("_getDate").toDate());
    getCarRec->setText(query.value("_getCar_name").toString());
    giveAwayCarRec->setText(query.value("_giveAwayCar_name").toString());
    _ordersPresentation->setText(query.value("presentation_orders").toString());
    sig_selectDealers();
}
