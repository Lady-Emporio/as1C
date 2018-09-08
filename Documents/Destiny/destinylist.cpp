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
}

DestinyList::DestinyList(QWidget *parent):QWidget(parent)
{
    makeGui();
}
