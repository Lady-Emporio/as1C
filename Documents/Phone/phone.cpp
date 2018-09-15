#include "phone.h"




void Phone::makeGui()
{
    QVBoxLayout * mainLayout=new QVBoxLayout(this);
    this->setLayout(mainLayout);

    QLabel * idLabel=new QLabel("id",this);
    QLabel * orderLabel=new QLabel("Order",this);
    idRec=new QLineEdit(code,this);
    idRec->setReadOnly(true);
    orderRec=new QLineEdit(parentOrder,this);
    statucRec=new MyComboBox(this);
    dateRec=new QLabel(dateCreate,this);
    statucRec->insertItem(0,"Search!!!");
    statucRec->insertItem(1,"Cancel");
    statucRec->insertItem(2,"Found");
    statucRec->insertItem(3,"Wait");
    QHBoxLayout * r2Layout=new QHBoxLayout(this);
    QLabel *ordersLabel=new QLabel("orders",this);
    ordersLabel->setSizePolicy(QSizePolicy ::Maximum   , QSizePolicy ::Maximum);
    orders_presentation=new QLabel(this);
    r2Layout->addWidget(ordersLabel);
    r2Layout->addWidget(orders_presentation);

    callsTable=new Call(this,code,0,1,13);
    DelegateForCall *forAllColimn=new DelegateForCall();
    for(int i=0;i!=15;++i){
        callsTable->tableView->setItemDelegateForColumn(i,forAllColimn);
    }
    if(""!=parentOrder){
        orders_presentation->setText(getOrderPresentation(parentOrder));
    }

    QHBoxLayout * r1Layout=new QHBoxLayout(this);
    r1Layout->addWidget(dateRec);
    r1Layout->addWidget(idLabel);
    r1Layout->addWidget(idRec);
    r1Layout->addWidget(orderLabel);
    r1Layout->addWidget(orderRec);
    r1Layout->addWidget(statucRec);
    mainLayout->addLayout(r2Layout);
    mainLayout->addLayout(r1Layout);
    mainLayout->addWidget(callsTable);

    QMenuBar * mainBar=new QMenuBar(this);
    mainLayout->setMenuBar(mainBar);
    mainBar->addAction("Save",this,SLOT(UPDATE_phone()));
    mainBar->addAction("Refresh",this,SLOT(SELECT_phone()));
    mainBar->addAction("FromFile",this,SLOT(action_chooseFile()));

    QMenu * tableActions=new QMenu(mainBar);
    mainBar->addMenu(tableActions);
    mainBar->addAction("show/hide",this,SLOT(action_showHide()));
    connect(orderRec, SIGNAL(editingFinished()), this, SLOT(sig_selectOrders()));
}

void Phone::itsNew()
{
    QSqlQuery query(Settings::S()->_db);
    if(""!=parentOrder){
        query.prepare("INSERT INTO phone(_orders,_date,_f_status) VALUES "
                      " (:_orders,datetime('now','localtime'),:_f_status);");
        query.bindValue(":_f_status","Search!!!");
        query.bindValue(":_orders",parentOrder);
    }else{
        query.prepare("INSERT INTO phone(_f_status,_date) VALUES "
                      " (:_f_status,datetime('now','localtime'));");
        query.bindValue(":_f_status","Search!!!");
    }
    if(!query.exec()){
        QMessageBox msgBox;
        msgBox.setText("Не получается создать нового phone\n\n"+Settings::S()->_db.lastError().text()+" |\n "+query.lastError().text()+" |\n "+query.lastQuery());
        msgBox.exec();
        return;
    }
    Settings::S()->_db.commit();
    query.finish();
    if(!query.exec("SELECT _id,_date FROM phone WHERE rowid=last_insert_rowid();")){
        QMessageBox msgBox;
        msgBox.setText("При создании нового phone что-то пошло не так с идом\n\n"+Settings::S()->_db.lastError().text()+" |\n "+query.lastError().text()+" |\n "+query.lastQuery());
        msgBox.exec();
        return;
    }
    query.next();
    code=query.value("_id").toString();
    dateCreate=query.value("_date").toString();
}

