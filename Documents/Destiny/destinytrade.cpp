#include "destinytrade.h"

void DestinyTrade::makeGui()
{
    vinCar= new QLabel(this);
    orderPresentation=new QLabel(this);
    parentTrade=new QLabel(this);
    boughtClient=new QLineEdit(this);
    soldManager=new QComboBox(this);
    QSqlQueryModel *modelManagers = new QSqlQueryModel;
    modelManagers->setQuery("SELECT _code FROM managers WHERE _folder=0 and _mark=0 and _parent='OnlyManagers'",Settings::S()->_db);
    soldManager->setModel(modelManagers);
    soldManager->setModelColumn(0);

    dateSold=new QDateEdit(QDate::currentDate(),this);
    dateSold->setCalendarPopup(true);
    dateSold->setDisplayFormat("yyyy-MM-dd");
    comment=new QLineEdit(this);

    QVBoxLayout * mainLayout=new QVBoxLayout(this);
    this->setLayout(mainLayout);

    QHBoxLayout * tradeLayout=new QHBoxLayout(this);
    QLabel * tradeLabel=new QLabel("trade:",this);
    tradeLabel->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
    tradeLayout->addWidget(tradeLabel);
    tradeLayout->addWidget(parentTrade);
    mainLayout->addLayout(tradeLayout);

    QHBoxLayout * orderLayout=new QHBoxLayout(this);
    QLabel * orderLabel=new QLabel("For:",this);
    orderLabel->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
    orderLayout->addWidget(orderLabel);
    orderLayout->addWidget(orderPresentation);
    mainLayout->addLayout(orderLayout);

    QHBoxLayout * vinLayout=new QHBoxLayout(this);
    QLabel * vinLabel=new QLabel("Vin:",this);
    vinLabel->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
    vinLayout->addWidget(vinLabel);
    vinLayout->addWidget(vinCar);
    mainLayout->addLayout(vinLayout);

    QHBoxLayout * clientLayout=new QHBoxLayout(this);
    QLabel * clientLabel=new QLabel("Bought client:",this);
    clientLabel->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
    clientLayout->addWidget(clientLabel);
    clientLayout->addWidget(boughtClient);
    mainLayout->addLayout(clientLayout);

    QHBoxLayout * managerLayout=new QHBoxLayout(this);
    QLabel * managerLabel=new QLabel("Sell manager:",this);
    managerLabel->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
    managerLayout->addWidget(managerLabel);
    managerLayout->addWidget(soldManager);
    mainLayout->addLayout(managerLayout);

    QVBoxLayout * dateSoldLayout=new QVBoxLayout(this);
    QHBoxLayout * dateWidgetLayout=new QHBoxLayout(this);
    QLabel * sellDateLabel=new QLabel("Sell date:",this);
    sellDateLabel->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
    dateWidgetLayout->addWidget(sellDateLabel);
    dateWidgetLayout->addWidget(dateSold);
    QLabel * resetDateLabel=new QLabel("Reset Date=0000-01-01",this);
    dateSoldLayout->addLayout(dateWidgetLayout);
    dateSoldLayout->addWidget(resetDateLabel);
    mainLayout->addLayout(dateSoldLayout);


    QHBoxLayout * commentLayout=new QHBoxLayout(this);
    QLabel * commentLabel=new QLabel("Сomment:",this);
    commentLabel->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
    commentLayout->addWidget(commentLabel);
    commentLayout->addWidget(comment);
    mainLayout->addLayout(commentLayout);

    QMenuBar * mainMenu=new QMenuBar(this);
    mainLayout->setMenuBar(mainMenu);
    mainMenu->addAction("Update",this,SLOT(UPDATE_destiny()));
    mainMenu->addAction("Refresh all",this,SLOT(SELECT_destiny()));
}

DestinyTrade::DestinyTrade(QWidget *parent,QString code) : QWidget(parent),code(code)
{
    makeGui();
    SELECT_destiny();
}

void DestinyTrade::UPDATE_destiny()
{
    QSqlQuery query(Settings::S()->_db);
    query.prepare("UPDATE  destinyTrade SET "
    " _boughtCliend=:_boughtCliend, "
    " _dateSold=:_dateSold, "
    " _soldManager=:_soldManager, "
    " _comment=:_comment "
    " WHERE _parentTrade =:code");
    query.bindValue(":code",code);
    query.bindValue(":_boughtCliend",boughtClient->text());
    if("0000-01-01"==dateSold->text()){
        query.bindValue(":_dateSold",QVariant());
    }else{
        query.bindValue(":_dateSold",dateSold->text());
    }
    if("default"!=soldManager->currentText()){
        query.bindValue(":_soldManager",soldManager->currentText());
    }else{
        query.bindValue(":_soldManager",QVariant());
    }
    query.bindValue(":_comment",comment->text());
    if(!query.exec()){
        QMessageBox msgBox;
        msgBox.setText("Не получается UPDATE_destiny\n\n"+Settings::S()->_db.lastError().text()+" |\n "+query.lastError().text()+" |\n "+query.lastQuery());
        msgBox.exec();
    }
}

void DestinyTrade::SELECT_destiny()
{
    QSqlQuery query(Settings::S()->_db);
    query.prepare("SELECT "
    " destinyTrade._parentTrade as code, "
    " destinyTrade._boughtCliend as _boughtCliend, "
    " destinyTrade._soldManager as _soldManager, "
    " destinyTrade._dateSold as _dateSold, "
    " destinyTrade._comment as _comment, "
    " trade._getVin  as _getVin, "
    " orders._presentation as _presentation "
    " FROM destinyTrade "
    " LEFT JOIN trade ON "
    " destinyTrade._parentTrade=trade._id "
    " LEFT JOIN orders ON "
    " trade._orders=orders._id "
    " WHERE _parentTrade=:code;");
    query.bindValue(":code",code);
    if(!query.exec()){
        QMessageBox msgBox;
        msgBox.setText("Не получается SELECT_destiny\n\n"+Settings::S()->_db.lastError().text()+" |\n "+query.lastError().text()+" |\n "+query.lastQuery());
        msgBox.exec();
    }
    query.next();
    code=query.value("code").toString();
    parentTrade->setText(code);
    vinCar->setText(query.value("_getVin").toString());
    orderPresentation->setText(query.value("_presentation").toString());
    boughtClient->setText(query.value("_boughtCliend").toString());
    soldManager->setCurrentText(query.value("_soldManager").toString());
    dateSold->setDate(query.value("_dateSold").toDate());
    comment->setText(query.value("_comment").toString());
}
