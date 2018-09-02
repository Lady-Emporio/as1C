#include "phone.h"




void Phone::makeGui()
{
    QVBoxLayout * mainLayout=new QVBoxLayout(this);
    this->setLayout(mainLayout);

    QLabel * idLabel=new QLabel("id",this);
    QLabel * orderLabel=new QLabel("Order",this);
    idRec=new QLineEdit(code,this);
    orderRec=new QLineEdit(parentOrder,this);
    statucRec=new QComboBox(this);
    dateRec=new QLabel(dateCreate,this);
    statucRec->insertItem(0,"Search!!!");
    statucRec->insertItem(1,"Cancel");
    statucRec->insertItem(2,"Found");
    statucRec->insertItem(3,"Wait");
    QHBoxLayout * r2Layout=new QHBoxLayout(this);
    QLabel *ordersLabel=new QLabel("orders",this);
    orders_presentation=new QLabel(this);
    r2Layout->addWidget(ordersLabel);
    r2Layout->addWidget(orders_presentation);

    callsTable=new Call(this,code,0,1,13);

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
}

void Phone::itsNew()
{
    qDebug()<<parentOrder;
    QSqlQuery query(Settings::S()->_db);
    if(""!=parentOrder){
        query.prepare("INSERT INTO phone(_orders,_date,_f_status) VALUES "
                      " (:_orders,datetime('now'),:_f_status);");
        query.bindValue(":_f_status","Search!!!");
        query.bindValue(":_orders",parentOrder);
    }else{
        query.prepare("INSERT INTO phone(_f_status) VALUES "
                      " (:_f_status);");
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
    query.bindValue(":_orders",orderRec->text());
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
}
