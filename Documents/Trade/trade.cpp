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
    _dateRec=new QLabel(this);
    _statusRec=new QComboBox(this);
    _statusRec->insertItem(0,"Учитывать в отчете по поиску");
    _statusRec->insertItem(0,"Не учитывать в отчете");
    _ordersRec=new QLineEdit(this);
    _dealerRec=new ChooseDealer(this);
    QLabel *dealerPress=new QLabel(this);
    _commentRec=new QTextEdit(this);
    color_optionRec=new QLineEdit(this);
    giveAwayCarRec=new LabelChoose(this,this);
    giveAwayVinRec=new QLineEdit(this);
    giveAwayDateRec=new QDateEdit(QDate::currentDate(),this);
    giveAwayDateRec->setCalendarPopup(true);
    giveAwayDateRec->setDisplayFormat("yyyy-MM-dd");
    getCarRec=new LabelChoose(this,this);
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
    r1->addWidget(_statusRec);
    QHBoxLayout *r2=new QHBoxLayout(this);
    QLabel * orderLabel=new QLabel("Order:",this);
    r2->addWidget(orderLabel);
    r2->addWidget(_ordersRec);
    QLabel * dealerLabel=new QLabel("Dealer:",this);
    r2->addWidget(dealerLabel);
    r2->addWidget(_dealerRec);
    r2->addWidget(dealerPress);
    mainLayout->addLayout(r1);
    mainLayout->addLayout(r2);
    mainLayout->addWidget(color_optionRec);
    mainLayout->addWidget(giveAwayCarRec);
    mainLayout->addWidget(giveAwayVinRec);
    mainLayout->addWidget(giveAwayDateRec);
    mainLayout->addWidget(getCarRec);
    mainLayout->addWidget(getVinRec);
    mainLayout->addWidget(getDateRec);
    mainLayout->addWidget(_commentRec);
}

Trade::Trade(QWidget *parent, QString code) : QWidget(parent),code(code)
{
    makeGui();
}

void ChooseDealer::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<this->text()<<this->objectName();
}
