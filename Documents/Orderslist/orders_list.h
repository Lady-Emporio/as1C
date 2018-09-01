#ifndef ORDERS_LIST_H
#define ORDERS_LIST_H

#include "BaseObject/basetable.h"



class OrdersTable:public BaseTableView
{
public:
    OrdersTable(QWidget * parent):BaseTableView(parent){}
    void mouseDoubleClickEvent(QMouseEvent *event);
};




class Orders_list : public BaseTable
{
    Q_OBJECT
    OrdersTable * tableTree;
public:
    explicit Orders_list(QWidget *parent = 0, bool onlyActive=false);

signals:

public slots:
    void action_addRow();
    //void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // ORDERS_LIST_H
