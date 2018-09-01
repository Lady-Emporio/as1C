#ifndef BASECHOOSE_H
#define BASECHOOSE_H

#include "allinclude.h"
#include "Settings/settings.h"
class baseChoose;

class TableChoose:public QTableView
{
Q_OBJECT
    QWidget *realParent;
public:
    TableChoose(QWidget *parent,QWidget *realParent): QTableView(parent),realParent(realParent){}
    void mouseDoubleClickEvent(QMouseEvent *event);
};

class baseChoose : public QWidget
{
    Q_OBJECT
    void makeGui();
    QString defaultFilter;
    QString table;
    TableChoose*tableGui;
    QSqlRelationalTableModel * model;
    QWidget *realParent;
public:
    QPushButton * forFilter;
    QStringList historyFilters;
    explicit baseChoose(QWidget *parent,QString table,QString defaultFilter,QWidget * realParent);

signals:

public slots:
    void action_backToFilters();
};


class LabelChoose:public QLabel{
Q_OBJECT
public:
    QWidget *realParent;
    LabelChoose(QWidget *parent,QWidget *realParent):QLabel(parent),realParent(realParent){this->setStyleSheet("border:1px solid green;");}
    void mouseDoubleClickEvent(QMouseEvent *);

};
#endif // BASECHOOSE_H
