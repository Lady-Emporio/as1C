#include "orders_list.h"

Orders_list::Orders_list(QWidget *parent,bool onlyActive) : BaseTable(parent)
{
    modelTable=nullptr;
    modelRelational=nullptr;
    modelSql=new QSqlQueryModel(this);
    modelSql->setQuery("SELECT * from orders",Settings::S()->_db);
    if (modelSql->lastError().isValid()){
        QMessageBox msgBox;
        msgBox.setText("Что-то не так с обновлением листа\n"+modelSql->lastError().text());
        msgBox.exec();
    }
    isDelegate=false;
    makeGui();
    tableTree=new OrdersTable(this);
    tableTree->table_name="Order list";
    tableTree->setModel(modelSql);
    tableTree->setSortingEnabled(true);
    tableView->hide();
    mainLayout->replaceWidget(tableView,tableTree);
    if(onlyActive){
        modelSql->setQuery("SELECT * from orders WHERE _status='Search!!!'",Settings::S()->_db);
        QString defaultFilter="_status='Search!!!'";
        filter->setText(defaultFilter);
        filter->setEnabled(false);
        setFilterButton->hide();
    }else{
        this->hideFilter();
    }
    commitButton->hide();

    mainMenu->addAction("Armor",this,SLOT(action_Armors()));
}

