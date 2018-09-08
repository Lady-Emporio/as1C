#include "carslist.h"

CarsList::CarsList(QWidget *parent) : BaseTable(parent)
{
    modelTable=new QSqlTableModel(this,Settings::S()->_db);
    modelRelational=nullptr;
    modelSql=nullptr;
    modelTable->setTable("cars");
    makeGui();
    action_refreshModel();
}
