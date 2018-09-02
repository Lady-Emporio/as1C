#include "phoneslist.h"

PhonesList::PhonesList(QWidget *parent,QString parentOrder) : BaseTable(parent),parentOrder(parentOrder)
{
    modelTable=nullptr;
    modelRelational=nullptr;
    modelSql=new QSqlQueryModel(this);
    modelSql->setQuery("SELECT * from phone",Settings::S()->_db);
    if (modelSql->lastError().isValid()){
        QMessageBox msgBox;
        msgBox.setText("Что-то не так с обновлением листа\n"+modelSql->lastError().text());
        msgBox.exec();
    }
    isDelegate=false;
    makeGui();
    tableTree=new PhoneTable(this,parentOrder);
    tableTree->table_name="Phone list";
    tableTree->setModel(modelSql);
    tableTree->setSortingEnabled(true);
    tableView->hide();
    mainLayout->replaceWidget(tableView,tableTree);
    if(""!=parentOrder){
        modelSql->setQuery("SELECT * from phone WHERE _orders='"+parentOrder+"'",Settings::S()->_db);
        QString defaultFilter="_orders='"+parentOrder+"'";
        filter->setText(defaultFilter);
        filter->setEnabled(false);
        setFilterButton->hide();
    }else{
        this->hideFilter();
    }
    commitButton->hide();
}



