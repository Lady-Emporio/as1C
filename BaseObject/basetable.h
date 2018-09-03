#ifndef BASETABLE_H
#define BASETABLE_H

#include "allinclude.h"
#include "Settings/settings.h"
class BaseTableView:public QTableView
{
public:
    QString table_name;
    BaseTableView(QWidget * parent):QTableView(parent){
        table_name="";
    }
};





class BaseTable : public QWidget
{
    Q_OBJECT

public:
    QMenuBar * mainMenu;
    QVBoxLayout *mainLayout;
    void makeGui();
    QSqlTableModel *modelTable;
    QSqlRelationalTableModel *modelRelational;
    QSqlQueryModel * modelSql;
    QPushButton * setFilterButton;
    QLineEdit *filter;
    QPushButton * commitButton;
    BaseTableView *tableView;
    explicit BaseTable(QWidget *parent = 0);
    void hideFilter();
    bool isDelegate;
    bool notUseTableView;
public slots:
    void action_addRow();
    void action_refreshModel();
    void action_commitModel();
    void action_filter();
    void delete_row();
};

#endif // BASETABLE_H
