#include "basetable.h"

void BaseTable::makeGui()
{

    mainLayout=new QVBoxLayout(this);
    /*set layout and mainMeny*/{
    this->setLayout(mainLayout);
    mainMenu=new QMenuBar(this);
    mainLayout->setMenuBar(mainMenu);
    }

    QHBoxLayout *filterLayout=new QHBoxLayout(this);
    filter=new QLineEdit(this);
    setFilterButton=new QPushButton("Filter",this);
    filterLayout->addWidget(filter);
    filterLayout->addWidget(setFilterButton);
    mainLayout->addLayout(filterLayout);

    if(!notUseTableView){
        tableView=new BaseTableView(this);
        tableView->setSortingEnabled(true);
        if(modelTable!=nullptr){
            modelTable->setEditStrategy(QSqlTableModel::OnManualSubmit);
            tableView->setModel(modelTable);
            tableView->setContextMenuPolicy(Qt::ActionsContextMenu);
            QAction *   removeAct = new QAction("remove row",this);
            tableView->addAction(removeAct);
            connect(removeAct, SIGNAL(triggered()), this, SLOT(delete_row()));
            mainLayout->addWidget(tableView);
        }else if(modelRelational!=nullptr){
            modelRelational->setEditStrategy(QSqlTableModel::OnManualSubmit);
            tableView->setModel(modelRelational);
            if(isDelegate){
                tableView->setItemDelegate(new QSqlRelationalDelegate(tableView));
            }
        }else if(nullptr!=modelSql){
            tableView->setModel(modelSql);

        }
        mainLayout->addWidget(tableView);
    }
    commitButton=new QPushButton("commit",this);
    mainLayout->addWidget(commitButton);
    mainMenu->addAction("New",this,SLOT(action_addRow()));
    mainMenu->addAction("Refresh",this,SLOT(action_refreshModel()));
    connect(commitButton, SIGNAL(clicked()), this, SLOT(action_commitModel()));
    connect(setFilterButton, SIGNAL(clicked()), this, SLOT(action_filter()));
}

BaseTable::BaseTable(QWidget *parent) : QWidget(parent)
{
    isDelegate=true;
    notUseTableView=false;
}

void BaseTable::hideFilter()
{
    filter->hide();
    setFilterButton->hide();
}

void BaseTable::action_addRow()
{
    if(modelTable!=nullptr){
        modelTable->insertRow(modelTable->rowCount());
    }else if(modelRelational!=nullptr){
        modelRelational->insertRow(modelRelational->rowCount());
    }
}

void BaseTable::action_refreshModel()
{
    if(modelTable!=nullptr){
        if(!modelTable->select()){
            QMessageBox msgBox;
            msgBox.setText("Error with modelTable:"+modelTable->lastError().text());
            msgBox.exec();
        }
    }else if(modelRelational!=nullptr) {
        if(!modelRelational->select()){
            QMessageBox msgBox;
            msgBox.setText("Error with modelRelational"+modelRelational->lastError().text());
            msgBox.exec();
        }
    }else if(modelSql!=nullptr){
        modelSql->setQuery(modelSql->query().lastQuery(),Settings::S()->_db);
        if (modelSql->lastError().isValid()){
            QMessageBox msgBox;
            msgBox.setText("Error with modelSql"+modelSql->lastError().text());
            msgBox.exec();
        }
    }
}

void BaseTable::action_commitModel()
{
    if(modelTable!=nullptr){
        if(!modelTable->submitAll()){
            QMessageBox msgBox;
            msgBox.setText(modelTable->lastError().text());
            msgBox.exec();
        }
    }else if(modelRelational!=nullptr){
        if(!modelRelational->submitAll()){
            QMessageBox msgBox;
            msgBox.setText(modelRelational->lastError().text());
            msgBox.exec();
        }
    }
}

void BaseTable::action_filter()
{
    if(modelTable!=nullptr){
        modelTable->setFilter(filter->text());
        modelTable->select();
    }else if(modelRelational!=nullptr){
        modelRelational->setFilter(filter->text());
        modelRelational->select();
    }
}


void BaseTable::delete_row()
{
    QModelIndex model_index=tableView->currentIndex();
    if(model_index.column()!=-1 or model_index.row()!=-1){
        QMap<int, QVariant> dataItem=modelTable->itemData(model_index);
        const QAbstractItemModel *itemModel = model_index.model();
        if (nullptr == itemModel)
        {
            return;
        }
        int row=model_index.row();
        QString text;
        for (int i = 0; i < modelTable->columnCount(); ++i)
        {
            text+="column "+QString("").setNum(i)+" :"+ modelTable->data(itemModel->index(model_index.row(),i),i).toString()+" \n";
        }
        QMessageBox msgBox;
        msgBox.setText("Need delete row?");
        msgBox.setInformativeText(text);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        int ret = msgBox.exec();
        switch (ret) {
            case QMessageBox::Yes:
                modelTable->removeRow(row);
                break;
        }
    }
}
