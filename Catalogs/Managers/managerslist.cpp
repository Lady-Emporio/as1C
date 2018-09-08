#include "managerslist.h"

ManagersList::ManagersList(QWidget *parent) : BaseTable(parent)
{
    modelTable=new QSqlTableModel(this,Settings::S()->_db);
    modelRelational=nullptr;
    modelSql=nullptr;
    modelTable->setTable("managers");
    makeGui();
    action_refreshModel();
}
