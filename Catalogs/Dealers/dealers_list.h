#ifndef DEALERS_LIST_H
#define DEALERS_LIST_H

#include "BaseObject/basetable.h"

class DealerTable:public BaseTableView
{
    Q_OBJECT
public:
    DealerTable(QWidget * parent):BaseTableView(parent){}
    void mouseDoubleClickEvent(QMouseEvent *event);
};

class Dealers_list : public QWidget
{
    Q_OBJECT    
public:
    QLineEdit *filter;
    QSqlTableModel * modelTable;
    DealerTable * tableView;
    explicit Dealers_list(QWidget *parent = 0);

signals:

public slots:
    void setFilter();
    void action_Refresh();
};

#endif // DEALERS_LIST_H
