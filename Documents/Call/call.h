#ifndef CALL_H
#define CALL_H

#include "allinclude.h"
#include "Settings/settings.h"
class TableModelForCall : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit TableModelForCall(QObject *parent = 0, QSqlDatabase db = QSqlDatabase());
    QVariant data(const QModelIndex &idx, int role) const;
    void rowsInserted(const QModelIndex &parent, int start, int end);
};

class Call : public QWidget
{
    Q_OBJECT
    QString phoneIndex;
    int indexColumnToHide;
    int parentColumnToHide;
    void makeGui();
    QTableView * tableView;
    int commentIndex;
public:
    TableModelForCall * modelCall;
    explicit Call(QWidget *parent , QString phoneIndex, int indexColumnToHide, int parentColumnToHide,int commentIndex);

signals:

public slots:
    void action_NewRow();
    void action_Refresh();
    void delete_row();
};

#endif // CALL_H
