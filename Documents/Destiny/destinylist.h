#ifndef DESTINYLIST_H
#define DESTINYLIST_H

#include "Settings/settings.h"
class DestinyList: public QWidget
{
    Q_OBJECT
    void makeGui();
public:
    QSqlTableModel *modelTable;
    QTableView * tableView;
    DestinyList(QWidget *parent = 0);
};

#endif // DESTINYLIST_H
