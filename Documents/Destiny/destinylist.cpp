#include "destinylist.h"

void DestinyList::makeGui()
{
    QVBoxLayout * mainLayout=new QVBoxLayout(this);
    this->setLayout(mainLayout);

    modelTable=new QSqlTableModel(this,Settings::S()->_db);
    modelTable->setTable("destinyTrade");
    modelTable->select();
    tableView=new QTableView(this);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setModel(modelTable);
    mainLayout->addWidget(tableView);
    QMenuBar * mainMenu=new QMenuBar(this);
    mainLayout->setMenuBar(mainMenu);
    mainMenu->addAction("Open",this,SLOT(sig_open_desniny()));
    mainMenu->addAction("Refresh",this,SLOT(action_refresh_desniny()));
}

DestinyList::DestinyList(QWidget *parent):QWidget(parent)
{
    makeGui();
}



void DestinyList::action_refresh_desniny()
{
    if(!modelTable->select()){
        QMessageBox msgBox;
        msgBox.setText("Error with modelTable:"+modelTable->lastError().text());
        msgBox.exec();
    }
}
