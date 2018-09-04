#include "trade.h"

void Trade::makeGui()
{
//    "CREATE TABLE IF NOT EXISTS trade( "
//        " _id integer PRIMARY KEY NOT NULL,"
//        " _date TEXT,"
//        " _status TEXT check( _folder='Учитывать в отчете по поиску' or _folder='Не учитывать в отчете') NOT NULL DEFAULT 'Учитывать в отчете по поиску'"
//        " _orders INTEGER REFERENCES orders(_id ) ON UPDATE CASCADE,"
//       " _dealer text REFERENCES dealers(_code) ON UPDATE CASCADE NOT NULL "
//       " _comment TEXT, "
//       " _color_option_trade TEXT,"
//       " giveAwayCar TEXT,"
//       " giveAwayVin TEXT,"
//       " giveAwayDate TEXT,"
//       " getCar TEXT,"
//       " getVin TEXT,"
//       " getDate TEXT);"
    QVBoxLayout * mainLayout=new QVBoxLayout(this);
    this->setLayout(mainLayout);
    _idRec=new QLabel(this);
    _dateRec=new QLabel(dateCreate,this);
    _statusRec=new QComboBox(this);
    _statusRec->insertItem(0,"Учитывать в отчете по поиску");
    _statusRec->insertItem(0,"Не учитывать в отчете");
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
