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
private slots:
    void sig_open_desniny();
    void action_refresh_desniny();
};

#endif // DESTINYLIST_H
