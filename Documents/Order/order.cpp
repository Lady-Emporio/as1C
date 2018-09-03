#include "order.h"

void Order::makeGui()
{
    QVBoxLayout * mainLayout=new QVBoxLayout(this);
    this->setLayout(mainLayout);

    subColorTable=new Subtable(this,0,2,code,-1);
    subColorTable->modelTable=nullptr;
    subColorTable->modelRelational=new QSqlRelationalTableModel(this,Settings::S()->_db);
    subColorTable->modelRelational->setTable("orders_color");
    subColorTable->modelRelational->setFilter("_parent='"+code+"'");
    subColorTable->modelRelational->setRelation(1, QSqlRelation("colors", "_id", "_name"));
    subColorTable->makeGui();
    subColorTable->hideFilter();
    subColorTable->commitButton->hide();
    subColorTable->tableView->hideColumn(subColorTable->indexColumnToHide);
    subColorTable->tableView->hideColumn(subColorTable->parentColumnToHide);

    subOptionTable=new Subtable(this,0,2,code,-1);
    subOptionTable->modelRelational=nullptr;
    subOptionTable->modelTable=new QSqlTableModel(this,Settings::S()->_db);
    subOptionTable->modelTable->setTable("orders_option");
    subOptionTable->modelTable->setFilter("_parent='"+code+"'");
    subOptionTable->makeGui();
    subOptionTable->hideFilter();
    subOptionTable->commitButton->hide();
    subOptionTable->tableView->hideColumn(subOptionTable->indexColumnToHide);
    subOptionTable->tableView->hideColumn(subOptionTable->parentColumnToHide);

    subCommentTable=new Subtable(this,0,3,code,1);
    subCommentTable->modelRelational=nullptr;
    subCommentTable->modelTable=new QSqlTableModel(this,Settings::S()->_db);
    subCommentTable->modelTable->setTable("order_timeline");
    subCommentTable->modelTable->setFilter("_parent='"+code+"'");
    subCommentTable->makeGui();
    subCommentTable->hideFilter();
    subCommentTable->commitButton->hide();
    subCommentTable->tableView->hideColumn(subCommentTable->indexColumnToHide);
    subCommentTable->tableView->hideColumn(subCommentTable->parentColumnToHide);

    idRec=new QLineEdit(this);
    dateRec=new QLabel(dateCreate,this);
    managerRec=new QComboBox(this);
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT _code FROM managers WHERE _folder=0 and _mark=0 and _parent='OnlyManagers'",Settings::S()->_db);
    managerRec->setModel(model);
    managerRec->setModelColumn(0);

    clientRec=new QLineEdit(this);

    rlRec=new QLineEdit(this);
    idRec->setText(code);

    carChooseLabel=new LabelChoose(this,this);
    statusRec=new QComboBox(this);
    statusRec->insertItem(0,"Search!!!");
    statusRec->insertItem(1,"Cancel");
    statusRec->insertItem(2,"Found");
    statusRec->insertItem(3,"Wait");

    QHBoxLayout * r1Layout=new QHBoxLayout(this);
    QLabel *idLabel=new QLabel("id",this);
    QLabel *dateLabel=new QLabel("date",this);
    r1Layout->addWidget(idLabel);
    r1Layout->addWidget(idRec);
    r1Layout->addWidget(dateLabel);
    r1Layout->addWidget(dateRec);
    r1Layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    QVBoxLayout * rightLayout=new QVBoxLayout(this);
    QVBoxLayout * leftLayout=new QVBoxLayout(this);
    QHBoxLayout * rightLeftLayout=new QHBoxLayout(this);
    rightLeftLayout->addLayout(leftLayout);
    rightLeftLayout->addLayout(rightLayout);
    mainLayout->addLayout(rightLeftLayout);

    rightLayout->addWidget(statusRec);
    rightLayout->addWidget(subCommentTable);


    QHBoxLayout * managerLayout=new QHBoxLayout(this);
    QLabel *managerLabel=new QLabel("manager",this);
    managerLabel->setSizePolicy(QSizePolicy ::Maximum   , QSizePolicy ::Maximum   );
    managerLayout->addWidget(managerLabel);
    managerLayout->addWidget(managerRec);
    QHBoxLayout * clientLayout=new QHBoxLayout(this);
    QLabel *clientLabel=new QLabel("client",this);
    clientLayout->addWidget(clientLabel);
    clientLayout->addWidget(clientRec);
    QHBoxLayout * RL_Layout=new QHBoxLayout(this);
    QLabel *RLLabel=new QLabel("RL",this);
    RL_Layout->addWidget(RLLabel);
    RL_Layout->addWidget(rlRec);
    QVBoxLayout * carLayout=new QVBoxLayout(this);
    QLabel *carLabel=new QLabel("car",this);
    carLabel->setSizePolicy(QSizePolicy ::Maximum   , QSizePolicy ::Maximum   );
    carLayout->addWidget(carLabel);
    carLayout->addWidget(carChooseLabel);

    leftLayout->addLayout(r1Layout);
    leftLayout->addLayout(managerLayout);
    leftLayout->addLayout(clientLayout);
    leftLayout->addLayout(RL_Layout);
    leftLayout->addLayout(carLayout);
    leftLayout->addWidget(subColorTable);
    leftLayout->addWidget(subOptionTable);
    leftLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    QMenuBar * mainMenu=new QMenuBar(this);
    mainLayout->setMenuBar(mainMenu);
    mainMenu->addAction("Update",this,SLOT(UPDATE_orders()));
    mainMenu->addAction("Refresh all",this,SLOT(SELECT_order()));
    mainMenu->addAction("Phones",this,SLOT(action_phones_list()));
    mainMenu->addAction("Armor",this,SLOT(action_getArmor()));
}

