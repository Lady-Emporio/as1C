#include "trade_list.h"

Trade_list::Trade_list(QWidget *parent) : BaseTable(parent)
{
    modelTable=new QSqlTableModel(this,Settings::S()->_db);
    modelRelational=nullptr;
    modelSql=nullptr;
    modelTable->setTable("trade");
    makeGui();
    action_refreshModel();
}


