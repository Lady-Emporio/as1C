#ifndef PHONESLIST_H
#define PHONESLIST_H

#include "allinclude.h"
#include "BaseObject/basetable.h"

class PhoneTable:public BaseTableView
{
    QString parentOrder;
public:
    PhoneTable(QWidget * parent,QString parentOrder):BaseTableView(parent),parentOrder(parentOrder){}
    void mouseDoubleClickEvent(QMouseEvent *event);
};

class PhonesList : public BaseTable
{
    Q_OBJECT
    PhoneTable * tableTree;
    QString parentOrder;
public:
    explicit PhonesList(QWidget *parent,QString parentOrder);

signals:

public slots:
    void action_addRow();
};

#endif // PHONESLIST_H
