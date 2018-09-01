#include "basechoose.h"





void baseChoose::makeGui()
{
    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    this->setLayout(mainLayout);
    forFilter=new QPushButton(defaultFilter,this);
    mainLayout->addWidget(forFilter);
    model = new QSqlRelationalTableModel(this,Settings::S()->_db);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable(table);
    model->select();
    TableChoose *tableView=new TableChoose(this,realParent);
    tableView->setModel(model);
    tableView->setColumnWidth(2,300);
    mainLayout->addWidget(tableView);
    model->setFilter(defaultFilter);

    connect(forFilter, SIGNAL(clicked()), this, SLOT(action_backToFilters()));
}

baseChoose::baseChoose(QWidget *parent, QString table, QString defaultFilter,QWidget * realParent):QWidget(parent),table(table),defaultFilter(defaultFilter),realParent(realParent)
{
    makeGui();
}

void baseChoose::action_backToFilters()
{
    if(historyFilters.empty()){
        model->setFilter(defaultFilter);
        forFilter->setText(defaultFilter);
    }else{
        historyFilters.pop_back();
        if(historyFilters.isEmpty()){
            model->setFilter(defaultFilter);
            forFilter->setText(defaultFilter);
        }else{
            QString filterLast=historyFilters.takeLast();
            model->setFilter(filterLast);
            forFilter->setText(filterLast);
        }
    }
}