Phone::~Phone()
{
    if(DELETEIfNotCreate){
        QSqlQuery query(Settings::S()->_db);
        query.prepare("DELETE FROM  phone WHERE _id =:id;");
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

QString Phone::getOrderPresentation(QString orderId)
{
    QSqlQuery query(Settings::S()->_db);
    query.prepare("SELECT _presentation FROM orders WHERE orders._id=:id;");
    query.bindValue(":id",orderId);
    if(!query.exec()){
        QMessageBox msgBox;
        msgBox.setText("При получении _presentation FROM orders что-то пошло не так\n\n"+Settings::S()->_db.lastError().text()+" |\n "+query.lastError().text()+" |\n "+query.lastQuery());
        msgBox.exec();
        return "";
    }
    query.next();
    return query.value("_presentation").toString();
}

Phone::Phone(QWidget *parent, QString code,QString parentOrder) : QWidget(parent),code(code),parentOrder(parentOrder)
{
    DELETEIfNotCreate=false;
    ""==code?this->setObjectName("New Phone"):
             this->setObjectName("Phone:"+code);
    if(""==code){
        DELETEIfNotCreate=true;
        itsNew();
    }
    makeGui();
    if(!DELETEIfNotCreate){
        SELECT_phone();
    }
}

void Phone::UPDATE_phone()
{
    QSqlQuery query(Settings::S()->_db);
    query.prepare("UPDATE phone SET "
                  " _id=:_id, "
                  " _orders=:_orders, "
                  " _f_status=:_f_status "
                  " WHERE _id=:oldId;");
    query.bindValue(":_id",idRec->text());
    if(""==orderRec->text()){
        query.bindValue(":_orders",QVariant());
    }else{
        query.bindValue(":_orders",orderRec->text());
    }
    query.bindValue(":_f_status",statucRec->currentText());
    query.bindValue(":oldId",code);
    if(!query.exec()){
        QMessageBox msgBox;
        msgBox.setText("Не получается сохранить phone\n\n"+Settings::S()->_db.lastError().text()+" |\n "+query.lastError().text()+" |\n "+query.lastQuery());
        msgBox.exec();
        return;
    }
    if(!callsTable->modelCall->submitAll()){
        QMessageBox msgBox;
        msgBox.setText("Не получается сохранить callsTable\n\n"+Settings::S()->_db.lastError().text()+" |\n "+callsTable->modelCall->lastError().text());
        msgBox.exec();
    };
    Settings::S()->_db.commit();
    DELETEIfNotCreate=false;
}

void Phone::SELECT_phone()
{
    QSqlQuery query(Settings::S()->_db);
    query.prepare("SELECT _id,_orders,_date,_f_status FROM phone WHERE _id=:_id;");
    query.bindValue(":_id",code);
    if(!query.exec()){
        QMessageBox msgBox;
        msgBox.setText("Не получается select phone\n\n"+Settings::S()->_db.lastError().text()+" |\n "+query.lastError().text()+" |\n "+query.lastQuery());
        msgBox.exec();
        return;
    }
    query.next();
    code=query.value("_id").toString();
    dateCreate=query.value("_date").toString();
    parentOrder=query.value("_orders").toString();

    idRec->setText(code);
    dateRec->setText(dateCreate);
    orderRec->setText(parentOrder);
    statucRec->setCurrentText(query.value("_f_status").toString());
    if(""!=parentOrder){
        orders_presentation->setText(getOrderPresentation(parentOrder));
    }
    if(!callsTable->modelCall->select()){
        QMessageBox msgBox;
        msgBox.setText("Не получается select call\n\n"+Settings::S()->_db.lastError().text()+" |\n "+query.lastError().text()+" |\n "+query.lastQuery());
        msgBox.exec();
    }
    callsTable->modelCall->setObjectName("Phone:|"+code+"|for order:|"+parentOrder+"|dateCreate:|"+dateCreate);
    int maxRow=callsTable->modelCall->rowCount();
    TableModelForCall * model=callsTable->modelCall;
    for(int i=0;i!=maxRow;++i){
        QString dealer=model->data( model->index(i,3),Qt::DisplayRole).toString();
        QStringList nameDateMailActive=getDealersFromFile(dealer);
        QString nameDealer=nameDateMailActive.at(0);
        if(0!=nameDateMailActive.at(2)){
            nameDealer="@"+nameDealer;
        }
        QString lastDate=nameDateMailActive.at(1);
        QString activePhone=nameDateMailActive.at(3);
        model->setData(model->index(i,4),activePhone);
        model->setData(model->index(i,8),lastDate);
        model->setData(model->index(i,7),nameDealer);
    }
}

void Phone::action_chooseFile()
{
    QString file_path = QFileDialog::getOpenFileName(this,"Choose db","./");
    if(!file_path.isEmpty()){
        QFile file(file_path);
        file.open(QIODevice::ReadOnly);
        QByteArray a = file.readAll();
        QString allText(a);
        QStringList listText=allText.split("\n");
        TableModelForCall * model=callsTable->modelCall;
        model->removeRows(0,model->rowCount());
        int i=-1;
        for(QString row:listText){
            if(row.isEmpty()){
                continue;
            }
            QStringList rowList=row.split("\t");
            if(rowList.length()!=7){
                QMessageBox msgBox;
                msgBox.setText("Странная строка, там нет 7 таб,прерываем:\n"+row);
                msgBox.exec();
                return;
            }
            ++i;
            QString vin=rowList.at(0);
            QString dealer=rowList.at(1);
            QString block=rowList.at(2);
            QString datecar=rowList.at(3);
            QString modelCar=rowList.at(4);
            QString option=rowList.at(5);
            QString color=rowList.at(6);

            QStringList nameDateMailActive=getDealersFromFile(dealer);
            QString nameDealer=nameDateMailActive.at(0);
            if(0!=nameDateMailActive.at(2)){
                nameDealer="@"+nameDealer;
            }
            QString lastDate=nameDateMailActive.at(1);
            QString activePhone=nameDateMailActive.at(3);

            model->insertRow(i);
            model->setData(model->index(i,1),code);
            model->setData(model->index(i,2),vin);
            model->setData(model->index(i,3),dealer);
            model->setData(model->index(i,4),activePhone);
            model->setData(model->index(i,5),block);
            model->setData(model->index(i,6),datecar);
            model->setData(model->index(i,7),nameDealer);
            model->setData(model->index(i,8),lastDate);
            model->setData(model->index(i,9),modelCar);
            model->setData(model->index(i,10),option);
            model->setData(model->index(i,11),color);

//            <<" CREATE TABLE IF NOT EXISTS calls( "
//              " _id INTEGER PRIMARY KEY NOT NULL, "
//              " _phone INTEGER REFERENCES phone(_id) ON UPDATE CASCADE NOT NULL, "
//              " _vinCar TEXT, "
//              " _code_dealer TEXT, "
//              " _activePhone TEXT, "
//              " _blockCar TEXT, "
//              " _dateCar TEXT, "
//              " _dealerNameAndOpen TEXT, "
//              " _dealerLastCall TEXT, "
//              " _modelCar TEXT, "
//              " _optionCar TEXT, "
//              " _colorCar TEXT, "
//              " _dateTalk TEXT, "
//              " _colorTalk TEXT CHECK(_colorTalk in ('','Красный','Зеленый','Синий','Коричневый','Желтый','Фиолетовый') ), "
//              " _commentTalk TEXT "

        }
    }
}

QStringList Phone::getDealersFromFile(QString dealer)
{
    QSqlQuery query(Settings::S()->_db);
    query.prepare("SELECT "
                  " dealers._name as _name, "
                  " dealers._activePhone as _activePhone, "
                  " (SELECT full_call._date FROM full_call WHERE _parent=dealers._code "
                  " ORDER BY datetime(_date) DESC LIMIT 1 ) as lastDate, "
                  " (SELECT ifnull(COUNT(DISTINCT email._mail),0) FROM email "
                  " WHERE email._parent=dealers._code  ORDER BY datetime(_date) DESC LIMIT 1 ) as isEmail "
                  " FROM dealers WHERE dealers._code=:code;");
    query.bindValue(":code",dealer);
    QStringList dataList;
    if(!query.exec()){
        QMessageBox msgBox;
        msgBox.setText("Не получается получить данные из дилера:"+dealer+"\n"+Settings::S()->_db.lastError().text()+" |\n "+query.lastError().text()+" |\n "+query.lastQuery());
        msgBox.exec();
        return dataList;
    }
    query.next();
    dataList<<query.value("_name").toString()
            <<query.value("lastDate").toString()
            <<query.value("isEmail").toString()
            <<query.value("_activePhone").toString();
    return dataList;
}

void Phone::action_showHide()
{
    static int status=0;
    if(0==status){
        callsTable->tableView->showColumn(0);
        callsTable->tableView->showColumn(1);
        callsTable->tableView->showColumn(2);
        callsTable->tableView->showColumn(3);
        callsTable->tableView->showColumn(4);
        callsTable->tableView->showColumn(5);
        callsTable->tableView->showColumn(6);
        callsTable->tableView->showColumn(7);
        callsTable->tableView->showColumn(8);
        callsTable->tableView->showColumn(9);
        callsTable->tableView->showColumn(10);
        callsTable->tableView->showColumn(11);
        callsTable->tableView->showColumn(12);
        callsTable->tableView->showColumn(13);
        callsTable->tableView->showColumn(14);
        status=1;
    }else if(1==status){
        callsTable->tableView->hideColumn(0);
        callsTable->tableView->hideColumn(1);
        status=2;
    }else if(2==status){
        callsTable->tableView->hideColumn(0);
        callsTable->tableView->hideColumn(1);
        //callsTable->tableView->hideColumn(2);
        callsTable->tableView->hideColumn(3);
        //callsTable->tableView->hideColumn(4);
        callsTable->tableView->hideColumn(5);
        //callsTable->tableView->hideColumn(6);
        //callsTable->tableView->hideColumn(7);
        //callsTable->tableView->hideColumn(8);
        callsTable->tableView->hideColumn(9);
        callsTable->tableView->hideColumn(10);
        callsTable->tableView->hideColumn(11);
        //callsTable->tableView->hideColumn(12);
        //callsTable->tableView->hideColumn(13);
        //callsTable->tableView->hideColumn(14);
        status=0;
    }
}

void Phone::sig_selectOrders()
{
    if(""!=orderRec->text()){
        orders_presentation->setText(getOrderPresentation(orderRec->text()));
    }
}
