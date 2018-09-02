#include "dealers_list.h"

Dealers_list::Dealers_list(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    this->setLayout(mainLayout);
    QMenuBar *mainMenu=new QMenuBar(this);
    mainLayout->setMenuBar(mainMenu);
    mainMenu->addAction("Refresh",this,SLOT(action_Refresh()));

    QHBoxLayout *filterLayout=new QHBoxLayout(this);
    filter=new QLineEdit(this);
    QPushButton *setFilterButton=new QPushButton("Filter",this);
    filterLayout->addWidget(filter);
    filterLayout->addWidget(setFilterButton);
    mainLayout->addLayout(filterLayout);


    modelTable=new QSqlTableModel(this,Settings::S()->_db);
    modelTable->setTable("dealers");
    modelTable->select();

    tableView=new DealerTable(this);
    tableView->setModel(modelTable);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSortingEnabled(true);
    connect(setFilterButton, SIGNAL(clicked()), this, SLOT(setFilter()));
    mainLayout->addWidget(tableView);
}

void Dealers_list::setFilter()
{
    modelTable->setFilter(filter->text());
    if(!modelTable->select()){
        QMessageBox msgBox;
        msgBox.setText("Проблема с фильтром:"+filter->text()+"\n"+modelTable->lastError().text());
        msgBox.exec();
    }
}

void Dealers_list::action_Refresh()
{
    modelTable->setFilter("");
    if(!modelTable->select()){
        QMessageBox msgBox;
        msgBox.setText("Проблема с обновлением\n"+modelTable->lastError().text());
        msgBox.exec();
    }
}

void DealerTable::mouseDoubleClickEvent(QMouseEvent *event)
{
    QModelIndex currentI=this->indexAt(event->pos());
    if(currentI!=QModelIndex()){
        int row=currentI.row();
        QSqlTableModel *model=(QSqlTableModel*)this->model();
        QString dealerCode=model->index(row,0).data().toString();
        qDebug()<<dealerCode;
    }
}