void Order::itsNew()
{
    QSqlQuery query(Settings::S()->_db);
    query.prepare("INSERT INTO orders(_date,_manager,_model,_status) VALUES "
                      " (datetime('now','localtime'),:manager,:model,:status);");
    query.bindValue(":manager","root");
    query.bindValue(":model","1");
    query.bindValue(":status","Search!!!");

    if(!query.exec()){
        QMessageBox msgBox;
        msgBox.setText("Не получается создать нового order\n\n"+Settings::S()->_db.lastError().text()+" |\n "+query.lastError().text()+" |\n "+query.lastQuery());
        msgBox.exec();
        return;
    }
    Settings::S()->_db.commit();
    query.finish();
    if(!query.exec("SELECT _id,_date FROM orders WHERE rowid=last_insert_rowid();")){
        QMessageBox msgBox;
        msgBox.setText("При создании нового order что-то пошло не так с идом\n\n"+Settings::S()->_db.lastError().text()+" |\n "+query.lastError().text()+" |\n "+query.lastQuery());
        msgBox.exec();
        return;
    }
    query.next();
    code=query.value("_id").toString();
    dateCreate=query.value("_date").toString();
}

Order::~Order()
{
    if(DELETEIfNotCreate){
        QSqlQuery query(Settings::S()->_db);
        query.prepare("DELETE FROM  orders WHERE _id =:id;");
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

void Order::setChooseCar(QString indexCar, QString nameCar)
{
    this->indexCar=indexCar;
    carChooseLabel->setText(nameCar);
}

Order::Order(QWidget *parent,QString code) : QWidget(parent),code(code)
{
    DELETEIfNotCreate=false;
    ""==code?this->setObjectName("New order"):
             this->setObjectName("Order:"+code);
    if(""==code){
        DELETEIfNotCreate=true;
        itsNew();
    }
    makeGui();
    if(!DELETEIfNotCreate){
        SELECT_order();
    }

}

void Order::UPDATE_orders()
{
    QSqlQuery query(Settings::S()->_db);
    query.prepare("UPDATE orders SET "
                  " _id=:_id, "
                  " _manager=:_manager, "
                  " _client=:_client, "
                  " _workList=:_workList, "
                  " _model=:_model, "
                  " _status=:_status "
                  " WHERE _id=:oldId;");
    query.bindValue(":_id",idRec->text());
    query.bindValue(":_manager",managerRec->currentText());
    query.bindValue(":_client",clientRec->text());
    query.bindValue(":_workList",rlRec->text());
    query.bindValue(":_model",indexCar);
    query.bindValue(":_status",statusRec->currentText());
    query.bindValue(":oldId",code);
    if(!query.exec()){
        QMessageBox msgBox;
        msgBox.setText("Не получается сохранить order\n\n"+Settings::S()->_db.lastError().text()+" |\n "+query.lastError().text()+" |\n "+query.lastQuery());
        msgBox.exec();
        return;
    }
    if(!subCommentTable->modelTable->submitAll()){
        QMessageBox msgBox;
        msgBox.setText("Не получается сохранить subCommentTable\n\n"+Settings::S()->_db.lastError().text()+" |\n "+subCommentTable->modelTable->lastError().text());
        msgBox.exec();
    };
    if(!subOptionTable->modelTable->submitAll()){
        QMessageBox msgBox;
        msgBox.setText("Не получается сохранить subOptionTable\n\n"+Settings::S()->_db.lastError().text()+" |\n "+subOptionTable->modelTable->lastError().text());
        msgBox.exec();
    };
    if(!subColorTable->modelRelational->submitAll()){
        QMessageBox msgBox;
        msgBox.setText("Не получается сохранить subColorTable\n\n"+Settings::S()->_db.lastError().text()+" |\n "+subColorTable->modelRelational->lastError().text());
        msgBox.exec();
    };
    DELETEIfNotCreate=false;
}

void Order::SELECT_order()
{
    QSqlQuery query(Settings::S()->_db);
    QString sql="SELECT "
                " orders._id as _id, "
                " orders._date as _date, "
                " orders._manager as _manager, "
                " orders._client as _client, "
                " orders._workList as _workList, "
                " orders._model as _model, "
                " orders._status as _status, "
                " cars._name as carName "
                " FROM orders "
                " LEFT JOIN cars ON "
                " cars._id=orders._model "
                " WHERE orders._id=:id;";
    query.prepare(sql);
    query.bindValue(":id",code);
    if(!query.exec()){
        QMessageBox msgBox;
        msgBox.setText("Не получается прочитать order\n\n"+Settings::S()->_db.lastError().text()+" |\n "+query.lastError().text()+" |\n "+query.lastQuery());
        msgBox.exec();
        return;
    }
    query.next();
    carChooseLabel->setText(query.value("carName").toString());
    indexCar=query.value("_model").toString();
    statusRec->setCurrentText(query.value("_status").toString());
    rlRec->setText(query.value("_workList").toString());
    clientRec->setText(query.value("_client").toString());
    managerRec->setCurrentText(query.value("_manager").toString());
    dateRec->setText(query.value("_date").toString());
    idRec->setText(query.value("_id").toString());
    carChooseLabel->setText(query.value("carName").toString());

    if(!subCommentTable->modelTable->select()){
        QMessageBox msgBox;
        msgBox.setText("Не получается select subCommentTable\n\n"+Settings::S()->_db.lastError().text()+" |\n "+subCommentTable->modelTable->lastError().text());
        msgBox.exec();
    };
    if(!subOptionTable->modelTable->select()){
        QMessageBox msgBox;
        msgBox.setText("Не получается select subOptionTable\n\n"+Settings::S()->_db.lastError().text()+" |\n "+subOptionTable->modelTable->lastError().text());
        msgBox.exec();
    };
    if(!subColorTable->modelRelational->select()){
        QMessageBox msgBox;
        msgBox.setText("Не получается select subColorTable\n\n"+Settings::S()->_db.lastError().text()+" |\n "+subColorTable->modelRelational->lastError().text());
        msgBox.exec();
    };
}


